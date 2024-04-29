/* 
 * File:   hal_usart.c
 * Author: imina
 *
 * Created on February 7, 2024, 3:17 PM
 */

#include "hal_usart.h"

/**
 * @brief: function to calculate baudrate
 * @param usart: struct has all information about USART
 */
static void BAUDRATE_CALCULATION(const usart_t *usart);
/**
 * @brief: function to initialize ASYNCHORONOUS TX 
 * @param usart: struct has all information about USART
 */
static void USART_ASYNC_TX_INIT(const usart_t *usart);
/**
 * @brief: function to initialize ASYNCHORONOUS RX 
 * @param usart: struct has all information about USART
 */
static void USART_ASYNC_RX_INIT(const usart_t *usart);
/**
 * @brief: function to initialize SYNCHORONOUS TX 
 * @param usart: struct has all information about USART
 */
static void USART_SYNC_TX_INIT(const usart_t *usart);
/**
 * @brief: function to initialize SYNCHORONOUS RX 
 * @param usart: struct has all information about USART
 */
static void USART_SYNC_RX_INIT(const usart_t *usart);


uint16 LENGTH;

#if USART_TX_INTERRUPT_ENABLE_  == USART_TX_INTERRUPT_FEATURE_ENABLED
    static void(*USART_TX_HANDLER_POINTER_TO_FUNCTION)(void)=NULL;
#endif
#if USART_RX_INTERRUPT_ENABLE_  == USART_RX_INTERRUPT_FEATURE_ENABLED
    static void(*USART_RX_HANDLER_POINTER_TO_FUNCTION)(void)=NULL;
    static void(*USART_FRAMING_ERROR_HANDLER_POINTER_TO_FUNCTION)(void)=NULL;
    static void(*USART_OVERRUN_ERROR_HANDLER_POINTER_TO_FUNCTION)(void)=NULL;
#endif 

