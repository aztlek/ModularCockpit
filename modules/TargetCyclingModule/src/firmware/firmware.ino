/*
||
|| @file firmware.ino
|| @author Luis Alejandro Bernal Romero (Aztlek)
|| @description
|| | This firmware is for the "Target Cycling Module" of the "Modular Cockpit".
|| | @see Target Cycling Module: https://github.com/aztlek/ModularCockpit/tree/main/modules/TargetCyclingModule
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

// Keypad
const byte NUMROWS = 4;
const byte NUMCOLS = 2;
char keys[NUMROWS][NUMCOLS] = {
  {  1,  2},
  {  3,  4},
  {  5,  6},
  {  7,  8}
};

byte rowPins[NUMROWS] = { 4, 5, 6, 7};
byte colPins[NUMCOLS] = { 2, 3};

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, NUMROWS, NUMCOLS );

// Encoders
const byte NUMENCODERS = 8;
Encoder encoders[NUMENCODERS] = {
  Encoder( 8,  9),
  Encoder(10, 11),
  Encoder(12, 15),
  Encoder(16, 17),
  Encoder(18, 19),
  Encoder(20, 21),
  Encoder(22, 23),
  Encoder(24, 25),
};

long oldPositionEncoders[NUMENCODERS] = { 0, 0, 0, 0, 0, 0, 0, 0};
long newPositionEncoders[NUMENCODERS];
char encodersKeys[NUMENCODERS * 2] = {
    9, 10, 11, 12,
   13, 14, 15, 16,
   17, 18, 19, 20,
   21, 22, 23, 24
};

// Keys
#define KEY_PRESS_TIME 150

String msg;

const int ledPin = 13;

extern "C" uint32_t set_arm_clock(uint32_t frequency);

void setup() {
  set_arm_clock(24000000);

  // Led as power indicator
  temporarily_increase_led_brightness(1000);
  
#ifdef DEBUG
  Serial.begin(9600);
#endif
}


void loop() {

    // Fills kpd.key[ ] array with up-to 10 active keys.
    // Returns true if there are ANY active keys.
    if (kpd.getKeys())
    {
        for (int i=0; i < LIST_MAX; i++)   // Scan the whole key list.
        {
            if ( kpd.key[i].stateChanged )   // Only find keys that have changed state.
            {
              byte code = (byte)kpd.key[i].kchar;
              KeyState keyState = kpd.key[i].kstate;
              switch (keyState) {  // Report active key state : IDLE, PRESSED, HOLD, or RELEASED
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

    // Encoders
    for(int i = 0; i < NUMENCODERS; i++) {
      byte key;
      newPositionEncoders[i] = encoders[i].read();
      long difEncoder = newPositionEncoders[i] - oldPositionEncoders[i];
      if(difEncoder != 0) {
        if(difEncoder > 0) {
          key = encodersKeys[i * 2] + 1;
          Joystick.button(key, 1);
          delay(KEY_PRESS_TIME);
          Joystick.button(key, 0);
          temporarily_increase_led_brightness(20);
        }
        else if(difEncoder < 0) {
          key = encodersKeys[i * 2];
          Joystick.button(key, 1);
          delay(KEY_PRESS_TIME);
          Joystick.button(key, 0);
          temporarily_increase_led_brightness(20);
        }
        oldPositionEncoders[i] = newPositionEncoders[i]; 
#ifdef DEBUG
        Serial.print("encoder[");
        Serial.print(i);
        Serial.print("]: ");
        Serial.print(difEncoder);
        Serial.print(": key = ");
        Serial.print(key);
        Serial.println();
#endif
      }
    }
}  // End loop


void temporarily_increase_led_brightness(uint32_t msec) {
      analogWrite(ledPin, 100); 
      delay(msec);
      analogWrite(ledPin,   5);  
}

