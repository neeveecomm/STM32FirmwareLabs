/*
 * DigitalInOut.h
 *
 *  Created on: Dec 4, 2020
 *      Author: Balaji Annamalai, Neevee Technologies, Chennai.
 */

#include "stm32l0xx_hal.h"
#include<math.h>
class DigitalInOut
{
	public:
		uint16_t PIN;
		GPIO_TypeDef* ALPHA;
		DigitalInOut(char a,int p)
		{
			switch(a)
			{
				case 'A':ALPHA=GPIOA;break;
				case 'B':ALPHA=GPIOB;break;
				case 'C':ALPHA=GPIOC;break;
				case 'H':ALPHA=GPIOH;break;
			}
			PIN=(uint16_t)pow(2,p);
		}
		void write(uint8_t val)
		{
			GPIO_PinState value;
			if(val==1) value=GPIO_PIN_SET;
			else       value=GPIO_PIN_RESET;
			HAL_GPIO_WritePin(ALPHA,PIN,value);
		}
		bool read()
		{
			GPIO_PinState value;
			value=HAL_GPIO_ReadPin(ALPHA,PIN);
			if(value==GPIO_PIN_SET) return 1;
			else                    return 0;
		}
};

