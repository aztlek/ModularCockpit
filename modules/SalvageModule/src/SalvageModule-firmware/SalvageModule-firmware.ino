/*
||
|| @file firmware.ino
|| @author Luis Alejandro Bernal Romero (Aztlek)
|| @description
|| | This firmware is for the "Salvage Module" of the "Modular Cockpit"
|| | @see Power Module: https://github.com/aztlek/ModularCockpit/tree/main/modules/SalvageModule
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

#include <Bounce.h>
#include <Encoder.h>

// #define DEBUG

// ====== Buttoms ======

#define NUM_BUTTOMS 5

Bounce buttons[NUM_BUTTOMS] = {
  Bounce(2, 10),
  Bounce(3, 10),
  Bounce(4, 10),
  Bounce(5, 10),
  Bounce(6, 10),
};

char keys[NUM_BUTTOMS] = {
  1, 2, 3, 4, 5
};

// ====== Concoders ======

const byte NUMENCODERS = 2;
Encoder encoders[NUMENCODERS] = {
  Encoder(  7,  8),
  Encoder(  9, 10),
};

long oldPositionEncoders[NUMENCODERS] = { 0, 0};
long newPositionEncoders[NUMENCODERS];
char encodersKeys[NUMENCODERS * 2] = {
    6, 7,
    8, 9,
};

// ====== Toggle Switchs ======

#define NUM_TOGGLE_SWITCHS 0
Bounce toggle_switchs[NUM_TOGGLE_SWITCHS] = {
  // Bounce(6, 10),
};

char keys_toggle_switchs[NUM_TOGGLE_SWITCHS * 2] = {
  // 8, 9, 
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

// ===========

#define KEY_PRESS_TIME 150
const int ledPin = 13;

int code;

extern "C" uint32_t set_arm_clock(uint32_t frequency);

void setup() {
  set_arm_clock(24000000);

  // Led as power indicator
  temporarily_increase_led_brightness(1000);

  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
}

void loop() {

  // ====== Buttoms ======

  for(unsigned i = 0; i < NUM_BUTTOMS; i++) {
    buttons[i].update();
  }

  for(unsigned i = 0; i < NUM_BUTTOMS; i++) {
    if (buttons[i].fallingEdge()) {
      code = keys[i];
      Joystick.button(code , 1);
      temporarily_increase_led_brightness(20);
#ifdef DEBUG
      Serial.printf("buttoms[%d]: key %d, ON\n", i, code);
#endif
    }
  }
  
  for(unsigned i = 0; i < NUM_BUTTOMS; i++) {
    if (buttons[i].risingEdge()) {
      code = keys[i];
      Joystick.button(code, 1);
      delay(KEY_PRESS_TIME);
      Joystick.button(code, 0);
      temporarily_increase_led_brightness(20);
#ifdef DEBUG
      Serial.printf("buttoms[%d]: key %d, OFF\n", i, code);
#endif
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
      Serial.printf("toggle_switchs[%d]: key %d, \n", i, code);
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
}

void temporarily_increase_led_brightness(uint32_t msec) {
      analogWrite(ledPin, 100); 
      delay(msec);
      analogWrite(ledPin,   5);  
}