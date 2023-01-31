#include <ESP8266WiFi.h>
#include <ArduinoOTA.h>
#include "Secrets.h"

/* Secrets.h file should contain data as below: */
#ifndef WIFI_SSID
#define WIFI_SSID "xxxxxxxxxx"
#define WIFI_PASSWORD "xxxxxxxxxx"
#endif

/* Configurable variables */
#define BUZZ_PIN 0
#define LED_PIN 2
#define OTA_HOSTNAME "WardrobeDoorAlarm"
#define WAIT_BEFORE_ALARM 60 // in seconds

/* Do not change these unless you know what you are doing */
int waitBeforeAlarm = WAIT_BEFORE_ALARM * 1000;
unsigned long previousMillis = 0;
const long noteDuration = 200;


void setup() {
  pinMode(BUZZ_PIN, OUTPUT);
  digitalWrite(BUZZ_PIN, LOW);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  Serial.begin(115200);
  Serial.println("Startup");
  setupWifi();
  ArduinoOTA.setHostname(OTA_HOSTNAME);
  ArduinoOTA.begin();
}


void loop() {
  unsigned long currentMillis = millis();
  if (millis() > waitBeforeAlarm && currentMillis - previousMillis >= noteDuration) {
    previousMillis = currentMillis;
    tone(BUZZ_PIN, 2000, 100);
    noTone(100);
  }
  ArduinoOTA.handle();
}


void setupWifi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
    delay(100);
  }
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  delay(700);
  digitalWrite(LED_PIN, HIGH);
  delay(1000);
  digitalWrite(LED_PIN, LOW);
}
