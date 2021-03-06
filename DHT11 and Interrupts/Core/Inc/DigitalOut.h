/*
 * DigitalOut.h
 *
 *  Created on: Dec 4, 2020
 *      Author: Balaji Annamalai, Neevee Technologies, Chennai.
 */

#include "stm32l0xx_hal.h"
#include<math.h>
class DigitalOut
{
	public:
		uint16_t PIN;
		GPIO_TypeDef* PORT;
		DigitalOut(char a,int p)
		{
			switch(a)
			{
				case 'A':PORT=GPIOA;break;
				case 'B':PORT=GPIOB;break;
				case 'C':PORT=GPIOC;break;
				case 'H':PORT=GPIOH;break;
			}
			PIN=(uint16_t)pow(2,p);
		}
		void toggle()
		{
			HAL_GPIO_TogglePin(PORT,PIN);
		}
		void write(uint8_t val)
		{
			GPIO_PinState value;
			if(val==1) value=GPIO_PIN_SET;
			else       value=GPIO_PIN_RESET;
			HAL_GPIO_WritePin(PORT,PIN,value);
		}

};

