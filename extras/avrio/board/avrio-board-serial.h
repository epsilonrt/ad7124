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
#ifndef _AVRIO_BOARD_SERIAL_H_
#define _AVRIO_BOARD_SERIAL_H_
/* ========================================================================== */

/* SERIAL =================================================================== */
#include <avrio/defs.h>
#include <avr/io.h>

/* configuration ============================================================ */
#define SERIAL_EOL SERIAL_CR
#define SERIAL_RXBUFSIZE 16
#define SERIAL_TXBUFSIZE 16
#define AVRIO_SERIAL_BAUD_USE_X2 1

/* macros =================================================================== */
#ifdef USART_TX_vect
  /*
   * ATmega328P,
   * ATmega168, ATmega168P,
   * ATmega88, ATmega88P,
   * ATmega48, ATmega48P
   */
#define USART_TXC_vect  USART_TX_vect
#define USART_RXC_vect  USART_RX_vect
#endif

#ifdef UCSR0A
/*
 * ATmega328P,
 * ATmega168, ATmega168P,
 * ATmega88, ATmega88P,
 * ATmega48, ATmega48P
 */
#define UCSRA           UCSR0A
#define UCSRB           UCSR0B
#define UCSRC           UCSR0C
#define UBRRL           UBRR0L
#define UBRRH           UBRR0H
#define UDR             UDR0

#define USART_PORT      PORTD
#define USART_DDR       DDRD
#define USART_TXPIN     PD1
#define USART_RXPIN     PD0

#endif

/* ========================================================================== */
#endif /* _AVRIO_BOARD_SERIAL_H_ */
