/******************************************************************************
*  longpress.ino
*  BC6xxx & BC759x Key Scan Interface Library Example Code
*
*  This code uses Serial1 to connect a BC6xxx or BC759x chip. it can
*  detect key presses.
*  Serial is also used to communicate with computer. When a key is
*  pressed, the key value is printed to the Serial port so can be
*  seen with the Arduino Serial Monitor
*  This code runs on any Arduino compatible boards.
*
*  Dependencies:
*     This code depends on the following libraries:
*        Arduino Software Serial Library
*        UART_Keyboard_Driver Library
*
*  Author:
*     This software is written by BitCode. https://bitcode.com.cn
*
*  Version:
*     V1.0 March 2021
*     V2.0 May 2021.  Changed to use Serial to print key value
*     V3.0 October 2024. Changed default keyboard port to Serial1
*
*  License:
*     MIT license. It can be used for both open source and commercial projects.
******************************************************************************/
#include <UART_Keyboard.h>

#define KEYBOARD_SERIAL Serial1		// By default this code uses Serial1 as keyboard port
// If you are using Arduino with only 1 Serial (such as UNO), you may want to disable 
// the above line and use the following setting:
// #include <SoftwareSerial.h>
// #define KEYBOARD_SERIAL	swSerial
// SoftwareSerial swSerial(11, 12);          // creating SoftwareSerial instance, using pin 11 as Rx, 12 as Tx (Tx not used in this example)

UartKeyboard      Keypad(KEYBOARD_SERIAL);        // creating UartKeyboard instance


void setup() {
  Serial.begin(115200);               // Initialize Serial for monitoring
  KEYBOARD_SERIAL.begin(9600);        // Initialize keyboard serial port
}

void loop() {
    Keypad.checkChanges();            // let the key scan library to update key status
    if (Keypad.isKeyChanged() == true) {       // if there is any detectable key change
      Serial.println(Keypad.getKeyValue());   // print key value on Serial (use Serial Monitor to see it!)
    }
    // put your main code here, to run repeatedly:
    delay(50);                     // delay 50ms
}
