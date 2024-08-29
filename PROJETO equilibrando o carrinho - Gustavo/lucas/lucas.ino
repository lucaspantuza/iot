#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP32Servo.h> 

#define POTENTIOMETER_PIN   15
#define BUZZER_PIN          25
#define LED_PIN             33
#define SERVO_PIN           26
#define LDR_PIN             34
#define CHAVE1_PIN          12
#define CHAVE2_PIN          14

Servo myservo;
Adafruit_SSD1306 display = Adafruit_SSD1306(); //OBJETO DO TIPO Adafruit_SSD1306
int analogValuePotenciometro, analogValueLdr;

void setup(){
  Wire.begin(); //INICIALIZA A BIBLIOTECA WIRE
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //INICIALIZA O DISPLAY COM ENDEREÇO I2C 0x3C
  display.setTextColor(WHITE); //DEFINE A COR DO TEXTO
  display.setTextSize(1); //DEFINE O TAMANHO DA FONTE DO TEXTO
  display.clearDisplay(); //LIMPA AS INFORMAÇÕES DO DISPLAY

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(POTENTIOMETER_PIN, INPUT);
  pinMode(LDR_PIN, INPUT);
  pinMode(CHAVE1_PIN, INPUT_PULLUP);
  pinMode(CHAVE2_PIN, INPUT_PULLUP);

  myservo.attach(SERVO_PIN);
}



void loop() {

  analogValuePotenciometro = analogRead(POTENTIOMETER_PIN);
  analogValuePotenciometro = map(analogValuePotenciometro, 0, 4095, 0, 180);

  
  analogValueLdr = analogRead(LDR_PIN);
  analogValueLdr = map(analogValueLdr, 0, 4095, 0, 100);


  display.clearDisplay();
  display.setCursor(10,10);
  display.print(analogValuePotenciometro);
  display.setCursor(50,10);
  display.print(analogValueLdr);

  display.setCursor(50,20);
  if (digitalRead(CHAVE1_PIN) == LOW)
    display.print("*oo");
  else if (digitalRead(CHAVE2_PIN) == LOW)
    display.print("oo*");
  else
    display.print("o*o");

  display.display();
  


  if(analogValuePotenciometro >= 150){// Ligar
    digitalWrite(BUZZER_PIN, HIGH);  
    digitalWrite(LED_PIN, HIGH);  
  }else{// Desligar
    digitalWrite(BUZZER_PIN, LOW);  
    digitalWrite(LED_PIN, LOW); 
  }


  myservo.write(analogValuePotenciometro); 

  delay(50); 
}