/*
 * systick.c
 *
 *  Created on: Mar 27, 2025
 *      Author: P.HIEU
 */

#include "systick.h"

volatile uint32_t usTicks = 0;

void SysTick_Inint(void){
	SYST_RVR = 7;//reload = 8-1 (1us with clock 8MHz)
	SYST_CVR = 0;
	SYST_CSR = 0;
	SYST_CSR |= SYST_CSR_TICKINT; //enable systick interrupt
	SYST_CSR |= SYST_CSR_CLKSOURCE; //clock = AHB = 8MHz
	SYST_CSR |= SYST_CSR_ENABLE;//enable systick
}

void SysTick_Handler(void){
	if (usTicks>0){
		usTicks--;
	}
	if (usTicks == 0){
		SYST_CSR &= ~SYST_CSR_ENABLE;//Disable Systick after Done
	}
}

void Delay_us (uint32_t us){
	usTicks = us;
	SYST_CVR = 0;
	SYST_CSR |= SYST_CSR_ENABLE;
	while(usTicks);
}

void Delay_ms (uint32_t ms){
	Delay_us(ms * 1000);
}

