/*
 * Title:        Bluetooth Remote Control
 * Description:  This program is intented to work with a connected
 *               Bluetooth dongle to the robot and an Android phone
 *               running Blueberry application
 * Author:       Karl Kangur <karl.kangur@gmail.com>
 * Modified by:  CalebJ2
 * Version:      1.0
 * Website:      github
 */
#include <Servo.h>
Servo myservo;

#define LED 13

//pins connected to motor controller
#define right1 2
#define right2 3 //must be pwm enabled
#define left1 4
#define left2 5 //must be pwm enabled

#define maxDrive 255 //On a scale from 0 to 255. Defines what 100% speed is.

char serialData[32];
byte error = 0;
unsigned long lastComTime;
unsigned long lastDrive; //millis() when drive() was called. millis() returns milliseconds since program start
boolean connected; //has communicated with phone within last second? This is mostly unused.

void setup()
{
  //FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  pinMode(right1,OUTPUT);
  pinMode(right2,OUTPUT);
  pinMode(left1,OUTPUT);
  pinMode(left2,OUTPUT);
  pinMode(LED, OUTPUT);
  // the bluetooth dongle communicates at 9600 baud only
  Serial.begin(9600);
  lastComTime = millis();

  myservo.attach(6);
}

void loop()
{
  if((millis()-lastComTime) > 1500 && connected == true){//if this hasn't heard from phone for 1.5 seconds
    Serial.println("reset due to timeout ");
    connected = false;
    digitalWrite(LED, LOW);
    reset();
  }
  if(Serial.available() > 0)
  {
    
    
    // clear timeout
    connected = true;
    digitalWrite(LED, HIGH);
    lastComTime = millis();

    Serial.readBytesUntil('\n', serialData, 31);
    switch(serialData[0])
    {
    case 0: //basically the blueberry ping command
      Serial.println(0);
      break;
    case 'a':
      // use as a small and slow oscilloscope
      int pin;
      if(parseCommand(serialData, &pin, 1) && pin >= 0 && pin <= 7)
      {
        // stop loop by sending something to the robot
        while(!Serial.available() && connected)
        {
          Serial.println(analogRead(pin));
        }
      }
      else
      {
        Serial.println("Error while setting ADC pin");
      }
      break;
    case 's':
      // set left and right motor speeds
      int speed[2];
      if(parseCommand(serialData, speed, 2))
      {
        drive(speed[0], speed[1]);
        Serial.print("New speed set ");
        Serial.println(String(serialData));
      }
      else
      {
        Serial.print("Error while setting new speed. ");
        Serial.println(String(serialData));
      }
      break;
    case 'i':
      // inform about robot
      Serial.println("Zygote 1.0");
      break;
    case 'r':
      // quickly stop
      reset();
      Serial.println("Robot reset");
      break;
    default:
      // inform user of non existing command
      Serial.print("Command not recognised. ");
      Serial.println(String(serialData));
    }

    // clear serialData array
    memset(serialData, 0, sizeof(serialData));
  }
}

void reset()
{
  drive(0, 0);
}

/**
 * This function makes ints out of the received serial data, the 2 first
 * characters are not counted as they consist of the command character and
 * a comma separating the first variable.
 *
 * @params command The whole serial data received as an address
 * @params returnValues The array where the return values go as an address
 * @params returnNumber The number of values to set inside the returnValues variable
 */
boolean parseCommand(char* command, int* returnValues, byte returnNumber)
{
  // parsing state machine
  byte i = 1, j = 0, sign = 0, ch = 0, number;
  int temp = 0;
  while(i++)
  {
    switch(*(command + i))
    {
    case '\0':
    case ',':
      // set return value
      if(ch != 0)
      {
        returnValues[j++] = sign?-temp:temp;
        sign = 0;
        temp = 0;
        ch = 0;
      }
      else
      {
        return false;
      }
      break;
    case '-':
      sign = 1;
      break;
    default:
      // convert string to int
      number = *(command + i) - '0';
      if(number < 0 || number > 9)
      {
        return false;
      }
      temp = temp * 10 + number;
      ch++;
    }

    // enough return values have been set
    if(j == returnNumber)
    {
      return true;
    }
    // end of command reached
    else if(*(command + i) == '\0')
    {
      return false;
    }
  }
}

void drive(int left,int right){
  left = map(left, -100, 100, -maxDrive, maxDrive);
  right = map(right, -100, 100, -maxDrive, maxDrive);
  //String tmp = " ";
  //Serial.println(tmp+left1+);
  if (left>0){
    digitalWrite(left1,HIGH);
    analogWrite(left2,255-left);    
  } else if (left <= 0){
    digitalWrite(left1,LOW);
    analogWrite(left2,-left);
  }
  if (right>=0){
    digitalWrite(right1,LOW);
    analogWrite(right2,right);
  } else if (right < 0){
    digitalWrite(right1,HIGH);
    analogWrite(right2,255+right);
  }
  
}
