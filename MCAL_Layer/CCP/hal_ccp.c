/* 
 * File:   ccp1_cfg.c
 * Author: imina
 *
 * Created on February 2, 2024, 1:08 PM
 */


#include "hal_ccp.h"

/**
 * @brief: function to choose capture configuration
 * @param _ccp_obj: struct has all information about CCP
 */
static void ccp_capture_config(const ccp_t *_ccp_obj );
/**
 * @brief: function to choose compare configuration
 * @param _ccp_obj: struct has all information about CCP
 */
static void ccp_compare_config(const ccp_t *_ccp_obj );
/**
 * @brief: function to configure the PMW Mode
 * @param _ccp_obj: struct has all information about CCP
 */
static void ccp_pmw_config(const ccp_t *_ccp_obj );
/**
 * @brief: function to configure the interrupt 
 * @param _ccp_obj: struct has all information about CCP
 */
static void ccp_interupt_config(const ccp_t *_ccp_obj );
/**
 * @brief: function to choose which timer will be used in CCP
 * @param _ccp_obj: struct has all information about CCP
 */
static void CCP_CAPTURE_COMPARE_TIMER_CONF(const ccp_t *_ccp_obj);


#if CCP1_INTERRUPT_ENABLE_ == CCP1_INTERRUPT_FEATURE_ENABLED
    static void(*CCP1_HANDLER_POINTER_TO_FUNCTION)(void)=NULL;
#endif

#if CCP2_INTERRUPT_ENABLE_ == CCP2_INTERRUPT_FEATURE_ENABLED
    static void(*CCP2_HANDLER_POINTER_TO_FUNCTION)(void)=NULL;
#endif    
    
    
/**
 * @brief: function to initialize the CCP module 
 * @param _ccp_obj: struct has all information about CCP
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */  
Std_ReturnType CCP_Init(const ccp_t *_ccp_obj)
{
    Std_ReturnType ret= E_OK;
    if(NULL == _ccp_obj){
        ret= E_NOT_OK;
    }
    else
    {
        if(_ccp_obj->ccp_current == CCP1_Current_ ){
            CCP1_SET_MODE(CCP_MODULE_DISABLE);
        }
        else if(_ccp_obj->ccp_current == CCP2_Current_){
            CCP2_SET_MODE(CCP_MODULE_DISABLE);
        }
        if(_ccp_obj->ccp_mode == CCP_CAPTURE_MODE_SELECTED ){
            ccp_capture_config(_ccp_obj);
        }
        else if(_ccp_obj->ccp_mode == CCP_COMPARE_MODE_SELECTED){
            ccp_compare_config(_ccp_obj);
        }
#if (CCP1_CFG_MODE_SELECTED == CCP_CFG_PWM_MODE_SELECTED) || (CCP2_CFG_MODE_SELECTED == CCP_CFG_PWM_MODE_SELECTED)   
        else if(_ccp_obj->ccp_mode == CCP_PWM_MODE_SELECTED)     
        {
            ccp_pmw_config(_ccp_obj);
        }
#endif 
        gpio_pin_initialize(&(_ccp_obj->ccp_pin));
        ccp_interupt_config(_ccp_obj);
    }
    return ret;
}
/**
 * @brief: function to deinitialize the CCP module 
 * @param _ccp_obj: struct has all information about CCP
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */  
Std_ReturnType CCP_DeInit(const ccp_t *_ccp_obj){
    Std_ReturnType ret = E_OK;
    if(NULL == _ccp_obj){
        ret=E_NOT_OK;
    }
    else{    
        if(_ccp_obj->ccp_current == CCP1_Current_ )
        {
            CCP1_SET_MODE(CCP_MODULE_DISABLE);
#if CCP1_INTERRUPT_ENABLE_ == CCP1_INTERRUPT_FEATURE_ENABLED
        CCP1_INTERRUPT_DISABLE();
#endif    
        }else if(_ccp_obj->ccp_current == CCP2_Current_ ){
            CCP2_SET_MODE(CCP_MODULE_DISABLE);
#if CCP2_INTERRUPT_ENABLE_ == CCP2_INTERRUPT_FEATURE_ENABLED
        CCP2_INTERRUPT_DISABLE();
#endif  
        }        
    }
    return ret;        
}
#if (CCP1_CFG_MODE_SELECTED == CCP_CFG_CAPTUTR_MODE_SELECTED) || (CCP2_CFG_MODE_SELECTED == CCP_CFG_CAPTUTR_MODE_SELECTED)
/**
 * @brief: function to know if the data ready to be read or not
 * @param _ccp_obj: struct has all information about CCP
 * @param _capture_status: variable to save status of CCP
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */  
Std_ReturnType CCP_IsCapturedDataReady(const ccp_t *_ccp_obj,uint8 *_capture_status){
    Std_ReturnType ret = E_OK;
    if ((_ccp_obj == NULL) || NULL==_capture_status){
        ret = E_NOT_OK;
    }else{
        if (_ccp_obj->ccp_current == CCP1_Current_)
        { 
            if( PIR1bits.CCP1IF ==  CCP_CAPTURE_READY){
                *_capture_status =  CCP_CAPTURE_READY;
                CCP1_INTERRUPT_CLEAR_FLAG();
            }else{
                *_capture_status=CCP_CAPTURE_NOT_READY;
            }
        }else if (_ccp_obj->ccp_current == CCP2_Current_)
        {
            if( PIR2bits.CCP2IF ==  CCP_CAPTURE_READY){
                *_capture_status =  CCP_CAPTURE_READY;
                CCP2_INTERRUPT_CLEAR_FLAG();
            }else{
                *_capture_status = CCP_CAPTURE_NOT_READY;
            }
        }
    }return ret;
}
/**
 * @brief: function to read the capture value
 * @param _ccp_obj: struct has all information about CCP
 * @param capture_value: capture value saved in CCP_REGISTER
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */  
Std_ReturnType CCP_Capture_Mode_Read_Value(const ccp_t *_ccp_obj,uint16 *capture_value)
{
    Std_ReturnType ret = E_OK;
    CCP_REG_T reg_values={.ccp_16Bit = 0} ;
    if ( (_ccp_obj== NULL) || (NULL == capture_value)){
        ret = E_NOT_OK;
    }else
    {
        if (_ccp_obj->ccp_current == CCP1_Current_)
        { 
            reg_values.ccp_low = CCPR1L;
            reg_values.ccp_high = CCPR1H;    
        }else if (_ccp_obj->ccp_current == CCP2_Current_)
        {
            reg_values.ccp_low = CCPR2L;
            reg_values.ccp_high = CCPR2H;

        }        
        *capture_value = reg_values.ccp_16Bit ;
    }return ret;
}
#endif

