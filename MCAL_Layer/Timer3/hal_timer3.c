/*
 * File:   hal_timer3.c
 * Author: imina
 *
 * Created on January 31, 2024, 6:10 PM
 */

#include "hal_timer3.h"

#if TIMER3_INTERRUPT_ENABLE_ == TIMER3_INTERRUPT_FEATURE_ENABLED
    static void(*TIMER3_HANDLER_POINTER_TO_FUNCTION)(void)=NULL;
#endif


static inline void TIMER3_MODE_CONFIG (const timer3_t *timer);
static inline void TIMER3_READ_WRITE_CONFIG (const timer3_t *timer);


static uint16 timer3_preload_value=0;




/**
 * @brief: function to initialize TIMER3
 * @param timer: struct has all information about the timer3
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType TIMER3_INIT(const timer3_t *timer){
Std_ReturnType ret = E_OK;
    if(NULL == timer){
        ret=E_NOT_OK;
    }
    else{ 
        TIMER3_STOPS();
        TIMER3_PRESCALER_SELECT((timer->timer3_prescaler));
        TIMER3_MODE_CONFIG(timer);
        TIMER3_READ_WRITE_CONFIG(timer);
        TMR3H = ((timer->pre_load_value)>>8 );
        TMR3L = (uint8)(timer->pre_load_value);   
        timer3_preload_value = (timer->pre_load_value);
#if TIMER3_INTERRUPT_ENABLE_ == TIMER3_INTERRUPT_FEATURE_ENABLED
        TIMER3_INTERRUPT_ENABLE();
        TIMER3_INTERRUPT_CLEAR_FLAG();
        TIMER3_HANDLER_POINTER_TO_FUNCTION = timer->TIMER3_HANDLER;  
#if INTERRUPT_PRIORITY_FEATURE_ENABLED == INTERRUPT_PRIORITY_ENABLED
        INTERRUPT_PRIORITY_ENABLE();
        INTCONbits.GIE = 1;
        if(timer->priority == INTERRUPT_HIGH ){
            TIMER3_INTERRUPT_SET_HIGH_PRIORITY();
            INTERRUPT_GLOBAL_INTERRUPT_HIGH_ENABLE();
        }
        else if(timer->priority == INTERRUPT_LOW ){
            TIMER3_INTERRUPT_SET_LOW_PRIORITY();
            INTERRUPT_GLOBAL_INTERRUPT_LOW_ENABLE();
        }
#else
        INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
        INTERRUPT_PREPHERAL_INTERRUPT_ENABLE();        
#endif        
#endif
       T3CONbits.TMR3ON = 1;
    }return ret;        
}
/**
 * @brief: function to deinitialize TIMER3
 * @param timer: struct has all information about the timer3
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType TIMER3_DEINIT(const timer3_t *timer){
    Std_ReturnType ret = E_OK;
    if(NULL == timer){
        ret=E_NOT_OK;
    }
    else{    
        TIMER3_STOPS();
        #if TIMER3_INTERRUPT_ENABLE_ == TIMER3_INTERRUPT_FEATURE_ENABLED
        TIMER3_INTERRUPT_DISABLE();
        #endif 
    }
    return ret;       
}
/**
 * @brief: function to write value in counter register
 * @param timer: struct has all information about the timer3
 * @param value: parameter to save the value to write it in counter register 
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType TIMER3_WRITE_VALUE(const timer3_t *timer,uint16 value ){
    Std_ReturnType ret = E_OK;
    if(NULL == timer ){
        ret=E_NOT_OK;
    }
    else{     
        TMR3H = ((value)>>8 );
        TMR3L = (uint8)(value);
    }
    return ret;  
    
        
}
/**
 * @brief: function to read value in counter register
 * @param timer: struct has all information about the timer3
 * @param value: pointer to variable to save the value in counter register
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType TIMER3_READ_VALUE(const timer3_t *timer, uint16 *value){
    Std_ReturnType ret = E_OK;
    uint8 timer3L = 0;
    uint8 timer3H = 0;
    if((NULL == timer)&&(NULL== value) ){
        ret=E_NOT_OK;
    }
    else{   
        timer3L =TMR3L;
        timer3H= TMR3H;
        *value = (uint16)( (timer3H<<8) + timer3L);
    }
    return ret;      
}

/**
 * @brief: function to choose the mode of the Timer1
 * @param timer: struct has all information about the timer1
 */
static inline void TIMER3_MODE_CONFIG (const timer3_t *timer)
{
    if(timer->mode == TIMER3_TIMER_MODE  )
    {
        TIMER3_TIMER_MODE_ENABLE();
    }
    
    else if(timer->mode ==TIMER3_counter_MODE  )
    {
        TIMER3_COUNTER_MODE_ENABLE();
        if(timer->counter_mode == TIMER3_SYNCHRONOUS_MODE )
        {
            TIMER3_SYNCHRONOUS_MODE_ENABLE();
        }
        else if(timer->counter_mode == TIMER3_ASYNCHRONOUS_MODE )
        {
            TIMER3_ASYNCHRONOUS_MODE_ENABLE();
        }  
    }        
}

/**
 * @brief: helper function to determine the register size
 * @param timer: struct has all information about the timer1
 */
static inline void TIMER3_READ_WRITE_CONFIG (const timer3_t *timer)
{
    if(timer->read_write_mode == TIMER3_8_BIT_TIMER )
    {
        TIMER3_8_BIT_TIMER_ENABLE();
    }
    else if(timer->read_write_mode == TIMER3_16_BIT_TIMER )
    {
        TIMER3_16_BIT_TIMER_ENABLE();
    }        
}
/**
 * function to execute the ISR 
 */
void TIMER3_ISR(void){
    TIMER3_INTERRUPT_CLEAR_FLAG();
    TMR3H = ((timer3_preload_value)>>8 );
    TMR3L = (uint8)(timer3_preload_value);
    if(TIMER3_HANDLER_POINTER_TO_FUNCTION)
    {
    TIMER3_HANDLER_POINTER_TO_FUNCTION();
    }        
}
