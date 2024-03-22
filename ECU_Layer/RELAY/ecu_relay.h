/* 
 * File:   ecu_relay.h
 * Author: imina
 *
 * Created on December 4, 2023, 8:28 PM
 */

#ifndef ECU_RELAY_H
#define	ECU_RELAY_H

/* section: Includes */
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* section: Macro Declarations */
#define RELAY_ON_STATUS  0X01
#define RELAY_OFF_STATUS 0X00

/* section: Macro functions Declarations */

/* section: Data type Declarations */
typedef struct{
    Pin_config_t relay_config;
}relay_t;

/* section: functions Declarations */

/**
 * @brief function to initialize relay
 * @param relay the struct which has all info about the relay
 * @return return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType relay_initialize(const relay_t *relay);
/**
 * @brief function to turn on relay
 * @param relay the struct which has all info about the relay
 * @return return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType relay_turn_on(const relay_t *relay);
/**
 * @brief function to turn off relay
 * @param relay the struct which has all info about the relay
 * @return return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType relay_turn_off(const relay_t *relay);


#endif	/* ECU_RELAY_H */

