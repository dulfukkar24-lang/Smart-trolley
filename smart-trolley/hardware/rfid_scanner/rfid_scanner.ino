#include <SPI.h>
#include <MFRC522.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>

#define SS_PIN 5
#define RST_PIN 22

#define LED_PIN 2
#define BUZZER_PIN 4

MFRC522 rfid(SS_PIN, RST_PIN);

// WiFi 
const char* ssid = "Ikka";
const char* password = "#1234567#";

// Server URL
String serverName = "http://10.155.141.49:5000/api/rfid/read";

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  SPI.begin(18, 19, 23, 5);
  rfid.PCD_Init();

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi...");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi!");
  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {

  if (!rfid.PICC_IsNewCardPresent())
    return;

  if (!rfid.PICC_ReadCardSerial())
    return;

  // --- BUZZER + LED ON SCAN ---
  digitalWrite(LED_PIN, HIGH);
  digitalWrite(BUZZER_PIN, HIGH);
  delay(200);
  digitalWrite(BUZZER_PIN, LOW);

  // Convert UID to String
  String uid = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    if (rfid.uid.uidByte[i] < 0x10) {
      uid += "0";
    }
    uid += String(rfid.uid.uidByte[i], HEX);
  }
  uid.toUpperCase();

  Serial.println("UID Scanned: " + uid);

  // --- SEND TO SERVER ---
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;

    http.begin(client, serverName);

    http.addHeader("Content-Type", "application/json");
    http.addHeader("Bypass-Tunnel-Reminder", "true");

    String jsonData = "{\"rfid_code\":\"" + uid + "\"}";

    int httpResponseCode = http.POST(jsonData);

    if (httpResponseCode > 0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);

      String payload = http.getString();
      Serial.println("Response: " + payload);

      // --- SUCCESS INDICATION ---
      digitalWrite(LED_PIN, HIGH);
      tone(BUZZER_PIN, 1000);
      delay(300);
      noTone(BUZZER_PIN);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);

      // --- ERROR INDICATION ---
      for(int i=0;i<2;i++){
        digitalWrite(LED_PIN, HIGH);
        digitalWrite(BUZZER_PIN, HIGH);
        delay(150);
        digitalWrite(LED_PIN, LOW);
        digitalWrite(BUZZER_PIN, LOW);
        delay(150);
      }
    }

    http.end();

  } else {
    Serial.println("WiFi Disconnected");
  }

  digitalWrite(LED_PIN, LOW);

  rfid.PICC_HaltA();

  delay(1000);
}
