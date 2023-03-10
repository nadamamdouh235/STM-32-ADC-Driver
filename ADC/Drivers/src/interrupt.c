/*
 * interrupt.c
 *
 *  Created on: May 25, 2022
 *      Author: nada
 */
#include "stm32f4xx.h"

int interrupt;
void interrupt_enable(){
	RCC->APB2ENR|=(1<<14);
}
void interrupt_init(char port,int pin,char edge){
	if((pin>0)&&(pin<=3)){
		interrupt=0;
	}
	if((pin>3)&&(pin<=7)){
		interrupt=1;
	}
	if((pin>7)&&(pin<=11)){
		interrupt=2;
	}
	if((pin>7)&&(pin<=15)){
		interrupt=3;
	}
			switch(port){
			//0 for port A,1 for port B,2 for port C,3 for port D,4 for port E,5 for port H
			case 0:
				SYSCFG->EXTICR[interrupt]&=~(1<<0);
				SYSCFG->EXTICR[interrupt]&=~(1<<1);
				SYSCFG->EXTICR[interrupt]&=~(1<<2);
				SYSCFG->EXTICR[interrupt]&=~(1<<3);
				break;
			case 1:
				SYSCFG->EXTICR[interrupt]|=(1<<0);
				SYSCFG->EXTICR[interrupt]&=~(1<<1);
				SYSCFG->EXTICR[interrupt]&=~(1<<2);
				SYSCFG->EXTICR[interrupt]&=~(1<<3);
				break;
			case 2:
				SYSCFG->EXTICR[interrupt]&=~(1<<0);
				SYSCFG->EXTICR[interrupt]|=(1<<1);
				SYSCFG->EXTICR[interrupt]&=~(1<<2);
				SYSCFG->EXTICR[interrupt]&=~(1<<3);
				break;
			case 3:
				SYSCFG->EXTICR[interrupt]|=(1<<0);
				SYSCFG->EXTICR[interrupt]|=(1<<1);
				SYSCFG->EXTICR[interrupt]&=~(1<<2);
				SYSCFG->EXTICR[interrupt]&=~(1<<3);
				break;
			case 4:
				SYSCFG->EXTICR[interrupt]&=~(1<<0);
				SYSCFG->EXTICR[interrupt]&=~(1<<1);
				SYSCFG->EXTICR[interrupt]|=(1<<2);
				SYSCFG->EXTICR[interrupt]&=~(1<<3);
				break;
			case 5:
				SYSCFG->EXTICR[interrupt]|=(1<<0);
				SYSCFG->EXTICR[interrupt]|=(1<<1);
				SYSCFG->EXTICR[interrupt]|=(1<<2);
				SYSCFG->EXTICR[interrupt]&=~(1<<3);
				break;
		}
	EXTI->IMR|=(1<<pin);
	//0 for falling edge and 1 for rising edge
		if (edge==0)
		{
			EXTI->FTSR|=(1<<pin);
			}
		else if(edge==1)
		{
			EXTI->RTSR|=(1<<(pin));
		}

		NVIC->ISER[0]|=(1<<(pin+6));


}
