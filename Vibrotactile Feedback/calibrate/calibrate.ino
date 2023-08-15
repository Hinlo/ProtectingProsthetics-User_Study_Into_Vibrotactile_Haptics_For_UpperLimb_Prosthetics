// constants won't change. They're used here to set pin numbers:

// const int FINISHEDbuttonPin = 3;
const int ledPin = 13;    // the number of the LED pin
const int NumOfEvents = 18; // how many times do we buzz the participants
const int motorPin = 3;
const int motorPin2 = 4;
const int motorPin3 = 5;
const int motorPin4 = 6;
int fsrPin = 0;     // the FSR and 10K pulldown are connected to a0

// variables will change:
int fsrReading;     // the analog reading from the FSR resistor divider
int FINISHEDbuttonState = 0;
float Time = 0;
float currentStopwatch = 0;
float StopTimesArray[NumOfEvents];
int MotorPWMArray[NumOfEvents] = {60, 99, 138, 177, 216, 255, 60, 99, 138, 177, 216, 255, 60, 99, 138, 177, 216, 255};
bool shuffled = false;
int timesStopped = 0;
int StartClock = random(17,25);

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(motorPin, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  Serial.begin(9600);
  delay(1000);
  Serial.println("*** NEW TRIAL ***");
}

void loop() {
while(Serial.available() == 0) { // once enter is pressed, this condition will no longer be satisfied.
  fsrReading = analogRead(fsrPin);  
 
  Serial.print("Analog reading = ");
  Serial.print(fsrReading);     // print the raw analog reading
 
  if (fsrReading < 30) {
    Serial.println(" - No pressure");
  } else if (fsrReading < 500) {
    Serial.println(" - Too Loose");
  } else if (fsrReading < 800) {
    Serial.println(" - Correct Tightness Range");
  } else {
    Serial.println(" - Too Tight");
  }

  }

    if (timesStopped < NumOfEvents) {
    vibrate(Time, StartClock, motorPin, MotorPWMArray[timesStopped]);
    vibrate(Time, StartClock, motorPin2, MotorPWMArray[timesStopped]);
    vibrate(Time, StartClock, motorPin3, MotorPWMArray[timesStopped]);
    vibrate(Time, StartClock, motorPin4, MotorPWMArray[timesStopped]);
    timesStopped+=1;
    Serial.println(timesStopped);
    delay(1000);
    digitalWrite(motorPin,LOW);
    digitalWrite(motorPin2,LOW);
    digitalWrite(motorPin3,LOW);
    digitalWrite(motorPin4,LOW);
    delay(1000);
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


