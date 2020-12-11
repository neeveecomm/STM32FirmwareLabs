/*
 * dht11.h
 *
 *  Created on: 20-Jan-2020
 *      Author: neevee technologies
 */

#ifndef INC_DHT11_H_
#define INC_DHT11_H_

typedef enum dht11_status {
	DHT11_OK,
	DHT11_PULLUP_ERR,
	DHT11_START_ERR,
	DHT11_DATA_ERR,
	DHT11_CHKSUM_ERR,
}dht11_status_t;

#define DHT11PORT	GPIOB
#define DHT11PIN	GPIO_PIN_6

dht11_status_t read_dht11_sensor(uint16_t *temp, uint16_t *humid);

#endif /* INC_DHT11_H_ */
