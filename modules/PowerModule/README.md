# Power Module

![Real Power Module](images/RealPowerModule.jpg)

## Design

![Power Module](images/PowerModule_125mmWidth.png)

## Keybindings

### Vehicles – Power Triangle  Assignement

| Keybinding                                                       | Input Device Type                    |
| ---------------------------------------------------------------- | ------------------------------------------------- |
| Weapons – Increase (tab)                                         | encoder[0]: increase                           |
| Weapons – Decrease (tab)                                         | encoder[0]: decrease                    |
| Weapons – Set to Max (tab)                                       | key[0]  |
| Weapons – Set to Min (tab)                                       | key[1]      |
| Engines – Increase (tab)                                         | encoder[1]: increase  |
| Engines – Decrease (tab)                                         | encoder[1]: decrease     |
| Engines – Set to Max (tab)                                       | key[2]                       |
| Engines – Set to Min (tab)                                       | key[3]        |
| Shields – Increase (tab)                                         | encoder[2]: increase   |
| Shields – Decrease (tab)                                         | encoder[2]: decrease   |
| Shields – Set to Max (tab)                                       | key[4]             |
| Shields – Set to Min (tab)                                       | key[5]         |
| Reset Assignements                                               | key[6]         |

### Flight – Power

| Keybinding                                                       | Input Device Type                    |
| ---------------------------------------------------------------- | ------------------------------------------------- |
| Set Power On                                                     | toggle_switch[0]: on   |
| Set Power Off                                                    | toggle_switch[0]: off        |
| Set Thrusters Power On                                           | toggle_switch[1]: on   |
| Set Thrusters Power Off                                          | toggle_switch[1]: off |
| Set Shields Power On                                             | toggle_switch[2]: on   |
| Set Shields Power Off                                            | toggle_switch[2]: off |
| Set Weapons Power On                                             | toggle_switch[3]: on |
| Set Weapons Power Off                                            | toggle_switch[3]: off |
| Increase Throttle                                                | encoder[3]: increase |
| Decrease Throttle                                                | encoder[3]: decrease |
| Increase Throttle to Max (double tab)                            | key[7] |
| Decrease Throttle to Min (double tab)                            | key[8] |

### Total devices in keybindings

| Device                |  Count |
| --------------------- | -----: |
| Keys                  |      9 |
| Toggle switchs        |      4 |
| Toggle switchs (hold) |      0 |
| Encoders              |      4 |
| Slide Pot             |      2 |
| Joystick              |      0 |

### Categorization

The following table organizes input devices into two orthogonal categories.
It is a first approximation of how the input devices should be organized on the
module panel.


| Power         | Shields       | Weapons       |    Engines    | Thrusters     | Throttle      |
| :------------ | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: |
| toggle_switch | toggle_switch | toggle_switch |               | toggle_switch |               |
|               | encoder       | encoder       | encoder       |               | encoder       |
|               | key (Max)     | key (Max)     | key (Max)     |               | key (Max)     |
|               | key (Min)     | key (Min)     | key (Min)     |               | key (Min)     |
| key (reset)   |               |               |               |               |               |

## Design

1. The `Thrusters` and `Throttle` columns were merged into one, but
    marking the difference between one group and another.
1. The `reset` key is integrated into the main key matrix below
    of the `toggle_switch` of the power.


## Bill of materials

| Material                                                                                                                                  | Qty. | Links                                                                  |
| ----------------------------------------------------------------------------------------------------------------------------------------- | ---: | ------------------------------------------------------------------------------- |
| Twidec/Heavy Duty Rocker Toggle Switch 16A 250V SPST 2 Position 2 Pin ON/Off Switch with Black PC Wear-Resistant Handle TEN-A-2210BK-A101 |    5 | [Amz](https://www.amazon.com/dp/B07VJ4GQPW)                                     |
| (7 Pin 20MM)10 PCS 360 Degree EC11 Rotary Encoder Code Switch Digital Potentiometer with Caps                                             |    5 | [Amz](https://www.amazon.com/dp/B08BFJ4F5C)                                     |
| Jade Kailh Box Key Switches                                                                                                               |    9 | [Amz (One Package)](https://www.amazon.com/dp/B09WYV6MTJ), [Amz (One Package)](https://www.amazon.com/dp/B0B9BDM57S) |
| Teensy 4.0                                                                                                                                |    1 | [Amz](https://www.amazon.com/dp/B07W5J3WNH)                                     |
| Terminal Block Breakout Board Module for Teensy 4.0, Screw Mount Version                                                                  |    1 | [Amz](https://www.amazon.com/dp/B08R7PVCFN)                                     |
| Female to Female Thread Spacer Screws Brass Hex Standoff M3 x 60mm                                                                        |    4 | [Amz](https://www.amazon.com/dp/B09V272N1N)                                     |
| 3Mx6 Socket Head Cap Bolts                                                                                                                |    4 | 1 package[Amz](https://www.amazon.com/dp/B00W8YSCIS)                            |
| 3M Flat Washers                                                                                                                           |    8 | In one package [Amz](https://www.amazon.com/dp/B08CHHLQQS)                      |
| 3Mx12 Button Head Socket Cap Bolts                                                                                                        |    2 | In one package [Amz](https://www.amazon.com/dp/B08CHHLQQS)                      |
| 3Mx5 Button Head Socket Cap Bolts                                                                                                         |    4 | In one package [Amz](https://www.amazon.com/dp/B08CHHLQQS)                      |
| Plastic Primer                                                                                                                            |    1 | [mtn](https://www.montanacolors.com/en/productos/mtn-pro-plastic-primer-spray/) |
| Black Matte Paint R-9011                                                                                                                  |    1 | [mtn](https://www.montanacolors.com/en/productos/mtn-94-aerosol-spray-paint/)   |
| 2mm white acrylic                                                                                                                         |    1 |                                                                                 |
| 3mm translucent acrylic                                                                                                                   |    1 |                                                                                 |
| 3mm black acrylic                                                                                                                         |    1 |                                                                                 |
| 3mm black acrylic                                                                                                                         |    1 |                                                                                 |

## Connections

![Drawing Connections](PowerModule-drawingConnections.svg)

## Key labels

[Key Labels](images/ModuleKeyLabels.pdf)
