/*
 * ADC.c

 *
 *  Created on: May 30, 2022
 *      Author: nada
 */

#include "stm32f4xx.h"
#include "adc.h"

void ADC_Init(ADCConfigType* ConfigParamPtr) {
	RCC->APB2ENR |= (1 << 8);
	ADC_register->CR1 &= ~(1 << 5); //EOCIE disable interrupt
#if use_polling==0
	NVIC->ISER[0] |= (1 << 18);
	ADC_register->CR1 |= (1 << 5); //EOCIE enable interrupt
#endif
	if (ConfigParamPtr->conversion_mode == single_conversion_mode) {
		ADC_register->CR2 &= ~(1 << 1); //CONT bit disabled

	} else if (ConfigParamPtr->conversion_mode == continous_conversion_mode) {
		ADC_register->CR2 |= (1 << 1); //CONT bit enabled

	}
	switch (ConfigParamPtr->resolution) {
	case bit_12:
		ADC_register->CR1 &= ~(1 << 24);
		ADC_register->CR1 &= ~(1 << 25);
		break;
	case bit_10:
		ADC_register->CR1 |= (1 << 24);
		ADC_register->CR1 &= ~(1 << 25);
		break;
	case bit_8:
		ADC_register->CR1 &= ~(1 << 24);
		ADC_register->CR1 |= (1 << 25);
		break;
	case bit_6:
		ADC_register->CR1 |= (1 << 24);
		ADC_register->CR1 |= (1 << 25);
		break;
	default:
		ADC_register->CR1 &= ~(1 << 24);
		ADC_register->CR1 &= ~(1 << 25);
	}
	ADC_register->CR2 |= (1 << 0);
	ADC_register->CR2 &= ~(1 << 11); // right alignment for data in DR
}

void ADC_StartConv(unsigned char ChannelNum) {
	//one conversion length
	ADC_register->SQR1 &= ~(1 << 20);
	ADC_register->SQR1 &= ~(1 << 21);
	ADC_register->SQR1 &= ~(1 << 22);
	ADC_register->SQR1 &= ~(1 << 23);
	ADC_register->SQR3 &=
			~((1 << 0) | (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4)); //clear bits chosen for for first channel number
	ADC_register->SQR3 |= (ChannelNum); //choose the channel number
	ADC_register->CR2 |= (1 << 30); //start conversion
}
void ADC_GetConversionState(unsigned char* ConversionStatePtr) {
	if (use_polling) {
		if ((ADC_register->SR) & (1 << 1)) {
			*ConversionStatePtr = 1;
		} else
			*ConversionStatePtr = 0;
	}
}
unsigned char ADC_ReadData(unsigned short int* DataPtr) {
	unsigned char valid;
	ADC_GetConversionState(&valid);
	if (valid == 1) {
		*DataPtr = ADC_register->DR;
		return 0;
	} else {
		return 1;
	}
}
