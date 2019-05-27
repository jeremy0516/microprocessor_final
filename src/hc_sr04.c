#include "stm32l476xx.h"
#include "helper_functions.h"
#include "7seg.h"
#include "keypad.h"
#include "led_button.h"
#include "timer.h"
#include "hc_sr04.h"

// Define pins for 7seg
#define SEG_gpio GPIOC
#define DIN_pin 3
#define CS_pin 4
#define CLK_pin 5

// Define pins for keypad
// If need to change need to also change EXTI_Setup and IRQHandler
#define COL_gpio GPIOA
#define COL_pin 6       // 6 7 8 9
#define ROW_gpio GPIOB
#define ROW_pin 3       // 3 4 5 6

// Define pins for led (default use on-board led PA5)
#define LED_gpio GPIOA
#define LED_pin 5

// Define pins for button (default use on-board button PC13)
#define BUTTON_gpio GPIOC
#define BUTTON_pin 13

// Define pins for motor
#define MOTOR_gpio GPIOA
#define MOTOR_pin 1
#define MOTORGD_gpio GPIOA
#define MOTORGD_pin 4

#define ROTOR_gpio GPIOB
#define ROTOR_pin 8
#define ROTORGD_gpio GPIOB
#define ROTORGD_pin 9

#define TRIG_gpio GPIOC
#define TRIG_pin 1
#define ECHO_gpio GPIOC
#define ECHO_pin 2


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
void send_trigger(){
	reset_gpio(TRIG_gpio, TRIG_pin);
	wait(0.5);
	set_gpio(TRIG_gpio, TRIG_pin);
	wait(0.0001);
	reset_gpio(TRIG_gpio, TRIG_pin);
}

// get the distance.
double get_distance(){

	double duration = 0.0;
	double distance_cm = 0.0;
	double sec = 0.0;
	double last = 0.0;

	send_trigger();
	while((read_gpio(ECHO_gpio, ECHO_pin) == 0)){
		timer_enable(TIM3);
		timer_init(TIM3, 1000, 10000);
		timer_start(TIM3);
		sec = 0.0;
		last = 0.0;
	}

	while((read_gpio(ECHO_gpio, ECHO_pin) == 1)){
		if(last!=TIM3->CNT){
			if(TIM3->CNT == 0){
				sec += 1.0;
			}
			last = TIM3->CNT;
			FPU_init();
			duration = sec + TIM3 -> CNT/10000.0;
		}
	}
	timer_stop(TIM3);

	distance_cm = duration * 340.0 * 100.0 / 2.0;
	return distance_cm;
}


