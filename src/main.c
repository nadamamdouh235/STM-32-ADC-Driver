#include <adc.h>
#include<stdint.h>
#include<stdio.h>
#include "stm32f4xx.h"
#include "gpio.h"
#include "keypad.h"
#include "interrupt.h"
#include "adc.h"
#include "LCD.h"
#include <math.h>
unsigned short int Data;
float output_temp;
char read;

void ISR(void);

int main(void) {
	LCD_Init();
	GPIO_Init(temp_sensor_GPIO,temp_sensor_pin,2,0,0);
	struct ADCConfigType configure;
	configure.voltage=5;
	configure.resolution=bit_12;
	configure.conversion_mode=single_conversion_mode;
	ADC_Init(&configure);

while(1){

	for(int i=0;i<300000;i++);

	ADC_StartConv(channel_num);
	if (use_polling){
	read=ADC_ReadData(&Data);
	if (read==0){
	LCD_ClearScreen();
	output_temp=((float) Data /4096) * 5;
	output_temp=output_temp/0.01;
	LCD_DisplayString("temp:");
	LCD_IntToStr(output_temp);
}
	}
}
}

void ISR(void ){
	LCD_ClearScreen();
	Data=ADC_register->DR;
	LCD_DisplayString("temp:");
	output_temp=((float) Data /4096) * 5;
	output_temp=output_temp/0.01;
	LCD_IntToStr(output_temp);
}
 void ADC_IRQHandler(void ){
		ISR();

 }

