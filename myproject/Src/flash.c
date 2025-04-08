/*
 * flash.c
 *
 *  Created on: Mar 30, 2025
 *      Author: P.HIEU
 */

#include "flash.h"

void Flash_Unlock(void){
	if (FLASH_CR & FLASH_CR_LOCK){
		FLASH_KEYR = FLASH_KEY1;
		FLASH_KEYR = FLASH_KEY2;
		while(FLASH_CR & FLASH_CR_LOCK);
	}
}

void Flash_Lock(void){
	FLASH_CR |= FLASH_CR_LOCK;
}

void Flash_ErasePage(uint32_t page){
	while(FLASH_CR & FLASH_CR_LOCK);
	FLASH_CR |= FLASH_CR_PER;
	FLASH_AR = page;
	FLASH_CR |= FLASH_CR_STRT;
	while(FLASH_SR & FLASH_SR_BSY);
	FLASH_CR &= ~FLASH_CR_PER;
}

void Flash_Write(uint32_t address, uint16_t data){
	while(FLASH_CR & FLASH_CR_LOCK);
	FLASH_CR |= FLASH_CR_PG;
	*(volatile uint16_t *)address = data;
	while(FLASH_SR & FLASH_SR_BSY);
	FLASH_CR &= ~FLASH_CR_PG;
}

void Flash_WriteString(uint32_t address, const char* str) {
	FLASH_ACR &= ~FLASH_ACR_LATENCY;
    uint16_t data;
    uint32_t i;
    uint32_t len = strlen(str) + 1;

    Flash_Unlock();
    Flash_ErasePage(address);

    for (i = 0; i < len; i += 2) {
        data = str[i] | (str[i + 1] << 8);
        Flash_Write(address + i, data);
    }

    Flash_Lock();
}
