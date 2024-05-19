#define BLYNK_TEMPLATE_ID "TMPL35Ewp7wTw"
#define BLYNK_TEMPLATE_NAME "LDR"
#define BLYNK_AUTH_TOKEN "FJPt5b4DLqtgl0EOX6UydWG1zNug3aYn"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Sudharsan";  // WiFi name
char pass[] = "nottu123";   // WiFi password

const int ldrPin = A0;      // LDR connected to analog pin A0
const int ledPin = D4;      // GPIO pin D4 connected to LED

void setup() {
  pinMode(ldrPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  Blynk.virtualWrite(V1,"OFF");
}

void loop() {
  Blynk.run();

  int buttonState = digitalRead(ledPin);
  if (buttonState == HIGH) {
    int ldrValue = analogRead(ldrPin);
    String ldrStatus = (ldrValue > 320) ? "OFF" : "ON";
    Blynk.virtualWrite(V1, ldrStatus);
    Blynk.virtualWrite(V2, 0);
    if (ldrValue > 320) {
      Serial.println("Defect detected: Light is OFF!");
      Blynk.virtualWrite(V1,"Defect detected");
      Blynk.virtualWrite(V2, 1);
      digitalWrite(ledPin, LOW);
      //Blynk.virtualWrite(V1, LOW);
      delay(1000); // Delay for stability
    }
    else{
      String ldrStatus = (ldrValue > 320) ? "OFF" : "ON";
       Serial.print("LDR Value: ");
       Serial.print(ldrValue);
       Serial.print("  LDR Status: ");
       Serial.println(ldrStatus);
       Blynk.virtualWrite(V1, ldrStatus);
  }
    
  }
  else{
    Blynk.virtualWrite(V1,"OFF");
  }
}