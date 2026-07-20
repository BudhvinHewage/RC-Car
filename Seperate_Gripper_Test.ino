//including the libraries
#include <SoftwareSerial.h> // TX RX software library for bluetooth
#include <AFMotor.h>
#include <Servo.h>


Servo myservo;



//Initializing pins for bluetooth Module
int bluetoothTx = 2; // bluetooth tx to 2 pin
int bluetoothRx = 3; // bluetooth rx to 3 pin
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);
//Servo myservo;

char command; //variable to store the data
int velocity = 0; // Variable to control the speed of motor
long duration; // vairable for the duration of sound wave travel
int length_check; // variable to store the data returned by the ultrasonic sensor
int distance; // variable for the distance measurement

// defines variables
//#define echoPin 13 // attach pin D2 Arduino to pin Echo of HC-SR04
//#define trigPin 12 // attach pin D3 Arduino to pin Trig of HC-SR04

AF_DCMotor Right_Motor(2, MOTOR12_64KHZ);// RIGHT side motor of BEETLE MK-1 is connected to shield pin set 1
AF_DCMotor Left_Motor(1, MOTOR12_64KHZ); // LEFT side motor of BEETLE MK-1 is connected to shield pin set 2

void setup() 
{       
  //Set the baud rate of serial communication and bluetooth module at same rate.
  Serial.begin(9600); 
  bluetooth.begin(9600);
  Right_Motor.setSpeed(250);     
  Left_Motor.setSpeed(250);
  //myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  pinMode (10,OUTPUT);
  pinMode (11,OUTPUT);
    myservo.attach(9);  // attaches the servo on pin 9 to the servo object

}


void loop()
{  
  if(bluetooth.available() > 0)  //Checking if there is some data available or not
  {
    command = bluetooth.read();   //Storing the data in the 'command' variable
    Serial.println(command);
    while (command == 'F')
    {   Right_Motor.run(FORWARD);      // motor goes forward
    Left_Motor.run(BACKWARD);
    break;
    }
    while (command == 'B')
    {
         Right_Motor.run(BACKWARD);     // motor goes backwards
    Left_Motor.run(FORWARD);
    break;
    }
    while (command == 'S')
    {
     Right_Motor.run(RELEASE);     // motor goes backwards
    Left_Motor.run(RELEASE);
    break;
      }
    while (command == 'L')
    {
         Right_Motor.run(FORWARD);     // motor goes LEFT
   Left_Motor.run(FORWARD);
   break;
    }
    while (command == 'R')
    {
         Right_Motor.run(BACKWARD);     // motor goes RIGHT
   Left_Motor.run(BACKWARD);
   break;
    }
   if (command == 'X')
   {
      myservo.write(90);
      delay (3000);
   }

      else if (command == 'x')
      {
      myservo.write(41);
      delay (3000);
    
      }   
    }
}


     
