/*
||
|| @file CentralControlPanel-Firmware
|| @author Luis Alejandro Bernal Romero (Aztlek)
|| @description
|| | This firmware is for the "Central Control Panel" of the "Modular Cockpit".
|| | Multiple Teensy joysticks can be connected to the pseudohub, and it 
|| | unifies them into a single one so that the operating system only sees 
|| | one joystick. This is done through a USB hub connected to a Teensy 4.1 
|| | via the "USB Host" port.
|| | @see Power Module: https://github.com/aztlek/ModularCockpit/tree/main/controlPanels/CentralControlPanel
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


#include "USBHost_t36.h"

// Configuration
//===============

/*
Here you should enter the total number of keys for each module. The order 
matters, and it must be the order in which they are connected to the USB hub.

If you have any doubts about the connection order, you can uncomment the
DEBUG line, and the Arduino IDE serial console will display the number 
of each module when you press the keys.

You can only put a maximum of 9 modules, due to limitations of the 
USBHost_t36 library.

This version only works for a total of 32 keys for all joysticks!!!
*/

#define DEBUG

int buttons_per_joystick[] = {
  12, // Torret module
   7, // Social module
  30, // Power module
   7, // Dockin and Landing module
   4, // HUD module
  24, // Target Cycling module
   9, // Cockpit module
   8, // Radar Module
  12, // Shields and Counterneasures module
};

//=============

#define NUM_JOYSTICKS ((sizeof(buttons_per_joystick))/(sizeof(int)))

USBHost myusb;
USBHub hubs[] = {
  USBHub(myusb), // 1
  USBHub(myusb), // 2
  USBHub(myusb), // 3
};

USBHIDParser hids[] = {
  USBHIDParser(myusb), USBHIDParser(myusb), USBHIDParser(myusb), USBHIDParser(myusb), USBHIDParser(myusb), // 1
  USBHIDParser(myusb), USBHIDParser(myusb), USBHIDParser(myusb), USBHIDParser(myusb), USBHIDParser(myusb), // 2
  USBHIDParser(myusb), USBHIDParser(myusb), USBHIDParser(myusb), USBHIDParser(myusb), USBHIDParser(myusb), // 3
  USBHIDParser(myusb), USBHIDParser(myusb), USBHIDParser(myusb), USBHIDParser(myusb), USBHIDParser(myusb), // 4
  USBHIDParser(myusb), USBHIDParser(myusb), USBHIDParser(myusb), USBHIDParser(myusb), USBHIDParser(myusb), // 5
  USBHIDParser(myusb), USBHIDParser(myusb), USBHIDParser(myusb), USBHIDParser(myusb), USBHIDParser(myusb), // 6
  USBHIDParser(myusb), USBHIDParser(myusb), USBHIDParser(myusb), USBHIDParser(myusb), USBHIDParser(myusb), // 7
  USBHIDParser(myusb), USBHIDParser(myusb), USBHIDParser(myusb), USBHIDParser(myusb), USBHIDParser(myusb), // 8
  USBHIDParser(myusb), USBHIDParser(myusb), USBHIDParser(myusb), USBHIDParser(myusb), USBHIDParser(myusb), // 9
};

JoystickController joysticks[] = {
  JoystickController(myusb), // 1
  JoystickController(myusb), // 2
  JoystickController(myusb), // 3
  JoystickController(myusb), // 4
  JoystickController(myusb), // 5
  JoystickController(myusb), // 6
  JoystickController(myusb), // 7
  JoystickController(myusb), // 8
  JoystickController(myusb), // 9
};

int psAxis[64];

const int ledPin = 13;

uint32_t old_pressed_buttons[NUM_JOYSTICKS];

void setup()
{
  Serial1.begin(2000000);
  while (!Serial) ;
#ifdef DEBUG
  Serial.println("\n\nUSB Host Joystick Testing");
#endif  
  myusb.begin();
    // Led as power indicator
  temporarily_increase_led_brightness(1000);
}

const int NUM_BUTTOMS_JOYSTICK = 32;

void loop()
{
  myusb.Task();

  int offset = 0;
  for (uint8_t joystick_index = 0; joystick_index < NUM_JOYSTICKS; joystick_index++) {
    offset += ((joystick_index == 0)? 0 : buttons_per_joystick[joystick_index - 1]);
    if (joysticks[joystick_index].available()) {
      uint32_t buttons = joysticks[joystick_index].getButtons();

#ifdef DEBUG
      Serial.printf ("Joystick(%d): ", joystick_index);
#endif

      for (int i = 0; i < NUM_BUTTOMS_JOYSTICK; i++) {
        int value = buttons & (1UL << i);
        int relative_button = i + offset + 1;
#ifdef DEBUG
        Serial.printf("%d(%2d)%s ", i, relative_button, ((value)? "ON ": "OFF"));
#endif
        Joystick.button(relative_button, value);
      }

#ifdef DEBUG
      Serial.println();
#endif      
      joysticks[joystick_index].joystickDataClear();
    }
  }

}

void temporarily_increase_led_brightness(uint32_t msec) {
      analogWrite(ledPin, 100); 
      delay(msec);
      analogWrite(ledPin,   5);  
}