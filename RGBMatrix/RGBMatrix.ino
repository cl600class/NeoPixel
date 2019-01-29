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
uint16_t color_b = matrix.Color(0,0,0);
uint16_t color_y = matrix.Color(255,140,0);

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
  int x_c[] = {0,0,0,1,2,2,2,3,4,4,4,5,6,6,6,7,8,8,8,9,10,10,10,11,12,12,12,13,14};
  int y_c[] = {0,1,2,2,2,1,0,0,0,1,2,2,2,1,0,0,0,1,2,2,2,1,0,0,0,1,2,2,2};
  int s = sizeof(x_c)/sizeof(x_c[0]);
  if (s == sizeof(y_c)/sizeof(y_c[0])){
    for(int i=0; i<s; i++){
      matrix.drawPixel(x_c[i], y_c[i], color_y);
      Serial.println(x_c[i]);
      if (i>0){
        matrix.drawPixel(x_c[i-1], y_c[i-1], color_b);
      }
      matrix.show();
      delay(100);
    }
    matrix.fillScreen(0);
    delay(500);
  }
}

