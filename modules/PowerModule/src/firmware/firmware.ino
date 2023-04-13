/*
 * firmware.ino
 * 
 * @author Luis Alejandro Bernal Romero (Aztlek)
 * 
 */
 
/* 
 * 
 * Copyright (C) 2020 Luis Alejandro Bernal Romero (Aztlek)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

 /*
  * The Button Box is made up of a series of switches, which can be 
  * used to make certain controls of the ship "more physical", thus 
  * facilitating the piloting of the ship in Star Citizen. For 
  * example, it can be used to raise and lower the landing gear, to 
  * turn the ship on and off, to lower and raise the shields and 
  * everything else you want.
  */
 
#include <Keypad.h>
#include <Encoder.h>

const byte NUMROWS = 4;
const byte NUMCOLS = 5;
const byte MAXKEYS = NUMROWS * NUMCOLS;


// Kaypad
char keys[NUMROWS][NUMCOLS] = {
  // Toggle switchs
  // For the on position of the switches
  {     1,  2,  3,  4,  5},
  // For the off position of the switches
  // {  6,  7,  8,  9, 10},

  // Encoders
  //  for the increment
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
String msg;

// Keys

#define MAX_THROTTLE_KEY 25

// Toggle switchs
typedef enum{ OFF, ON} T_ToggleSwitchState;
T_ToggleSwitchState toggleSwitchStates[NUMCOLS] = {OFF, OFF, OFF, OFF, OFF};
#define delayToggleSwitch 150
#define toggleSwitchState(code) (toggleSwitchStates[(code) - 1])
#define isToggleSwitch(code) ((code) >= 1 && (code) <= 5)
#define offCodeToggleSwitch(code) ((code) + NUMCOLS)

// Encoders
byte encodersPinsA[NUMCOLS] = { 23, 21, 19, 17, 15};
byte encodersPinsB[NUMCOLS] = { 22, 20, 18, 16, 14};
Encoder encoders[NUMCOLS] = {
  Encoder(encodersPinsA[0], encodersPinsB[0]),
  Encoder(encodersPinsA[1], encodersPinsB[1]),
  Encoder(encodersPinsA[2], encodersPinsB[2]),
  Encoder(encodersPinsA[3], encodersPinsB[3]),
  Encoder(encodersPinsA[4], encodersPinsB[4]),
};
long oldPositionEncoders[NUMCOLS];
long newPositionEncoders[NUMCOLS];
#define ENCODER_INCREMENT_KEYS 1
#define ENCODER_INCREMENT_KEY(i) (keys[ENCODER_INCREMENT_KEYS][i] + NUMCOLS)

extern "C" uint32_t set_arm_clock(uint32_t frequency);

void setup() {
  set_arm_clock(24000000);
#ifdef SERIAL
  Serial.begin(9600);
#endif

  // Encoders
  for(int i = 0; i < NUMCOLS; i++) {
    oldPositionEncoders[i] = 0;
  }
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
                    delay(delayToggleSwitch);
                    Joystick.button(code, 0);                           
                    toggleSwitchState(code) = ON;
                  }
                  else if(keyState == RELEASED && toggleSwitchState(code) != OFF ) 
                  {
                    msg = " OFF.";
                    Joystick.button(offCodeToggleSwitch(code), 1);
                    delay(delayToggleSwitch);
                    Joystick.button(offCodeToggleSwitch(code), 0);      
                    toggleSwitchState(code) = OFF;                      
                  } 
              }
              else // Normal key
              {
                switch (keyState) {  // Report active key state : IDLE, PRESSED, HOLD, or RELEASED
                    case PRESSED:
                      msg = " PRESSED.";
                      Joystick.button(code, 1);
                    break;
                    case RELEASED:
                      msg = " RELEASED.";
                      Joystick.button(code, 0);
                    break;
                    default:
                    break;
                }                
              }
#ifdef SERIAL                              
              Serial.print("kpd.key[");
              Serial.print(i);
              Serial.print("] ");
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
          delay(delayToggleSwitch);
          Joystick.button(key, 0);
        }
        else if(difEncoder < 0) {
          key = ENCODER_INCREMENT_KEY(i);
          Joystick.button(key, 1);
          delay(delayToggleSwitch);
          Joystick.button(key, 0);
        }
        oldPositionEncoders[i] = newPositionEncoders[i]; 
#ifdef SERIAL  
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

