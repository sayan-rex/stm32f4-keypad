#include "stm32f4xx.h"
#include "keypad.h"

const char keymap[4][3] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'},
    {'*','0','#'}
};

void keypad_init(void) {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;

    // Rows (PD0–PD3) inputs with pull-up
    GPIOD->MODER &= ~(0xFF << 0);
    GPIOD->PUPDR &= ~(0xFF << 0);
    GPIOD->PUPDR |=  (0x55 << 0); // Pull-up

    // Columns (PD4–PD6) outputs
    GPIOD->MODER &= ~(0x3F << 8);
    GPIOD->MODER |=  (0x15 << 8);
    GPIOD->OTYPER &= ~(0x7 << 4);
}

char keypad_getkey(void) {
    for (int col = 0; col < 3; col++) {
        GPIOD->ODR |= (0x7 << 4);               // All high
        GPIOD->ODR &= ~(1 << (4 + col));        // Set one low

        for (int row = 0; row < 4; row++) {
            if (!(GPIOD->IDR & (1 << row))) {
                while (!(GPIOD->IDR & (1 << row))); // Wait for release
                return keymap[row][col];
            }
        }
    }
    return 0;
}
