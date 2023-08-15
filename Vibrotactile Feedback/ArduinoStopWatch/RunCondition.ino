// constants won't change. They're used here to set pin numbers:
const int buttonPin = 2;  // the number of the pushbutton pin
// const int FINISHEDbuttonPin = 3;
const int ledPin = 13;    // the number of the LED pin
const int NumOfEvents = 12; // how many times do we buzz the participants
const int motorPin = 3;
const int motorPin2 = 4;
const int motorPin3 = 5;
const int motorPin4 = 6;

// variables will change:
int buttonState = 0;  // variable for reading the pushbutton status
int FINISHEDbuttonState = 0;
float Time = 0;
float currentStopwatch = 0;
float StopTimesArray[NumOfEvents];
int MotorPWMArray[NumOfEvents] = {60, 99, 138, 177, 216, 255, 60, 99, 138, 177, 216, 255};
bool shuffled = false;
int timesStopped = 0;
int StartClock = random(17,25);


void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  pinMode(motorPin, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  Serial.begin(9600);
  delay(1000);
  Serial.println("*** NEW TRIAL ***");
}

void loop() {
  randomSeed(analogRead(A0)); // Analog read on an unsused analog pin gives the random floating voltage noise on that pin. 
  // Fill the motor intensities list in a random order
  if (shuffled == false) {
    shuffled = true;
    for (int i=0; i < NumOfEvents; i++) {

    int r = random(i, NumOfEvents);
    int temp = MotorPWMArray[i];
    MotorPWMArray[i] = MotorPWMArray[r];
    MotorPWMArray[r] = temp;
    Serial.println(MotorPWMArray[i]);
  }

  }

  // check time and button state
  Time = float(millis())/float(1000);
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // Conditions to Stop the loop
  // STOPSTOPSTOPSTOP

  if (timesStopped == NumOfEvents) {
    Serial.println("***ReactionTimes***");
    
    // Iterate over the StopTimesArray to print the recorded reaction times
    for (int i = 0; i < NumOfEvents; i++) {
      if (StopTimesArray[i] == 100.0) {
        Serial.print("Signal Missed");  // Print "Signal Missed" if the reaction time is 100.0
        Serial.print(", ");
        // Serial.print("  , Intensity (% PWM) = ");
        Serial.print((MotorPWMArray[i]*100)/255);
        Serial.print(", ");
        Serial.println(MotorPWMArray[i]);
      } else {
        // Serial.print("Time (s) =  ");
        Serial.print(StopTimesArray[i]);  // Print the recorded reaction time
        Serial.print(", ");
        // Serial.print("  , Intensity (% PWM) = ");
        Serial.print((MotorPWMArray[i]*100)/255);
        Serial.print(", ");
        Serial.println(MotorPWMArray[i]);
      }
    } 
    timesStopped += 1;  // Increment the timesStopped variable by 1
}

  else if (timesStopped > NumOfEvents){
    return;
  }
  // STOPSTOPSTOPSTOP


  // Condition to wait until reaching the start time
  else if (Time < StartClock){ // should work on the grounds that time list increases in order.
  // turn the stopwatch on to indicate to the user that they should react

  digitalWrite(ledPin, LOW);
  return;
  }
  // Once start time is reached
  else{
  digitalWrite(ledPin, HIGH);
  vibrate(Time, StartClock, motorPin, MotorPWMArray[timesStopped]);
  vibrate(Time, StartClock, motorPin2, MotorPWMArray[timesStopped]);
  vibrate(Time, StartClock, motorPin3, MotorPWMArray[timesStopped]);
  vibrate(Time, StartClock, motorPin4, MotorPWMArray[timesStopped]);

if (buttonState == HIGH) {
  // turn LED on:
  digitalWrite(ledPin, LOW);
  
  float pressTime = currentStopwatch;  // Store the current stopwatch value as the press time
  StopTimesArray[timesStopped] = pressTime;  // Store the press time in the StopTimesArray
  
  StartClock = StartClock + random(15,20);  // Adjust the StartClock for the next event

  timesStopped += 1;  // Increment the timesStopped variable by 1
  
  digitalWrite(motorPin, LOW);  // Turn off the motors
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW); 
  digitalWrite(motorPin4, LOW);
  
  // Now wait for serial input while the participant provides a pleasantness rating.
  Serial.read(); // set available back to zero
  // Serial.println(Serial.available());
  Serial.println("Waiting For input");
  while(Serial.available() == 0) { // once enter is pressed, this condition will no longer be satisfied.
    
    }
  Serial.println("Input received.");
  Serial.read(); // set available back to zero
  // Serial.println(Serial.available());
  return;  // Exit the function
}

// If they take longer than 3 seconds, mark the signal as missed.
else if (currentStopwatch > 3.0) {
  digitalWrite(ledPin, LOW);  // Turn off the LED.
  Serial.println("***************** Signal Missed ****************"); 
  StopTimesArray[timesStopped] = 100.0;  // Mark the signal as missed by assigning 100.0 to the corresponding index in StopTimesArray.
  
  StartClock = StartClock + random(15,20);  // Adjust the StartClock for the next event.
  
  timesStopped += 1;  // Increment the timesStopped variable by 1.
  
  digitalWrite(motorPin, LOW);  // Turn off the motors
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW); 
  digitalWrite(motorPin4, LOW);

  currentStopwatch = 0.0;  // Reset currentStopwatch to 0.0 to avoid immediate triggering of this condition on subsequent buzzes.
  
  return;  // Exit the function.
}

    else {
    // turn LED off:
    currentStopwatch = float(millis())/float(1000) - StartClock;
    // Serial.println(currentStopwatch);
    }
    }
  }






// I am using motors 1,2,3,4
// Function to control the vibration of the motor
void vibrate(float time, float startingTime, int motor, int pwm) {
  float vibrateUntil = startingTime + 0.5;  // Calculate the time until which the motor should vibrate (0.5 seconds)
  
  if (Time < vibrateUntil) {
    analogWrite(motor, pwm);  // Turn on the motor vibration
  } else {
    digitalWrite(motor, LOW);   // Turn off the motor vibration
    }
  }


