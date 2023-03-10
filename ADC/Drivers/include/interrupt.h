/*
 * interrupt.h
 *
 *  Created on: May 25, 2022
 *      Author: nada
 */

#ifndef INCLUDE_INTERRUPT_H_
#define INCLUDE_INTERRUPT_H_

#define PORTA 0
#define PORTB 1
#define PORTC 2
#define PORTD 3
#define PORTE 4
#define PORTH 5
#define falling_edge 0
#define raising_edge 1

void interrupt_init(char port,int pin,char edge);
void interrupt_enable();

#endif /* INCLUDE_INTERRUPT_H_ */
