#ifndef __led__H__
#define __led__H__

#include "stm32l476xx.h"

void wave(float sec);
void all_twinkling(float sec);
void single_led(char color);
void led_moder(int mode);

#endif
