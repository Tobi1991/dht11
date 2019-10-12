/*
 * dht11.h
 *
 *  Created on: 05.10.2019
 *      Author: root
 */

#ifndef DHT11_H_
#define DHT11_H_

#include <msp430f5529.h>

// Clock configuration
#define TASSEL 0x01
#define ID
#define IDEX


typedef struct dht11_data {
    char integral_rh_data;
    char decimal_rh_data;
    char integral_t_data;
    char decimal_t_data;
    char checksum;
} dht11_data_t;

//
void configureClock(void);

// Checks the integrity of a data transmission
char checkTransmission(dht11_data_t transmission);

// MCU pulls down voltage
void beginStartSignal(void);

// Stop pulling down voltage after at least 18ms
#pragma vector=TIMER0_A1_VECTOR
__interrupt void stopStartSignal(void);




#endif /* DHT11_H_ */
