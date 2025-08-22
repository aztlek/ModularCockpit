# Protocolo de comunicación por el serial de los modules, controlPanels e interfaz gráfica

Este protocolo se implementa sobre el serial de los módulos y de los paneles de control.

## Mensajes del Module

* Como los módulos pueden conectarse directamente al computador o mediante un ControlPanel los mensajes que le llegan son indiferentes si llegan de la interfaz gráfica o del ControlPanel. Por eso hay una columna en la siguiente tabla en el que disparador puede llegar de la interfa gráfica o del ControlPanel.
* Los mensajes de debug comienzan con una 'D' amyúscula, que viene a ser en byte 0, para diferenciarlos de los otros tipos de mensajes.


| Mensaje                     | Valor Byte 0 | Tipo parámetro | Valor | Disparador en el Module  | Disparador desde el ControlPanel o Interfáz Gráfica | Descripción                                                                                                                                |
| --------------------------- | -----------: | -------------- | ----- | ------------------------ | --------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------ |
| Change_debug_mode           | 1            | byte           | 0,1   | Toggle Buttom            | Change_debug_mode                                   | Cambia el modo de debug 0 no debug, 1 debug                                                                                                |
| Change_backlight_brightness | 2            | byte           | 0-255 | Potentiometer            | Change_backlight_brightness                         | Cambia el brillo de la retroilumimación                                                                                                    |
| Change_fan_speed            | 3            | byte           | 0-255 | Potentiometer            |                                                     | Cambia la velocidad del ventilador.                                                                                                        |
| Send_names                  | 11           | string         |       |                          | Ask_names                                           | Envía el nombre del Module                                                                                                                 |
| Send_number_buttons         | 21           | byte           | 0-128 |                          | Ask_number                                          | Envía el número de botones                                                                                                                 |
| Send_number_axis            | 23           | byte           | 0-128 |                          | Ask_number                                          | Envía el número de ejes                                                                                                                    |
| Send_debug_output           | 'D'          | string         |       |                          | Cambio en el estado de debug a 1                    | Envía mensajes de debug si el debug está activo                                                                                            |

## Mensajes del ControlPanel

* El brillo de los módulos puede ser cambiado desde un módulo, o desde un potenciometro conectado directamente al ControlPanel o desde la Intefaz Gráfica.
* El estado del debug puede ser cambiado desde un módulo, o desde un toggle buttom conectado directamente al Control Panel o desde la Interfaz Gráfica.
* Por lo anterior la Intefáz Gráfica debe tener una parte donde se muestren los mensajes que llegan desde el serial.
* Los mensajes de debug comienzan con una 'D' amyúscula, que viene a ser en byte 0, para diferenciarlos de los otros tipos de mensajes.

| Mensaje                     | Valor Byte 0 | Tipo parámetro | Valor | Disparador en el ControlPanel  | Disparador desde el Module  | Disparador desde la Interfaz Gráfica  | Descripción                                                                                                                                |
| --------------------------- | -----------: | -------------- | ----- | ------------------------------ | --------------------------- | ------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------ |
| Change_debug_mode           | 1            | byte           | 0,1   | Toggle Buttom                  | Change_debug_mode           | Change_debug_mode                     | Cambia el modo de debug 0 no debug, 1 debug                                                                                                |
| Change_backlight_brightness | 2            | byte           | 0-255 | Potentiometer                  | Change_backlight_brightness | Change_backlight_brightness           | Cambia el brillo de la retroilumimación de los modules conectados a ControlPanel, o de los controlPanles conectados a la Interfaz Gráfica  |
| Change_fan_speed            | 3            | byte           | 0-255 | Potentiometer                  | Change_fan_speed            | Change_fan_speed                      | Cambia la velocidad del ventilador.                                                                                                        |
| Ask_names                   | 10           |                |       | setup()                        |                             | Ask_names                             | Pregunta por el nombre del modulo desde el control panel, o del panel desde la Interfaz Gráfica                                            |
| Send_names                  | 11           | string         |       |                                |                             | Ask_names                             | Envía el nombre del panel seguida por dos puntos y una lista separada por comas de los nombres de los Modules                                                                           |
| Ask_numbers                 | 20           |                |       | setup()                        |                             | Ask_number                            | Pregunta por el numero de componentes desde el ControlPanel, o número de modules desde la Interfáz Gráfica                                 |
| Send_number_modules         | 22           | byte           | 0-9   |                                |                             | Ask_number                            | Envía el número de modulos coectados a ControlPanel                                                                                        |
| Send_debug_output           | 'D'          | string         |       | El estado de debug == 1     |                             |                                       | Envía mensajes de debug si el debug está activo                                                                                            |