#if (CCP1_CFG_MODE_SELECTED == CCP_CFG_COMPARE_MODE_SELECTED)||(CCP2_CFG_MODE_SELECTED == CCP_CFG_COMPARE_MODE_SELECTED)
/**
 * @brief: function to know if the CCP reached the value of not
 * @param _ccp_obj: struct has all information about CCP
 * @param _compare_status: variable to save status of CCP
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */  
Std_ReturnType CCP_IsCompareComplete(const ccp_t *_ccp_obj,uint8 *_compare_status){
    Std_ReturnType ret = E_OK;
    if (NULL==_compare_status){
        ret = E_NOT_OK;
    }else{
        if (_ccp_obj->ccp_current == CCP1_Current_)
        {
            if(PIR1bits.CCP1IF ==  CCP_COMPARE_READY)
            {
                *_compare_status =CCP_COMPARE_READY;
                CCP1_INTERRUPT_CLEAR_FLAG();
            }else
            {
                *_compare_status =CCP_COMPARE_NOT_READY;
            }
        }else if(_ccp_obj->ccp_current == CCP2_Current_)
        {
            if(PIR2bits.CCP2IF ==  CCP_COMPARE_READY)
            {
                *_compare_status =CCP_COMPARE_READY;
                CCP2_INTERRUPT_CLEAR_FLAG();
            }else
            {
                *_compare_status =CCP_COMPARE_NOT_READY;
            }            
        }
    }    
}
/**
 * @brief: function to give the CCP Value to be compared
 * @param _ccp_obj: struct has all information about CCP
 * @param compare_value: value that you want to reach
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */ 
Std_ReturnType CCP_Compare_Mode_Set_Value(const ccp_t *_ccp_obj, uint16 compare_value){
    Std_ReturnType ret = E_OK;
    CCP_REG_T reg_values={.ccp_16Bit = compare_value} ;
    if (NULL == _ccp_obj){
        ret = E_NOT_OK;
    }else
    {
        if (_ccp_obj->ccp_current == CCP1_Current_)
        {        
            CCPR1L = reg_values.ccp_low;
            CCPR1H = reg_values.ccp_high;
        }else if (_ccp_obj->ccp_current == CCP2_Current_)
        {
            CCPR2L = reg_values.ccp_low;
            CCPR2H = reg_values.ccp_high;            
        }
    }    
}
#endif

