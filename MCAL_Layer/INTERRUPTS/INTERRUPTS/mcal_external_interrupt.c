/* 
 * File:   mcal_external_interrupt.c
 * Author: imena
 *
 * Created on January 3, 2024, 8:45 PM
 */

#include "mcal_external_interrupt.h"


static void(*EXT_INTERRUPT0_HANDLER_POINTER_TO_FUNCTION)(void)=NULL;
static void(*EXT_INTERRUPT1_HANDLER_POINTER_TO_FUNCTION)(void)=NULL;
static void(*EXT_INTERRUPT2_HANDLER_POINTER_TO_FUNCTION)(void)=NULL;

static void(*EXT_RBINTERRUPT4_HANDLER_POINTER_TO_FUNCTION_HIGH)(void)=NULL;
static void(*EXT_RBINTERRUPT4_HANDLER_POINTER_TO_FUNCTION_LOW)(void)=NULL;
static void(*EXT_RBINTERRUPT5_HANDLER_POINTER_TO_FUNCTION_HIGH)(void)=NULL;
static void(*EXT_RBINTERRUPT5_HANDLER_POINTER_TO_FUNCTION_LOW)(void)=NULL;
static void(*EXT_RBINTERRUPT6_HANDLER_POINTER_TO_FUNCTION_HIGH)(void)=NULL;
static void(*EXT_RBINTERRUPT6_HANDLER_POINTER_TO_FUNCTION_LOW)(void)=NULL;
static void(*EXT_RBINTERRUPT7_HANDLER_POINTER_TO_FUNCTION_HIGH)(void)=NULL;
static void(*EXT_RBINTERRUPT7_HANDLER_POINTER_TO_FUNCTION_LOW)(void)=NULL;


static Std_ReturnType INTx_INTERRUPT_DISABLE(const intx_interrupt_t  *intx_object);
static Std_ReturnType INTx_INTERRUPT_CLEAR_FLAG(const intx_interrupt_t  *intx_object);
static Std_ReturnType INTx_INTERRUPT_EDGE_INIT(const intx_interrupt_t  *intx_object);
static Std_ReturnType INTx_INTERRUPT_PIN_INIT(const intx_interrupt_t  *intx_object);
static Std_ReturnType INTx_INTERRUPT_SET_HANDLER_FUNCTION(const intx_interrupt_t *intx_object);
static Std_ReturnType INTx_INTERRUPT_ENABLE(const intx_interrupt_t  *intx_object);

 
void INT0_ISR(void);
void INT2_ISR(void);
void INT2_ISR(void);
void RB10_ISR(uint8 value);
void RB11_ISR(uint8 value);
void RB12_ISR(uint8 value);
void RB13_ISR(uint8 value);


