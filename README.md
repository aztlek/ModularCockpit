# Modular Cockpit for Star Citizen

The `Modular Cockpit` is a system of physical controls for *Star Citizen*. 

![Star Citizen Modular Cockpit](controlPanels/images/ControlPanels.png)

It is composed of `Modules` that group several interrelated physical controls such as *switches*, *potentiometers*, *encoders*, etc. For example, the `Power Module` has several *toggle switches* to activate or deactivate power for weapons, shields, or others; it also has *encoders* to increase and decrease power, as well as buttons to quickly set maximum or minimum power.

![Power Module](modules/PowerModule/images/PowerModule_125mmWidth.png)

![Real Power Module](images/RealPowerModule.jpg)

These `Modules` can be connected directly to the computer's USB port and the operating system sees them as a joystick, which makes it easy to perform *keybinding* in *Star Citizen*.

You can also `dock` several `Modules` to a `Control Panel`, which in turn connects to a computer USB port. When multiple `Modules` are docked to a `Control Panel`, the computer sees them all as a single joystick. This is very convenient when having a large number of `Modules` connected, preventing the operating system from failing in recognition and operation of multiple joysticks.

The `Modules` are interchangeable, meaning they can be swapped between `Control Panels` or positions within it. This way, the player can easily configure their cockpit depending on their playstyle.

Also, and very importantly, the `Modular Cockpit` is a free hardware and free software project. This means that anyone can download the designs and firmware, and build their own cockpit. They can also use it for whatever they want. In addition, they are free to study how the `Modular Cockpit` is made and modify it for their needs. Finally, they are free to redistribute it with or without changes as long as they state where it came from and who the authors are.

## Motivations

