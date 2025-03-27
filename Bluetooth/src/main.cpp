#include <Arduino.h>
#include <SoftwareSerial.h>

int ledPin = 13;

// Create a software serial port for HM-10 communication
SoftwareSerial bluetooth(2, 3); // RX, TX (adjust pins accordingly)

void setup() {
  pinMode(ledPin, OUTPUT);
  
  // Start the software serial port for HM-10 communication
  bluetooth.begin(9600);
  
  // Start the hardware serial port for the Arduino (Serial Monitor)
  Serial.begin(9600);
  
  Serial.println("Setup complete");
}

void loop() {
  // Check if there is data available to read from the Serial Monitor
  if (Serial.available() > 0) {
    Serial.println("Serial Data available");
    char c = Serial.read();
    bluetooth.write(c);
    Serial.print("Sent to Bluetooth: ");
    Serial.println(c);
  }

  // Example: Write a predefined string to Bluetooth
  // String message = "Hello from Arduino!";
  // bluetooth.println(message); // Send the string to Bluetooth
  // Serial.print("Sent to Bluetooth: ");
  // Serial.println(message);

  delay(1000); // Delay to avoid flooding the Bluetooth connection

  // Check if there is data available to read from the HM-10
  if (bluetooth.available() > 0) {
    Serial.println("Bluetooth Data available");
    // If the HM-10 is connected, set the LED to HIGH
    digitalWrite(ledPin, HIGH);
    
    // Read the data from the HM-10 and accumulate it in a string
    String receivedData = "";
    while (bluetooth.available() > 0) {
      char c = bluetooth.read();
      receivedData += c;
    }
    // Print the entire received string to the Serial Monitor
    Serial.print("Received from Bluetooth: ");
    Serial.println(receivedData);

    // Try sending that data back to the HM-10
    bluetooth.println(receivedData);
    Serial.print("Sent to Bluetooth: ");
    Serial.println(receivedData);
    
  } else {
    // If no data is available, set the LED to LOW
    digitalWrite(ledPin, LOW);
  }
}