/**
 * @brief :function to enable initialize interrupt intx 
 * @param intx_object: :the struct which has all info about the pin
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType INTx_INTERRUPT_INITIALIZATION (const intx_interrupt_t  *intx_object){
    Std_ReturnType ret = E_OK;
    if (NULL ==intx_object){
        ret = E_NOT_OK;
    }else
    {
        ret = INTx_INTERRUPT_DISABLE(intx_object);
        ret = INTx_INTERRUPT_CLEAR_FLAG(intx_object);
        ret = INTx_INTERRUPT_EDGE_INIT(intx_object);
        ret = INTx_INTERRUPT_PIN_INIT(intx_object);
        ret = INTx_INTERRUPT_SET_HANDLER_FUNCTION(intx_object);
        ret = INTx_INTERRUPT_ENABLE(intx_object);   
    }
    return ret;  
}

/**
 * @brief :function to enable deinitialize interrupt intx 
 * @param intx_object: :the struct which has all info about the pin
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType INTx_INTERRUPT_DEINITIALIZATION(const intx_interrupt_t  *intx_object){
    Std_ReturnType ret = E_OK;
    if (NULL ==intx_object){
        ret = E_NOT_OK;
    }else
    {
        INTx_INTERRUPT_DISABLE(intx_object);
    }
    return ret; 
}

/**
 * @brief : helper function to enable specific intx and determine its priority 
 * @param intx_object: :the struct which has all info about the pin
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
static Std_ReturnType INTx_INTERRUPT_ENABLE(const intx_interrupt_t  *intx_object)
{
    Std_ReturnType ret = E_OK;
    if (NULL ==intx_object)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(intx_object->external_int_source)
        {
            case INTERRUPT_INT0:
            #if INTERRUPT_PRIORITY_FEATURE_ENABLED == INTERRUPT_PRIORITY_ENABLED
                INTERRUPT_PRIORITY_ENABLE();
                INTERRUPT_GLOBAL_INTERRUPT_HIGH_ENABLE();
            #else
                INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
                INTERRUPT_PREPHERAL_INTERRUPT_ENABLE();
            #endif
                EXT_INT0_INTERRUPT_ENABLED();break;
            case INTERRUPT_INT1:
                #if INTERRUPT_PRIORITY_FEATURE_ENABLED == INTERRUPT_PRIORITY_ENABLED
                INTERRUPT_PRIORITY_ENABLE();
                if(intx_object->external_int_priority == INTERRUPT_HIGH)
                {
                    INTERRUPT_GLOBAL_INTERRUPT_HIGH_ENABLE();
                    EXT_INT1_INTERRUPT_HIGH_PRIORITY();
                }
                else if (intx_object->external_int_priority == INTERRUPT_LOW)
                {
                    INTERRUPT_GLOBAL_INTERRUPT_LOW_ENABLE();
                    EXT_INT1_INTERRUPT_LOW_PRIORITY();
                }
                else{}
                #else
                INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
                INTERRUPT_PREPHERAL_INTERRUPT_ENABLE();
                #endif
                EXT_INT1_INTERRUPT_ENABLED();break;
            case INTERRUPT_INT2:
                #if INTERRUPT_PRIORITY_FEATURE_ENABLED == INTERRUPT_PRIORITY_ENABLED
                INTERRUPT_PRIORITY_ENABLE();
                if(intx_object->external_int_priority == INTERRUPT_HIGH)
                {
                    INTERRUPT_GLOBAL_INTERRUPT_HIGH_ENABLE();
                    EXT_INT2_INTERRUPT_HIGH_PRIORITY();
                }
                else if (intx_object->external_int_priority == INTERRUPT_LOW){
                    INTERRUPT_GLOBAL_INTERRUPT_LOW_ENABLE();
                    EXT_INT2_INTERRUPT_LOW_PRIORITY();
                }
                else{}
                #else
                INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
                INTERRUPT_PREPHERAL_INTERRUPT_ENABLE();
                #endif
                EXT_INT2_INTERRUPT_ENABLED();break;
            default:ret = E_NOT_OK;
        }
    }
    return ret;
}

/**
 * @brief : helper function to disable specific intx 
 * @param intx_object: :the struct which has all info about the pin
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
static Std_ReturnType INTx_INTERRUPT_DISABLE(const intx_interrupt_t  *intx_object)
{
    Std_ReturnType ret = E_OK;
    if (NULL ==intx_object)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch (intx_object->external_int_source)
        {
            case INTERRUPT_INT0:EXT_INT0_INTERRUPT_DISABLED();break;
            case INTERRUPT_INT1:EXT_INT1_INTERRUPT_DISABLED();break;
            case INTERRUPT_INT2:EXT_INT2_INTERRUPT_DISABLED();break;
            default :ret = E_NOT_OK;
        }
    }
    return ret;
}

/**
 * @brief : helper function to determine edge for specific intx 
 * @param intx_object: :the struct which has all info about the pin
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
static Std_ReturnType INTx_INTERRUPT_EDGE_INIT(const intx_interrupt_t  *intx_object)
{
    Std_ReturnType ret = E_OK;
    if (NULL ==intx_object)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch (intx_object->external_int_source)
        {
            case INTERRUPT_INT0: 
                if(intx_object->external_int_edge == INTERRUPT_RISING_EDGE){EXT_INT0_INTERRUPT_RISING_EDGE();}
                else if (intx_object->external_int_edge == INTERRUPT_FALLING_EDGE){EXT_INT0_INTERRUPT_FAILING_EDGE();}
                else{}
                break;            
            case INTERRUPT_INT1: 
                if(intx_object->external_int_edge == INTERRUPT_RISING_EDGE){EXT_INT1_INTERRUPT_RISING_EDGE();}
                else if (intx_object->external_int_edge == INTERRUPT_FALLING_EDGE){EXT_INT1_INTERRUPT_FAILING_EDGE();}
                else{}
                break;  
            case INTERRUPT_INT2: 
                if(intx_object->external_int_edge == INTERRUPT_RISING_EDGE){EXT_INT2_INTERRUPT_RISING_EDGE();}
                else if (intx_object->external_int_edge == INTERRUPT_FALLING_EDGE){EXT_INT2_INTERRUPT_FAILING_EDGE();}
                else{}
                break;  
            default :ret = E_NOT_OK;
        }          
    }
    return ret;  
}


/**
 * @brief : helper function to initialize specific intx 
 * @param intx_object: :the struct which has all info about the pin
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
static Std_ReturnType INTx_INTERRUPT_PIN_INIT(const intx_interrupt_t  *intx_object){
    Std_ReturnType ret = E_OK;
    if (NULL ==intx_object){
        ret = E_NOT_OK;
    }else
    {
        gpio_pin_direction_initialize(&(intx_object->external_int_config));
    }return ret;   
}
/**
 * @brief : helper function to clear flag specific intx 
 * @param intx_object: :the struct which has all info about the pin
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
static Std_ReturnType INTx_INTERRUPT_CLEAR_FLAG(const intx_interrupt_t  *intx_object){
    Std_ReturnType ret = E_OK;
    if (NULL ==intx_object){
        ret = E_NOT_OK;
    }else
    {
        switch (intx_object->external_int_source)
        {
            case INTERRUPT_INT0: EXT_INT0_INTERRUPT_FLAG_CLEAR();break;            
            case INTERRUPT_INT1: EXT_INT1_INTERRUPT_FLAG_CLEAR();break;            
            case INTERRUPT_INT2: EXT_INT2_INTERRUPT_FLAG_CLEAR();break;
            default :ret = E_NOT_OK;
        }
    }    return ret;
}

/**
 * @brief : helper function set the handler function specific intx 
 * @param intx_object: :the struct which has all info about the pin
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
static Std_ReturnType INTx_INTERRUPT_SET_HANDLER_FUNCTION(const intx_interrupt_t  *intx_object){
    Std_ReturnType ret = E_OK;
    if (NULL ==intx_object){
        ret = E_NOT_OK;
    }else
    {
        switch (intx_object->external_int_source)
        {
            case INTERRUPT_INT0:EXT_INTERRUPT0_HANDLER_POINTER_TO_FUNCTION =(intx_object->EXT_INTX_INTERRUPT_HANDLER);break;            
            case INTERRUPT_INT1:EXT_INTERRUPT1_HANDLER_POINTER_TO_FUNCTION =(intx_object->EXT_INTX_INTERRUPT_HANDLER);break;
            case INTERRUPT_INT2:EXT_INTERRUPT2_HANDLER_POINTER_TO_FUNCTION =(intx_object->EXT_INTX_INTERRUPT_HANDLER);break;
            default :ret = E_NOT_OK;
        }            
    }      return ret;
}

/**
 * @brief: ISR function to callback function to be executed when the interrupt happens on int0
 */
