#define RELAY1 14  // Define the pins for the relays
#define RELAY2 12
#define RELAY3 13
#define IGNITION_SENSOR A0  // Define the analog input pin for the ignition sensor
#define IGNITION_THRESHOLD 900  // Adjust this value based on your voltage divider configuration
#define WAIT_TIME 30000  // 1 minute in milliseconds

bool relay2Activated = false;  // Flag to control Relay 2 activation
bool relay3Activated = false;  // Flag to control Relay 3 activation

void setup() {
  pinMode(RELAY1, OUTPUT);  // Set relay pins as output
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);

  digitalWrite(RELAY1, HIGH);
  digitalWrite(RELAY2, HIGH);
  digitalWrite(RELAY3, LOW);


  
  Serial.begin(9600);  // Start serial communication
}

void loop() {
  
  int ignitionValue = analogRead(IGNITION_SENSOR);

  if (ignitionValue > IGNITION_THRESHOLD) {
    // Car ignition is ON
    digitalWrite(RELAY1, LOW);

    if (!relay2Activated) {
      digitalWrite(RELAY2, LOW);
      delay(5000);  // Relay 2 is on for 5 seconds
      digitalWrite(RELAY2, HIGH);
      relay2Activated = true;
    }

    Serial.println("Ignition ON - Relay 1 and Relay 2 ON");
  } else {
    // Car ignition is OFF
    digitalWrite(RELAY3, HIGH);

    delay(2000);  // Relay 3 is on for 2 seconds
    digitalWrite(RELAY3, LOW);

    Serial.println("Ignition OFF - Relay 3 ON");

    delay(WAIT_TIME);

    if (digitalRead(RELAY1) == LOW) {
      digitalWrite(RELAY1, HIGH);
      relay2Activated = false;
      Serial.println("Relay 1 still ON after waiting - Relay 1 OFF");
    }
  }
  delay(1000);
}
