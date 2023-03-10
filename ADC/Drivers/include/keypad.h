/*
 * keypad.h
 *
 *  Created on: May 16, 2022
 *      Author: nada
 */

#ifndef INCLUDE_KEYPAD_H_
#define INCLUDE_KEYPAD_H_

#define keypad_port GPIOA
#define seg_port GPIOB


void init_seg(void);
void init_keypad(void);
void KeyPad_MANAGE(void);
char KeyPad_GET_VALUE(void);

void KeypadCallouts_KeyPressNotificaton(char value);

#endif /* INCLUDE_KEYPAD_H_ */
