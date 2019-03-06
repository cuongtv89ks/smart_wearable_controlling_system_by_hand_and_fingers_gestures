#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>
#include <SPI.h>

#define sclk 13
#define mosi 11
#define dc   9
#define cs   8
#define rst  7

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

int clockCenterX = 64;
int clockCenterY = 64;
int oldsec = 0;

void setup() {
  // put your setup code here, to run once:
    tft.begin();
    tft.fillRect(0, 0, 128, 128, BLACK);
    tft.invert(true);
    delay(100);
    tft.invert(false);
    delay(100);
    tft.fillScreen(BLACK);
    drawDisplay();
}

void loop() {
  // put your main code here, to run repeatedly:

}

void drawDisplay(){
    tft.fillScreen(BLACK);

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
    /*
    for (int i=0; i<60; i++){
        drawSec(i);
        delay(1000);
    }

    for (int i=0; i<60; i++){
        drawMin(i);
        delay(1000);
    }*/

    drawSec(15);
    drawMin(15);

    for (int i=0; i<12; i++){
        drawHour(i, 14);
        delay(1000);
    }
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

