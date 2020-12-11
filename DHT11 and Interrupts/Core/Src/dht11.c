/*
 * dht11.c
 *
 *  Created on: 20-Jan-2020
 *      Author: neevee technologies
 */
#include "main.h"
#include "dht11.h"

static void dht11_gpio_config_output()
{
	GPIO_InitTypeDef dht11PinDef = {0};

	__HAL_RCC_GPIOB_CLK_ENABLE();

	dht11PinDef.Pin = DHT11PIN;
	dht11PinDef.Mode = GPIO_MODE_OUTPUT_PP;
	dht11PinDef.Pull = GPIO_PULLUP;
	dht11PinDef.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(DHT11PORT, &dht11PinDef);
}

static void dht11_gpio_config_input()
{
	GPIO_InitTypeDef dht11PinDef = {0};

	__HAL_RCC_GPIOB_CLK_ENABLE();

	dht11PinDef.Pin = DHT11PIN;
	dht11PinDef.Mode = GPIO_MODE_INPUT;
	dht11PinDef.Pull = GPIO_PULLUP;
	dht11PinDef.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(DHT11PORT, &dht11PinDef);
}

static void dht11_gpio_output_set()
{
	HAL_GPIO_WritePin(DHT11PORT, DHT11PIN, GPIO_PIN_SET);
}

static void dht11_gpio_output_clear()
{
	HAL_GPIO_WritePin(DHT11PORT, DHT11PIN, GPIO_PIN_RESET);
}

static int dht11_gpio_input_read()
{
	return HAL_GPIO_ReadPin(DHT11PORT, DHT11PIN);
}

extern TIM_HandleTypeDef htim6;

static void dht11_delay_usec(uint16_t delay)
{
	__HAL_TIM_SET_COUNTER(&htim6, 0);
	while ((__HAL_TIM_GET_COUNTER(&htim6))<delay);
}

dht11_status_t read_dht11_sensor (uint16_t *temp, uint16_t *humid)
{
	int cntr;
	int bits = 40;
	uint8_t dht11_data[5];
	uint8_t data = 0;
	uint8_t i = 0;

	dht11_gpio_config_input();
	dht11_delay_usec(50);
	if(dht11_gpio_input_read() == 0) {
		return DHT11_PULLUP_ERR;
	}

	dht11_gpio_config_output();
	dht11_gpio_output_set();
	dht11_gpio_output_clear();
	/* Delay for 18 - 20 mSec */
	dht11_delay_usec(18500);
	//dht11_gpio_output_set();

	dht11_gpio_config_input();
	/*if(dht11_gpio_input_read() == 0) {
		return DHT11_PULLUP_ERR;
	}*/

	dht11_delay_usec(40);
	if(dht11_gpio_input_read() != 0) {
		return DHT11_START_ERR;
	}

	cntr=18;
	while(dht11_gpio_input_read() == 0) {
		dht11_delay_usec(5);
		if(--cntr == 0) {
			return DHT11_START_ERR;
		}
	}

	cntr=18;
	while(dht11_gpio_input_read() != 0) {
		dht11_delay_usec(5);
		if(--cntr == 0) {
			return DHT11_START_ERR;
		}
	}

	do {
		cntr=11;
		while(dht11_gpio_input_read() == 0) {
			dht11_delay_usec(5);
			if(--cntr == 0) {
				return DHT11_DATA_ERR;
			}
		}

		cntr=15;
		while(dht11_gpio_input_read() != 0) {
			dht11_delay_usec(5);
			if(--cntr == 0) {
				return DHT11_DATA_ERR;
			}
		}
		data = data << 1;

		if(cntr < 11) {
			data = data | 0x01;
		}
		if((bits & 0x07) == 1) {
			dht11_data[i] = data;
			i++;
			data = 0;
		}
	} while(--bits != 0);

	if ((dht11_data[0] + dht11_data[1] + dht11_data[2] + dht11_data[3]) != dht11_data[4]) {
		return DHT11_CHKSUM_ERR;
	}

	*humid = dht11_data[0] * 100 + dht11_data[1] * 10;
	*temp = dht11_data[2] * 100 + dht11_data[3] * 10;

	return DHT11_OK;
}
