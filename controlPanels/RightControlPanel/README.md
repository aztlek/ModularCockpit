# Right Control Panel

## Configuration for more than 128 buttons (Extreme Joystick)

1. Exit the Arduino IDE.
1. Edit the file ```arduino15/packages/teensy/hardware/avr/1.59.0/cores/teensy4/usb_desc.h```.
1. Where it says ```JOYSTICK_SIZE 12```, change it to ```JOYSTICK_SIZE 64```. This is four lines.
1. Save
1. Launch the Arduino IDE.
1. Compile and upload to the Teensy 4.1

## Configure each module

1. Edit the file ```src/CentralControlPanel-Firmware/CentralControlPanel-Firmware.ino``` with the Arduino IDE.

1. Uncomment the ```#define DEBUG``` line.
1. Upload the script to the Teensy.
1. Open the ```Serial Monitor``` via ```Tools -> Serial Monitor```.
1. Now press the buttons on each module.
1. In the ```Serial Monitor```, you'll see something like ```Joystick(n): ..```, where n is the module's position in the USB Hub. Use that number and the total number of buttons per module.
1. With that information, fill in the ```buttons_per_joystick[]``` array. You can only add up to 9 modules (limited by the Teensy libraries).
1. Compile/upload and enjoy configuring Star Citizen with your keypads.

## How to Create a Custom Joystick Specially for the Central Control

### Adding a USB Type-C to the Teensy 4.0

1. Edit the file ```boards.txt``` located in the path ```~/.arduino15/packages/teensy/hardware/avr/1.59.0``` on Linux.

1. Insert the following lines after the line ```teensy41.menu.usb.flightsimjoystick.fake_serial=teensy_gateway```: 
``` 
teensy41.menu.usb.customcontroller2=Modular Cockpit Right Control Panel Joystick 
teensy41.menu.usb.customcontroller2.build.usbtype=MODULAR_COCKPIT_RIGHT_CONTROL_PANEL_JOYSTICK 
teensy41.menu.usb.customcontroller2.upload_port.usbtype=MODULAR_COCKPIT_RIGHT_CONTROL_PANEL_JOYSTICK 
teensy41.menu.usb.customcontroller2.fake_serial=teensy_gateway 
```
1. Save and exit

### Define a new USB type

1. Edit the ```usb_desc.h``` file located in the path ```~/.arduino15/packages/teensy/hardware/avr/1.59.0/cores/teensy4``` on Linux.
1. Insert the following code before the line ```#elif defined(USB_SERIAL_HID)``` 
``` 
#elif defined(MODULAR_COCKPIT_RIGHT_CONTROL_PANEL_JOYSTICK) 
#define VENDOR_ID 0x16C0 
#define PRODUCT_ID 0x0482 
#define MANUFACTURER_NAME {'T','e','e','n','s','y','d','u','i','n','o'} 
#define MANUFACTURER_NAME_LEN 11 
#define PRODUCT_NAME {'M','o','d','u','l','a','r',' ','C','o','c','k','p','i','t',' ','R','i','g','h','t',' ','C','o','n','t','r','o','l',' ','P','a','n','e','l',' ','J','o','y','s','t','i','c','k'} 
#define PRODUCT_NAME_LEN 44 
#define EP0_SIZE 64 
#define NUM_ENDPOINTS 6 
#define NUM_USB_BUFFERS 24 
#define NUM_INTERFACE 5 
#define SEREMU_INTERFACE 2 // Serial emulation 
#define SEREMU_TX_ENDPOINT 2 
#define SEREMU_TX_SIZE 64 
#define SEREMU_TX_INTERVAL 1 
#define SEREMU_RX_ENDPOINT 2 
#define SEREMU_RX_SIZE 32 
#define SEREMU_RX_INTERVAL 2 
#define KEYBOARD_INTERFACE 0 // Keyboard 
#define KEYBOARD_ENDPOINT 3 
#define KEYBOARD_SIZE 8 
#define KEYBOARD_INTERVAL 1 
#define KEYMEDIA_INTERFACE 4 // Keyboard Media Keys 
#define KEYMEDIA_ENDPOINT 4 
#define KEYMEDIA_SIZE 8 
#define KEYMEDIA_INTERVAL 4 
#define MOUSE_INTERFACE 1 // Mouse 
#define MOUSE_ENDPOINT 5 
#define MOUSE_SIZE 8 
#define MOUSE_INTERVAL 1 
#define JOYSTICK_INTERFACE 3 // Joystick 
#define JOYSTICK_ENDPOINT 6 
#define JOYSTICK_SIZE 64 // 12 = normal, 64 = extreme joystick 
#define JOYSTICK_INTERVAL 2 
#define ENDPOINT2_CONFIG ENDPOINT_RECEIVE_INTERRUPT + ENDPOINT_TRANSMIT_INTERRUPT 
#define ENDPOINT3_CONFIG ENDPOINT_RECEIVE_UNUSED + ENDPOINT_TRANSMIT_INTERRUPT 
#define ENDPOINT4_CONFIG ENDPOINT_RECEIVE_UNUSED + ENDPOINT_TRANSMIT_INTERRUPT 
#define ENDPOINT5_CONFIG ENDPOINT_RECEIVE_UNUSED + ENDPOINT_TRANSMIT_INTERRUPT 
#define ENDPOINT6_CONFIG ENDPOINT_RECEIVE_UNUSED + ENDPOINT_TRANSMIT_INTERRUPT
```
1. Save and exit.

### Create the USB HID descriptor

Nothing was done because the 64-bit version, the ```extreme joystick``` was used.

### Modify the ```usb_joystick``` library

Nothing was done because the 64-bit version, the ```extreme joystick``` was used.

### Reconfigure and restart the Arduino IDE

1. Exit the Arduino IDE.

1. Delete the ```arduino-ide``` directory located at
1. On Linux ```~/.config/arduino-ide/```
1. On Windows ```C:\Users\<user name>\AppData\Roaming\arduino-ide\```
1. On MacOS ```~/Library/Application Support/arduino-ide/```
1. Restart the Arduino IDE.

### References for How to Create a Custom Joystick

1. [Create a Custom Joystick With Teensy 4.1](https://www.instructables.com/Create-a-Custom-Joystick-With-the-Teensy-41/)
1. [Changes to custom board option definitions in boards.txt are not picked up #1030](https://github.com/arduino/arduino-ide/issues/1030#issuecomment-1152005617)
