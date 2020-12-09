#include <Arduino.h>
#include "parser.h"

extern void initserver();

//void storePos();

void setup()
{
  // put your setup code here, to run once:

  initialize(0);
  initserver();
//  inithandpad();

}
void loop() {
  // Si une donnée est dispo sur le port série
  while (Serial.available () > 0)
  {
    char c = '\0';
    c = Serial.read ();
    processIncomingByte (c);
  }

  // Si une donnée est dispo sur le port I2C
//  while (parser.handleConnected() && (Wire.available() >0))
//    parser.processIncomingByte (Serial.read ());

  
  move();
  // time2= millis();
  // if ((time2 - time1) > 60000) // save the position each minute
  // {
  //   storePos();
  //   time1 = millis();
  // }
}

