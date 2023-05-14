// #include <WiFiManager.h> // https://github.com/tzapu/WiFiManager

// #include <SPI.h>
// #include <Wire.h>
// #include <Adafruit_GFX.h>
// #include <Adafruit_SH110X.h>
// //#include <Adafruit_SSD1306.h> // PARA DISPLAY COM SSD1306 sketch também muda!

// // DEFINIÇÕES DE PINOS
// #define PIN_AP 23

// // DEFINIÇÕES
// #define APERTADO LOW

// #define SCREEN_WIDTH 128     // OLED display width, in pixels
// #define SCREEN_HEIGHT 32     // OLED display height, in pixels
// #define SCREEN_ADDRESS 0x3C  ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

// #define OLED_RESET -1

// Adafruit_SH1106G tela(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// // DECLARAÇÃO DE VARIÁVEIS
// char nomeWifi[15] = "MeuESP";
// char senhaWifi[15] = "MinhaSenha";

// void setup() {
//   pinMode(PIN_AP, INPUT_PULLUP);

//   tela.begin(SCREEN_ADDRESS, true);
//   tela.clearDisplay();

//   tela.setTextSize(2);
//   tela.setTextColor(SH110X_WHITE);
//   tela.setCursor(0, 0);
//   tela.print("Iniciando ...");
//   tela.display();

//   // WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
//   // it is a good practice to make sure your code sets wifi mode how you want it.

//   // put your setup code here, to run once:
//   Serial.begin(115200);

//   //WiFiManager, Local intialization. Once its business is done, there is no need to keep it around
//   WiFiManager wm;

//   // reset settings - wipe stored credentials for testing
//   // these are stored by the esp library
//   // wm.resetSettings();

//   // Automatically connect using saved credentials,
//   // if connection fails, it starts an access point with the specified name ( "AutoConnectAP"),
//   // if empty will auto generate SSID, if password is blank it will be anonymous AP (wm.autoConnect())
//   // then goes into a blocking loop awaiting configuration and will return success result

//   if (digitalRead(PIN_AP) == APERTADO) {
//     tela.clearDisplay();
//     tela.setTextSize(2);
//     tela.setCursor(0, 0);
//     tela.print("Resetando ...");
//     tela.display();

//     wm.resetSettings();
//   }

//   bool res;
//   // res = wm.autoConnect(); // auto generated AP name from chipid
//   // res = wm.autoConnect("AutoConnectAP"); // anonymous ap
//   wm.setConfigPortalBlocking(false);
//   res = wm.autoConnect(nomeWifi, senhaWifi); // password protected ap


//   if (!res) {
//     Serial.println("Failed to connect");
//     // ESP.restart();

//     tela.clearDisplay();
//     tela.setTextSize(2);
//     tela.setTextColor(SH110X_WHITE);
//     tela.setCursor(0, 0);
//     tela.print("FEITO!");
//     tela.display();
//     delay(2000);

//     tela.clearDisplay();
//     tela.setCursor(0, 0);
//     tela.setTextSize(1);
//     tela.print("WiFi:  ");
//     tela.println(nomeWifi);
//     tela.print("Senha: ");
//     tela.println(senhaWifi);
//     tela.print("IP:    ");
//     tela.println(WiFi.softAPIP());
//     tela.display();
//     while (true) {
//       wm.process();
//     }
//   }
//   else {
//     //if you get here you have connected to the WiFi
//     Serial.println("connected...yeey :)");

//     tela.clearDisplay();
//     tela.setTextSize(2);
//     tela.setTextColor(SH110X_WHITE);
//     tela.setCursor(0, 0);
//     tela.println("CONECTADO!");
//     tela.setTextSize(1);
//     tela.print("IP: ");
//     tela.println(WiFi.localIP());
//     tela.display();
//   }

// }

// void loop() {
//   // put your main code here, to run repeatedly:


// }