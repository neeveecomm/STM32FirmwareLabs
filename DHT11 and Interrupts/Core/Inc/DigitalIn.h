/*
 * DigitalIn.h
 *
 *  Created on: Dec 4, 2020
 *      Author: Balaji Annamalai, Neevee Technologies, Chennai.
 */

#include "stm32l0xx_hal.h"
#include<math.h>
class DigitalIn
{
	public:
		uint16_t PIN;
		GPIO_TypeDef* PORT;
		DigitalIn(char a,int p)
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
		bool read()
		{
			GPIO_PinState value;
			value=HAL_GPIO_ReadPin(PORT,PIN);
			if(value==GPIO_PIN_SET) return 1;
			else                    return 0;
		}
};

