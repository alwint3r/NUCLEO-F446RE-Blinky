#include "stm32f4xx_hal.h"

void LED_Init();
void LED_Toggle();

#define LED_PIN 5

int main(void)
{
    HAL_Init();
    LED_Init();

    while (1)
    {
        GPIOA->BSRR = (1 << LED_PIN);

        HAL_Delay(1000);

        GPIOA->BSRR = (1 << (LED_PIN + 16));

        HAL_Delay(1000);
    }
}

void LED_Init()
{
    __HAL_RCC_GPIOA_CLK_ENABLE();

    uint32_t temp = GPIOA->MODER;
    temp &= ~(0b11 << (LED_PIN * 2));
    temp |= (0b01 << (LED_PIN * 2));

    GPIOA->MODER = temp;

    temp = GPIOA->OTYPER;
    temp &= ~(0b01 << LED_PIN);

    GPIOA->OTYPER = temp;

    temp = GPIOA->OSPEEDR;
    temp &= ~(0b11 << (LED_PIN * 2));
    temp |= (0b11 << (LED_PIN * 2));

    GPIOA->OSPEEDR = temp;

    temp = GPIOA->PUPDR;
    temp &= ~(0b11 << (LED_PIN * 2));

    GPIOA->PUPDR = temp;
}

void SysTick_Handler(void)
{
    HAL_IncTick();
}