/* --------------------------------------- Blynk Setup --------------------------------------- */
#define BLYNK_TEMPLATE_ID "TMPL2p394rYup"
#define BLYNK_TEMPLATE_NAME "Kart"
#define BLYNK_AUTH_TOKEN "nKebSy43qwB-M_L5QDbV-CfWPZkVkcV4"

// #define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "R.P.D.";
char pass[] = "31415926";

BlynkTimer timer;

/* --------------------------------------- ESP-NOW Setup --------------------------------------- */
#include <espnow.h>

uint8_t broadCastAddress[] = {0xC0, 0x49, 0xEF, 0xCC, 0x29, 0x14};

typedef struct {
  int x_axis = 2048, y_axis = 2048, speed = 100;
  bool on;
} Joystick;
Joystick joystick;

void OnDataSent(uint8_t *mac_addr, uint8_t status) {
  // Serial.print("Last Packet Send Status: ");
  // Serial.println(status == 0 ? "Success" : "Fail");
}

void OnDataRecv(uint8_t *mac_addr, uint8_t *data, uint8_t size) {
  memcpy(&joystick, data, sizeof(joystick));
  // Serial.print("Bytes received: ");
  // Serial.println(size);
}

/* --------------------------------------- Controller Setup --------------------------------------- */
#include <Servo.h>

#define ENS 13 // D7
#define IN1 15 // D5
#define IN2  2 // D4
#define IN3  0 // D3
#define IN4  4 // D2

#define LIF_PIN  14 // D8
#define RIF_PIN  16 // D0

#define TRIG_PIN 1 // TX
#define ECHO_PIN 3 // RX
#define SERV_PIN 5 // D1
#define SWTC_PIN 12 // D6

#define SOUND_SPEED 0.034
#define AVOID_DISTANCE 10

/* Váriaveis Globais */
Servo myServo;
int distance;
bool follower = false;
// int set = 15;
int distance_L, distance_R;

/* --------------------------------------- Blynk Functions --------------------------------------- */
void pushData() {
  Blynk.virtualWrite(V3, joystick.speed);
  Blynk.virtualWrite(V5, joystick.x_axis);
  Blynk.virtualWrite(V6, joystick.y_axis);
  Blynk.virtualWrite(V9, distance);
}

BLYNK_WRITE(V0) {
  if (!joystick.on) joystick.x_axis = param[0].asInt(); 
}

BLYNK_WRITE(V1) {
  if (!joystick.on) joystick.y_axis = param[0].asInt();
}

BLYNK_WRITE(V2) {
  if (param[0].asInt() == 0) {
    joystick.on = false;
    esp_now_send(broadCastAddress, (uint8_t *) &joystick, sizeof(joystick));
    esp_now_deinit();
  } else {
    joystick.on = true;
    connectJoy();
    esp_now_send(broadCastAddress, (uint8_t *) &joystick, sizeof(joystick));
  }
}

BLYNK_WRITE(V4) {
  if (!joystick.on) {
    joystick.speed = param[0].asInt();
    Blynk.virtualWrite(V3, joystick.speed);
  }
}

void connectBlynk() {
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(1000L, pushData);
}

/* --------------------------------------- Controller Functions --------------------------------------- */
void setup() {
  pinMode(ENS, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(LIF_PIN, INPUT);
  pinMode(RIF_PIN, INPUT);

  //********** CHANGE PIN FUNCTION  TO GPIO **********
  //GPIO 1 (TX) swap the pin to a GPIO.
  pinMode(TRIG_PIN, FUNCTION_3); 
  //GPIO 3 (RX) swap the pin to a GPIO.
  pinMode(ECHO_PIN, FUNCTION_3); 
  //**************************************************

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(SERV_PIN, OUTPUT);
  pinMode(SWTC_PIN, INPUT_PULLUP);

  myServo.attach(SERV_PIN, 500, 2400);
  myServo.write(90);

  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(ssid, pass, 1, NULL, true);
  WiFi.disconnect();

  connectBlynk();
  // connectJoy();
}

void loop() {
  Blynk.run();
  timer.run();

  if (digitalRead(SWTC_PIN) == HIGH) follower = true;
  else follower = false;

  distance = getDistance();

  if (follower) {
    if (Blynk.connected()) Blynk.disconnect();
    lineFollower();
  } else {
    if (!Blynk.connected()) connectBlynk();
    moveKart();
  }
}

void connectJoy() {
  if (esp_now_init() != 0) {
    // Serial.println("Error initializing ESP-NOW.");
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_COMBO);

  esp_now_register_send_cb(OnDataSent);

  esp_now_add_peer(broadCastAddress, ESP_NOW_ROLE_COMBO, 1, NULL, 0);

  esp_now_register_recv_cb(OnDataRecv);
}

void moveKart() {
  analogWrite(ENS, joystick.speed);
  if (joystick.y_axis >= 3072 && distance > AVOID_DISTANCE) forward();
  else if (joystick.y_axis < 1024) backward();
  else if (joystick.x_axis >= 3072) right();
  else if (joystick.x_axis < 1024) left();
  else stop();
}

void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void backward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void right() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void left() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void stop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

/* --------------------------------------- Line Follower --------------------------------------- */
void lineFollower() {
  int lif = digitalRead(LIF_PIN);
  int rif = digitalRead(RIF_PIN);

  analogWrite(ENS, 110);
  if (lif == LOW && rif == LOW) {
    if (distance > AVOID_DISTANCE) {
      forward();
    } else {
      stop();
      checkSides();
      compareDistance();
    }
  } else if (lif == HIGH && rif == LOW) {
    left();
  } else if (lif == LOW && rif == HIGH) {
    right();
  } else  if (lif == HIGH && rif == HIGH) {
    stop();
  }
}

int getDistance() {
  /* Disparo do pulso ultrassônico */
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  int microseconds = pulseIn(ECHO_PIN, HIGH);

  int centimeters = microseconds*SOUND_SPEED/2;
  
  return centimeters;
}

void checkSides() {
  myServo.write(5);
  delay(1000);
  distance_L = getDistance();
  myServo.write(175);
  delay(1000);
  distance_R = getDistance();
  myServo.write(90);
}

void compareDistance(){
  if(distance_L < distance_R){
    analogWrite(ENS, 255);
    left();
    delay(250);

    analogWrite(ENS, 110);
    forward();
    delay(500);

    analogWrite(ENS, 255);
    right();
    delay(250);

    analogWrite(ENS, 110);
    forward();
    delay(500);

    analogWrite(ENS, 255);
    right();
    delay(250);
  }
  else{
    analogWrite(ENS, 255);
    right();
    delay(250);

    analogWrite(ENS, 110);
    forward();
    delay(500);

    analogWrite(ENS, 255);
    left();
    delay(250);

    analogWrite(ENS, 110);
    forward();
    delay(500);  

    analogWrite(ENS, 255);
    left();
    delay(250);
  }
}