void INT0_ISR(void){
    EXT_INT0_INTERRUPT_FLAG_CLEAR();
    if(EXT_INTERRUPT0_HANDLER_POINTER_TO_FUNCTION)
    {
        EXT_INTERRUPT0_HANDLER_POINTER_TO_FUNCTION();
    }
}

/**
 * @brief: ISR function to callback function to be executed when the interrupt happens on int1
 */
void INT1_ISR(void){
    EXT_INT1_INTERRUPT_FLAG_CLEAR();
    if(EXT_INTERRUPT1_HANDLER_POINTER_TO_FUNCTION)
    {
        EXT_INTERRUPT1_HANDLER_POINTER_TO_FUNCTION();
    }
}

/**
 * @brief: ISR function to callback function to be executed when the interrupt happens on int2
 */
void INT2_ISR(void){
    EXT_INT2_INTERRUPT_FLAG_CLEAR();
    if(EXT_INTERRUPT2_HANDLER_POINTER_TO_FUNCTION)
    {
        EXT_INTERRUPT2_HANDLER_POINTER_TO_FUNCTION();
    }
}




/**
 * @brief :function to initialize interrupt rbx 
 * @param intx_object: :the struct which has all info about the pin
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType RBx_INTERRUPT_INITIALIZATION  (const rbx_interrupt_t   *rbx_object)
{
    Std_ReturnType ret = E_OK;
    if (NULL ==rbx_object){
        ret = E_NOT_OK;
    }else
    {
        EXT_RBx_INTERRUPT_DISABLED();
        EXT_RBx_INTERRUPT_FLAG_CLEAR();
        EXT_RBx_INTERRUPT_PULL_UP_DISABLED();
    #if INTERRUPT_PRIORITY_FEATURE_ENABLED == INTERRUPT_PRIORITY_ENABLED
        INTERRUPT_PRIORITY_ENABLE();
        INTERRUPT_GLOBAL_INTERRUPT_HIGH_ENABLE();//as shown in diagram it should be high             
        if (rbx_object->external_rb_priority == INTERRUPT_HIGH){      
            EXT_RBx_INTERRUPT_HIGH_PRIORITY();
        }else if(rbx_object->external_rb_priority == INTERRUPT_LOW){
            INTERRUPT_GLOBAL_INTERRUPT_LOW_ENABLE();
            EXT_RBx_INTERRUPT_LOW_PRIORITY();
        } 
        else{}
    #else
        INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
        INTERRUPT_PREPHERAL_INTERRUPT_ENABLE();
    #endif
        gpio_pin_direction_initialize(&(rbx_object->external_rb_config));
        switch(rbx_object->external_rb_source){
                case INTERRUPT_RB4 :
                    EXT_RBINTERRUPT4_HANDLER_POINTER_TO_FUNCTION_HIGH=rbx_object->EXT_RBX_INTERRUPT_HANDLER_RISING_EDGE;
                    EXT_RBINTERRUPT4_HANDLER_POINTER_TO_FUNCTION_LOW=rbx_object->EXT_RBX_INTERRUPT_HANDLER_FAILING_EDGE;
                    break;
                case INTERRUPT_RB5 :
                    EXT_RBINTERRUPT5_HANDLER_POINTER_TO_FUNCTION_HIGH=rbx_object->EXT_RBX_INTERRUPT_HANDLER_RISING_EDGE;
                    EXT_RBINTERRUPT5_HANDLER_POINTER_TO_FUNCTION_LOW=rbx_object->EXT_RBX_INTERRUPT_HANDLER_FAILING_EDGE;
                    break;
                case INTERRUPT_RB6 :
                    EXT_RBINTERRUPT6_HANDLER_POINTER_TO_FUNCTION_HIGH=rbx_object->EXT_RBX_INTERRUPT_HANDLER_RISING_EDGE;
                    EXT_RBINTERRUPT6_HANDLER_POINTER_TO_FUNCTION_LOW=rbx_object->EXT_RBX_INTERRUPT_HANDLER_FAILING_EDGE;
                    break;
                case INTERRUPT_RB7 :
                    EXT_RBINTERRUPT7_HANDLER_POINTER_TO_FUNCTION_HIGH=rbx_object->EXT_RBX_INTERRUPT_HANDLER_RISING_EDGE;
                    EXT_RBINTERRUPT7_HANDLER_POINTER_TO_FUNCTION_LOW=rbx_object->EXT_RBX_INTERRUPT_HANDLER_FAILING_EDGE;
                    break;
        }
        EXT_RBx_INTERRUPT_ENABLED();
    }return ret;
}
/**
 * @brief :function to deinitialize interrupt rbx 
 * @param intx_object: :the struct which has all info about the pin
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType RBx_INTERRUPT_DEINITIALIZATION   (const rbx_interrupt_t   *rbx_object){
    Std_ReturnType ret = E_OK;
    if (NULL ==rbx_object){
        ret = E_NOT_OK;
    }else
    {
            EXT_RBx_INTERRUPT_DISABLED();
    }
    return ret;
}
/**
 * @brief: ISR function to callback function to be executed when the interrupt happens on rb10
 * @param value: to choose which function should be executed
 */
