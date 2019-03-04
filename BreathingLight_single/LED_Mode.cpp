/****************************************************************************
  FileName     [ LED_Mode.cpp]
  PackageName  [ BreathingLight ]
  Synopsis     [ Define member functions of class LED_Mode ]
  Author       [ Rui-Teng Zhang ]
  Copyright    [ Copyleft(c) 2018, NTUMaker Club, Taiwan ]
****************************************************************************/
#include <Adafruit_NeoPixel.h>
#include "LED_Mode.h"

LED_Mode::LED_Mode(int pin, int LED_amount, int mode)
{
    strip.setPin(pin);
    strip.updateLength(LED_amount);
    _led_amount = LED_amount;
    _last = millis();
    _mode = mode;
    _pmode = mode;
    _max_step = (_mode==2)? LED_amount+10: LED_amount;
    strip.begin();
}

void LED_Mode::set_step(int step)
{

    if (_mode == 1)
        set_step_1(step);
    else if (_mode == 2)
        set_step_2(step);
    else if (_mode == 3)
        set_step_3(step);
    else
        set_step_0();

    strip.show();
}

void LED_Mode::set_step_0()
{
    for(int i=0;i<strip.numPixels();i++)
    {
        strip.setPixelColor(i, strip.Color(0, 0, 0));
    }
}

void LED_Mode::set_step_1(int step)
{
    int n=_led_amount;
    brightness = abs(20-step)*2.5;
    for(int i=0;i<n;i++)
    {
        strip.setBrightness(brightness);
        strip.setPixelColor(i, strip.Color(red, green, blue));
    }
}

void LED_Mode::set_step_2(int step)
{
    strip.setBrightness(50);
    int n = _led_amount+10;
    for(int j=0;j<n;j++)
    {
        int k = (step+j)%n;
        if (j <= 5)
            strip.setPixelColor(k, red/(7-j), green/(7-j), blue);
        else if (j <= 10)
            strip.setPixelColor(k, red, green, blue);
        else
            strip.setPixelColor(k, 0, 0, 0);
    }
}

void LED_Mode::set_step_3(int step)
{
	strip.setBrightness(50);
	int n = _led_amount/2;
    for (int j = 0; j < 2*n; ++j)
    {
        int k = abs(n-(step+j)%(2*n));
        int red = (red_2*k+red_1*(n-k))/n;
        int green = (green_2*k+green_1*(n-k))/n;
        int blue = (blue_2*k+blue_1*(n-k))/n;
        strip.setPixelColor(j, strip.Color(red, green, blue));
    }
}

void LED_Mode::run() {
    unsigned long now = millis();
    if (now - _last > _wait) {
        _step = (_step+1) % _max_step;
        if (_pmode!=_mode){
          _step=0;
          _pmode = _mode; 
        }
        set_step(_step);
        _last = now;
    }
}
