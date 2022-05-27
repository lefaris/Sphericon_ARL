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


 
void setup() {
  setUp = true;
  oscilationCounter = 0;
  pinMode(StepPin, OUTPUT);
  pinMode(DirPin, OUTPUT);
  Counter = (stopValueA / 2); //initilizes counter variable:

}

void loop() {
  delay(10000);
  while(1){
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
}

void moveAUpOne() { //moves the stepper motor up one counter
   digitalWrite(DirPin, HIGH);
   for(int x = 0; x < stepCounter; x++){
    digitalWrite(StepPin, HIGH);
    delayMicroseconds(stepDelay);
    digitalWrite(StepPin, LOW);
    delayMicroseconds(stepDelay);
  }
  Counter++;
}

void moveADownOne() { //moves the stepper motor up one counter
   digitalWrite(DirPin, LOW);
   for(int x = 0; x < stepCounter; x++){
    digitalWrite(StepPin, HIGH);
    delayMicroseconds(stepDelay);
    digitalWrite(StepPin, LOW);
    delayMicroseconds(stepDelay);
  }
  Counter--;
}