/**
 * @brief: function to initialize USART
 * @param usart: struct has all information about USART
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType USART_INIT(const usart_t *usart){
    Std_ReturnType ret= E_NOT_OK;
    if(NULL == usart){
        ret= E_NOT_OK;
    }    
    else{
        EUSART_SERIAL_PORT_DISABLED();
        RCSTAbits.SPEN = 0;
        TRISCbits.RC6 = 1;
        TRISCbits.RC7 = 1;
        
        BAUDRATE_CALCULATION(usart);
        USART_ASYNC_TX_INIT(usart);
        USART_ASYNC_RX_INIT(usart);
        USART_SYNC_TX_INIT(usart);
        USART_SYNC_RX_INIT(usart);
        EUSART_SERIAL_PORT_ENABLED();

    }return ret;
}
/**
 * @brief: function to deinitialize USART
 * @param usart: struct has all information about USART
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType USART_DEINIT(const usart_t *usart){
    Std_ReturnType ret= E_NOT_OK;
    if(NULL == usart){
        ret= E_NOT_OK;
    }    
    else{
        EUSART_SERIAL_PORT_ENABLED();
#if USART_TX_INTERRUPT_ENABLE_  == USART_TX_INTERRUPT_FEATURE_ENABLED
    USART_TX_INTERRUPT_DISABLE();
#elif USART_RX_INTERRUPT_ENABLE_  == USART_RX_INTERRUPT_FEATURE_ENABLED
    USART_RX_INTERRUPT_DISABLE();
#endif        
    }return ret;
}

/**
 * @brief: function to send data by USART
 * @param usart: struct has all information about USART
 * @param value: byte you want to send
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType USART_TRANSMIT_BYTE_BLOCKING(const usart_t *usart,uint8 value ){
    Std_ReturnType ret= E_NOT_OK;
    if(NULL == usart){
        ret= E_NOT_OK;
    }    
    else{
        while(!TXSTAbits.TRMT);
#if USART_TX_INTERRUPT_ENABLE_ == USART_TX_INTERRUPT_FEATURE_ENABLED        
        USART_TX_INTERRUPT_ENABLE();
#endif
        TXREG = value;
    }return ret;    
}

/**
 * @brief: function to send data by USART BUT LOOP IN MAIN
 * @param usart: struct has all information about USART
 * @param value: byte you want to send
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType USART_TRANSMIT_BYTE_NOT_BLOCKING(const usart_t *usart,uint8 value ){
    Std_ReturnType ret= E_NOT_OK;
    if((NULL == usart )){
        ret= E_NOT_OK;
    }    
    else{
        if(1==TXSTAbits.TRMT)
        {
#if USART_TX_INTERRUPT_ENABLE_ == USART_TX_INTERRUPT_FEATURE_ENABLED        
        USART_TX_INTERRUPT_ENABLE();
#endif            
            TXREG = value;
            LENGTH++;
            ret= E_OK;
        }else{
            ret= E_NOT_OK;
        } 
    }return ret;     
}
/**
 * @brief: function to receive data by USART
 * @param usart: struct has all information about USART
 * @param value: byte was sent 
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType USART_RECEIVE_BYTE_BLOCKING(const usart_t *usart, uint8 *value){
    Std_ReturnType ret= E_NOT_OK;
    if((NULL == usart )){
        ret= E_NOT_OK;
    }    
    else{
        while(!PIR1bits.RCIF);
        *value = RCREG;
        
    }return ret;    
}
/**
 * @brief: function to receive data by USART BUT LOOP IN MAIN
 * @param usart: struct has all information about USART
 * @param value: byte was sent 
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType USART_RECEIVE_BYTE_NOT_BLOCKING(const usart_t *usart, uint8 *value){
    Std_ReturnType ret= E_NOT_OK;
    if(NULL == usart)
    {
        ret= E_NOT_OK;
    }    
    else{
        if(1==PIR1bits.RCIF)
        {
            ret= E_OK;
            *value = RCREG;
        }else
        {
            ret= E_NOT_OK;
        } 
    }
return ret;      
}
/**
 * @brief: function to send data by USART
 * @param usart: struct has all information about USART
 * @param value: text you want to send
 * @param len: length of the text 
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType USART_TRANSMIT_STRING_BLOCKING(const usart_t *usart,uint8 *value,uint16 len  ){
    Std_ReturnType ret= E_NOT_OK;
    if((NULL == usart )){
        ret= E_NOT_OK;
    }    
    else{
        for(uint16 i=0;i<len;i++)
        {
            USART_TRANSMIT_BYTE_BLOCKING(usart , value[i]);
        }
    }return ret; 
}
/**
 * @brief: function to send data by USART BUT LOOP IN MAIN
 * @param usart: struct has all information about USART
 * @param value: text you want to send
 * @param len: length of the text 
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType USART_TRANSMIT_STRING_NOT_BLOCKING(const usart_t *usart,uint8 *value,uint16 len){
    Std_ReturnType ret= E_NOT_OK;
    if((NULL == usart )){
        ret= E_NOT_OK;
    }    
    else{
        for(LENGTH=0;LENGTH<len;)
        {
            USART_TRANSMIT_BYTE_NOT_BLOCKING(usart , value[LENGTH]);
        }
    }return ret;     
}
/**
 * @brief: function to calculate baudrate
 * @param usart: struct has all information about USART
 */
