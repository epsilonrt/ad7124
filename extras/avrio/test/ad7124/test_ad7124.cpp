//#include <avrio/led.h>
#include <avrio/delay.h>
#include <ad7124.h>

using namespace Ad7124;
/* constants ================================================================ */
/* macros =================================================================== */
/* structures =============================================================== */
/* types ==================================================================== */
/* private variables ======================================================== */
/* public variables ========================================================= */
/* private functions ======================================================== */
/* internal public functions ================================================ */
Ad7124Chip adc;

/* main ===================================================================== */
int
main (void) {
  long value;
  
  //vLedInit ();
  // Votre code d'initialisation devrait être ici
  // Your initialization code should be here
  adc.init(10);
  adc.setAdcControl(SingleConvMode, FullPower, true);
  adc.setConfig (0, RefInternal, Pga64, true);
  adc.setChannel (0, 0, V20mVPInput, V20mVMInput);

  for (;;) {

    // Your main code should be here,
    // you can delete the two lines below
    // Votre code principal devrait être ici,
    // Vous pouvrez supprimer les deux lignes ci-dessous
    //vLedToggle (LED_LED1);
    value = adc.read(0);
    delay_ms (1000);
  }
  return 0;
}

/* ========================================================================== */
