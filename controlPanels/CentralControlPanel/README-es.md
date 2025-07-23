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


## Cómo crear un joystick personalizado especial para el Central Control

### Adicionar un ```USB Type```al Teensy 4.0

1. Edite al archivo ```boards.txt```que se encuentra en la ruta ```~/.arduino15/packages/teensy/hardware/avr/1.59.0``` en Linux .
1. Inserte en después de la linea ```teensy41.menu.usb.flightsimjoystick.fake_serial=teensy_gateway``` las siguientes líneas:
	```
	teensy41.menu.usb.customcontroller=Modular Cockpit Central Control Panel Joystick
	teensy41.menu.usb.customcontroller.build.usbtype=MODULAR_COCKPIT_CENTRAL_CONTROL_PANEL_JOYSTICK
	teensy41.menu.usb.customcontroller.upload_port.usbtype=MODULAR_COCKPIT_CENTRAL_CONTROL_PANEL_JOYSTICK
	teensy41.menu.usb.customcontroller.fake_serial=teensy_gateway
	```	
1. Guardar y salir

### Definir un nuevo tipo de USB

1. Edite el archivo ```usb_desc.h``` que se encuentra en la ruta ```~/.arduino15/packages/teensy/hardware/avr/1.59.0/cores/teensy4```en Linux.
1. Inserte el siguiente código antes de la línea ```#elif defined(USB_SERIAL_HID)```
	```
	#elif defined(MODULAR_COCKPIT_CENTRAL_CONTROL_PANEL_JOYSTICK)
	  #define VENDOR_ID		0x16C0
	  #define PRODUCT_ID		0x0482
	  #define MANUFACTURER_NAME	{'A','z','t','l','e','k',' ','G','a','m','e','s'}
	  #define MANUFACTURER_NAME_LEN	12
	  #define PRODUCT_NAME		{'M','o','d','u','l','a','r',' ','C','o','c','k','p','i','t',' ','C','e','n','t','r','a','l',' ','C','o','n','t','r','o','l',' ','P','a','n','e','l',' ','J','o','y','s','t','i','c','k'}
	  #define PRODUCT_NAME_LEN	46
	  #define EP0_SIZE		64
	  #define NUM_ENDPOINTS         3
	  #define NUM_USB_BUFFERS	24
	  #define NUM_INTERFACE		2
	  #define SEREMU_INTERFACE      1	// Serial emulation
	  #define SEREMU_TX_ENDPOINT    2
	  #define SEREMU_TX_SIZE        64
	  #define SEREMU_TX_INTERVAL    1
	  #define SEREMU_RX_ENDPOINT    2
	  #define SEREMU_RX_SIZE        32
	  #define SEREMU_RX_INTERVAL    2
	  #define JOYSTICK_INTERFACE    2	// Joystick
	  #define JOYSTICK_ENDPOINT     3
	  #define JOYSTICK_SIZE         64	//  12 = normal, 64 = extreme joystick
	  #define JOYSTICK_INTERVAL     1
	  #define ENDPOINT2_CONFIG ENDPOINT_RECEIVE_INTERRUPT + ENDPOINT_TRANSMIT_INTERRUPT
	  #define ENDPOINT3_CONFIG ENDPOINT_RECEIVE_UNUSED + ENDPOINT_TRANSMIT_INTERRUPT

	```
1. 	Guardar y salir.

### Crear el descriptor USB HID

No se hizo nada por que se usó el de 64, el ```extreme joystick```.

### Modificar la librería ```usb_joystick```

No se hizo nada por que se usó el de 64, el ```extreme joystick```.

### Reconfigurar y reniciar el IDE de Arduino

1. Salir del IDE de Arduino.
1. Borrar el directorio ```arduino-ide``` que está en
	1. En linux ```~/.config/arduino-ide/```
	1. En windows ```C:\Users\<user name>\AppData\Roaming\arduino-ide\ ```
	1. En MacOS ```~/Library/Application Support/arduino-ide/```
1. Reiniciar el IDE de Arduino.


### Referencias de Cómo crear un joystick personalizado

1. [Create a Custom Joystick With Teensy 4.1](https://www.instructables.com/Create-a-Custom-Joystick-With-the-Teensy-41/)
1. [Changes to custom board option definitions in boards.txt are not picked up #1030](https://github.com/arduino/arduino-ide/issues/1030#issuecomment-1152005617)


