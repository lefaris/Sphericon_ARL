//Global Constants
//const int ledPin = 2;
const int StepPin = 3;
const int DirPin = 2;
const int stepDelay = 300; // Delay (microseconds) of the motor between steps.
const int stepCounter = 50; // # of time the move commands loop 
int stopValueA = 30; // sets max value of stepper motor, min is set to 0.
int oscilationCounter;
bool setUp;

int Counter; // global variables


#include <ArduinoBLE.h> 
#include <Arduino_LSM6DS3.h> 
#include <Arduino.h>

BLEService TenseRoboA("0fcf5793-df75-475c-be63-62affc3fbbf9"); //UUID for turning a LED on
BLEByteCharacteristic MotorPosition("bbf8", BLERead | BLENotify); //UUID for monitering
BLEByteCharacteristic MotorControl("bbf7", BLERead | BLENotify | BLEWrite); //UUID for Writing to A
BLEBoolCharacteristic OscStatus("bbf9", BLERead | BLENotify | BLEWrite); //UUID for Writing to A


 
void setup() {
  setUp = true;
  oscilationCounter = 0;
  pinMode(StepPin, OUTPUT);
  pinMode(DirPin, OUTPUT);
  Counter = (stopValueA / 2); //initilizes counter variable:
  if (!BLE.begin()) {
    while (1); //stop program becuase it won't work
  } //notifies via //Serial if BLE is not working
  
  BLE.setLocalName("TensegrityRobotA"); //sets name for device
  BLE.setAdvertisedService(TenseRoboA);
  TenseRoboA.addCharacteristic(MotorPosition); //adds  to controlLed
  TenseRoboA.addCharacteristic(MotorControl); //adds  to controlLed
  TenseRoboA.addCharacteristic(OscStatus); //adds  to controlLed

  BLE.addService(TenseRoboA); //adds  to TensegrityRobot
  MotorPosition.writeValue(Counter); //Sets initial value to counter
  MotorControl.writeValue(0); //Sets initial value (0 = off)
  OscStatus.writeValue(0); //Sets initial value to false
  BLE.advertise(); //advertises TenseRoboA 

  digitalWrite(DirPin, HIGH);
  digitalWrite(StepPin, HIGH);

}

void loop() {
}

void moveAUpOne() { //moves the stepper motor up one counter
   digitalWrite(DirPin, HIGH);
   digitalWrite(LED_BUILTIN, HIGH);
   for(int x = 0; x < stepCounter; x++){
    digitalWrite(StepPin, HIGH);
    delayMicroseconds(stepDelay);
    digitalWrite(StepPin, LOW);
    delayMicroseconds(stepDelay);
  }
  digitalWrite(LED_BUILTIN, LOW);
  Counter++;
}

void moveADownOne() { //moves the stepper motor up one counter
   digitalWrite(DirPin, LOW);
   digitalWrite(LED_BUILTIN, HIGH);
   for(int x = 0; x < stepCounter; x++){
    digitalWrite(StepPin, HIGH);
    delayMicroseconds(stepDelay);
    digitalWrite(StepPin, LOW);
    delayMicroseconds(stepDelay);
  }
  digitalWrite(LED_BUILTIN, LOW);
  Counter--;
}
