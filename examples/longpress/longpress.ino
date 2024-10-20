/******************************************************************************
*  longpress.ino
*  BC6xxx & BC759x Key Scan Interface Library Example Code
*
*  This code uses Serial1 to connect a BC6xxx or BC759x chip. Besides
*  normal single key pressing, it can also detect the long-press of particular
*  keys.
*  Serial port is used to print the keypad detection results.
*  This software monitors keypad actions and print key values on Serial. When key 
*  1 or key 5 is pressed for more than 3s, a new key event with user defined key 
*  value of 120(0x78) or 121(0x79) is generated.
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
*     V2.0 May 2021, changed to use hardware Serial to print key values.
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

// Definition of long-press keys
const unsigned char  lp1[2]    = { 1, 120 };          // Longpress key 1, detecting long-pressing of key 1 and use 120 as the user defined key value
const unsigned char  lp2[2]    = { 5, 121 };          // Longpress key 2, detecting long-pressing of key 5 and use 121 as the user defined key value
const unsigned char* LPList[2] = { lp1, lp2 };        // Longpress key list

void setup() {
  Serial.begin(115200);                     // Initialize Serial for monitoring
  KEYBOARD_SERIAL.begin(9600);              // Initialize keyboard serial port
  Keypad.defLongpressKey(LPList, 2);        // Define long-press keys
  Keypad.setLongpressCount(60);             // Set long-press time to 3s (50ms * 60)
}

void loop() {
    Keypad.checkChanges();                // let the key scan library to update key status
    if (Keypad.isKeyChanged() == true) {  // if there is any detectable key change
      Serial.println(Keypad.getKeyValue());   // print key value on Serial (use Serial Monitor to see it!)
    }
    Keypad.longpressTick();        // Tick the long-press detector in BC_key_scan library
    // put your main code here, to run repeatedly:
    delay(50);                     // delay 50ms
}
