/* 
 * File:   hal_spi.c
 * Author: imina
 *
 * Created on April 27, 2024, 2:29 PM
 */
#include "hal_spi.h"

#if SPI_INTERRUPT_ENABLE_ == SPI_INTERRUPT_FEATURE_ENABLED
    static void(*SPI_HANDLER_POINTER_TO_FUNCTION)(void)=NULL;
#endif

/**
 * @brief: helper function to configure master 
 * @param spi: struct has all information about SPI
 */    
void SPI_master_config(const spi_t *spi);    
/**
 * @brief: helper function to configure slave 
 * @param spi: struct has all information about SPI
 */
void SPI_slave_config(const spi_t *spi);


/**
 * @brief: function to initialize SPI
 * @param spi: struct has all information about SPI
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType SPI_INIT(const spi_t *spi){
    Std_ReturnType ret = E_OK;
    if(NULL == spi){
        ret=E_NOT_OK;
    }else{
        SPI_DISABLES_SERIAL_PORT();
        CLEAR_BIT(TRISC,5);
        if(spi->SPI_master_slave_mode == SPI_MASTER_MODE){
            CLEAR_BIT(TRISC,3);
            SET_BIT(TRISA,5); 
            SPI_master_config(spi);
        }else if(spi->SPI_master_slave_mode == SPI_SLAVE_MODE){
            SET_BIT(TRISC,3);
            SET_BIT(TRISA,5);             
            SPI_slave_config(spi);
        }
#if SPI_INTERRUPT_ENABLE_ == SPI_INTERRUPT_FEATURE_ENABLED
        SPI_INTERRUPT_ENABLE();
        SPI_HANDLER_POINTER_TO_FUNCTION = spi->SPI_HANDLER;  
#if INTERRUPT_PRIORITY_FEATURE_ENABLED == INTERRUPT_PRIORITY_ENABLED
        INTERRUPT_PRIORITY_ENABLE();
        INTCONbits.GIE = 1;
        if(spi->priority == INTERRUPT_HIGH ){
            SPI_INTERRUPT_SET_HIGH_PRIORITY();
            INTERRUPT_GLOBAL_INTERRUPT_HIGH_ENABLE();
        }
        else if(spi->priority ==INTERRUPT_LOW ){
            SPI_INTERRUPT_SET_LOW_PRIORITY();
            INTERRUPT_GLOBAL_INTERRUPT_LOW_ENABLE();
        }
#else
        INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
        INTERRUPT_PREPHERAL_INTERRUPT_ENABLE();         
#endif        
#endif        

        SPI_ENABLES_SERIAL_PORT();
    }   
    return ret;
}
/**
 * @brief: function to deinitialize SPI
 * @param spi: struct has all information about SPI
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType SPI_DEINIT(const spi_t *spi){
    Std_ReturnType ret = E_OK;
    if(NULL == spi){
        ret=E_NOT_OK;
    }else{
        SPI_DISABLES_SERIAL_PORT();
#if SPI_INTERRUPT_ENABLE_ == SPI_INTERRUPT_FEATURE_ENABLED
    SPI_INTERRUPT_DISABLE();
#endif     
    }   
    return ret;    
}
/**
 * @brief: function to Receive data by SPI
 * @param spi: struct has all information about SPI
 * @return:  return the status of the function 
 * @data: pointer to data to save 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType SPI_RECEIVE_DATA_POLLING(const spi_t *spi, uint8 *data){
    Std_ReturnType ret = E_OK;
    if(NULL == spi){
        ret=E_NOT_OK;
    }else{
        while(!SPI_RECEIVE_COMPLETE_SSPBUF_STATUS());
        *data = SSPBUF;
        PIR1bits.SSPIF =0;
    }   
    return ret;    
}
/**
 * @brief: function to send data by SPI
 * @param spi: struct has all information about SPI
 * @return:  return the status of the function 
 * @data: variable to write data 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType SPI_SEND_DATA_POLLING(const spi_t *spi, uint8 data){
    Std_ReturnType ret = E_OK;
    uint8 puff =0;
    if(NULL == spi){
        ret=E_NOT_OK;
    }else{
        SSPBUF = data;
        while(!SSPSTATbits.BF);
        puff= SSPBUF;        
        PIR1bits.SSPIF =0;

    }   
    return ret;    
}
/**
 * @brief: function to Receive data by SPI
 * @param spi: struct has all information about SPI
 * @return:  return the status of the function 
 * @data: pointer to data to save 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType SPI_RECEIVE_DATA_INTERRUPT(const spi_t *spi, uint8 *data){
    Std_ReturnType ret = E_OK;
    if(NULL == spi){
        ret=E_NOT_OK;
    }else{
        if(PIR1bits.SSPIF == 1){
            *data = SSPBUF;
            PIR1bits.SSPIF =0;
        }else{
            ret=E_NOT_OK;
        }
    }   
    return ret;    
}
/**
 * @brief: function to send data by SPI
 * @param spi: struct has all information about SPI
 * @return:  return the status of the function 
 * @data: variable to write data 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType SPI_SEND_DATA_INTERRUPT(const spi_t *spi, uint8 data){
    Std_ReturnType ret = E_OK;
    if(NULL == spi){
        ret=E_NOT_OK;
    }else{
        if( (PIR1bits.SSPIF == 0) || (1 == SSPSTATbits.BF)){
            SSPBUF = data;
            PIR1bits.SSPIF =0;
        }else{
            ret=E_NOT_OK;
        }
    }   
    return ret;    
}

/**
 * @brief: helper function to configure master 
 * @param spi: struct has all information about SPI
 */
