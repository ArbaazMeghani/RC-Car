/*
 * Arbaaz Meghani
 * Description: Processor for the RC-Car.  Receives the input from controller using IR Receiver and modifies it so it can be easily read by the Driver.
 */
#include <IRLib.h>
 
IRrecv My_Receiver(11);
 
IRdecode My_Decoder;

int angl_U = 0;
int spd_U = 0;

int angl = 0;
int spd = 0;
int dir = 0;

void setup()
{
  Serial.begin(9600);
  My_Receiver.enableIRIn();
}
 
void loop() {
  if (My_Receiver.GetResults(&My_Decoder)) {
    My_Decoder.decode();
    if(My_Decoder.value <= 1023)
      spd_U = My_Decoder.value;
    else if(My_Decoder.value <= 2047)
      angl_U = My_Decoder.value - 1024;

    angl = map(angl_U, 0, 1023, 135, 45);
    if(spd_U >= 515) {
      dir = 1;
      spd = map(spd_U, 512, 1023, 0, 255);
    }
    else if(spd_U <= 509) {
      dir = 0;
      spd = map(spd_U, 512, 0, 0, 255);
    }
    else
      spd = 0;

    Serial.print(spd);
    Serial.print(",");
    Serial.print(dir);
    Serial.print(",");
    Serial.println(angl);

    delay(150);
    My_Receiver.resume();
  }

}
