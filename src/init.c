#include "stm32l476xx.h"
#include "helper_functions.h"
#include "7seg.h"
#include "keypad.h"
#include "led_button.h"
#include "timer.h"
#include "hc_sr04.h"
#include "beeper.h"
#include "init.h"

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
#define LED_pin 1

// Define pins for button (default use on-board button PC13)
#define BUTTON_gpio GPIOC
#define BUTTON_pin 13

// Define pins for motor
#define MOTOR_gpio_1 GPIOA
#define MOTOR_pin_1 1
#define MOTOR_gpio_2 GPIOA
#define MOTOR_pin_2 2

#define ROTOR_gpio GPIOB
#define ROTOR_pin 8

#define TRIG_gpio GPIOC
#define TRIG_pin 1
#define ECHO_gpio GPIOC
#define ECHO_pin 2

// Define Counter timer
#define COUNTER_timer TIM2


int initialize(){
	FPU_init();
	SystemClock_Config(10);

	if(init_led(LED_gpio, LED_pin) != 0){
		return -1;
	}
	if(init_led(MOTOR_gpio_1, MOTOR_pin_1) != 0){
		return -1;
	}
	if(init_led(MOTOR_gpio_2, MOTOR_pin_2) != 0){
		return -1;
	}
	if(init_led(ROTOR_gpio, ROTOR_pin) != 0){
		return -1;
	}
	if(init_led(TRIG_gpio, TRIG_pin) != 0){
		return -1;
	}
	if(init_button(ECHO_gpio, ECHO_pin) != 0){
		return -1;
	}
	if(init_7seg_number(SEG_gpio, DIN_pin, CS_pin, CLK_pin) != 0){
		// Fail to init 7seg
		return -1;
	}

	return 0;
}
