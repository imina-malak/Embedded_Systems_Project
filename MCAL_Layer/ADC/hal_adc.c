/* 
 * File:   hal_adc.c
 * Author: imina
 *
 * Created on January 20, 2024, 5:40 PM
 */

#include "hal_adc.h"

/**
 * @brief: helper function to set pin as input the (Disable pin output driver (See TRIS register))
 * @param channel: nubmer of channel
 */
static inline void SET_PINS(adc_channel_select_t channel);
/**
 * @brief: helper function to choose result format
 * @param adc: the struct which has all info about the pin
 */
static inline void SET_RESULT_FORMAT(const adc_conf_t *adc);
/**
 * @brief: helper function to choose which voltage reference we should choose  
 * @param adc: the struct which has all info about the pin
 */
static inline void SET_VOLTAGE_REF(const adc_conf_t *adc);


#if ADC_INTERRUPT_ENABLE_ == ADC_INTERRUPT_FEATURE_ENABLED
    static void(*ADC_HANDLER_POINTER_TO_FUNCTION)(void)=NULL;
#endif


/**
 * @breif : function to initialize ADC 
 * @param adc:  the struct which has all info about the pin
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType ADC_INIT(const adc_conf_t *adc){
    Std_ReturnType ret = E_OK;
    if(NULL == adc){
        ret=E_NOT_OK;
    }
    else{
        ADC_CONVERTER_DISABLE();
        SET_PINS(adc->acd_channel_number);
        ADC_DIGITAL_ANALOG_CONFIG(adc->adc_digital_analog_config);
        
        ADCON2bits.ADCS = adc->acd_conversion_clock;
        SET_VOLTAGE_REF(adc);
        ADCON0bits.CHS = adc->acd_channel_number;
        SET_RESULT_FORMAT(adc);        
        ADCON2bits.ACQT = adc->acd_acqusition_time;
#if ADC_INTERRUPT_ENABLE_ == ADC_INTERRUPT_FEATURE_ENABLED
        INTERRUPT_PRIORITY_ENABLE();
        PIR1bits.ADIF = 0;
        ADC_INTERRUPT_ENABLE();
        INTCONbits.GIE = 1;
#if INTERRUPT_PRIORITY_FEATURE_ENABLED == INTERRUPT_PRIORITY_ENABLED
        if(adc->priority == INTERRUPT_HIGH ){
            ADC_INTERRUPT_SET_HIGH_PRIORITY();
            INTERRUPT_GLOBAL_INTERRUPT_HIGH_ENABLE();}
        else if(adc->priority == INTERRUPT_LOW ){
            ADC_INTERRUPT_SET_LOW_PRIORITY();            
            INTERRUPT_GLOBAL_INTERRUPT_LOW_ENABLE();
        }
#else
        INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
        INTERRUPT_PREPHERAL_INTERRUPT_ENABLE();        
#endif
        ADC_HANDLER_POINTER_TO_FUNCTION = adc->ADC_INERRUPT_HANDELER;  
#endif
        ADC_CONVERTER_ENABLE();
    }
    return ret;
} 
/**
 * @breif : function to deinitialize ADC 
 * @param adc: the struct which has all info about the pin
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType ADC_DEINIT(const adc_conf_t *adc){
    Std_ReturnType ret = E_OK;
    if(NULL == adc){
        ret=E_NOT_OK;
    }
    else{
        ADC_CONVERTER_DISABLE();
#if ADC_INTERRUPT_ENABLE_ ==ADC_INTERRUPT_FEATURE_ENABLED
        ADC_INTERRUPT_DISABLE();
#endif
    }
    return ret;
    
}

/**
 * @breif : function to check if ADC has done the conversion or not 
 * @param adc: the struct which has all info about the pin
 * @param status: pointer to variable to save the status of the conversion 
 * @return 
 */