static void BAUDRATE_CALCULATION(const usart_t *usart){
    float BRUDRATE_RES=0;
    switch(usart->baudrate_cfg){
        case(BAUDRATE_ASYN_8BIT_LOW_SPEED):
            EUSART_ASYNCHRONOUS_MODE_ENABLED();
            TXSTAbits.SYNC = 0;
            EUSART_ASYNCHRONOUS_LOW_SPEED_ENABLED();
            EUSART_8_BIT_BAUD_RATE_GENERATOR();
            BRUDRATE_RES = ((_XTAL_FREQ / (float)usart->baudrate )/64)-1;
            break; 
        case(BAUDRATE_ASYN_8BIT_HIGH_SPEED):
            EUSART_ASYNCHRONOUS_MODE_ENABLED();
            EUSART_ASYNCHRONOYS_HIGH_SPEED_ENABLED();
            EUSART_8_BIT_BAUD_RATE_GENERATOR();       
            BRUDRATE_RES = ((_XTAL_FREQ / (float)usart->baudrate )/16)-1;
            break; 
        case(BAUDRATE_ASYN_16BIT_LOW_SPEED):
            EUSART_ASYNCHRONOUS_MODE_ENABLED();
            EUSART_ASYNCHRONOUS_LOW_SPEED_ENABLED();
            EUSART_16_BIT_BAUD_RATE_GENERATOR();          
            BRUDRATE_RES = ((_XTAL_FREQ / (float)usart->baudrate )/16)-1;            
            break; 
        case(BAUDRATE_ASYN_16BIT_HIGH_SPEED):
            EUSART_ASYNCHRONOUS_MODE_ENABLED();
            EUSART_ASYNCHRONOYS_HIGH_SPEED_ENABLED();
            EUSART_16_BIT_BAUD_RATE_GENERATOR();      
            BRUDRATE_RES = ((_XTAL_FREQ / (float)usart->baudrate )/4)-1;
            break; 
        case(BAUDRATE_SYN_8BIT):
            EUSART_SYNCHRONOUS_MODE_ENABLED();
            TXSTAbits.SYNC = 1;
            if(usart->usart_tx_cfg.usart_tx_sync_master_mode == EUSART_SYNCHRONOUS_MASTER_MODE){
                EUSART_SYNCHRONOUS_MASTER_MODE_TX_ENABLED();
            }else if(usart->usart_tx_cfg.usart_tx_sync_master_mode == EUSART_SYNCHRONOUS_SLAVE_MODE){
                EUSART_SYNCHRONOUS_SLAVE_MODE_TX_ENABLED();
            }
            EUSART_8_BIT_BAUD_RATE_GENERATOR();            
            BRUDRATE_RES = ((_XTAL_FREQ /(float)usart->baudrate )/4)-1;
            break; 
        case(BAUDRATE_SYN_16BIT):
            EUSART_SYNCHRONOUS_MODE_ENABLED();
            if(usart->usart_tx_cfg.usart_tx_sync_master_mode == EUSART_SYNCHRONOUS_MASTER_MODE){
                EUSART_SYNCHRONOUS_MASTER_MODE_TX_ENABLED();
            }else if(usart->usart_tx_cfg.usart_tx_sync_master_mode == EUSART_SYNCHRONOUS_SLAVE_MODE){
                EUSART_SYNCHRONOUS_SLAVE_MODE_TX_ENABLED();
            }            
            EUSART_16_BIT_BAUD_RATE_GENERATOR();            
            BRUDRATE_RES = (float)((_XTAL_FREQ / usart->baudrate )/4)-1;
            break; 
        default:
            break;
    }  
    SPBRG =  (uint8)(uint32)(BRUDRATE_RES);
    SPBRGH=  (uint8)((uint32)BRUDRATE_RES >> 8);
} 
/**
 * @brief: function to initialize ASYNCHORONOUS TX 
 * @param usart: struct has all information about USART
 */
static void USART_ASYNC_TX_INIT(const usart_t *usart){
    if (usart->usart_tx_cfg.usart_tx_enable == EUSART_ASYNCHRONOUS_TX_ENABLE ){
        EUSART_USART_TX_ENABLED();
#if USART_TX_INTERRUPT_ENABLE_  == USART_TX_INTERRUPT_FEATURE_ENABLED
      USART_TX_INTERRUPT_ENABLE();  
#if INTERRUPT_PRIORITY_FEATURE_ENABLED == INTERRUPT_PRIORITY_ENABLED
        INTERRUPT_PRIORITY_ENABLE();
        INTCONbits.GIE = 1;
        if(usart->usart_tx_cfg.usart_tx_priority == INTERRUPT_HIGH ){
            USART_TX_INTERRUPT_SET_HIGH_PRIORITY();
            INTERRUPT_GLOBAL_INTERRUPT_HIGH_ENABLE();
        }
        else if(usart->usart_tx_cfg.usart_tx_priority ==INTERRUPT_LOW ){
            USART_TX_INTERRUPT_SET_LOW_PRIORITY();
            INTERRUPT_GLOBAL_INTERRUPT_LOW_ENABLE();
        }
#else
        INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
        INTERRUPT_PREPHERAL_INTERRUPT_ENABLE();         
#endif      
        
#else  
        PIE1bits.TXIE = EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE;
#endif
        if( EUSART_ASYNCHRONOUS_9Bit_TX_ENABLE == usart->usart_tx_cfg.usart_tx_9bit_enable ){
            EUSART_USART_9Bit_TX_ENABLED();
        }else if(EUSART_ASYNCHRONOUS_9Bit_TX_DISABLE == usart->usart_tx_cfg.usart_tx_9bit_enable){
            EUSART_USART_9Bit_TX_DISABLED();        
        }  
    }else{}
}
/**
 * @brief: function to initialize ASYNCHORONOUS RX 
 * @param usart: struct has all information about USART
 */
