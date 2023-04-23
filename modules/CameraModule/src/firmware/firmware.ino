/*
||
|| @file firmware.ino
|| @author Luis Alejandro Bernal Romero (Aztlek)
|| @description
|| | This firmware is for the "Camera Module" of the "Modular Cockpit".
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


// Keypad
const byte NUMROWS = 4;
const byte NUMCOLS = 5;
const byte MAXKEYS = NUMROWS * NUMCOLS;
char keys[NUMROWS][NUMCOLS] = {
  { 0,  1,  2,  3,  4},
  { 5,  6,  7,  8,  9},
  {10, 11, 12, 13, 14},
  {15, 16, 17, 18, 19}
};


// Characters
int chs[MAXKEYS] = {
  'z'     , KEY_F4  , 'z'     , 0             , 0     ,
  KEYPAD_7, KEYPAD_8, KEYPAD_9, KEYPAD_ASTERIX, 1     ,
  KEYPAD_4, KEYPAD_5, KEYPAD_6, 0             , 2     ,
  KEYPAD_1, KEYPAD_2, KEYPAD_3, 0             , KEY_F4
};

#define keyToCh(key) (chs[key])

byte rowPins[NUMROWS] = {  2,  3,  4,  5};
byte colPins[NUMCOLS] = {  6,  7,  8,  9, 10};

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, NUMROWS, NUMCOLS );

// Keys
#define KEY_PRESS_TIME 150

// // Toggle switchs
// typedef enum{ OFF, ON} T_ToggleSwitchState;
// T_ToggleSwitchState toggleSwitchStates[NUMCOLS] = {OFF, OFF, OFF, OFF, OFF};
// #define toggleSwitchState(code) (toggleSwitchStates[(code) - 1])
// #define isToggleSwitch(code) ((code) >= 1 && (code) <= 5)
// #define offCodeToggleSwitch(code) ((code) + NUMCOLS)

// Encoders
#define NUM_ENCODERS 6
Encoder encoders[NUM_ENCODERS] = {
  Encoder(11, 12), // 0 ZOOM_3RD_PERSON
  Encoder(22, 21), // 1 FOV
  Encoder(20, 19), // 2 Y_OFFSET
  Encoder(18, 17), // 3 Z_OFFSET
  Encoder(16, 15), // 4 DOF
  Encoder(14, 29)  // 5 X_OFFSET
};
//                               ZOOM_3RD_PERSON, FOV         , Y_OFFSET, Z_OFFSET     , DOF     , X_OFFSET
int inc_encoder[NUM_ENCODERS] = {  3            , KEYPAD_PLUS , KEY_UP  , KEY_PAGE_UP  , KEY_HOME, KEY_RIGHT};
int dec_encoder[NUM_ENCODERS] = { -3            , KEYPAD_MINUS, KEY_DOWN, KEY_PAGE_DOWN, KEY_END , KEY_LEFT} ;
long oldPositionEncoders[NUM_ENCODERS] = { 0, 0, 0, 0, 0, 0};
long newPositionEncoders[NUM_ENCODERS];
#define ENCODER_INCREMENT_KEYS 1

// Potentiometer
#define potentiometerPin 23
int potentiometerOldValue = 0;


String msg;

extern "C" uint32_t set_arm_clock(uint32_t frequency);

void setup() {
  set_arm_clock(24000000);
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  pinMode(22, INPUT_PULLUP);
  pinMode(21, INPUT_PULLUP);
  pinMode(20, INPUT_PULLUP);
  pinMode(19, INPUT_PULLUP);
  pinMode(18, INPUT_PULLUP);
  pinMode(17, INPUT_PULLUP);
  pinMode(16, INPUT_PULLUP);
  pinMode(15, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);
  pinMode(29, INPUT_PULLUP);
  Serial.begin(9600);
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
              int ch = keyToCh(code);
              KeyState keyState = kpd.key[i].kstate;
              switch (keyState) {  // Report active key state : IDLE, PRESSED, HOLD, or RELEASED
                case PRESSED:
                  msg = "PRESSED";
                  if(code == 9 || code == 14) {
                      Joystick.button((uint8_t)ch, 1);
                  }
                  else if(ch != 0) {
                    Keyboard.press(ch);
                  }                    
                break;
                case RELEASED:
                  msg = "RELEASED";
                  if(code == 9 || code == 14) {
                      Joystick.button((uint8_t)ch, 0);
                  }
                  else if(ch != 0) {
                    Keyboard.release(ch);
                  }
                break;
                default:
                break;
              }
              Serial.print("kpd.key[");
              Serial.print(i);
              Serial.print("]: ");
              Serial.print("Code=");
              Serial.print(code);
              Serial.print(" ,Ch=");
              switch(ch) {
                case KEYPAD_7:
                  Serial.print("KEYPAD_7");
                  break;
                case KEYPAD_8:
                  Serial.print("KEYPAD_8");
                  break;
                case KEYPAD_9:
                  Serial.print("KEYPAD_9");
                  break;
                case KEYPAD_4:
                  Serial.print("KEYPAD_4");
                  break;
                case KEYPAD_5:
                  Serial.print("KEYPAD_5");
                  break;
                case KEYPAD_6:
                  Serial.print("KEYPAD_6");
                  break;
                case KEYPAD_1:
                  Serial.print("KEYPAD_1");
                  break;
                case KEYPAD_2:
                  Serial.print("KEYPAD_2");
                  break;
                case KEYPAD_3:
                  Serial.print("KEYPAD_3");
                  break;
                case KEYPAD_ASTERIX:
                  Serial.print("KEYPAD_ASTERIX");
                  break;
                case KEY_F4:
                  Serial.print("KEY_F4");
                  break;
                default:
                  if(isPrintable(ch)) {
                    Serial.print((char)ch);
                  }
              }
              Serial.print("(");
              Serial.print(ch);
              Serial.print(")");
              Serial.print(", ");
              Serial.print(msg);
              Serial.println();
            }
        }
    }

    // Encoders
    for(int i = 0; i < NUM_ENCODERS; i++) {
      newPositionEncoders[i] = encoders[i].read();
      long difEncoder = newPositionEncoders[i] - oldPositionEncoders[i];
      int key = (difEncoder > 0) ? inc_encoder[i] : dec_encoder[i];
      if(difEncoder != 0) {
        if(i == 0) { // send as mouse
          Mouse.scroll(key);
        }      
        else if(i != 0) { // send as keyboard
          Keyboard.press(key);
          delay(KEY_PRESS_TIME);
          Keyboard.release(key);
        }        
        oldPositionEncoders[i] = newPositionEncoders[i]; 
        
        Serial.print("encoder[");
        Serial.print(i);
        Serial.print("]: difEncoder=");
        Serial.print(difEncoder);
        Serial.print(", key=");
        switch(key) {
          case KEY_HOME:
            Serial.print("KEY_HOME");
            break;
          case KEY_END:
            Serial.print("KEY_END");
            break;
          case KEY_PAGE_UP:
            Serial.print("KEY_PAGE_UP");
            break;
          case KEY_PAGE_DOWN:
            Serial.print("KEY_PAGE_DOWN");
            break;
          case KEY_RIGHT:
            Serial.print("KEY_RIGHT");
            break;
          case KEY_LEFT:
            Serial.print("KEY_LEFT");
            break;
          case KEY_UP:
            Serial.print("KEY_UP");
            break;
          case KEYPAD_PLUS:
            Serial.print("KEYPAD_PLUS");
            break;
          case KEYPAD_MINUS:
            Serial.print("KEYPAD_MINUS");
            break;
        }
        Serial.println();
      }      
    }

    // Potentiometer-
    int potentiometerValue = analogRead(potentiometerPin);
    if(abs(potentiometerValue - potentiometerOldValue) > 2) {
      Serial.print("potentiometer");
      Serial.print(": ");
      Serial.print(potentiometerValue);
      Serial.println();
      Joystick.X(potentiometerValue);
      potentiometerOldValue = potentiometerValue;
    }
   
}  // End loop