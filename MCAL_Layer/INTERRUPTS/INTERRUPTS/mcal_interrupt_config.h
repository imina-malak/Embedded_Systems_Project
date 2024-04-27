/* 
 * File:   mcal_interrupt_config.h
 * Author: imena
 *
 * Created on January 3, 2024, 8:44 PM
 */

#ifndef MCAL_INTERRUPT_CONFIG_H
#define	MCAL_INTERRUPT_CONFIG_H

/* section: Includes */
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../../MCAL_Layer/device_config.h"


/* section: Macro Declarations */
#define INTERRUPT_ENABLED           1
#define INTERRUPT_DISABLED          0
#define INTERRUPT_OCCURED           1
#define INTERRUPT_DID_NOT_OCCURED   0
#define INTERRUPT_PRIORITY_ENABLED  1
#define INTERRUPT_PRIORITY_DISABLED 0

#define INTERRUPT_PRIORITY_FEATURE_ENABLED  INTERRUPT_ENABLED

/* section: Macro functions Declarations */
#if INTERRUPT_PRIORITY_FEATURE_ENABLED == INTERRUPT_PRIORITY_ENABLED
#define INTERRUPT_PRIORITY_ENABLE()   (RCONbits.IPEN = 1)
#define INTERRUPT_PRIORITY_DISABLE()  (RCONbits.IPEN = 0)

#define INTERRUPT_GLOBAL_INTERRUPT_HIGH_ENABLE()  (INTCONbits.GIEH = 1)
#define INTERRUPT_GLOBAL_INTERRUPT_HIGH_DISABLE() (INTCONbits.GIEH = 0)

#define INTERRUPT_GLOBAL_INTERRUPT_LOW_ENABLE()  (INTCONbits.GIEL = 1)
#define INTERRUPT_GLOBAL_INTERRUPT_LOW_DISABLE() (INTCONbits.GIEL = 0)

#else
#define INTERRUPT_GLOBAL_INTERRUPT_ENABLE()     (INTCONbits.GIE = 1)
#define INTERRUPT_GLOBAL_INTERRUPT_DISABLE()    (INTCONbits.GIE = 0)
#define INTERRUPT_PREPHERAL_INTERRUPT_ENABLE()  (INTCONbits.PEIE = 1)
#define INTERRUPT_PREPHERAL_INTERRUPT_DISABLE() (INTCONbits.PEIE = 0)
#endif

/* section: Data type Declarations */

typedef enum{
    INTERRUPT_LOW,
    INTERRUPT_HIGH,
}interrupt_priority_t;


/* section: functions Declarations */


#endif	/* MCAL_INTERRUPT_CONFIG_H */

