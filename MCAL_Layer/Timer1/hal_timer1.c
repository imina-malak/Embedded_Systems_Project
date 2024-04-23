/* 
 * File:   hal_timer1.c
 * Author: imina
 *
 * Created on January 29, 2024, 2:48 PM
 */
#include "hal_timer1.h"


#if TIMER1_INTERRUPT_ENABLE_ == TIMER1_INTERRUPT_FEATURE_ENABLED
    static void(*TIMER1_HANDLER_POINTER_TO_FUNCTION)(void)=NULL;
#endif



/**
 * @brief: function to choose the mode of the Timer1
 * @param timer: struct has all information about the timer1
 */
static inline void TIMER1_MODE_CONFIG (const timer1_t *timer);
/**
 * @brief: helper function to determine the register size
 * @param timer: struct has all information about the timer1
 */
static inline void TIMER1_READ_WRITE_CONFIG (const timer1_t *timer);


static uint16 timer1_preload_value=0;


/**
 * @brief: function to initialize TIMER1
 * @param timer: struct has all information about the timer1
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType TIMER1_INIT(const timer1_t *timer){
    Std_ReturnType ret = E_OK;
    if(NULL == timer){
        ret=E_NOT_OK;
    }
    else{ 
        TIMER1_STOPS();
        TIMER1_PRESCALER_SELECT((timer->timer1_prescaler));
        TIMER1_MODE_CONFIG(timer);
        TIMER1_READ_WRITE_CONFIG(timer);
        TMR1H = ((timer->pre_load_value)>>8 );
        TMR1L = (uint8)(timer->pre_load_value);   
        timer1_preload_value = (timer->pre_load_value);
#if TIMER1_INTERRUPT_ENABLE_ == TIMER1_INTERRUPT_FEATURE_ENABLED
        TIMER1_INTERRUPT_ENABLE();
        TIMER1_INTERRUPT_CLEAR_FLAG();
        TIMER1_HANDLER_POINTER_TO_FUNCTION = timer->TIMER1_HANDLER;  
#if INTERRUPT_PRIORITY_FEATURE_ENABLED == INTERRUPT_PRIORITY_ENABLED
        INTERRUPT_PRIORITY_ENABLE();
        INTCONbits.GIE = 1;
        if(timer->priority == INTERRUPT_HIGH ){
            TIMER1_INTERRUPT_SET_HIGH_PRIORITY();
            INTERRUPT_GLOBAL_INTERRUPT_HIGH_ENABLE();
        }
        else if(timer->priority == INTERRUPT_LOW ){
            TIMER1_INTERRUPT_SET_LOW_PRIORITY();
            INTERRUPT_GLOBAL_INTERRUPT_LOW_ENABLE();
        }
#else
        INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
        INTERRUPT_PREPHERAL_INTERRUPT_ENABLE();        
#endif        
#endif
        TIMER1_ENABLES();
    }return ret;    
}

/**
 * @brief: function to deinitialize TIMER1
 * @param timer: struct has all information about the timer1
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType TIMER1_DEINIT(const timer1_t *timer){
    Std_ReturnType ret = E_OK;
    if(NULL == timer){
        ret=E_NOT_OK;
    }
    else{    
        TIMER1_STOPS();
        #if TIMER1_INTERRUPT_ENABLE_ == TIMER1_INTERRUPT_FEATURE_ENABLED
        TIMER1_INTERRUPT_DISABLE();
        #endif 
    }
    return ret;    
}

/**
 * @brief: function to write value in counter register
 * @param timer: struct has all information about the timer1
 * @param value: parameter to save the value to write it in counter register 
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType TIMER1_WRITE_VALUE(const timer1_t *timer,uint16 value ){
    Std_ReturnType ret = E_OK;
    if(NULL == timer ){
        ret=E_NOT_OK;
    }
    else{     
        TMR1H = ((value)>>8 );
        TMR1L = (uint8)(value);
    }
    return ret;  
    
    
}
/**
 * @brief: function to read value in counter register
 * @param timer: struct has all information about the timer1
 * @param value: pointer to variable to save the value in counter register
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType TIMER1_READ_VALUE(const timer1_t *timer, uint16 *value){
    Std_ReturnType ret = E_OK;
    uint8 timer1L = 0;
    uint8 timer1H = 0;
    if((NULL == timer)&&(NULL== value) ){
        ret=E_NOT_OK;
    }
    else{   
        timer1L =TMR1L;
        timer1H= TMR1H;
        *value = (uint16)( (timer1H<<8) + timer1L);
    }
    return ret;      
}
/**
 * @brief: function to choose the mode of the Timer1
 * @param timer: struct has all information about the timer1
 */
static inline void TIMER1_MODE_CONFIG (const timer1_t *timer)
{
    if(timer->mode == TIMER1_TIMER_MODE  )
    {
        TIMER1_TIMER_MODE_ENABLE();
    }
    
    else if(timer->mode ==TIMER1_counter_MODE  )
    {
        TIMER1_COUNTER_MODE_ENABLE();
        if(timer->counter_mode == TIMER1_SYNCHRONOUS_MODE )
        {
            TIMER1_SYNCHRONOUS_MODE_ENABLE();
        }
        else if(timer->counter_mode == TIMER1_ASYNCHRONOUS_MODE )
        {
            TIMER1_ASYNCHRONOUS_MODE_ENABLE();
        }  
    }        
}
/**
 * @brief: helper function to determine the register size
 * @param timer: struct has all information about the timer1
 */
static inline void TIMER1_READ_WRITE_CONFIG (const timer1_t *timer)
{
    if(timer->read_write_mode == TIMER1_8_BIT_TIMER )
    {
        TIMER1_8_BIT_TIMER_ENABLE();
    }
    else if(timer->read_write_mode == TIMER1_16_BIT_TIMER )
    {
        TIMER1_16_BIT_TIMER_ENABLE();
    }        
}
/**
 * function to execute the ISR 
 */
void TIMER1_ISR(void){
    TIMER1_INTERRUPT_CLEAR_FLAG();
    TMR1H = ((timer1_preload_value)>>8 );
    TMR1L = (uint8)(timer1_preload_value);
    if(TIMER1_HANDLER_POINTER_TO_FUNCTION)
    {
    TIMER1_HANDLER_POINTER_TO_FUNCTION();
    }    
}

