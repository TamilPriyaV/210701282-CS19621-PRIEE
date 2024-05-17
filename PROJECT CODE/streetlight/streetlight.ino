#define BLYNK_TEMPLATE_ID "TMPL35Ewp7wTw"
#define BLYNK_TEMPLATE_NAME "LDR"
#define BLYNK_AUTH_TOKEN "FJPt5b4DLqtgl0EOX6UydWG1zNug3aYn"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "Sudharsan";  // type your WiFi name
char pass[] = "nottu123";  // type your WiFi password

const int ldrPin = A0;  // LDR connected to analog pin A0
const int ledPin = D4;  // GPIO pin D4 connected to LED bulb
const int buttonPin = V2;  // Virtual pin V2 for the Blynk button

bool ledState = false;  // Variable to track LED state
bool buttonStatePrev = false;  // Variable to track previous button state

void sendSensor() {
  int ldrValue = analogRead(ldrPin);
  bool buttonState = digitalRead(buttonPin);

  if (ldrValue > 320) {  // Adjust threshold based on LDR sensitivity
    Serial.println("Light is OFF");
    Blynk.virtualWrite(V1, "Light is OFF! "); // Send notification-like message to Blynk app using Virtual Pin V1
    digitalWrite(ledPin, LOW); // Turn off LED
    ledState = false;  // Update LED state variable
  } else {
    Serial.println("Light is ON");
    Blynk.virtualWrite(V1, "Light is ON!");
    if (!ledState) {  // Check if LED was previously off
      digitalWrite(ledPin, HIGH); // Turn on LED only if it was off
      ledState = true;  // Update LED state variable
    }
  }

  buttonStatePrev = buttonState;  // Update previous button state
}

BLYNK_WRITE(buttonPin) {  // Blynk virtual pin V2 callback function
  int buttonState = param.asInt();  // Get value from Blynk app button (0 or 1)
  if (buttonState == 1) {  // If button is turned on
    sendSensor();  // Call sendSensor to check LDR and control LED
  } else {  // If button is turned off
    digitalWrite(ledPin, LOW); // Turn off LED
    ledState = false;  // Update LED state variable
  }
}

void setup() {
  pinMode(ldrPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);  // Set buttonPin as input with internal pull-up resistor
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();
}
