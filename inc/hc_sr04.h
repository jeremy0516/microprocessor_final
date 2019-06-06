#ifndef __hc_sr04__H__
#define __hc_sr04__H__

#include "stm32l476xx.h"

void wait(float TIME);
void send_trigger();
double get_distance();
void send_trigger_back();
double get_distance_back();

#endif
