# Notas de Star Citizen Button Box V2

La idea es hacer una botonera que sea más funcional que la anterior
[StarCitizen_6_ButtonBox](https://github.com/aztlek/StarCitizen_6_ButtonBox) que
sólo era una prueba de concepto. Más funcional en el sentido que si se use para
jugar a [Star Citizen](https://robertsspaceindustries.com/star-citizen/) el
simulador de vida espacial.

## Requerimientos del teclado

1. Debe ser nodular.
1. La estética debe ser una combinación de:
   * [The Warthog Project](https://www.youtube.com/@thewarthogproject)
   * La estética de las naves de SC. Por ejemplo de la Terrapin y la Freelancer.
1. Los dispositivos de entrada deben ser identificables.
   * Teclas que se puedan marcar.
   * Los otros dispositivos en el panel.
1. Algunas de los controles pueden ser potenciometros o *rotary encoders*. Esto
   para algunos *keybindings* que sean *axis* (ejes) o *sliders* (controles
   deslizantes).
1. Al ancho máximo de la botonera debe ser de unos 82 cms que corresponde con el
   ancho de un monitor de 34'' QHD. por uqe ese va a ser su lugar.

### Debe tener un bue numero de teclas o ¿Cuántas teclas debe tener la botonera?

Para ello se hizo una hoja de cálculo [Número de teclas en Star Citizen](NumberOfKeys_StarCitizen.ods).
Y son muchas las teclas 

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
