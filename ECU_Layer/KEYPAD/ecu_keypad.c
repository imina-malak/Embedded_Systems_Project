/* 
 * File:   ecu_keypad.c
 * Author: imina
 *
 * Created on November 9, 2023, 3:25 PM
 */

#include "ecu_keypad.h"

static const uint8 keypad_values [ECU_KEYPAD_ROWS][ECU_KEYPAD_COLUMNS]={
                                                        {'7','8','9','/'},
                                                        {'4','5','6','*'},
                                                        {'1','2','3','-'},
                                                        {'#','0','=','+'},
};

/**
 * @brief : function to initialize keypad 
 * @param keypad :the struct which has all info about the pin
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform
 */
Std_ReturnType keypad_initialize(const keypad_t *keypad){
    Std_ReturnType ret = E_OK;
    if (NULL==keypad){
        ret = E_NOT_OK;
    }
    else{
        for(uint8 rows = 0; rows < ECU_KEYPAD_ROWS ;rows++){
            ret=gpio_pin_initialize(&(keypad->keypad_rows_config[rows]));
        }
        for(uint8 columns=0;columns<ECU_KEYPAD_COLUMNS;columns++){
            ret=gpio_pin_direction_initialize(&(keypad->keypad_columns_config[columns]));
        }      
    }
    return ret;
    
}

/**
 * @brief : function to get the value from the keypad 
 * @param keypad :the struct which has all info about the pin
 * @param value: pointer to variable to save the value
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform
 */
Std_ReturnType keypad_get_value(const keypad_t *keypad, uint8 *value ){
    Std_ReturnType ret = E_OK;
    Logic_t get_value=LOW;
    if ((NULL==keypad)||(NULL==value)){
        ret = E_NOT_OK;
    }
    else{
        for(uint8 rows =0;rows<ECU_KEYPAD_ROWS;rows++){
            for(uint8 i=0;i<ECU_KEYPAD_ROWS;i++){
                ret = gpio_pin_write_logic(&(keypad->keypad_rows_config[i]),LOW);
            }
            ret = gpio_pin_write_logic(&(keypad->keypad_rows_config[rows]),HIGH);
            for(uint8 columns=0;columns<ECU_KEYPAD_COLUMNS;columns++){
                ret = gpio_pin_read_logic(&(keypad->keypad_columns_config[columns]),&get_value);
                if(get_value==HIGH){
                    *value=keypad_values[rows][columns];
                }
            }           
        }
    }
    return ret;    
}