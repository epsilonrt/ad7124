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
#ifndef _AVRIO_BOARD_TWI_H_
#  define _AVRIO_BOARD_TWI_H_
/* ========================================================================== */

/* TWI ====================================================================== */
#  include <avrio/defs.h>
#  include <avr/io.h>

/* constants ================================================================ */
/*
 * @ingroup twiboard_module
 * @def TWI_MASTER_ENABLE
 * @brief Valide le module \ref twimaster_module.
 */
// #define TWI_MASTER_ENABLE

/*
 * @ingroup twiboard_module
 * @def TWI_SLAVE_ENABLE
 * @brief Valide le module \ref twislave_module.
 */
// #define TWI_SLAVE_ENABLE



/* inline public functions ================================================== */
/*
 * @ingroup twiboard_module
 * @brief Valide les résistances de tirage à l'état haut des lignes SDA et SCL
 *
 * Doit être réimplémentée par l'utilisateur dans le cas d'une carte 
 * personnalisée.
 */
static inline void
vTwiEnablePullup (void) {

  PORTC |= (_BV (4) | _BV (5));
}

/*-----------------------------Mode Maître------------------------------------*/
/* constants ================================================================ */
/*
 * @ingroup twimasterboard_module
 * @def TWI_MASTER_RXBUFSIZE
 * @brief Taille du buffer de réception en octets.
 */
#  define TWI_MASTER_RXBUFSIZE 32

/*
 * @ingroup twimasterboard_module
 * @def TWI_MASTER_TXBUFSIZE
 * @brief Taille du buffer de transmission en octets.
 */
#  define TWI_MASTER_TXBUFSIZE 32

/*
 * @ingroup twimasterboard_module
 * @def TWI_MASTER_CTRLBUFSIZE
 * @brief Taille du buffer de contrôle en octets.
 *
 * Le buffer de contrôle permet de transmettre les messages de contrôle à la 
 * routine d'interruption du module.\n
 * Chaque message de contrôle est constitué d'un identifiant de trame
 * (xTwiId), d'une adresse circuit (xTwiDeviceAddr) et d'un nombre d'octets 
 * (xTwiLength).
 */
#  define TWI_MASTER_CTRLBUFSIZE 15

/*
 * @ingroup twimasterboard_module
 * @def TWI_MASTER_STATUSBUFSIZE
 * @brief Taille du buffer d'état en octets.
 *
 * Le buffer d'état permet de récupérer les messages d'état émis par la 
 * routine d'interruption du module.\n
 * Chaque message d'état est constitué d'un identifiant de trame
 * (\ref xTwiId), d'un état (xTwiStatus) et d'un nombre d'octets (xTwiLength).
 */
#  define TWI_MASTER_STATUSBUFSIZE 15

/*
 * @ingroup twimasterboard_module
 * @def TWI_MASTER_ADDR_NACK_RETRY
 * @brief Nombre d'essais avant de déclarer un esclave absent du bus.
 *
 *  Permet en mode maître, de renvoyer un certain nombre de demandes à un
 *  esclave qui n'a pas répondu la première fois (esclave lent à la détente !).
 */
#  define TWI_MASTER_ADDR_NACK_RETRY 1

/*----------------------------Mode Esclave------------------------------------*/
/* constants ================================================================ */
/*
 * @ingroup twislaveboard_module
 * @def TWI_SLAVE_RXBUFSIZE
 * @brief Taille du buffer de réception en octets.
 */
#  define TWI_SLAVE_RXBUFSIZE 32

/*
 * @ingroup twislaveboard_module
 * @def TWI_SLAVE_TXBUFSIZE
 * @brief Taille du buffer de transmission en octets.
 */
#  define TWI_SLAVE_TXBUFSIZE 32

/* ========================================================================== */
#endif /* _AVRIO_BOARD_TWI_H_ */
