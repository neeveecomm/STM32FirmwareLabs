/*
 * ConfigPin.h
 *
 *  Created on: Dec 2, 2020
 *      Author: Balaji Annamalai, Neevee Technologies, Chennai.
 */

#include "stm32l0xx_hal.h"
class ConfigPin
{
	public:
		uint16_t PIN;
		GPIO_TypeDef* ALPHA;
		ConfigPin(char a,int p)
		{
			switch(a)
			{
				case 'A':ALPHA=GPIOA;break;
				case 'B':ALPHA=GPIOB;break;
				case 'C':ALPHA=GPIOC;break;
				case 'H':ALPHA=GPIOH;break;
				//default: throw "Invalid PIN";
			}
			switch(p+1)
			{
				case 1:PIN=GPIO_PIN_0;break;
				case 2:PIN=GPIO_PIN_1;break;
				case 3:PIN=GPIO_PIN_2;break;
				case 4:PIN=GPIO_PIN_3;break;
				case 5:PIN=GPIO_PIN_4;break;
				case 6:PIN=GPIO_PIN_5;break;
				case 7:PIN=GPIO_PIN_6;break;
				case 8:PIN=GPIO_PIN_7;break;
				case 9:PIN=GPIO_PIN_8;break;
				case 10:PIN=GPIO_PIN_9;break;
				case 11:PIN=GPIO_PIN_10;break;
				case 12:PIN=GPIO_PIN_11;break;
				case 13:PIN=GPIO_PIN_12;break;
				case 14:PIN=GPIO_PIN_13;break;
				case 15:PIN=GPIO_PIN_14;break;
				case 16:PIN=GPIO_PIN_15;break;
				//default: throw "Invalid PIN";
			}
		}
		void write(uint8_t val)
		{
			GPIO_PinState value;
			if(val==1)
			value=GPIO_PIN_SET;
			else
			value=GPIO_PIN_RESET;
			HAL_GPIO_WritePin(ALPHA,PIN,value);
		}
		bool read()
		{
			GPIO_PinState value;
			value=HAL_GPIO_ReadPin(ALPHA,PIN);
			if(value==GPIO_PIN_SET)
				return 1;
			else
				return 0;
		}
};

