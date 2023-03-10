/*
 * adc.h
 *
 *  Created on: May 30, 2022
 *      Author: nada
 */

#ifndef INCLUDE_ADC_H_
#define INCLUDE_ADC_H_

#define ADC_register ADC1
#define temp_sensor_GPIO GPIOA
#define temp_sensor_pin 1
#define use_polling 0
#define channel_num 1

int conversion_mode;
typedef struct ADCConfigType {
	enum resolution {
		bit_12, bit_10, bit_8, bit_6
	} resolution;
	enum conversion_mode {
		single_conversion_mode, continous_conversion_mode
	} conversion_mode;

	int voltage;

} ADCConfigType;

void ADC_Init(ADCConfigType* ConfigParamPtr);
void ADC_StartConv(unsigned char ChannelNum);
void ADC_GetConversionState(unsigned char* ConversionStatePtr);
unsigned char ADC_ReadData(unsigned short int* DataPtr);

#endif /* INCLUDE_ADC_H_ */
