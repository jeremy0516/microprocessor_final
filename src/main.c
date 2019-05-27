#include "stm32l476xx.h"
#include "helper_functions.h"
#include "7seg.h"
#include "keypad.h"
#include "led_button.h"
#include "timer.h"
#include "hc_sr04.h"
#include "beeper.h"

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
#define LED_pin 0

// Define pins for button (default use on-board button PC13)
#define BUTTON_gpio GPIOC
#define BUTTON_pin 13

// Define pins for motor
#define MOTOR_gpio GPIOA
#define MOTOR_pin 1
#define MOTORGD_gpio GPIOA
#define MOTORGD_pin 4

#define ROTOR_gpio GPIOB
#define ROTOR_pin 8
#define ROTORGD_gpio GPIOB
#define ROTORGD_pin 9

#define TRIG_gpio GPIOC
#define TRIG_pin 1
#define ECHO_gpio GPIOC
#define ECHO_pin 2


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
		FPU_init();
		SystemClock_Config(10);

		int motion=1;	//motion=1	forward ; motion=0	stop ; motion=-1  backward
		double distance_cm = 0.0;

		if(init_led(LED_gpio, LED_pin) != 0){
			return -1;
		}
		if(init_led(MOTOR_gpio, MOTOR_pin) != 0){
			return -1;
		}
		if(init_led(MOTORGD_gpio, MOTORGD_pin) != 0){
			return -1;
		}
		if(init_led(ROTOR_gpio, ROTOR_pin) != 0){
			return -1;
		}
		if(init_led(ROTORGD_gpio, ROTORGD_pin) != 0){
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
		/*
		if(motion==1){
			set_gpio(MOTOR_gpio, MOTOR_pin);
			reset_gpio(MOTORGD_gpio, MOTORGD_pin);
			set_gpio(ROTOR_gpio, ROTOR_pin);
			reset_gpio(ROTORGD_gpio, ROTORGD_pin);

		}
		else if(motion==-1){
			reset_gpio(MOTOR_gpio, MOTOR_pin);
			set_gpio(MOTORGD_gpio, MOTORGD_pin);
			reset_gpio(ROTOR_gpio, ROTOR_pin);
			set_gpio(ROTORGD_gpio, ROTORGD_pin);
		}
		else{
			reset_gpio(MOTOR_gpio, MOTOR_pin);
			reset_gpio(MOTORGD_gpio, MOTORGD_pin);
			reset_gpio(ROTOR_gpio, ROTOR_pin);
			reset_gpio(ROTORGD_gpio, ROTORGD_pin);
		}
		*/

		distance_cm = get_distance();

		display_two_decimal(SEG_gpio, DIN_pin, CS_pin, CLK_pin, distance_cm);
		//wait(1);


		if ((distance_cm <= 20) && (distance_cm >= 10)){
			sound(587);
			wait(0.5);
		}

		else if (distance_cm <= 10){
			sound(787);
			wait(0.001);
		}

		//sound(587);

	}
	return 0;
}
