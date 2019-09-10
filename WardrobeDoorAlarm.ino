#define BUZZ_PIN 0

void setup() {
  pinMode(BUZZ_PIN, OUTPUT);
  digitalWrite(BUZZ_PIN, LOW);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.begin(115200);
  Serial.println("Startup");
  delay(30000);
  Serial.println("End of wait");
}

void loop() {
  tone(BUZZ_PIN, 2000, 100);
  noTone(100);
  delay(200);
}
