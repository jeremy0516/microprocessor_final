#include "stm32l476xx.h"
#include "helper_functions.h"
#include "led_button.h"
#include "timer.h"
#include "hc_sr04.h"
#include "led.h"

// Define pins for motor
#define LED_gpio GPIOA
#define LED_pin 6       //6 7 8 9 10

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


void single_led(char color){
	for (int i = 0; i < 5; i++){
		set_gpio(LED_gpio, LED_pin + i);
	}

	if (color == 'w'){
		reset_gpio(LED_gpio, LED_pin);
	}
	else if (color == 'r'){
		reset_gpio(LED_gpio, LED_pin + 1);
	}
	else if (color == 'y'){
		reset_gpio(LED_gpio, LED_pin + 2);
	}
	else if (color == 'g'){
		reset_gpio(LED_gpio, LED_pin + 3);
	}
	else if (color == 'b'){
		reset_gpio(LED_gpio, LED_pin + 4);
	}
	else{
		for (int i = 0; i < 5; i++){
			reset_gpio(LED_gpio, LED_pin + i);
		}
	}
}


void led_moder(int mode){
	if (mode == 0){
		for (int i = 0; i < 5; i++){
			set_gpio(LED_gpio, LED_pin + i);
		}
		wait(0.01);
	}
	if (mode == 1){
		wave(0.05);
	}
	if (mode == 2){
		all_twinkling(0.1);
	}
	if (mode == 3){
		single_led('w');
	}
	if (mode == 4){
		single_led('r');
	}
	if (mode == 5){
		single_led('y');
	}
	if (mode == 6){
		single_led('g');
	}
	if (mode == 7){
		single_led('b');
	}
}
