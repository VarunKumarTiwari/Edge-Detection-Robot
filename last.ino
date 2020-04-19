/*          Arduino Obstacle Avoiding Robot
    with a servo motor and an ultrasonic sensor HC-SR04
              LED and buzzer
          
  Dev: Michalis Vasilakis // Date: 11/12/2015 // www.ardumotive.com */


//Libraries
#include <Servo.h> 
#include "Ultrasonic.h"
#include "UltrasonicEdge.h"

//Constants
const int motorA1= 4;     //motor A positive (+) pin to pin 6 (PWM) (from L298 module!)
const int motorA2= 5;         //motor A negative (-) pin to pin 9 (PWM)
const int motorB1=6;     //motor B positive (+) pin to pin 10 (PWM)
const int motorB2=7;     //motor B negative (-) pin to pin 11 (PWM)

Ultrasonic ultrasonic(10 ,9); //Create Ultrsonic object ultrasonic(trig pin,echo pin)
UltrasonicEdge ultrasonicEdge(2 ,3); 
Servo myservo;          //Create Servo object to control a servo

//Variables
int distance; //Variable to store distance from an object
int distance1;
int checkRight;
int checkLeft;
int function=0;         //Variable to store function of robot: '1' running or '0' stoped. By default is stoped
int buttonState=0;            //Variable to store the state of the button. By default '0'
int pos=90;             //Variable to store the servo position. By default 90 degrees - sensor will 'look' forward
int flag=0;                 //Useful flag to keep the button state when button is released 
int arra[10];
int siz;
int lef=0;
int rig=1;
int result;

void setup()
{
    myservo.attach(11);      //Servo pin connected to pin 11
    myservo.write(pos);        // tell servo to go to position in variable 'pos' 

  pinMode(motorA1,OUTPUT);
  pinMode(motorA2,OUTPUT);
  pinMode(motorB1,OUTPUT);
  pinMode(motorB2,OUTPUT);
  
}

void loop()
{
       int v = 0;
      siz = sizeof(arra) / sizeof(arra[0]);
      
  
//If button is pressed then:
    //Read distance...
    distance = ultrasonic.Ranging(CM); //Tip: Use 'CM' for centimeters or 'INC' for inches
    distance1 = ultrasonicEdge.Ranging(CM);
    //Check for objects...
 if(distance1<6)
 {   
    if (distance > 20){
      forward(); //All clear, move forward!
      
    }
    else if (distance <=20){
      stop(); //Object detected! Stop the robot and check left and right for the better way out!
   
      
       
      for(pos = 0; pos < 180; pos += 1){  //goes from 0 degrees to 180 degrees 
                myservo.write(pos);             //tell servo to go to position in variable 'pos' 
                delay(10);                      //waits 10ms for the servo to reach the position 
            } 
            
            checkLeft = ultrasonic.Ranging(CM);   //Take distance from the left side
            
            for(pos = 180; pos>=0; pos-=1){     //goes from 180 degrees to 0 degrees                           
                myservo.write(pos);             //tell servo to go to position in variable 'pos' 
                delay(10);                      //waits 10ms for the servo to reach the position   
            }
            
            checkRight= ultrasonic.Ranging(CM);
            
            myservo.write(90);                   // Sensor "look" forward again

            
            
            //Finally, take the right decision, turn left or right?
            if (checkLeft < checkRight){
              left();
              delay(400);
              left();
              delay(400);
              
               // delay, change value if necessary to make robot turn.            
              }
            else if (checkLeft > checkRight){
              right();
              delay(400); // delay, change value if necessary to make robot turn.
              right();
              delay(400);
              
            }
            else if (checkLeft <= distance && checkRight <= distance){
              backward(); //The road is closed... go back and then left ;)
                if (checkLeft < checkRight){
                  left();
              delay(400);
              left();
              delay(400);
               // delay, change value if necessary to make robot turn.            
                }
                else if (checkLeft > checkRight){
                  right();
                  delay(400); // delay, change value if necessary to make robot turn.
                  right();
                  delay(400);
                  }
            }
    }
    //check array
    
      arra[v]=lef;
      arra[v+1]= rig;
      arra[v+2]=lef;
      arra[v+3]= rig;
      if(siz==3)
    {
      result = arra[0]%2;
      if(result == 0)
      {
        if(arra[1]%2!=0)
        {
          if(arra[2]%2==0)
          {
            right();
            right();
            right();
            right();
            delay(400);
          }
        }
          
        }
      else{
        if(arra[1]%2==0)
        {
          if(arra[2]%2!=0)
          {
            left();
            left();
            left();
            left();
            delay(400);
          }
          }
        }
      
    }
    
  }
else
{
  stop();
  delay(500);
  backward();
  delay(400);
  right();
              delay(400); // delay, change value if necessary to make robot turn.
              right();
              delay(400);
}
}

void forward(){
  
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
}

void backward(){
 
   
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW); 
}

void left(){
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
  
}

void right(){
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW); 
  
}

void stop(){
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, LOW);
}
