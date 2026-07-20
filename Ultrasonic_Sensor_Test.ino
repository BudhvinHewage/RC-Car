//including the libraries
#include <SoftwareSerial.h> // TX RX software library for bluetooth
#include <AFMotor.h>
//#include <Servo.h>



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
#define echoPin 13 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 12 // attach pin D3 Arduino to pin Trig of HC-SR04

AF_DCMotor Right_Motor(1, MOTOR12_64KHZ);// RIGHT side motor of BEETLE MK-1 is connected to shield pin set 1
AF_DCMotor Left_Motor(2, MOTOR12_64KHZ); // LEFT side motor of BEETLE MK-1 is connected to shield pin set 2

void setup() 
{       
  //Set the baud rate of serial communication and bluetooth module at same rate.
  Serial.begin(9600); 
  bluetooth.begin(9600);
  Right_Motor.setSpeed(velocity);     
  Left_Motor.setSpeed(velocity);
  //myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  pinMode (10,OUTPUT);
  pinMode (11,OUTPUT);
}


void loop()
{  
  if(bluetooth.available() > 0)  //Checking if there is some data available or not
  {
    length_check = ultrasonic_sensor();  
    command = bluetooth.read();   //Storing the data in the 'command' variable
    while (length_check > 30)
    {
      length_check = ultrasonic_sensor();
      switch(instruction)
      {
        case 'F':
        Right_Motor.run(FORWARD);      // motor goes forward
        Left_Motor.run(BACKWARD);
        digitalWrite(10,HIGH);
        digitalWrite(11,LOW);
        break;
    
        case 'B':
        Right_Motor.run(BACKWARD);     // motor goes backwards
        Left_Motor.run(FORWARD);
        digitalWrite(10,LOW);
        digitalWrite(11,HIGH);
        break;
    
        case 'L':
        Right_Motor.run(FORWARD);     // motor goes LEFT
        Left_Motor.run(FORWARD);
        break;
    
        case 'R':
        Right_Motor.run(BACKWARD);     // motor goes RIGHT
        Left_Motor.run(BACKWARD);
        break;
    
        case 'S':
        Right_Motor.run(RELEASE);      // all motors stopped
        Left_Motor.run(RELEASE);
        digitalWrite(10,LOW);
        digitalWrite(11,LOW);
        break;
        
        default:
        if (instruction == 'q')
        {
          digitalWrite(7, HIGH);  
          velocity = 255;
          Right_Motor.setSpeed(velocity);     
          Left_Motor.setSpeed(velocity);   
        }
        else
        {
          if ((instruction >= 48) && (instruction <= 57))
          {
            velocity = (instruction - 48)*25;
            Right_Motor.setSpeed(velocity);     
            Left_Motor.setSpeed(velocity);
          }
        }   
      }
    }
    while (length_check <= 30)
    {
      length_check = ultrasonic_sensor();
      if (command == 'B')
      {
        Right_Motor.run(BACKWARD);     
        Left_Motor.run(FORWARD);
        digitalWrite(10,LOW);
        digitalWrite(11,HIGH);
        break;
      }
    }
  }
}

int ultrasonic_sensor ()
{
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  return distance;    
}
     
