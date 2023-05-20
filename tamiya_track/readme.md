# Microcontroller-based Lap Timer using Light Sensors

This repository contains the code for a microcontroller-based lap timer system that utilizes light sensors to accurately measure the lap times of model cars on three different tracks (A, B, and C). The system is designed to be used with microcontrollers like Arduino and provides additional features such as last lap detection, lap count, and a display to show the winner.

## Hardware Requirements

To use this lap timer system, you will need the following components:

- Microcontroller board (such as Arduino or a compatible board)
- Light sensors (to be connected to pins 2, 3, and 4 for tracks A, B, and C respectively)
- Reset/Stop button (to be connected to pin 5)
- Last Lap button (to be connected to pin 6)
- Buzzer (to be connected to pin 7)
- LiquidCrystal_I2C library and a compatible LCD (with I2C address 0x27)

## Software Requirements

To program and run the lap timer system, you will need:

- Arduino IDE (or any compatible development environment)
- Wire library (included with the Arduino IDE)
- LiquidCrystal_I2C library (can be installed from the Arduino Library Manager)

## Circuit Connection

Before running the lap timer system, make sure to connect the hardware components correctly to your microcontroller. Here's the recommended circuit connection:

1. Connect the light sensors to the appropriate pins on the microcontroller:
   - Track A: Connect the light sensor to pin 2.
   - Track B: Connect the light sensor to pin 3.
   - Track C: Connect the light sensor to pin 4.

2. Connect the Reset/Stop button to pin 5 and the Last Lap button to pin 6.

3. Connect the buzzer to pin 7.

4. Connect the LCD display using the I2C interface, ensuring that the I2C address is set to 0x27.

## Usage

To use the lap timer system, follow these steps:

1. Open the `lap_timer.ino` file in the Arduino IDE.

2. If you haven't already, install the required libraries (Wire and LiquidCrystal_I2C) using the Arduino Library Manager.

3. Select the appropriate board and port in the Arduino IDE.

4. Upload the code to the microcontroller.

5. Power on the circuit and observe the LCD display.

6. Place the light sensors on the start/finish lines of each track.

7. Press the Last Lap button to trigger the detection of the last lap.

8. Press the Reset/Stop button to reset the lap times and lap counts.

9. The LCD display will show the winner and lap statistics based on the fastest lap time achieved by any of the tracks.

10. The buzzer will emit tones when a lap is completed and when the winner is determined.

## Notes

- Make sure to adjust the debounce delays (`delay(50)`) if necessary to avoid false triggering of the buttons.

- The code assumes that the light sensors are connected to the microcontroller's falling edge interrupt pins. If you have different requirements, modify the code accordingly.

- Feel free to customize the code to suit your specific needs or add additional functionality as desired.

## Contributions

Contributions to this project are welcome! If you encounter any issues or have suggestions for improvements, please feel free to open an issue or submit a pull request.