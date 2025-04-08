/*
 * config.h
 *
 *  Created on: Mar 21, 2025
 *      Author: P.HIEU
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include "stdint.h"
// Define base addresses for peripherals
#define AHB_BASE_ADDR 0x40018000
#define APB1_BASE_ADDR 0x40000000
#define APB2_BASE_ADDR 0x40010000

//define RCC
#define RCC_BASE_ADDR    0x40021000
#define RCC_CR           (*(volatile uint32_t *)(RCC_BASE_ADDR + 0x00))
#define RCC_CFGR         (*(volatile uint32_t *)(RCC_BASE_ADDR + 0x04))
#define RCC_AHBENR       (*(volatile uint32_t *)(RCC_BASE_ADDR + 0x14))
#define RCC_APB2ENR      (*(volatile uint32_t *)(RCC_BASE_ADDR + 0x18))
#define RCC_APB1ENR      (*(volatile uint32_t *)(RCC_BASE_ADDR + 0x1C))
//define bit in RCC
#define RCC_CR_HSION     (1 << 0)
#define RCC_CR_HSIRDY    (1 << 1)
// SYSCLK = 8MHz
#define RCC_CFGR_SW      (0 << 0)
#define RCC_CFGR_SWS     (0 << 2)

#define RCC_APB2ENR_IOPAEN  (1 << 2)
#define RCC_APB1ENR_USART2EN (1 << 17)
#define RCC_APB2ENR_ADC1EN  (1 << 9)
#define RCC_APB2ENR_IOPBEN  (1 << 3)
#define RCC_APB1ENR_I2C1EN  (1 << 21)
#define RCC_APB1ENR_TIM2EN  (1 << 0)
#define RCC_APB1ENR_TIM3EN  (1 << 1)
#define RCC_APB1ENR_TIM4EN  (1 << 2)
#define RCC_APB2ENR_TIM1EN  (1 << 11)

//USART2
#define USART2_BASE      (APB1_BASE_ADDR + 0x4400)
#define USART2_SR        (*(volatile uint32_t *)(USART2_BASE + 0x00))
#define USART2_DR        (*(volatile uint32_t *)(USART2_BASE + 0x04))
#define USART2_BRR       (*(volatile uint32_t *)(USART2_BASE + 0x08))
#define USART2_CR1       (*(volatile uint32_t *)(USART2_BASE + 0x0C))
#define USART2_CR2       (*(volatile uint32_t *)(USART2_BASE + 0x10))
#define USART2_CR3       (*(volatile uint32_t *)(USART2_BASE + 0x14))
//define bit in USART2
//Configure Baudrate = 9600
//PCLK1 = 8 MHz, (oversampling 16)
//USARTDIV = f_ck / (16 * Baudrate) = 8,000,000 / (16 * 9600) = 52.083
//DIV_Mantissa = 52 (0x34), DIV_Fraction = 1.33 = 1 (0x1)
#define USART2_BRR_DIV_Mantissa  (52 << 4)
#define USART2_BRR_DIV_Fraction  (1 << 0)
//configure bit in USART_CR1
#define USART_CR1_UE    (1 << 13)
#define USART_CR1_TE    (1 << 3)
#define USART_CR1_RE    (1 << 2)
//configure bit in USART_CR2
#define USART_CR2_STOP_1BIT (0 << 12)
//configure bit in USART_SR
#define USART_SR_TXE    (1 << 7)
#define USART_SR_TC     (1 << 6)
#define USART_SR_RXNE   (1 << 5)

//GPIOA
#define GPIOA_BASE       (APB2_BASE_ADDR + 0x0800)
#define GPIOA_CRL        (*(volatile uint32_t *)(GPIOA_BASE + 0x00))
#define GPIOA_CRH        (*(volatile uint32_t *)(GPIOA_BASE + 0x04))
#define GPIOA_ODR        (*(volatile uint32_t *)(GPIOA_BASE + 0x0C))
//define bit in GPIOA
#define GPIO_CRL_CNF_MODE_2    10
#define GPIO_CRL_CNF_MODE_3    4
#define GPIO_CRL_CNF_MODE_1    0

//ADC1
#define ADC1_BASE        (APB2_BASE_ADDR + 0x2400)
#define ADC1_SR          (*(volatile uint32_t *)(ADC1_BASE + 0x00))
#define ADC1_CR1         (*(volatile uint32_t *)(ADC1_BASE + 0x04))
#define ADC1_CR2         (*(volatile uint32_t *)(ADC1_BASE + 0x08))
#define ADC1_SMPR1       (*(volatile uint32_t *)(ADC1_BASE + 0x0C))
#define ADC1_SMPR2       (*(volatile uint32_t *)(ADC1_BASE + 0x10))
#define ADC1_SQR1        (*(volatile uint32_t *)(ADC1_BASE + 0x2C))
#define ADC1_SQR3        (*(volatile uint32_t *)(ADC1_BASE + 0x34))
#define ADC1_DR          (*(volatile uint32_t *)(ADC1_BASE + 0x4C))
//define bit in ADC
#define ADC_CR2_ADON     (1 << 0)//enable ADC
#define ADC_CR2_SWSTART  (1 << 22)// starts conversion of regular channels
#define ADC_SR_EOC       (1 << 1)// end of conversion
#define ADC_SQR1_L       (0 << 20) //1 conversion
#define ADC_SQR3_SQ1     (1 << 0)// channel 1: ADC1_IN1
#define ADC_SMPR2_SMP1   (3 << 3)//channel 1: 28.5 cycles
#define ADC_CR2_CONT     (1 << 1)
#define ADC_CR2_EXTSEL   (7 << 17)

//define for calculating temperature
#define R0    10000
#define R1    10000
#define beta  3380
#define T0    25
#define Vcc   3.3

//GPIOB
#define GPIOB_BASE       (APB2_BASE_ADDR + 0x0C00)
#define GPIOB_CRL        (*(volatile uint32_t *)(GPIOB_BASE + 0x00))
#define GPIOB_IDR        (*(volatile uint32_t *)(GPIOB_BASE + 0x08))
#define GPIOB_ODR        (*(volatile uint32_t *)(GPIOB_BASE + 0x0C))
//define bit in GPIOB
#define GPIOB_CRL_CNF_MODE_6    14
#define GPIOB_CRL_CNF_MODE_7    14

//I2C1
#define I2C1_BASE        (APB1_BASE_ADDR + 0x5400)
#define I2C1_CR1         (*(volatile uint32_t *)(I2C1_BASE + 0x00))
#define I2C1_CR2         (*(volatile uint32_t *)(I2C1_BASE + 0x04))
#define I2C1_DR          (*(volatile uint32_t *)(I2C1_BASE + 0x10))
#define I2C1_SR1         (*(volatile uint32_t *)(I2C1_BASE + 0x14))
#define I2C1_SR2         (*(volatile uint32_t *)(I2C1_BASE + 0x18))
#define I2C1_CCR         (*(volatile uint32_t *)(I2C1_BASE + 0x1C))
#define I2C1_TRISE       (*(volatile uint32_t *)(I2C1_BASE + 0x20))
//define bit in I2C1
#define I2C1_CR1_PE      (1 << 0)

#define I2C1_CR2_FREQ    (8 << 0)//8MHz
#define I2C1_CCR_CCR     (40 << 0)//standard mode(100kHz)
#define I2C1_TRISE_TRISE (0x9 << 0)
#define LCD_I2C_ADDR     0x4E


//TIM2
#define TIM2_BASE        (APB1_BASE_ADDR + 0x0000)
#define TIM2_CR1         (*(volatile uint32_t *)(TIM2_BASE + 0x00))
#define TIM2_CCMR1       (*(volatile uint32_t *)(TIM2_BASE + 0x18))
#define TIM2_CCER        (*(volatile uint32_t *)(TIM2_BASE + 0x20))
#define TIM2_PSC         (*(volatile uint32_t *)(TIM2_BASE + 0x28))
#define TIM2_ARR         (*(volatile uint32_t *)(TIM2_BASE + 0x2C))
#define TIM2_CCR1        (*(volatile uint32_t *)(TIM2_BASE + 0x34))
#define TIM2_CR1         (*(volatile uint32_t *)(TIM2_BASE + 0x00))

#define TIM2_CCMR1_OC1PE (1 << 3)
#define TIM2_CCER_CC1E   (1 << 0)
#define TIM2_CR1_CEN     (1 << 0)
#define TIM2_CCMR1_OC1M_Pos (6 << 4)


//TIM3
#define TIM3_BASE        (APB1_BASE_ADDR + 0x0400)
#define TIM3_CR1         (*(volatile uint32_t *)(TIM3_BASE + 0x00))
#define TIM3_CCMR1       (*(volatile uint32_t *)(TIM3_BASE + 0x18))
#define TIM3_CCER        (*(volatile uint32_t *)(TIM3_BASE + 0x20))
#define TIM3_CNT         (*(volatile uint32_t *)(TIM3_BASE + 0x24))
#define TIM3_PSC         (*(volatile uint32_t *)(TIM3_BASE + 0x28))
#define TIM3_ARR         (*(volatile uint32_t *)(TIM3_BASE + 0x2C))
#define TIM3_CCR1        (*(volatile uint32_t *)(TIM3_BASE + 0x34))
#define TIM3_CR1         (*(volatile uint32_t *)(TIM3_BASE + 0x00))
#define TIM3_SR          (*(volatile uint32_t *)(TIM3_BASE + 0x10))
#define TIM3_DIER        (*(volatile uint32_t *)(TIM3_BASE + 0x0C))

#define TIM3_DIER_UIE    (1 << 0)
#define TIM3_CR1_CEN     (1 << 0)

//TIM1
#define TIM1_BASE        (APB2_BASE_ADDR + 0x2C00)
#define TIM1_CNT         (*(volatile uint32_t *)(TIM1_BASE + 0x24))
#define TIM1_PSC         (*(volatile uint32_t *)(TIM1_BASE + 0x28))
#define TIM1_ARR         (*(volatile uint32_t *)(TIM1_BASE + 0x2C))
#define TIM1_CR1         (*(volatile uint32_t *)(TIM1_BASE + 0x00))
#define TIM1_SR          (*(volatile uint32_t *)(TIM1_BASE + 0x10))

#define TIM1_CR1_CEN     (1 << 0)


//TIM4
#define TIM4_BASE        (APB1_BASE_ADDR + 0x0800)
#define TIM4_CR1         (*(volatile uint32_t *)(TIM4_BASE + 0x00))
#define TIM4_CCMR1       (*(volatile uint32_t *)(TIM4_BASE + 0x18))
#define TIM4_CCER        (*(volatile uint32_t *)(TIM4_BASE + 0x20))
#define TIM4_CNT         (*(volatile uint32_t *)(TIM4_BASE + 0x24))
#define TIM4_PSC         (*(volatile uint32_t *)(TIM4_BASE + 0x28))
#define TIM4_ARR         (*(volatile uint32_t *)(TIM4_BASE + 0x2C))
#define TIM4_CCR1        (*(volatile uint32_t *)(TIM4_BASE + 0x34))
#define TIM4_CR1         (*(volatile uint32_t *)(TIM4_BASE + 0x00))
#define TIM4_SR          (*(volatile uint32_t *)(TIM4_BASE + 0x10))
#define TIM4_DIER        (*(volatile uint32_t *)(TIM4_BASE + 0x0C))

#define TIM4_DIER_UIE    (1 << 0)
#define TIM4_CR1_CEN     (1 << 0)


//interrupt
#define EXTI_BASE        (APB2_BASE_ADDR + 0x0400)
#define EXTI_IMR         (*(volatile uint32_t *)(EXTI_BASE + 0x00))
#define EXTI_SWIER       (*(volatile uint32_t *)(EXTI_BASE + 0x10))
#define EXTI_PR          (*(volatile uint32_t *)(EXTI_BASE + 0x14))

#define NVIC_BASE        0xE000E100
#define NVIC_ISER0       (*(volatile uint32_t *)(NVIC_BASE + 0x00))
#define NVIC_ISER1       (*(volatile uint32_t *)(NVIC_BASE + 0x02))
#define NVIC_ICPR0       (*(volatile uint32_t *)(NVIC_BASE + 0x180))
#define NVIC_IPR7        (*(volatile uint32_t *)(NVIC_BASE + 0x300 + 0xE))
#define NVIC_IPR12       (*(volatile uint32_t *)(NVIC_BASE + 0x300 + 0x30))

//systick
#define SYST_BASE        0xE000E010
#define SYST_CSR         (*(volatile uint32_t *)(SYST_BASE + 0x00))
#define SYST_RVR         (*(volatile uint32_t *)(SYST_BASE + 0x04))
#define SYST_CVR         (*(volatile uint32_t *)(SYST_BASE + 0x08))

#define SYST_CSR_COUNTFLAG  (1 << 16)
#define SYST_CSR_CLKSOURCE  (1 << 2)
#define SYST_CSR_TICKINT    (1 << 1)
#define SYST_CSR_ENABLE     (1 << 0)


//flash
#define FLASH_BASE       0x40022000
#define FLASH_ACR        (*(volatile uint32_t *)(FLASH_BASE + 0x00))
#define FLASH_KEYR       (*(volatile uint32_t *)(FLASH_BASE + 0x04))
#define FLASH_OPTKEYR    (*(volatile uint32_t *)(FLASH_BASE + 0x08))
#define FLASH_SR         (*(volatile uint32_t *)(FLASH_BASE + 0x0C))
#define FLASH_CR         (*(volatile uint32_t *)(FLASH_BASE + 0x10))
#define FLASH_AR         (*(volatile uint32_t *)(FLASH_BASE + 0x14))
#define FLASH_OBR        (*(volatile uint32_t *)(FLASH_BASE + 0x1C))
#define FLASH_WRPR       (*(volatile uint32_t *)(FLASH_BASE + 0x20))

#define FLASH_KEY1       0x45670123
#define FLASH_KEY2       0xCDEF89AB
#define FLASH_ACR_LATENCY (7 << 0)
#define FLASH_SR_BSY     (1 << 0)
#define FLASH_CR_LOCK    (1 << 7)
#define FLASH_CR_PG      (1 << 0)
#define FLASH_CR_PER     (1 << 1)
#define FLASH_CR_STRT    (1 << 6)









#endif /* CONFIG_H_ */

