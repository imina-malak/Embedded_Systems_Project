/* 
 * File:   hal_timer0.c
 * Author: imina
 *
 * Created on January 28, 2024, 6:35 PM
 */
#include "hal_timer0.h"
/**
 * @brief: helper function to enable/disable and determine the pre-scaler value if enabled 
 * @param timer: struct has all information about the timer0 
 */
static inline void TIMER0_PRESCALER_CONFIG (const timer0_t *timer);
/**
 * @brief: helper function to determine the mode of timer0
 * @param timer: struct has all information about the timer0 
 */
static inline void TIMER0_MODE_CONFIG (const timer0_t *timer);
/**
 * @brief: helper function to determine the register size
 * @param timer: struct has all information about the timer0 
 */
static inline void TIMER0_REG_CONFIG (const timer0_t *timer);

#if TIMER0_INTERRUPT_ENABLE_ == TIMER0_INTERRUPT_FEATURE_ENABLED
    static void(*TIMER0_HANDLER_POINTER_TO_FUNCTION)(void)=NULL;
#endif
   
/*variable to save the pre-scaler value to use it in ISR */    
static uint16 timer0_preload_value=0;
/**
 * @brief: function to initialize TIMER0
 * @param timer: struct has all information about the timer0 
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType TIMER0_INIT(const timer0_t *timer){
    Std_ReturnType ret = E_OK;
    if(NULL == timer){
        ret=E_NOT_OK;
    }
    else{ 
        TIMER0_STOPS();
        TIMER0_PRESCALER_CONFIG(timer);
        TIMER0_MODE_CONFIG(timer);
        TIMER0_REG_CONFIG(timer);
        TMR0H = ((timer->pre_load_value)>>8 );
        TMR0L = (uint8)(timer->pre_load_value);
        timer0_preload_value = (timer->pre_load_value);
#if TIMER0_INTERRUPT_ENABLE_ == TIMER0_INTERRUPT_FEATURE_ENABLED
        TIMER0_INTERRUPT_ENABLE();
        TIMER0_INTERRUPT_CLEAR_FLAG();
        TIMER0_HANDLER_POINTER_TO_FUNCTION = timer->TIMER0_HANDLER;  
#if INTERRUPT_PRIORITY_FEATURE_ENABLED == INTERRUPT_PRIORITY_ENABLED
        INTERRUPT_PRIORITY_ENABLE();
        INTCONbits.GIE = 1;
        if(timer->priority == INTERRUPT_HIGH ){
            TIMER0_INTERRUPT_SET_HIGH_PRIORITY();
            INTERRUPT_GLOBAL_INTERRUPT_HIGH_ENABLE();
        }
        else if(timer->priority == INTERRUPT_LOW ){
            TIMER0_INTERRUPT_SET_LOW_PRIORITY();
            INTERRUPT_GLOBAL_INTERRUPT_LOW_ENABLE();
        }
#else
        INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
        INTERRUPT_PREPHERAL_INTERRUPT_ENABLE();        
#endif        
#endif
        TIMER0_ENABLES();
    }return ret;
}
/**
 * @brief: function to deinitialize TIMER0
 * @param timer: struct has all information about the timer0 
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType TIMER0_DEINIT(const timer0_t *timer){
    Std_ReturnType ret = E_OK;
    if(NULL == timer){
        ret=E_NOT_OK;
    }
    else{    
        TIMER0_STOPS();
#if TIMER0_INTERRUPT_ENABLE_ == TIMER0_INTERRUPT_FEATURE_ENABLED
        TIMER0_INTERRUPT_DISABLE();
#endif 
    }
    return ret;
}
/**
 * @brief: function to write value in counter register
 * @param timer: struct has all information about the timer0 
 * @param value: parameter to save the value to write it in counter register 
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType TIMER0_WRITE_VALUE(const timer0_t *timer,uint16 value ){
    Std_ReturnType ret = E_OK;
    if(NULL == timer ){
        ret=E_NOT_OK;
    }
    else{     
        TMR0H = ((value)>>8 );
        TMR0L = (uint8)(value);
    }
    return ret;    
}
/**
 * @brief: function to read value in counter register
 * @param timer: struct has all information about the timer0 
 * @param value: pointer to variable to save the value in counter register
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType TIMER0_READ_VALUE(const timer0_t *timer, uint16 *value){
    Std_ReturnType ret = E_OK;
    uint8 timer0L = 0;
    uint8 timer0H = 0;
    if((NULL == timer)&&(NULL== value) ){
        ret=E_NOT_OK;
    }
    else{   
        timer0L =TMR0L;
        timer0H= TMR0H;
        *value = (uint16)( (timer0H<<8) + timer0L);
    }
    return ret;      
}
/**
 * @brief: helper function to enable/disable and determine the pre-scaler value if enabled 
 * @param timer: struct has all information about the timer0 
 */
static inline void TIMER0_PRESCALER_CONFIG (const timer0_t *timer)
{
    if(timer->enable_prescaler == TIMER0_ENABLE_PRESCALER )
    {
        TIMER0_PRESCALER_ENABLE();
        TIMER0_PRESCALER_VALUE(timer->timer0_prescaler_value);
    }
    else if(timer->enable_prescaler == TIMER0_DISABLE_PRESCALER )
    {
        TIMER0_PRESCALER_DISABLE();
    }        
        
}
/**
 * @brief: helper function to determine the mode of timer0
 * @param timer: struct has all information about the timer0 
 */
static inline void TIMER0_MODE_CONFIG (const timer0_t *timer)
{
    if(timer->mode == TIMER0_TIMER_MODE  )
    {
        TIMER0_TIMER_MODE_ENABLE();
    }
    else if(timer->mode ==TIMER0_counter_MODE  )
    {
        TIMER0_COUNTER_MODE_ENABLE();
        if(timer->edge == TIMER0_RISING_EDGE )
        {
            TIMER0_LOW_TO_HIGH_EDGE();
        }
        else if(timer->edge == TIMER0_FALLING_EDGE )
        {
            TIMER0_HIGH_TO_LOW_EDGE();
        }  
    }        
}
/**
 * @brief: helper function to determine the register size
 * @param timer: struct has all information about the timer0 
 */
static inline void TIMER0_REG_CONFIG (const timer0_t *timer)
{
    if(timer->reg_size == TIMER0_reg_8_BIT )
    {
        TIMER0_8_BIT_TIMER_COUNTER();
    }
    else if(timer->reg_size == TIMER0_reg_16_BIT )
    {
        TIMER0_16_BIT_TIMER_COUNTER();
    }        
}
/**
 * function to execute the ISR 
 */
void TIMER0_ISR(void){
    TIMER0_INTERRUPT_CLEAR_FLAG();
    TMR0H = ((timer0_preload_value)>>8 );
    TMR0L = (uint8)(timer0_preload_value);
    if(TIMER0_HANDLER_POINTER_TO_FUNCTION)
    {
    TIMER0_HANDLER_POINTER_TO_FUNCTION();
    }
}