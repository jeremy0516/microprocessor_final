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

// Define pins for 7seg                                                           //PC3¡B4¡B5
#define SEG_gpio GPIOC
#define DIN_pin 3
#define CS_pin 4
#define CLK_pin 5

// Define pins for keypad
// If need to change need to also change EXTI_Setup and IRQHandler               //PA6¡B7¡B8¡B9      //PB3¡B4¡B5¡B6
#define COL_gpio GPIOA
#define COL_pin 6       // 6 7 8 9
#define ROW_gpio GPIOB
#define ROW_pin 3       // 3 4 5 6

// Define pins for led (default use on-board led PA5)                            //PA1
#define LED_gpio GPIOA
#define LED_pin 1

// Define pins for button (default use on-board button PC13)                     //PC13
#define BUTTON_gpio GPIOC
#define BUTTON_pin 13

// Define pins for motor                                                         //PA0¡B1¡B2      //PB8      //PC1¡B2
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
	while(1){
		double distance_cm = 0.0;
		int state = 0;   // state=0 => no need to turn.    state=1 => need to turn.

		// initialize.
		if(initialize() != 0){
			return -1;
		};


		// get the distance & show it.
		distance_cm = get_distance();
		display_two_decimal(SEG_gpio, DIN_pin, CS_pin, CLK_pin, distance_cm);
		//wait(1);       //make a delay in order to make the number on monitor look good.


		// make the buzzer beep.
		if ((distance_cm <= 30) && (distance_cm >= 20)){
			beep(587);
			wait(0.8);
			state = 1;
		}
		else if ((distance_cm <= 20) && (distance_cm >= 10)){
			beep(687);
			wait(0.1);
			state = 2;
		}
		else if (distance_cm <= 10){
			beep(787);
			wait(0.001);
			state = 3;
		}
		else{
			state = 0;
		}


		// obstacle avoidance.
		if (state != 0){
			forward();
		}
		else if ((state == 1) || (state == 2)){
			stop_forward();
		}
		else if (state == 3){
			CCW_turn();
		}


	}
	return 0;
}
