// Define the analog pin for ignition detection
const int ignitionPin = A0;

// Define the relay control pins
const int relay1Pin = 14;
const int relay2Pin = 12;
const int relay3Pin = 13;

int ignitionThreshold = 900;  // Adjust this threshold based on your car's ignition voltage

void setup() {
  // Initialize Serial for debugging purposes
  Serial.begin(115200);

  // Set relay control pins as OUTPUT
  pinMode(ignitionPin, INPUT);
  pinMode(relay1Pin, OUTPUT);
  pinMode(relay2Pin, OUTPUT);
  pinMode(relay3Pin, OUTPUT);
  
  // Initial state of relays (can be HIGH or LOW depending on your relay module)
  digitalWrite(relay1Pin, HIGH);
  digitalWrite(relay2Pin, HIGH);
  digitalWrite(relay3Pin, HIGH);
}

void loop() {
  // Read the ignition status
  int ignitionValue = analogRead(ignitionPin);

  // Check if ignition is detected
  if (ignitionValue > ignitionThreshold) {
    // Ignition detected
    Serial.println("Ignition detected!");

    // Turn on relay 1
    digitalWrite(relay1Pin, LOW);
    delay(1000);

    // Turn on relay 2 for 5 seconds
    digitalWrite(relay2Pin, LOW);
    delay(5000);
    digitalWrite(relay2Pin, HIGH);

  } else {
    // No ignition detected
    Serial.println("No ignition detected!");

    // Turn on relay 3 for 2 seconds
    digitalWrite(relay3Pin, LOW);
    delay(2000);
    digitalWrite(relay3Pin, HIGH);

    // Turn on relay 2 for 5 seconds
    digitalWrite(relay2Pin, LOW);
    delay(5000);
    digitalWrite(relay2Pin, HIGH);

    // Wait for a minute
    delay(60000);

    // Turn off relay 1
    digitalWrite(relay1Pin, HIGH);
  }
}
