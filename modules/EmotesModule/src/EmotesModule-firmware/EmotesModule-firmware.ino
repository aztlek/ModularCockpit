/*
||
|| @file firmware.ino
|| @author Luis Alejandro Bernal Romero (Aztlek)
|| @description
|| | This firmware is for the "Emotes Module" of the "Modular Cockpit".
|| | @see Mining Module: https://github.com/aztlek/ModularCockpit/tree/main/modules/EmotesModule
|| | @see Modular Cockpit: https://github.com/aztlek/ModularCockpit.
|| #
|| 
|| @license
|| | Copyright (C) 2020 Luis Alejandro Bernal Romero (Aztlek)
|| | 
|| | This program is free software: you can redistribute it and/or modify
|| | it under the terms of the GNU General Public License as published by
|| | the Free Software Foundation, either version 3 of the License, or
|| | (at your option) any later version.
|| | 
|| | This program is distributed in the hope that it will be useful,
|| | but WITHOUT ANY WARRANTY; without even the implied warranty of
|| | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
|| | GNU General Public License for more details.
|| | 
|| | You should have received a copy of the GNU General Public License
|| | along with this program.  If not, see <http://www.gnu.org/licenses/>.
|| #
||
*/
 
#include <Keypad.h>
#include <Encoder.h>

// #define DEBUG

const int BACKLIGHT_LEDS_PIN = 14;

// Keypad
const byte NUMROWS = 5;
const byte NUMCOLS = 5;
char keys[NUMROWS][NUMCOLS] = {
  {  1,  2,  3,  4,  5},
  {  6,  7,  8,  9, 10},
  { 11, 12, 13, 14, 15},
  { 16, 17, 18, 19, 20},
  { 21, 22, 23, 24, 25}
};

byte rowPins[NUMROWS] = {  3,  4,  5,  6,  7};
byte colPins[NUMCOLS] = { 12, 11, 10,  9,  8};

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, NUMROWS, NUMCOLS );


// Keys
#define KEY_PRESS_TIME 150

String msg;

const int ledPin = 13;

extern "C" uint32_t set_arm_clock(uint32_t frequency);

void setup() {
  set_arm_clock(24000000);

  // Led as power indicator
  temporarily_increase_led_brightness(1000);


  // Backlight led
  pinMode(BACKLIGHT_LEDS_PIN, OUTPUT);
  
#ifdef DEBUG
  Serial.begin(9600);
#endif
}


void loop() {

    if (kpd.getKeys()) {
        for (int i=0; i < LIST_MAX; i++) {
            if ( kpd.key[i].stateChanged ) {
              byte code = (byte)kpd.key[i].kchar;
              KeyState keyState = kpd.key[i].kstate;
              switch (keyState) {
                  case PRESSED:
                    msg = " PRESSED.";
                    Joystick.button(code, 1);
                    temporarily_increase_led_brightness(20);
                  break;
                  case RELEASED:
                    msg = " RELEASED.";
                    Joystick.button(code, 0);
                    temporarily_increase_led_brightness(20);
                  break;
                  default:
                  break;
              }   
#ifdef DEBUG                       
              Serial.print("kpd.key[");
              Serial.print(i);
              Serial.print("]: ");
              Serial.print("Key = ");
              Serial.print(code);
              Serial.println(msg);
#endif
            }
        }
    }

  // Backlight led
  if (Serial.available()) {
    int val = Serial.read();
    Serial.printf("1: val = %d\n", val);
    if (val >= 0 && val <= 255) {
      analogWrite(BACKLIGHT_LEDS_PIN, val);
    }
  }
}  // End loop


void temporarily_increase_led_brightness(uint32_t msec) {
      analogWrite(ledPin, 100); 
      delay(msec);
      analogWrite(ledPin,   5);  
}

