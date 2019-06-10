#include "stm32l476xx.h"
#include "helper_functions.h"
#include "led_button.h"
#include "timer.h"
#include "hc_sr04.h"
#include "move.h"

// Define pins for motor
#define RF_MOTOR_gpio_pos GPIOB
#define RF_MOTOR_pin_pos 4
#define RF_MOTOR_gpio_neg GPIOB
#define RF_MOTOR_pin_neg 5
#define LF_MOTOR_gpio_pos GPIOB
#define LF_MOTOR_pin_pos 6
#define LF_MOTOR_gpio_neg GPIOB
#define LF_MOTOR_pin_neg 7
#define RB_MOTOR_gpio_pos GPIOB
#define RB_MOTOR_pin_pos 8
#define RB_MOTOR_gpio_neg GPIOB
#define RB_MOTOR_pin_neg 9
#define LB_MOTOR_gpio_pos GPIOB
#define LB_MOTOR_pin_pos 10
#define LB_MOTOR_gpio_neg GPIOB
#define LB_MOTOR_pin_neg 11


void forward(){
	set_gpio(LF_MOTOR_gpio_pos, LF_MOTOR_pin_pos);
	reset_gpio(LF_MOTOR_gpio_neg, LF_MOTOR_pin_neg);
	set_gpio(RF_MOTOR_gpio_pos, RF_MOTOR_pin_pos);
	reset_gpio(RF_MOTOR_gpio_neg, RF_MOTOR_pin_neg);
	set_gpio(LB_MOTOR_gpio_pos, LB_MOTOR_pin_pos);
	reset_gpio(LB_MOTOR_gpio_neg, LB_MOTOR_pin_neg);
	set_gpio(RB_MOTOR_gpio_pos, RB_MOTOR_pin_pos);
	reset_gpio(RB_MOTOR_gpio_neg, RB_MOTOR_pin_neg);
}


void stop(){
	reset_gpio(LF_MOTOR_gpio_pos, LF_MOTOR_pin_pos);
	reset_gpio(LF_MOTOR_gpio_neg, LF_MOTOR_pin_neg);
	reset_gpio(RF_MOTOR_gpio_pos, RF_MOTOR_pin_pos);
	reset_gpio(RF_MOTOR_gpio_neg, RF_MOTOR_pin_neg);
	reset_gpio(LB_MOTOR_gpio_pos, LB_MOTOR_pin_pos);
	reset_gpio(LB_MOTOR_gpio_neg, LB_MOTOR_pin_neg);
	reset_gpio(RB_MOTOR_gpio_pos, RB_MOTOR_pin_pos);
	reset_gpio(RB_MOTOR_gpio_neg, RB_MOTOR_pin_neg);
}


void CW_turn(){
	reset_gpio(LF_MOTOR_gpio_pos, LF_MOTOR_pin_pos);
	set_gpio(LF_MOTOR_gpio_neg, LF_MOTOR_pin_neg);
	set_gpio(RF_MOTOR_gpio_pos, RF_MOTOR_pin_pos);
	reset_gpio(RF_MOTOR_gpio_neg, RF_MOTOR_pin_neg);
	reset_gpio(LB_MOTOR_gpio_pos, LB_MOTOR_pin_pos);
	set_gpio(LB_MOTOR_gpio_neg, LB_MOTOR_pin_neg);
	set_gpio(RB_MOTOR_gpio_pos, RB_MOTOR_pin_pos);
	reset_gpio(RB_MOTOR_gpio_neg, RB_MOTOR_pin_neg);
}


void CCW_turn(){
	set_gpio(LF_MOTOR_gpio_pos, LF_MOTOR_pin_pos);
	reset_gpio(LF_MOTOR_gpio_neg, LF_MOTOR_pin_neg);
	reset_gpio(RF_MOTOR_gpio_pos, RF_MOTOR_pin_pos);
	set_gpio(RF_MOTOR_gpio_neg, RF_MOTOR_pin_neg);
	set_gpio(LB_MOTOR_gpio_pos, LB_MOTOR_pin_pos);
	reset_gpio(LB_MOTOR_gpio_neg, LB_MOTOR_pin_neg);
	reset_gpio(RB_MOTOR_gpio_pos, RB_MOTOR_pin_pos);
	set_gpio(RB_MOTOR_gpio_neg, RB_MOTOR_pin_neg);
}

