/*
 * This file is part of AvrIO.
 *
 * This software is governed by the CeCILL license under French law and
 * abiding by the rules of distribution of free software.  You can  use, 
 * modify and/ or redistribute the software under the terms of the CeCILL
 * license as circulated by CEA, CNRS and INRIA at the following URL
 * <http://www.cecill.info>. 
 * 
 * The fact that you are presently reading this means that you have had
 * knowledge of the CeCILL license and that you accept its terms.
 */
#ifndef _AVRIO_BOARD_TC_H_
#define _AVRIO_BOARD_TC_H_
/* ========================================================================== */
#include <avrio/defs.h>
#include <avr/io.h>

/* constants ================================================================ */
#define TC_EOL SERIAL_CR
#define TC_RXBUFSIZE 16
#define TC_TXBUFSIZE 16
#define AVRIO_TC_BAUD_USE_X2 1

#define TC_RXTX_PULLUP_ENABLE
#define TC_NUMOF_PORT 1
#ifndef AVRIO_TC_FLAVOUR
#define AVRIO_TC_FLAVOUR TC_FLAVOUR_IRQ
#endif

#define UCSRA           UCSR0A
#define UCSRB           UCSR0B
#define UCSRC           UCSR0C
#define UBRRL           UBRR0L
#define UBRRH           UBRR0H
#define UDR             UDR0
#define TC0_IO { \
  .rxd =  { .port = &PORTD, { .pin = 0 }}, \
  .txd =  { .port = &PORTD, { .pin = 1 }}, \
 }

/* ========================================================================== */
#endif /* _AVRIO_BOARD_TC_H_ */