Std_ReturnType ADC_IS_CONVERSION_DONE(const adc_conf_t *adc, uint8 *status){
    Std_ReturnType ret = E_OK;    
    if((NULL == adc) || (NULL== status) ){
        ret=E_NOT_OK;
    }
    else{
        *status = (uint8)(!(ADCON0bits.GO_nDONE));
    }
    return ret;    
}
/**
 * @breif : helper function to save result  
 * @param adc: the struct which has all info about the pin
 * @param result: pointer to variable to save the result from conversion
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType ADC_CONVERSION_RESULT(const adc_conf_t *adc, uint16 *result){
    Std_ReturnType ret = E_OK;
    if((NULL == adc) || (NULL == result) ){
        ret=E_NOT_OK;
    }
    else{
        if(ADC_RESULT_RIGHT == adc->acd_result_format )
        {
            *result = (uint16)((ADRESH<<8) + ADRESL); 
        }
        else if(ADC_RESULT_LEFT == adc->acd_result_format)
        {
            *result = (uint16)   (((ADRESH<<8)+ADRESL)>>6);   // left     
        }else{
            *result = (uint16)( (ADRESH<<8) + ADRESL); 
        }
    }
    return ret;    
}
/**
 * @breif : function to convert to digital by blocking  
 * @param adc: the struct which has all info about the pin
 * @param status
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType ADC_CONVERSION_BLOCKING(const adc_conf_t *adc,adc_channel_select_t channel ,uint16 *result){
    Std_ReturnType ret = E_OK;    
    if(NULL == adc || (NULL == result )){
        ret=E_NOT_OK;
    }
    else{
        ADCON0bits.CHS = channel;
        SET_PINS(channel);
        ADC_START_CONVERSION();
        while(ADCON0bits.GO_nDONE);
        ADC_CONVERSION_RESULT(adc,result);
    }
    return ret;    
}
/**
 * @breif : function to convert to digital by interrupting  
 * @param adc: the struct which has all info about the pin
 * @param status
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType ADC_CONVERSION_WITH_FLAG(const adc_conf_t *adc,adc_channel_select_t channel){
    Std_ReturnType ret = E_OK;    
    if(NULL == adc ){
        ret=E_NOT_OK;
    }
    else{
        PIR1bits.ADIF = 0;
        ADCON0bits.CHS = channel;
        SET_PINS(channel);
        ADC_START_CONVERSION();
    }
    return ret;    
}
/**
 * @brief: helper function to set pin as input the (Disable pin output driver (See TRIS register))
 * @param channel: nubmer of channel
 */
static inline void SET_PINS(adc_channel_select_t channel){
        switch(channel){
            case ADC_CHANNEL_AN0:SET_BIT(TRISA,_TRISA_RA0_POSN);break;
            case ADC_CHANNEL_AN1:SET_BIT(TRISA,_TRISA_RA1_POSN);break;
            case ADC_CHANNEL_AN2:SET_BIT(TRISA,_TRISA_RA2_POSN);break;
            case ADC_CHANNEL_AN3:SET_BIT(TRISA,_TRISA_RA3_POSN);break;
            case ADC_CHANNEL_AN4:SET_BIT(TRISA,_TRISA_RA5_POSN);break;
            
            case ADC_CHANNEL_AN5:SET_BIT(TRISE,_TRISE_RE0_POSN);break;
            case ADC_CHANNEL_AN6:SET_BIT(TRISE,_TRISE_RE1_POSN);break;
            case ADC_CHANNEL_AN7:SET_BIT(TRISE,_TRISE_RE2_POSN);break;
            
            case ADC_CHANNEL_AN8:SET_BIT(TRISB,_TRISB_RB2_POSN);break;
            case ADC_CHANNEL_AN9:SET_BIT(TRISB,_TRISB_RB3_POSN);break;
            case ADC_CHANNEL_AN10:SET_BIT(TRISB,_TRISB_RB1_POSN);break;
            case ADC_CHANNEL_AN11:SET_BIT(TRISB,_TRISB_RB4_POSN);break;
            case ADC_CHANNEL_AN12:SET_BIT(TRISB,_TRISB_RB0_POSN);break;
        }
}
/**
 * @brief: helper function to choose result format
 * @param adc: the struct which has all info about the pin
 */
static inline void SET_RESULT_FORMAT(const adc_conf_t *adc){
    Std_ReturnType ret = E_OK;
    if(NULL == adc){
        ret=E_NOT_OK;
    }
    else{
        if(adc->acd_result_format == ADC_RESULT_RIGHT ){
            ADC_RESULT_RIGHT_FORMAT();
        }else if(adc->acd_result_format == ADC_RESULT_LEFT){
            ADC_RESULT_LEFT_FORMAT();
        }else{
            ADC_RESULT_RIGHT_FORMAT();            
        }
    }
}
/**
 * @brief: helper helper function to choose which voltage reference we should choose  
 * @param adc: the struct which has all info about the pin
 */
static inline void SET_VOLTAGE_REF(const adc_conf_t *adc){
    Std_ReturnType ret = E_OK;
    if(NULL == adc){
        ret=E_NOT_OK;
    }
    else{
        if(adc->acd_volatage_ref == ADC_ENABLE_VOLTAGE_REF ){
            ADC_ENABLE_VOLTAGE_REF_FORMAT();
        }else if(adc->acd_volatage_ref == ADC_DISENABLE_VOLTAGE_REF){
            ADC_DISABLE_VOLTAGE_REF_FORMAT();
        }else{
            ADC_DISABLE_VOLTAGE_REF_FORMAT();            
        }
    }
}


/**
 * @brief: function to call Interrupt handler function
 */
void ADC_ISR(void){
    ADC_INTERRUPT_CLEAR_FLAG();
    if(ADC_HANDLER_POINTER_TO_FUNCTION)
    {
    ADC_HANDLER_POINTER_TO_FUNCTION();
    }
}