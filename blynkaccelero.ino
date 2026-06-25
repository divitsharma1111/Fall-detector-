#define BLYNK_TEMPLATE_ID "TMPL33T7BRpbo"
#define BLYNK_TEMPLATE_NAME "Fall detectionn"
#define BLYNK_AUTH_TOKEN "UIvFkwUOAgzYH3PufFBQ5l0M-6XOYoJq"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Change if your LCD is different


bool isAlertSent=false;
const int MPU_ADDR = 0x69;  
const float threshold = 15.0;        // <-- Updated MPU6050 address
int buzzerPin=19;
int16_t AcX, AcY, AcZ,acc;

char ssid[] = "ADVAITH's M34";
char pass[] = "nicejeans-2H";
BlynkTimer timer;
void setup() {
  Wire.begin(21, 22);               // ESP32 SDA=21, SCL=22
  Serial.begin(115200);

  lcd.init();
  lcd.backlight();

  // Wake up MPU6050
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);                 // Power management register
  Wire.write(0);                    // Wake up
  Wire.endTransmission(true);

  lcd.setCursor(0, 0);
  lcd.print("MPU6050 Ready");
  delay(1000);
  lcd.clear();
   Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Timer to read accelerometer every 200 ms
}

void loop() {
 
 Blynk.run(); // Move to the top
  timer.run();
   // Read accelerometer registers
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);                 // ACCEL_XOUT_H register
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 6, true);

  AcX = Wire.read() << 8 | Wire.read();
  AcY = Wire.read() << 8 | Wire.read();
  AcZ = Wire.read() << 8 | Wire.read();

  // Serial output
  Serial.print("AcX=");
  Serial.print(AcX);
  Serial.print(" | AcY=");
  Serial.println(AcY);
  Serial.print("AcZ=");
  Serial.print(AcZ);
  acc=(9.8/16384)*(sqrt((AcX*AcX)+(AcY*AcY)+(AcZ*AcZ)));
  // LCD output
  lcd.setCursor(0, 0);
  lcd.print("accelration: "); 
lcd.print(acc);

 Blynk.virtualWrite(V1, acc);

   if (acc > threshold) {
    digitalWrite(19, HIGH); // Buzzer on
    
    // ONLY send the notification if we haven't sent one yet for this specific fall
    if (isAlertSent == false) {
      Blynk.logEvent("fall_alert", "Emergency! Acceleration exceeded 12g");
      isAlertSent = true; // Set the flag to true so it doesn't send again
    }
  } 
  else {
    digitalWrite(19, LOW); // Buzzer off
    isAlertSent = false;    // Reset the flag when acceleration returns to normal
  }

  delay(100); // Small delay to keep things stable
}


