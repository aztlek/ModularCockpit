/*
||
|| @file firmware.ino
|| @author Luis Alejandro Bernal Romero (Aztlek)
|| @description
|| | This firmware is for the "Power Module" of the "Modular Cockpit".
|| | @see Power Module: https://github.com/aztlek/ModularCockpit/tree/main/modules/PowerModule
|| | @see Modular Cockpit: https://github.com/aztlek/ModularCockpit.
|| #
|| 
|| @license
|| | Copyright (C) 2020 Luis Alejandro Bernal Romero (Aztlek)
|| | 
|| | This program is free software: you can redistribute it and/or modify
|| | it under the terms of the GNU General Public License as published by
|| | the Free Software Foundation, either version 3 of the License, or
|| | (at your option) any later version.
|| | 
|| | This program is distributed in the hope that it will be useful,
|| | but WITHOUT ANY WARRANTY; without even the implied warranty of
|| | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
|| | GNU General Public License for more details.
|| | 
|| | You should have received a copy of the GNU General Public License
|| | along with this program.  If not, see <http://www.gnu.org/licenses/>.
|| #
||
*/
 
#include <Keypad.h>
#include <Encoder.h>

// #define DEBUG


// Keypad
const byte NUMROWS = 4;
const byte NUMCOLS = 5;
const byte MAXKEYS = NUMROWS * NUMCOLS;
char keys[NUMROWS][NUMCOLS] = {
  // Toggle switchs
  // for the on position of the switches
  {     1,  2,  3,  4,  5},
  // for the off position of the switches
  // {  6,  7,  8,  9, 10},

  // Encoders
  // for the increment
  {   11, 12, 13, 14, 15},
  // for the decrement
  //{ 16, 17, 18, 19, 20}, 

  // Key switchs
  { 21, 22, 23, 24, 25},
  { 26, 27, 28, 29, 30}
};

byte rowPins[NUMROWS] = {  2,  3,  4,  5};
byte colPins[NUMCOLS] = {  6,  7,  8,  9, 10};

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, NUMROWS, NUMCOLS );

// Keys
#define KEY_PRESS_TIME 150

// Toggle switchs
typedef enum{ OFF, ON} T_ToggleSwitchState;
T_ToggleSwitchState toggleSwitchStates[NUMCOLS] = {OFF, OFF, OFF, OFF, OFF};
#define toggleSwitchState(code) (toggleSwitchStates[(code) - 1])
#define isToggleSwitch(code) ((code) >= 1 && (code) <= 5)
#define offCodeToggleSwitch(code) ((code) + NUMCOLS)

// Encoders
Encoder encoders[NUMCOLS] = {
  Encoder(23, 22),
  Encoder(21, 20),
  Encoder(19, 18),
  Encoder(17, 16),
  Encoder(15, 14),
};
long oldPositionEncoders[NUMCOLS] = { 0, 0, 0, 0, 0};
long newPositionEncoders[NUMCOLS];
#define ENCODER_INCREMENT_KEYS 1


String msg;

const int ledPin = 13;

extern "C" uint32_t set_arm_clock(uint32_t frequency);

void setup() {
  set_arm_clock(24000000);

  // Led as power indicator
  temporarily_increase_led_brightness(1000);
  
#ifdef DEBUG
  Serial.begin(9600);
#endif
}


void loop() {

    // Fills kpd.key[ ] array with up-to 10 active keys.
    // Returns true if there are ANY active keys.
    if (kpd.getKeys())
    {
        for (int i=0; i < LIST_MAX; i++)   // Scan the whole key list.
        {
            if ( kpd.key[i].stateChanged )   // Only find keys that have changed state.
            {
              byte code = (byte)kpd.key[i].kchar;
              KeyState keyState = kpd.key[i].kstate;
              if( isToggleSwitch(code) )
              {
                  if(keyState == PRESSED  && toggleSwitchState(code) != ON )
                  {
                    msg = " ON.";
                    Joystick.button(code, 1);
                    delay(KEY_PRESS_TIME);
                    Joystick.button(code, 0);                           
                    toggleSwitchState(code) = ON;
                    temporarily_increase_led_brightness(20);
                  }
                  else if(keyState == RELEASED && toggleSwitchState(code) != OFF ) 
                  {  
                    msg = " OFF.";
                    Joystick.button(offCodeToggleSwitch(code), 1);
                    delay(KEY_PRESS_TIME);
                    Joystick.button(offCodeToggleSwitch(code), 0);      
                    toggleSwitchState(code) = OFF;
                    temporarily_increase_led_brightness(20);            
                  } 
              }
              else // Normal key
              {
                switch (keyState) {  // Report active key state : IDLE, PRESSED, HOLD, or RELEASED
                    case PRESSED:
                      msg = " PRESSED.";
                      Joystick.button(code, 1);
                      temporarily_increase_led_brightness(20);
                    break;
                    case RELEASED:
                      msg = " RELEASED.";
                      Joystick.button(code, 0);
                      temporarily_increase_led_brightness(20);
                    break;
                    default:
                    break;
                }                
              }     
#ifdef DEBUG                       
              Serial.print("kpd.key[");
              Serial.print(i);
              Serial.print("]: ");
              Serial.print("Key ");
              Serial.print(code - 1);
              Serial.println(msg);
#endif
            }
        }
    }

    // Encoders
    for(int i = 0; i < NUMCOLS; i++) {
      byte key;
      newPositionEncoders[i] = encoders[i].read();
      long difEncoder = newPositionEncoders[i] - oldPositionEncoders[i];
      if(difEncoder != 0) {
        if(difEncoder > 0) {
          key = keys[ENCODER_INCREMENT_KEYS][i];
          Joystick.button(key, 1);
          delay(KEY_PRESS_TIME);
          Joystick.button(key, 0);
          temporarily_increase_led_brightness(20);
        }
        else if(difEncoder < 0) {
          key = keys[ENCODER_INCREMENT_KEYS][i] + NUMCOLS;
          Joystick.button(key, 1);
          delay(KEY_PRESS_TIME);
          Joystick.button(key, 0);
          temporarily_increase_led_brightness(20);
        }
        oldPositionEncoders[i] = newPositionEncoders[i]; 
#ifdef DEBUG
        Serial.print("encoder[");
        Serial.print(i);
        Serial.print("]: ");
        Serial.print(difEncoder);
        Serial.print(": key = ");
        Serial.print(key - 1);
        Serial.println();
#endif
      }
    }
}  // End loop


void temporarily_increase_led_brightness(uint32_t msec) {
      analogWrite(ledPin, 100); 
      delay(msec);
      analogWrite(ledPin,   5);  
}

