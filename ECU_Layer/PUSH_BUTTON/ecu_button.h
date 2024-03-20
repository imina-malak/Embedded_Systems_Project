/* 
 * File:   ecu_button.h
 * Author: imina
 *
 * Created on December 1, 2023, 2:02 PM
 */

#ifndef ECU_BUTTON_H
#define	ECU_BUTTON_H

/* section: Includes */
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
/* section: Macro Declarations */

/* section: Macro functions Declarations */

/* section: Data type Declarations */

typedef enum{
    BUTTON_RELEASED,
    BUTTON_PRESSED
}button_status_t;

typedef enum{
    BUTTON_ACTIVE_LOW,
    BUTTON_ACTIVE_HIGH    
}button_active_t;

typedef struct{
    Pin_config_t    button_config;
    button_status_t button_status;
    button_active_t button_active;
}button_t;

/* section: functions Declarations */
/**
 * @brief: function to initialize push button 
 * @param: btn: the struct which has all info about the pin
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType button_initialize(const button_t *btn);
/**
 * @brief: functon to read the button status(pressed or released)
 * @param btn: the struct which has all info about the pin
 * @param btn_status: pointer to save the button status(pressed or released)
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType button_read_status(const button_t *btn,button_status_t *btn_status); 
#endif	/* ECU_BUTTON_H */
