const int BACKLIGHT_LEDS_PIN = 2;

void setup() {
  // Backlight led
  pinMode(BACKLIGHT_LEDS_PIN, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // Backlight led
  if (Serial.available()) {
    int val = Serial.read();
    Serial.printf("1: val = %d\n", val);
    if (val >= 0 && val <= 255) {
      analogWrite(BACKLIGHT_LEDS_PIN, val);
    }
  }
}
