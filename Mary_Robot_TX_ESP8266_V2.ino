#include <espnow.h>
#include <ESP8266WiFi.h>

// Motor pins
int L1 = D1;
int L2 = D2;
int R1 = D3;
int R2 = D4;
int ENA = D7; // Left motor speed
int ENB = D6; // Right motor speed

void setup() {
  Serial.begin(115200);

  // Set motor pins as OUTPUT
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Initialize ESP-NOW
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != 0) {
    Serial.println("ESP-NOW init failed");
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);

  // Receive callback
  esp_now_register_recv_cb([](uint8_t *mac, uint8_t *incomingData, uint8_t len) {
    char msg[len + 1];
    memcpy(msg, incomingData, len);
    msg[len] = '\0';
    Serial.print("Received: ");
    Serial.println(msg);

    if (strcmp(msg, "F") == 0) moveForward();
else if (strcmp(msg, "B") == 0) moveBackward();
else if (strcmp(msg, "L") == 0) turnLeft();
else if (strcmp(msg, "R") == 0) turnRight();
else stopMotors();

  });
}

void loop() {
  // Motors are controlled via callback, no code needed here
}

// Move Forward
void moveForward() {
  analogWrite(ENA, 200); // speed 0-255
  analogWrite(ENB, 200);
  digitalWrite(L1, LOW);
  digitalWrite(L2, HIGH);
  digitalWrite(R1, LOW);
  digitalWrite(R2, HIGH);
  Serial.println("Moving Forward");
}

// Move Backward
void moveBackward() {
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);
  digitalWrite(L1, HIGH);
  digitalWrite(L2, LOW);
  digitalWrite(R1, HIGH);
  digitalWrite(R2, LOW);
  Serial.println("Moving Backward");
}

// Stop Motors
void stopMotors() {
  digitalWrite(L1, LOW);
  digitalWrite(L2, LOW);
  digitalWrite(R1, LOW);
  digitalWrite(R2, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  Serial.println("Motors Stopped");
}

void turnLeft() {
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);

  digitalWrite(L1, LOW);
  digitalWrite(L2, HIGH);
  digitalWrite(R1, HIGH);
  digitalWrite(R2, LOW);
}

void turnRight() {
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);

  digitalWrite(L1, HIGH);
  digitalWrite(L2, LOW);
  digitalWrite(R1, LOW);
  digitalWrite(R2, HIGH);
}
