#include <Servo.h>
#include <SoftwareSerial.h>
#include "TensorFlowLite.h"

// Include necessary TensorFlow Lite libraries
#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/version.h"

// Load the TensorFlow Lite model
#include "gesture_model.h"  // Model header file generated from the .tflite file

const int tensorArenaSize = 2 * 1024;
uint8_t tensorArena[tensorArenaSize];

const int emgPin = A1;
const int bluetoothRx = 10;
const int bluetoothTx = 11;

// Servo motor pins
const int wristPin = 3;
const int thumbPin = 5;
const int indexPin = 6;
const int ringPin = 8;
const int middlePin = 10;
const int pinkyPin = 12;

SoftwareSerial bluetooth(bluetoothRx, bluetoothTx);
Servo Thumb;
Servo Pinky;
Servo Index;
Servo Ring;
Servo Middle;
Servo Wrist;

tflite::MicroErrorReporter errorReporter;
tflite::AllOpsResolver resolver;
const tflite::Model* model = tflite::GetModel(gesture_model);
tflite::MicroInterpreter interpreter(model, resolver, tensorArena, tensorArenaSize, &errorReporter);
TfLiteTensor* input = interpreter.input(0);

void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);
  
  // Attach servo motors to respective pins
  Thumb.attach(thumbPin);
  Pinky.attach(pinkyPin);
  Index.attach(indexPin);
  Ring.attach(ringPin);
  Middle.attach(middlePin);
  Wrist.attach(wristPin);

  // Set initial positions for all servos
  Thumb.write(90);
  Pinky.write(90);
  Index.write(90);
  Ring.write(90);
  Middle.write(90);
  Wrist.write(90);
  
  if (interpreter.AllocateTensors() != kTfLiteOk) {
    Serial.println("Failed to allocate tensors!");
    while (1);
  }
}
void loop() {
  int emgValue = analogRead(emgPin);
  Serial.println(emgValue);
  bluetooth.println(emgValue);
  
  // Preprocess EMG value and input into the model
  input->data.f[0] = static_cast<float>(emgValue) / 1024.0;

  if (interpreter.Invoke() != kTfLiteOk) {
    Serial.println("Failed to invoke!");
    return;
  }
  // Get the output from the model
  TfLiteTensor* output = interpreter.output(0);
  int gesture = static_cast<int>(output->data.f[0]);  // Assuming output is the gesture index

  // Control the servos based on the gesture
  switch (gesture) {
    case 0:
      Thumb.write(90); // Neutral position for the thumb
      break;
    case 1:
      Pinky.write(90); // Neutral position for the pinky
      break;
    case 2:
      Index.write(90); // Neutral position for the index finger
      break;
    case 3:
      Ring.write(90); // Neutral position for the ring finger
      break;
    case 4:
      Middle.write(90); // Neutral position for the middle finger
      break;
    case 5:
      Wrist.write(90); // Neutral position for the wrist
      break;
    case 6:
      Thumb.write(0); // Example position for specific gesture affecting the thumb
      Pinky.write(0); // Example position for specific gesture affecting the pinky
      Index.write(0); // Example position for specific gesture affecting the index finger
      Ring.write(0); // Example position for specific gesture affecting the ring finger
      Middle.write(0); // Example position for specific gesture affecting the middle finger
      Wrist.write(0); // Example position for specific gesture affecting the wrist
      break;
    // Add more cases as needed for specific gestures and corresponding servo movements
  }
  delay(10);
}
