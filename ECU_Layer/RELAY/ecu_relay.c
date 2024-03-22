/* 
 * File:   ecu_relay.c
 * Author: imina
 *
 * Created on November 9, 2023, 3:25 PM
 */


#include "ecu_relay.h"

/**
 * @brief function to initialize relay
 * @param relay the struct which has all info about the relay
 * @return return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType relay_initialize(const relay_t *relay){
    Std_ReturnType ret = E_OK;
    if (NULL==relay){
        ret = E_NOT_OK;
    }
    else{
        gpio_pin_initialize(&(relay->relay_config));
    }
    return ret;
}

/**
 * @brief function to turn on relay
 * @param relay the struct which has all info about the relay
 * @return return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType relay_turn_on(const relay_t *relay){
    Std_ReturnType ret = E_OK;
    if (NULL==relay){
        ret = E_NOT_OK;
    }
    else{
        gpio_pin_write_logic(&(relay->relay_config),HIGH);
    }
    return ret;
}

/**
 * @brief function to turn off relay
 * @param relay the struct which has all info about the relay
 * @return return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType relay_turn_off(const relay_t *relay){
    Std_ReturnType ret = E_OK;
    if (NULL==relay){
        ret = E_NOT_OK;
    }
    else{
        gpio_pin_write_logic(&(relay->relay_config),LOW);
    }
    return ret;    
}
