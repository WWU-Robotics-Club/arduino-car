/*
 *  By: Samuel Loredo
 *  
 *  For this example, we have two motors connected to the same motor controller, on the two sides. 
 *  
 *  Not perfect, but pretend this is the motor controller.
 *       __________________________
 *       |       |||||||           |
 *       |       |||||||           |
 *Rmotor+][]  /\                 [][+Lmotor
 *Rmotor-][]  \/                 [][-Lmotor
 *       |  [] [] []               |
 *        --12-GND-5-re-1-2-3-4-le--
 *           |  |  |  | | | | |  |
 *           |  |  |  | | | | |  Left enable, optional.  Default is that it is bridged => Always HIGH or LOW depending if you turn it on or off.  I pluged this one into pin 6 on the Arduino.
 *           |  |  |  | | | | What I called motorPinLL, and I ran a wire from this pin to pin 2 on the Arduino.
 *           |  |  |  | | | What I called motorPinL, running from this pin to pin 3 on the Arduino.
 *           |  |  |  | | What I called motorPinL, running from this pin to pin 4 on the Arduino.
 *           |  |  |  | What I called motorPinL, running from this pin to pin 5 on the Arduino.
 *           |  |  |  Right enable, optional.  Default is that it is bridged => Always HIGH or LOW depending if you turn it on or off.  I pluged this one into pin 7 on the Arduino.
 *           |  |  5 volt input.
 *           |  Ground.  All grounds must connect together.
 *           12 volt input.  My battery is plugged into this port.  Even though my battery is only 7.4 V, I have int plugged into this port since it is more than 5 V.
*/

// Motor placement may be different in your case.  This code was written for my case.

int motorPinLL = 2;  //Backward Pin (-)  -  This is connected to the digital pin 2
int motorPinL  = 3;  //Forward Pin  (+)  -  This is connected to the digital pin 2 
int Leftenable = 6;  //If you unbridge the speed controller, then you need to control it by the arduino.  In this example its on pin 6
int motorPinR  = 4;  //Forward Pin  (+)  -  This is connected to the digital pin 4
int motorPinRR = 5;  //Backward Pin (-)  -  This is connected to the digital pin 5
int Rightenable= 7;  //If you unbridge the speed controller, then you need to control it by the arduino.  In this example its on pin 7

void setup() {
  // put your setup code here, to run once:
  
  // Setting up the pins named above to have an output signal.  Won't work without a setup.
  pinMode(motorPinL,   OUTPUT);  //Left motor (+)
  pinMode(motorPinLL,  OUTPUT);  //Left motor (-)
  pinMode(Leftenable,  OUTPUT);  //Enables left motor
  pinMode(motorPinR,   OUTPUT);  //Right motor (+)
  pinMode(motorPinRR,  OUTPUT);  //Right motor (-)
  pinMode(Rightenable, OUTPUT);  //Enables Right motor
}

//  These are combinations of different digital writes which allow you to control the movement of the motors.
void forward() //Full Foreward.
{  
  digitalWrite(motorPinRR, 1);
  digitalWrite(motorPinR, 0);
  digitalWrite(motorPinLL, 1);
  digitalWrite(motorPinL, 0); 
}

void Forward(int velocity)  // ***** Example code for using the "Rightenable" and "Leftenable" pins.  Optional, the bluetooth doesn't care how you talk with your motors.
{
  // Left Motor forward
  digitalWrite(motorPinLL, HIGH);     //Establishes forward direction of Channel A
  digitalWrite(motorPinL, LOW);       //Disengage the Brake for Channel A
  analogWrite(Leftenable, velocity);  //Setting speed to velocity variable
  
  // Right Motor B forward
  digitalWrite(motorPinR, HIGH);      //Establishes forward direction of Channel B
  digitalWrite(motorPinRR, LOW);      //Disengage the Brake for Channel B
  analogWrite(Rightenable, velocity); //Setting speed to velocity variable
} // ***** WARNING ***** I copied this part of the code from a different code than the others, so there might be some issues with it that I haven't debugged yet.

void backward() //Full backward.
{ 
  digitalWrite(motorPinRR, 0);
  digitalWrite(motorPinR, 1);
  digitalWrite(motorPinLL, 0);
  digitalWrite(motorPinL, 1);
}

void turn_right() //Turn Right
{
  digitalWrite(motorPinRR, 1);
  digitalWrite(motorPinR, 0);
  digitalWrite(motorPinLL, 0);
  digitalWrite(motorPinL, 1);
}

void vere_right() //Slowly turn right
{
  analogWrite(Rightenable, 255);
  analogWrite(Leftenable, 75);
  delay(1000);
  analogWrite(Rightenable, 0);
  analogWrite(Leftenable, 0);
}

void vere_left() //Slowly turn left
{
  analogWrite(Rightenable, 75);
  analogWrite(Leftenable, 255);
  delay(1000);
  analogWrite(Rightenable, 0);
  analogWrite(Leftenable, 0);
}
  
void turn_left() //Turn Left
{
  digitalWrite(motorPinRR, 0);
  digitalWrite(motorPinR, 1);
  digitalWrite(motorPinLL, 1);
  digitalWrite(motorPinL, 0);
}

void off() //Full off.
{
  digitalWrite(motorPinRR, 0);
  digitalWrite(motorPinR, 0);
  digitalWrite(motorPinLL, 0);
  digitalWrite(motorPinL, 0);
}


void loop() {
  // put your main code here, to run repeatedly:
  
forward();

delay(1000);

backward();

delay(1000);

}
