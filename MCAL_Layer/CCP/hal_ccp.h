/* 
 * File:   hal_ccp.h
 * Author: imina
 *
 * Created on February 2, 2024, 1:07 PM
 */

#ifndef HAL_CCP_H
#define	HAL_CCP_H

/* section: Includes */
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../INTERRUPTS/mcal_internal_interrupt.h"
#include "pic18f4620.h"
#include "ccp_cfg.h"
/* section: Macro Declarations */

#define CCP_MODULE_DISABLE                 ((uint8)0x00)

#define CCP_CAPTURE_MODE_1_FALLING_EDGE    ((uint8)0x04)
#define CCP_CAPTURE_MODE_1_RISING_EDGE     ((uint8)0x05)
#define CCP_CAPTURE_MODE_4_RISING_EDGE     ((uint8)0x06)
#define CCP_CAPTURE_MODE_16_RISING_EDGE    ((uint8)0x07)

#define CCP_COMPARE_MODE_SET_PIN_LOW       ((uint8)0x08)
#define CCP_COMPARE_MODE_SET_PIN_HIGH      ((uint8)0x09)
#define CCP_COMPARE_MODE_TOGGLE_ON_MATCH   ((uint8)0x02)
#define CCP_COMPARE_MODE_GEN_SW_INTERRUPT  ((uint8)0x0A)
#define CCP_COMPARE_MODE_GEN_EVENT         ((uint8)0x0B)

#define CCP_PWM_MODE                       ((uint8)0x0C)

/* CCP1 Capture Mode State  */
#define CCP_CAPTURE_NOT_READY              0X00
#define CCP_CAPTURE_READY                  0X01

/* CCP1 Compare Mode State  */
#define CCP_COMPARE_NOT_READY              0X00
#define CCP_COMPARE_READY                  0X01

#define CCP_TIMER2_POSTSCALER_DIV_BY_1   1
#define CCP_TIMER2_POSTSCALER_DIV_BY_2   2
#define CCP_TIMER2_POSTSCALER_DIV_BY_3   3
#define CCP_TIMER2_POSTSCALER_DIV_BY_4   4
#define CCP_TIMER2_POSTSCALER_DIV_BY_5   5
#define CCP_TIMER2_POSTSCALER_DIV_BY_6   6
#define CCP_TIMER2_POSTSCALER_DIV_BY_7   7
#define CCP_TIMER2_POSTSCALER_DIV_BY_8   8 
#define CCP_TIMER2_POSTSCALER_DIV_BY_9   9
#define CCP_TIMER2_POSTSCALER_DIV_BY_10  10 
#define CCP_TIMER2_POSTSCALER_DIV_BY_11  11 
#define CCP_TIMER2_POSTSCALER_DIV_BY_12  12 
#define CCP_TIMER2_POSTSCALER_DIV_BY_13  13
#define CCP_TIMER2_POSTSCALER_DIV_BY_14  14 
#define CCP_TIMER2_POSTSCALER_DIV_BY_15  15
#define CCP_TIMER2_POSTSCALER_DIV_BY_16  16

#define CCP_TIMER2_PRESCALER_DIV_BY_1   1
#define CCP_TIMER2_PRESCALER_DIV_BY_4   4
#define CCP_TIMER2_PRESCALER_DIV_BY_16  16

/* section: Macro functions Declarations */
#define CCP1_SET_MODE(_mode)       (CCP1CONbits.CCP1M = _mode)
#define CCP2_SET_MODE(_mode)       (CCP2CONbits.CCP2M = _mode)

/* section: Data type Declarations */
typedef enum{
    CCP_CAPTURE_MODE_SELECTED = 0, /* Select CCP Capture Mode */
    CCP_COMPARE_MODE_SELECTED,     /* Select CCP Compare Mode */
    CCP_PWM_MODE_SELECTED          /* Select CCP PWM Mode */
}ccp_mode_t;

typedef union{
    struct{
        uint8 ccp_low;  /* CCPR1 low register */
        uint8 ccp_high; /* CCPR1 high register */
    };
    struct{
        uint16 ccp_16Bit; /* Read CCPR1 as a 16 Bit value */
    };
}CCP_REG_T;

typedef enum {
    CCP1_Current_,
    CCP2_Current_       
}ccp_current_t;


typedef enum{
    CCP1_CCP2_TIMER3 = 0,
    CCP1_TIMER1_CCP2_TIMER3,
    CCP1_CCP2_TIMER1
}ccp_capture_compare_timer_t;

