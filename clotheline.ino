#include <Servo.h>

#define RAIN_SENSOR A0
#define SERVO_PIN 9

Servo clothesServo;

// Adjust these angles based on your mechanical design
#define OUT_POSITION 20    // Clothesline outside
#define IN_POSITION 120    // Clothesline inside

int rainValue;
bool isRaining = false;
bool lastState = false;

// Adjust rain threshold after testing
#define RAIN_THRESHOLD 500

void setup() {
  clothesServo.attach(SERVO_PIN);
  pinMode(RAIN_SENSOR, INPUT);

  clothesServo.write(OUT_POSITION); // Default start outside

  Serial.begin(9600);
}

void loop() {
  rainValue = analogRead(RAIN_SENSOR);

  // Rain sensor gives LOW value when wet
  if (rainValue < RAIN_THRESHOLD) {
    isRaining = true;
  } else {
    isRaining = false;
  }

  Serial.print("Rain value: ");
  Serial.println(rainValue);

  // Move servo only if state changes
  if (isRaining != lastState) {
    if (isRaining) {
      clothesServo.write(IN_POSITION);   // Pull clothes inside
      Serial.println("Rain detected → Pulling clothes IN");
    } else {
      clothesServo.write(OUT_POSITION);  // Push clothes outside
      Serial.println("No rain → Moving clothes OUT");
    }
    lastState = isRaining;
    delay(2000); // Give servo time to complete movement
  }

  delay(500);
}
