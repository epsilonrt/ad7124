#include <avrio/tc.h>
#include <avrio/led.h>
#include <avrio/delay.h>
#include <avr/pgmspace.h>
#include <avr/version.h>
// Pour TC_TXBUFSIZE
#include "avrio-board-tc.h"

/* constants ================================================================ */
#define PORT         "tty0"
//#define BAUDRATE     38400
#define BAUDRATE     500000
#define DATABIT      SERIAL_DATABIT_8 // 5 à 9 bits
#define PARITY       SERIAL_PARITY_NONE // NONE, EVEN, ODD
#define STOPBIT      SERIAL_STOPBIT_ONE // 1 ou 2
//#define FLOWCTL      SERIAL_FLOW_RTSCTS
#define FLOWCTL      SERIAL_FLOW_NONE

#define OPT_READ     1
#define OPT_WRITE    1
#define OPT_ECHO     0
#define OPT_NOBLOCK  1
#define LOOP_DELAY   0 // Valeur en ms

/* Pour valider 1, pour invalider 0 */
#define TEST_DEBUG        0 /* Transmission de la lettre 'U' en boucle */
#define TEST_ALPHABET     1 /* Envoi de l'alphabet A -> Z en boucle */
#define TEST_PRINTF       1 /* Test intégration printf */
#define TEST_TXEN         0 /* Envoi d'une chaine de caractères très courte pour 
                             * vérifier la gestion de TXEN */
#define TEST_TXOVERFLOW   0 /* Envoi un string 2 fois plus long que le buffer tx 
                             * permet de vérifier la gestion du buffer tx sous irq */
#define TEST_TERMINAL     1 /* Invite puis attente d'un caractère puis renvoi */
#define TEST_PONG         0 /* Boucle infinie d'attente d'un caractère puis renvoi */
#define TEST_PONG_FWRITE  0 /* Variante de pong avec fwrite et fread */

/* constants ================================================================ */
#ifndef AVRIO_TC_RS485
#define FLAGS ((OPT_READ ? O_RD : 0) + \
               (OPT_WRITE ? O_WR : 0) + \
               (OPT_ECHO ? O_ECHO : 0) + \
               (OPT_NOBLOCK ? O_NONBLOCK : 0))
#else
#define FLAGS ((OPT_READ ? O_RD : 0) + \
               (OPT_WRITE ? O_WR : 0) + \
               (OPT_ECHO ? O_ECHO : 0) + \
               (O_HDUPLEX) + \
               (OPT_NOBLOCK ? O_NONBLOCK : 0))
#undef FLOWCTL
#define FLOWCTL SERIAL_FLOW_NONE
#warning RS485 enabled, disabling RTS/CTS
#endif

/* private variables ======================================================== */
static xSerialIos settings = {
  .baud = BAUDRATE, .dbits = DATABIT, .parity = PARITY,
  .sbits = STOPBIT, .flow = FLOWCTL, .eol = SERIAL_CRLF
};

/* internal public functions ================================================ */
void vTestDebug (void);
void vTestAlphabet (void);
void vTestTerminal (void);
void vTestPrintf (void);
void vTestPong (void);
void vTestPongFwrite (void);
void vTestReception (void);
void vTestTxOverflow (void);
void vTestTxEn (void);
void vLedAssert (int i);

/* main ===================================================================== */
int
main (void) {

  vLedInit();
  FILE * tc = xFileOpen (PORT, FLAGS, &settings);
  stdout = tc;
  stdin = tc;
  sei();

  for (;;) {

    vTestDebug ();
    vTestAlphabet ();
    vTestTxOverflow();
    vTestTxEn();
    vTestPrintf ();
    vTestTerminal ();
    vTestPong();
    vTestPongFwrite();
#if LOOP_DELAY > 0
    delay_ms (LOOP_DELAY);
#endif
  }
  return 0;
}

/* internal public functions ================================================ */
static int iErr;
static int c;

/* -----------------------------------------------------------------------------
 * Test de debug
 * Envoi d'un U
 */
void
vTestDebug (void) {
#if TEST_DEBUG

  c = 0x55;
  iErr = putchar (c);
  vLedAssert (iErr == c);
  vLedToggle (LED_LED1);
#endif
}

/* -----------------------------------------------------------------------------
 * Envoi de l'alphabet A -> Z
 */
void
vTestAlphabet (void) {
#if TEST_ALPHABET
  uint8_t ucCount = 32;

  vLedSet (LED_LED1);
  while (ucCount--) {

    c = 'A';
    do {

      iErr = putchar (c);
      vLedAssert (iErr == c);
    }
    while (c++ < 'Z');

    c = '\n';
    iErr = putchar (c);
    vLedAssert (iErr == c);
  }
  vLedClear (LED_LED1);
#endif
}

