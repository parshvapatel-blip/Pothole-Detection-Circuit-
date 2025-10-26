#include <Wire.h>
#include <LiquidCrystal.h>
#include <MPU6050.h>

MPU6050 mpu;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);  

int16_t ax, ay, az;
float accelZ;
float baseZ = 0;
bool calibrated = false;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("Pothole Detect");
  delay(1500);
  lcd.clear();

  mpu.initialize();


  lcd.print("Calibrating...");
  long sumZ = 0;
  for (int i = 0; i < 100; i++) {
    mpu.getAcceleration(&ax, &ay, &az);
    sumZ += az;
    delay(10);
  }
  baseZ = sumZ / 100.0;
  calibrated = true;

  lcd.clear();
  lcd.print("Ready...");
  delay(1000);
  lcd.clear();
}

void loop() {
  mpu.getAcceleration(&ax, &ay, &az);
  accelZ = az;


  float diffZ = abs(accelZ - baseZ);

  Serial.print("Z: ");
  Serial.print(accelZ);
  Serial.print(" | Diff: ");
  Serial.println(diffZ);

  lcd.setCursor(0, 0);
  if (diffZ > 2000) {  
    lcd.print("Pothole Detected");
  } else {
    lcd.print("Road Smooth     ");
  }

  delay(200);
}
