/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "core_clock.h"
#include "uart.h"
#include "adc.h"
#include "config.h"
#include "lcd.h"
#include "matrix_key.h"
#include "pwm.h"
#include "interrupt.h"
#include "flash.h"


#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

char pass[4] = {'1', '2', '3', '4'};
char new_pass[4] = {'1', '2', '3', '4'};
char checkpass[4];
int value[4] = {100, 5, 50, 8};// s1, t1, s2, t2
int new_value[4] = {100, 5, 50, 8};// s1, t1, s2, t2
float T = 25.0;

char Enter_Number(char *cache){
	int j = 8;
	char new = read_keypad();
	while ((new != '=') && (new != 'C')){
		new = read_keypad();
		if (new >= '0' && new <= '9'){
			LCD_PutChar(new);
			if (j<8) {
				for (int i = 1; i <= 8; i++){
					cache[i-1] = cache[i];
				}
			}
			cache[8] = new;
			j--;
		}
	}
	return new;
}

void Display_Data(void){
	LCD_Gotoxy(0,0);
	char buffer[25];
	int S1 = (int)value[0];
	int T1 = (int)value[1];
	int S2 = (int)value[2];
	int T2 = (int)value[3];
	sprintf(buffer, "%d, %d, %d, %d, %.2f", S1, T1, S2, T2, T);
	LCD_SendCommand(0x0C);
	LCD_Puts(buffer);
}

void TIM3_IRQHandler(void){
	if (TIM3_SR & (1 << 0)){
		T = calculate_temperature();
		char buffer1[20];
		int S1 = (int)value[0];
		int T1 = (int)value[1];
		int S2 = (int)value[2];
		int T2 = (int)value[3];
		sprintf(buffer1, "%d, %d, %d, %d, ", S1, T1, S2, T2);
		char buffer[10];
		int intPart = (int)T;
		int decimalPart = (int)((T - intPart) * 100);
		sprintf(buffer, "%d.%02d, \r\n", intPart, decimalPart);
		uart_sendstring(buffer1);
		uart_sendstring(buffer);
		TIM3_SR &= ~(1 << 0);
	}
}

int count = -1;
int x = 0;
void TIM4_IRQHandler(void){
	if (TIM4_SR & (1 << 0)){
		count ++;
		if (count == value[1]){
			GPIOA_ODR |= (1 << 4);
			GPIOA_ODR &= ~(1 << 5);
			TIM2_CCR1 = 1000 * (value[2] / 100);
		}
		if (count == (value[1] + value[3])){
			GPIOA_ODR |= (1 << 5);
			GPIOA_ODR &= ~(1 << 4);
			TIM2_CCR1 = 1000 * (value[0] / 100);
			count = 0;
		}
		TIM4_SR &= ~(1 << 0);
	}
}

