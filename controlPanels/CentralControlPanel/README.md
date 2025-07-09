# Centras Control Panel

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
1. With that information, fill in the ```buttons_per_joystick[]``` ​​array. You can only add up to 9 modules (limited by the Teensy libraries).
1. Compile/upload and enjoy configuring Star Citizen with your keypads.
