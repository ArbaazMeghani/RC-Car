/*
 * Arbaaz Meghani
 * Description: Controller for RC-Car. Gets value of potentiometer and joystick and sends it using an IR Blaster.
 * 
 */

#include <IRLib.h>

IRsend My_Sender;

void loop() {
  int joystickValue = analogRead(0);
  int potentiometerValue = analogRead(1)+1024;
  My_Sender.send(SONY, joystickValue, 20);
  My_Sender.send(SONY, potentiometerValue, 20);

  delay(100);
}

