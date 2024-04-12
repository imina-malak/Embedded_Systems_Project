/* 
 * File:   hal_adc.h
 * Author: imina
 *
 * Created on January 20, 2024, 5:40 PM
 */

#ifndef HAL_ADC_H
#define	HAL_ADC_H

/* section: Includes */
#include "hal_adc_cfg.h"
#include "../mcal_std_types.h"
#include "../INTERRUPTS/mcal_internal_interrupt.h"
#include "pic18f4620.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
/* section: Macro Declarations */

/*DEFINE ANALOG PINS */
#define ADC_AN0_AND_BEFORE_ANALOG  0x0E
#define ADC_AN1_AND_BEFORE_ANALOG  0x0D
#define ADC_AN2_AND_BEFORE_ANALOG  0x0C
#define ADC_AN3_AND_BEFORE_ANALOG  0x0B
#define ADC_AN4_AND_BEFORE_ANALOG  0x0A
#define ADC_AN5_AND_BEFORE_ANALOG  0x09
#define ADC_AN6_AND_BEFORE_ANALOG  0x08
#define ADC_AN7_AND_BEFORE_ANALOG  0x07
#define ADC_AN8_AND_BEFORE_ANALOG  0x06
#define ADC_AN9_AND_BEFORE_ANALOG  0x05
#define ADC_AN10_AND_BEFORE_ANALOG 0x04
#define ADC_AN11_AND_BEFORE_ANALOG 0x03
#define ADC_AN12_AND_BEFORE_ANALOG 0x02
#define ADC_ALL_ANALOG             0x00
#define ADC_ALL_DIGITAL            0x0F


#define ADC_ENABLE_VOLTAGE_REF        0x01
#define ADC_DISENABLE_VOLTAGE_REF     0x00
#define ADC_RESULT_RIGHT              0x01U
#define ADC_RESULT_LEFT               0x00U

#define ADC_CONVERSION_IS_DONE              0x01U
#define ADC_CONVERSION_IS_NOT_DONE          0x00U
/* section: Macro functions Declarations */
#define ADC_CONVERTER_ENABLE()     (ADCON0bits.ADON = 1)
#define ADC_CONVERTER_DISABLE()    (ADCON0bits.ADON = 0)
#define ADC_CONVERSION_STATUS()    (ADCON0bits.GO_nDONE)
#define ADC_START_CONVERSION()     (ADCON0bits.GO_nDONE = 1)
/*use the VSS AND VDD or use OUTPUT VOLTAGE */
#define ADC_DISABLE_VOLTAGE_REF_FORMAT() do{ADCON1bits.VCFG0 = 0;\
                                            ADCON1bits.VCFG1 = 0;\
                                            }while(0)
#define ADC_ENABLE_VOLTAGE_REF_FORMAT() do{ADCON1bits.VCFG0 = 1;\
                                           ADCON1bits.VCFG1 = 1;\
                                           }while(0)
/*configure which pins to be ANALOG*/
#define ADC_DIGITAL_ANALOG_CONFIG(_config) (ADCON1bits.PCFG = _config)
/*RIGHT or LEFT justified */
#define ADC_RESULT_RIGHT_FORMAT()   (ADCON2bits.ADFM = 1)
#define ADC_RESULT_LEFT_FORMAT()    (ADCON2bits.ADFM = 0)
/* section: Data type Declarations */

//CHANNEL NUMBER
typedef enum{
    ADC_CHANNEL_AN0 = 0,
    ADC_CHANNEL_AN1 ,
    ADC_CHANNEL_AN2 ,
    ADC_CHANNEL_AN3 ,
    ADC_CHANNEL_AN4 ,
    ADC_CHANNEL_AN5 ,
    ADC_CHANNEL_AN6 ,
    ADC_CHANNEL_AN7 ,
    ADC_CHANNEL_AN8 ,
    ADC_CHANNEL_AN9 ,
    ADC_CHANNEL_AN10 ,
    ADC_CHANNEL_AN11 ,
    ADC_CHANNEL_AN12 
}adc_channel_select_t;
typedef enum{
    ADC_0_Tad = 0,
    ADC_2_Tad ,
    ADC_4_Tad ,
    ADC_6_Tad ,
    ADC_8_Tad ,
    ADC_12_Tad ,
    ADC_16_Tad ,
    ADC_20_Tad ,
}adc_acquisition_time_t;
typedef enum {
    ADC_CONVERSION_CLOCK_FOSC_DIV_2 = 0,
    ADC_CONVERSION_CLOCK_FOSC_DIV_8,
    ADC_CONVERSION_CLOCK_FOSC_DIV_32,
    ADC_CONVERSION_CLOCK_FOSC_DIV_FRC,
    ADC_CONVERSION_CLOCK_FOSC_DIV_4,
    ADC_CONVERSION_CLOCK_FOSC_DIV_16,
    ADC_CONVERSION_CLOCK_FOSC_DIV_64,
}adc_conversion_clock_t;

typedef struct{
#if ADC_INTERRUPT_ENABLE_ == ADC_INTERRUPT_FEATURE_ENABLED
    void(* ADC_INERRUPT_HANDELER)(void);
    interrupt_priority_t priority;
#endif
    adc_channel_select_t   acd_channel_number;
    adc_acquisition_time_t acd_acqusition_time;
    adc_conversion_clock_t acd_conversion_clock;
    uint8 acd_volatage_ref  : 1;
    uint8 acd_result_format :1;
    uint8 adc_digital_analog_config:4;
    uint8 reserved:2;
}adc_conf_t;

/* section: functions Declarations */

/**
 * @breif : function to initialize ADC 
 * @param adc:  the struct which has all info about the pin
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType ADC_INIT(const adc_conf_t *adc);
/**
 * @breif : function to deinitialize ADC 
 * @param adc: the struct which has all info about the pin
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType ADC_DEINIT(const adc_conf_t *adc);
/**
 * @breif : function to convert to digital by blocking  
 * @param adc: the struct which has all info about the pin
 * @param status
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType ADC_CONVERSION_BLOCKING(const adc_conf_t *adc,adc_channel_select_t channel,uint16 *result);
/**
 * @breif : function to convert to digital by interrupting  
 * @param adc: the struct which has all info about the pin
 * @param status
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType ADC_CONVERSION_WITH_FLAG(const adc_conf_t *adc,adc_channel_select_t channel);
/**
 * @breif : function to check if ADC has done the conversion or not 
 * @param adc: the struct which has all info about the pin
 * @param status: pointer to variable to save the status of the conversion 
 * @return 
 */
Std_ReturnType ADC_IS_CONVERSION_DONE(const adc_conf_t *adc, uint8 *status);
/**
 * @breif : helper function to save result  
 * @param adc: the struct which has all info about the pin
 * @param result: pointer to variable to save the result from conversion
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType ADC_CONVERSION_RESULT(const adc_conf_t *adc, uint16 *result);


/**
 * @brief: function to call Interrupt handler function
 */
void ADC_ISR(void);


#endif	/* HAL_ADC_H */

