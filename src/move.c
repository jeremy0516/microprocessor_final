#include "stm32l476xx.h"
#include "helper_functions.h"
#include "led_button.h"
#include "timer.h"
#include "hc_sr04.h"
#include "move.h"

// Define pins for motor
#define MOTOR_gpio_1 GPIOA
#define MOTOR_pin_1 1
#define MOTOR_gpio_2 GPIOA
#define MOTOR_pin_2 2

#define ROTOR_gpio GPIOB
#define ROTOR_pin 8


void forward(){
	reset_gpio(MOTOR_gpio_1, MOTOR_pin_1);
	reset_gpio(MOTOR_gpio_2, MOTOR_pin_2);
	set_gpio(ROTOR_gpio, ROTOR_pin);
}


void stop_forward(){
	set_gpio(MOTOR_gpio_1, MOTOR_pin_1);
	set_gpio(MOTOR_gpio_2, MOTOR_pin_2);
	set_gpio(ROTOR_gpio, ROTOR_pin);
}


void CCW_turn(){
	reset_gpio(ROTOR_gpio, ROTOR_pin);
	wait(0.1);
	set_gpio(ROTOR_gpio, ROTOR_pin);
}













