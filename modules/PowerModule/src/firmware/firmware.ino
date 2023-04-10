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

const byte NUMROWS = 4;
const byte NUMCOLS = 5;
const byte MAXKEYS = NUMROWS * NUMCOLS;

char keys[NUMROWS][NUMCOLS] = {
  { 0,  1,  2,  3,  4},
  { 5,  6,  7,  8,  9},
  { 10, 11, 12, 13, 14},
  { 15, 16, 17, 18, 19}
};
byte rowPins[NUMROWS] = { 2, 3,  4,  5};
byte colPins[NUMCOLS] = { 8, 9, 10, 11, 12};

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, NUMROWS, NUMCOLS );
String msg;

void setup() {
  Serial.begin(9600);
}


void loop() {
    // Fills kpd.key[ ] array with up-to 10 active keys.
    // Returns true if there are ANY active keys.
    if (kpd.getKeys())
    {
        for (int i=0; i<LIST_MAX; i++)   // Scan the whole key list.
        {
            if ( kpd.key[i].stateChanged )   // Only find keys that have changed state.
            {
                switch (kpd.key[i].kstate) {  // Report active key state : IDLE, PRESSED, HOLD, or RELEASED
                    case PRESSED:
                    msg = " PRESSED.";
                break;
                    case HOLD:
                    msg = " HOLD.";
                break;
                    case RELEASED:
                    msg = " RELEASED.";
                break;
                    case IDLE:
                    msg = " IDLE.";
                }
                Serial.print("Key ");
                Serial.print((byte)kpd.key[i].kchar);
                Serial.println(msg);
            }
        }
    }
}  // End loop
