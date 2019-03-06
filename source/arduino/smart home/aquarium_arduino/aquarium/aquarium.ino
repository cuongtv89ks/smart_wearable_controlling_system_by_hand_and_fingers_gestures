#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>
#include <SPI.h>
#include <Wire.h>
#include "RTClib.h"
#include <Adafruit_NeoPixel.h>
#include <OneWire.h>
#include <NewPing.h>


#define PIXEL_PIN    6    // Digital IO pin connected to the NeoPixels.

#define PIXEL_COUNT 9

#define TRIGGER_PIN  13 // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

// Color definitions
#define  BLACK           0x0000
#define BLUE            0x001F
#define RED             0xF800
#define GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0
#define WHITE           0xFFFF

RTC_DS1307 rtc;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);
OneWire  ds(12);  // on pin 12 (a 4.7K resistor is necessary)
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
int brightness = 50;
void setup() {
  // put your setup code here, to run once:
    Serial.begin(115200);
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);

    strip.begin();
    strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  // put your main code here, to run repeatedly:
  int temperature;
  if (Serial.available()){
    byte data = Serial.read();
    if (data == 'h'){
    digitalWrite(4, HIGH);
    }
    else if (data == 'b') {
      digitalWrite(4, LOW);
    }
    else if (data == 'u') {
      brightness += 50;
    }
    else if (data == 'd') {
      brightness -= 50;
    }
  }

  if (brightness>250){
    brightness = 250;
  }
  if (brightness<=0){
    brightness = 1;
  }

  temperature =  (5.0 * analogRead(A0) * 100.0) / 1024;
  //Serial.print("temperature analog: ");
  Serial.println(temperature);

  startShow(4);
  delay(100);
}


//1
void brownColor(void){
  for (int i=0; i < strip.numPixels(); i++){
    strip.setPixelColor(i, (brightness*102/255) , (brightness*51/255), (brightness*0/255));
    strip.show();
  }
}

//2
void whiteColor(void){
  for (int i=0; i < strip.numPixels(); i++){
    strip.setPixelColor(i, (brightness*255/255) , (brightness*255/255), (brightness*255/255));
    strip.show();
  }
}

//3
void pinkColor(void){
  for (int i=0; i < strip.numPixels(); i++){
    strip.setPixelColor(i, (brightness*243/255) , (brightness*0/255), (brightness*255/255));
    strip.show();
  }
}

//4
void blueColor(void){
  for (int i=0; i < strip.numPixels(); i++){
    strip.setPixelColor(i, (brightness*0/255) , (brightness*0/255), (brightness*255/255));
    strip.show();
  }
}

//5
void blueSkyColor(void){
  for (int i=0; i < strip.numPixels(); i++){
    strip.setPixelColor(i, (brightness*0/255) , (brightness*128/255), (brightness*255/255));
    strip.show();
  }
}

//6
void bluePearlColor(void){
  for (int i=0; i < strip.numPixels(); i++){
    strip.setPixelColor(i, (brightness*0/255) , (brightness*255/255), (brightness*255/255));
    strip.show();
  }
}

//7
void redColor(void){
  for (int i=0; i < strip.numPixels(); i++){
    strip.setPixelColor(i, (brightness*255/255) , (brightness*0/255), (brightness*0/255));
    strip.show();
  }
}

//8
void greenColor(void){
  for (int i=0; i < strip.numPixels(); i++){
    strip.setPixelColor(i, (brightness*0/255) , (brightness*255/255), (brightness*0/255));
    strip.show();
  }
}

//9
void orangeColor(void){
  for (int i=0; i < strip.numPixels(); i++){
    strip.setPixelColor(i, (brightness*255/255) , (brightness*128/255), (brightness*0/255));
    strip.show();
  }
}

//10
void violetColor(void){
  for (int i=0; i < strip.numPixels(); i++){
    strip.setPixelColor(i, (brightness*127/255) , (brightness*0/255), (brightness*255/255));
    strip.show();
  }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

//11
void rainbow(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//12
// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//13
//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j = 0; j < 10; j++) { //do 10 cycles of chasing
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, c);  //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}


//14
//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j = 0; j < 256; j++) {   // cycle all 256 colors in the wheel
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, Wheel( (i + j) % 255)); //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}


//15
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void startShow(int i) {
  switch(i){
    case 0: whiteColor();
            break;
    case 1: whiteColor();
            break;
    case 2: brownColor();
            break;
    case 3: greenColor();
            break;
    case 4: blueColor();
            break;
    case 5: pinkColor();
            break;
    case 6: redColor();
            break;
    case 7: orangeColor();
            break;
    case 8: bluePearlColor();
            break;
    case 9: blueSkyColor();
            break;
    case 10: violetColor();
            break;
    case 11: rainbow(5);
            break;
    case 12: rainbowCycle(5);
            break;
    case 13: theaterChaseRainbow(5);
            break;
  }
}

void ds18x20(void){
    byte i;
    byte present = 0;
    byte type_s;
    byte data[12];
    byte addr[8];
    float celsius;

    //ds.search(addr);
    for (int i=0; i<8; i++){
        Serial.println(addr[i],HEX);
    }

    ds.reset();
    ds.select(addr);
    ds.write(0x44, 1);        // start conversion, with parasite power on at the end

    //delay(1000);     // maybe 750ms is enough, maybe not
    // we might do a ds.depower() here, but the reset will take care of it.

    present = ds.reset();
    ds.select(addr);
    ds.write(0xBE);         // Read Scratchpad

    for ( i = 0; i < 9; i++) {           // we need 9 bytes
      data[i] = ds.read();
    }

    // Convert the data to actual temperature
    // because the result is a 16 bit signed integer, it should
    // be stored to an "int16_t" type, which is always 16 bits
    // even when compiled on a 32 bit processor.
    int16_t raw = (data[1] << 8) | data[0];
    if (type_s) {
      raw = raw << 3; // 9 bit resolution default
      if (data[7] == 0x10) {
        // "count remain" gives full 12 bit resolution
        raw = (raw & 0xFFF0) + 12 - data[6];
      }
    } else {
      byte cfg = (data[4] & 0x60);
      // at lower res, the low bits are undefined, so let's zero them
      if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
      else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
      else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
      //// default is 12 bit resolution, 750 ms conversion time
    }
    celsius = (float)raw / 16.0;
    Serial.print("  Temperature = ");
    Serial.print(celsius);
    Serial.println(" Celsius, ");
}