/* -----------------------------------------------------------------------------
 * Envoi d'une longue chaine de caractères (2 fois plus longue que le buffer tx)
 */
void
vTestTxOverflow (void) {
#if TEST_TXOVERFLOW != 0 && defined(TC_TXBUFSIZE)
#define BUFSIZE ((TC_TXBUFSIZE * 2) - 1)
  char s[BUFSIZE];

  vLedToggle (LED_LED1);
  for (int i = 0; i < BUFSIZE - 1; i++) {

    s[i] = (i % 26) + 'A';
  }
  s[BUFSIZE - 1] = 0;
  puts (s);
#endif
}

/* -----------------------------------------------------------------------------
 * Envoi d'une chaine de caractères très courte pour vérifier la gestion de TXEN
 */
void
vTestTxEn (void) {
#if TEST_TXEN
  puts ("A");
  vLedToggle (LED_LED1);
#endif
}

/* -----------------------------------------------------------------------------
 * Test Terminal
 * Invite puis attente d'un caractère puis renvoi
 */
void
vTestTerminal (void) {
#if TEST_TERMINAL
  uint16_t usCount = 0;
  bool isWait = true;

  printf_P (PSTR ("\nTerminal Test (%s version)\nPress any key (ENTER to quit)..."),
            (AVRIO_TC_FLAVOUR == TC_FLAVOUR_POLL) ? "poll" : "irq");
  do {

    c = getchar ();
    if (c != EOF) {

      if (isWait) {
        iErr = putchar ('\n');
        vLedAssert (iErr == '\n');
        isWait = false;
      }
      iErr = putchar (c);
      vLedAssert (iErr == c);
      vLedToggle (LED_LED1);
    }
    else {
      if ( (isWait) && ( (usCount++ % 32768) == 0)) {

        iErr = putchar ('.');
        vLedAssert (iErr == '.');
      }
    }
  }
  while (c != '\r');       /* Return pour terminer */
  iErr = putchar ('\n');
  vLedAssert (iErr == '\n');
#endif
}

/* -----------------------------------------------------------------------------
 * Test Printf
 */
void
vTestPrintf (void) {
#if TEST_PRINTF

  printf_P (PSTR ("\nPrintf Test (libc %s)\n-printf() test\n"), __AVR_LIBC_VERSION_STRING__);
  for (c = 0; c < 8; c++) {

    printf_P (PSTR ("\tTest #0x%02X\n"), c);
  }
#endif
}

/* -----------------------------------------------------------------------------
 * Test Pong
 * Boucle infinie d'attente d'un caractère puis renvoi
 */
void
vTestPong (void) {
#if TEST_PONG

  for (;;) {

    c = getchar ();
    iErr = ferror (stdin);
    vLedAssert (iErr == 0);
    if ( (c != EOF) && (feof (stdin) == 0)) {

      iErr = putc (c, stdin);
      vLedAssert (iErr == c);
      iErr = ferror (stdout);
      vLedAssert (iErr == 0);
      vLedToggle (LED_LED1);
    }
  }
#endif
}

/* -----------------------------------------------------------------------------
 * Test avec les fonctions stdio fread et fwrite
 * Boucle infinie d'attente d'un caractère puis renvoi
 *                            <<< WARNING >>>
 * Les fonctions fread et fwrite de avr-libc font appel à getc et putc pour lire
 * le stream ce qui n'améne donc aucune optimisation par rapport à un appel
 * direct.
 */
void
vTestPongFwrite (void) {
#if TEST_PONG_FWRITE
  char buffer[32];
  static size_t ulReadLen, ulWriteLen;

  for (;;) {

    ulReadLen = fread (buffer, 1, sizeof (buffer), stdin);
    vLedAssert (ferror (stdin) == 0);
    if (ulReadLen) {

      ulWriteLen = fwrite (buffer, 1, ulReadLen, stdout);
      vLedAssert (ferror (stdout) == 0);
      vLedToggle (LED_LED1);
    }
  }
#endif
}

/* -----------------------------------------------------------------------------
 * Vérifie que la condition passée est vraie, sinon fait clignoter rapidement
 * la led 1 à l'infinie
 */
void
vLedAssert (int i) {

  if (!i) {

    for (;;) {

      vLedSet (LED_LED1);
      delay_ms (50);
      vLedClear (LED_LED1);
      delay_ms (100);
    }
  }
}

/* ========================================================================== */