#if (CCP1_CFG_MODE_SELECTED == CCP_CFG_PWM_MODE_SELECTED)||(CCP2_CFG_MODE_SELECTED == CCP_CFG_PWM_MODE_SELECTED)
/**
 * @brief: function to set the duty time (PEAK of the wave)
 * @param _ccp_obj: struct has all information about CCP
 * @param _duty: percentage number
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */ 
Std_ReturnType CCP_PWM_Set_Duty(const ccp_t *_ccp_obj, const uint8 _duty){
    Std_ReturnType ret = E_OK;
    uint16 temp_duty=0;
    if(NULL == _ccp_obj ){
        ret = E_NOT_OK;
    }else{
        temp_duty = (uint16)(4 * (PR2 + 1) * (_duty / 100.0));
        
        if(_ccp_obj->ccp_current == CCP1_Current_ ){
            CCP1CONbits.DC1B = (uint8)(temp_duty & 0x0003);
            CCPR1L = (uint8)(temp_duty >> 2);   
        }
        else if(_ccp_obj->ccp_current == CCP2_Current_ ){
            CCP2CONbits.DC2B = (uint8)(temp_duty & 0x0003);
            CCPR2L = (uint8)(temp_duty >> 2);          
        }
    }
}
/**
 * @brief: function to start PMW mode
 * @param _ccp_obj: struct has all information about CCP
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */ 
Std_ReturnType CCP_PWM_Start(const ccp_t *_ccp_obj){
    Std_ReturnType ret = E_OK;
    if(NULL == _ccp_obj ){
        ret = E_NOT_OK;
    }
    else{    
        if(_ccp_obj->ccp_current == CCP1_Current_ ){
            CCP1CONbits.CCP1M =CCP_PWM_MODE;
        }
        else if(_ccp_obj->ccp_current == CCP2_Current_ ){
            CCP2CONbits.CCP2M =CCP_PWM_MODE;
        }
    }
}
/**
 * @brief: function to stop PMW mode
 * @param _ccp_obj: struct has all information about CCP
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */ 
Std_ReturnType CCP_PWM_Stop(const ccp_t *_ccp_obj){
    Std_ReturnType ret = E_OK;
    if(NULL == _ccp_obj ){
        ret = E_NOT_OK;
    }else
    {
        if(_ccp_obj->ccp_current == CCP1_Current_ ){
            CCP1CONbits.CCP1M =CCP_MODULE_DISABLE;
        }
        else if(_ccp_obj->ccp_current == CCP2_Current_ ){
            CCP2CONbits.CCP2M =CCP_MODULE_DISABLE;
        }
    }  
}
#endif

#if (CCP1_CFG_MODE_SELECTED == CCP_CFG_PWM_MODE_SELECTED) || (CCP2_CFG_MODE_SELECTED == CCP_CFG_PWM_MODE_SELECTED)
/**
 * @brief: function to configure the PMW Mode
 * @param _ccp_obj: struct has all information about CCP
 */
static void ccp_pmw_config(const ccp_t *_ccp_obj )
{
    if(_ccp_obj->ccp_current == CCP1_Current_ )
    {
        if (_ccp_obj->ccp_mode_variant == CCP_PWM_MODE )
        {
            CCP1_SET_MODE(CCP_PWM_MODE);
        }
        else{}
    }
    else if(_ccp_obj->ccp_current == CCP2_Current_ )
    {
        if (_ccp_obj->ccp_mode_variant == CCP_PWM_MODE )
        {
            CCP2_SET_MODE(CCP_PWM_MODE);
        }
        else{}
    }
    PR2 = (uint8)((_XTAL_FREQ / (_ccp_obj->PWM_Frequency * 4.0 * _ccp_obj->timer2_prescaler_value * 
                    _ccp_obj->timer2_postscaler_value)) - 1);
}
#endif
/**
 * @brief: function to configure the interrupt 
 * @param _ccp_obj: struct has all information about CCP
 */