static void USART_ASYNC_RX_INIT(const usart_t *usart){
    if (usart->usart_rx_cfg.usart_rx_enable == EUSART_ASYNCHRONOUS_RX_ENABLE ){
        EUSART_USART_RX_ENABLED();
#if USART_RX_INTERRUPT_ENABLE_  == USART_RX_INTERRUPT_FEATURE_ENABLED
      USART_RX_INTERRUPT_ENABLE();  
      USART_RX_HANDLER_POINTER_TO_FUNCTION= usart->USART_RX_HANDLER;
        USART_FRAMING_ERROR_HANDLER_POINTER_TO_FUNCTION= usart->USART_FRAMING_ERROR_HANDLER;
        USART_OVERRUN_ERROR_HANDLER_POINTER_TO_FUNCTION= usart->USART_OVERRUN_ERROR_HANDLER;      
#if INTERRUPT_PRIORITY_FEATURE_ENABLED == INTERRUPT_PRIORITY_ENABLED
        INTERRUPT_PRIORITY_ENABLE();
        INTCONbits.GIE = 1;
        if(usart->usart_rx_cfg.usart_rx_priority == INTERRUPT_HIGH ){
            USART_RX_INTERRUPT_SET_HIGH_PRIORITY();
            INTERRUPT_GLOBAL_INTERRUPT_HIGH_ENABLE();
        }
        else if(usart->usart_rx_cfg.usart_rx_priority ==INTERRUPT_LOW ){
            USART_RX_INTERRUPT_SET_LOW_PRIORITY();
            INTERRUPT_GLOBAL_INTERRUPT_LOW_ENABLE();
        }
#else
        INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
        INTERRUPT_PREPHERAL_INTERRUPT_ENABLE();         
#endif      
#else
        PIE1bits.RCIE = EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE;
#endif           
        if( EUSART_ASYNCHRONOUS_9Bit_RX_ENABLE == usart->usart_rx_cfg.usart_rx_9bit_enable ){
            EUSART_USART_9Bit_RX_ENABLED();
        }else if(EUSART_ASYNCHRONOUS_9Bit_RX_DISABLE == usart->usart_rx_cfg.usart_rx_9bit_enable){
            EUSART_USART_9Bit_RX_DISABLED();        
        }  
    }else{}
}
/**
 * @brief: function to initialize SYNCHORONOUS TX 
 * @param usart: struct has all information about USART
 */
static void USART_SYNC_TX_INIT(const usart_t *usart){
    if (usart->usart_tx_cfg.usart_tx_enable == EUSART_SYNCHRONOUS_TX_ENABLE ){
        EUSART_USART_TX_ENABLED();
#if USART_TX_INTERRUPT_ENABLE_  == USART_TX_INTERRUPT_FEATURE_ENABLED
      USART_TX_INTERRUPT_ENABLE();  
      USART_TX_HANDLER_POINTER_TO_FUNCTION= usart->USART_TX_HANDLER;
#if INTERRUPT_PRIORITY_FEATURE_ENABLED == INTERRUPT_PRIORITY_ENABLED
        INTERRUPT_PRIORITY_ENABLE();
        INTCONbits.GIE = 1;
        if(usart->usart_tx_cfg.usart_tx_priority == INTERRUPT_HIGH ){
            USART_TX_INTERRUPT_SET_HIGH_PRIORITY();
            INTERRUPT_GLOBAL_INTERRUPT_HIGH_ENABLE();
        }
        else if(usart->usart_tx_cfg.usart_tx_priority ==INTERRUPT_LOW ){
            USART_TX_INTERRUPT_SET_LOW_PRIORITY();
            INTERRUPT_GLOBAL_INTERRUPT_LOW_ENABLE();
        }
#else
        INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
        INTERRUPT_PREPHERAL_INTERRUPT_ENABLE();         
#endif      
        
#else  
        PIE1bits.TXIE = EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE;
#endif
        if( EUSART_ASYNCHRONOUS_9Bit_TX_ENABLE == usart->usart_tx_cfg.usart_tx_9bit_enable ){
            EUSART_USART_9Bit_TX_ENABLED();
        }else if(EUSART_ASYNCHRONOUS_9Bit_TX_DISABLE == usart->usart_tx_cfg.usart_tx_9bit_enable){
            EUSART_USART_9Bit_TX_DISABLED();        
        }  
    }else{}
}
/**
 * @brief: function to initialize SYNCHORONOUS RX 
 * @param usart: struct has all information about USART
 */
