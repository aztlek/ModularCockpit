unsigned backligth_leds_pins[] = {
  2,
};

#define NUM_BACKLIGHT_LEDS_PINS (sizeof(backligth_leds_pins) / sizeof(unsigned))

#define MODULE_NAME "Module Name"

void setup() {
  // Backlight leds
  for(unsigned backlight_leds_index = 0; backlight_leds_index < NUM_BACKLIGHT_LEDS_PINS; backlight_leds_index++) {
    pinMode(backligth_leds_pins[backlight_leds_index], OUTPUT);
  }

  Serial.begin(9600);
}

void loop() {
  // Backlight leds
  if (Serial.available()) {
    int val = Serial.read();
    Serial.printf("%s: val = %d\n", MODULE_NAME, val);
    if (val >= 0 && val <= 255) {
      for(unsigned backlight_leds_index = 0; backlight_leds_index < NUM_BACKLIGHT_LEDS_PINS; backlight_leds_index++) {
        analogWrite(backligth_leds_pins[backlight_leds_index], val);
      }
    }
  }
}
