/*
 * XMem.hpp:
 *
 * This file contains the setup sequence that is needed to enable the
 *   ATmega XMEM interface.  It must be included in the main project
 *   file to be linked correctly in the final executable.
 *
 *  Created on: March 25, 2020
 *      Author: Sterling Peet <sterling.peet@ae.gatech.edu>
 */

#include <avr/io.h>

#ifndef OS_AVR_XMEM_HPP_
#define OS_AVR_XMEM_HPP_

void xmem_init(void) __attribute__ ((naked, used, section(".init3")));

void xmem_init(void)
{
    // Set up the XMEM interface
    XMCRB = 0; // need all 64K. no pins released
    #if defined(__AVR_ATmega128__)
    MCUCR = _BV(SRE); // enable xmem, no wait states
    #else
    XMCRA = _BV(SRE); // enable xmem, no wait states
    #endif

    // set up the bank selector pins (address lines A16..A18)
    // these are on pins 38,42,43 (PD7,PL7,PL6)
    #if defined(__AVR_ATmega128__)
    DDRD |= (_BV(PD5)|_BV(PD6)|_BV(PD7));
    #else
    DDRD |= _BV(PD7);
    DDRL |= (_BV(PL6)|_BV(PL7));
    #endif

    // set the bank selector pins (address lines A16..A18)
    // to zero only, we aren't doing fancy mem page swapping right now
    #if defined(__AVR_ATmega128__)
    PORTD &= ~(_BV(PD5)|_BV(PD6)|_BV(PD7));
    #else
    PORTD &= ~_BV(PD7);
    PORTL &= ~(_BV(PL6)|_BV(PL7));
    #endif
}

#endif  /* OS_AVR_XMEM_HPP_ */
