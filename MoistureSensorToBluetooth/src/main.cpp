#include <Arduino.h>
#include <SoftwareSerial.h>

// Create a software serial port for HM-10 communication
SoftwareSerial bluetooth(2, 3); // RX, TX (adjust pins accordingly)

// Define the pins
int sensorPin = A0;
int ledPin = 13;

// Variables to store sensor value and threshold
int sensorValue = 0;
int moistureThreshold = 500; // Default threshold

void sendMessage(String message);
void checkBluetoothInput();

void setup() {
  Serial.println("Setup started");
  
  // Start the software serial port for HM-10 communication
  bluetooth.begin(9600);
  
  // Start the hardware serial port for the Arduino (Serial Monitor)
  Serial.begin(9600);
  
  pinMode(ledPin, OUTPUT);
  
  Serial.println("Setup complete");
}

void loop() {
  // Check for Bluetooth input to update the threshold
  checkBluetoothInput();

  // Read the analog value from the sensor
  sensorValue = analogRead(sensorPin);
  
  // Print the sensor value to the Serial Monitor
  Serial.print("Soil Moisture Value: ");
  Serial.println(sensorValue);
  
  // Check if the soil is dry
  if (sensorValue > moistureThreshold) {
    // Turn the LED on
    digitalWrite(ledPin, HIGH);

    // Send a message to the HM-10 module
    sendMessage("Soil is dry!");
  } else {
    // Turn the LED off
    digitalWrite(ledPin, LOW);
  }
  
  // Wait for 30 seconds before taking another reading
  delay(1000);
}

// Sends a message to the HM-10 module
void sendMessage(String message) {
  if (bluetooth.available() > 0) {
    Serial.println("Bluetooth not available");
    return;
  }

  bluetooth.println(message);
  Serial.print("Sent to Bluetooth: ");
  Serial.println(message);
}

// Checks for Bluetooth input and updates the threshold
void checkBluetoothInput() {
  if (bluetooth.available() > 0) {
    String input = bluetooth.readStringUntil('\n'); // Read input until newline
    input.trim(); // Remove any extra whitespace
    Serial.println("Received input via Bluetooth: " + input);

    // Try to convert the input to an integer
    int newThreshold = input.toInt();
    if (newThreshold > 0) { // Ensure it's a valid positive number
      moistureThreshold = newThreshold;
      Serial.print("Updated moisture threshold to: ");
      Serial.println(moistureThreshold);
    } else {
      Serial.println("Invalid threshold input received via Bluetooth");
    }
  }
}