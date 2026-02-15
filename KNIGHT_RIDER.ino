
int ledPins[] = {2, 3, 4, 5, 6};  // LED pins 
int numLeds = 5; 
void setup() { 
for (int i = 0; i < numLeds; i++) { 
pinMode(ledPins[i], OUTPUT); // set all pins as outputs 
} 
} 
void loop() { 
// move LEDs forward 
for (int i = 0; i < numLeds; i++) { 
digitalWrite(ledPins[i], HIGH); 
delay(200); 
digitalWrite(ledPins[i], LOW); 
} 
// move LEDs backward 
for (int i = numLeds - 2; i > 0; i--) { 
digitalWrite(ledPins[i], HIGH); 
delay(200); 
digitalWrite(ledPins[i], LOW);
}
