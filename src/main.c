#include "stm32l476xx.h"
#include "helper_functions.h"
#include "7seg.h"
#include "keypad.h"
#include "led_button.h"
#include "timer.h"
#include "hc_sr04.h"
#include "beeper.h"
#include "init.h"
#include "move.h"
#include "led.h"

// PA : 0¡B6¡B7¡B8¡B9¡B10
// PB : 10¡B11¡B12¡B13¡B14¡B15
// PC : 1¡B2¡B3¡B4¡B5¡B13


// Define pins for 7seg                                                          //PC3¡B4¡B5
#define SEG_gpio GPIOC
#define DIN_pin 3
#define CS_pin 4
#define CLK_pin 5

// Define pins for led (default use on-board led PA5)                            //PA6¡B7¡B8¡B9¡B10
#define LED_gpio GPIOA
#define LED_pin 6

// Define pins for button (default use on-board button PC13)                     //PC13
#define BUTTON_gpio GPIOC
#define BUTTON_pin 13

// Define pins for motor                                                         //PA0              //PB8¡B9¡B10¡B11¡B12¡B13¡B14¡B15      //PC1¡B2
#define LF_MOTOR_gpio_pos GPIOB
#define LF_MOTOR_pin_pos 8
#define LF_MOTOR_gpio_neg GPIOB
#define LF_MOTOR_pin_neg 9
#define RF_MOTOR_gpio_pos GPIOB
#define RF_MOTOR_pin_pos 10
#define RF_MOTOR_gpio_neg GPIOB
#define RF_MOTOR_pin_neg 11
#define LB_MOTOR_gpio_pos GPIOB
#define LB_MOTOR_pin_pos 12
#define LB_MOTOR_gpio_neg GPIOB
#define LB_MOTOR_pin_neg 13
#define RB_MOTOR_gpio_pos GPIOB
#define RB_MOTOR_pin_pos 14
#define RB_MOTOR_gpio_neg GPIOB
#define RB_MOTOR_pin_neg 15

#define TRIG_gpio GPIOC
#define TRIG_pin 0
#define ECHO_gpio GPIOC
#define ECHO_pin 1

#define BEEPER_gpio GPIOA
#define BEEPER_pin 0

// Define Counter timer
#define COUNTER_timer TIM2

// Buzzer is fixed to PA0 due to its need for PWM signal
// Can change to other ports if needed, but need to look up the reference

// Use to decide which part of the code will run
// Use define & ifdef to control
#define lab_systick_blink
//#define lab_interrupt_keypad
//#define lab_alarm

// Remember to use correct "startup_stm32.s"

int main(){
	int mode = 0;
	int button_press = 0;

	while(1){
		double distance_cm = 0.0;
		int state = 0;   // state=0 => no need to turn.    state=1 => need to turn.

		// initialize.
		if(initialize() != 0){
			return -1;
		};

		button_press = user_press_button(100);
		if (button_press == 1){
			mode++;
		}

		mode = mode % 7;
		led_moder(mode);

		// get the distance & show it.
		distance_cm = get_distance();
		display_two_decimal(SEG_gpio, DIN_pin, CS_pin, CLK_pin, distance_cm);
		wait(0.01);       //make a delay in order to make the number on monitor looking good.


		// make the buzzer beep.
		if ((distance_cm <= 30) && (distance_cm >= 10)){
			beep(687);
			wait(0.1);
			state = 1;
		}
		else if (distance_cm <= 10){
			beep(787);
			wait(0.001);
			state = 2;
		}
		else{
			state = 0;
		}

		/*
		// obstacle avoidance.
		if (state == 0){
			forward();
		}
		else if ((state == 1) || (state == 2)){
			stop_forward();
		}
		else if (state == 3){
			CCW_turn();
		}
		*/

	}
	return 0;
}
