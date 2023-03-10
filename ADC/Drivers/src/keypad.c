#include "stm32f4xx.h"
#include "keypad.h"
#include "gpio.h"

char current_value;
char input_array[4] = { 5, 6, 7, 0 };
char output_array[3] = { 2, 3, 4 };
char seg[10] = { 0x7E, 0x0C, 0xB6, 0x9E, 0xCC, 0xDA, 0xFA, 0x0E, 0xFE, 0xDE };


char lookupTable[4][3] = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 },
		{ '*', 0, '#' } };

void init_keypad() {
	for (int i = 0; i < 4; i++) {
		GPIO_Init(keypad_port, input_array[i], 0, 0, 1); //initialize as input pins with internal pull up resistance
	}
	for (int i = 0; i < 3; i++) {
		GPIO_Init(keypad_port, output_array[i], 1, 0, 0); //initialize as output pins
	}
}
void KeyPad_MANAGE() {

	for (int i = 0; i < 3; i++) //loop for the columns
			{
		GPIO_Write(keypad_port, output_array[0], 1);
		GPIO_Write(keypad_port, output_array[1], 1);
		GPIO_Write(keypad_port, output_array[2], 1);
		GPIO_Write(keypad_port, output_array[i], 0);
		for (int j = 0; j < 4; j++) //loop for the rows
				{
			if ((GPIO_Read(keypad_port, input_array[j]) == 0)) //check if button is pressed
			{
				for (int i = 0; i < 3000; i++)
					;
				if ((GPIO_Read(keypad_port, input_array[j]) == 0)) //second check due to debounce
				{
					while ((GPIO_Read(keypad_port, input_array[j]) == 0)) {
					} //wait until button is released
					current_value = lookupTable[j][i]; //detect the pressed button
					KeypadCallouts_KeyPressNotificaton(current_value);
				}
			}
		}
	}
}



void init_seg() {
	for (int i = 1; i < 8; i++) {
		GPIO_Init(seg_port, i, 1, 1, 0); //Initialize as output pins
		GPIO_Write(seg_port, i, 0); //make 7segemnt pins initially low
	}

}
void KeypadCallouts_KeyPressNotificaton(char value ) {

//detect the button pressed and write on 7 segment
	switch (value) {
	case 0:
		seg_port->ODR = (seg[0]);
		break;
	case 1:
		seg_port->ODR = (seg[1]);
		break;
	case 2:
		seg_port->ODR = (seg[2]);
		break;
	case 3:
		seg_port->ODR = (seg[3]);
		break;
	case 4:
		seg_port->ODR = (seg[4]);
		break;
	case 5:
		seg_port->ODR = (seg[5]);
		break;
	case 6:
		seg_port->ODR = (seg[6]);
		break;
	case 7:
		seg_port->ODR = (seg[7]);
		break;
	case 8:
		seg_port->ODR = (seg[8]);
		break;
	case 9:
		seg_port->ODR = (seg[9]);
	}

}

