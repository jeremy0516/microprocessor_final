#include "stm32l476xx.h"
#include "helper_functions.h"
#include "led_button.h"
#include "timer.h"
#include "beeper.h"

// Define Counter timer
#define BEEPER_gpio GPIOA
#define BEEPER_pin 0

// make beeper can buzzer at a specific frequency.
void beep(int frequency){
        // Cause we want to use floating points we need to init FPU
    FPU_init();
    GPIO_init_AF();
    init_led(BEEPER_gpio, BEEPER_pin);
    timer_enable(TIM2);
    timer_init(TIM2,1,20);
    PWM_channel_init();
    timer_start(TIM2);
    //int freq[7]={523,587,659,698,784,880,988};
    int state=0;

    timer_init(TIM2,40,50000/frequency);
    timer_start(TIM2);

    for(int i=0;i<20000;i++){
        if(TIM2->CNT==0){
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
