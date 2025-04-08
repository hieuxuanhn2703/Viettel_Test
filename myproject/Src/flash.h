/*
 * flash.h
 *
 *  Created on: Mar 30, 2025
 *      Author: P.HIEU
 */

#ifndef FLASH_H_
#define FLASH_H_

#include <stdint.h>
#include <string.h>
#include "config.h"

void Flash_Unlock(void);

void Flash_Lock(void);

void Flash_ErasePage(uint32_t page);

void Flash_Write(uint32_t address, uint16_t data);

void Flash_WriteString(uint32_t address, const char* str);

#endif /* FLASH_H_ */
