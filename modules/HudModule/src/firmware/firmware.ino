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

Bounce buttons[] = {
  Bounce(2, 10),
  Bounce(3, 10),
  Bounce(4, 10),
  Bounce(5, 10)
};


const int ledPin = 13;

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
}

void loop() {
  for(unsigned i = 0; i < sizeof(buttons) / sizeof(Bounce); i++) {
    buttons[i].update();
  }

  for(unsigned i = 0; i < sizeof(buttons) / sizeof(Bounce); i++) {
    if (buttons[i].fallingEdge()) {
      Joystick.button(i + 1, 1);
      temporarily_increase_led_brightness(20);
    }
  }
  
  for(unsigned i = 0; i < sizeof(buttons) / sizeof(Bounce); i++) {
    if (buttons[i].risingEdge()) {
      Joystick.button(i + 1, 0);
      temporarily_increase_led_brightness(20);
    }
  }
}

void temporarily_increase_led_brightness(uint32_t msec) {
      analogWrite(ledPin, 100); 
      delay(msec);
      analogWrite(ledPin,   5);  
}