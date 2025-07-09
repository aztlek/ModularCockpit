
#include "USBHost_t36.h"

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
  Serial.println("\n\nUSB Host Joystick Testing");
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
      Serial.printf ("Joystick(%2d): ", joystick_index);
      int num_buttons = 0;
      int *arr_buttons = getPressedButtons(buttons, num_buttons);
      Serial.printf("num_buttons = %d buttons = ", num_buttons);
      for(int b = 0; b < num_buttons; b++) {
        int relative_button = arr_buttons[b] + offset;
        Serial.printf("%d(%d) ", arr_buttons[b], relative_button);
      }
      Serial.println();
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
