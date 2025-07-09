# Notas en español

## Configuración para que más de 128 botones (Extreme joystick)

1. Salir del IDE de Arduino.
1. Editar el archvo ```arduino15/packages/teensy/hardware/avr/1.59.0/cores/teensy4/usb_desc.h```.
1. En donde dice ```JOYSTICK_SIZE         12``` cambiar por ```JOYSTICK_SIZE         64```. Son cuatro líneas.
1. Guardar
1. Lanzar el IDE de Arduino.
1. Compilar y cargar al Teensy 4.1

## Configurar cada uno de los módulos

1. Editar el archivo ```src/CentralControlPanel-Firmware/CentralControlPanel-Firmware.ino``` con el IDE de Arduino.
1. Descomentariar la línea ```#define DEBUG```.
1. Cargar el el script al Teensy.
1. Abrir el ```Serial Monitor``` por ```Tools -> Serial Monitor```.
1. Ahota oprirmir los botones de cada módulo. 
1. En el ```Serial Monitor``` se ve algo como ```Joystick(n): ..```, donde n es la posición del módulo en el USB Hub. Con ese numero y el total de botones por módulo.
1. Con esa información se llenar el areglo ```buttons_per_joystick[]```. Solo se pueden poner hasta 9 módulos (limitaciones de las librerías del Teensy).
1. Compilar/cargar y disfrutar configurando el Star Citizen con tus botoneras.
