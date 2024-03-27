
/* 
 * File:   ecu_seven_seg.c
 * Author: imina
 *
 * Created on November 9, 2023, 3:25 PM
 */
#include "ecu_seven_seg.h"


/**
 * @brief: function to initialize the 7-segment
 * @param segement : the struct which has all info about the pins
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType seven_segement_initialize(const segement_t *segement){
    Std_ReturnType ret = E_OK;
    if ((NULL ==segement)){
        ret = E_NOT_OK;
    }else
    {
        ret = gpio_pin_direction_initialize(&(segement->segemet_pins[0]));
        ret = gpio_pin_direction_initialize(&(segement->segemet_pins[1]));
        ret = gpio_pin_direction_initialize(&(segement->segemet_pins[2]));
        ret = gpio_pin_direction_initialize(&(segement->segemet_pins[3]));
    }
    return ret;   
}


/**
 * @brief: function to write specific number on seven-segment
 * @param segement: the struct which has all info about the pins
 * @param num: the number which the user want to display  
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType seven_segement_write_number (const segement_t *segement,uint8 num){
    Std_ReturnType ret = E_OK;
    if ((NULL ==segement) ||num>9 ){
        ret = E_NOT_OK;
    }else
    {
       ret= gpio_pin_write_logic(&(segement->segemet_pins[0]),(0x01 & (num>>0)));
       ret= gpio_pin_write_logic(&(segement->segemet_pins[1]),(0x01 & (num>>1)));
       ret= gpio_pin_write_logic(&(segement->segemet_pins[2]),(0x01 & (num>>2)));
       ret= gpio_pin_write_logic(&(segement->segemet_pins[3]),(0x01 & (num>>3)));
               
    }
    return ret;   
}