void RB4_ISR(uint8 value)
{
    EXT_RBx_INTERRUPT_FLAG_CLEAR();
    if (value==HIGH)
    {
        if(EXT_RBINTERRUPT4_HANDLER_POINTER_TO_FUNCTION_HIGH)
        {
            EXT_RBINTERRUPT4_HANDLER_POINTER_TO_FUNCTION_HIGH();
        }         
    }
    else if (value==LOW)
    {
        if(EXT_RBINTERRUPT4_HANDLER_POINTER_TO_FUNCTION_LOW)
        {
            EXT_RBINTERRUPT4_HANDLER_POINTER_TO_FUNCTION_LOW();
        } 
    } 
}
/**
 * @brief: ISR function to callback function to be executed when the interrupt happens on rb11
 * @param value: to choose which function should be executed
 */
void RB5_ISR(uint8 value)
{
    EXT_RBx_INTERRUPT_FLAG_CLEAR();
    if (value==HIGH)
    {
        if(EXT_RBINTERRUPT5_HANDLER_POINTER_TO_FUNCTION_HIGH)
        {
            EXT_RBINTERRUPT5_HANDLER_POINTER_TO_FUNCTION_HIGH();
        }         
    }
    else if (value==LOW)
    {
        if(EXT_RBINTERRUPT5_HANDLER_POINTER_TO_FUNCTION_LOW)
        {
            EXT_RBINTERRUPT5_HANDLER_POINTER_TO_FUNCTION_LOW();
        } 
    }
}
/**
 * @brief: ISR function to callback function to be executed when the interrupt happens on rb12
 * @param value: to choose which function should be executed
 */
