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

////// pins that had been used. //////
// PA : 0¡B6¡B7¡B8¡B9¡B10
// PB : 4¡B5¡B6¡B7¡B8¡B9¡B10¡B11
// PC : 0¡B1¡B3¡B4¡B5¡B13
////// pins that had been used. //////

// Define pins for 7seg
#define SEG_gpio GPIOC
#define DIN_pin 3
#define CS_pin 4
#define CLK_pin 5

// Define pins for hc_sr04
#define TRIG_gpio GPIOC
#define TRIG_pin 0
#define ECHO_gpio GPIOC
#define ECHO_pin 1
#define L_TRIG_gpio GPIOC
#define L_TRIG_pin 6
#define L_ECHO_gpio GPIOC
#define L_ECHO_pin 7
#define R_TRIG_gpio GPIOC
#define R_TRIG_pin 8
#define R_ECHO_gpio GPIOC
#define R_ECHO_pin 9

int main(){
	int mode = 0;                 // 8 modes.
	int button_press = 0;         // button_press=0 => not pressed.      button_press=1 => pressed.
	int state = 0;                // state=0 => no need to turn.    state>=1 => need to turn.
	double distance_cm = 0.0;
	double distance_cm_L = 0.0;
	double distance_cm_R = 0.0;

	while(1){
		// initialize.
		if(initialize() != 0){
			return -1;
		};

		// LED mode change.
		button_press = user_press_button(100);
		if (button_press == 1){
			mode++;
		}
		mode = mode % 8;
		led_moder(mode);

		// get the distance & show it.
		distance_cm = get_distance(TRIG_gpio, TRIG_pin, ECHO_gpio, ECHO_pin);
		distance_cm_L = get_distance(L_TRIG_gpio, L_TRIG_pin, L_ECHO_gpio, L_ECHO_pin);
		distance_cm_R = get_distance(R_TRIG_gpio, R_TRIG_pin, R_ECHO_gpio, R_ECHO_pin);
		display_two_decimal(SEG_gpio, DIN_pin, CS_pin, CLK_pin, distance_cm);
		wait(0.01);       //make a delay in order to make the number on monitor looking good.

		// make the buzzer beep.
		if ((distance_cm <= 30) && (distance_cm >= 25)){
			for (int i = 0; i < 10; i++){
				beep(387);
				wait(0.001);
			}
		}
		else if ((distance_cm <= 25) && (distance_cm >= 20)){
			for (int i = 0; i < 10; i++){
				beep(587);
				wait(0.001);
			}
		}
		else if (distance_cm <= 20){
			for (int i = 0; i < 10; i++){
				beep(787);
				wait(0.001);
			}
		}

		// determine which state according to hc_sr04's callback.
		if ((distance_cm <= 20) && (distance_cm >= 15)){
			state = 1;
		}
		else if ((distance_cm <= 15) && (distance_cm >= 10)){
			state = 2;
		}
		else if (distance_cm <= 10){
			state = 3;
		}
		else{
			state = 0;
		}

		// obstacle avoidance.
		if (state == 0){
			forward();
			wait(0.1);
			stop_forward();
			wait(0.3);
		}
		if ((state == 1) || (state == 2)){
			stop_forward();
		}
		if ((state == 1) || (state == 2) || (state == 3)){
			if (distance_cm_L >= distance_cm_R){
				CCW_turn();
			}
			if (distance_cm_L < distance_cm_R){
				CW_turn();
			}
		}
		if (distance_cm_L <= 10.2){
			CW_turn();
		}
		if (distance_cm_R <= 10.2){
			CCW_turn();
		}
	}
	return 0;
}
