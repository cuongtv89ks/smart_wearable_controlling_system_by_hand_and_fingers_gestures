#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>
#include <SPI.h>
#include <Wire.h>
#include "RTClib.h"
#include <Adafruit_NeoPixel.h>
#include <OneWire.h>
#include <NewPing.h>

// OLED 128x128 SSD1351 SPI connecter mode
#define sclk 13
#define mosi 11
#define dc   12
#define cs   4
#define rst  8

#define BUTTON_1   A0    // Digital IO pin connected to the button.  This will be
                          // driven with a pull-up resistor so the switch should
                          // pull the pin to ground momentarily.  On a high -> low
                          // transition the button press logic will execute.
#define BUTTON_2   A1
#define BUTTON_3   A2


#define PIXEL_PIN    3    // Digital IO pin connected to the NeoPixels.

#define PIXEL_COUNT 10

#define TRIGGER_PIN  A3 // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     2  // Arduino pin tied to echo pin on the ultrasonic sensor.
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

Adafruit_SSD1351 tft = Adafruit_SSD1351(cs, dc, rst);
RTC_DS1307 rtc;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);
OneWire  ds(16);  // on pin 12 (a 4.7K resistor is necessary)
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

int clockCenterX = 64;
int clockCenterY = 64;
int oldsec = 0;

bool oldState = HIGH;
int showType = 0;

int brightness = 255;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
DateTime t;
/*
byte i;
byte present = 0;
byte type_s;
byte data[12];
byte addr[8];
float celsius;
*/
void setup() {
  // put your setup code here, to run once:
    tft.begin();
    tft.fillRect(0, 0, 128, 128, BLACK);
    tft.invert(true);
    delay(100);
    tft.invert(false);
    delay(100);
    tft.fillScreen(BLACK);
    Serial.begin(9600);

    rtc.begin();
    //rtc.adjust(DateTime(2017, 3, 16, 14, 26, 50));

    pinMode(BUTTON_1, INPUT_PULLUP);
    pinMode(BUTTON_2, INPUT_PULLUP);
    pinMode(BUTTON_3, INPUT_PULLUP);

    strip.begin();
    strip.show(); // Initialize all pixels to 'off'
}

void loop() {
      // put your main code here, to run repeatedly:
      int x, y;
      int prevSec;
      //float temperature;

      t = rtc.now();
      /*
      drawDisplay();
      //drawSec(t.second());
      drawMin(t.minute());
      drawHour(t.hour(), t.minute());
      */
      drawCalendar(t.day(), t.month(), t.year());
      Serial.print("Ping: ");
      Serial.print(sonar.ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range)
      Serial.println("cm");

      bool newState = digitalRead(BUTTON_3);
      if (newState == LOW && oldState == HIGH){
          delay(20);
          newState = digitalRead(BUTTON_3);
          if (newState == LOW){
              showType++;
              if (showType > 12)
                  showType = 0;
        }
      }
      oldState = newState;
      //Serial.println(showType);
      startShow(showType);
}

void drawDisplay(){

    //tft.fillScreen(BLACK);

    for (int i=0; i<3; i++){
        tft.drawCircle(clockCenterX, clockCenterY, 61 - i, WHITE);
    }

    for (int i=0; i<3; i++){
        tft.drawCircle(clockCenterX, clockCenterY, i, WHITE);
    }

    tft.setCursor(clockCenterX + 46, clockCenterY - 6);
    tft.setTextColor(CYAN);
    tft.setTextSize(2);
    tft.print("3");

    tft.setCursor(clockCenterX - 6, clockCenterY + 43);
    tft.setTextColor(CYAN);
    tft.setTextSize(2);
    tft.print("6");

    tft.setCursor(clockCenterX - 54, clockCenterY - 6);
    tft.setTextColor(CYAN);
    tft.setTextSize(2);
    tft.print("9");

    tft.setCursor(clockCenterX - 11, clockCenterY - 54);
    tft.setTextColor(CYAN);
    tft.setTextSize(2);
    tft.print("12");

    for (int i=0; i<12; i++){
        if ((i%3) != 0){
            drawMark(i);
        }
    }
}

void drawCalendar(int day, int month, int year){
    //tft.fillRect(0, 0, 128, 128, WHITE);
    for (int i=0; i<11; i++){
        tft.drawLine(15+(i*10), 0, 14+(i*10), 5, WHITE);
        tft.drawLine(16+(i*10), 0, 15+(i*10), 5, WHITE);
        tft.drawLine(17+(i*10), 0, 16+(i*10), 5, WHITE);
    }

    tft.setCursor(10, 20);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.print(day);

    tft.setCursor(40, 20);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.print(month);

    tft.setCursor(50, 50);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.print(year);

    tft.setCursor(10, 80);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.print(daysOfTheWeek[t.dayOfTheWeek()]);
}

void drawMark(int h){
    float x1, x2, y1, y2;

    h = h * 30;
    h = h + 270;

    x1 = 59 * cos(h*0.0175);
    y1 = 59 * sin(h*0.0175);
    x2 = 55 * cos(h*0.0175);
    y2 = 55 * sin(h*0.0175);

    tft.drawLine(x1+clockCenterX, y1+clockCenterY, x2+clockCenterX, y2+clockCenterY, WHITE);
}

