/* 
 * File:   hal_timer2.c
 * Author: imina
 *
 * Created on January 31, 2024, 6:05 PM
 */

#include "hal_timer2.h"


#if TIMER2_INTERRUPT_ENABLE_ == TIMER2_INTERRUPT_FEATURE_ENABLED
    static void(*TIMER2_HANDLER_POINTER_TO_FUNCTION)(void)=NULL;
#endif

static uint8 timer2_preload_value=0;



/**
 * @brief: function to initialize TIMER2
 * @param timer: struct has all information about the timer2
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType TIMER2_INIT(const timer2_t *timer){
    Std_ReturnType ret = E_OK;
    if(NULL == timer){
        ret=E_NOT_OK;
    }
    else{ 
        TIMER2_STOPS();
        TIMER2_PRESCALER_SELECT((timer->timer2_prescaler_value));
        TIMER2_POSTSCALER_SELECT((timer->timer2_postscaler_value));
        TMR2 = (timer->pre_load_value); 
        timer2_preload_value = (timer->pre_load_value);
#if TIMER2_INTERRUPT_ENABLE_ == TIMER2_INTERRUPT_FEATURE_ENABLED
        TIMER2_INTERRUPT_ENABLE();
        TIMER2_INTERRUPT_CLEAR_FLAG();
        TIMER2_HANDLER_POINTER_TO_FUNCTION = timer->TIMER2_HANDLER;  
#if INTERRUPT_PRIORITY_FEATURE_ENABLED == INTERRUPT_PRIORITY_ENABLED
        INTERRUPT_PRIORITY_ENABLE();
        INTCONbits.GIE = 1;
        if(timer->priority == INTERRUPT_HIGH ){
            TIMER2_INTERRUPT_SET_HIGH_PRIORITY();
            INTERRUPT_GLOBAL_INTERRUPT_HIGH_ENABLE();
        }
        else if(timer->priority == INTERRUPT_LOW ){
            TIMER2_INTERRUPT_SET_LOW_PRIORITY();
            INTERRUPT_GLOBAL_INTERRUPT_LOW_ENABLE();
        }
#else
        INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
        INTERRUPT_PREPHERAL_INTERRUPT_ENABLE();        
#endif        
#endif
        TIMER2_ENABLES();   
    }
}

/**
 * @brief: function to deinitialize TIMER2
 * @param timer: struct has all information about the timer2
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType TIMER2_DEINIT(const timer2_t *timer){
    Std_ReturnType ret = E_OK;
    if(NULL == timer){
        ret=E_NOT_OK;
    }
    else{    
        TIMER2_STOPS();
        #if TIMER2_INTERRUPT_ENABLE_ == TIMER2_INTERRUPT_FEATURE_ENABLED
        TIMER2_INTERRUPT_DISABLE();
        #endif 
    }
    return ret;      
}
/**
 * @brief: function to write value in counter register
 * @param timer: struct has all information about the timer2
 * @param value: parameter to save the value to write it in counter register 
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType TIMER2_WRITE_VALUE(const timer2_t *timer,uint8 value ){
    Std_ReturnType ret = E_OK;
    if(NULL == timer ){
        ret=E_NOT_OK;
    }
    else{     
        TMR2 = (uint8)(value);
    }
    return ret;  
}
/**
 * @brief: function to read value in counter register
 * @param timer: struct has all information about the timer2
 * @param value: pointer to variable to save the value in counter register
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType TIMER2_READ_VALUE(const timer2_t *timer, uint8 *value){
    Std_ReturnType ret = E_OK;
    if((NULL == timer)&&(NULL== value) ){
        ret=E_NOT_OK;
    }
    else{   

        *value = (uint8)(TMR2);
    }
    return ret;      
    
}
/**
 * function to execute the ISR 
 */
void TIMER2_ISR(void){
    TIMER2_INTERRUPT_CLEAR_FLAG();
    TMR2 = (uint8)(timer2_preload_value);
    if(TIMER2_HANDLER_POINTER_TO_FUNCTION)
    {
    TIMER2_HANDLER_POINTER_TO_FUNCTION();
    }        
}