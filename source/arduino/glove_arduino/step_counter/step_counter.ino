#include <Wire.h>
#include "I2Cdev.h"
#include "MPU6050.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

#define BNO055_SAMPLERATE_DELAY_MS (10)
#define TCAADDR 0x70
//#define BUTTON_PIN 5


Adafruit_BNO055 bno1 = Adafruit_BNO055();

void tcaselect(uint8_t i) {
  if (i > 7) return;
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();  
}

void setup() {
  // put your setup code here, to run once:
  Serial2.begin(115200);
  Wire.begin();

  // initialize device
  Serial2.println("Initializing I2C devices...");
  tcaselect(0);
  if(!bno1.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial2.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }

  bno1.setExtCrystalUse(true);
}

void loop() {
  // put your main code here, to run repeatedly:
  int start_time;
  start_time = millis();
  tcaselect(0);
  imu::Vector<3> acc = bno1.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
  imu::Vector<3> l_acc = bno1.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
  Serial2.print(start_time);
  Serial2.print(F(" "));
  Serial2.print((float)acc.x());
  Serial2.print(F(" "));
  Serial2.print((float)acc.y());
  Serial2.print(F(" "));
  Serial2.print((float)acc.z());

  Serial2.print(F(" "));
  Serial2.print((float)l_acc.x());
  Serial2.print(F(" "));
  Serial2.print((float)l_acc.y());
  Serial2.print(F(" "));
  Serial2.println((float)l_acc.z());
  
  delay(BNO055_SAMPLERATE_DELAY_MS);

}
