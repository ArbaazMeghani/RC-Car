/*
 * Arbaaz Meghani
 * Description: Driver for the RC-Car.  Receives the processed input and controls the servos and the motors to drive and turn the car.
 */
 
#include <Servo.h>

Servo sLeft;
Servo sRight;

int pinServoL = 7;
int pinServoR = 6;

int pinMotor1[] = {10, 9, 8};
int pinMotor2[] = {12, 13, 4};


int spd;
int angle;
int dir;

char arr[10];

void setup() {
  Serial.begin(9600);
  sLeft.attach(pinServoL);
  sRight.attach(pinServoR);
  for(int i = 0; i < 3; i++) {
    pinMode(pinMotor1[i], OUTPUT);
    pinMode(pinMotor2[i], OUTPUT);
  }
  stop();
  Serial.begin(9600);
}

void loop() {
  if(Serial.available()) {
    spd = Serial.readStringUntil(',').toInt();
    dir = Serial.readStringUntil(',').toInt();
    angle = Serial.parseInt();
   
    Serial.println(spd);
    Serial.println(dir);
    Serial.println(angle);
    sLeft.write(angle);
    sRight.write(angle);
  
    if(spd == 0)
      stop();
    else {
      if(dir)
        forward();
      else
        reverse();
    }  
  }
}

void forward() {
  digitalWrite(pinMotor1[1], HIGH); 
  digitalWrite(pinMotor1[0], LOW); 

  digitalWrite(pinMotor2[1], HIGH); 
  digitalWrite(pinMotor2[0], LOW);
  
  analogWrite(pinMotor1[2], spd);
  analogWrite(pinMotor2[2], spd);
}

void reverse() {
  digitalWrite(pinMotor1[0], HIGH); 
  digitalWrite(pinMotor1[1], LOW); 

  digitalWrite(pinMotor2[0], HIGH); 
  digitalWrite(pinMotor2[1], LOW);
  
  analogWrite(pinMotor1[2], spd);
  analogWrite(pinMotor2[2], spd);
}

void stop() {
  digitalWrite(pinMotor1[1], LOW); 
  digitalWrite(pinMotor1[0], LOW); 

  digitalWrite(pinMotor2[1], LOW); 
  digitalWrite(pinMotor2[0], LOW); 

  analogWrite(pinMotor1[2], spd);
  analogWrite(pinMotor2[2], spd);
}