int main(void)
{
	core_clock_config();
	uart2_config();
	uart2_gpio();
	adc_config();
	LCD_Init();
	matrix_key_init();
	pwm_init();
	Timer3_Init();
	Timer4_Init();
	Timer1_Init();
	GPIOA_ODR |= (1 << 5);//select direction of rotation
	GPIOA_ODR &= ~(1 << 4);//select direction of rotation
	TIM2_CCR1 = 1000 * (value[0] / 100);      // PWM
	TIM2_CR1 |= TIM2_CR1_CEN; // start Timer2
	TIM4_CR1 |= TIM4_CR1_CEN; // start Timer4
    /* Loop forever */
	Display_Data();
	while(1){
		//enter 'C' and '=' to go to password
		char data = read_keypad();
		if (data == 'C'){
			TIM1_CNT = 0;
			TIM1_CR1 |=  TIM1_CR1_CEN;
			TIM1_SR &= ~(1 << 0);
			char data = read_keypad();
			while ((!(TIM1_SR & (1 << 0))) && (data == 0x01)){
				data = read_keypad();
			}
			TIM1_CR1 &= ~TIM1_CR1_CEN;
			if (data == '='){

				//enter password
				LCD_SendCommand(0x0E);
				LCD_Clear();
				LCD_Gotoxy(0,0);
				LCD_Puts("Enter Password:");
				bool password = false;
				while (password == false){
					LCD_Gotoxy(0,1);
					int i = 0;
					while (i < 4){
						char entered_pass = read_keypad();
						if (entered_pass != 0x01){
							checkpass[i] = entered_pass;
							LCD_PutChar(entered_pass);
							LCD_Gotoxy(i+1,1);
							i++;
						}
					}
					if ((pass[0]==checkpass[0]) && (pass[1]==checkpass[1])
							&& (pass[2]==checkpass[2]) && (pass[3]==checkpass[3])){
						password = true;
					}
					else {
						LCD_Clear();
						LCD_Puts("incorrect, again:");
					}
				}

				//go to menu
				LCD_Menu(0);
				char new_data;
				int a = 0;
				while (new_data != '='){
					new_data = read_keypad();
					if ((a>=0) && (a<=1) && (new_data == 'X')){
						a++;
						LCD_Menu(a);
					}
					if ((a>=1) && (a<=2) && (new_data == '%')){
						a--;
						LCD_Menu(a);
					}
					if (new_data == '+'){
						if (a == 0){

							//change values of S1 and T1
							char cache[10] = {'0','0','0','0','0','0','0','0','0','\0'};
							char cache1[10] = {'0','0','0','0','0','0','0','0','0','\0'};
							LCD_Clear();
							LCD_Gotoxy(0,0);
							LCD_Puts("+ Enter new value:");
							LCD_Gotoxy(0,1);
							LCD_Puts("S1:");
							LCD_Gotoxy(0,2);
							LCD_Puts("T1:");
							LCD_Gotoxy(3,1);
							char new = read_keypad();

							while (1){
								new = Enter_Number(cache);
								if (new == '='){
									LCD_Gotoxy(3,2);
									new = Enter_Number(cache1);
									if (new == '=') {
										new_value[0] = atoi(cache);
										new_value[1] = atoi(cache1);
										LCD_Menu(a);
										break;
									}
								}

								if (new == 'C') {
									LCD_Menu(a);
									break;
								}
							}
						}
						else if (a == 1){

							//change values of S2, T2
							char cache[10] = {'0','0','0','0','0','0','0','0','0','\0'};
							char cache1[10] = {'0','0','0','0','0','0','0','0','0','\0'};
							LCD_Clear();
							LCD_Gotoxy(0,0);
							LCD_Puts("+ Enter new value:");
							LCD_Gotoxy(0,1);
							LCD_Puts("S2:");
							LCD_Gotoxy(0,2);
							LCD_Puts("T2:");
							LCD_Gotoxy(3,1);
							char new = read_keypad();

							while (1){
								new = Enter_Number(cache);
								if (new == '='){
									LCD_Gotoxy(3,2);
									new = Enter_Number(cache1);
									if (new == '=') {
										new_value[2] = atoi(cache);
										new_value[3] = atoi(cache1);
										LCD_Menu(a);
										break;
									}
								}
								if (new == 'C') {
									LCD_Menu(a);
									break;
								}
							}
						}
						else{

							//change password
							bool format = false;
							LCD_Clear();
							LCD_Gotoxy(0,0);
							LCD_Puts("Enter new password:");
							LCD_Gotoxy(0,1);
							while (format == false){
								char cache[10] = {'0','0','0','0','0','0','0','0','0','\0'};
								char new = read_keypad();
								new = Enter_Number(cache);
								if (new == '='){
									if (cache[4] == '0'){
										new_pass[0] = cache[5];
										new_pass[1] = cache[6];
										new_pass[2] = cache[7];
										new_pass[3] = cache[8];
										LCD_Menu(a);
										format = true;
									}
									else{
										LCD_Clear();
										LCD_Gotoxy(0,0);
										LCD_Puts("Enter password again");
										LCD_Gotoxy(0,1);
										LCD_Puts("(only 4 characters!)");
										LCD_Gotoxy(0,2);
									}
								}
								if (new == 'C') LCD_Menu(a);
							}
						}
					}
				}
				if (new_data == '=') {
					//save to flash memory
					LCD_Clear();
					LCD_Gotoxy(0,0);
					LCD_Puts("Save the old values");
					LCD_Gotoxy(0,1);
					LCD_Puts("to flash memory:");
					LCD_Gotoxy(0,2);
					LCD_Puts("1: Save");
					LCD_Gotoxy(0,3);
					LCD_Puts("2: Do not save");
					while ((new_data != '1') && (new_data != '2')){
						new_data = read_keypad();
					}
					if (new_data == '1') {
						char buffer[25];
						int S1 = (int)value[0];
						int T1 = (int)value[1];
						int S2 = (int)value[2];
						int T2 = (int)value[3];
						sprintf(buffer, "%d, %d, %d, %d, %.2f", S1, T1, S2, T2, T);
						Flash_WriteString(0x0800FC00 + 25 * x, buffer);
						x ++;
					}
					value[0] = new_value[0];
					value[1] = new_value[1];
					value[2] = new_value[2];
					value[3] = new_value[3];
					pass[0] = new_pass[0];
					pass[1] = new_pass[1];
					pass[2] = new_pass[2];
					pass[3] = new_pass[3];
				}
				LCD_Clear();
			}
		}
		Display_Data();
	}

}

