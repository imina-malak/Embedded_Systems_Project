/* 
 * File:   ecu_keypad.h
 * Author: imina
 *
 * Created on December 13, 2023, 6:24 PM
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H

/* section: Includes */

#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* section: Macro Declarations */

/* section: Macro functions Declarations */
#define ECU_KEYPAD_ROWS    4
#define ECU_KEYPAD_COLUMNS 4

/* section: Data type Declarations */
typedef struct{
    Pin_config_t keypad_rows_config[ECU_KEYPAD_ROWS];
    Pin_config_t keypad_columns_config[ECU_KEYPAD_COLUMNS];
}keypad_t;
/* section: functions Declarations */

/**
 * @brief : function to initialize keypad 
 * @param keypad :the struct which has all info about the pin
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform
 */
Std_ReturnType keypad_initialize(const keypad_t *keypad);
/**
 * @brief : function to get the value from the keypad 
 * @param keypad :the struct which has all info about the pin
 * @param value: pointer to variable to save the value
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform
 */
Std_ReturnType keypad_get_value(const keypad_t *keypad, uint8 *value );


#endif	/* ECU_KEYPAD_H */

