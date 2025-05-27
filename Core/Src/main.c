#include "../../Drivers/CMSIS/Device/stm32f103xb.h"

/*
 * Enable Port C clock
 * Set PC13 as output
 * Clear PC13
 * Set PC13 HIGH
 * Delay
 * Set PC13 LOW
 * Delay
*/

void delay(uint16_t t) {
    for (uint16_t i=0; i<t; i++) {

    }
}

int main(void){
    // Enable Port C clock
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
    // Clear PC13
    GPIOC->CRH &= ~(GPIO_CRH_CNF13 | GPIO_CRH_MODE13);
    // Set PC13 as output
    // GPIO_CRH_CNF13 already cleared to 00 for General purpose output push-pull
    GPIOC->CRH |= GPIO_CRH_MODE13_1; // Output - 2 MHz note: _1 sets the 1st bit while _0 sets the 0th bit
    

    while(1){
        // Set PC13 HIGH
        GPIOC->ODR |= GPIO_ODR_ODR13;
        delay(65534);
        // Set PC13 LOW
        GPIOC->ODR &= ~GPIO_ODR_ODR13;
        delay(65534);
        // XOR Alternative
        // GPIOC->ODR ^= GPIO_ODR_ODR13;
        // delay(65534);
    }
}
