/* 
 * File:   hal_timer2.h
 * Author: imina
 *
 * Created on January 31, 2024, 6:05 PM
 */

#ifndef NEWFILE_H
#define	NEWFILE_H

/* section: Includes */
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../INTERRUPTS/mcal_internal_interrupt.h"
#include "pic18f4620.h"
/* section: Macro Declarations */

#define TIMER2_POSTSCALER_DIV_BY_1   0
#define TIMER2_POSTSCALER_DIV_BY_2   1
#define TIMER2_POSTSCALER_DIV_BY_3   2
#define TIMER2_POSTSCALER_DIV_BY_4   3
#define TIMER2_POSTSCALER_DIV_BY_5   4
#define TIMER2_POSTSCALER_DIV_BY_6   5
#define TIMER2_POSTSCALER_DIV_BY_7   6
#define TIMER2_POSTSCALER_DIV_BY_8   7 
#define TIMER2_POSTSCALER_DIV_BY_9   8
#define TIMER2_POSTSCALER_DIV_BY_10  9 
#define TIMER2_POSTSCALER_DIV_BY_11  10 
#define TIMER2_POSTSCALER_DIV_BY_12  11 
#define TIMER2_POSTSCALER_DIV_BY_13  12
#define TIMER2_POSTSCALER_DIV_BY_14  13 
#define TIMER2_POSTSCALER_DIV_BY_15  14
#define TIMER2_POSTSCALER_DIV_BY_16  15


#define TIMER2_PRESCALER_DIV_BY_1   0
#define TIMER2_PRESCALER_DIV_BY_4   1
#define TIMER2_PRESCALER_DIV_BY_16  2


/* section: Macro functions Declarations */
#define TIMER2_ENABLES()                       (T2CONbits.TMR2ON = 1) 
#define TIMER2_STOPS()                         (T2CONbits.TMR2ON = 0) 

#define TIMER2_PRESCALER_SELECT(_PRES)          (T2CONbits.T2CKPS = _PRES) 
#define TIMER2_POSTSCALER_SELECT(_POST)         (T2CONbits.TOUTPS = _POST) 


/* section: Data type Declarations */

typedef struct {
    #if TIMER2_INTERRUPT_ENABLE_ == TIMER2_INTERRUPT_FEATURE_ENABLED
    void(*TIMER2_HANDLER)(void);
    interrupt_priority_t priority;
    #endif      
    uint8 pre_load_value;
    uint8 timer2_prescaler_value:2;
    uint8 timer2_postscaler_value:4;
    uint8 reserved: 2;         
}timer2_t;

/* section: functions Declarations */

/**
 * @brief: function to initialize TIMER2
 * @param timer: struct has all information about the timer2
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType TIMER2_INIT(const timer2_t *timer);
/**
 * @brief: function to deinitialize TIMER2
 * @param timer: struct has all information about the timer2
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType TIMER2_DEINIT(const timer2_t *timer);
/**
 * @brief: function to write value in counter register
 * @param timer: struct has all information about the timer2
 * @param value: parameter to save the value to write it in counter register 
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType TIMER2_WRITE_VALUE(const timer2_t *timer,uint8 value );
/**
 * @brief: function to read value in counter register
 * @param timer: struct has all information about the timer2
 * @param value: pointer to variable to save the value in counter register
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType TIMER2_READ_VALUE(const timer2_t *timer, uint8 *value);
/**
 * function to execute the ISR 
 */
void TIMER2_ISR(void);

#endif	/* hal_timer2 */

