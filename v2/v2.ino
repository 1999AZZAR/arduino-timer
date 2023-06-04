// Library yang diperlukan
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Inisialisasi pin dan sensor cahaya
const int sensorPin1 = A0;  // Pin analog untuk sensor cahaya jalur 1
const int sensorPin2 = A1;  // Pin analog untuk sensor cahaya jalur 2
const int sensorPin3 = A2;  // Pin analog untuk sensor cahaya jalur 3

// Inisialisasi LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Alamat I2C LCD dan ukuran kolom dan baris

// Variabel penampung waktu
unsigned long startTime[3] = {0};  // Waktu mulai untuk setiap jalur
unsigned long lapTime[3] = {0};    // Waktu lap untuk setiap jalur
unsigned long totalTime[3] = {0};  // Waktu total untuk setiap jalur
int lapCount[3] = {0};             // Jumlah lap untuk setiap jalur

// Inisialisasi tombol lap terakhir dan reset
const int lapButtonPin = 2;     // Pin digital untuk tombol lap terakhir
const int resetButtonPin = 3;   // Pin digital untuk tombol reset
bool lapButtonPressed = false;
bool resetButtonPressed = false;

void setup() {
  // Mengaktifkan sensor cahaya sebagai input
  pinMode(sensorPin1, INPUT);
  pinMode(sensorPin2, INPUT);
  pinMode(sensorPin3, INPUT);

  // Mengaktifkan tombol lap terakhir dan reset sebagai input dengan resistor pull-up internal
  pinMode(lapButtonPin, INPUT_PULLUP);
  pinMode(resetButtonPin, INPUT_PULLUP);

  // Inisialisasi LCD
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Timer Tamiya");
  lcd.setCursor(0, 1);
  lcd.print("Siap!");

  // Delay singkat sebelum memulai
  delay(2000);
}

void loop() {
  checkSensor(0, sensorPin1);
  checkSensor(1, sensorPin2);
  checkSensor(2, sensorPin3);
  checkLapButton();
  checkResetButton();
  displayTime();
  delay(10);
}

void checkSensor(int index, int sensorPin) {
  int sensorValue = analogRead(sensorPin);

  if (sensorValue < 500) {
    if (startTime[index] == 0) {
      startTime[index] = millis();
    } else {
      lapTime[index] = millis() - startTime[index];
      totalTime[index] += lapTime[index];
      lapCount[index]++;
      startTime[index] = millis();
    }
  }
}

void checkLapButton() {
  if (digitalRead(lapButtonPin) == LOW && !lapButtonPressed) {
    lapButtonPressed = true;
    for (int i = 0; i < 3; i++) {
      totalTime[i] += lapTime[i];
    }
  } else if (digitalRead(lapButtonPin) == HIGH && lapButtonPressed) {
    lapButtonPressed = false;
  }
}

void checkResetButton() {
  if (digitalRead(resetButtonPin) == LOW && !resetButtonPressed) {
    resetButtonPressed = true;
    for (int i = 0; i < 3; i++) {
      startTime[i] = 0;
      lapTime[i] = 0;
      totalTime[i] = 0;
      lapCount[i] = 0;
    }
  } else if (digitalRead(resetButtonPin) == HIGH && resetButtonPressed) {
    resetButtonPressed = false;
  }
}

void displayTime() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Jalur 1: ");
  lcd.print(lapCount[0]);
  lcd.print(" Lap");
  lcd.setCursor(0, 1);
  lcd.print("Waktu: ");
  lcd.print(totalTime[0] / lapCount[0]);
  lcd.print(" ms");

  lcd.setCursor(9, 0);
  lcd.print("Jalur 2: ");
  lcd.print(lapCount[1]);
  lcd.print(" Lap");
  lcd.setCursor(9, 1);
  lcd.print("Waktu: ");
  lcd.print(totalTime[1] / lapCount[1]);
  lcd.print(" ms");

  lcd.setCursor(0, 0);
  lcd.print("Jalur 3: ");
  lcd.print(lapCount[2]);
  lcd.print(" Lap");
  lcd.setCursor(0, 1);
  lcd.print("Waktu: ");
  lcd.print(totalTime[2] / lapCount[2]);
  lcd.print(" ms");

  lcd.setCursor(15, 1);
  lcd.print(digitalRead(resetButtonPin) == LOW ? "*" : " ");
}
