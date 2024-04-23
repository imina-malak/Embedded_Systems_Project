/* 
 * File:   hal_timer1.h
 * Author: imina
 *
 * Created on January 29, 2024, 2:48 PM
 */

#ifndef HAL_TIMER1_H
#define	HAL_TIMER1_H

/* section: Includes */
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../INTERRUPTS/mcal_internal_interrupt.h"
#include "pic18f4620.h"
/* section: Macro Declarations */

#define TIMER1_TIMER_MODE   0
#define TIMER1_counter_MODE 1

#define TIMER1_SYNCHRONOUS_MODE   0
#define TIMER1_ASYNCHRONOUS_MODE  1

#define TIMER1_OSCILLATOR_ON       1
#define TIMER1_OSCILLATOR_SHUT_OFF 0

#define TIMER1_8_BIT_TIMER         0
#define TIMER1_16_BIT_TIMER        1

/* section: Macro functions Declarations */
#define TIMER1_ENABLES()                       (T1CONbits.TMR1ON = 1) 
#define TIMER1_STOPS()                         (T1CONbits.TMR1ON = 0) 

#define TIMER1_COUNTER_MODE_ENABLE()           (T1CONbits.TMR1CS= 1) 
#define TIMER1_TIMER_MODE_ENABLE()             (T1CONbits.TMR1CS= 0) 

#define TIMER1_SYNCHRONOUS_MODE_ENABLE()       (T1CONbits.T1SYNC= 0) 
#define TIMER1_ASYNCHRONOUS_MODE_ENABLE()      (T1CONbits.T1SYNC= 1) 

#define TIMER1_OSCILLATOR_ENABLE()             (T1CONbits.T1OSCEN= 1) 
#define TIMER1_OSCILLATOR_DISABLE()            (T1CONbits.T1OSCEN= 0) 

#define TIMER1_SYSTEM_CLOCK_STATUS()           (T1CONbits.T1RUN)

#define TIMER1_8_BIT_TIMER_ENABLE()            (T1CONbits.RD16 = 0)
#define TIMER1_16_BIT_TIMER_ENABLE()           (T1CONbits.RD16 = 1)

#define TIMER1_PRESCALER_SELECT(_PRES)         (T1CONbits.T1CKPS = _PRES) 

/* section: Data type Declarations */

typedef enum {
    TIMER1_PRESCALER_DIV_BY_1 = 0, 
    TIMER1_PRESCALER_DIV_BY_2, 
    TIMER1_PRESCALER_DIV_BY_4, 
    TIMER1_PRESCALER_DIV_BY_8,
}timer1_prescaler_select_t;

typedef struct {
    #if TIMER1_INTERRUPT_ENABLE_ == TIMER1_INTERRUPT_FEATURE_ENABLED
    void(*TIMER1_HANDLER)(void);
    interrupt_priority_t priority;
    #endif      
    uint8 mode: 1;   
    uint8 counter_mode: 1;         
    uint8 oscillator_mode: 1;
    uint8 read_write_mode:1;
    timer1_prescaler_select_t timer1_prescaler;
    uint8 reserved: 4;         
    uint16 pre_load_value;
}timer1_t;


/* section: functions Declarations */
/**
 * @brief: function to initialize TIMER1
 * @param timer: struct has all information about the timer1
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType TIMER1_INIT(const timer1_t *timer);
/**
 * @brief: function to deinitialize TIMER1
 * @param timer: struct has all information about the timer1
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType TIMER1_DEINIT(const timer1_t *timer);
/**
 * @brief: function to write value in counter register
 * @param timer: struct has all information about the timer1
 * @param value: parameter to save the value to write it in counter register 
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType TIMER1_WRITE_VALUE(const timer1_t *timer,uint16 value );
/**
 * @brief: function to read value in counter register
 * @param timer: struct has all information about the timer1
 * @param value: pointer to variable to save the value in counter register
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType TIMER1_READ_VALUE(const timer1_t *timer, uint16 *value);
/**
 * function to execute the ISR 
 */
void TIMER1_ISR(void);

#endif	/* HAL_TIMER1_H */