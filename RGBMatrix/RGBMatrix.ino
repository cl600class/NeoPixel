#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif

#define PIN 6

// MATRIX DECLARATION:
// Parameter 1 = width of NeoPixel matrix
// Parameter 2 = height of matrix
// Parameter 3 = pin number (most are valid)
// Parameter 4 = matrix layout flags, add together as needed:
//   NEO_MATRIX_TOP, NEO_MATRIX_BOTTOM, NEO_MATRIX_LEFT, NEO_MATRIX_RIGHT:
//     Position of the FIRST LED in the matrix; pick two, e.g.
//     NEO_MATRIX_TOP + NEO_MATRIX_LEFT for the top-left corner.
//   NEO_MATRIX_ROWS, NEO_MATRIX_COLUMNS: LEDs are arranged in horizontal
//     rows or in vertical columns, respectively; pick one or the other.
//   NEO_MATRIX_PROGRESSIVE, NEO_MATRIX_ZIGZAG: all rows/columns proceed
//     in the same order, or alternate lines reverse direction; pick one.
//   See example below for these values in action.
// Parameter 5 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_GRBW    Pixels are wired for GRBW bitstream (RGB+W NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)


// Example for NeoPixel Shield.  In this application we'd like to use it
// as a 5x8 tall matrix, with the USB port positioned at the top of the
// Arduino.  When held that way, the first pixel is at the top right, and
// lines are arranged in columns, progressive order.  The shield uses
// 800 KHz (v2) pixels that expect GRB color data.
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(16, 3, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
  NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800);

int x = matrix.width();
int y = matrix.height();
int brightness = 40;
uint16_t color_w = matrix.Color(255,255,255);
uint16_t color_bk = matrix.Color(0,0,0);
uint16_t color_y = matrix.Color(255,140,0);
uint16_t color_bl = matrix.Color(0,0,255);

void setup() {
  Serial.begin(9600);
   matrix.begin();
   matrix.setBrightness(brightness);
}

void loop() {
  matrix.fillScreen(0);
  set();
}

void set(){
  fill_srow();
  fade_out(millis());
  fill();
  fade_out(millis());
  single_point();
  single_point_t();
  dual();
  fade_out(millis());
  highlight();
  //turn_light();
}

void fill_srow(){
  for(int j=0; j<y; j++){
    for(int i=0; i<x; i++){
      matrix.drawPixel(i, j, color_w);
      matrix.show();
      delay(100);
    }
  }
}

void fill(){
  for(int i=0; i<x; i++){
    for(int j=0; j<y; j++){
      matrix.drawPixel(i, j, color_y);
    }
    matrix.show();
    delay(80);
  }
}

void fade_out(unsigned long _last){
  unsigned long now;
  unsigned long last = _last;
  int temp_b = brightness;
  while (temp_b > 0){
     now = millis();
     if (now-last>50){
        temp_b -= 1;
        matrix.setBrightness(temp_b);
        matrix.show();
        last = now;
    }
  }
  matrix.setBrightness(brightness);
  delay(1000);
}

void single_point(){
  int x_c[] = {0,0,0,1,2,2,2,3,4,4,4,5,6,6,6,7,8,8,8,9,10,10,10,11,12,12,12,13,14,14,14,15};
  int y_c[] = {0,1,2,2,2,1,0,0,0,1,2,2,2,1,0,0,0,1,2,2,2,1,0,0,0,1,2,2,2,1,0,0};
  int s = sizeof(x_c)/sizeof(x_c[0]);
  if (s == sizeof(y_c)/sizeof(y_c[0])){
    for(int i=0; i<s; i++){
      matrix.drawPixel(x_c[i], y_c[i], color_y);
      //Serial.println(x_c[i]);
      if (i>0){
        matrix.drawPixel(x_c[i-1], y_c[i-1], color_bk);
      }
      matrix.show();
      delay(100);
    }
    matrix.fillScreen(0);
    delay(500);
  }
}

void single_point_t(){
  int x_c[] = {0,0,0,1,2,2,2,3,4,4,4,5,6,6,6,7,8,8,8,9,10,10,10,11,12,12,12,13,14,14,14,15};
  int y_c[] = {0,1,2,2,2,1,0,0,0,1,2,2,2,1,0,0,0,1,2,2,2,1,0,0,0,1,2,2,2,1,0,0};
  int s = sizeof(x_c)/sizeof(x_c[0]);
  if (s == sizeof(y_c)/sizeof(y_c[0])){
    for(int i=0; i<s; i++){
      matrix.drawPixel(x_c[i], y_c[i], color_y);
      //Serial.println(x_c[i]);
      matrix.show();
      delay(100);
    }
    matrix.fillScreen(0);
    delay(500);
  }
}

void dual(){
  int x_c[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0};
  int y_c[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2};
  int s = sizeof(x_c)/sizeof(x_c[0]);
  int i, j = 0;
  bool nstop = true;
  while (nstop){
    if (i<x){
      matrix.drawPixel(i, 0, color_w);
      i++;
    }
    if (j<s){
      matrix.drawPixel(x_c[j], y_c[j], color_bl);
      j++;
    }
    nstop = i<x or j<s;
    matrix.show();
    delay(100);
  }
}

//highlight effect for only 16*3 matrix
void highlight(){
  //single row effect
  int max_brightness = 255;
  uint16_t temp_w = matrix.Color(80, 65, 80);
  matrix.setBrightness(max_brightness);
  for (int j=0; j<3; j++){
    for (int i=0; i<8; i++){
      matrix.drawPixel(i, j, temp_w);
      matrix.show();
      delay(50);
    }
  }
  //fade in
  unsigned long now;
  unsigned long last = millis();
  uint16_t temp_b;
  int tmp = 0;
  while (tmp <= 255){
     now = millis();
     if (now-last>10){
        temp_b = matrix.Color(tmp, tmp, tmp);
        tmp += 1;
        matrix.drawPixel(11, 1, temp_b);
        matrix.drawPixel(12, 1, temp_b);
        matrix.show();
        last = now;
    }
  }
  while (tmp >= 100){
     now = millis();
     if (now-last>10){
        tmp -= 1;
        temp_b = matrix.Color(tmp, tmp, tmp);
        matrix.drawPixel(11, 1, temp_b);
        matrix.drawPixel(12, 1, temp_b);
        matrix.show();
        last = now;
    }
  }
    while (tmp <= 255){
     now = millis();
     if (now-last>10){
        temp_b = matrix.Color(tmp, tmp, tmp);
        tmp += 1;
        matrix.drawPixel(11, 1, temp_b);
        matrix.drawPixel(12, 1, temp_b);
        matrix.show();
        last = now;
    }
  }
  delay(1000);
  matrix.fillScreen(0);
  matrix.setBrightness(brightness);
}

void turn_light(){
  int n = 1;
  //blinking
  while (n<=5){
    for(int i=0; i<8; i++){
      matrix.drawPixel(i, 1, color_y);
    }
    matrix.show();
    delay(400);
    matrix.fillScreen(0);
    matrix.show();
    delay(400);
    n++;
  }
  n = 1;
  //flow
  while (n<=5){
    for(int i=0; i<8; i++){
      matrix.drawPixel(7-i, 1, color_y);
      matrix.show();
      delay(50);
    }
    delay(200);
    matrix.fillScreen(0);
    matrix.show();
    delay(200);
    n++;
  }
  delay(200);
}


