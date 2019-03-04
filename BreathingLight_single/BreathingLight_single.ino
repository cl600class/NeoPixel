/****************************************************************************
  FileName     [ BreathingLight_single.ino ]
  PackageName  [ BreathingLight_single ]
  Synopsis     [ Define main() function ]
  Author       [ Rui-Teng Zhang (BreathingLight)]
  Copyright    [ Copyleft(c) 2018, NTUMaker Club, Taiwan ]
  Adapter      [ C.Y. Tsai ]
****************************************************************************/

#ifdef __AVR__
  #include <avr/power.h>
#endif

#include "LED_Mode.h"

#define PIN 6

#define LED_AMOUNT 16

LED_Mode st = LED_Mode(PIN,LED_AMOUNT, 0);

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  if(Serial.available())
  {
    char val = Serial.read();
    if(val == '1')
    {
      st.set_wait(70);
			st.set_mode(1);
    }
		else if(val == '2')
		{
      st.set_wait(90);
			st.set_mode(2);
		}
		else if(val == '3')
		{
      st.set_wait(70);
			st.set_mode(3);
		}
    else if(val == '4')
    {
      st.set_mode(0);
    }   
  }
  st.run();
  delay(1);
}

