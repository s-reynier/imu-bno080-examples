#include <Wire.h>

#include "SparkFun_BNO080_Arduino_Library.h" // Click here to get the library: http://librarymanager/All#SparkFun_BNO080
BNO080 myIMU;
#define SDA_PIN 21
#define SCL_PIN 22
#define POWER_PIN 12

void setup()
{
  
  Serial.begin(115200);
  delay(5000);
  Serial.println();
  Serial.println("BNO080 Read Example");
  Wire.setClock(400000);
  delay(100);
  Wire.flush();
  Wire.begin (SDA_PIN, SCL_PIN);
  //=================================

  if (myIMU.begin(0x4A, Wire) == false)
  {
    Serial.println("BNO080 not detected at default I2C address. Check your jumpers and the hookup guide. Freezing...");
    while (1);
  }

  Wire.setClock(400000); //Increase I2C data rate to 400kHz

  myIMU.enableGravity(50); //Send data update every 50ms
  myIMU.enableLinearAccelerometer(50);

  Serial.println(F("Rotation vector enabled"));
  Serial.println(F("Output in form i, j, k, real, accuracy"));
}

void loop()
{
  //Look for reports from the IMU
  if (myIMU.dataAvailable() == true)
  {
    float gx = myIMU.getGravityX();
    float gy = myIMU.getGravityY();
    float gz = myIMU.getGravityZ();
  
    float absg = sqrt((gx * gx) + (gy * gy) + (gz * gz));
  
    float  ax = myIMU.getLinAccelX();
    float  ay = myIMU.getLinAccelY();
    float  az = myIMU.getLinAccelZ();
  
    double acc = 0.0;
  
    if ((9.0 < absg) && (absg < 11.0)) {
      float skag = (gx * ax) + (gy * ay) + (gz * az);
      acc = skag / absg;
    } else {
      // Sensor error, the gravity vector is reported to be invalid
      acc = 0;
    }
    Serial.println(acc, 2);
   
  }
}
