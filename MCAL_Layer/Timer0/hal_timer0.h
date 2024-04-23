/* 
 * File:   hal_timer0.h
 * Author: imina
 *
 * Created on January 28, 2024, 6:35 PM
 */

#ifndef HAL_TIMER0_H
#define	HAL_TIMER0_H

/* section: Includes */
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../INTERRUPTS/mcal_internal_interrupt.h"
#include "pic18f4620.h"

/* section: Macro Declarations */
#define TIMER0_ENABLE_PRESCALER 1
#define TIMER0_DISABLE_PRESCALER 0

#define TIMER0_RISING_EDGE  1
#define TIMER0_FALLING_EDGE 0

#define TIMER0_TIMER_MODE   1
#define TIMER0_counter_MODE 0

#define TIMER0_reg_8_BIT   1
#define TIMER0_reg_16_BIT  0

/* section: Macro functions Declarations */
#define TIMER0_ENABLES()                (T0CONbits.TMR0ON = 1) 
#define TIMER0_STOPS()                  (T0CONbits.TMR0ON = 0) 

#define TIMER0_8_BIT_TIMER_COUNTER()    (T0CONbits.T08BIT = 1) 
#define TIMER0_16_BIT_TIMER_COUNTER()   (T0CONbits.T08BIT = 0) 

#define TIMER0_COUNTER_MODE_ENABLE()    (T0CONbits.T0CS= 1) 
#define TIMER0_TIMER_MODE_ENABLE()      (T0CONbits.T0CS = 0) 

#define TIMER0_HIGH_TO_LOW_EDGE()       (T0CONbits.T0SE = 1) 
#define TIMER0_LOW_TO_HIGH_EDGE()       (T0CONbits.T0SE = 0)

#define TIMER0_PRESCALER_ENABLE()       (T0CONbits.PSA = 0) 
#define TIMER0_PRESCALER_DISABLE()      (T0CONbits.PSA = 1)

#define TIMER0_PRESCALER_VALUE(_value)  (T0CONbits.T0PS= _value)

/* section: Data type Declarations */
typedef enum {
    TIMER0_PRESCALER_DIV_BY_2, 
    TIMER0_PRESCALER_DIV_BY_4, 
    TIMER0_PRESCALER_DIV_BY_8, 
    TIMER0_PRESCALER_DIV_BY_16, 
    TIMER0_PRESCALER_DIV_BY_32, 
    TIMER0_PRESCALER_DIV_BY_46, 
    TIMER0_PRESCALER_DIV_BY_128, 
    TIMER0_PRESCALER_DIV_BY_256, 
}timer0_prescaler_select_t;

typedef struct{
    #if TIMER0_INTERRUPT_ENABLE_ == TIMER0_INTERRUPT_FEATURE_ENABLED
    void(*TIMER0_HANDLER)(void);
    interrupt_priority_t priority;
    #endif    
    uint8 reg_size: 1;     
    uint8 mode: 1;         
    uint8 edge: 1;     
    uint8 enable_prescaler: 1; 
    timer0_prescaler_select_t timer0_prescaler_value;
    uint16 pre_load_value;
    uint8 reserved: 4;         
}timer0_t;

/* section: functions Declarations */
/**
 * @brief: function to initialize TIMER0
 * @param timer
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType TIMER0_INIT(const timer0_t *timer);
/**
 * @brief: function to deinitialize TIMER0
 * @param timer
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType TIMER0_DEINIT(const timer0_t *timer);
/**
 * @brief: function to write value in counter register
 * @param timer: struct has all information about the timer0 
 * @param value: parameter to save the value to write it in counter register 
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType TIMER0_WRITE_VALUE(const timer0_t *timer,uint16 value );
/**
 * @brief: function to read value in counter register
 * @param timer: struct has all information about the timer0 
 * @param value: pointer to variable to save the value in counter register
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType TIMER0_READ_VALUE(const timer0_t *timer, uint16 *value);
/**
 * function to execute the ISR 
 */
void TIMER0_ISR(void);
#endif	/* HAL_TIMER0_H */

