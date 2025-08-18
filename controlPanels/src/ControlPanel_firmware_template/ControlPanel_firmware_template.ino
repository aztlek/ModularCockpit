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

/*
Configuration for more than 128 buttons (Extreme Joystick)

    1. Exit the Arduino IDE.
    2. Edit the file arduino15/packages/teensy/hardware/avr/1.59.0/cores/teensy4/usb_desc.h.
    3. Where it says JOYSTICK_SIZE 12, change it to JOYSTICK_SIZE 64. This is four lines.
    4. Save
    5. Launch the Arduino IDE.
    6. Compile and upload to the Teensy 4.1

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

This only works for a total of 128 keys and 7 faxes for all joysticks.
*/

#define DEBUG

// Maximum total of 128 buttons.
int buttons_per_joystick[] = {
  10, // Mining Module
   9, // Salvage  Module
   2, // Stopwatch
   2, // Camera Module
};
#define NUM_JOYSTICKS ((sizeof(buttons_per_joystick))/(sizeof(int)))

// Maximum total of 7 axes.
int axis_per_joystick[NUM_JOYSTICKS] = {
  0, // Mining Module
  0, // Salvage  Module
  0, // Stopwatch
  1, // Camera Module
};

#define USBBAUD 1000000 //115200

uint32_t baud = USBBAUD;
uint32_t format = USBHOST_SERIAL_8N1;

USBHost myusb;

USBSerial_BigBuffer userials[] = {
  USBSerial_BigBuffer(myusb, 1), // 1
  USBSerial_BigBuffer(myusb, 1), // 2
  USBSerial_BigBuffer(myusb, 1), // 3
  USBSerial_BigBuffer(myusb, 1), // 4
  // USBSerial_BigBuffer(myusb, 1), // 5
  // USBSerial_BigBuffer(myusb, 1), // 6
  // USBSerial_BigBuffer(myusb, 1), // 7
  // USBSerial_BigBuffer(myusb, 1), // 8
  // USBSerial_BigBuffer(myusb, 1), // 9
}; // Handles anything up to 512 bytes

#define NUM_USERIALS (sizeof(userials) / sizeof(USBSerial_BigBuffer))

// Define the buffer to use to copy between the two devices
// I am using 512 bytes as that is the largest one that can happen between two T4.x
// if other type devices could easily reduce to something like 64 bytes
char buffer[512];