## Mensajes

### Setup modules

En el Setup se le pregunta a cada módulo su nombre, numero de teclas y de ejes.

![Setup modules](images/Protocol-SetupModules.png)

### Change_debug_mode

El mensaje Change_debug_mode cambia el modo de debug, si se envia un 1 se activa la impresión de mensajes de menú, si se envía un 0 se desactiva.

#### Change_debug_mode from Module without Control panels

El piloto cambia el estado de debug de todos los módulos conectados al computador mediante un toggle buttom que está conectado al módulo. Esto permite dos cosas: Tener un botón en cualquiera de los módulos. Tener un módulo especialisado de setup que tenga en toggle buttom de debug.

![Change_debug_mode from Module without Control panel](images/Protocol-ChangingDebugStateFromModuleWithoutControlPanel.png)

#### Change_debug_mode from Graphic Interface without Control panels

El piloto cambia el estado de debug de todos los módulos conectados al computador, pero mediante toggle buttom en la interfaz gráfica.

![Change_debug_mode from Graphic Interface without Control panel](images/Protocol-ChangingDebugStateFromGraphicInterfaceWithoutControlPanel.png)

#### Change_debug_mode from Module

El piloto cambia el estado de debug de todos los módulos conectados al ControlPanel y todos los que están conectados al computador, pero mediante un toggle buttom que está conectado al Module. Si esta corriendo la interfaz gráfica cambia el estdo de todos los modulos conectados a los ControlPanels, o de los módulos conectados directo al computador.

![Change_debug_mode from Module](images/Protocol-ChangingDebugStateFromModule.png)

#### Change_debug_mode from Graphic Interface

El piloto cambia el estado de debug de todos los módulos conectados al ControlPanels que están conectados al computador, pero mediante un toggle buttom de la Interfaz Gráfica.

![Change_debug_mode from Graphic Interface](images/Protocol-ChangingDebugStateFromGraphicInterface.png)

#### Change_debug_mode from ControlPanel

El piloto cambia el estado de debug de todos los módulos conectados al ControlPanel, pero mediante un toggle buttom que está conectado al ControlPanel. Si esta corriendo la interfaz gráfica cambia el estdo de todos los modulos conectados a los ControlPanels, o de los módulos conectados directo al computador.

![Change_debug_mode from ControlPanel](images/Protocol-ChangingDebugStateFromControlPanel.png)

### Change_backlight_brightness

Cambia el brillo de la retroiluminación de los módulos. La forma en como funciona este mensaje es casi igual que la de Change_debug_mode (pero sin el mensaje de Send_debug_output) por lo que no se presentam estos diagramas de interación.

### Change_fan_speed

Cambia la velocidad del el ventilador o ventiladores de ControlPanel. ESto se puede hacer mediante un potenciometro conectado directamante al ControlPanel, mediante un mensaje Change_fan_speed que llega de un módulo o de la GraphicInterface.

#### Change_fan_speed from ControlPanel

Cambia la velocidad del los ventiladores con un potenciometro conectado al ControlPanel. Sólo cambia la velocidad de sus propios ventiladores, por que los demás ControlPanels tiene diferentes necesidades de ventilación.

![change_fan_speed from ControlPanel](protocol/images/Protocol-Change_fan_speed-fromControlPanel.png)

#### Change_fan_speed from GraphicInterface

Cambia la velocidad de los ventiladores de un ControlPanel selecionado en la interfaz desde la GraphicInterface. Sólo cambia la velocidad de los ventiladores de un ControlPanel selecionado, esto porque cada controlPanel tiene diferentes necesidades de ventilación.

![Change_fan_speed from GraphicInterface](protocol/images/Protocol-Change_fan_speed-fromGraphicInterface.png)

#### Change_fan_speed from Module

Cambia la velocidad del las ventiladores del ControlPanel al que está conectado el Module. Sólo cambia la velocidad de los ventiladores del ContolPanel al que está conectado el módulo, esto porque cada ControlPanel tiene sus necesidades particulares de ventilación

![Change_fan_speed from Module](protocol/images/Protocol-Change_fan_speed-fromModule.png)

### Send_debug_output

Si el debug está a 1, se imprimen los mensajes de debug en el serial del módulo, y si está conectado al un ControlPanel esta los pasa con Control Panel he imprime sus propios mensajes, a contianuación la interfaz gráfica toma todos estos mensajes y los muestra. Se usa para mostar toda la informacion de paneles de control y modulos conectados.

### Ask_names

Se preguntan los nombres de los módulos y control panels con el fin de ser mostrados en la Interfa Gráfica.

![Ask_names](images/Protocol-Ask_names.png)


