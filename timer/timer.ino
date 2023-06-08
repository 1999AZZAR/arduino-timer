#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Define button and buzzer pin constants
const int buttonAPin = 2;  // Replace with the appropriate pin number
const int buttonBPin = 3;  // Replace with the appropriate pin number
const int buttonCPin = 4;  // Replace with the appropriate pin number
const int buttonLPin = 5;  // Replace with the appropriate pin number
const int buzzerPin = 6;   // Replace with the appropriate pin number

// Define LCD constants
const int lcdColumns = 16;  // Number of LCD columns
const int lcdRows = 2;      // Number of LCD rows

// Define LCD I2C address
const int lcdAddress = 0x27;  // Replace with the actual I2C address of your LCD

// Create LCD object
LiquidCrystal_I2C lcd(lcdAddress, lcdColumns, lcdRows);

// Define state variables
enum State {
  READY,
  RUNNING,
  STOPPED
};

State currentState = READY;
unsigned long startTime = 0;
unsigned long lapTime = 0;
unsigned long fastestTime = 0;
int lapCount = 0;
bool isLButtonEnabled = false;
char fastestButton = ' ';

void setup() {
  // Initialize LCD
  lcd.begin(lcdColumns, lcdRows);
  lcd.setBacklight(LOW);
  lcd.print("Ready");

  // Initialize button pins
  pinMode(buttonAPin, INPUT_PULLUP);
  pinMode(buttonBPin, INPUT_PULLUP);
  pinMode(buttonCPin, INPUT_PULLUP);
  pinMode(buttonLPin, INPUT_PULLUP);

  // Initialize buzzer pin
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  // Handle button presses based on the current state
  switch (currentState) {
    case READY:
      handleReadyState();
      break;
    case RUNNING:
      handleRunningState();
      break;
    case STOPPED:
      handleStoppedState();
      break;
  }
}

void handleReadyState() {
  if (buttonPressed(buttonAPin) || buttonPressed(buttonBPin) || buttonPressed(buttonCPin)) {
    // A, B, or C button pressed
    if (isTimerRunning()) {
      if (isLButtonEnabled) {
        // L button enabled, return A, B, or C button as stop button
        stopTimer();
      } else {
        // L button disabled, return A, B, or C button as lap button
        lapTimer();
      }
    } else {
      // Timer not running, return A, B, or C button as start button
      startTimer();
    }
  }
}

void handleRunningState() {
  if (buttonPressed(buttonAPin) || buttonPressed(buttonBPin) || buttonPressed(buttonCPin)) {
    // A, B, or C button pressed
    if (isLButtonEnabled) {
      // L button enabled, return A, B, or C button as stop button
      stopTimer();
    } else {
      // L button disabled, return A, B, or C button as lap button
      lapTimer();
    }
  } else if (buttonPressed(buttonLPin)) {
    // L button pressed
    enableLButton();
  }
}

void handleStoppedState() {
  if (buttonPressed(buttonLPin)) {
    // L button pressed
    disableLButton();
    restartTimer();
  }
}

bool buttonPressed(int buttonPin) {
  static bool previousState = HIGH;
  bool currentState = digitalRead(buttonPin);

  if (previousState == HIGH && currentState == LOW) {
    delay(50);  // Debounce delay
    currentState = digitalRead(buttonPin);
    return currentState == LOW;
  }

  previousState = currentState;
  return false;
}

void startTimer() {
  lcd.clear();
  lcd.print("Running...");

  // Set the current state to RUNNING
  currentState = RUNNING;

  // Store the start time
  startTime = millis();

  // Store the fastest button as the first button pressed
  fastestTime = 0;
  lapCount = 0;
  fastestButton = ' ';

  // Sound the buzzer
  soundBuzzer();
}

void lapTimer() {
  if (lapCount == 0) {
    lcd.clear();
    lcd.print("Last Lap");
    lcd.setCursor(0, 1);
    lcd.print("00:00:00.000");
    delay(1000);
    lcd.clear();
    lcd.print("Running...");
  }

  // Calculate the lap time
  unsigned long currentTime = millis();
  lapTime = currentTime - startTime;

  // Update the fastest time and button if necessary
  if (lapTime < fastestTime || fastestTime == 0) {
    fastestTime = lapTime;
    fastestButton = ' ';
    if (buttonPressed(buttonAPin)) {
      fastestButton = 'A';
    } else if (buttonPressed(buttonBPin)) {
      fastestButton = 'B';
    } else if (buttonPressed(buttonCPin)) {
      fastestButton = 'C';
    }
  }

  // Increment lap count
  lapCount++;

  // Sound the buzzer
  soundBuzzer();

  // Reset the lap start time
  startTime = currentTime;
}

void stopTimer() {
  // Calculate the total time
  unsigned long currentTime = millis();
  unsigned long totalTime = currentTime - startTime;

  // Display the results on the LCD
  lcd.clear();
  lcd.print("Fastest: ");
  lcd.print(fastestButton);
  lcd.print(", Laps: ");
  lcd.print(lapCount);
  lcd.setCursor(0, 1);
  printTime(totalTime);

  // Set the current state to STOPPED
  currentState = STOPPED;
}

void restartTimer() {
  lcd.clear();
  lcd.print("Ready");

  // Reset all variables
  startTime = 0;
  lapTime = 0;
  fastestTime = 0;
  lapCount = 0;
  fastestButton = ' ';

  // Set the current state to READY
  currentState = READY;
}

void enableLButton() {
  isLButtonEnabled = true;
  lcd.clear();
  lcd.print("Last Lap");
}

void disableLButton() {
  isLButtonEnabled = false;
}

bool isTimerRunning() {
  return currentState == RUNNING;
}

void soundBuzzer() {
  // Sound the buzzer
  digitalWrite(buzzerPin, HIGH);
  delay(100);
  digitalWrite(buzzerPin, LOW);
}

void printTime(unsigned long time) {
  unsigned long hours = time / 3600000;
  time %= 3600000;
  unsigned long minutes = time / 60000;
  time %= 60000;
  unsigned long seconds = time / 1000;
  unsigned long milliseconds = time % 1000;

  if (hours < 10) lcd.print('0');
  lcd.print(hours);
  lcd.print(':');
  if (minutes < 10) lcd.print('0');
  lcd.print(minutes);
  lcd.print(':');
  if (seconds < 10) lcd.print('0');
  lcd.print(seconds);
  lcd.print('.');
  if (milliseconds < 100) lcd.print('0');
  if (milliseconds < 10) lcd.print('0');
  lcd.print(milliseconds);
}
