#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD setup (address 0x27 is common for many I2C LCDs, check yours)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// HC-SR04 pin setup
int trigPin = 9;
int echoPin = 10;

void setup() {
  // Start serial communication for debugging
  Serial.begin(9600);
  
  // Set up the HC-SR04 pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Initialize the LCD
  lcd.begin(16, 2);
  lcd.print("Distance: ");
}

void loop() {
  // Clear the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Send a 10 microsecond pulse to trigger the sensor
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the pulse from the echoPin
  long duration = pulseIn(echoPin, HIGH);

  // Calculate distance (duration * speed of sound in cm, divided by 2 for round trip)
  long distance = duration * 0.0344 / 2;

  // Print distance to Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Display the distance on the LCD
  lcd.setCursor(0, 1); // Set the cursor to the second row
  lcd.print("Dist: ");
  lcd.print(distance);
  lcd.print(" cm    "); // The spaces ensure the previous value is cleared
  
  delay(500); // Delay for half a second before the next reading
}
