#ifndef __led__H__
#define __led__H__

#include "stm32l476xx.h"

void wave(int sec);
void all_twinkling(int sec);
void led_moder(int mode);
int mode_change();

#endif
