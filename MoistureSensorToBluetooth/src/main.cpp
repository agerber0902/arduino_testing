#include <Arduino.h>
#include <SoftwareSerial.h>

// Create a software serial port for HM-10 communication
SoftwareSerial bluetooth(2, 3); // RX, TX (adjust pins accordingly)

// Define the pins
int sensorPin = A0;
int ledPin = 13;

// Variables to store sensor value
int sensorValue = 0;

void sendMessage(String message);

void setup() {
  Serial.println("Setup started");
  
  // Start the software serial port for HM-10 communication
  bluetooth.begin(9600);
  
  // Start the hardware serial port for the Arduino (Serial Monitor)
  Serial.begin(9600);
  
  Serial.println("Setup complete");
}

void loop() {
  // Read the analog value from the sensor
  sensorValue = analogRead(sensorPin);
  
  // Print the sensor value to the Serial Monitor
  Serial.print("Soil Moisture Value: ");
  Serial.println(sensorValue);
  
  // Check if the soil is dry
  if (sensorValue > 500) {
    // Turn the LED on
    digitalWrite(ledPin, HIGH);

    // Send a message to the HM-10 module
    sendMessage("Soil is dry!");
  } else {
    // Turn the LED off
    digitalWrite(ledPin, LOW);
  }
  
  // Wait for 30 seconds before taking another reading
  delay(30000);
}

// Sends a message to the HM-10 module
void sendMessage(String message) {

  if(bluetooth.available() <= 0) {
    Serial.println("Bluetooth not available");
    return;
  }

  bluetooth.println(message);
  Serial.print("Sent to Bluetooth: ");
  Serial.println(message);
}