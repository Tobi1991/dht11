/*
 * dht11.c
 *
 *  Created on: 05.10.2019
 *      Author: root
 */

#include "dht11.h"

char checkTransmission(dht11_data_t transmission){

    char checksum = 0;
    checksum += transmission.integral_rh_data;
    checksum += transmission.decimal_rh_data;
    checksum += transmission.integral_t_data;
    checksum += transmission.decimal_t_data;

    if(checksum == transmission.checksum){
        return 1;
    } else {
        return 0;
    }
}

void configureClock(void){

    // Configures the "TASSEL" multiplexer to use ACLK
    TAOCTL |= TASSEL_1;

    // Configures "ID" Devider to devide by 1
    TA0CTL |= ID_0;

    // Configures "IDEX" Devider to devide by 1
    TA0EX0 |= TAIDEX_0;
}

void beginStartSignal(void){

    // Configures P1.2 as output
    P1DIR |= 0x04;

    // Toggles P1.2 voltage
    P1OUT ^= 0x04;

    // Enable timer to interrupt on overflow
    TA0CTL |= TAIE;

    // Starts the timer in continuous mode (counts up to 0xFFFF)
    TA0CTL |= MC_2;

}

#pragma vector=TIMER0_A1_VECTOR
__interrupt void stopStartSignal(void){

    // Clear the interrupt flag to acknowledge that we handled the interrupt
    TA0CTL &= TAIFG;

    // Toggles P1.2 voltage
    P1OUT ^= 0x04;
}





