/* --------------------------------------- Blynk Setup --------------------------------------- */
// #define BLYNK_TEMPLATE_ID "TMPL2_GVkPbrs"
// #define BLYNK_TEMPLATE_NAME "Joystick"
// #define BLYNK_AUTH_TOKEN "WD_P0ssEBthDrKgi-UTRTtidRLKu58Zn"

// #define BLYNK_PRINT Serial

#include <WiFi.h>
// #include <WiFiClient.h>
// #include <BlynkSimpleEsp32.h>

char ssid[] = "Test";
char pass[] = "31415926";

// BlynkTimer timer;

/* --------------------------------------- ESP-NOW Setup --------------------------------------- */
#include <esp_now.h>

esp_now_peer_info_t peerInfo;
uint8_t broadcastAddress[] = {0xEC, 0xFA, 0xBC, 0x52, 0xD1, 0x06};

typedef struct {
  int x_axis, y_axis, speed;
  bool on;
} Joystick;
Joystick joystick;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("Last packet send status: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Sucess" : "Fail");
}

void OnDataRecv(const uint8_t *mac_addr, const uint8_t *data, int size) {
  // Tratamento ao receber informação.
  memcpy(&joystick, data, sizeof(joystick));
  Serial.print("Bytes received: ");
  Serial.println(size);
}

/* --------------------------------------- Main --------------------------------------- */
#define VRX 36 // VP
#define VRY 39 // VN
#define SPD 35 // D35
#define SW  34 // D34
#define LED 25 // D25

// void pushData() {
//   Blynk.virtualWrite(V4, joystick.x_axis);
//   Blynk.virtualWrite(V5, joystick.y_axis);
// }

void initJoy() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass, 1, NULL, false);
  WiFi.disconnect();

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW.");
    return;
  }

  esp_now_register_send_cb(OnDataSent);

  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 1;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer.");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);
}

void setup() {
  Serial.begin(115200);
  pinMode(SW, INPUT);
  pinMode(LED, OUTPUT);

  initJoy();

  // Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  // timer.setInterval(100L, pushData);
  joystick.on = false;
}

void loop() {
  // Blynk.run();
  // timer.run();

  if (joystick.on) {
    joystick.x_axis = analogRead(VRX);
    joystick.y_axis =  map(analogRead(VRY), 0, 4095, 4095, 0);
    joystick.speed = map(analogRead(SPD), 0, 4095, 0, 255);
    if (joystick.speed < 60) joystick.speed = 60;

    // Serial.print(joystick.x_axis);
    // Serial.print(", ");
    // Serial.print(joystick.y_axis);
    // Serial.print(", ");
    // Serial.println(joystick.speed);

    digitalWrite(LED, HIGH);

    esp_now_send(broadcastAddress, (uint8_t *) &joystick, sizeof(joystick));
  } else digitalWrite(LED, LOW);
  delay(10);
}
