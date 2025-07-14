/*
||
|| @file firmware.ino
|| @author Luis Alejandro Bernal Romero (Aztlek)
|| @description
|| | This firmware is for the "Movement Module" of the "Modular Cockpit"
|| | @see Power Module: https://github.com/aztlek/ModularCockpit/tree/main/modules/MovementModule
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
#include <Bounce.h>
#include <Encoder.h>

// #define DEBUG

// ====== Keypad ======

const byte NUMROWS = 3;
const byte NUMCOLS = 4;
char keys[NUMROWS][NUMCOLS] = {
  {  1,  2,  3,   4},
  {  5,  6,  7,   8},
  {  9, 10,  0,   0}
};

byte rowPins[NUMROWS] = { 5, 4, 3};
byte colPins[NUMCOLS] = { 9, 8, 7, 6};

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, NUMROWS, NUMCOLS );

// ====== Encoders ======

const byte NUMENCODERS = 0;
Encoder encoders[NUMENCODERS] = {
  // Encoder(  7,  8),
  // Encoder(  9, 10),
};

long oldPositionEncoders[NUMENCODERS];
long newPositionEncoders[NUMENCODERS];
char encodersKeys[NUMENCODERS * 2] = {
    // 6, 7,
    // 8, 9,
};

// ====== Toggle Switchs ======

#define NUM_TOGGLE_SWITCHS 1
Bounce toggle_switchs[NUM_TOGGLE_SWITCHS] = {
  Bounce(10, 10),
};

char keys_toggle_switchs[NUM_TOGGLE_SWITCHS * 2] = {
  11, 12,
};


// ====== Multi Switch ======

#define NUM_MULTI_SWITCHS 0
#define NUM_POS_MULTI_SWITCHS 3
Bounce multi_switchs[NUM_MULTI_SWITCHS][NUM_POS_MULTI_SWITCHS] = {
  // { Bounce(7, 10),  Bounce(8, 10), Bounce(9, 10), },
};

char keys_multi_switchs[NUM_MULTI_SWITCHS][NUM_POS_MULTI_SWITCHS] = {
  // { 5, 6, 7,},
};

// ====== Potentiometers ======

#define NUM_POTENTIOMETERS 2
byte potentiometersPins[NUM_POTENTIOMETERS] =
{
  A4, A5
};

int potentiometersOldValues[NUM_POTENTIOMETERS] = {
  0, 0
};
int potentiometersValues[NUM_POTENTIOMETERS] = {
  0, 0
};

const int potentiometerDelta = 8;

// ===========

#define KEY_PRESS_TIME 150
String msg;
const int ledPin = 13;

int code;

extern "C" uint32_t set_arm_clock(uint32_t frequency);

void setup() {
  set_arm_clock(24000000);
  Serial.begin(9600);

  // Led as power indicator
  temporarily_increase_led_brightness(1000);

  pinMode(10, INPUT_PULLUP);


  // ====== Potentiometers ======

  for(unsigned i = 0; i < NUM_POTENTIOMETERS; i++) {
    potentiometersValues[i] = analogRead(potentiometersPins[i]);
    potentiometersOldValues[i] = potentiometersValues[i];
  }
}

void loop() {

  // ====== Keypad ======

  if (kpd.getKeys()) {
      for (unsigned i = 0; i < LIST_MAX; i++) {
          if ( kpd.key[i].stateChanged ) {
            byte code = (byte)kpd.key[i].kchar;
            KeyState keyState = kpd.key[i].kstate;
            switch (keyState) {
                case PRESSED:
                  msg = "PRESSED";
                  Joystick.button(code, 1);
                break;
                case RELEASED:
                  msg = "RELEASED";
                  Joystick.button(code, 0);
                break;
                default:
                break;
            }   
#ifdef DEBUG        
            Serial.printf("kpd.key[%d]: Key = %d ", i, code);
            Serial.println(msg);
#endif
            temporarily_increase_led_brightness(20);
          }
      }
  }


  // ====== Encoders ======

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
      Serial.printf("encoder[%d]: %2ld: key = %d\n", i, difEncoder, key);
  #endif
    }
  }

  // ====== Toggle Switchs ======

  for(unsigned i =0; i < NUM_TOGGLE_SWITCHS; i++) {
    toggle_switchs[i].update();
  }

  for(unsigned i = 0; i < NUM_TOGGLE_SWITCHS; i++) {
    if (toggle_switchs[i].fallingEdge()) {
      code = keys_toggle_switchs[i];
      Joystick.button(code, 1);
      delay(KEY_PRESS_TIME);
      Joystick.button(code, 0);
      temporarily_increase_led_brightness(20);
#ifdef DEBUG                       
      Serial.printf("toggle_switchs[%d]: key %d\n", i, code);
#endif
    }
  }

  for(unsigned i = 0; i < NUM_TOGGLE_SWITCHS; i++) {
    if (toggle_switchs[i].risingEdge()) {
      code = keys_toggle_switchs[i + 1];
      Joystick.button(code, 1);
      delay(KEY_PRESS_TIME);
      Joystick.button(code, 0);
      temporarily_increase_led_brightness(20);
#ifdef DEBUG
      Serial.printf("toggle_switchs[%d]: key %d\n", i, code);
#endif
    }
  }


  // ====== Multi 3 Switch ======

  for(unsigned i = 0; i < NUM_MULTI_SWITCHS; i++) {
    for(unsigned j = 0; j < NUM_POS_MULTI_SWITCHS; j++) {
      multi_switchs[i][j].update();
    }
  }

  for(unsigned i = 0; i < NUM_MULTI_SWITCHS; i++) {
    for(unsigned j = 0; j < NUM_POS_MULTI_SWITCHS; j++) {
      if (multi_switchs[i][j].fallingEdge()) {
        code = keys_multi_switchs[i][j];
        Joystick.button(code, 1);
        delay(KEY_PRESS_TIME);
        Joystick.button(code, 0);
        temporarily_increase_led_brightness(20);
#ifdef DEBUG                       
        Serial.printf("multi_switchs[%d][%d]: key %d\n", i, j, code);
#endif
      }
    }
  }


  // ====== Potentiometers ======

  for(unsigned i = 0; i < NUM_POTENTIOMETERS; i++) {
    potentiometersValues[i] = analogRead(potentiometersPins[i]);
    if(abs(potentiometersValues[i] - potentiometersOldValues[i]) > potentiometerDelta) {    
#ifdef DEBUG
      Serial.printf("potentiometersValues[%d]: %d\n", i, potentiometersValues[i]);
#endif

      switch(i) {
        case 0: Joystick.X(potentiometersValues[i] * 64); break;
        case 1: Joystick.Y(potentiometersValues[i] * 64); break;
        case 2: Joystick.Z(potentiometersValues[i] * 64); break;
        case 3: Joystick.Xrotate(potentiometersValues[i] * 64); break;
        case 4: Joystick.Yrotate(potentiometersValues[i] * 64); break;
        case 5: Joystick.Zrotate(potentiometersValues[i] * 64); break;
        case 6: Joystick.slider(1, potentiometersValues[i] * 64); break;
      }

      potentiometersOldValues[i] = potentiometersValues[i];
      temporarily_increase_led_brightness(20);
    }
  }
}

void temporarily_increase_led_brightness(uint32_t msec) {
      analogWrite(ledPin, 100); 
      delay(msec);
      analogWrite(ledPin,   5);  
}