static void ccp_interupt_config(const ccp_t *_ccp_obj ){
    
#if CCP1_INTERRUPT_ENABLE_ == CCP1_INTERRUPT_FEATURE_ENABLED
    CCP1_INTERRUPT_ENABLE();
    CCP1_INTERRUPT_CLEAR_FLAG();
    CCP1_HANDLER_POINTER_TO_FUNCTION = _ccp_obj->CCP1_HANDLER ;  
#if INTERRUPT_PRIORITY_FEATURE_ENABLED == INTERRUPT_PRIORITY_ENABLED
    INTERRUPT_PRIORITY_ENABLE();
    INTCONbits.GIE = 1;
    if(_ccp_obj->ccp1_priority == INTERRUPT_HIGH )
    {
        CCP1_INTERRUPT_SET_HIGH_PRIORITY();
        INTERRUPT_GLOBAL_INTERRUPT_HIGH_ENABLE();
    }
    else if(_ccp_obj->ccp1_priority == INTERRUPT_LOW )
    {
        CCP1_INTERRUPT_SET_LOW_PRIORITY();
        INTERRUPT_GLOBAL_INTERRUPT_LOW_ENABLE();
    }
#else
    INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
    INTERRUPT_PREPHERAL_INTERRUPT_ENABLE();        
#endif        
#endif     
        
#if CCP2_INTERRUPT_ENABLE_ == CCP2_INTERRUPT_FEATURE_ENABLED
    CCP2_INTERRUPT_ENABLE();
    CCP2_INTERRUPT_CLEAR_FLAG();
    CCP2_HANDLER_POINTER_TO_FUNCTION = _ccp_obj->CCP2_HANDLER ;  
#if INTERRUPT_PRIORITY_FEATURE_ENABLED == INTERRUPT_PRIORITY_ENABLED
    INTERRUPT_PRIORITY_ENABLE();
    INTCONbits.GIE = 1;    
    if(_ccp_obj->ccp2_priority == INTERRUPT_HIGH )
    {
        CCP2_INTERRUPT_SET_HIGH_PRIORITY();
        INTERRUPT_GLOBAL_INTERRUPT_HIGH_ENABLE();
    }
    else if(_ccp_obj->ccp2_priority == INTERRUPT_LOW )
    {
        CCP2_INTERRUPT_SET_LOW_PRIORITY();
        INTERRUPT_GLOBAL_INTERRUPT_LOW_ENABLE();
    }
#else
    INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
    INTERRUPT_PREPHERAL_INTERRUPT_ENABLE();        
#endif        
#endif             
}
/**
 * @brief: function to choose which timer will be used in CCP
 * @param _ccp_obj: struct has all information about CCP
 */
static void CCP_CAPTURE_COMPARE_TIMER_CONF(const ccp_t *_ccp_obj)
{
    if(_ccp_obj->ccp_capture_timer == CCP1_CCP2_TIMER3)
    { T3CONbits.T3CCP1 = 0;
      T3CONbits.T3CCP2 = 1;
    }else if(_ccp_obj->ccp_capture_timer == CCP1_TIMER1_CCP2_TIMER3)
    { T3CONbits.T3CCP1 = 1;
      T3CONbits.T3CCP2 = 0;
    }else if(_ccp_obj->ccp_capture_timer ==CCP1_CCP2_TIMER1 )   
    { T3CONbits.T3CCP1 = 0;
      T3CONbits.T3CCP2 = 0;
    }   
}
/**
 * @brief: function to choose capture configuration
 * @param _ccp_obj: struct has all information about CCP
 */
