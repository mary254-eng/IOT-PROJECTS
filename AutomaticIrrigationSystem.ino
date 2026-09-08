#include <LiquidCrystal_I2C.h>

// Initialize the I2C LCD (0x27 address, 16 columns, 2 rows)
LiquidCrystal_I2C lcd(0x27, 16, 2); 

int moistureSensor = A0;  // Soil sensor connected to A0
int pump = 7;             // Relay connected to pin 7

int moisture;              // Stores sensor value
int lastMoisture = -1;     // Tracks previous moisture to avoid unnecessary redraws
bool pumpState = false;    // Tracks whether pump was ON or OFF on the last loop

void setup()
{
  pinMode(pump, OUTPUT);
  Serial.begin(9600);
  
  // Initialize the I2C LCD and turn on the backlight
  lcd.init();
  lcd.backlight();
  
  lcd.setCursor(0, 0);
  lcd.print("JSS Project");
  delay(1500);
  lcd.clear();
}

void loop()
{
  // Read soil moisture
  moisture = analogRead(moistureSensor);

  Serial.print("Soil moisture = ");
  Serial.println(moisture);

  // 1. Update moisture level on Row 0 ONLY if the value has changed
  if (moisture != lastMoisture)
  {
    lcd.setCursor(0, 0);
    lcd.print("Moisture: ");
    lcd.print(moisture);
    lcd.print("   "); // Clears trailing digits if value drops from 3 digits to 2
    lastMoisture = moisture;
  }

  // 2. Determine current pump state based on your threshold
  bool currentPumpState;
  if (moisture > 500)
  {
    digitalWrite(pump, LOW);             // Pump ON
    Serial.println("Watering plant..."); 
    currentPumpState = true;
  }
  else
  {
    digitalWrite(pump, HIGH);            // Pump OFF
    Serial.println("Soil has enough water"); 
    currentPumpState = false;
  }

  // 3. Update Row 1 on the LCD ONLY if the pump state actually changed
  if (currentPumpState != pumpState)
  {
    lcd.setCursor(0, 1);
    if (currentPumpState)
    {
      lcd.print("Pump: ON        ");
    }
    else
    {
      lcd.print("Pump: OFF       ");
    }
    pumpState = currentPumpState; // Save the state
  }

  delay(1000);
}
