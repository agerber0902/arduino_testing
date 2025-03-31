#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Adafruit_SHT31.h>

// Create a software serial port for HM-10 communication
SoftwareSerial bluetooth(2, 3); // RX, TX (adjust pins accordingly)

// Define the pins
int sensorPin = A0;
int ledPin = 13;

// Variables to store sensor value and threshold
int sensorValue = 0;
int moistureThreshold = 500; // Default threshold

// Create an instance of the SHT31-D sensor
Adafruit_SHT31 sht31 = Adafruit_SHT31();

void sendMessage(String message);
void checkBluetoothInput();

void setup() {
  Serial.println("Setup started");
  
  // Start the software serial port for HM-10 communication
  bluetooth.begin(9600);
  
  // Start the hardware serial port for the Arduino (Serial Monitor)
  Serial.begin(9600);
  
  pinMode(ledPin, OUTPUT);

  // Initialize the SHT31-D sensor
  if (!sht31.begin(0x44)) { // 0x44 is the default I2C address
    Serial.println("Couldn't find SHT31-D sensor!");
    while (1) delay(1);
  }
  
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
  
  // Read temperature and humidity from the SHT31-D sensor
  float temperature = sht31.readTemperature();
  float humidity = sht31.readHumidity();

  if (!isnan(temperature) && !isnan(humidity)) {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" *C");
    sendMessage("Temperature: " + String(temperature) + " *C");
    
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
    sendMessage("Humidity: " + String(humidity) + " %");

  } else {
    Serial.println("Failed to read from SHT31-D sensor!");
    sendMessage("Failed to read from SHT31-D sensor!");
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