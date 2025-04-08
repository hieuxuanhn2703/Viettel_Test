/*
 * core_clock.c
 *
 *  Created on: Mar 21, 2025
 *      Author: P.HIEU
 */
#include "core_clock.h"

void core_clock_config(void){
	//Enable HSI
	RCC_CR |= RCC_CR_HSION;
	while (!(RCC_CR & RCC_CR_HSIRDY));
	//Configure HSI as Sysclk, HCLK = 8mhz
	RCC_CFGR &= ~(3 << 0 | 0xF << 4 | 7 << 8 | 7 << 11); //clear SW and HPRE and PPRE1
	RCC_CFGR |= RCC_CFGR_SW; // SW = 00: HSI as sysclk
	while ((RCC_CFGR & (3 << 2)) != RCC_CFGR_SWS); // wait for SWS = 00
}