static void USART_SYNC_RX_INIT(const usart_t *usart){
    if (usart->usart_rx_cfg.usart_rx_enable == EUSART_SYNCHRONOUS_RX_ENABLE ){
        EUSART_USART_RX_DISABLED();
        RCSTAbits.CREN = 0;
        EUSART_SYNCHRONOUS_MASTER_DISABLES_SINGLE_RECEIVE_ENABLED();
        EUSART_SYNCHRONOUS_MASTER_ENABLES_SINGLE_RECEIVE_ENABLED();
#if USART_RX_INTERRUPT_ENABLE_  == USART_RX_INTERRUPT_FEATURE_ENABLED
      USART_RX_INTERRUPT_ENABLE();  
      USART_RX_HANDLER_POINTER_TO_FUNCTION= usart->USART_RX_HANDLER;
        USART_FRAMING_ERROR_HANDLER_POINTER_TO_FUNCTION= usart->USART_FRAMING_ERROR_HANDLER;
        USART_OVERRUN_ERROR_HANDLER_POINTER_TO_FUNCTION= usart->USART_OVERRUN_ERROR_HANDLER;      
#if INTERRUPT_PRIORITY_FEATURE_ENABLED == INTERRUPT_PRIORITY_ENABLED
        INTERRUPT_PRIORITY_ENABLE();
        INTCONbits.GIE = 1;
        if(usart->usart_rx_cfg.usart_rx_priority == INTERRUPT_HIGH ){
            USART_RX_INTERRUPT_SET_HIGH_PRIORITY();
            INTERRUPT_GLOBAL_INTERRUPT_HIGH_ENABLE();
        }
        else if(usart->usart_rx_cfg.usart_rx_priority ==INTERRUPT_LOW ){
            USART_RX_INTERRUPT_SET_LOW_PRIORITY();
            INTERRUPT_GLOBAL_INTERRUPT_LOW_ENABLE();
        }
#else
        INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
        INTERRUPT_PREPHERAL_INTERRUPT_ENABLE();         
#endif      
#else
        PIE1bits.RCIE = EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE;
#endif           
        if( EUSART_ASYNCHRONOUS_9Bit_RX_ENABLE == usart->usart_rx_cfg.usart_rx_9bit_enable ){
            EUSART_USART_9Bit_RX_ENABLED();
        }else if(EUSART_ASYNCHRONOUS_9Bit_RX_DISABLE == usart->usart_rx_cfg.usart_rx_9bit_enable){
            EUSART_USART_9Bit_RX_DISABLED();        
        }  
    }else{}
}
/**
 *  TX INTERRUPT SERVICE ROUTINE
 */
#if USART_TX_INTERRUPT_ENABLE_  == USART_TX_INTERRUPT_FEATURE_ENABLED

void USART_TX_ISR(void){
#if USART_TX_INTERRUPT_ENABLE_  == USART_TX_INTERRUPT_FEATURE_ENABLED    
    USART_TX_INTERRUPT_DISABLE();
    PIE1bits.TXIE = 0;
#endif    
    if(USART_TX_HANDLER_POINTER_TO_FUNCTION){
        USART_TX_HANDLER_POINTER_TO_FUNCTION();
    }
}
#endif
#if USART_RX_INTERRUPT_ENABLE_  == USART_RX_INTERRUPT_FEATURE_ENABLED
/**
 * RX INTERRUPT SERVICE ROUTINE function
 */
void USART_RX_ISR(void){
    if(USART_RX_HANDLER_POINTER_TO_FUNCTION){
        USART_RX_HANDLER_POINTER_TO_FUNCTION();
        USART_RX_HANDLER_POINTER_TO_FUNCTION();
    }
    if(USART_FRAMING_ERROR_HANDLER_POINTER_TO_FUNCTION){
        USART_FRAMING_ERROR_HANDLER_POINTER_TO_FUNCTION();
    }     
    if(USART_OVERRUN_ERROR_HANDLER_POINTER_TO_FUNCTION){
        USART_OVERRUN_ERROR_HANDLER_POINTER_TO_FUNCTION();
    }
}
#endif