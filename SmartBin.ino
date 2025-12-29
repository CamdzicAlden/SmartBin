#include <Servo.h>

Servo myServo;
int trigPin1 = 10, echoPin1 = 11, servoPin = 9, trigPin2 = 12, echoPin2 = 13, redLed = 2, greenLed = 3;
int distance, distance1;

void setup() {
  myServo.attach(servoPin); 
  myServo.write(0);
  delay(500);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
}


void loop() {
    
    distance = distanceCalculation(trigPin1, echoPin1);  //Distance caluclation for outer sensor
    distance1 = distanceCalculation(trigPin2, echoPin2);  //Distance caluclation for inner sensor
  

  if(distance < 10 && distance > 0 && distance1 > 15){ //Logic for opening the bin
    myServo.write(63);
    delay(4000);
    myServo.write(0);
    delay(500);
  }else{  //Logic for closing the bin
    myServo.write(0);
    delay(500);
  }

 //Logic for turning red led on when bin is full
  if(distance1 < 15 && distance1 > 0){
    digitalWrite(greenLed, LOW);
    digitalWrite(redLed, HIGH);
  }else{
    //Logic for turning green led on when bin is not full
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);
  }
}

int distanceCalculation(int trigger, int echo){
  	long duration;

  	digitalWrite(trigger, LOW); //Reseting trigger
  	delayMicroseconds(2);
  	digitalWrite(trigger, HIGH);  //10 microseconds pulse
    delayMicroseconds(10);
  	digitalWrite(trigger, LOW);
  
  	duration = pulseIn(echo, HIGH, 30000);  //Measuring duration in microseconds
  
  	return duration * 0.034 / 2;  // 0.034-cm/micSec  /2-Sound traveling both directions
}
