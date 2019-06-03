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

// PA : 0¡B6¡B7¡B8¡B9¡B11¡B12¡B13¡B14¡B15
// PB : 3¡B4¡B5¡B6¡B10¡B11¡B12¡B13¡B14¡B15
// PC : 1¡B2¡B3¡B4¡B5¡B13


// Define pins for 7seg                                                          //PC3¡B4¡B5
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

// Define pins for led (default use on-board led PA5)                            //PA11¡B12¡B13¡B14¡B15
#define LED_gpio GPIOA
#define LED_pin 11

// Define pins for button (default use on-board button PC13)                     //PC13
#define BUTTON_gpio GPIOC
#define BUTTON_pin 13

// Define pins for motor                                                         //PA0              //PB10¡B11¡B12¡B13¡B14¡B15      //PC1¡B2
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
	int mode = 0;
	int button_press = 0;
	// button_press_cycle_per_second (How many button press segments in a second)
	int button_press_cycle_per_second = 10;
	// Use to state how many cycles to check per button_press_cycle
	int debounce_cycles = 100;
	// Use to state the threshold when we consider a button press
	int debounce_threshold = debounce_cycles*0.7;
	// Used to implement negative edge trigger 0=not-presses 1=pressed
	int last_button_state=0;
	while(1){
		double distance_cm = 0.0;
		int state = 0;   // state=0 => no need to turn.    state=1 => need to turn.
		//button_press = mode_change();


		// initialize.
		if(initialize() != 0){
			return -1;
		};

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
					mode++;
				}
				last_button_state = 0;
			}
			mode %= 6;
			led_moder(mode);
		}


		/*
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
