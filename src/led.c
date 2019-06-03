#include "stm32l476xx.h"
#include "helper_functions.h"
#include "led_button.h"
#include "timer.h"
#include "hc_sr04.h"
#include "led.h"

// Define pins for motor
#define LED_gpio GPIOA
#define LED_pin 11       //11 12 13 14 15
#define BUTTON_gpio GPIOC
#define BUTTON_pin 13

void wave(int sec){
	for (int i = 0; i < 5; i++){
		set_gpio(LED_gpio, LED_pin + i);
	}

	for (int i = 0; i < 5; i++){
		reset_gpio(LED_gpio, LED_pin + i);
		wait(sec);
	}
}


void all_twinkling(int sec){
	for (int i = 0; i < 5; i++){
		set_gpio(LED_gpio, LED_pin + i);
	}

	for (int i = 0; i < 5; i++){
		reset_gpio(LED_gpio, LED_pin + i);
	}

	wait(sec);
}


void led_moder(int mode){
	if (mode == 0){
		wave(1);
	}
	if (mode == 1){
		wave(0.5);
	}
	if (mode == 2){
		wave(0.1);
	}
	if (mode == 3){
		all_twinkling(1);
	}
	if (mode == 4){
		all_twinkling(0.5);
	}
	if (mode == 5){
		all_twinkling(0.1);
	}
}

int mode_change(){
	// button_press_cycle_per_second (How many button press segments in a second)
	int button_press_cycle_per_second = 10;
	// Use to state how many cycles to check per button_press_cycle
	int debounce_cycles = 100;
	// Use to state the threshold when we consider a button press
	int debounce_threshold = debounce_cycles*0.7;
	// Used to implement negative edge trigger 0=not-presses 1=pressed
	int last_button_state=0;
	int state = 0;

	for(int a=0;a<button_press_cycle_per_second;a++){
		// Simple Debounce without interrupt
		int pos_cnt=0;
		for(int a=0;a<debounce_cycles;a++){
			// If button press add count
			if(read_gpio(BUTTON_gpio, BUTTON_pin)==0){
				pos_cnt++;
			}
			delay_without_interrupt(1000/(button_press_cycle_per_second*debounce_cycles));
		}
		// Check if need to change state
		if(pos_cnt>debounce_threshold){
			if(last_button_state==0){
				// Pressed button - Pos edge

				//SysTick->CTRL ^= (1 << SysTick_CTRL_ENABLE_Pos);
			}
			else{
				// Pressed button - Continued pressing
				// Do nothing
			}
			last_button_state = 1;
		}
		else{
			if(last_button_state==0){
				// Released button - Not pressing
				// Do nothing
			}
			else{
				// Released button - Neg edge
				// Do nothing
				state = 1;
			}
			last_button_state = 0;
		}
	}

	if (state == 1){
		return 1;
	}
	else{
		return 0;
	}
}