USBHub hubs[] = {
  USBHub(myusb), // 1
  USBHub(myusb), // 2
  USBHub(myusb), // 3
  USBHub(myusb), // 4
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


#ifdef KEYBOARD_INTERFACE
KeyboardController keyboards[] = {
  KeyboardController(myusb), // 1
  KeyboardController(myusb), // 2
  KeyboardController(myusb), // 3
  KeyboardController(myusb), // 4
  KeyboardController(myusb), // 5
  KeyboardController(myusb), // 6 
  KeyboardController(myusb), // 7
  KeyboardController(myusb), // 8
  KeyboardController(myusb), // 9
};
#define NUM_KEYBOARDS (sizeof(keyboards) / sizeof(keyboards[0]))
#endif // KEYBOARD_INTERFACE

#ifdef MOUSE_INTERFACE
MouseController mouses[] = {
  MouseController(myusb), // 1
  MouseController(myusb), // 2
  MouseController(myusb), // 3
  MouseController(myusb), // 4
  MouseController(myusb), // 5
  MouseController(myusb), // 6
  MouseController(myusb), // 7
  MouseController(myusb), // 8
  MouseController(myusb), // 9
};
#define NUM_MOUSES (sizeof(mouses) / sizeof(mouses[0]))
#endif // MOUSE_INTERFACE

JoystickController joysticks[NUM_JOYSTICKS] = {
  JoystickController(myusb), // 1
  JoystickController(myusb), // 2
  JoystickController(myusb), // 3
  JoystickController(myusb), // 4
  // JoystickController(myusb), // 5
  // JoystickController(myusb), // 6
  // JoystickController(myusb), // 7
  // JoystickController(myusb), // 8
  // JoystickController(myusb), // 9
};

const int NUM_BUTTOMS_JOYSTICK = 32;

#ifdef MOUSE_INTERFACE
bool print_mouse_info = true;
#endif // MOUSE_INTERFACE

uint8_t keyboard_modifiers = 0;  // try to keep a reasonable value

#ifdef MOUSE_INTERFACE
uint8_t mouse_buttons_prev[NUM_MOUSES] = {0};
#endif

#ifdef KEYBOARD_INTERFACE
uint8_t keyboard_last_leds[NUM_KEYBOARDS] = {0};
#endif // KEYBOARD_INTERFACE


const int ledPin = 13;

extern "C" uint32_t set_arm_clock(uint32_t frequency);

void setup() {
  set_arm_clock(24000000);
  delay(250);

  myusb.begin();

  // Serials
  for(unsigned i = 0; i < NUM_USERIALS; i++){
    userials[i].begin(USBBAUD); 
  }
  Serial.begin(USBBAUD);


#ifdef DEBUG
#ifdef KEYBOARD_INTERFACE
  keyboards[0].attachPress(OnPress0);
  keyboards[1].attachPress(OnPress1);
  keyboards[2].attachPress(OnPress2);
  keyboards[3].attachPress(OnPress3);
  keyboards[4].attachPress(OnPress4);
  keyboards[5].attachPress(OnPress5);
  keyboards[6].attachPress(OnPress6);
  keyboards[7].attachPress(OnPress7);
  keyboards[8].attachPress(OnPress8);
#endif //  KEYBOARD_INTERFACE  
#endif // DEBUG

#ifdef KEYBOARD_INTERFACE
  keyboards[0].attachRawPress(OnRawPress0);
  keyboards[0].attachRawRelease(OnRawRelease0);
  keyboards[0].attachExtrasPress(OnHIDExtrasPress0);
  keyboards[0].attachExtrasRelease(OnHIDExtrasRelease0);

  keyboards[1].attachRawPress(OnRawPress1);
  keyboards[1].attachRawRelease(OnRawRelease1);
  keyboards[1].attachExtrasPress(OnHIDExtrasPress1);
  keyboards[1].attachExtrasRelease(OnHIDExtrasRelease1);

  keyboards[2].attachRawPress(OnRawPress2);
  keyboards[2].attachRawRelease(OnRawRelease2);
  keyboards[2].attachExtrasPress(OnHIDExtrasPress2);
  keyboards[2].attachExtrasRelease(OnHIDExtrasRelease2);

  keyboards[3].attachRawPress(OnRawPress3);
  keyboards[3].attachRawRelease(OnRawRelease3);
  keyboards[3].attachExtrasPress(OnHIDExtrasPress3);
  keyboards[3].attachExtrasRelease(OnHIDExtrasRelease3);

  keyboards[4].attachRawPress(OnRawPress4);
  keyboards[4].attachRawRelease(OnRawRelease4);
  keyboards[4].attachExtrasPress(OnHIDExtrasPress4);
  keyboards[4].attachExtrasRelease(OnHIDExtrasRelease4);

  keyboards[5].attachRawPress(OnRawPress5);
  keyboards[5].attachRawRelease(OnRawRelease5);
  keyboards[5].attachExtrasPress(OnHIDExtrasPress5);
  keyboards[5].attachExtrasRelease(OnHIDExtrasRelease5);

  keyboards[6].attachRawPress(OnRawPress6);
  keyboards[6].attachRawRelease(OnRawRelease6);
  keyboards[6].attachExtrasPress(OnHIDExtrasPress6);
  keyboards[6].attachExtrasRelease(OnHIDExtrasRelease6);

  keyboards[7].attachRawPress(OnRawPress7);
  keyboards[7].attachRawRelease(OnRawRelease7);
  keyboards[7].attachExtrasPress(OnHIDExtrasPress7);
  keyboards[7].attachExtrasRelease(OnHIDExtrasRelease7);

  keyboards[8].attachRawPress(OnRawPress8);
  keyboards[8].attachRawRelease(OnRawRelease8);
  keyboards[8].attachExtrasPress(OnHIDExtrasPress8);
  keyboards[8].attachExtrasRelease(OnHIDExtrasRelease8);
#endif // KEYBOARD_INTERFACE

#ifdef MOUSE_INTERFACE
  Mouse.begin();
#endif  

  temporarily_increase_led_brightness(1000);
}


void loop() {
  // digitalToggleFast(13);
  // delay(250);
  myusb.Task();

#ifdef MOUSE_INTERFACE
  // Mouses
  for(unsigned i = 0; i < NUM_MOUSES; i++){
    if (mouses[i].available()) {
#ifdef DEBUG      
      Serial.printf("mouse[%d]: buttons = ", i);
      Serial.print(mouses[i].getButtons());
      Serial.print(",  mouseX = ");
      Serial.print(mouses[i].getMouseX());
      Serial.print(",  mouseY = ");
      Serial.print(mouses[i].getMouseY());
      Serial.print(",  wheel = ");
      Serial.print(mouses[i].getWheel());
      Serial.print(",  wheelH = ");
      Serial.print(mouses[i].getWheelH());
      Serial.println();
      Mouse.move(mouses[i].getMouseX(), mouses[i].getMouseY(), mouses[i].getWheel(), mouses[i].getWheelH());
#endif // DEBUG

      uint8_t btns = mouses[i].getButtons();
      if (btns != mouse_buttons_prev[i]) {
        Mouse.set_buttons(btns & 1U, btns & 4U, btns & 2U, btns & 8U, btns & 16);
        mouse_buttons_prev[i] = btns;    
      }
      mouses[i].mouseDataClear();
    }
  }  // mouses  
#endif //  MOUSE_INTERFACE
  
  // myusb.Task();

  // Joysticks
  unsigned offset = 0;
  unsigned offset_axis = 0;
  for (uint8_t joystick_index = 0; joystick_index < NUM_JOYSTICKS; joystick_index++) {
    if (joysticks[joystick_index].available()) {
      uint32_t buttons = joysticks[joystick_index].getButtons();

#ifdef DEBUG
      Serial.printf("Joystick(%d): ", joystick_index);
#endif

      for (int i = 0; i < NUM_BUTTOMS_JOYSTICK; i++) {
        int value = buttons & (1UL << i);
        int relative_button = i + offset + 1;

#ifdef DEBUG
        Serial.printf("%2d(%2d)%-3s ", i, relative_button, ((value)? "ON": "off"));
#endif

        Joystick.button(relative_button, value);
      }

#ifdef DEBUG
      Serial.println();
#endif      
    

      // Axis

      uint64_t axis_changed_mask = joysticks[joystick_index].axisChangedMask();
      for (uint8_t i = 0; axis_changed_mask != 0; i++, axis_changed_mask >>= 1) {
        if (axis_changed_mask & 1U) {
          unsigned axis_value = joysticks[joystick_index].getAxis(i);
          switch(offset_axis + i) {
            case 0: Joystick.X(axis_value); break;
            case 1: Joystick.Y(axis_value); break;
            case 2: Joystick.Z(axis_value); break;
            case 3: Joystick.Xrotate(axis_value); break;
            case 4: Joystick.Yrotate(axis_value); break;
            case 5: Joystick.Zrotate(axis_value); break;
            case 6: Joystick.slider(1,axis_value); break;
          }
#ifdef DEBUG
          Serial.printf("Joystick[%d] axis[%d]:%d\n", joystick_index, i, axis_value);
#endif      
        }
      }

      joysticks[joystick_index].joystickDataClear();
    }

    offset += buttons_per_joystick[joystick_index];
    offset_axis += axis_per_joystick[joystick_index];
  }

  // Serials

  uint16_t rd, wr, n;

  // check if any data has arrived on the USB virtual serial port
  rd = Serial.available();
  if (rd > 0) {
    for(unsigned i = 0; i < NUM_USERIALS; i++){
      // check if the USB Host serial port is ready to transmit
      wr = userials[i].availableForWrite();
      if (wr > 0) {
        // compute how much data to move, the smallest
        // of rd, wr and the buffer size
        if (rd > wr) rd = wr;
        if (rd > sizeof(buffer)) rd = sizeof(buffer);
        // read data from the USB port
        n = Serial.readBytes((char *)buffer, rd);
        // write it to the USB Host serial port
#ifdef DEBUG        
        Serial.printf("S-U(%u %u)\n", rd, n);
#endif        
        userials[i].write(buffer, n);
      }
    }
  }

  for(unsigned i = 0; i < NUM_USERIALS; i++){
    // check if any data has arrived on the USBHost serial port
    rd = userials[i].available();
    if (rd > 0) {
      // check if the USB virtual serial port is ready to transmit
      wr = Serial.availableForWrite();
      if (wr > 0) {
        // compute how much data to move, the smallest
        // of rd, wr and the buffer size
        if (rd > wr) rd = wr;
        if (rd > 80) rd = 80;
        // read data from the USB host serial port
        n = userials[i].readBytes((char *)buffer, rd);
        // write it to the USB port
#ifdef DEBUG        
        Serial.printf("U-S(%u %u):", rd, n);
#endif        
        Serial.write(buffer, n);
        // // turn on the LED to indicate activity
        // digitalWrite(LED_BUILTIN, HIGH);
        // led_on_time = millis();
      }
    }
  }

  // check if the USB virtual serial wants a new baud rate
  // ignore if 0 as current Serial monitor of Arduino sets to 0..
  uint32_t cur_usb_baud = Serial.baud();
  if (cur_usb_baud && (cur_usb_baud != baud)) {
    baud = cur_usb_baud;
#ifdef DEBUG    
    Serial.printf("DEBUG: baud change: %u\n", baud);
#endif    
    if (baud == 57600) {
      // This ugly hack is necessary for talking
      // to the arduino bootloader, which actually
      // communicates at 58824 baud (+2.1% error).
      // Teensyduino will configure the UART for
      // the closest baud rate, which is 57143
      // baud (-0.8% error).  Serial communication
      // can tolerate about 2.5% error, so the
      // combined error is too large.  Simply
      // setting the baud rate to the same as
      // arduino's actual baud rate works.
      for(unsigned i = 0; i < NUM_USERIALS; i++){
        userials[i].begin(58824);
      }
    } else {
      for(unsigned i = 0; i < NUM_USERIALS; i++){
        userials[i].begin(baud);
      }
    }
  }

#ifdef DEBUG
  ShowUpdatedDeviceListInfo();
#endif  
}

#ifdef KEYBOARD_INTERFACE
//======================================================
// HIDS extra press
//======================================================
void OnHIDExtrasPress0(uint32_t top, uint16_t key) {
  OnHIDExtrasPress(top, key);
}
void OnHIDExtrasPress1(uint32_t top, uint16_t key) {
  OnHIDExtrasPress(top, key);
}
void OnHIDExtrasPress2(uint32_t top, uint16_t key) {
  OnHIDExtrasPress(top, key);
}
void OnHIDExtrasPress3(uint32_t top, uint16_t key) {
  OnHIDExtrasPress(top, key);
}
void OnHIDExtrasPress4(uint32_t top, uint16_t key) {
  OnHIDExtrasPress(top, key);
}
void OnHIDExtrasPress5(uint32_t top, uint16_t key) {
  OnHIDExtrasPress(top, key);
}
void OnHIDExtrasPress6(uint32_t top, uint16_t key) {
  OnHIDExtrasPress(top, key);
}
void OnHIDExtrasPress7(uint32_t top, uint16_t key) {
  OnHIDExtrasPress(top, key);
}
void OnHIDExtrasPress8(uint32_t top, uint16_t key) {
  OnHIDExtrasPress(top, key);
}

void OnHIDExtrasPress(uint32_t top, uint16_t key) {
  if (top == 0xc0000) {
    Keyboard.press(0XE400 | key);
  }
#ifdef DEBUG
  ShowHIDExtrasPress(top, key);
#endif
}
#endif // KEYBOARD_INTERFACE


#ifdef KEYBOARD_INTERFACE
//======================================================
// HIDS extra release
//======================================================
void OnHIDExtrasRelease0(uint32_t top, uint16_t key) {
  OnHIDExtrasRelease(top, key);
}
void OnHIDExtrasRelease1(uint32_t top, uint16_t key) {
  OnHIDExtrasRelease(top, key);
}
void OnHIDExtrasRelease2(uint32_t top, uint16_t key) {
  OnHIDExtrasRelease(top, key);
}
void OnHIDExtrasRelease3(uint32_t top, uint16_t key) {
  OnHIDExtrasRelease(top, key);
}
void OnHIDExtrasRelease4(uint32_t top, uint16_t key) {
  OnHIDExtrasRelease(top, key);
}
void OnHIDExtrasRelease5(uint32_t top, uint16_t key) {
  OnHIDExtrasRelease(top, key);
}
void OnHIDExtrasRelease6(uint32_t top, uint16_t key) {
  OnHIDExtrasRelease(top, key);
}
void OnHIDExtrasRelease7(uint32_t top, uint16_t key) {
  OnHIDExtrasRelease(top, key);
}
void OnHIDExtrasRelease8(uint32_t top, uint16_t key) {
  OnHIDExtrasRelease(top, key);
}

void OnHIDExtrasRelease(uint32_t top, uint16_t key) {
  if (top == 0xc0000) {
    Keyboard.release(0XE400 | key);
  }
#ifdef DEBUG
  Serial.print("HID (");
  Serial.print(top, HEX);
  Serial.print(") key release:");
  Serial.println(key, HEX);
#endif
}
#endif // KEYBOARD_INTERFACE

#ifdef KEYBOARD_INTERFACE
//======================================================
// Raw Press
//======================================================
void OnRawPress0(uint8_t keycode) {
  OnRawPress(0, keyboard_last_leds[0], keycode);
}
void OnRawPress1(uint8_t keycode) {
  OnRawPress(1, keyboard_last_leds[1], keycode);
}
void OnRawPress2(uint8_t keycode) {
  OnRawPress(2, keyboard_last_leds[2], keycode);
}
void OnRawPress3(uint8_t keycode) {
  OnRawPress(3, keyboard_last_leds[3], keycode);
}
void OnRawPress4(uint8_t keycode) {
  OnRawPress(4, keyboard_last_leds[4], keycode);
}
void OnRawPress5(uint8_t keycode) {
  OnRawPress(5, keyboard_last_leds[5], keycode);
}
void OnRawPress6(uint8_t keycode) {
  OnRawPress(6, keyboard_last_leds[6], keycode);
}
void OnRawPress7(uint8_t keycode) {
  OnRawPress(7, keyboard_last_leds[7], keycode);
}
void OnRawPress8(uint8_t keycode) {
  OnRawPress(8, keyboard_last_leds[8], keycode);
}

void OnRawPress(unsigned i, uint8_t &keyboard_last_leds, uint8_t keycode) {
  if (keyboard_leds != keyboard_last_leds) {
    //Serial.printf("New LEDS: %x\n", keyboard_leds);
    keyboard_last_leds = keyboard_leds;
    keyboards[i].LEDS(keyboard_leds);
  }
  if (keycode >= 103 && keycode < 111) {
    // one of the modifier keys was pressed, so lets turn it
    // on global..
    uint8_t keybit = 1 << (keycode - 103);
    keyboard_modifiers |= keybit;
    Keyboard.set_modifier(keyboard_modifiers);
  } else {
    if (keyboards[i].getModifiers() != keyboard_modifiers) {
#ifdef DEBUG
      Serial.printf("Mods mismatch: %x != %x\n", keyboard_modifiers, keyboards[i].getModifiers());
#endif
      keyboard_modifiers = keyboards[i].getModifiers();
      Keyboard.set_modifier(keyboard_modifiers);
    }
    Keyboard.press(0XF000 | keycode);
  }
#ifdef DEBUG
  Serial.printf("keyboards[%d]: OnRawPress keycode: ",i);
  Serial.print(keycode, HEX);
  Serial.print(" Modifiers: ");
  Serial.println(keyboard_modifiers, HEX);
#endif
}
#endif // KEYBOARD_INTERFACE

#ifdef KEYBOARD_INTERFACE
//======================================================
// Raw Relese
//======================================================
//======================================================
// Raw Press
//======================================================
void OnRawRelease0(uint8_t keycode) {
  OnRawRelease(0, keyboard_last_leds[0], keycode);
}
void OnRawRelease1(uint8_t keycode) {
  OnRawRelease(1, keyboard_last_leds[1], keycode);
}
void OnRawRelease2(uint8_t keycode) {
  OnRawRelease(2, keyboard_last_leds[2], keycode);
}
void OnRawRelease3(uint8_t keycode) {
  OnRawRelease(3, keyboard_last_leds[3], keycode);
}
void OnRawRelease4(uint8_t keycode) {
  OnRawRelease(4, keyboard_last_leds[4], keycode);
}
void OnRawRelease5(uint8_t keycode) {
  OnRawRelease(5, keyboard_last_leds[5], keycode);
}
void OnRawRelease6(uint8_t keycode) {
  OnRawRelease(6, keyboard_last_leds[6], keycode);
}
void OnRawRelease7(uint8_t keycode) {
  OnRawRelease(7, keyboard_last_leds[7], keycode);
}
void OnRawRelease8(uint8_t keycode) {
  OnRawRelease(8, keyboard_last_leds[8], keycode);
}

void OnRawRelease(unsigned i, uint8_t &keyboard_last_leds, uint8_t keycode) {
  if (keycode >= 103 && keycode < 111) {
    // one of the modifier keys was pressed, so lets turn it
    // on global..
    uint8_t keybit = 1 << (keycode - 103);
    keyboard_modifiers &= ~keybit;
    Keyboard.set_modifier(keyboard_modifiers);
  } else {
    Keyboard.release(0XF000 | keycode);
  }
#ifdef DEBUG
  Serial.printf("keyboards[%d]: OnRawRelease keycode: ", i);
  Serial.print(keycode, HEX);
  Serial.print(" Modifiers: ");
  Serial.println(keyboards[i].getModifiers(), HEX);
#endif
}
#endif //KEYBOARD_INTERFACE

//=============================================================
// Device and Keyboard Output To Serial objects...
//=============================================================
#ifdef DEBUG
USBDriver *drivers[] = { 

  &userials[0], &userials[1],&userials[2], &userials[3],
  &hubs[0], &hubs[1], &hubs[2], &hubs[3],
  &hids[0], &hids[1], &hids[2], &hids[3], &hids[4], // 1
  &hids[5], &hids[6], &hids[7], &hids[8], &hids[9], // 2
  &hids[10], &hids[11], &hids[12], &hids[13], &hids[14], // 3
  &hids[15], &hids[16], &hids[17], &hids[18], &hids[19], // 4
  &hids[20], &hids[21], &hids[22], &hids[23], &hids[24], // 5
  &hids[25], &hids[26], &hids[27], &hids[28], &hids[29], // 6
  &hids[30], &hids[31], &hids[32], &hids[33], &hids[34], // 7
  &hids[35], &hids[36], &hids[37], &hids[38], &hids[39], // 8
  &hids[40], &hids[41], &hids[42], &hids[43], &hids[44], // 9
};
#define CNT_DEVICES (sizeof(drivers) / sizeof(drivers[0]))
const char *driver_names[CNT_DEVICES] = { 
  "userials[0]", "userials[1]", "userials[2]", "userials[3]", 
  "hubs[0]", "hubs[1]", "hubs[2]","hubs[3]",
  "hids[0]", "hids[1]", "hids[2]", "hids[3]", "hids[4]", // 1
  "hids[5]", "hids[6]", "hids[7]", "hids[8]", "hids[9]", // 2
  "hids[10]", "hids[11]", "hids[12]", "hids[13]", "hids[14]", // 3
  "hids[15]", "hids[16]", "hids[17]", "hids[18]", "hids[19]", // 4
  "hids[20]", "hids[21]", "hids[22]", "hids[23]", "hids[24]", // 5
  "hids[25]", "hids[26]", "hids[27]", "hids[28]", "hids[29]", // 6
  "hids[30]", "hids[31]", "hids[32]", "hids[33]", "hids[34]", // 7
  "hids[35]", "hids[36]", "hids[37]", "hids[38]", "hids[38]", // 8
  "hids[40]", "hids[41]", "hids[42]", "hids[43]", "hids[44]", // 9
};
bool driver_active[CNT_DEVICES] = { false, false, false, false };

// Lets also look at HID Input devices
USBHIDInput *hiddrivers[] = { 
#ifdef KEYBOARD_INTERFACE  
  &keyboards[0], 
  &keyboards[1], 
  &keyboards[2], 
  &keyboards[3],
  &keyboards[4], 
  &keyboards[5], 
  &keyboards[6], 
  &keyboards[7],
  &keyboards[8],
#endif // KEYBOARD_INTERFACE  
#ifdef MOUSE_INTERFACE
  &mouses[0],
  &mouses[1],
  &mouses[2],
  &mouses[3],
  &mouses[4],
  &mouses[5],
  &mouses[6],
  &mouses[7],
  &mouses[8],
#endif // MOUSE_INTERFACE  
  &joysticks[0], 
  &joysticks[1], 
  &joysticks[2], 
  &joysticks[3],
};
#define CNT_HIDDEVICES (sizeof(hiddrivers) / sizeof(hiddrivers[0]))
const char *hid_driver_names[CNT_DEVICES] = { 
#ifdef KEYBOARD_INTERFACE
  "keyboards[0]", 
  "keyboards[1]", 
  "keyboards[2]", 
  "keyboards[3]",
  "keyboards[4]", 
  "keyboards[5]", 
  "keyboards[6]", 
  "keyboards[7]",
  "keyboards[8]",
#endif // KEYBOARD_INTERFACE
#ifdef MOUSE_INTERFACE
  "mouses[0]",
  "mouses[1]",
  "mouses[2]",
  "mouses[3]",
  "mouses[4]",
  "mouses[5]",
  "mouses[6]",
  "mouses[7]",
  "mouses[8]",
#endif // MOUSE_INTERFACE  
  "joysticks[0]",
  "joysticks[1]",
  "joysticks[2]",
  "joysticks[3]",
};
bool hid_driver_active[CNT_DEVICES] = { false };

void ShowUpdatedDeviceListInfo() {
  for (uint8_t i = 0; i < CNT_DEVICES; i++) {
    if (*drivers[i] != driver_active[i]) {
      if (driver_active[i]) {
        Serial.printf("*** Device %s - disconnected ***\n", driver_names[i]);
        driver_active[i] = false;
      } else {
        Serial.printf("*** Device %s %x:%x - connected ***\n", driver_names[i], drivers[i]->idVendor(), drivers[i]->idProduct());
        driver_active[i] = true;

        const uint8_t *psz = drivers[i]->manufacturer();
        if (psz && *psz) Serial.printf("  manufacturer: %s\n", psz);
        psz = drivers[i]->product();
        if (psz && *psz) Serial.printf("  product: %s\n", psz);
        psz = drivers[i]->serialNumber();
        if (psz && *psz) Serial.printf("  Serial: %s\n", psz);
      }
    }
  }

  for (uint8_t i = 0; i < CNT_HIDDEVICES; i++) {
    if (*hiddrivers[i] != hid_driver_active[i]) {
      if (hid_driver_active[i]) {
        Serial.printf("*** HID Device %s - disconnected ***\n", hid_driver_names[i]);
        hid_driver_active[i] = false;
      } else {
        Serial.printf("*** HID Device %s %x:%x - connected ***\n", hid_driver_names[i], hiddrivers[i]->idVendor(), hiddrivers[i]->idProduct());
        hid_driver_active[i] = true;

        const uint8_t *psz = hiddrivers[i]->manufacturer();
        if (psz && *psz) Serial.printf("  manufacturer: %s\n", psz);
        psz = hiddrivers[i]->product();
        if (psz && *psz) Serial.printf("  product: %s\n", psz);
        psz = hiddrivers[i]->serialNumber();
        if (psz && *psz) Serial.printf("  Serial: %s\n", psz);
      }
    }
  }
}
#endif

#ifdef KEYBOARD_INTERFACE
//======================================================
// OnPress
//======================================================
void OnPress0(int key) {
  OnPress(0, key);
}
void OnPress1(int key) {
  OnPress(1, key);
}
void OnPress2(int key) {
  OnPress(2, key);
}
void OnPress3(int key) {
  OnPress(3, key);
}
void OnPress4(int key) {
  OnPress(4, key);
}
void OnPress5(int key) {
  OnPress(5, key);
}
void OnPress6(int key) {
  OnPress(6, key);
}
void OnPress7(int key) {
  OnPress(7, key);
}
void OnPress8(int key) {
  OnPress(8, key);
}


void OnPress(unsigned i, int key) {
  Serial.printf("keyboards[%d]: key '", i);
  switch (key) {
    case KEYD_UP: Serial.print("UP"); break;
    case KEYD_DOWN: Serial.print("DN"); break;
    case KEYD_LEFT: Serial.print("LEFT"); break;
    case KEYD_RIGHT: Serial.print("RIGHT"); break;
    case KEYD_INSERT: Serial.print("Ins"); break;
    case KEYD_DELETE: Serial.print("Del"); break;
    case KEYD_PAGE_UP: Serial.print("PUP"); break;
    case KEYD_PAGE_DOWN: Serial.print("PDN"); break;
    case KEYD_HOME: Serial.print("HOME"); break;
    case KEYD_END: Serial.print("END"); break;
    case KEYD_F1: Serial.print("F1"); break;
    case KEYD_F2: Serial.print("F2"); break;
    case KEYD_F3: Serial.print("F3"); break;
    case KEYD_F4: Serial.print("F4"); break;
    case KEYD_F5: Serial.print("F5"); break;
    case KEYD_F6: Serial.print("F6"); break;
    case KEYD_F7: Serial.print("F7"); break;
    case KEYD_F8: Serial.print("F8"); break;
    case KEYD_F9: Serial.print("F9"); break;
    case KEYD_F10: Serial.print("F10"); break;
    case KEYD_F11: Serial.print("F11"); break;
    case KEYD_F12: Serial.print("F12"); break;
    default: Serial.print((char)key); break;
  }
  Serial.print("'  ");
  Serial.print(key);
  Serial.print(" MOD: ");
  Serial.print(keyboards[i].getModifiers(), HEX);
  Serial.print(" OEM: ");
  Serial.print(keyboards[i].getOemKey(), HEX);
  Serial.print(" LEDS: ");
  Serial.println(keyboards[i].LEDS(), HEX);
}

#ifdef DEBUG
void ShowHIDExtrasPress(uint32_t top, uint16_t key) {
  Serial.print("HID (");
  Serial.print(top, HEX);
  Serial.print(") key press:");
  Serial.print(key, HEX);
  if (top == 0xc0000) {
    switch (key) {
      case 0x20: Serial.print(" - +10"); break;
      case 0x21: Serial.print(" - +100"); break;
      case 0x22: Serial.print(" - AM/PM"); break;
      case 0x30: Serial.print(" - Power"); break;
      case 0x31: Serial.print(" - Reset"); break;
      case 0x32: Serial.print(" - Sleep"); break;
      case 0x33: Serial.print(" - Sleep After"); break;
      case 0x34: Serial.print(" - Sleep Mode"); break;
      case 0x35: Serial.print(" - Illumination"); break;
      case 0x36: Serial.print(" - Function Buttons"); break;
      case 0x40: Serial.print(" - Menu"); break;
      case 0x41: Serial.print(" - Menu  Pick"); break;
      case 0x42: Serial.print(" - Menu Up"); break;
      case 0x43: Serial.print(" - Menu Down"); break;
      case 0x44: Serial.print(" - Menu Left"); break;
      case 0x45: Serial.print(" - Menu Right"); break;
      case 0x46: Serial.print(" - Menu Escape"); break;
      case 0x47: Serial.print(" - Menu Value Increase"); break;
      case 0x48: Serial.print(" - Menu Value Decrease"); break;
      case 0x60: Serial.print(" - Data On Screen"); break;
      case 0x61: Serial.print(" - Closed Caption"); break;
      case 0x62: Serial.print(" - Closed Caption Select"); break;
      case 0x63: Serial.print(" - VCR/TV"); break;
      case 0x64: Serial.print(" - Broadcast Mode"); break;
      case 0x65: Serial.print(" - Snapshot"); break;
      case 0x66: Serial.print(" - Still"); break;
      case 0x80: Serial.print(" - Selection"); break;
      case 0x81: Serial.print(" - Assign Selection"); break;
      case 0x82: Serial.print(" - Mode Step"); break;
      case 0x83: Serial.print(" - Recall Last"); break;
      case 0x84: Serial.print(" - Enter Channel"); break;
      case 0x85: Serial.print(" - Order Movie"); break;
      case 0x86: Serial.print(" - Channel"); break;
      case 0x87: Serial.print(" - Media Selection"); break;
      case 0x88: Serial.print(" - Media Select Computer"); break;
      case 0x89: Serial.print(" - Media Select TV"); break;
      case 0x8A: Serial.print(" - Media Select WWW"); break;
      case 0x8B: Serial.print(" - Media Select DVD"); break;
      case 0x8C: Serial.print(" - Media Select Telephone"); break;
      case 0x8D: Serial.print(" - Media Select Program Guide"); break;
      case 0x8E: Serial.print(" - Media Select Video Phone"); break;
      case 0x8F: Serial.print(" - Media Select Games"); break;
      case 0x90: Serial.print(" - Media Select Messages"); break;
      case 0x91: Serial.print(" - Media Select CD"); break;
      case 0x92: Serial.print(" - Media Select VCR"); break;
      case 0x93: Serial.print(" - Media Select Tuner"); break;
      case 0x94: Serial.print(" - Quit"); break;
      case 0x95: Serial.print(" - Help"); break;
      case 0x96: Serial.print(" - Media Select Tape"); break;
      case 0x97: Serial.print(" - Media Select Cable"); break;
      case 0x98: Serial.print(" - Media Select Satellite"); break;
      case 0x99: Serial.print(" - Media Select Security"); break;
      case 0x9A: Serial.print(" - Media Select Home"); break;
      case 0x9B: Serial.print(" - Media Select Call"); break;
      case 0x9C: Serial.print(" - Channel Increment"); break;
      case 0x9D: Serial.print(" - Channel Decrement"); break;
      case 0x9E: Serial.print(" - Media Select SAP"); break;
      case 0xA0: Serial.print(" - VCR Plus"); break;
      case 0xA1: Serial.print(" - Once"); break;
      case 0xA2: Serial.print(" - Daily"); break;
      case 0xA3: Serial.print(" - Weekly"); break;
      case 0xA4: Serial.print(" - Monthly"); break;
      case 0xB0: Serial.print(" - Play"); break;
      case 0xB1: Serial.print(" - Pause"); break;
      case 0xB2: Serial.print(" - Record"); break;
      case 0xB3: Serial.print(" - Fast Forward"); break;
      case 0xB4: Serial.print(" - Rewind"); break;
      case 0xB5: Serial.print(" - Scan Next Track"); break;
      case 0xB6: Serial.print(" - Scan Previous Track"); break;
      case 0xB7: Serial.print(" - Stop"); break;
      case 0xB8: Serial.print(" - Eject"); break;
      case 0xB9: Serial.print(" - Random Play"); break;
      case 0xBA: Serial.print(" - Select DisC"); break;
      case 0xBB: Serial.print(" - Enter Disc"); break;
      case 0xBC: Serial.print(" - Repeat"); break;
      case 0xBD: Serial.print(" - Tracking"); break;
      case 0xBE: Serial.print(" - Track Normal"); break;
      case 0xBF: Serial.print(" - Slow Tracking"); break;
      case 0xC0: Serial.print(" - Frame Forward"); break;
      case 0xC1: Serial.print(" - Frame Back"); break;
      case 0xC2: Serial.print(" - Mark"); break;
      case 0xC3: Serial.print(" - Clear Mark"); break;
      case 0xC4: Serial.print(" - Repeat From Mark"); break;
      case 0xC5: Serial.print(" - Return To Mark"); break;
      case 0xC6: Serial.print(" - Search Mark Forward"); break;
      case 0xC7: Serial.print(" - Search Mark Backwards"); break;
      case 0xC8: Serial.print(" - Counter Reset"); break;
      case 0xC9: Serial.print(" - Show Counter"); break;
      case 0xCA: Serial.print(" - Tracking Increment"); break;
      case 0xCB: Serial.print(" - Tracking Decrement"); break;
      case 0xCD: Serial.print(" - Pause/Continue"); break;
      case 0xE0: Serial.print(" - Volume"); break;
      case 0xE1: Serial.print(" - Balance"); break;
      case 0xE2: Serial.print(" - Mute"); break;
      case 0xE3: Serial.print(" - Bass"); break;
      case 0xE4: Serial.print(" - Treble"); break;
      case 0xE5: Serial.print(" - Bass Boost"); break;
      case 0xE6: Serial.print(" - Surround Mode"); break;
      case 0xE7: Serial.print(" - Loudness"); break;
      case 0xE8: Serial.print(" - MPX"); break;
      case 0xE9: Serial.print(" - Volume Up"); break;
      case 0xEA: Serial.print(" - Volume Down"); break;
      case 0xF0: Serial.print(" - Speed Select"); break;
      case 0xF1: Serial.print(" - Playback Speed"); break;
      case 0xF2: Serial.print(" - Standard Play"); break;
      case 0xF3: Serial.print(" - Long Play"); break;
      case 0xF4: Serial.print(" - Extended Play"); break;
      case 0xF5: Serial.print(" - Slow"); break;
      case 0x100: Serial.print(" - Fan Enable"); break;
      case 0x101: Serial.print(" - Fan Speed"); break;
      case 0x102: Serial.print(" - Light"); break;
      case 0x103: Serial.print(" - Light Illumination Level"); break;
      case 0x104: Serial.print(" - Climate Control Enable"); break;
      case 0x105: Serial.print(" - Room Temperature"); break;
      case 0x106: Serial.print(" - Security Enable"); break;
      case 0x107: Serial.print(" - Fire Alarm"); break;
      case 0x108: Serial.print(" - Police Alarm"); break;
      case 0x150: Serial.print(" - Balance Right"); break;
      case 0x151: Serial.print(" - Balance Left"); break;
      case 0x152: Serial.print(" - Bass Increment"); break;
      case 0x153: Serial.print(" - Bass Decrement"); break;
      case 0x154: Serial.print(" - Treble Increment"); break;
      case 0x155: Serial.print(" - Treble Decrement"); break;
      case 0x160: Serial.print(" - Speaker System"); break;
      case 0x161: Serial.print(" - Channel Left"); break;
      case 0x162: Serial.print(" - Channel Right"); break;
      case 0x163: Serial.print(" - Channel Center"); break;
      case 0x164: Serial.print(" - Channel Front"); break;
      case 0x165: Serial.print(" - Channel Center Front"); break;
      case 0x166: Serial.print(" - Channel Side"); break;
      case 0x167: Serial.print(" - Channel Surround"); break;
      case 0x168: Serial.print(" - Channel Low Frequency Enhancement"); break;
      case 0x169: Serial.print(" - Channel Top"); break;
      case 0x16A: Serial.print(" - Channel Unknown"); break;
      case 0x170: Serial.print(" - Sub-channel"); break;
      case 0x171: Serial.print(" - Sub-channel Increment"); break;
      case 0x172: Serial.print(" - Sub-channel Decrement"); break;
      case 0x173: Serial.print(" - Alternate Audio Increment"); break;
      case 0x174: Serial.print(" - Alternate Audio Decrement"); break;
      case 0x180: Serial.print(" - Application Launch Buttons"); break;
      case 0x181: Serial.print(" - AL Launch Button Configuration Tool"); break;
      case 0x182: Serial.print(" - AL Programmable Button Configuration"); break;
      case 0x183: Serial.print(" - AL Consumer Control Configuration"); break;
      case 0x184: Serial.print(" - AL Word Processor"); break;
      case 0x185: Serial.print(" - AL Text Editor"); break;
      case 0x186: Serial.print(" - AL Spreadsheet"); break;
      case 0x187: Serial.print(" - AL Graphics Editor"); break;
      case 0x188: Serial.print(" - AL Presentation App"); break;
      case 0x189: Serial.print(" - AL Database App"); break;
      case 0x18A: Serial.print(" - AL Email Reader"); break;
      case 0x18B: Serial.print(" - AL Newsreader"); break;
      case 0x18C: Serial.print(" - AL Voicemail"); break;
      case 0x18D: Serial.print(" - AL Contacts/Address Book"); break;
      case 0x18E: Serial.print(" - AL Calendar/Schedule"); break;
      case 0x18F: Serial.print(" - AL Task/Project Manager"); break;
      case 0x190: Serial.print(" - AL Log/Journal/Timecard"); break;
      case 0x191: Serial.print(" - AL Checkbook/Finance"); break;
      case 0x192: Serial.print(" - AL Calculator"); break;
      case 0x193: Serial.print(" - AL A/V Capture/Playback"); break;
      case 0x194: Serial.print(" - AL Local Machine Browser"); break;
      case 0x195: Serial.print(" - AL LAN/WAN Browser"); break;
      case 0x196: Serial.print(" - AL Internet Browser"); break;
      case 0x197: Serial.print(" - AL Remote Networking/ISP Connect"); break;
      case 0x198: Serial.print(" - AL Network Conference"); break;
      case 0x199: Serial.print(" - AL Network Chat"); break;
      case 0x19A: Serial.print(" - AL Telephony/Dialer"); break;
      case 0x19B: Serial.print(" - AL Logon"); break;
      case 0x19C: Serial.print(" - AL Logoff"); break;
      case 0x19D: Serial.print(" - AL Logon/Logoff"); break;
      case 0x19E: Serial.print(" - AL Terminal Lock/Screensaver"); break;
      case 0x19F: Serial.print(" - AL Control Panel"); break;
      case 0x1A0: Serial.print(" - AL Command Line Processor/Run"); break;
      case 0x1A1: Serial.print(" - AL Process/Task Manager"); break;
      case 0x1A2: Serial.print(" - AL Select Tast/Application"); break;
      case 0x1A3: Serial.print(" - AL Next Task/Application"); break;
      case 0x1A4: Serial.print(" - AL Previous Task/Application"); break;
      case 0x1A5: Serial.print(" - AL Preemptive Halt Task/Application"); break;
      case 0x200: Serial.print(" - Generic GUI Application Controls"); break;
      case 0x201: Serial.print(" - AC New"); break;
      case 0x202: Serial.print(" - AC Open"); break;
      case 0x203: Serial.print(" - AC Close"); break;
      case 0x204: Serial.print(" - AC Exit"); break;
      case 0x205: Serial.print(" - AC Maximize"); break;
      case 0x206: Serial.print(" - AC Minimize"); break;
      case 0x207: Serial.print(" - AC Save"); break;
      case 0x208: Serial.print(" - AC Print"); break;
      case 0x209: Serial.print(" - AC Properties"); break;
      case 0x21A: Serial.print(" - AC Undo"); break;
      case 0x21B: Serial.print(" - AC Copy"); break;
      case 0x21C: Serial.print(" - AC Cut"); break;
      case 0x21D: Serial.print(" - AC Paste"); break;
      case 0x21E: Serial.print(" - AC Select All"); break;
      case 0x21F: Serial.print(" - AC Find"); break;
      case 0x220: Serial.print(" - AC Find and Replace"); break;
      case 0x221: Serial.print(" - AC Search"); break;
      case 0x222: Serial.print(" - AC Go To"); break;
      case 0x223: Serial.print(" - AC Home"); break;
      case 0x224: Serial.print(" - AC Back"); break;
      case 0x225: Serial.print(" - AC Forward"); break;
      case 0x226: Serial.print(" - AC Stop"); break;
      case 0x227: Serial.print(" - AC Refresh"); break;
      case 0x228: Serial.print(" - AC Previous Link"); break;
      case 0x229: Serial.print(" - AC Next Link"); break;
      case 0x22A: Serial.print(" - AC Bookmarks"); break;
      case 0x22B: Serial.print(" - AC History"); break;
      case 0x22C: Serial.print(" - AC Subscriptions"); break;
      case 0x22D: Serial.print(" - AC Zoom In"); break;
      case 0x22E: Serial.print(" - AC Zoom Out"); break;
      case 0x22F: Serial.print(" - AC Zoom"); break;
      case 0x230: Serial.print(" - AC Full Screen View"); break;
      case 0x231: Serial.print(" - AC Normal View"); break;
      case 0x232: Serial.print(" - AC View Toggle"); break;
      case 0x233: Serial.print(" - AC Scroll Up"); break;
      case 0x234: Serial.print(" - AC Scroll Down"); break;
      case 0x235: Serial.print(" - AC Scroll"); break;
      case 0x236: Serial.print(" - AC Pan Left"); break;
      case 0x237: Serial.print(" - AC Pan Right"); break;
      case 0x238: Serial.print(" - AC Pan"); break;
      case 0x239: Serial.print(" - AC New Window"); break;
      case 0x23A: Serial.print(" - AC Tile Horizontally"); break;
      case 0x23B: Serial.print(" - AC Tile Vertically"); break;
      case 0x23C: Serial.print(" - AC Format"); break;
    }
  }
  Serial.println();
}
#endif // DEBUG
#endif // KEYBOARD_INTERFACE

void temporarily_increase_led_brightness(uint32_t msec) {
      analogWrite(ledPin, 100); 
      delay(msec);
      analogWrite(ledPin,   5);  
}