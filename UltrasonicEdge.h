/*
  Ultrasonic.h - Library for HR-SC04 Ultrasonic Ranging Module.
  Created by ITead studio. Alex, Apr 20, 2010.
  iteadstudio.com
*/


#ifndef UltrasonicEdge_h
#define UltrasonicEdge_h

#include "Arduino.h"

#define CM 1
#define INC 0

class UltrasonicEdge
{
  public:
    UltrasonicEdge(int TP, int EP);
    long Timing();
    long Ranging(int sys);

    private:
    int Trig_pin;
    int Echo_pin;
    long  duration1,distacne1_cm,distance1_inc;
    
};

#endif