1. [Star Citizen](https://robertsspaceindustries.com/star-citizen/) is a game with highly enriched functionality and interactivity.
1. Each ship in *Star Citizen* can perform one or more roles.
1. Each player in *Star Citizen* can play one or more roles.
1. Each role has a particular form of interactivity.
1. Each player has a different way of playing.

Therefore, each player needs a unique cockpit adapted to their playstyle. A modular, open, and adaptable cockpit is needed for *Star Citizen*.

### Definitions

<dl>

<dt>Pilot:</dt>
<dd>The user of the <i>Modular Cockpit</i>, its very reason for existing.</dd>

<dt>Component:<dt>
<dd>The atoms that make up the <i>Modular Cockpit</i>. They can be electronic components, such as switches, potentiometers, cables, diodes, microcontrollers; or mechanical ones, such as acrylic sheets, makerbeams, etc.</dd>

<dt>Physical Control:<dt>
<dd>A type of electronic <i>Component</i> through which the <i>Pilot</i> interacts with <i>Star Citizen</i>. For example, switches, buttons, encoders, potentiometers, etc.</dd>

<dt>Module:</dt>
<dd>A grouping of physical controls and components with related functions.</dd>

<dt>Control Panel</dt>
<dd>A structure made with <a href="https://www.makerbeam.com/makerbeam/">10x10 mm Makerbeam</a> (see <i>Frame</i>) where one or several <i>Modules</i> can be <i>docked</i>.</dd>

<dt>Frame:<dt>
<dd>This is a structure built with <a href="https://www.makerbeam.com/makerbeam/">10x10 mm Makerbeam</a>. It has a height of 120 mm and the required width. For this, <a href="https://www.makerbeam.com/makerbeam-100mm-16p-black-makerbeam.html"><i>100 mm vertical beams</i></a> are used and joined to the <a href="https://www.makerbeam.com/makerbeam/10x10mm-profiles-black/"><i>horizontal beams</i></a> with <a href="https://www.makerbeam.com/makerbeam-corner-cubes-12p-black-for-makerbeam.html">MakerBeam Corner Cubes</a>. Several <a href="https://www.makerbeam.com/makerbeam-t-slot-nuts-for-makerbeam-25p.html">T-slot nuts</a> are inserted into the horizontal beams, where the <i>Modules</i> are screwed in with M3 bolts. Any other compatible system can be used. For example, the following image shows a <i>Frame</i> 220 mm wide with its different parts.</dd>

<dt>Docking a Module</dt>
<dd>Physically placing a <i>Module</i> into a <i>Control Panel</i> so that it is fixed and connected.</dd>

<dt>Undocking a Module</dt>
<dd>Removing a <i>Module</i> from the <i>Control Panel</i>, leaving the slot free.</dd>

</dl>

![Frame with measurements](images/Makerbeam_Frame220x120mm_Measurements.png)

## Design Requirements

### Design Requirements for `Modules`

1. Each `Module` must work independently: it should not require other modules or elements to function, except the computer.
1. It must be interchangeable, meaning it can be placed in any `ControlPanel` and work.
1. A module must have only one cable connected to it: the USB cable.
1. A `Module` must be screwable to the `Frame` of a `ControlPanel`.
1. A module groups several related functions. The grouping of these functions must follow the categorization given in the *Keybinding* of *Star Citizen*. For example, there is a *Vehicles - Cockpit* category, so there will be at least one module that covers that category.
1. The aesthetics of the `Modules` must resemble those of military aircraft. See [The Warthod Project](https://thewarthogproject.com/) as a reference.
1. Particular functions, such as backlighting, must work within the `Module`. If there is no dedicated control for this function, it must be controllable from the computer or from a `Control Panel` independently. 

### Design Requirements for Control Panels

1. The front part of a `ControlPanel` is a `Frame` as defined above.
1. Each `ControlPanel` must have only two cables connected to it: the USB cable and the power cable.
1. The `Modules` connected to the `Control Panel` must be seen by the computer as if they were a single joystick. This avoids errors and problems caused by connecting many joysticks simultaneously.
1. A `Control Panel` can centralize particular functions of a `Module`, such as backlighting, to make global changes to these functions.
1. A `Control Panel` controls the ventilation function, which the `Modules` do not handle.


## Modules

1. [Salvage Module](modules/SalvageModule)
1. [Missiles Module](modules/MissilesModule)
1. [Docking and Landing Module](modules/DockingLandingModule)
1. [Shields and Countermeasures Module](modules/ShieldsCountermeasuresModule)
1. [Emotes Module](modules/EmotesModule)
1. [Movement Module](modules/MovementModule)
1. [Weapons Module](modules/WeaponsModule)
1. [Target Cycling Module](modules/TargetCyclingModule)
1. [Camera Module](modules/CameraModule)
1. [Stopwatch Module](modules/StopwatchModule)
1. [Power Module](modules/PowerModule)
1. [Targeting Module](modules/TargetingModule)
1. [Social Module](modules/SocialModule)
1. [Turret Module](modules/TorretModule)
1. [Mining Module](modules/MiningModule)
1. [Cockpit Module](modules/CockpitModule)
1. [Radar and Scanning Module](modules/RadarScanningModule)
1. [Hud Module](modules/HudModule)

## Input Devices

There are several types of input devices:

<dl>

<dt>Mechanical keyboard keys:</dt>
<dd>Mechanical keyboard keys are used for most SC keybindings, since SC is designed around keys.</dd>

<dt>Encoder</dt>
<dd>For cases where there are two keys, one for increasing and another for decreasing the same value, such as increasing or decreasing shield energy.</dd>

<dt>Toggle Switch (ON/OFF)</dt>
<dd>These are used when there are two keys, one to turn on and another to turn off, for example, turning shields on and off.</dd>

<dt>Linear Potentiometer</dt>
<dd>These are used for cases where SC has associated axes, or absolute changes of a value.</dd>

<dt>Joystick</dt>
<dd>Apart from obvious cases where joysticks are used, there are keybindings that by their nature should be controlled with a joystick. A joystick is essentially (at least) two orthogonal potentiometers, allowing control of two orthogonal absolute variables, such as z/y displacement of the camera.</dd>

<dt><a href="https://www.cirque.com/glidepoint-circle-trackpads">GlidePoint® Circle Trackpads</a> (like the Steam Controller)</dt>
<dd>This trackpad works very similarly to an analog joystick, so it can be used for the same purposes.</dd>

</dl>

## Microcontroller

* [Teensy®](https://www.pjrc.com/teensy/) is used for the following reasons:

1. It can function as multiple HID devices simultaneously: it can be a keyboard, joystick, and mouse at the same time, in addition to working with serial. This last feature is necessary to implement a communication protocol with the modules, or in case *Star Citizen* implements something similar to *DCS-BIOS*. Being able to have both keyboard and joystick simultaneously is necessary, for example, for the ```CameraModule```, since *Star Citizen* has no way to map joystick buttons to advanced camera functions and those can only be mapped to keyboard and mouse.
1. It has many input pins. In the case of the *Teensy 4.0*, there are 40 digital pins and 14 analog ones. In the *Teensy 4.1*, there are 55 digital inputs and 18 analog ones. This is necessary since some modules require many inputs, such as the `TargetCyclingModule` with 24 digital inputs or the `PowerModule` with 30 digital inputs.
1. Furthermore, all digital inputs have interrupt capability. This makes input reading much faster. For example, the `TargetCyclingModule` with many encoders is much faster thanks to interrupt capability.
1. It also has many PWM outputs. In the case of the *Teensy 4.0*, there are 31. In the case of the *Teensy 4.1*, there are 35. This is very important for managing the backlighting of the modules.
1. The *Teensy 4.1* has a *USB Host* port used in `Control Panels` to unify the `Modules` so the operating system sees them as a single joystick.
1. It has very good speed, making the *Teensy 4.1* preferable for unifying the modules in the `ControlPanel`.
1. It also has a good amount of memory, which makes this not a concern when coding.

## References

### Components

#### Microcontrollers

##### Teensy

1. [Teensy® 4.1 Development Board](https://www.pjrc.com/store/teensy41.html)
1. [Teensy® 4.0 Development Board](https://www.pjrc.com/store/teensy40.html)

###### Teensy with Arduino

To work with the Arduino IDE at least three parts are required:

1. [Teensyduino](https://www.pjrc.com/teensy/teensyduino.html) Arduino IDE extension for Teensy.
1. [Using USB Keyboard](https://www.pjrc.com/teensy/td_keyboard.html) Library to simulate a keyboard with Teensy.
   1. [Using USB Joystick](https://www.pjrc.com/teensy/td_joystick.html) Library to simulate a joystick with Teensy.
   1. [Keypad Library](https://www.pjrc.com/teensy/td_libs_Keypad.html) Library to read a key matrix.
   1. [Encoder Library](https://www.pjrc.com/teensy/td_libs_Encoder.html) Library to read encoders.

##### Encoders

1. [Rotary Encoder - Illuminated (RGB)](https://www.sparkfun.com/products/15141)  
   A 24-step RGB encoder from Sparkfun.
   1. [Clear Plastic Knob](https://www.sparkfun.com/products/10597) Another knob, but transparent. This would be better for the RGB encoder.
1. [AliExpress: 100 step encoder](https://www.aliexpress.com/w/wholesale-100-step-encoder.html) 100-step encoders on Aliexpress.
1. [Amazon: 5V 60MM Ultra-Thin Hand Wheel Pulse Encoder](https://www.amazon.com/Terminal-Aviation-Aluminum-Positions-Electronic/dp/B07Q75KT49/ref=sr_1_4?crid=2X4LKS9I1QZKQ)
1. [Amazon: CNC rotary encoder search](https://www.amazon.com/s?k=cnc+rotary+encoder)  
   A 100-step encoder like the ones on Aliexpress, but on Amazon.
   1. [100PPR Hand Wheel Encoder for CNC (Black)](https://www.amazon.com/100PPR-Terminal-Electronic-Manual-Encoder/dp/B07G9FVHM8)

###### Encoders with Arduino

1. [Arduino - Rotary encoder Simple Example KY-040](https://create.arduino.cc/projecthub/vandenbrande/arduino-rotary-encoder-simple-example-ky-040-b78752)

###### Encoders with QMK

1. [Encoders: QMK Documentation](https://github.com/qmk/qmk_firmware/blob/master/docs/feature_encoders.md)
1. [How can I use a rotary encoder?](https://docs.splitkb.com/hc/en-us/articles/360010513760-How-can-I-use-a-rotary-encoder-)
1. [QMK Encoder Setup](https://www.youtube.com/watch?v=GLqSPa_Zc2Q)
1. [Hub16 Encoder Configuration](https://www.youtube.com/watch?v=TTCaQ-STD-E)
1. [Using multiple encoders in QMK](https://www.youtube.com/watch?v=DyHxccSvsPs)

### Images

* [xkeys: Printable Legend Templates](https://xkeys.com/usbcustomkeyboards/customprintedlegends.html#LegendTemplates)  
  A template to print xkeys labels.  
  Local file: [SingleKeyLegendTemplate.pdf](images/xkeys/SingleKeyLegendTemplate.pdf)

### openclipart

* Toggle Switch (On/OFF) Black Plastic
  * [Switch On](https://www.openclipart.org/detail/180085/switch-on)  
    On/Off switch in ON position, black plastic.  
    Local file: [ToggleSwitch_ON-OFF_PlasticoNegro-On.svg](images/openclipart/ToggleSwitch_ON-OFF_PlasticoNegro-On.svg)
  * [Switch Off](https://www.openclipart.org/detail/62737/switch-onoff)  
    On/Off switch in OFF position, black plastic.  
    Local file: [ToggleSwitch_ON-OFF_PlasticoNegro-Off.svg](images/openclipart/ToggleSwitch_ON-OFF_PlasticoNegro-Off.svg)
* [Faders from mixing board](https://www.openclipart.org/detail/201691/faders-from-mixing-board)  
  Linear potentiometer.  
  Local file: [faders.svg](images/openclipart/faders.svg)
* [metallic shine](https://www.openclipart.org/detail/307289/metallic-shine)  
  A metallic-looking knob.  
  Local file: [metallic-shine.svg](images/openclipart/metallic-shine.svg)
* [Joystick](https://www.openclipart.org/detail/246396/joystick)  
  A small, schematic joystick.  
  Local file: [JoyStick.svg](images/openclipart/JoyStick.svg)
* [DPST micro push button switch](https://www.openclipart.org/detail/299643/dpst-micro-push-button-switch)  
  A small switch, suitable for protoboards.  
  Local file: [JoyStick.svg](images/openclipart/JoyStick.svg)
* [Blank Generic Keyboard](https://www.openclipart.org/detail/177279/blank-generic-keyboard)  
  Blank keyboard.  
  Local file: [Blank-Generic-Keyboard-Remix-by-Merlin2525.svg](images/openclipart/Blank-Generic-Keyboard-Remix-by-Merlin2525.svg)
* [Non-linear video editing system 1](https://www.openclipart.org/detail/284960/nonlinear-video-editing-system-1)  
  A non-linear video editing console. Knobs and other device icons can be taken from here.  
  Local file: [Non-linear video editing system 1.svg](images/openclipart/Non-linear video editing system 1.svg)
* [Industrial Toggle Switch](https://www.openclipart.org/detail/246398/industrial-toggle-switch)  
  A multi-selector or potentiometer knob.  
  Local file: [TwoPosToggle.svg](images/openclipart/TwoPosToggle.svg)
* [Mixer knobs](https://www.openclipart.org/detail/15859/mixer-knobs)  
  Mixer knobs. Useful for encoder knobs.  
  Local file: [odaibanet-Mixer-knobs.svg](images/openclipart/odaibanet-Mixer-knobs.svg)
* [Power Button Icon](https://www.openclipart.org/detail/253614/power-button-icon)  
  A power key. Useful for constructing xkeys.  
  Local file: [Power-Button-Icon.svg](images/openclipart/Power-Button-Icon.svg)
* [qwerty keyboard](https://www.openclipart.org/detail/37291/qwerty-keyboard)  
  A Mac-style keyboard. Useful for constructing xkeys.  
  Local file: [qwerty-keyboard.svg](images/openclipart/qwerty-keyboard.svg)
* [Keyboard Keys](https://www.openclipart.org/detail/27549/keyboard-keys)  
  Some keyboard keys. Useful for constructing xkeys.  
  Local file: [Simanek-Keyboard-Keys-2.svg](images/openclipart/Simanek-Keyboard-Keys-2.svg)
