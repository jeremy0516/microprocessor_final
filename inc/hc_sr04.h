#ifndef __hc_sr04__H__
#define __hc_sr04__H__

#include "stm32l476xx.h"

void wait(int TIME);
void send_trigger();
double get_distance();

#endif
