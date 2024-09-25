#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <BlynkSimpleEsp8266.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // I2C LCD address

char auth[] = "YourBlynkAuthToken";
char ssid[] = "YourWiFiSSID";
char pass[] = "YourWiFiPassword";

// Sensor Pins
const int turbidityPin = A0;
const int tdsPin = A1;
const int phPin = A2;

float turbidityValue, tdsValue, phValue;

// Read sensor values
void readSensors() {
  // Read turbidity value
  turbidityValue = analogRead(turbidityPin);
  
  // Read TDS value
  tdsValue = analogRead(tdsPin);
  
  // Read pH value
  phValue = analogRead(phPin);

  // Convert analog values to meaningful measurements (calibration needed)
  turbidityValue = map(turbidityValue, 0, 1023, 0, 100);  // Example conversion
  tdsValue = map(tdsValue, 0, 1023, 0, 1000);             // Example conversion
  phValue = map(phValue, 0, 1023, 0, 14);                 // Example conversion
}

// Blynk virtual pin assignment
Blynk.virtualWrite(V0, turbidityValue); // V0 for turbidity
Blynk.virtualWrite(V1, tdsValue);       // V1 for TDS
Blynk.virtualWrite(V2, phValue);        // V2 for pH

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);

  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Water Quality");
}

void loop() {
  Blynk.run();

  readSensors();

  // Display values on LCD
  lcd.setCursor(0, 1);
  lcd.print("Turb: ");
  lcd.print(turbidityValue);
  lcd.print(" NTU");
  
  lcd.setCursor(0, 2);
  lcd.print("TDS: ");
  lcd.print(tdsValue);
  lcd.print(" ppm");

  lcd.setCursor(0, 3);
  lcd.print("pH: ");
  lcd.print(phValue);

  delay(1000); // Refresh every second
}