void RB6_ISR(uint8 value)
{
    EXT_RBx_INTERRUPT_FLAG_CLEAR();
    if (value==HIGH)
    {
        if(EXT_RBINTERRUPT6_HANDLER_POINTER_TO_FUNCTION_HIGH)
        {
            EXT_RBINTERRUPT6_HANDLER_POINTER_TO_FUNCTION_HIGH();
        }         
    }
    else if (value==LOW)
    {
        if(EXT_RBINTERRUPT6_HANDLER_POINTER_TO_FUNCTION_LOW)
        {
            EXT_RBINTERRUPT6_HANDLER_POINTER_TO_FUNCTION_LOW();
        } 
    }
}
/**
 * @brief: ISR function to callback function to be executed when the interrupt happens on rb13
 * @param value: to choose which function should be executed
 */ 
void RB7_ISR(uint8 value)
{
    EXT_RBx_INTERRUPT_FLAG_CLEAR();
    if (value==HIGH)
    {
        if(EXT_RBINTERRUPT7_HANDLER_POINTER_TO_FUNCTION_HIGH)
        {
            EXT_RBINTERRUPT7_HANDLER_POINTER_TO_FUNCTION_HIGH();
        }         
    }
    else if (value==LOW)
    {
        if(EXT_RBINTERRUPT7_HANDLER_POINTER_TO_FUNCTION_LOW)
        {
            EXT_RBINTERRUPT7_HANDLER_POINTER_TO_FUNCTION_LOW();
        } 
    }
}
