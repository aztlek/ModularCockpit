/*
||
|| @file firmware.ino
|| @author Luis Alejandro Bernal Romero (Aztlek)
|| @description
|| | This firmware is for the "HUD Module" of the "Modular Cockpit".
|| | @see Power Module: https://github.com/aztlek/ModularCockpit/tree/main/modules/HudModule
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

// #define DEBUG

#define NUM_BUTTOMS 6

Bounce buttons[NUM_BUTTOMS] = {
  Bounce(2, 10),
  Bounce(3, 10),
  Bounce(4, 10),
  Bounce(5, 10),
  Bounce(6, 10),
  Bounce(7, 10)
};

#define TOGGLE_SWITCH 0
#define isToggleSwitch(i) ((i) == (TOGGLE_SWITCH))
#define KEY_PRESS_TIME 150

const int ledPin = 13;

String msg;
int code;

extern "C" uint32_t set_arm_clock(uint32_t frequency);

void setup() {
  set_arm_clock(24000000);

  // Led as power indicator
  temporarily_increase_led_brightness(1000);

  // Buttoms
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
}

void loop() {
  for(unsigned i = 0; i < NUM_BUTTOMS; i++) {
    buttons[i].update();
  }

  for(unsigned i = 0; i < NUM_BUTTOMS; i++) {
    if (buttons[i].fallingEdge()) {
      if(isToggleSwitch(i)) {
      msg = "ON delay OFF";
        code = i + 1;
        Joystick.button(code, 1);
        delay(KEY_PRESS_TIME);
        Joystick.button(code, 0);
      }
      else {
      msg = "ON";
        code = i + 2;
        Joystick.button(code , 1);
      }
      temporarily_increase_led_brightness(20);
#ifdef DEBUG                       
      Serial.print("buttoms[");
      Serial.print(i);
      Serial.print("]: ");
      Serial.print("Key ");
      Serial.print(code);
      Serial.print(", ");
      Serial.println(msg);
#endif
    }
  }
  
  for(unsigned i = 0; i < NUM_BUTTOMS; i++) {
    if (buttons[i].risingEdge()) {
      if(isToggleSwitch(i)) {
        msg = "ON delay OFF";
        code = i + 2;
        Joystick.button(code, 1);
        delay(KEY_PRESS_TIME);
        Joystick.button(code, 0);
      }
      else {
        msg = "OFF";
        code = i + 2;
        Joystick.button(code, 0);
      }
      temporarily_increase_led_brightness(20);
#ifdef DEBUG                       
      Serial.print("buttoms[");
      Serial.print(i);
      Serial.print("]: ");
      Serial.print("Key ");
      Serial.print(code);
      Serial.print(", ");
      Serial.println(msg);
#endif
    }
  }
}

void temporarily_increase_led_brightness(uint32_t msec) {
      analogWrite(ledPin, 100); 
      delay(msec);
      analogWrite(ledPin,   5);  
}