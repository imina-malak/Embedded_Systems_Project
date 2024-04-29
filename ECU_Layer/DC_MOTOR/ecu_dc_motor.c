/* 
 * File:   ecu_dc_motor.c
 * Author: imina
 *
 * Created on November 9, 2023, 3:25 PM
 */

#include "ecu_dc_motor.h"

/**
 * @brief: function to initialize DC_motor
 * @param: led: the struct which has all info about the pin
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType dc_motor_initialize(const dc_motor_t *motor){
    Std_ReturnType ret = E_OK;
    if (NULL==motor){
        ret = E_NOT_OK;
    }
    else{
        
        gpio_pin_initialize(&(motor->dc_motor_config[0]));   
        gpio_pin_initialize(&(motor->dc_motor_config[1]));        
    }
    return ret;
}
/**
 * @brief: function to turn DC_motor right
 * @param: led: the struct which has all info about the pin
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType dc_motor_turn_right(const dc_motor_t *motor){
    Std_ReturnType ret = E_OK;
    if (NULL==motor){
        ret = E_NOT_OK;
    }
    else{

        gpio_pin_write_logic(&(motor->dc_motor_config[0]),HIGH);
        gpio_pin_write_logic(&(motor->dc_motor_config[1]),LOW);


    } 
    return ret;
}
    
/**
 * @brief: function to turn DC_motor left
 * @param: led: the struct which has all info about the pin
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType dc_motor_turn_left(const dc_motor_t *motor){
    Std_ReturnType ret = E_OK;
    if (NULL==motor){
        ret = E_NOT_OK;
    }
    else{

        gpio_pin_write_logic(&(motor->dc_motor_config[0]),LOW);
        gpio_pin_write_logic(&(motor->dc_motor_config[1]),HIGH);
        
    }        
     return ret;       
}
/**
 * @brief: function to stop DC_motor
 * @param: led: the struct which has all info about the pin
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType dc_motor_turn_off(const dc_motor_t *motor){
    Std_ReturnType ret = E_OK;
    if (NULL==motor){
        ret = E_NOT_OK;
    }
    else{
        gpio_pin_write_logic(&(motor->dc_motor_config[0]),LOW);
        gpio_pin_write_logic(&(motor->dc_motor_config[1]),LOW);
    }
    return ret;   
}