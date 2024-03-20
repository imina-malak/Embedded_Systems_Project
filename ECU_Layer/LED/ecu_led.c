/* 
 * File:   ecu_led.c
 * Author: imina
 *
 * Created on November 9, 2023, 3:25 PM
 */

#include "ecu_led.h"

/**
 * @brief: function to initialize led
 * @param: led: the struct which has all info about the pin
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType led_initialize(const led_t *led){
    Std_ReturnType ret = E_OK;
    if (NULL==led){
        ret = E_NOT_OK;
    }
    else{
        gpio_pin_initialize(&(led->led_config));
    }
    return ret;
}

/**
 * @brief: function to turn on led
 * @param: led: the struct which has all info about the pin
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType led_turn_on(const led_t *led){
    Std_ReturnType ret = E_OK;
    if (NULL==led){
        ret = E_NOT_OK;
    }
    else{
        gpio_pin_write_logic(&(led->led_config),HIGH);
    }
    
    
    return ret;
}

/**
 * @brief: function to turn off led
 * @param: led: the struct which has all info about the pin
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType led_turn_off(const led_t *led){

    Std_ReturnType ret = E_OK;
    if (NULL==led){
        ret = E_NOT_OK;
    }
    else{
        gpio_pin_write_logic(&(led->led_config),LOW);

    }

    return ret;
    
}

/**
 * @brief: function to toggle led
 * @param: led: the struct which has all info about the pin
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType led_turn_toggle(const led_t *led){
    Std_ReturnType ret = E_OK;
     if (NULL==led){
        ret = E_NOT_OK;
    }
    else{
         gpio_pin_toggle_logic(&(led->led_config));
    }   
    
    return ret;
       
}
