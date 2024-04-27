/* 
 * File:   hal_spi.h
 * Author: imina
 *
 * Created on April 27, 2024, 2:29 PM
 */

#ifndef HAL_SPI_H
#define	HAL_SPI_H

/* section: Includes */
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../INTERRUPTS/mcal_internal_interrupt.h"
#include "pic18f4620.h"
/* section: Macro Declarations */

/* SPI Master mode */
#define  SPI_INPUT_DATA_SAMPLED_AT_END_OF_DATA_OUTPUT_TIME        1
#define  SPI_INPUT_DATA_SAMPLED_AT_MIDDLE_OF_DATA_OUTPUT_TIME     0
/*SPI Clock Select bit*/
#define  SPI_TRANSMIT_OCCURS_ON_TRANSITION_FROM_ACTIVE_TO_IDLE_CLOCK_STATE   1
#define  SPI_TRANSMIT_OCCURS_ON_TRANSITION_FROM_IDLE_TO_ACTIVE_CLOCK_STATE   0
/* CKP: Clock Polarity Select bit */
#define  SPI_IDLE_STATE_FOR_CLOCK_IS_HIGH   1 
#define  SPI_IDLE_STATE_FOR_CLOCK_IS_LOW    0 

#define  SPI_MASTER_MODE    1 
#define  SPI_SLAVE_MODE     0 

/* section: Macro functions Declarations */

/* SPI Master mode */
#define SPI_INPUT_DATA_SAMPLED_AT_END_OF_DATA_OUTPUT_TIME_ENABLED()    (SSPSTATbits.SMP = 1)
#define SPI_INPUT_DATA_SAMPLED_AT_MIDDLE_OF_DATA_OUTPUT_TIME_ENABLED() (SSPSTATbits.SMP = 0)

#define SPI_SLAVE_SMP()                                                (SSPSTATbits.SMP = 0)
/*SPI Clock Select bit*/
#define SPI_TRANSMIT_OCCURS_ON_TRANSITION_FROM_ACTIVE_TO_IDLE_CLOCK_STATE_ENABLED() (SSPSTATbits.CKE = 1)
#define SPI_TRANSMIT_OCCURS_ON_TRANSITION_FROM_IDLE_TO_ACTIVE_CLOCK_STATE_ENABLED() (SSPSTATbits.CKE = 0)
/* BF: Buffer Full Status bit (Receive mode only)*/
#define SPI_RECEIVE_COMPLETE_SSPBUF_STATUS()                 (SSPSTATbits.BF)   
/* SSPEN: Master Synchronous Serial Port Enable bit*/
#define SPI_ENABLES_SERIAL_PORT()                            (SSPCON1bits.SSPEN =1)
#define SPI_DISABLES_SERIAL_PORT()                           (SSPCON1bits.SSPEN =0)
/* CKP: Clock Polarity Select bit */
#define  SPI_IDLE_STATE_FOR_CLOCK_IS_HIGH_ENABLED()          (SSPCON1bits.CKP=1)
#define  SPI_IDLE_STATE_FOR_CLOCK_IS_LOW_ENABLED()           (SSPCON1bits.CKP=0)
/*Master Synchronous Serial Port Mode Select bits */
#define  SPI_MODE_CLOCK_SELECT(_mode_)                   (SSPCON1bits.SSPM = _mode_)

/* section: Data type Declarations */

/*Master Synchronous Serial Port Mode Select bits */
typedef enum {
    SPI_Master_mode_clock_FOSC_by_4 = 0,
    SPI_Master_mode_clock_FOSC_by_16,
    SPI_Master_mode_clock_FOSC_by_64,
    SPI_Master_mode_clock_FOSC_TMR2_output_by_2,
    SPI_Slave_mode_clock_SCK_pin_SS_pin_enabled,
    SPI_Slave_mode_clock_SCK_pin_SS_pin_disabled,
}spi_mode_t;

typedef struct {
#if SPI_INTERRUPT_ENABLE_  == SPI_INTERRUPT_FEATURE_ENABLED
    void(*SPI_HANDLER)(void);
    interrupt_priority_t priority;
#endif        
    spi_mode_t SPI_MODE_CLOCK;
    uint8 SPI_master_slave_mode;
    uint8 SPI_INPUT_DATA_SAMPLED;
    uint8 SPI_TRANSMIT_OCCURS;
    uint8 SPI_IDLE_STATE_FOR_CLOCK;
}spi_t;

/* section: functions Declarations */
/**
 * @brief: function to initialize SPI
 * @param spi: struct has all information about SPI
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType SPI_INIT(const spi_t *spi);
/**
 * @brief: function to deinitialize SPI
 * @param spi: struct has all information about SPI
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType SPI_DEINIT(const spi_t *spi);
/**
 * @brief: function to Receive data by SPI
 * @param spi: struct has all information about SPI
 * @return:  return the status of the function 
 * @data: pointer to data to save 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType SPI_RECEIVE_DATA_POLLING(const spi_t *spi, uint8 *data);
/**
 * @brief: function to send data by SPI
 * @param spi: struct has all information about SPI
 * @return:  return the status of the function 
 * @data: variable to write data 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType SPI_SEND_DATA_POLLING(const spi_t *spi, uint8 data);
/**
 * @brief: function to Receive data by SPI
 * @param spi: struct has all information about SPI
 * @return:  return the status of the function 
 * @data: pointer to data to save 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType SPI_RECEIVE_DATA_INTERRUPT(const spi_t *spi, uint8 *data);
/**
 * @brief: function to send data by SPI
 * @param spi: struct has all information about SPI
 * @return:  return the status of the function 
 * @data: variable to write data 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType SPI_SEND_DATA_INTERRUPT(const spi_t *spi, uint8 data);
/**
 * ISR function
 */
void SPI_ISR(void);

#endif	/* HAL_SPI_H */

