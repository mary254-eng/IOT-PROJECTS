const int redPin = 8;    // Red light wire goes to pin 8
const int greenPin = 9; // Green light wire goes to pin 9 
const int bluePin = 10;  // Blue light wire goes to pin 10
int setColor;
void setup() {
  // Tell Arduino that these pins will send power out 
  pinMode(redPin, OUTPUT);  
  pinMode(greenPin, OUTPUT); 
  pinMode(bluePin, OUTPUT); 
} 
void loop() {
  // Show red light   
  setColor(255, 0, 0);   
  delay(1000); // wait 1 second
  // Show green light  
  setColor(0, 255, 0);  
  delay(1000); 
  // Show blue light  
  setColor(0, 0, 255);   
  delay(1000); 
 
  // Show yellow light  
  setColor(255, 255, 0);  
  delay(1000 ); 
 
  // Show cyan light (blue + green)
  setColor(0, 255, 255);   
  delay(500);    
   // Show magenta light (red + blue)
  setColor(255, 0, 255);  
  delay(500);      
// Show white light (red + green + blue)
setColor(255, 255, 255);   
delay(500);  
{  
// This function mixes the colors 
void setColor(int redValue, int greenValue, int blueValue) { 
  // Tell each color how bright to shine  
  analogWrite(redPin, redValue);  
  analogWrite(greenPin, greenValue); 
  analogWrite(bluePin, blueValue); 


}    
}
 
