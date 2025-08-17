const int LED = 2;

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    int val = Serial.read();   // lee un byte 0–255
    Serial.printf("val = %d\n", val);
    if (val >= 0 && val <= 255) {
      analogWrite(LED, val);
    }
  }
}
