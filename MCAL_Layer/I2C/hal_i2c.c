/* 
 * File:   hal_i2c.c
 * Author: imina
 *
 * Created on February 25, 2024, 10:34 PM
 */

#include "hal_i2c.h"


#if I2C_INTERRUPT_ENABLE_ == I2C_INTERRUPT_FEATURE_ENABLED
    static void(*I2C_Repot_Write_Collision_HANDLER)(void)=NULL;
    static void(*I2C_Interrupt_Default_HANDLER)(void)=NULL;  
    static void(*I2C_Repot_Receive_Overflow_HANDLER)(void)=NULL;
#endif
/**
 * @brief: function to initialize I2C
 * @param i2c_obj: struct has all information about I2C
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType MSSP_I2C_Init (const mssp_i2c_t *i2c_obj){
    Std_ReturnType ret = E_OK;
    if(NULL == i2c_obj){
        ret=E_NOT_OK;
    }
    else
    {
        MSSP_MODULE_DISABLE_CFG();
        
        if(i2c_obj->i2c_cfg.mode == I2C_MSSP_MASTER_MODE){
            SSPCON1bits.SSPM=i2c_obj->i2c_cfg.mode_cfg;
            SSPADD =(uint8)(((_XTAL_FREQ / 4.0) / i2c_obj->i2c_clock) -1);
        }else if(i2c_obj->i2c_cfg.mode == I2C_MSSP_SLAVE_MODE){
            SSPCON1bits.SSPM=i2c_obj->i2c_cfg.mode_cfg;
            if(I2C_GENERAL_CALL_ENABLE ==i2c_obj->i2c_cfg.general_call){
                I2C_GENERAL_CALL_ENABLE_CFG();
            }else if(I2C_GENERAL_CALL_DISABLE ==i2c_obj->i2c_cfg.general_call){
                I2C_GENERAL_CALL_DISABLE_CFG();
            }
            SSPCON1bits.WCOL = 0;
            SSPCON1bits.SSPOV = 0;
            SSPCON1bits.CKP = 1;
            SSPADD = i2c_obj->i2c_cfg.i2c_slave_address;
        }
        TRISCbits.TRISC3 = 0x01;
        TRISCbits.TRISC4 = 0x01;
        
        if( I2C_SLEW_RATE_ENABLE ==i2c_obj->i2c_cfg.slew_rate){
            I2C_SLEW_RATE_ENABLE_CFG();
        }else if(I2C_SLEW_RATE_DISABLE ==i2c_obj->i2c_cfg.slew_rate){
            I2C_SLEW_RATE_DISABLE_CEG();   
        }        
        else{}
        
        if( I2C_SMBus_ENABLE ==i2c_obj->i2c_cfg.SMBus_control){
            I2C_SMBus_ENABLE_CFG();
        }else if(I2C_SMBus_DISABLE ==i2c_obj->i2c_cfg.SMBus_control){
            I2C_SMBus_DISABLE_CFG();   
        }else{}

#if I2C_INTERRUPT_ENABLE_ == I2C_INTERRUPT_FEATURE_ENABLED
        I2C_INTERRUPT_ENABLE();
        I2C_BUS_COLI_INTERRUPT_ENABLE();
        
        I2C_INTERRUPT_CLEAR_FLAG();
        I2C_BUS_COLI_INTERRUPT_CLEAR_FLAG();
        
        I2C_Interrupt_Default_HANDLER =i2c_obj->I2C_Interrupt_Default_handler;  
        I2C_Repot_Write_Collision_HANDLER =i2c_obj->I2C_Repot_Write_Collision; 
        I2C_Repot_Receive_Overflow_HANDLER =i2c_obj->I2C_Repot_Receive_Overflow;  
#if INTERRUPT_PRIORITY_FEATURE_ENABLED == INTERRUPT_PRIORITY_ENABLED
        INTERRUPT_PRIORITY_ENABLE();
        INTCONbits.GIE = 1;
        if(i2c_obj->i2c_cfg.mssp_priority == INTERRUPT_HIGH ){
            I2C_INTERRUPT_SET_HIGH_PRIORITY();
            INTERRUPT_GLOBAL_INTERRUPT_HIGH_ENABLE();
        }
        else if(i2c_obj->i2c_cfg.mssp_priority == INTERRUPT_LOW ){
            I2C_INTERRUPT_SET_LOW_PRIORITY();
            INTERRUPT_GLOBAL_INTERRUPT_LOW_ENABLE();
        }else{}

        if(i2c_obj->i2c_cfg.bus_coli_priority == INTERRUPT_HIGH ){
            I2C_BUS_COLI_INTERRUPT_SET_HIGH_PRIORITY();
            INTERRUPT_GLOBAL_INTERRUPT_HIGH_ENABLE();
        }
        else if(i2c_obj->i2c_cfg.bus_coli_priority == INTERRUPT_LOW ){
            I2C_BUS_COLI_INTERRUPT_SET_LOW_PRIORITY();
            INTERRUPT_GLOBAL_INTERRUPT_LOW_ENABLE();
        }else{}        
#else
        INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
        INTERRUPT_PREPHERAL_INTERRUPT_ENABLE();        
#endif        
#endif
        MSSP_MODULE_ENABLE_CFG();
        
    }
    return ret;
}
/**
 * @brief: function to deinitialize I2C
 * @param i2c_obj: struct has all information about I2C
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType MSSP_I2C_Deinit (const mssp_i2c_t *i2c_obj){
    Std_ReturnType ret = E_OK;
    if(NULL == i2c_obj){
        ret=E_NOT_OK;
    }
    else
    { 
        MSSP_MODULE_DISABLE_CFG();
#if I2C_INTERRUPT_ENABLE_ == I2C_INTERRUPT_FEATURE_ENABLED
        I2C_INTERRUPT_DISABLE();
        I2C_BUS_COLI_INTERRUPT_DISABLE();
#endif        
        
    }
    return ret;    
}
/**
 * @brief: function to send start bit by I2C
 * @param i2c_obj: struct has all information about I2C
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType MSSP_I2C_Master_Send_Start (const mssp_i2c_t *i2c_obj){
    Std_ReturnType ret = E_OK;
    if(NULL == i2c_obj){
        ret=E_NOT_OK;
    }
    else
    { 
        SSPCON2bits.SEN = 1;
        while(SSPCON2bits.SEN);
        PIR1bits.SSPIF=0;
        if(I2C_START_BIT_DETECTED == SSPSTATbits.S ){
            ret = E_OK;
        }else if (I2C_START_BIT_NOT_DETECTED == SSPSTATbits.S ){
            ret=E_NOT_OK;
        }
    }
    return ret;    
}
/**
 * @brief: function to send repeated start bit by I2C
 * @param i2c_obj: struct has all information about I2C
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType MSSP_I2C_Master_Send_Repeated_Start (const mssp_i2c_t *i2c_obj){
    Std_ReturnType ret = E_OK;
    if(NULL == i2c_obj){
        ret=E_NOT_OK;
    }
    else
    { 
        SSPCON2bits.RSEN = 1;
        while(SSPCON2bits.RSEN);
        PIR1bits.SSPIF=0;
 
    }
    return ret;    
}
/**
 * @brief: function to send stop bit by I2C
 * @param i2c_obj: struct has all information about I2C
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType MSSP_I2C_Mastelr_Send_Stop (const mssp_i2c_t *i2c_obj){
    Std_ReturnType ret = E_OK;
    if(NULL == i2c_obj){
        ret=E_NOT_OK;
    }
    else
    {
        SSPCON2bits.PEN = 1;
        SSPCON2bits.PEN = 1;
        while(SSPCON2bits.PEN);
        PIR1bits.SSPIF=0;
        if(I2C_STOP_BIT_DETECTED == SSPSTATbits.P ){
            ret = E_OK;
        }else if (I2C_STOP_BIT_NOT_DETECTED == SSPSTATbits.P ){
            ret=E_NOT_OK;
        }
        
    }
    return ret;    
}
/**
 * @brief: function to send data by I2C
 * @param i2c_obj: struct has all information about I2C
 * @param i2c_data: data want to send 
 * @param ack: if data is _RECEIVED_FROM_SLAVE  or not 
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType MSSP_I2C_Write_POLLING (const mssp_i2c_t *i2c_obj, uint8 i2c_data,uint8 *ack){
    Std_ReturnType ret = E_OK;
    if((NULL == i2c_obj)||(NULL==ack)) {
        ret=E_NOT_OK;
    }
    else
    { 
        SSPBUF = i2c_data;
        while(!PIR1bits.SSPIF);
        PIR1bits.SSPIF=0;
        if(I2C_ACK_RECEIVED_FROM_SLAVE == SSPCON2bits.ACKSTAT){
            *ack = I2C_ACK_RECEIVED_FROM_SLAVE;
        }else{
            *ack = I2C_ACK_NOT_RECEIVED_FROM_SLAVE;   
        }
    }
    return ret;    
}
/**
 * @brief: function to send data by I2C
 * @param i2c_obj: struct has all information about I2C
 * @param i2c_data: data want to send 
 * @param ack: if data is _RECEIVED_FROM_SLAVE  or not 
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType MSSP_I2C_Write_interrupt(const mssp_i2c_t *i2c_obj, uint8 i2c_data,uint8 *ack){
    Std_ReturnType ret = E_OK;
    if((NULL == i2c_obj)||(NULL==ack)) {
        ret=E_NOT_OK;
    }
    else
    { 
        if((PIR1bits.SSPIF == 0) || (1 == SSPSTATbits.BF)){
            SSPBUF = i2c_data;
            PIR1bits.SSPIF =0;
        }
        else{}
        if(I2C_ACK_RECEIVED_FROM_SLAVE == SSPCON2bits.ACKSTAT){
            *ack = I2C_ACK_RECEIVED_FROM_SLAVE;
        }else{
            *ack = I2C_ACK_NOT_RECEIVED_FROM_SLAVE;   
        }
    }
    return ret;    
}

/**
 * @brief: function to read data by I2C
 * @param i2c_obj: struct has all information about I2C
 * @param i2c_data: pointer to save data want to read 
 * @param ack: choose master or slave to read  
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType MSSP_I2C_Read (const mssp_i2c_t *i2c_obj,uint8 ack, uint8 *i2c_data){
    Std_ReturnType ret = E_OK;
    if( (NULL == i2c_obj)||(NULL == i2c_data) ){
        ret=E_NOT_OK;
    }
    else
    { 
        I2C_MASTER_RECEIVE_ENABLE_CFG();
        while(!SSPSTATbits.BF);
        *i2c_data = SSPBUF;
        if(I2C_ACK_RECEIVED_FROM_MASTER == ack ){
            SSPCON2bits.ACKDT = 0;
            SSPCON2bits.ACKEN = 1;            
        }else{
            SSPCON2bits.ACKDT = 1;
            SSPCON2bits.ACKEN = 1;       
        }
    }
    return ret;    
}
/**
 * function to call ISR
 */
void MSSP_I2C_ISR(void)
{
#if I2C_INTERRUPT_ENABLE_ == I2C_INTERRUPT_FEATURE_ENABLED    
    I2C_INTERRUPT_CLEAR_FLAG();
    PIR1bits.SSPIF = 0;
    if(I2C_Interrupt_Default_HANDLER)
    {
    I2C_Interrupt_Default_HANDLER();
    }
#endif
}
/**
 * function to call ISR
 */
void BUS_COLI_ISR(void){
#if I2C_INTERRUPT_ENABLE_ == I2C_INTERRUPT_FEATURE_ENABLED        
    I2C_BUS_COLI_INTERRUPT_CLEAR_FLAG();
    if(I2C_Repot_Write_Collision_HANDLER)
    {
    I2C_Repot_Write_Collision_HANDLER();
    }
#endif    
}