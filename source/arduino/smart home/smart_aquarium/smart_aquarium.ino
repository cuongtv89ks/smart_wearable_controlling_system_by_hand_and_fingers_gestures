#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#include <DHT22.h> 
#include <stdio.h>
#include <Wire.h>
#include <SPI.h>
#include <NewPing.h>

#define PIXEL_PIN         6    
#define PIXEL_COUNT       36  
  
#define TRIGGER_PIN       11
#define ECHO_PIN          12
#define MAX_DISTANCE      200 

#define LAMP_RELAY        4

#define DHT22_PIN         8

// Setup a DHT22 instance
DHT22 myDHT22(DHT22_PIN);

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

int brightness = 0;
int showCase = 0;
int st = 0;
float temperature = 0.0;
float humidity = 0.0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LAMP_RELAY, OUTPUT);
  digitalWrite(LAMP_RELAY, LOW);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  // put your main code here, to run repeatedly:
    DHT22_ERROR_t errorCode;
    errorCode = myDHT22.readData();
    if (errorCode == DHT_ERROR_NONE){
      temperature = myDHT22.getTemperatureC();
      humidity = myDHT22.getHumidity();
    }

    if (Serial.available()){
      //byte buf[20];
      //byte data = Serial.readBytes(buf, 20);
      //Serial.write(buf, data);
      //Serial.println();
      byte data = Serial.read();
      if (data == 'h'){
        digitalWrite(LAMP_RELAY, HIGH);
      }
      else if (data == 'l'){
        digitalWrite(LAMP_RELAY, LOW);
      }
      else if (data == '+') {
        brightness += 50;
      }
      else if (data == '-') {
        brightness -= 50;
      }
      else if (data == '1') {
        showCase = 1;
      }
      else if (data == '2') {
        showCase = 2;
      }
      else if (data == '3') {
        showCase = 3;
      }
      else if (data == '4') {
        showCase = 4;
      }
      else if (data == '5') {
        showCase = 5;
      }
      else if (data == '6') {
        showCase = 6;
      }
      else if (data == '7') {
        showCase = 7;
      }
      else if (data == '8') {
        showCase = 8;
      }
      else if (data == '9') {
        showCase = 9;
      }
      else if (data == '0') {
        showCase = 0;
      }
      else if (data == 'a') {
          Serial.print(temperature);
          Serial.print(" ");
          Serial.print(humidity);
          Serial.print(" ");
          Serial.println(sonar.ping_cm());
      }
  }

  if (brightness>250){
    brightness = 250;
  }
  if (brightness<=0){
    brightness = 0;
  }

  startShow(showCase);
  
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
