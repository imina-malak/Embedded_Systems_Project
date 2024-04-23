/* 
 * File:   hal_timer3.h
 * Author: imina
 *
 * Created on January 31, 2024, 6:10 PM
 */

#ifndef HAL_TIMER3_H
#define	HAL_TIMER3_H

/* section: Includes */
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../INTERRUPTS/mcal_internal_interrupt.h"
#include "pic18f4620.h"
/* section: Macro Declarations */

#define TIMER3_TIMER_MODE   0
#define TIMER3_counter_MODE 1

#define TIMER3_SYNCHRONOUS_MODE   0
#define TIMER3_ASYNCHRONOUS_MODE  1

#define TIMER3_8_BIT_TIMER         0
#define TIMER3_16_BIT_TIMER        1

/* section: Macro functions Declarations */
#define TIMER3_ENABLES()                       (T3CONbits.TMR3ON = 1) 
#define TIMER3_STOPS()                         (T3CONbits.TMR3ON = 0) 

#define TIMER3_COUNTER_MODE_ENABLE()           (T3CONbits.TMR3CS= 1) 
#define TIMER3_TIMER_MODE_ENABLE()             (T3CONbits.TMR3CS= 0) 

#define TIMER3_SYNCHRONOUS_MODE_ENABLE()       (T3CONbits.T3SYNC= 0) 
#define TIMER3_ASYNCHRONOUS_MODE_ENABLE()      (T3CONbits.T3SYNC= 1) 

#define TIMER3_8_BIT_TIMER_ENABLE()            (T3CONbits.RD16 = 0)
#define TIMER3_16_BIT_TIMER_ENABLE()           (T3CONbits.RD16 = 1)

#define TIMER3_PRESCALER_SELECT(_PRES)         (T3CONbits.T3CKPS = _PRES) 


/* section: Data type Declarations */
typedef enum {
    TIMER3_PRESCALER_DIV_BY_1 = 0, 
    TIMER3_PRESCALER_DIV_BY_2, 
    TIMER3_PRESCALER_DIV_BY_4, 
    TIMER3_PRESCALER_DIV_BY_8,
}timer3_prescaler_select_t;


typedef struct {
    #if TIMER3_INTERRUPT_ENABLE_ == TIMER3_INTERRUPT_FEATURE_ENABLED
    void(*TIMER3_HANDLER)(void);
    interrupt_priority_t priority;
    #endif      
    uint8 mode: 1;   
    uint8 counter_mode: 1;         
    uint8 read_write_mode:1;
    timer3_prescaler_select_t timer3_prescaler;
    uint8 reserved: 3;         
    uint16 pre_load_value;
}timer3_t;

/* section: functions Declarations */

/**
 * @brief: function to initialize TIMER3
 * @param timer: struct has all information about the timer3
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType TIMER3_INIT(const timer3_t *timer);
/**
 * @brief: function to deinitialize TIMER3
 * @param timer: struct has all information about the timer3
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType TIMER3_DEINIT(const timer3_t *timer);
/**
 * @brief: function to write value in counter register
 * @param timer: struct has all information about the timer3
 * @param value: parameter to save the value to write it in counter register 
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType TIMER3_WRITE_VALUE(const timer3_t *timer,uint16 value );
/**
 * @brief: function to read value in counter register
 * @param timer: struct has all information about the timer3
 * @param value: pointer to variable to save the value in counter register
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType TIMER3_READ_VALUE(const timer3_t *timer, uint16 *value);

/**
 * function to execute the ISR 
 */
void TIMER3_ISR(void);
#endif	/* HAL_TIMER3_H */

