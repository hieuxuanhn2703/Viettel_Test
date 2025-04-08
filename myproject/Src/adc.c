/*
 * adc.c
 *
 *  Created on: Mar 22, 2025
 *      Author: P.HIEU
 */

#include "adc.h"

void adc_config(void){
	// turn on clock for GPIOA and ADC1
	RCC_APB2ENR |= RCC_APB2ENR_IOPAEN;

	//configure PA1 to analog mode
	GPIOA_CRL &= ~(0xF << (1 * 4));
	GPIOA_CRL |= (GPIO_CRL_CNF_MODE_1 << (1 * 4));

	ADC1_CR2 |= ADC_CR2_EXTSEL;
	RCC_APB2ENR |= RCC_APB2ENR_ADC1EN;
	//configure ADC1
	ADC1_SMPR2 |= ADC_SMPR2_SMP1;
	ADC1_SQR1 |= ADC_SQR1_L;
	ADC1_SQR3 |= ADC_SQR3_SQ1;
//	ADC1_CR2 |= ADC_CR2_CONT;
	ADC1_CR2 |= ADC_CR2_ADON;
	for (volatile int i = 0; i < 10000; i++);
	ADC1_CR2 |= ADC_CR2_ADON;
}
uint16_t adc_read(void){
	ADC1_CR2 |= ADC_CR2_ADON;
	ADC1_CR2 |= ADC_CR2_SWSTART;
	while(!(ADC1_SR & ADC_SR_EOC));
	return ADC1_DR;
}
float calculate_temperature(void){
	uint16_t adc_value = adc_read();
	float Vout = (float)(adc_value * Vcc) / 4095;
	float Rntc = (R1 * (Vcc - Vout)) / Vout;
	float T = 1 / ((log(Rntc/R0) / beta) + (1 / (T0 + 273.15)));
	return T - 273.15;
}
