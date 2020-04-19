/*
  Ultrasonic.cpp - Library for HC-SR04 Ultrasonic Ranging Module.library

  Created by ITead studio. Apr 20, 2010.
  iteadstudio.com
*/

#include "Arduino.h"
#include "UltrasonicEdge.h"

UltrasonicEdge::UltrasonicEdge(int TP, int EP)
{
   pinMode(TP,OUTPUT);
   pinMode(EP,INPUT);
   Trig_pin=TP;
   Echo_pin=EP;
}

long UltrasonicEdge::Timing()
{
  digitalWrite(Trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig_pin, LOW);
  duration1 = pulseIn(Echo_pin,HIGH);
  return duration1;
}

long UltrasonicEdge::Ranging(int sys)
{
  Timing();
  distacne1_cm = duration1 /29 / 2 ;
  distance1_inc = duration1 / 74 / 2;
  if (sys)
  return distacne1_cm;
  else
  return distance1_inc;
}
