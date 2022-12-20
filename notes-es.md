# Notas de Star Citizen Button Box V2

La idea es hacer una botonera que sea más funcional que la anterior
[StarCitizen_6_ButtonBox](https://github.com/aztlek/StarCitizen_6_ButtonBox) que
sólo era una prueba de concepto. Mas funcional en el sentido que si la use para
jugar a [Star Citizen](https://robertsspaceindustries.com/star-citizen/) el
simulador de vida espacial.

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

Estos son dispositivos de entrada hay que hacer pruebas lógicas y de
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
por su naturaleza deberían ser controlarse con joystick, por ejemplo las
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

## Referencias

### Imagenes

* [xkeys: Printable Legend Templates](https://xkeys.com/usbcustomkeyboards/customprintedlegends.html#LegendTemplates)
  Una plantilla para imprimir las etiquetas de la teclas de xkeys.
  Archivo local: [SingleKeyLegendTemplate.pdf](images/SingleKeyLegendTemplate.pdf)

### Iconos

* Toggle Switch (On/OFF) Plástico Negro
  * [Switch On](https://www.openclipart.org/detail/180085/switch-on)
    Switch On/Off, en posición ON, plástico negro.
    Nombre archivo local: [ToggleSwitch_ON-OFF_PlasticoNegro-On.svg](images/iconos/ToggleSwitch_ON-OFF_PlasticoNegro-On.svg)
  * [switch on/off](https://www.openclipart.org/detail/62737/switch-onoff)  
    Switch On/Off, en posición OFF , plástico negro.
    Archivo local: [ToggleSwitch_ON-OFF_PlasticoNegro-Off.svg](images/iconos/ToggleSwitch_ON-OFF_PlasticoNegro-Off.svg)
* [Faders from mixing board](https://www.openclipart.org/detail/201691/faders-from-mixing-board)
  Petenciometro líneal.
  Archivo local: [faders.svg](images/iconos/faders.svg)
* [metallic shine](https://www.openclipart.org/detail/307289/metallic-shine)
  Lo que parece ser un knob metálico.
  Archivo local: [metallic-shine.svg](images/iconos/metallic-shine.svg)
* [Joystick](https://www.openclipart.org/detail/246396/joystick)
  Un joystick pequeño y muy esquemático.
  Archivo local: [JoyStick.svg](images/iconos/JoyStick.svg)
* [DPST micro push button switch](https://www.openclipart.org/detail/299643/dpst-micro-push-button-switch)
  Un switch pequeño como para protoboard.
  Archivo local: [JoyStick.svg](images/iconos/JoyStick.svg)
* [Blank Generic Keyboard](https://www.openclipart.org/detail/177279/blank-generic-keyboard)
  Teclado en blanco.
  Archivo local: [Blank-Generic-Keyboard-Remix-by-Merlin2525.svg](images/iconos/Blank-Generic-Keyboard-Remix-by-Merlin2525.svg)
* [Non-linear video editing system 1](https://www.openclipart.org/detail/284960/nonlinear-video-editing-system-1)
  Una consola de edición no lineal de vídeo.
  Se pueden sacar de aquí los knobs y otros iconos de dispositivos.
  Archivo local: [Non-linear video editing system 1.svg](images/iconos/Non-linear video editing system 1.svg)
* [Industrial Toggle Switch](https://www.openclipart.org/detail/246398/industrial-toggle-switch)
  Un knb de multi-selector o de potenciometro.
  Archivo local: [TwoPosToggle.svg](images/iconos/TwoPosToggle.svg)
* [Mixer knobs](https://www.openclipart.org/detail/15859/mixer-knobs)
  Unos knobs de mezcladora.
  Se pueden sacar de aquí la imagen de knobs de encoders.
  Archivo local: [odaibanet-Mixer-knobs.svg](images/iconos/odaibanet-Mixer-knobs.svg)
* [Power Button Icon](https://www.openclipart.org/detail/253614/power-button-icon)
  Una tecla de apagado.
  Se puede usar para construir las teclas de xkeys.
  Archivo local: [Power-Button-Icon.svg](images/iconos/Power-Button-Icon.svg)
* [qwerty keyboard](https://www.openclipart.org/detail/37291/qwerty-keyboard)
  Un teclado tipo mac.
  Se puede usar para construir las teclas de xkeys.
  Archivo local: [qwerty-keyboard.svg](images/iconos/qwerty-keyboard.svg)
* [Keyboard Keys](https://www.openclipart.org/detail/27549/keyboard-keys)
  Alguna teclas de teclado.
  Se puede usar para construir las teclas de xkeys.
  Archivo local: [Simanek-Keyboard-Keys-2.svg](images/iconos/Simanek-Keyboard-Keys-2.svg)
