/*
 * systick.h
 *
 *  Created on: Mar 27, 2025
 *      Author: P.HIEU
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

#include "config.h"
#include <stdint.h>

void SysTick_Inint(void);

void SysTick_Handler(void);

void Delay_us (uint32_t us);

void Delay_ms (uint32_t ms);

#endif /* SYSTICK_H_ */
