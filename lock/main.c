#include "stm32f4xx.h"
#include "keypad.h"

void delay_ms(uint32_t ms);

int main(void) {
    keypad_init();

    // Enable LED GPIOs
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    GPIOD->MODER |= (1 << (12*2)) | (1 << (13*2)); // PD12, PD13 as output

    const char password[] = "1234";
    char entered[5] = {0};
    int index = 0;

    while (1) {
        char key = keypad_getkey();
        if (key) {
            entered[index++] = key;

            if (index == 4) {
                entered[4] = '\0';
                if (strcmp(entered, password) == 0) {
                    // Correct password
                    GPIOD->ODR |= (1 << 12);  // Green LED ON
                    GPIOD->ODR &= ~(1 << 13); // Red LED OFF
                } else {
                    // Wrong password
                    GPIOD->ODR |= (1 << 13);  // Red LED ON
                    GPIOD->ODR &= ~(1 << 12); // Green LED OFF
                }
                index = 0;
                delay_ms(1000);
                GPIOD->ODR &= ~(1 << 12); // turn off both
                GPIOD->ODR &= ~(1 << 13);
            }
        }
    }
}

void delay_ms(uint32_t ms) {
    for (uint32_t i = 0; i < ms * 16000; i++) {
        __NOP();
    }
}
