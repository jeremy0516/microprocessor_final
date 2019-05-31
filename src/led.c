#include "stm32l476xx.h"
#include "helper_functions.h"
#include "led_button.h"
#include "timer.h"
#include "hc_sr04.h"
#include "led.h"

// Define pins for motor
#define LED_gpio GPIOA
#define LED_pin 11       //11 12 13 14

void wave(){
	for (int i = 0; i < 4; i++){
		set_gpio(LED_gpio, LED_pin + i);
	}

	for (int i = 0; i < 4; i++){
		reset_gpio(LED_gpio, LED_pin + i);
		wait(0.5);
	}
}
