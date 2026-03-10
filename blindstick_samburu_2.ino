#include <SoftwareSerial.h>

#define TRIG 6
#define ECHO 7
#define RELAY 5
#define BUZZER 8
#define LED 9

SoftwareSerial gsm(3,4); // RX, TX

long duration;
int distance;

unsigned long lastSMS = 0;
const unsigned long smsInterval = 120000; // 2 minutes

String phoneNumber = "+254718992360";

//================ RANDOM LOCATION FUNCTION ================//
String generateRandomLocation()
{
  float latitude  = -4.5 + (random(0, 8000) / 1000.0);
  float longitude = 33.5 + (random(0, 8000) / 1000.0);

  String loc = String(latitude, 6);
  loc += ", ";
  loc += String(longitude, 6);
  return loc;
}

//================ GSM SMS FUNCTION ================//
void sendSMS(String message)
{
  gsm.println("AT+CMGF=1");    
  delay(1000);
  gsm.println("AT+CMGS=\"" + phoneNumber + "\"");
  delay(1000);
  gsm.print(message);
  delay(500);
  gsm.write(26);
  delay(5000);
}

//================ ULTRASONIC FUNCTION ================//
int getDistance()
{
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  duration = pulseIn(ECHO, HIGH);
  distance = duration * 0.034 / 2;
  return distance;
}

//================ SETUP ================//
void setup()
{
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(RELAY, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(LED, OUTPUT);
  
  digitalWrite(RELAY, HIGH); // relay OFF (active LOW)
  digitalWrite(BUZZER, LOW);
  digitalWrite(LED, LOW);

  Serial.begin(9600);
  gsm.begin(9600);

  randomSeed(analogRead(A0));

  delay(5000);
  sendSMS("Blind stick activated and working.");
}

//================ LOOP ================//
void loop()
{
  int dist = getDistance();
  Serial.print("Distance: ");
  Serial.println(dist);

  // 🚨 OBSTACLE ALERT (<30cm)
  if(dist > 0 && dist < 30)
  {
    digitalWrite(RELAY, LOW);    // RELAY ON (inverted)
    digitalWrite(BUZZER, HIGH);
    digitalWrite(LED, HIGH);
  }
  else
  {
    digitalWrite(RELAY, HIGH);   // RELAY OFF (inverted)
    digitalWrite(BUZZER, LOW);
    digitalWrite(LED, LOW);
  }

  // 📩 SMS EVERY 2 MINUTES
  if(millis() - lastSMS > smsInterval)
  {
    lastSMS = millis();

    String msg = "Blind stick update\n";
    msg += "Distance: " + String(dist) + " cm\n";
    msg += "Location: " + generateRandomLocation();

    sendSMS(msg);
  }

  delay(200);
}
