//Global Constants
//const int ledPin = 2;
const int StepPin = 3;
const int DirPin = 2;
const int stepDelay = 500; // Delay (microseconds) of the motor between steps.
const int stepCounter = 50; // # of time the move commands loop 
int stopValueA = 30; // sets max value of stepper motor, min is set to 0.
int oscilationCounter;
bool setUp;

int Counter; // global variables


#include <ArduinoBLE.h> 
#include <Arduino_LSM6DS3.h> 
#include <Arduino.h>

BLEService TenseRoboB("0fcf5793-df75-475c-be63-62affc3faaf9"); //UUID for turning a LED on
BLEByteCharacteristic MotorPosition("aaf8", BLERead | BLENotify); //UUID for monitering
BLEByteCharacteristic MotorControl("aaf7", BLERead | BLENotify | BLEWrite); //UUID for Writing to A
BLEBoolCharacteristic OscStatus("aaf9", BLERead | BLENotify | BLEWrite); //UUID for Writing to A


 
void setup() {
  setUp = true;
  oscilationCounter = 0;
  pinMode(StepPin, OUTPUT);
  pinMode(DirPin, OUTPUT);
  Counter = (stopValueA / 2); //initilizes counter variable:
  if (!BLE.begin()) {
    while (1); //stop program becuase it won't work
  } //notifies via //Serial if BLE is not working
  
  BLE.setLocalName("TensegrityRobotB"); //sets name for device
  BLE.setAdvertisedService(TenseRoboB);
  TenseRoboB.addCharacteristic(MotorPosition); //adds  to controlLed
  TenseRoboB.addCharacteristic(MotorControl); //adds  to controlLed
  TenseRoboB.addCharacteristic(OscStatus); //adds  to controlLed

  BLE.addService(TenseRoboB); //adds  to TensegrityRobot
  MotorPosition.writeValue(Counter); //Sets initial value to counter
  MotorControl.writeValue(0); //Sets initial value (0 = off)
  OscStatus.writeValue(0); //Sets initial value to false
  BLE.advertise(); //advertises TenseRoboB 

}

void loop() {
BLEDevice central = BLE.central(); //Sets a boolean "central" to notify if connection has occured
//setup loop, set bounds with BLE main
  if (central) { // central = device connected
    digitalWrite(LED_BUILTIN, HIGH); // turns built in LED on    
    while(central.connected()) {
      //This if tree tells the motor what to do
      if (MotorControl.value() == 0) {
        int oscilationCounter = 0;//resets the counter after a different command is executed
      }
      if (MotorControl.value() != 0) {
        //default and debug statuses
        if(MotorControl.value() == 1) { //default response
          MotorControl.writeValue(0);
        }else if (MotorControl.value() == 2) { //counter has reached stopValue
          MotorControl.writeValue(0);
        }else if (MotorControl.value() == 3) { //counter has reached 0
          MotorControl.writeValue(0);
        }
        
        //these cases move counter up
        else if (MotorControl.value() == 16 ) { //Hex Value 10
          if (Counter < stopValueA) {
            moveAUpOne();
          } else {
            MotorControl.writeValue(2);
          }
        }else if (MotorControl.value() == 17 ) { //Hex Value 11
          if (Counter < stopValueA) {
            moveAUpOne();
            MotorControl.writeValue(1);
          } else {
            MotorControl.writeValue(2);
          }
        }else if (MotorControl.value() == 21 ) { //Hex Value 15
          if (Counter < stopValueA) {
            for (int i = 0; i<5; i++) { 
              moveAUpOne();
            }
            MotorControl.writeValue(1);
          } else {
            MotorControl.writeValue(2);
          }
        }
        
        //these cases move counter down
        else if (MotorControl.value() == 32 ) { //Hex Value 20
          if (Counter > 0) {
            moveADownOne();
          } else {
            MotorControl.writeValue(3);
          }
        }else if (MotorControl.value() == 33 ) { //Hex Value 21
          if (Counter > 0) {
            moveADownOne();
            MotorControl.writeValue(1);
          } else {
            MotorControl.writeValue(3);
          }
        }else if (MotorControl.value() == 37 ) { //Hex Value 25
          if (Counter > 0) {
            for (int i = 0; i<5; i++) { 
              moveADownOne();
            }
            MotorControl.writeValue(1);
          } else {
            MotorControl.writeValue(3);
          }
        }
        //
        else if(MotorControl.value() == 49 ){ //Hex Value 31
          Counter = 0; 
        }
        //This case sets the maximum value of counter to be what the counter currently is. This is the other endpoint
        else if(MotorControl.value() == 50 ){ //Hex Value 32
          stopValueA = Counter;
        }
        //Resets the counter to the middle value if messed up
        else if(MotorControl.value() == 51 ){ //Hex Value 33
          Counter = (stopValueA /2); 
        }
        //This case sets the maximum value of counter to 1000, serves as reset of Hex value 32.
        else if(MotorControl.value() == 52 ){ //Hex Value 34
          stopValueA = 1000;
        }

        else if(MotorControl.value() == 53 ){ //Hex Value 35
          if (Counter == stopValueA) {
          oscilationCounter = 1;
          }
          else if (Counter == 0){
           oscilationCounter = 0;
          }
          if ((Counter < stopValueA) && (oscilationCounter == 0)) {
            while ( Counter < stopValueA ) {
              moveAUpOne(); 
            }
            delay(3000);
            while (Counter > 0){
              moveADownOne();
            }
            delay(3000);
          }
          else if ((Counter > 0)&&(oscilationCounter == 1)) {
            while(Counter > 0){
              moveADownOne();
            }
            delay(3000);
            while (Counter < stopValueA) {
              moveAUpOne(); 
            }
            delay(3000);
          }
        }
        else {
          //Serial.print("Written Value of ");
          //Serial.print(MotorControl.value());
          //Serial.println(" does not match any commands, try another value."); 
          MotorControl.writeValue(0);
        }
      }
    }
  }

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
