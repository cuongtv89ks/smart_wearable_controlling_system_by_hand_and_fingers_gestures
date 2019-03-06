#include <Wire.h>
#include "I2Cdev.h"
#include "MPU6050.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

#define BNO055_SAMPLERATE_DELAY_MS (10)
#define TCAADDR 0x70
#define BUTTON_PIN 5


Adafruit_BNO055 bno1 = Adafruit_BNO055();
Adafruit_BNO055 bno2 = Adafruit_BNO055();
Adafruit_BNO055 bno3 = Adafruit_BNO055();

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
  pinMode(BUTTON_PIN, INPUT_PULLUP);

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
  
    tcaselect(3);
  if(!bno2.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial2.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
   bno2.setExtCrystalUse(false);

   tcaselect(4);
  if(!bno3.begin())
  {
    // There was a problem detecting the BNO055 ... check your connections 
    Serial2.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }

  bno3.setExtCrystalUse(false);
}

void loop() {
  // IMU on arm
  int start_time;
  
  if (digitalRead(BUTTON_PIN) == LOW){
    start_time = millis();
    tcaselect(0);
    //imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
    sensors_event_t event1;
    bno1.getEvent(&event1);
  
    // IMU on index finger
    tcaselect(3);
    //imu::Vector<3> euler = bno2.getVector(Adafruit_BNO055::VECTOR_EULER);
    sensors_event_t event2;
    bno2.getEvent(&event2);
  
    // IMU on thumb finger
      tcaselect(4);
    //imu::Vector<3> euler = bno2.getVector(Adafruit_BNO055::VECTOR_EULER);
    sensors_event_t event3;
    bno3.getEvent(&event3);
  
    Serial2.print(start_time);
    Serial2.print(F(","));
    Serial2.print((float)event1.orientation.x);
    Serial2.print(F(","));
    Serial2.print((float)event1.orientation.y);
    Serial2.print(F(","));
    Serial2.print((float)event1.orientation.z);
    Serial2.print(F(","));
    Serial2.print((float)event2.orientation.x);
    Serial2.print(F(","));
    Serial2.print((float)event2.orientation.y);
    Serial2.print(F(","));
    Serial2.print((float)event2.orientation.z);
    Serial2.print(F(","));
    Serial2.print((float)event3.orientation.x);
    Serial2.print(F(","));
    Serial2.print((float)event3.orientation.y);
    Serial2.print(F(","));
    Serial2.println((float)event3.orientation.z);
    
    delay(BNO055_SAMPLERATE_DELAY_MS);
  }
}