void drawSec(int s){
    float x1, x2, y1, y2;

    int ps = s - 1;

    if (ps == -1)
        ps = 59;

    ps = ps * 6;
    ps = ps + 270;

    x1 = 53 * cos(ps*0.0175);
    y1 = 53 * sin(ps*0.0175);

    x2 = 49 * cos(ps*0.0175);
    y2 = 49 * sin(ps*0.0175);

    tft.drawLine(clockCenterX+x1, clockCenterY+y1, clockCenterX+x2, clockCenterY+y2, BLACK);

    s = s * 6;
    s = s + 270;

    x1 = 53 * cos(s*0.0175);
    y1 = 53 * sin(s*0.0175);

    x2 = 46 * cos(s*0.0175);
    y2 = 46 * sin(s*0.0175);

    tft.drawLine(clockCenterX+x1, clockCenterY+y1, clockCenterX+x2, clockCenterY+y2, RED);
}

void drawMin(int m) {
    float x1, x2, x3, x4, y1, y2, y3, y4;

    int pm = m -1;

    if (pm == -1)
        pm = 59;

    pm = pm * 6;
    pm = pm + 270;

    x1=40*cos(pm*0.0175);
    y1=40*sin(pm*0.0175);
    x2=4*cos(pm*0.0175);
    y2=4*sin(pm*0.0175);
    x3=15*cos((pm+4)*0.0175);
    y3=15*sin((pm+4)*0.0175);
    x4=15*cos((pm-4)*0.0175);
    y4=15*sin((pm-4)*0.0175);

    tft.drawLine(x1+clockCenterX, y1+clockCenterY, x3+clockCenterX, y3+clockCenterY, BLACK);
    tft.drawLine(x3+clockCenterX, y3+clockCenterY, x2+clockCenterX, y2+clockCenterY, BLACK);
    tft.drawLine(x2+clockCenterX, y2+clockCenterY, x4+clockCenterX, y4+clockCenterY, BLACK);
    tft.drawLine(x4+clockCenterX, y4+clockCenterY, x1+clockCenterX, y1+clockCenterY, BLACK);

    m=m*6;
    m=m+270;

    x1=40*cos(m*0.0175);
    y1=40*sin(m*0.0175);
    x2=4*cos(m*0.0175);
    y2=4*sin(m*0.0175);
    x3=15*cos((m+4)*0.0175);
    y3=15*sin((m+4)*0.0175);
    x4=15*cos((m-4)*0.0175);
    y4=15*sin((m-4)*0.0175);

    tft.drawLine(x1+clockCenterX, y1+clockCenterY, x3+clockCenterX, y3+clockCenterY, BLUE);
    tft.drawLine(x3+clockCenterX, y3+clockCenterY, x2+clockCenterX, y2+clockCenterY, BLUE);
    tft.drawLine(x2+clockCenterX, y2+clockCenterY, x4+clockCenterX, y4+clockCenterY, BLUE);
    tft.drawLine(x4+clockCenterX, y4+clockCenterY, x1+clockCenterX, y1+clockCenterY, BLUE);
}

void drawHour(int h, int m) {
    float x1, x2, x3, x4, y1, y2, y3, y4;

    int ph = h;

    if (m == 0){
        ph = ((ph-1)*30) + ((m+59)/2);
    }
    else {
        ph = (ph*30) + ((m-1)/2);
    }

    ph = ph + 270;

    x1=25*cos(ph*0.0175);
    y1=25*sin(ph*0.0175);
    x2=3*cos(ph*0.0175);
    y2=3*sin(ph*0.0175);
    x3=10*cos((ph+5)*0.0175);
    y3=10*sin((ph+5)*0.0175);
    x4=10*cos((ph-5)*0.0175);
    y4=10*sin((ph-5)*0.0175);

    tft.drawLine(x1+clockCenterX, y1+clockCenterY, x3+clockCenterX, y3+clockCenterY, BLACK);
    tft.drawLine(x3+clockCenterX, y3+clockCenterY, x2+clockCenterX, y2+clockCenterY, BLACK);
    tft.drawLine(x2+clockCenterX, y2+clockCenterY, x4+clockCenterX, y4+clockCenterY, BLACK);
    tft.drawLine(x4+clockCenterX, y4+clockCenterY, x1+clockCenterX, y1+clockCenterY, BLACK);

    h = (h*30) + (m/2);
    h = h+270;

    x1=25*cos(h*0.0175);
    y1=25*sin(h*0.0175);
    x2=3*cos(h*0.0175);
    y2=3*sin(h*0.0175);
    x3=10*cos((h+5)*0.0175);
    y3=10*sin((h+5)*0.0175);
    x4=10*cos((h-5)*0.0175);
    y4=10*sin((h-5)*0.0175);

    tft.drawLine(x1+clockCenterX, y1+clockCenterY, x3+clockCenterX, y3+clockCenterY, MAGENTA);
    tft.drawLine(x3+clockCenterX, y3+clockCenterY, x2+clockCenterX, y2+clockCenterY, MAGENTA);
    tft.drawLine(x2+clockCenterX, y2+clockCenterY, x4+clockCenterX, y4+clockCenterY, MAGENTA);
    tft.drawLine(x4+clockCenterX, y4+clockCenterY, x1+clockCenterX, y1+clockCenterY, MAGENTA);
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

