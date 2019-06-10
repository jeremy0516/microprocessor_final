#ifndef __hc_sr04__H__
#define __hc_sr04__H__

#include "stm32l476xx.h"

void wait(float TIME);
void send_trigger(GPIO_TypeDef* gpio, int pin);
double get_distance(GPIO_TypeDef* trig_gpio, int trig_pin, GPIO_TypeDef* echo_gpio, int echo_pin);

#endif
