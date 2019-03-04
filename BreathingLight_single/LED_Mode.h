/****************************************************************************
  FileName     [ LED_Mode.h]
  PackageName  [ BreathingLight ]
  Synopsis     [Header file for class LED_Mode ]
  Author       [ Rui-Teng Zhang ]
  Copyright    [ Copyleft(c) 2018, NTUMaker Club, Taiwan ]
****************************************************************************/
#ifndef LED_MODE_H
#define LED_MODE_H

#include "Adafruit_NeoPixel.h"

class LED_Mode
{
	public:
		
		Adafruit_NeoPixel strip = Adafruit_NeoPixel();
		LED_Mode(int, int, int);

		    void set_wait(int wait) { _wait = wait; }
        void set_mode(int mode) { 
          _mode = mode;
          if (mode==2) set_max_step(_led_amount+10); 
          else set_max_step(_led_amount);
         }
        void set_max_step(int max_step) { _max_step = max_step; }
        void set_step(int);
        void set_step_0();
        void set_step_1(int);
        void set_step_2(int);
        void set_step_3(int);
        void run();
		
	private:
        int _mode = 0;
        int _pmode = 0;
		    int _led_amount = 1;
		    int brightness = 0;
		    int fadeAmount = 1;
        int _step = 0;
        int _wait = 100;
        int _max_step = 0;
        unsigned long _last;

		const int red=255, green=140, blue=0;
		const int red_1 = 0, green_1 = 0, blue_1 = 255;
		const int red_2 = 160, green_2 = 32, blue_2 = 240;
		
};

#endif
