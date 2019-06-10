#include "stm32l476xx.h"
#include "helper_functions.h"
#include "timer.h"
#include "hc_sr04.h"

// a function that can delay time accurate to 0.1ms
void wait(float TIME){
	timer_enable(TIM2);
	timer_init(TIM2, 1000, 10000); //set timer to 1us.
	timer_start(TIM2);
	int sec = 0, last = 0;
	while(1){
		if(last!=TIM2->CNT){
			if(TIM2->CNT == 0){
				sec++;
			}
			last = TIM2->CNT;
			FPU_init();
			double now_time = sec + TIM2 -> CNT/10000.0;

			if (now_time >= TIME){      // the time executing the code above already pass through 1us.
				break;
			}
		}
	}
	timer_stop(TIM2);
}

// trigger the hc-sr04
void send_trigger(GPIO_TypeDef* gpio, int pin){
	reset_gpio(gpio, pin);
	wait(0.1);
	set_gpio(gpio, pin);
	wait(0.0001);
	reset_gpio(gpio, pin);
}

// get the distance.
double get_distance(GPIO_TypeDef* trig_gpio, int trig_pin, GPIO_TypeDef* echo_gpio, int echo_pin){

	double duration = 0.0;
	double distance_cm = 0.0;
	double sec = 0.0;
	double last = 0.0;

	send_trigger(trig_gpio, trig_pin);
	while((read_gpio(echo_gpio, echo_pin) == 0)){
		timer_enable(TIM3);
		timer_init(TIM3, 1000, 10000);
		timer_start(TIM3);
		sec = 0.0;
		last = 0.0;
	}

	while((read_gpio(echo_gpio, echo_pin) == 1)){
		if(last!=TIM3->CNT){
			if(TIM3->CNT == 0){
				sec += 1.0;
			}
			last = TIM3->CNT;
			FPU_init();
			duration = sec + TIM3->CNT/10000.0;
		}
	}
	timer_stop(TIM3);

	distance_cm = duration * 340.0 * 100.0 / 2.0;
	return distance_cm;
}
