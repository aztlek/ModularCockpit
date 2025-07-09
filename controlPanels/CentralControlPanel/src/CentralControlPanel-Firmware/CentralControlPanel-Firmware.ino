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

void setup()
{
  Serial1.begin(2000000);
  while (!Serial) ;

#ifdef DEBUG
  Serial.println("\n\nUSB Host Joystick Testing");
#endif  
  myusb.begin();
}

void loop()
{
  myusb.Task();

  int offset = 0;
  for (uint8_t joystick_index = 0; joystick_index < NUM_JOYSTICKS; joystick_index++) {
    offset += ((joystick_index == 0)? 0 : buttons_per_joystick[joystick_index - 1]);
    if (joysticks[joystick_index].available()) {
      uint32_t buttons = joysticks[joystick_index].getButtons();
#ifdef DEBUG      
      Serial.printf ("Joystick(%2d): ", joystick_index);
#endif      
      int num_buttons = 0;
      int *arr_buttons = getPressedButtons(buttons, num_buttons);
#ifdef DEBUG      
      Serial.printf("num_buttons = %d buttons = ", num_buttons);
#endif      
      for(int b = 0; b < num_buttons; b++) {
        int relative_button = arr_buttons[b] + offset;
#ifdef DEBUG        
        Serial.printf("%d(%d) ", arr_buttons[b], relative_button);
#endif        
      }
#ifdef DEBUG      
      Serial.println();
#endif      
      joysticks[joystick_index].joystickDataClear();
    }
  }

}

int* getPressedButtons(uint32_t n, int& count) {
  static int buttons[32];
  count = 0;
  
  for (int i = 0; i < 32; i++) {
    if (n & (1UL << i)) {
      buttons[count++] = i;
    }
  }

  return buttons;
}
