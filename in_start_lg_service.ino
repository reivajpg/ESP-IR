#include <Arduino.h>
#include <IRremoteESP8266.h>
//#include <IRremote.h>
#include <IRsend.h>


const uint16_t kIrLed = 13;  //13 (D7)//15 (D8)// ESP8266 GPIO pin to use. Recommended: 4 (D2).
IRsend irsend(kIrLed);      // Set the GPIO to be used to sending the message.

//0x20DFDF20 - "IN-START" preselected below
//0x20DF3FC0 - "RESET TO FACTORY"
//MEGA328 IR PINOUT INT1 PD3
//PIN 0 4 1 3 Use TV remote 2018-2020

void setup() {
  irsend.begin();
  Serial.begin(115200, SERIAL_8N1);
}

void loop() {
 Serial.println("IN-START");
 Serial.println("PIN 0 4 1 3"); 
 for (int i = 0; i < 4; i++){
 irsend.sendNEC(0x20DFDF20, 32); //"IN-START" 2018-2020 models
 delay(5000);} //Command repeats every 5 seconds on first run untill arduino power disconnect
}