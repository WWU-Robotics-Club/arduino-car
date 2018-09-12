/*
 *  By: Samuel Loredo and Bobby Berglund
 *  
 *  Works with the Arduino Bluetooth RC Car android app: https://play.google.com/store/apps/details?id=braulio.calle.bluetoothRCcontroller
 *
 *  Bluetooth Module
 *  
 *  --------------------------------
 *  |                         State| No connection (This pin is not used)
 *  |                           RXD|- This pin connects to pin 1 (TX) on your Arduino
 *  |                           TXD|- This pin connects to pin 0 (RX) on your Arduino
 *  |                           GND|- This pin connects to one of your ground pins.
 *  |                           VCC|- This pin connects to your 3.3v pin on your Arduino.
 *  |                        Wakeup| No connection (This pin is not used)
 *  --------------------------------
 *  
 *  The RXD pin acts as a receiver which connects to the TX pin on the Arduino, the transmitter.
 *  The TXD pin acts as a transmitter which connects to the RX pin on the Arduino, the receiver.
 *  
 *  Commands can also be sent via the Serial Monitor instead of using a bluetooth module 
 *  This can be accessed under tools or by pressing ctrl+shift+m.
 *  
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

int motorPinLL = 8;  //Backward Pin (-)  -  This is connected to the digital pin 2
int motorPinL  = 9;  //Forward Pin  (+)  -  This is connected to the PWM supported digital pin 3
int motorPinRR = 10;  //Backward Pin (-)  -  This is connected to the digital pin 4
int motorPinR  = 11;  //Forward Pin  (+)  -  This is connected to the PWM supported digital pin 5

//Setup some variables for storing controls from serial

int current_speed = 0; //Current Speed Settings
char current_dir = 'S'; //Current movement direction, forward, backward or neutral (stopped)
char current_turn = 'S'; //Current turn direction, right, left, or neutral (stopped)
bool light = false; //Current light value

void setup() {
  //Initialize Serial Communications on port 9600
  Serial.begin(9600);
  
  // Setting up the pins named above to have an output signal.  Won't work without a setup.
  pinMode(motorPinL,   OUTPUT);  //Left motor (+)
  pinMode(motorPinLL,  OUTPUT);  //Left motor (-)
  pinMode(motorPinR,   OUTPUT);  //Right motor (+)
  pinMode(motorPinRR,  OUTPUT);  //Right motor (-)
}


void spinwheel(int motorPinA, int motorPinD, int spd)
{  
  //If there is a positive value for the speed we will go forward.
  if (spd >= 0) {
    digitalWrite(motorPinD, LOW); //Write low so current flows down to this pin
    analogWrite(motorPinA, spd); //Write speed value to PWM pin
  }
  //If the value is negative we go backwards.
  else if (spd < 0) {
    digitalWrite(motorPinD, HIGH); //Write high so current flows from this pin.
    analogWrite(motorPinA, 255+spd); //Invert signal since 0 is a larger voltage difference and gives more speed.
  }
}

void powerwheels(float Lpow, float Rpow)
{
  //Setup equations for calculating a speed for the wheels
  //Analog values range from 0 to 255 so we do a ratio conversion to change a value from 0 to 10 to 0 to 255.
  //This value is multiplied by our power factor which is a float ranging between 0 and 1.
  int Lspd = int(Lpow*float(current_speed)*255.0/10.0);
  int Rspd = int(Rpow*float(current_speed)*255.0/10.0);
  
  spinwheel(motorPinL,motorPinLL,Lspd); //Set left wheel to turn
  spinwheel(motorPinR,motorPinRR,Rspd); //Set right wheel to turn
}


// Input handler for changing settings based on what the input character was
void inputhandler(char i) {
  switch (i) {
    //Speed Settings
    case '0': //Speed Level 0
      current_speed = 0;
      break;
    case '1': //Speed Level 1
      current_speed = 1;
      break;
    case '2': //Speed Level 2
      current_speed = 2;
      break;
    case '3': //Speed Level 3
      current_speed = 3;
      break;
    case '4': //Speed Level 4
      current_speed = 4;
      break;
    case '5': //Speed Level 5
      current_speed = 5;
      break;
    case '6': //Speed Level 6
      current_speed = 6;
      break;
    case '7': //Speed Level 7
      current_speed = 7;
      break;
    case '8': //Speed Level 8
      current_speed = 8;
      break;
    case '9': //Speed Level 9
      current_speed = 9;
      break;
    case 'q': //Speed Level 10
      current_speed = 10;
      break;

    //Direction Commands
    case 'F': //Forward
      powerwheels(1,1);
      break;
    case 'B': //Back
      powerwheels(-1,-1);
      break;
    case 'L': //Left
      powerwheels(-1,1);
      break;
    case 'R': //Right
      powerwheels(1,-1);
      break;
    case 'G': //Forward Left
      powerwheels(1,0.5);
      break;
    case 'I': //Forward Right
      powerwheels(0.5,1);
      break;
    case 'H': //Back Left
      powerwheels(-0.5,-1);
      break;
    case 'J': //Back Right
      powerwheels(-1,-0.5);
      break;
    case 'S': //Stop
      powerwheels(0,0);
      break;

    //Light Commands
    case 'W': //Light on
      light = true;
      break;
    case 'w': //Light off
      light = false;
      break;
  }
}

void loop() {
  // Loop through serial messages received.
  while (Serial.available()) {
    // Read the incoming characters received.
    char inChar = (char)Serial.read();
    Serial.println(inChar);
    // Pass the input to the inputhandler function.
    inputhandler(inChar);
  }
}