static void ccp_capture_config(const ccp_t *_ccp_obj )
{
    if(_ccp_obj->ccp_current == CCP1_Current_){
        switch(_ccp_obj->ccp_mode_variant)
        {
            case CCP_CAPTURE_MODE_1_FALLING_EDGE:CCP1_SET_MODE(CCP_CAPTURE_MODE_1_FALLING_EDGE);break;
            case CCP_CAPTURE_MODE_1_RISING_EDGE: CCP1_SET_MODE(CCP_CAPTURE_MODE_1_RISING_EDGE);break;
            case CCP_CAPTURE_MODE_4_RISING_EDGE: CCP1_SET_MODE(CCP_CAPTURE_MODE_4_RISING_EDGE);break;
            case CCP_CAPTURE_MODE_16_RISING_EDGE:CCP1_SET_MODE(CCP_CAPTURE_MODE_16_RISING_EDGE);break;                
        }        
    }else if(_ccp_obj->ccp_current == CCP2_Current_){
        switch(_ccp_obj->ccp_mode_variant)
        {
            case CCP_CAPTURE_MODE_1_FALLING_EDGE:CCP2_SET_MODE(CCP_CAPTURE_MODE_1_FALLING_EDGE);break;
            case CCP_CAPTURE_MODE_1_RISING_EDGE: CCP2_SET_MODE(CCP_CAPTURE_MODE_1_RISING_EDGE);break;
            case CCP_CAPTURE_MODE_4_RISING_EDGE: CCP2_SET_MODE(CCP_CAPTURE_MODE_4_RISING_EDGE);break;
            case CCP_CAPTURE_MODE_16_RISING_EDGE:CCP2_SET_MODE(CCP_CAPTURE_MODE_16_RISING_EDGE);break;                
        }        
    }
    CCP_CAPTURE_COMPARE_TIMER_CONF(_ccp_obj);
}
/**
 * @brief: function to choose compare configuration
 * @param _ccp_obj: struct has all information about CCP
 */
static void ccp_compare_config(const ccp_t *_ccp_obj ){
    if(_ccp_obj->ccp_current == CCP1_Current_){
        switch(_ccp_obj->ccp_mode_variant)
        {
            case CCP_COMPARE_MODE_SET_PIN_LOW:     CCP1_SET_MODE(CCP_COMPARE_MODE_SET_PIN_LOW);break;
            case CCP_COMPARE_MODE_SET_PIN_HIGH:    CCP1_SET_MODE(CCP_COMPARE_MODE_SET_PIN_HIGH);break;
            case CCP_COMPARE_MODE_TOGGLE_ON_MATCH: CCP1_SET_MODE(CCP_COMPARE_MODE_TOGGLE_ON_MATCH);break;
            case CCP_COMPARE_MODE_GEN_SW_INTERRUPT:CCP1_SET_MODE(CCP_COMPARE_MODE_GEN_SW_INTERRUPT);break;                
            case CCP_COMPARE_MODE_GEN_EVENT:       CCP1_SET_MODE(CCP_COMPARE_MODE_GEN_EVENT);break;               
        }        
    }else if(_ccp_obj->ccp_current == CCP2_Current_){
        switch(_ccp_obj->ccp_mode_variant)
        {
            case CCP_COMPARE_MODE_SET_PIN_LOW:     CCP2_SET_MODE(CCP_COMPARE_MODE_SET_PIN_LOW);break;
            case CCP_COMPARE_MODE_SET_PIN_HIGH:    CCP2_SET_MODE(CCP_COMPARE_MODE_SET_PIN_HIGH);break;
            case CCP_COMPARE_MODE_TOGGLE_ON_MATCH: CCP2_SET_MODE(CCP_COMPARE_MODE_TOGGLE_ON_MATCH);break;
            case CCP_COMPARE_MODE_GEN_SW_INTERRUPT:CCP2_SET_MODE(CCP_COMPARE_MODE_GEN_SW_INTERRUPT);break;                
            case CCP_COMPARE_MODE_GEN_EVENT:       CCP2_SET_MODE(CCP_COMPARE_MODE_GEN_EVENT);break;               
        }         
    } 
    CCP_CAPTURE_COMPARE_TIMER_CONF(_ccp_obj);
}
/**
 * function to execute the ISR of CCP1
 */
void CCP1_ISR(void){
    CCP1_INTERRUPT_CLEAR_FLAG();
    if(CCP1_HANDLER_POINTER_TO_FUNCTION)
    {
    CCP1_HANDLER_POINTER_TO_FUNCTION();
    }        
}
/**
 * function to execute the ISR of CCP2
 */
void CCP2_ISR(void){
    CCP2_INTERRUPT_CLEAR_FLAG();
    if(CCP2_HANDLER_POINTER_TO_FUNCTION)
    {
    CCP2_HANDLER_POINTER_TO_FUNCTION();
    }        
}