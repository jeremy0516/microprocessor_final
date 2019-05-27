#include "stm32l476xx.h"
#include "helper_functions.h"
#include "7seg.h"
#include "keypad.h"
#include "led_button.h"
#include "timer.h"
#include "beeper.h"


// Define pins for 7seg
#define SEG_gpio GPIOC
#define DIN_pin 3
#define CS_pin 4
#define CLK_pin 5


// Define pins for keypad
#define COL_gpio GPIOA
#define COL_pin 6       // 6 7 8 9
#define ROW_gpio GPIOB
#define ROW_pin 3       // 3 4 5 6


// Define pins for led (default use on-board led PA5)
#define LED_gpio GPIOA
#define LED_pin 5


// Define pins for button (default use on-board button PC13)
#define BUTTON_gpio GPIOC
#define BUTTON_pin 13


// Define Counter timer
#define COUNTER_timer TIM2


#define BEEPER_gpio GPIOA
#define BEEPER_pin 1
// Buzzer is fixed to PA0 due to its need for PWM signal
// Can change to other ports if needed, but need to look up the reference


// Use to decide which part of the code will run
// Use define & ifdef to control
#define lab_modify_system_clock
//#define lab_counter
//#define lab_music_keyboard
//#define lab_music_song


// make beeper can buzzer at a specific frequency.
void sound(int frequency){
        // Cause we want to use floating points we need to init FPU
    FPU_init();
    GPIO_init_AF();
    init_led(BEEPER_gpio,BEEPER_pin);
    timer_enable(TIM2);
    timer_init(TIM2,1,20);
    PWM_channel_init();
    timer_start(TIM2);
    //int freq[7]={523,587,659,698,784,880,988};
    int state=0;

    timer_init(TIM2,40,50000/frequency);
    timer_start(COUNTER_timer);

    for(int i=0;i<20000;i++){
        if(COUNTER_timer->CNT==0){
            if(state==0){
                set_gpio(BEEPER_gpio,BEEPER_pin);
            }
            if(state==1){
                reset_gpio(BEEPER_gpio,BEEPER_pin);
            }
            state=!state;
        }
    }
}