void SPI_master_config(const spi_t *spi){
    if(spi->SPI_IDLE_STATE_FOR_CLOCK == SPI_IDLE_STATE_FOR_CLOCK_IS_HIGH){
        SPI_IDLE_STATE_FOR_CLOCK_IS_HIGH_ENABLED();
    }else if(spi->SPI_IDLE_STATE_FOR_CLOCK == SPI_IDLE_STATE_FOR_CLOCK_IS_LOW){
        SPI_IDLE_STATE_FOR_CLOCK_IS_LOW_ENABLED();
    }
    if(spi->SPI_TRANSMIT_OCCURS == SPI_TRANSMIT_OCCURS_ON_TRANSITION_FROM_ACTIVE_TO_IDLE_CLOCK_STATE){
        SPI_TRANSMIT_OCCURS_ON_TRANSITION_FROM_ACTIVE_TO_IDLE_CLOCK_STATE_ENABLED();
    }else if(spi->SPI_TRANSMIT_OCCURS == SPI_TRANSMIT_OCCURS_ON_TRANSITION_FROM_IDLE_TO_ACTIVE_CLOCK_STATE){
        SPI_TRANSMIT_OCCURS_ON_TRANSITION_FROM_IDLE_TO_ACTIVE_CLOCK_STATE_ENABLED();
    }
    if(spi->SPI_INPUT_DATA_SAMPLED == SPI_INPUT_DATA_SAMPLED_AT_END_OF_DATA_OUTPUT_TIME)
    {
        SPI_INPUT_DATA_SAMPLED_AT_END_OF_DATA_OUTPUT_TIME_ENABLED();    
    }else if(spi->SPI_INPUT_DATA_SAMPLED == SPI_INPUT_DATA_SAMPLED_AT_MIDDLE_OF_DATA_OUTPUT_TIME){
        SPI_INPUT_DATA_SAMPLED_AT_MIDDLE_OF_DATA_OUTPUT_TIME_ENABLED();
    }
    switch (spi->SPI_MODE_CLOCK){
        case SPI_Master_mode_clock_FOSC_by_4:SPI_MODE_CLOCK_SELECT(SPI_Master_mode_clock_FOSC_by_4);break;
        case SPI_Master_mode_clock_FOSC_by_16:SPI_MODE_CLOCK_SELECT(SPI_Master_mode_clock_FOSC_by_16);break;
        case SPI_Master_mode_clock_FOSC_by_64:SPI_MODE_CLOCK_SELECT(SPI_Master_mode_clock_FOSC_by_64);break;
        case SPI_Master_mode_clock_FOSC_TMR2_output_by_2:SPI_MODE_CLOCK_SELECT(SPI_Master_mode_clock_FOSC_TMR2_output_by_2);break;
    }    
}
/**
 * @brief: helper function to configure master 
 * @param spi: struct has all information about SPI
 */
void SPI_slave_config(const spi_t *spi){
    if(spi->SPI_IDLE_STATE_FOR_CLOCK == SPI_IDLE_STATE_FOR_CLOCK_IS_HIGH){
        SPI_IDLE_STATE_FOR_CLOCK_IS_HIGH_ENABLED();
    }else if(spi->SPI_IDLE_STATE_FOR_CLOCK == SPI_IDLE_STATE_FOR_CLOCK_IS_LOW){
        SPI_IDLE_STATE_FOR_CLOCK_IS_LOW_ENABLED();
    }
    if(spi->SPI_TRANSMIT_OCCURS == SPI_TRANSMIT_OCCURS_ON_TRANSITION_FROM_ACTIVE_TO_IDLE_CLOCK_STATE){
        SPI_TRANSMIT_OCCURS_ON_TRANSITION_FROM_ACTIVE_TO_IDLE_CLOCK_STATE_ENABLED();
    }else if(spi->SPI_TRANSMIT_OCCURS == SPI_TRANSMIT_OCCURS_ON_TRANSITION_FROM_IDLE_TO_ACTIVE_CLOCK_STATE){
        SPI_TRANSMIT_OCCURS_ON_TRANSITION_FROM_IDLE_TO_ACTIVE_CLOCK_STATE_ENABLED();
    }
     SPI_SLAVE_SMP();
    switch (spi->SPI_MODE_CLOCK){
        case SPI_Slave_mode_clock_SCK_pin_SS_pin_enabled:SPI_MODE_CLOCK_SELECT(SPI_Slave_mode_clock_SCK_pin_SS_pin_enabled);break;
        case SPI_Slave_mode_clock_SCK_pin_SS_pin_disabled:SPI_MODE_CLOCK_SELECT(SPI_Slave_mode_clock_SCK_pin_SS_pin_disabled);break;
    }
}
/**
 * ISR function
 */
void SPI_ISR(void){
    PIR1bits.SSPIF =0;
    if(SPI_HANDLER_POINTER_TO_FUNCTION){
        SPI_HANDLER_POINTER_TO_FUNCTION();
    }
}