typedef struct {
    ccp_current_t ccp_current;
    ccp_mode_t ccp_mode;
    uint8 ccp_mode_variant;   
    Pin_config_t ccp_pin;
    ccp_capture_compare_timer_t ccp_capture_timer;
#if (CCP1_CFG_MODE_SELECTED == CCP_CFG_PWM_MODE_SELECTED) || (CCP2_CFG_MODE_SELECTED == CCP_CFG_PWM_MODE_SELECTED)   
    uint32 PWM_Frequency;
    uint8 timer2_prescaler_value:2;
    uint8 timer2_postscaler_value:4;    
#endif
#if CCP1_INTERRUPT_ENABLE_ == CCP1_INTERRUPT_FEATURE_ENABLED
    void(*CCP1_HANDLER)(void);
    interrupt_priority_t ccp1_priority;
#endif
#if CCP2_INTERRUPT_ENABLE_ == CCP2_INTERRUPT_FEATURE_ENABLED
    void(*CCP2_HANDLER)(void);
    interrupt_priority_t ccp2_priority;
#endif
}ccp_t;
/* section: functions Declarations */

/**
 * @brief: function to initialize the CCP module 
 * @param _ccp_obj: struct has all information about CCP
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */  
Std_ReturnType CCP_Init(const ccp_t *_ccp_obj);

/**
 * @brief: function to deinitialize the CCP module 
 * @param _ccp_obj: struct has all information about CCP
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */  
Std_ReturnType CCP_DeInit(const ccp_t *_ccp_obj);

#if (CCP1_CFG_MODE_SELECTED == CCP_CFG_CAPTUTR_MODE_SELECTED) || (CCP2_CFG_MODE_SELECTED == CCP_CFG_CAPTUTR_MODE_SELECTED)   
/**
 * @brief: function to know if the data ready to be read or not
 * @param _ccp_obj: struct has all information about CCP
 * @param _capture_status: variable to save status of CCP
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */  
Std_ReturnType CCP_IsCapturedDataReady(const ccp_t *_ccp_obj,uint8 *_capture_status);
/**
 * @brief: function to read the capture value
 * @param _ccp_obj: struct has all information about CCP
 * @param capture_value: capture value saved in CCP_REGISTER
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */  
Std_ReturnType CCP_Capture_Mode_Read_Value(const ccp_t *_ccp_obj,uint16 *capture_value);
#endif

#if (CCP1_CFG_MODE_SELECTED == CCP_CFG_COMPARE_MODE_SELECTED) || (CCP2_CFG_MODE_SELECTED == CCP_CFG_COMPARE_MODE_SELECTED)   
/**
 * @brief: function to know if the CCP reached the value of not
 * @param _ccp_obj: struct has all information about CCP
 * @param _compare_status: variable to save status of CCP
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */  
Std_ReturnType CCP_IsCompareComplete(const ccp_t *_ccp_obj,uint8 *_compare_status);
/**
 * @brief: function to give the CCP Value to be compared
 * @param _ccp_obj: struct has all information about CCP
 * @param compare_value: value that you want to reach
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */ 
Std_ReturnType CCP_Compare_Mode_Set_Value(const ccp_t *_ccp_obj, uint16 compare_value);
#endif

#if (CCP1_CFG_MODE_SELECTED == CCP_CFG_PWM_MODE_SELECTED) || (CCP2_CFG_MODE_SELECTED == CCP_CFG_PWM_MODE_SELECTED)   
/**
 * @brief: function to set the duty time (PEAK of the wave)
 * @param _ccp_obj: struct has all information about CCP
 * @param _duty: percentage number
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */ 
Std_ReturnType CCP_PWM_Set_Duty(const ccp_t *_ccp_obj, const uint8 _duty);
/**
 * @brief: function to start PMW mode
 * @param _ccp_obj: struct has all information about CCP
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */ 
Std_ReturnType CCP_PWM_Start(const ccp_t *_ccp_obj);
/**
 * @brief: function to stop PMW mode
 * @param _ccp_obj: struct has all information about CCP
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */ 
Std_ReturnType CCP_PWM_Stop(const ccp_t *_ccp_obj);
#endif

/**
 * function to execute the ISR of CCP1
 */
void CCP1_ISR(void);
/**
 * function to execute the ISR of CCP2
 */
void CCP2_ISR(void);

#endif	/* HAL_CCP1_H */

