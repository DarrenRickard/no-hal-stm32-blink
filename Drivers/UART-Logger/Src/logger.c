/*
 * FT232RL as UART Bridge
 * STM32F103C8 as MCU
 * PA9 (TX1)
 * PA10 (RX1) optional for sending data to MCU
 */
#include "logger.h"
#include "../../CMSIS/Device/stm32f103xb.h"

uint32_t const CLK_RATE = 72000000;
uint16_t const BAUD_RATE = 115200;

void uart1_init(void){
    // Enable clock for PortA and USART1
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    // Configure PA9 as alternate function push-pull @ 50 MHz
    GPIOA->CRH &= ~(2 << GPIO_CRH_MODE9 | 2 << GPIO_CRH_CNF9);
    GPIOA->CRH |= (2 << GPIO_CRH_MODE9 | 3 << GPIO_CRH_CNF9);
    // Set USART1 baud rate
    USART1->BRR = $(CLK_RATE) / $(BAUD_RATE);
    // Enable TX and USART
    USART1->CR1 = (1 << USART_CR1_TE | 1 << USART_CR1_UE);
}

// Define UART1_send_char and UART1_send_string
void uart1_send_char(char c) {
    while (!(USART1->SR & USART_SR_TXE));
    USART1->DR = c;
}

void uart1_send_string(const char *str) {
    while (*str) {
        uart1_send_char(*str++);
    }
}
