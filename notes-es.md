# Notas de Star Citizen Button Box V2

La idea es hacer una botonera que sea más funcional que la anterior
[StarCitizen_6_ButtonBox](https://github.com/aztlek/StarCitizen_6_ButtonBox) que
sólo era una prueba de concepto. Más funcional en el sentido que si se use para
jugar a [Star Citizen](https://robertsspaceindustries.com/star-citizen/).

## Requerimientos del teclado

1. Debe ser modular.
1. La estética debe ser una combinación de:
   * [The Warthog Project](https://www.youtube.com/@thewarthogproject)
   * La estética de las naves de SC. Por ejemplo de la Terrapin y la Freelancer.
1. Los dispositivos de entrada deben ser identificables.
   * Teclas que se puedan marcar.
   * Los otros dispositivos se idedentifican marcandolos en el panel.
1. Al ancho máximo de la botonera debe ser de unos 82 cms que corresponde con el
   ancho de un monitor de 34'' QHD.
1. El numero total de keybindings en SC es de 502, según [Número de teclas en Star Citizen](docs/NumberOfKeys_StarCitizen.ods),
   Por lo que la botonera debe facilitar el uso de este gran número de entradas.

## Módulos

El Button Box tiene un diseño modular. Cado módulo corresponde a un conjunto de
funcionalidades relacionadas, keybindings.

* [Módulo de Potencia](modules/PowerModule/notes-es.md)
* [Módulo de Cámara](modules/CameraModule/notes-es.md)
* [Módulo Social](modules/SocialModule/notes-es.md)

## Dispositivos de entrada

Tendrá varios tipos de dispositivos de entradas.

**Teclas de teclado mecánico**
: Las teclas de teclado mecánico se usan para la mayoría de los keybindings de
SC, esto es por que SC esta diseñado usando teclas.

**Encoders**
: Para los casos que se tienen dos teclas en la que una es de incrementar y otra
de decrementar que cambian una misma cantidad, por ejemplo incrementar o
decrementar la energía de los escudos.

**Toggle Switch (ON/OFF)**
: Estos se usan cuando se tienen dos teclas, una de prender y otra de apagar,
por ejemplo prender y apagar escudos. Pero para poder usarlo en SC es necesario
hacer una programación que aunque este permanentemente en ON mande solo una tecla
de ON en el momento que se cambia a esta posición, al igual que con el OFF.

### Dispositivos de entrada que posiblemente se puedan usar

Estos son dispositivos de entrada en los hay que hacer pruebas lógicas y de
usabilidad conectándose a SC, y teniendo en cuenta sus limitaciones de este para
saber si sirven.

**Potenciómetro líneal**
: Estos sirven para aquellos casos en los que SC tiene asociados ejes (axis). El
problema es con los keybindings que no sean ejes y que por su naturaleza
deberían serlo (como incrementar o decrementar la potencia de los escudos), por
que los potenciómetros dan mediadas absolutas y no incrementos y esto último es
como funciona SC, oprimiendo varias veces una tecla para incrementar o
decrementar una cantidad.

**Joystick**
: Aparte de los casos obvios en el cual se usan los joystick hay keybinding que
por su naturaleza deberían controlarse con joystick, por ejemplo las
rotaciones de algo. Pero un joystick en realidad son (por menos) dos
potenciómetros ortogonales, por lo que tiene el mismo problema de estos con los
keybindings que no sean ejes y que por su naturaleza deberían serlo (como el
desplazamiento angular de la cámara), por que los potenciómetros dan mediadas
absolutas y no incrementos.

**[GlidePoint® Circle Trackpads](https://www.cirque.com/glidepoint-circle-trackpads) (el del Steam Controler)**
: Este trackpad funciona muy parecido a un joystick análogo por lo que puede
usarse en lo mismo, pero también tiene el mismo problema de dar valores absolutos
y no incrementos que lo que necesita SC que maneja este pulsando repetidamente
una tecla.

## Microcontroladores

Se tienen dos posibilidades:

**[Sparkfun Pro Micro](https://www.sparkfun.com/products/12587)**
: Este microcontrolador es como un [Arduino](https://www.arduino.cc/) pero puede
funcionar como si fuera un teclado o un joystick.

**[Teensy®](https://www.pjrc.com/teensy/)**
: Este es como el [Sparkfun Pro Micro](https://www.sparkfun.com/products/12587)
o un [Arduino](https://www.arduino.cc/) también puede funcionar como un Teclado
y un joystick con la diferencia que tiene un procesador mas potente, más memoria
y muchos más pines de entrada/salida por lo que se le pueden conectar más
dispositivos de entrada y tener un firmware mas grande.

## Firmware

Hay dos posibilidades:

**[Arduino](https://www.arduino.cc/) con keypad.h, joystick.h y keyboard,h**
: Hay que programar casi todo desde cero, lo cual es una ventaja y una
desventaja al mismo tiempo. Una ventaja por que se tiene un control sobre todo,
pero es una desventaja por que hay que hacer mucho.

**[QMK Firmware](https://qmk.fm/)**
: Muchas de las cosas que se necesitan están presentes en QMK y no abría que
programar desde cero.

El usar el uno o el otro depende de:

1. Se puedan programas todos los dispositivos de la forma en que se quieren usar.
1. Facilidad de programación.
1. Que se pueda usar joystick y keyboard al mismo tiempo. Esto para sobrepasar la limitación de las 32 teclas del joystick tanto en Arduino como en QMK.


## Componentes

### Para el prototipo

#### Switches

* [Sparkfun: Tactile Button Assortment](https://www.sparkfun.com/products/10302)
  * [Drawing](https://www.sparkfun.com/datasheets/Components/Buttons/TSA12110%20TACT%20SWITCH.jpg)
* [Sparkfun: Mini Power Switch - SPDT](https://www.sparkfun.com/products/102)
  * [Dimensional Drawing](https://www.sparkfun.com/datasheets/Components/Buttons/P040040c.pdf)

#### Encoders

* [Sparkfun: Rotary Encoder](https://www.sparkfun.com/products/9117)
  * [Datasheet](https://www.sparkfun.com/datasheets/Components/TW-700198.pdf)

#### Potenciómetros

* [Sparkfun: Rotary Potentiometer - Linear (10k ohm)](https://www.sparkfun.com/products/9288)
  * [Datasheet R0902N-DD1-B10K-GP](https://cdn.sparkfun.com/assets/b/3/2/7/f/01_ECC-_R0901N_R0902N-Rotary_Potentiometers-2022-S.pdf)
* [Sparkfun: Slide Pot - Small (10k Linear Taper)](https://www.sparkfun.com/products/11620)
  * [Datasheet (C2031N-1A2-B10K-GP)](https://cdn.sparkfun.com/datasheets/Components/Switches/C-31-.pdf)
* [Sparkfun: Slide Pot - X-Large (10k Linear Taper)](https://www.sparkfun.com/products/9119)
  * [Datesheet](https://cdn.sparkfun.com/datasheets/Components/Switches/SC608N-b10k.pdf)

#### Joysticks

* [Sparkfun: Thumb Joystick - Deluxe](https://www.sparkfun.com/products/16273)
  * [Planos](https://cdn.sparkfun.com/assets/d/7/c/0/6/Schematic-Thumb_Joystick_-_Deluxe-16273.pdf)
  * [Especificación](https://cdn.sparkfun.com/assets/c/4/9/7/f/Specs-16273-Thumb_Joystick_-_Deluxe.pdf)
* [Sparkfun: Thumb Joystick](https://www.sparkfun.com/products/9032)
  * [Thumb Joystick Hookup Guide](https://learn.sparkfun.com/tutorials/thumb-joystick-hookup-guide)
  * [SparkFun Thumb Joystick Breakout](https://www.sparkfun.com/products/9110)

#### Otros
* [Circle Trackpad Development Kit](https://www.cirque.com/circle-trackpad-dev-kit)
  * [Trackpad Development Kit User Guide](https://static1.squarespace.com/static/53233e4be4b044fa7626c453/t/592449fc725e25ab6118ee63/1495550462985/Trackpad_DevKit_UserGuide-V1_0.pdf)
  * [Esquematic](https://static1.squarespace.com/static/53233e4be4b044fa7626c453/t/592449ea725e25ab6118ed65/1495550442448/02-000620-00RevA00_Adapter_SCHnew.pdf)

## Referencias

### Diseño de la PCB

1. [Teensy symbol library for KiCAD](https://github.com/XenGi/teensy_library) La librería de simbolos de Teensy para KiCAD
1. [Keyboard PCB Guide](https://github.com/ruiqimao/keyboard-pcb-guide)
1. [Designing a keyboard from scratch - Part 1](https://www.masterzen.fr/2020/05/03/designing-a-keyboard-part-1/)

#### KiCAD

1. KRSTEC-keyboard: Teclado diseñado de cero
  1. [KRSTEC-keyboard](https://github.com/criscol64/KRSTEC-keyboard) Github del
    teclado donde están los foodprint del teclado, entre esos los del switch de
    reset.
  1. [Diseño de Teclado KrsTec - creando el PCB](https://www.youtube.com/watch?v=98n5OJNPwCo)
  1. [Teclado KrsTec - Montaje de las partes](https://www.youtube.com/watch?v=wbh_nis3UaA)
  1. [KrsTec Programado y Prueba de Sonido](https://www.youtube.com/watch?v=8fZAfUpEjqw)
    1. Montaje de plates
    1. [Keyboard layout editor](http://www.keyboard-layout-editor.com/)
       Editor del mapa de teclado.
    1. [Keyboard Firmware Builder](https://kbfirmware.com/)
       Produce el código fuente para QMK del teclado.
  1. [Modificando el PCB Krstec añadiendo un Encoder + Crear archivos Gerber](https://www.youtube.com/watch?v=qYooFJVYEfo)
     Generando los archivos gerber.
    1. Modificando el equemático.
    1. Modificando el PCB
    1. Generando y comprimiendo los archivos Gerber para JLCPCB
    1. Mandar a fabricar en JLCPCB.
  1. [Teclado Krstec - Generando Archivos QMK](https://www.youtube.com/watch?v=irB1jytr30w)
  1. [Como generar los archivos para mandar a cortar los acrilicos]()

### Componentes

#### Microcontrodores

##### Teensy

1. [Teensy® 4.1 Development Board](https://www.pjrc.com/store/teensy41.html)
1. [Teensy® 4.0 Development Board](https://www.pjrc.com/store/teensy40.html)
1. [Teensy® 3.6 Development Board](https://www.pjrc.com/store/teensy36.html) No está en stock:
  1. [Amazon: Teensy 3.5 (Without Pins)](https://www.amazon.com/PJRC-3267-Teensy-3-5/dp/B072JL5C2G)

###### Teensy con  Arduino

Para trabajar con el IDE de Arduino se necesitan al menos tres partes:

1. [Teensyduino](https://www.pjrc.com/teensy/teensyduino.html) La extensión del
   IDE de Arduino para Teensy.
1. [Using USB Keyboard](https://www.pjrc.com/teensy/td_keyboard.html) Libraría
   para simular un teclado con Teensy.
   1. [Using USB Joystick](https://www.pjrc.com/teensy/td_joystick.html)
       Librería para sinular un joystick con Teensy. No sirve parque sólo maneja 32 botones.
   1. [Keypad Library](https://www.pjrc.com/teensy/td_libs_Keypad.html) Librería para leer una matriz de teclas.
   1. [Encoder Library](https://www.pjrc.com/teensy/td_libs_Encoder.html) Libreria para leer los encoders.

##### Teensy con QMK

Si se usa el Teensy QMK en el archivo ```rules.mk``` hay que poner el microcontrolador, el MCU.

###### Empezando con QMK

1. [Building Your First Firmware](https://docs.qmk.fm/#/newbs_building_firmware)
   Explica como crear un nuevo keymap.
1. [QMK_Teensy_2.0_Tutorial](https://github.com/gkubed/QMK_Teensy_2.0_Tutorial)
   Tutorial que explica como poner el firmware en un Teensy 2.0. Funciona mejor en Linux.
1. [Using The Teensy Loader on Ubuntu Linux](https://www.pjrc.com/teensy/loader_linux.html)
  Complementario al anterior explica como quemar desde Linux (Ubuntu).
1. [Keycodes Overview](https://github.com/qmk/qmk_firmware/blob/master/docs/keycodes.md)

#### Encoders

1. [Rotary Encoder](https://www.sparkfun.com/products/9117) En encoder sensillo
   de 12 pasos de Sparkfun.
   1. [Rotary Encoder 318-ENC130175F-12PS](https://www.sparkfun.com/datasheets/Components/TW-700198.pdf)
      El datasheed del encoder.
   1. [Black Metal Knob - 14x24mm](https://www.sparkfun.com/products/10002)
      La perilla del (knob) encoder. Negra de metal y para 6mm.
   1. [Clear Plastic Knob](https://www.sparkfun.com/products/10597) Otra perilla
      para el encoder, pero transparente. Esta sería mejor para el encoder que tiene RGB.
   1. [uxcell 5pcs, Potentiometer Control Knobs For Encoder Code Switch Knobs Acrylic Volume Tone Knobs Black D type 6mm](https://www.amazon.com/uxcell-Potentiometer-Control-Encoder-Acrylic/dp/B07T615NSB)
      Perilla para concoder plana.
1. [Rotary Encoder - Illuminated (RGB)](https://www.sparkfun.com/products/15141)
   Un encoder 24 pasos y RGB de Sparkfun.
   1. [Clear Plastic Knob](https://www.sparkfun.com/products/10597) Otra perilla
      para el encoder, pero transparente. Esta sería mejor para el encoder que tiene RGB.
1. [AliExpress: 100 step encoder](https://www.aliexpress.com/w/wholesale-100-step-encoder.html) Encoders de 100 pasos en Aliexpress.
1. [Amazon: 5V 60MM Ultra-Thin Hand Wheel Pulse Encode](https://www.amazon.com/Terminal-Aviation-Aluminum-Positions-Electronic/dp/B07Q75KT49/ref=sr_1_4?crid=2X4LKS9I1QZKQ)
1. [Amazon: Busqueda cnc rotary encoder](https://www.amazon.com/s?k=cnc+rotary+encoder)
   Un Encoder de 100 pasos como los de Aliexpress pero en Amazon.
   1. [100PPR 6 Terminal Electronic Hand Wheel Manual Pulse Encoder for CNC System (Black)](https://www.amazon.com/100PPR-Terminal-Electronic-Manual-Encoder/dp/B07G9FVHM8)
      Otro encoder de 100 pasos mejor documentado.    

##### Los encoders con Arduino

1. [Arduino - Rotary encoder Simple Example KY-040](https://create.arduino.cc/projecthub/vandenbrande/arduino-rotary-encoder-simple-example-ky-040-b78752)

##### Los encoders con QMK

1. [Encoders: Documentación de QMK](https://github.com/qmk/qmk_firmware/blob/master/docs/feature_encoders.md)
  Parece estar muy bien exlicado, supone que se sabe que son las líneas A y B.
1. [How can I use a rotary encoder?](https://docs.splitkb.com/hc/en-us/articles/360010513760-How-can-I-use-a-rotary-encoder-)
  Explica como usar un _rotaty encoder_ wn QMK con eejemplo específicos como control de audio, scrolling, moviemiento de ventanas, tabbing, etc.
1. [QMK Encoder Setup](https://www.youtube.com/watch?v=GLqSPa_Zc2Q) Explica como configurar un escoder de cien pasos (de los que se consiguen en Aliexpress)
1. [Hub16 Encoder Configuration](https://www.youtube.com/watch?v=TTCaQ-STD-E) Como configurar dos encoder con QMK y los codigos de teclado de QMK.
1. [Using multiple encoders in QMK by wiring them up to your matrix rows](https://www.youtube.com/watch?v=DyHxccSvsPs) Explica como conectar varios encoders.





### Imagenes

* [xkeys: Printable Legend Templates](https://xkeys.com/usbcustomkeyboards/customprintedlegends.html#LegendTemplates)
  Una plantilla para imprimir las etiquetas de la teclas de xkeys.
  Archivo local: [SingleKeyLegendTemplate.pdf](images/xkeys/SingleKeyLegendTemplate.pdf)

### openclipart

* Toggle Switch (On/OFF) Plástico Negro
  * [Switch On](https://www.openclipart.org/detail/180085/switch-on)
    Switch On/Off, en posición ON, plástico negro.
    Nombre archivo local: [ToggleSwitch_ON-OFF_PlasticoNegro-On.svg](images/openclipart/ToggleSwitch_ON-OFF_PlasticoNegro-On.svg)
  * [switch on/off](https://www.openclipart.org/detail/62737/switch-onoff)  
    Switch On/Off, en posición OFF , plástico negro.
    Archivo local: [ToggleSwitch_ON-OFF_PlasticoNegro-Off.svg](images/openclipart/ToggleSwitch_ON-OFF_PlasticoNegro-Off.svg)
* [Faders from mixing board](https://www.openclipart.org/detail/201691/faders-from-mixing-board)
  Petenciometro líneal.
  Archivo local: [faders.svg](images/openclipart/faders.svg)
* [metallic shine](https://www.openclipart.org/detail/307289/metallic-shine)
  Lo que parece ser un knob metálico.
  Archivo local: [metallic-shine.svg](images/openclipart/metallic-shine.svg)
* [Joystick](https://www.openclipart.org/detail/246396/joystick)
  Un joystick pequeño y muy esquemático.
  Archivo local: [JoyStick.svg](images/openclipart/JoyStick.svg)
* [DPST micro push button switch](https://www.openclipart.org/detail/299643/dpst-micro-push-button-switch)
  Un switch pequeño como para protoboard.
  Archivo local: [JoyStick.svg](images/openclipart/JoyStick.svg)
* [Blank Generic Keyboard](https://www.openclipart.org/detail/177279/blank-generic-keyboard)
  Teclado en blanco.
  Archivo local: [Blank-Generic-Keyboard-Remix-by-Merlin2525.svg](images/openclipart/Blank-Generic-Keyboard-Remix-by-Merlin2525.svg)
* [Non-linear video editing system 1](https://www.openclipart.org/detail/284960/nonlinear-video-editing-system-1)
  Una consola de edición no lineal de vídeo.
  Se pueden sacar de aquí los knobs y otros openclipart de dispositivos.
  Archivo local: [Non-linear video editing system 1.svg](images/openclipart/Non-linear video editing system 1.svg)
* [Industrial Toggle Switch](https://www.openclipart.org/detail/246398/industrial-toggle-switch)
  Un knb de multi-selector o de potenciometro.
  Archivo local: [TwoPosToggle.svg](images/openclipart/TwoPosToggle.svg)
* [Mixer knobs](https://www.openclipart.org/detail/15859/mixer-knobs)
  Unos knobs de mezcladora.
  Se pueden sacar de aquí la imagen de knobs de encoders.
  Archivo local: [odaibanet-Mixer-knobs.svg](images/openclipart/odaibanet-Mixer-knobs.svg)
* [Power Button Icon](https://www.openclipart.org/detail/253614/power-button-icon)
  Una tecla de apagado.
  Se puede usar para construir las teclas de xkeys.
  Archivo local: [Power-Button-Icon.svg](images/openclipart/Power-Button-Icon.svg)
* [qwerty keyboard](https://www.openclipart.org/detail/37291/qwerty-keyboard)
  Un teclado tipo mac.
  Se puede usar para construir las teclas de xkeys.
  Archivo local: [qwerty-keyboard.svg](images/openclipart/qwerty-keyboard.svg)
* [Keyboard Keys](https://www.openclipart.org/detail/27549/keyboard-keys)
  Alguna teclas de teclado.
  Se puede usar para construir las teclas de xkeys.
  Archivo local: [Simanek-Keyboard-Keys-2.svg](images/openclipart/Simanek-Keyboard-Keys-2.svg)
