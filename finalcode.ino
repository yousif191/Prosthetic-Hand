#include <Servo.h>
#include <SoftwareSerial.h> // Include the SoftwareSerial library for Bluetooth communication

SoftwareSerial BTSerial(1, 0); // RX, TX

// Define the pin for the EMG sensor
const int emgSensorPin = A1; // Analog pin A0 for EMG sensor

// Define threshold value
const int threshold = 15; // Adjust the threshold as necessary

// Create servo objects
String command = "";

Servo Thumb;
Servo Pinky;
Servo Index;
Servo Ring;
Servo Middle;
Servo Wrist;
// Define the pins for the servos


void setup() {
  // Initialize serial communication
  // Serial.begin(9600);
  BTSerial.begin(9600);

  // Attach the servo objects to the specified pins
  Wrist.attach(3);
  Thumb.attach(5);
  Index.attach(6);
  Middle.attach(8);
  Ring.attach(10);
  Pinky.attach(12);



  Thumb.write(180);
  Middle.write(180);
  Ring.write(180);
  Index.write(180);
  Pinky.write(180);
}

void loop() {
  // Arrays to store the EMG sensor readings
  int readings1[5];
  int readings2[5];
  
  // Collect the first set of 5 readings
  for (int i = 0; i < 5; i++) {
    readings1[i] = analogRead(emgSensorPin);
    delay(1000); // Delay between readings to simulate sampling rate
  }

  // Calculate the mean of the first set of readings
  float mean1 = calculateMean(readings1, 5);
  // Serial.print("Mean1: ");
  // BTSerial.println(mean1);

  // Collect the second set of 5 readings
  for (int i = 0; i < 5; i++) {
    readings2[i] = analogRead(emgSensorPin);
    delay(1000); // Delay between readings to simulate sampling rate
  }

  // Calculate the mean of the second set of readings
  float mean2 = calculateMean(readings2, 5);
  // Serial.print("Mean2: ");
  // BTSerial.println(mean2);

  // Compare the means and control the servos if the difference exceeds the threshold
  if (abs(mean2 - mean1) > threshold) {
    BTSerial.println("Successfully Received Data");
    moveServos();
  } else {
    BTSerial.println("Failed data from the sensor");
    handleBluetoothCommand();
}
    delay(500);

  // Add a delay before the next loop iteration
}

// Function to calculate the mean of an array of integers
float calculateMean(int readings[], int numReadings) {
  int sum = 0;
  for (int i = 0; i < numReadings; i++) {
    sum += readings[i];
  }
  return (float)sum / numReadings;
}

// Function to move the servos
void moveServos() {
  // Example: Move servo1 to 90 degrees and servo2 to 45 degrees
  Thumb.write(0);
  Middle.write(0);
  Ring.write(0);
  Index.write(0);
  Pinky.write(0);
  delay(1000); // Hold the position for 1 second

  // Example: Move the servos back to their original positions

  Thumb.write(180);
  Middle.write(180);
  Ring.write(180);
  Index.write(180);
  Pinky.write(180);
  delay(1000); // Hold the position for 1 second
}

void handleBluetoothCommand(){
  if (BTSerial.available()) {
    command = BTSerial.readStringUntil('\n');

    // Control servos based on received command
    if (command == "pinkyup") {
      Pinky.write(0);
    } else if (command == "pinkydown") {
      Pinky.write(180);
    } else if (command == "ringup") {
      Ring.write(0);
    } else if (command == "ringdown") {
      Ring.write(180);
    } else if (command == "middleup") {
      Middle.write(0);
    } else if (command == "middledown") {
      Middle.write(180);
    } else if (command == "indexup") {
      Index.write(0);
    } else if (command == "indexdown") {
      Index.write(180);
    } else if (command == "thumbup") {
      Thumb.write(0);
    } else if (command == "thumbdown") {
      Thumb.write(180);
    } else if (command == "turnup") {
      Thumb.write(180);
      Middle.write(180);
      Ring.write(180);
      Index.write(180);
      Pinky.write(180);
    } else if (command == "turndown") {
      Thumb.write(0);
      delay(100);
      Middle.write(0);
      Ring.write(0);
      Pinky.write(0);
      Index.write(0);
    } else if (command == "close") {
      Thumb.write(0);
      Middle.write(0);
      Ring.write(0);
      Index.write(0);
      Pinky.write(0);
    } else if (command == "open") {
      Thumb.write(180);
      Middle.write(180);
      Ring.write(180);
      Index.write(180);
      Pinky.write(180);
    } else if (command == "turnleft") {
      Wrist.write(180);
    } else if (command == "turnright") {
      Wrist.write(0);
    } else if (command == "normal") {
      Wrist.write(90);
    }
  }
}

