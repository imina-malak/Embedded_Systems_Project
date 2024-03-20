/* 
 * File:   ecu_button.c
 * Author: imina
 *
 * Created on December 1, 2023, 2:02 PM
 */
#include "ecu_button.h"

/**
 * @brief: function to initialize push button 
 * @param: btn: the struct which has all info about the pin
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType button_initialize(const button_t *btn){
    Std_ReturnType ret = E_OK;
    if(NULL == btn){
        Std_ReturnType ret = E_NOT_OK;

    }
    else
    {
        ret = gpio_pin_direction_initialize(&(btn->button_config));
    }
    return ret;
}
/**
 * 
 * @param btn: the struct which has all info about the pin
 * @param btn_status: pointer to save the button status(pressed or released)
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType button_read_status(const button_t *btn, button_status_t *btn_state){
    Std_ReturnType ret = E_NOT_OK;
    Logic_t Pin_Logic_Status = LOW;
    if((NULL == btn) || (NULL == btn_state)){
        ret = E_NOT_OK;
    }
    else{
        gpio_pin_read_logic(&(btn->button_config),&Pin_Logic_Status);
        if(BUTTON_ACTIVE_HIGH == btn->button_active){
            if(HIGH == Pin_Logic_Status){
                *btn_state = BUTTON_RELEASED;
            }
            else{
                *btn_state = BUTTON_PRESSED;
            }
        }
        else if(BUTTON_ACTIVE_LOW == btn->button_active){
            if(HIGH == Pin_Logic_Status){
                *btn_state = BUTTON_PRESSED;
            }
            else{
                *btn_state = BUTTON_RELEASED;
            }
        }
        else { /* Nothing */ }
        ret = E_OK;
    }
    return ret;
}