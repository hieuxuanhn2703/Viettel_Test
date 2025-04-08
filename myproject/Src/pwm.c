/*
 * pwm.c
 *
 *  Created on: Mar 26, 2025
 *      Author: P.HIEU
 */
#include "pwm.h"

void pwm_init(void) {

    RCC_APB1ENR |= RCC_APB1ENR_TIM2EN;  // turn on clock for TIM2
    RCC_APB2ENR |= RCC_APB2ENR_IOPAEN; // turn on clock for GPIOA

    //configure GPIO
    GPIOA_CRL &= ~(0xF << (0 * 4)); // delete old configuration
    GPIOA_CRL |= (0x9 << (0 * 4));  // setup PA0 (AF Push-Pull, max speed 50MHz)

    //configure TIM2
    TIM2_PSC = 160 - 1;    // divide clock into 50kHz
    TIM2_ARR = 1000 - 1;  // (frequency: PWM = 50Hz)
//    TIM2_CCR1 = 1000;      // PWM: 100%

    //Select mode
    TIM2_CCMR1 |= TIM2_CCMR1_OC1M_Pos; // PWM: 1
    TIM2_CCMR1 |= TIM2_CCMR1_OC1PE; // turn on preload (CC1 is updated when CCR1register is reconfigure)

   // turn on PWM
    TIM2_CCER |= TIM2_CCER_CC1E; // turn on PWM in CC1 channel

    //start Timer
//    TIM2_CR1 |= TIM2_CR1_CEN;
}

