# PedalMotorController: An Arduino platform for programmatically turning pedal knobs

## Description

The Pedal Motor Controller (abbreviated PMC) is a project that involves the mechanical turning of guitar pedal knobs for expressive guitar performance. Users can connect their phone over UDP to an Arduino hub that translates their phone's gyroscopic movements into knob turns. The knob turns can then influence music performed with the pedals.

If the user attaches their phone to the guitar headstock, then the guitar movements will have a direct correlation to sonic output. This is especially relevant for gestural research, as it provides a platform for investigating the relationship between performance gestures and musical style.

## Installation

1. Clone this repository to your machine.
2. In src, zip all folders into individual files, EXCLUDING src/Main.
3. Install the Arduino IDE and launch. Under the Sketch tab, select Include Library > Add .ZIP Library...
4. Select and install each of the zipped folders you created in step 2.
5. Once all zips are installed, make sure the program compiles by clicking the checkmark on the top left (labeled "Verify").
6. Finally, connect an Arduino GIGA to your computer, select it in the top left, and select Upload.

## Hardware

* Arduino GIGA R1 WiFi
* 4x 28BYJ-48 stepper motors
* 4x ULN2003 stepper motor drivers
* LCD1602 2x20 LCD display
* Joystick module
* Prototyping breadboard
* 3-pin potentiometer

## Credits

Created by Ian Doherty, fall 2025 through winter 2026.

Special thanks to Dr. Marcelo Wanderley for his supervision and Darryl Cameron for his assistance in assembly.

Created at the Input Devices and Music Interaction Laboratory (IDMIL) at McGill University in Montreal, Canada.