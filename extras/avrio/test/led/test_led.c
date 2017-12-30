/*
 * led_test.c
 * LED Test: Lights the LEDs by a one, then the off one by one and again.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License")
 */
#include <avrio/led.h>
#include <avrio/delay.h>

int
main (void) {
  uint8_t ucLed;
  
  vLedInit ();

  for (;;) {

    for (ucLed = 0; ucLed < LED_QUANTITY; ucLed++) {

      vLedSet (xLedGetMask (ucLed));
      delay_ms (500);
    }
    for (ucLed = 0; ucLed < LED_QUANTITY; ucLed++) {

      vLedClear (xLedGetMask (ucLed));
      delay_ms (500);
    }
  }
  return 0;
}
