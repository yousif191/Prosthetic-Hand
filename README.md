# Prosthetic-Hand

## EMG-Controlled Robotic Hand with Bluetooth Communication

### Project Title
EMG-Controlled Robotic Hand with Bluetooth Communication

### Description
This project involves the development of a robotic hand controlled by electromyography (EMG) signals and Bluetooth commands. The robotic hand uses servo motors to mimic the movements of a human hand based on muscle signals and commands received via Bluetooth.

### Table of Contents
- [Project Overview](#project-overview)
- [Installation](#installation)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [Features](#features)
- [License](#license)

### Project Overview
The project consists of:
- An EMG sensor to capture muscle activity.
- Servo motors to control the movement of the robotic hand.
- A Bluetooth module for wireless communication.
- An Arduino to process the EMG signals and control the servos based on the processed data and Bluetooth commands.

### Installation
To run this project, you will need:
- Arduino board (e.g., Arduino Uno)
- EMG sensor
- Servo motors
- Bluetooth module (e.g., HC-05)
- Jumper wires
- Breadboard

1. Connect the components as per the pin configurations defined in the code.
2. Upload the provided Arduino code to your Arduino board.

### Usage
1. Upload the code to the Arduino board.
2. Connect the Bluetooth module to your computer or smartphone.
3. Send commands via Bluetooth to control the robotic hand, or let the EMG sensor data control it automatically based on muscle signals.

### Project Structure
- `main.ino`: The main Arduino script that handles EMG data processing, Bluetooth communication, and servo control.

### Features
1. **EMG Data Processing**: Captures and processes EMG signals to control the robotic hand.
2. **Bluetooth Control**: Allows remote control of the robotic hand via Bluetooth commands.
3. **Servo Control**: Controls individual fingers and wrist movements using servo motors.
4. **Automatic and Manual Modes**: Switch between automatic mode (based on EMG signals) and manual mode (based on Bluetooth commands).

### Short Description
This project uses an EMG sensor and Bluetooth communication to control a robotic hand. The hand mimics human finger movements based on muscle signals and commands received via Bluetooth.
