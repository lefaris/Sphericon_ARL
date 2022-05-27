//Lower bound is: 00 in hex or 0 in decimal
//Upper bound is: 1E in hex or 30 in decimal
//Total length is: 1E

#define stepPinA 3
#define dirPinA 2
#define stepDelay 500 // Delay (microseconds) of the motor between steps.
#define stepCounter 50 // # of time the move commands loop 
int stopValueA = 30; // sets max value of stepper motor, min is set to 0.
int oscilationCounter;
int motorAControl;
int counterA; // global variables

int stepCount = 0;         // number of steps the motor has taken

void setup() {
  oscilationCounter = 0;

  pinMode(stepPinA, OUTPUT);
  pinMode(dirPinA, OUTPUT);
  counterA = (stopValueA / 2); //initilizes counter variable: sets to 500 becuase that is the middle of the spectrum
  motorAControl = 53; //Sets initial value (0 = off)
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH); // turns built in LED on

  if (motorAControl == 0) {
    int oscilationCounter = 0; //resets counter
  }

  if (motorAControl != 0) {
        //Oscilate motor A once
        if (motorAControl == 53 ) { //Hex Value 35
          if (counterA == stopValueA) {
            oscilationCounter = 1;
          }
          else if (counterA == 0){
           oscilationCounter = 0;
          }
          
          if ((counterA < stopValueA) && (oscilationCounter == 0)) {
            while ( counterA < stopValueA ) {
              moveAUpOne(); 
            }
            delay(3000);
            while (counterA > 0){
              moveADownOne();
            }
            delay(3000);
          }
          else if ((counterA > 0)&&(oscilationCounter == 1)) {
            while(counterA > 0){
              moveADownOne();
            }
            delay(3000);
            while (counterA < stopValueA) {
              moveAUpOne(); 
            }
            delay(3000);
          }
        }

        //oscilate motor A until another command is input. 
        else {
          motorAControl = 0;
        }
       }//End of motor A's Loop
}


void moveAUpOne() { //moves the stepper motor up one counter
   digitalWrite(dirPinA, HIGH);
   digitalWrite(LED_BUILTIN, HIGH);
   for(int x = 0; x < stepCounter; x++){
    digitalWrite(stepPinA, HIGH);
    delayMicroseconds(stepDelay);
    digitalWrite(stepPinA, LOW);
    delayMicroseconds(stepDelay);
  }
  digitalWrite(LED_BUILTIN, LOW);
  counterA++;
}

void moveADownOne() { //moves the stepper motor up one counter
   digitalWrite(dirPinA, LOW);
   digitalWrite(LED_BUILTIN, HIGH);
   for(int x = 0; x < stepCounter; x++){
    digitalWrite(stepPinA, HIGH);
    delayMicroseconds(stepDelay);
    digitalWrite(stepPinA, LOW);
    delayMicroseconds(stepDelay);
  }
  digitalWrite(LED_BUILTIN, LOW);
  counterA--;
}
