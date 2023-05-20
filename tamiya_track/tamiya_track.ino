#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Constants
const int START_FINISH_PIN_A = 2; // Light sensor pin for track A start/finish line
const int START_FINISH_PIN_B = 3; // Light sensor pin for track B start/finish line
const int START_FINISH_PIN_C = 4; // Light sensor pin for track C start/finish line
const int RESET_STOP_BUTTON_PIN = 5; // Reset/Stop button pin
const int LAST_LAP_BUTTON_PIN = 6; // Last Lap button pin
const int BUZZER_PIN = 7; // Buzzer pin

// Variables
volatile unsigned long lapTimesA = 0; // Lap times for track A
volatile unsigned long lapTimesB = 0; // Lap times for track B
volatile unsigned long lapTimesC = 0; // Lap times for track C
volatile unsigned long lastCrossingTime = 0; // Time of the last tamiya (model car) crossing
volatile bool lastLapTriggered = false; // Flag to track if the last lap button has been triggered

volatile unsigned long lapCountA = 0;
volatile unsigned long lapCountB = 0;
volatile unsigned long lapCountC = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2); // Initialize LCD object with I2C address 0x27

void setup() {
  pinMode(START_FINISH_PIN_A, INPUT);
  pinMode(START_FINISH_PIN_B, INPUT);
  pinMode(START_FINISH_PIN_C, INPUT);
  pinMode(RESET_STOP_BUTTON_PIN, INPUT_PULLUP);
  pinMode(LAST_LAP_BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);

  // Initialize LCD
  lcd.begin(16, 2);
  lcd.backlight();

  // Play Super Mario card start tone
  playTone(300, 200);
  delay(250);
  playTone(600, 200);
  delay(250);
  playTone(1200, 200);

  // Attach interrupt handlers
  attachInterrupts();
}

void loop() {
  // Check if the last lap button is triggered
  if (digitalRead(LAST_LAP_BUTTON_PIN) == LOW) {
    lastLapTriggered = true;
    delay(50); // Debounce delay
  }

  // Check if the reset/stop button is triggered
  if (digitalRead(RESET_STOP_BUTTON_PIN) == LOW) {
    resetCounter();
    delay(50); // Debounce delay
  }

  // Calculate fastest time
  unsigned long fastestTime = min(min(lapTimesA, lapTimesB), lapTimesC);

  // Display winner and statistics on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  if (fastestTime == lapTimesA) {
    lcd.print("Winner: Track A");
    lcd.setCursor(0, 1);
    lcd.print("Avg: ");
    lcd.print(lapTimesA / lapCountA);
    lcd.print("ms  Total: ");
    lcd.print(lapTimesA);
    lcd.print("ms  ");
  } else if (fastestTime == lapTimesB) {
    lcd.print("Winner: Track B");
    lcd.setCursor(0, 1);
    lcd.print("Avg: ");
    lcd.print(lapTimesB / lapCountB);
    lcd.print("ms  Total: ");
    lcd.print(lapTimesB);
    lcd.print("ms  ");
  } else if (fastestTime == lapTimesC) {
    lcd.print("Winner: Track C");
    lcd.setCursor(0, 1);
    lcd.print("Avg:");
    lcd.print(lapTimesC / lapCountC);
    lcd.print("ms Total: ");
    lcd.print(lapTimesC);
    lcd.print("ms ");
  }

  // Play buzzer tones
  if (fastestTime > 0) {
    playTone(400, 200);
    delay(200);
    playTone(400, 200);
  }

  // Reset last lap triggered flag
  lastLapTriggered = false;
}

void playTone(int frequency, int duration) {
  tone(BUZZER_PIN, frequency, duration);
  delay(duration);
  noTone(BUZZER_PIN);
}

void resetCounter() {
  lapTimesA = 0;
  lapTimesB = 0;
  lapTimesC = 0;
  lapCountA = 0;
  lapCountB = 0;
  lapCountC = 0;
  lastCrossingTime = 0;
}

void trackACrossing() {
  unsigned long currentTime = millis();
  if (currentTime - lastCrossingTime > 100 && !lastLapTriggered) {
    lapTimesA += currentTime - lastCrossingTime;
    lapCountA++;
    lastCrossingTime = currentTime;
    playTone(400, 100);
  }
}

void trackBCrossing() {
  unsigned long currentTime = millis();
  if (currentTime - lastCrossingTime > 100 && !lastLapTriggered) {
    lapTimesB += currentTime - lastCrossingTime;
    lapCountB++;
    lastCrossingTime = currentTime;
    playTone(400, 100);
  }
}

void trackCCrossing() {
  unsigned long currentTime = millis();
  if (currentTime - lastCrossingTime > 100 && !lastLapTriggered) {
    lapTimesC += currentTime - lastCrossingTime;
    lapCountC++;
    lastCrossingTime = currentTime;
    playTone(400, 100);
  }
}

void attachInterrupts() {
  attachInterrupt(digitalPinToInterrupt(START_FINISH_PIN_A), trackACrossing, FALLING);
  attachInterrupt(digitalPinToInterrupt(START_FINISH_PIN_B), trackBCrossing, FALLING);
  attachInterrupt(digitalPinToInterrupt(START_FINISH_PIN_C), trackCCrossing, FALLING);
}
