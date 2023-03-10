#include "stm32f4xx.h"
#include "gpio.h"

void GPIO_Init(GPIO_TypeDef * GPIOx, char pin, char dir, char enable_pin,
		char pull) {
	//Enable clock to GBIOx
	RCC->AHB1ENR |= (1u << enable_pin);

	//1 for output and 0 for input
	//2 for analog input
	if (dir==1) {
		GPIOx->MODER |= (1u << (2 * pin));
		GPIOx->MODER &= ~(1u << (2 * pin + 1));
	}
	else if (dir==0)

	{
		GPIOx->MODER &= ~(1u << (2 * pin));
		GPIOx->MODER &= ~(1u << (2 * pin + 1));
		if (pull) // 1 for pull up and 0 for pull down
		{

			GPIOx->PUPDR |= (1u << (2 * pin));
			GPIOx->PUPDR &= ~(1u << (2 * pin + 1));

		} else if (!pull) {
			GPIOx->PUPDR &= ~(1u << (2 * pin));
			GPIOx->PUPDR |= (1u << (2 * pin + 1));

		}
	}
	else if (dir==2){
		GPIOx->MODER |= (1u << (2 * pin));
		GPIOx->MODER |= (1u << (2 * pin + 1));


	}

}

char GPIO_Write(GPIO_TypeDef * GPIOx, char pin, char state) {
	if (GPIOx->MODER & (1u << (2 * pin))) {
		if (state) {
			GPIOx->ODR |= (1u << pin);
		} else {
			GPIOx->ODR &= ~(1u << pin);
		}
		return 0;
	} else {
		return 1;
	}
}

char GPIO_Read(GPIO_TypeDef * GPIOx, char pin) {

	return GPIOx->IDR & (1 << pin);

}

