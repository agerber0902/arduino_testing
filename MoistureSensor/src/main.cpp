#include <Arduino.h>

// #include <SoftwareSerial.h>

// SoftwareSerial BTSerial(2, 3); // RX | TX
// int ledPin = 7;

// void setup() {
//     Serial.begin(9600);  // Monitor serial communication
//     BTSerial.begin(9600); // HM-10 default baud rate
//     Serial.println("HM-10 Bluetooth Module Ready");
// }

// void loop() {
//     // Read from HM-10 and send to Serial Monitor
//     if (BTSerial.available()) {
//         Serial.write(BTSerial.read());

//         digitalWrite(ledPin, 1);
//         delay(1000);
//         digitalWrite(ledPin, 0);
//         delay(1000);
//         digitalWrite(ledPin, 1);
//         delay(1000);
//         digitalWrite(ledPin, 0);
//         delay(1000);
//         digitalWrite(ledPin, 1);
//         delay(1000);
//         digitalWrite(ledPin, 0);
//         delay(1000);
//     }

//     // Read from Serial Monitor and send to HM-10
//     if (Serial.available()) {
//         BTSerial.write(Serial.read());
//     }
// }


// Define the pins
int sensorPin = A0;
int ledPin = 7;

// Variables to store sensor value
int sensorValue = 0;

void setup() {
  // Initialize serial communication at 9600 baud rate
  Serial.begin(9600);
  
  // Initialize the LED pin as an output
  pinMode(ledPin, OUTPUT);
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
  } else {
    // Turn the LED off
    digitalWrite(ledPin, LOW);
  }
  
  // Wait for a second before taking another reading
  delay(1000);
}