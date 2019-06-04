#include "stm32l476xx.h"
#include "helper_functions.h"
#include "led_button.h"
#include "timer.h"
#include "hc_sr04.h"
#include "led.h"

// Define pins for motor
#define LED_gpio GPIOA
#define LED_pin 6       //6 7 8 9 10
#define BUTTON_gpio GPIOC
#define BUTTON_pin 13

void wave(float sec){
	for (int i = 0; i < 5; i++){
		set_gpio(LED_gpio, LED_pin + i);
	}

	for (int i = 0; i < 5; i++){
		reset_gpio(LED_gpio, LED_pin + i);
		wait(sec);
	}
}


void all_twinkling(float sec){
	for (int i = 0; i < 5; i++){
		set_gpio(LED_gpio, LED_pin + i);
	}

	wait(sec);

	for (int i = 0; i < 5; i++){
		reset_gpio(LED_gpio, LED_pin + i);
	}

	wait(sec);
}


void led_moder(int mode){
	if (mode == 0){
		for (int i = 0; i < 5; i++){
			set_gpio(LED_gpio, LED_pin + i);
		}
		wait(0.3);
	}
	if (mode == 1){
		wave(0.5);
	}
	if (mode == 2){
		wave(0.3);
	}
	if (mode == 3){
		wave(0.1);
	}
	if (mode == 4){
		all_twinkling(0.5);
	}
	if (mode == 5){
		all_twinkling(0.3);
	}
	if (mode == 6){
		all_twinkling(0.1);
	}
}
