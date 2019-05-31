#include "stm32l476xx.h"
#include "helper_functions.h"
#include "led_button.h"
#include "timer.h"
#include "hc_sr04.h"
#include "move.h"

// Define pins for motor
#define MOTOR_gpio_1_1 GPIOB
#define MOTOR_pin_1_1 10
#define MOTOR_gpio_1_2 GPIOB
#define MOTOR_pin_1_2 11
#define MOTOR_gpio_2_1 GPIOB
#define MOTOR_pin_2_1 12
#define MOTOR_gpio_2_2 GPIOB
#define MOTOR_pin_2_2 13

#define ROTOR_gpio_1_1 GPIOB
#define ROTOR_pin_1_1 14
#define ROTOR_gpio_1_2 GPIOB
#define ROTOR_pin_1_2 15


void forward(){
	reset_gpio(MOTOR_gpio_1_1, MOTOR_pin_1_1);
	set_gpio(MOTOR_gpio_1_2, MOTOR_pin_1_2);
	reset_gpio(MOTOR_gpio_2_1, MOTOR_pin_2_1);
	set_gpio(MOTOR_gpio_2_2, MOTOR_pin_2_2);
	reset_gpio(ROTOR_gpio_1_1, ROTOR_pin_1_1);
	reset_gpio(ROTOR_gpio_1_2, ROTOR_pin_1_2);
}


void stop_forward(){
	reset_gpio(MOTOR_gpio_1_1, MOTOR_pin_1_1);
	reset_gpio(MOTOR_gpio_1_2, MOTOR_pin_1_2);
	reset_gpio(MOTOR_gpio_2_1, MOTOR_pin_2_1);
	reset_gpio(MOTOR_gpio_2_2, MOTOR_pin_2_2);
	reset_gpio(ROTOR_gpio_1_1, ROTOR_pin_1_1);
	reset_gpio(ROTOR_gpio_1_2, ROTOR_pin_1_2);
}


void CCW_turn(){
	reset_gpio(MOTOR_gpio_1_1, MOTOR_pin_1_1);
	reset_gpio(MOTOR_gpio_1_2, MOTOR_pin_1_2);
	reset_gpio(MOTOR_gpio_2_1, MOTOR_pin_2_1);
	reset_gpio(MOTOR_gpio_2_2, MOTOR_pin_2_2);
	reset_gpio(ROTOR_gpio_1_1, ROTOR_pin_1_1);
	set_gpio(ROTOR_gpio_1_2, ROTOR_pin_1_2);
}













