// including the libraries
#include <SoftwareSerial.h> // TX RX software library for bluetooth
#include <AFMotor.h>
#include <Servo.h>
#include <NewPing.h>

// defines variables
#define bluetoothTx 2
#define bluetoothRx 3
#define echoPin A3
#define trigPin A4
#define MAX_DISTANCE 10

AF_DCMotor Right_Motor(2, MOTOR12_64KHZ);
AF_DCMotor Left_Motor(1, MOTOR12_64KHZ);
NewPing sonar(trigPin, echoPin, MAX_DISTANCE);
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);
Servo myservo;

char command; // variable to store the data
int velocity = 0; // Variable to control the speed of motor

void setup()
{
  // Set the baud rate of serial communication and bluetooth module at same rate.
  Serial.begin(9600);
  bluetooth.begin(9600);
  Right_Motor.setSpeed(250);
  Left_Motor.setSpeed(250);
  // myservo.attach(9); // attaches the servo on pin 9 to the servo object
  pinMode(A0, OUTPUT);
  pinMode(A2, OUTPUT);
  myservo.attach(9); // attaches the servo on pin 9 to the servo object
}

void loop()
{
  if (bluetooth.available() > 0) // Checking if there is some data available or not
  {
    command = bluetooth.read(); // Storing the data in the 'command' variable

    while (command == 'F')
    {
      int distance = sonar.ping_cm();

      if (distance <= 10)
      {
        Right_Motor.run(BACKWARD);
        Left_Motor.run(FORWARD);
        digitalWrite(A0, HIGH);
        digitalWrite(A2, LOW);
      }
      else if (distance <= 10 && distance > 0)
      {
        Right_Motor.run(RELEASE);
        Left_Motor.run(RELEASE);
      }
      break;
    }

    while (command == 'B')
    {
      Right_Motor.run(FORWARD); // motor goes forward
      Left_Motor.run(BACKWARD);

      digitalWrite(A0, LOW);
      digitalWrite(A2, HIGH);
      break;
    }

    while (command == 'S')
    {
      Right_Motor.run(RELEASE); // motor goes backwards
      Left_Motor.run(RELEASE);
      digitalWrite(A0, LOW);
      digitalWrite(A2, LOW);
      break;
    }

    while (command == 'L')
    {
      Right_Motor.run(FORWARD); // motor goes LEFT
      Left_Motor.run(FORWARD);
      break;
    }

    while (command == 'R')
    {
      Right_Motor.run(BACKWARD); // motor goes RIGHT
      Left_Motor.run(BACKWARD);
      break;
    }

    if (command == 'X')
    {
      myservo.write(90);
      delay(1000);
    }
    else if (command == 'x')
    {
      myservo.write(39);
      delay(1000);
    }
    else if (command == 'V')
    {
      velocity = 250;
      Right_Motor.setSpeed(velocity);
      Left_Motor.setSpeed(velocity);
    }
    else if (command == 'v')
    {
      velocity = 125;
      Right_Motor.setSpeed(velocity);
      Left_Motor.setSpeed(velocity);
    }
  }
}