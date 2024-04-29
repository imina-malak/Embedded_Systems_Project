/* 
 * File:   hal_i2c.h
 * Author: imina
 *
 * Created on February 25, 2024, 10:34 PM
 */

#ifndef HAL_I2C_H
#define	HAL_I2C_H

/* section: Includes */
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../INTERRUPTS/mcal_internal_interrupt.h"
#include "pic18f4620.h"

/* section: Macro Declarations */
/* SMP: Slew Rate Control bit*/
#define I2C_SLEW_RATE_DISABLE                         0x01
#define I2C_SLEW_RATE_ENABLE                          0x00
/* CKE: SMBus Select bit*/
#define I2C_SMBus_ENABLE                              0x01
#define I2C_SMBus_DISABLE                             0x00
/* In Slave mode:*/
#define I2C_LAST_BYTE_DATA                            0x01
#define I2C_LAST_BYTE_ADDRESS                         0x00
/* S: Start bit*/
#define I2C_START_BIT_DETECTED                        0x01
#define I2C_START_BIT_NOT_DETECTED                    0x00
/* P: Stop bit*/
#define I2C_STOP_BIT_DETECTED                         0x01
#define I2C_STOP_BIT_NOT_DETECTED                     0x00

#define I2C_MSSP_MASTER_MODE                          0x01
#define I2C_MSSP_SLAVE_MODE                           0x00
/* SSPM3:SSPM0: Master Synchronous Serial Port Mode Select bits*/
#define I2C_SLAVE_MODE_7BIT_ADDRESS                   0x06U
#define I2C_SLAVE_MODE_10BIT_ADDRESS                  0x07U
#define I2C_SLAVE_MODE_7BIT_ADDRESS_SS_INT_ENABLE     0x0EU
#define I2C_SLAVE_MODE_10BIT_ADDRESS_SS_INT_ENABLE    0x0FU
#define I2C_MASTER_MODE_DEFINED_CLOCK                 0x08U
#define I2C_MASTER_MODE_FIRMWARE_CONTROLLED           0x0BU
/* GCEN: General Call Enable bit (Slave mode only)*/
#define I2C_GENERAL_CALL_ENABLE   0x01
#define I2C_GENERAL_CALL_DISABLE  0x00

#define I2C_MASTER_RECEIVE_ENABLE   0x01
#define I2C_MASTER_RECEIVE_DISABLE  0x00

/* ACKSTAT: Acknowledge Status bit (Master Transmit mode only)*/
#define I2C_ACK_RECEIVED_FROM_SLAVE          0x00
#define I2C_ACK_NOT_RECEIVED_FROM_SLAVE      0x01
/* ACKDT: Acknowledge Data bit (Master Receive mode only)*/
#define I2C_ACK_RECEIVED_FROM_MASTER          0x00
#define I2C_ACK_NOT_RECEIVED_FROM_MASTER      0x01

/* section: Macro functions Declarations */

/* SMP: Slew Rate Control bit*/
#define I2C_SLEW_RATE_DISABLE_CEG()         (SSPSTATbits.SMP= 0x01)
#define I2C_SLEW_RATE_ENABLE_CFG()          (SSPSTATbits.SMP= 0x00)
/* CKE: SMBus Select bit*/
#define I2C_SMBus_DISABLE_CFG()             (SSPSTATbits.CKE= 0x00)
#define I2C_SMBus_ENABLE_CFG()              (SSPSTATbits.CKE= 0x01) 

#define I2C_GENERAL_CALL_DISABLE_CFG()      (SSPCON2bits.GCEN = 0x00) 
#define I2C_GENERAL_CALL_ENABLE_CFG()       (SSPCON2bits.GCEN = 0x01)
/* RCEN: Receive Enable bit (Master mode only)*/
#define I2C_MASTER_RECEIVE_DISABLE_CFG()    (SSPCON2bits.RCEN = 0x00)
#define I2C_MASTER_RECEIVE_ENABLE_CFG()     (SSPCON2bits.RCEN = 0x01)

#define MSSP_MODULE_ENABLE_CFG()            (SSPCON1bits.SSPEN = 0x01)
#define MSSP_MODULE_DISABLE_CFG()           (SSPCON1bits.SSPEN = 0x00)
/* CKP: SCK Release Control bit */
#define I2C_CLOCK_STRETCH_ENABLE()           (SSPCON1bits.CKP=0)
#define I2C_CLOCK_STRETCH_DISABLE()          (SSPCON1bits.CKP=1)  
/* section: Data type Declarations */

typedef struct {
    uint8 mode_cfg;
    uint8 i2c_slave_address;
    uint8 mode : 1;
    uint8 slew_rate: 1;
    uint8 SMBus_control: 1;
    uint8 general_call: 1;
    uint8 master_rec_mode: 1;
    uint8 reserved : 3;
#if I2C_INTERRUPT_ENABLE_ == I2C_INTERRUPT_FEATURE_ENABLED    
    interrupt_priority_t mssp_priority;
    interrupt_priority_t bus_coli_priority;
#endif    
}i2c_configs_t;

typedef struct{
    uint32 i2c_clock;
#if I2C_INTERRUPT_ENABLE_ == I2C_INTERRUPT_FEATURE_ENABLED    
    void(*I2C_Repot_Write_Collision)(void);
    void(*I2C_Interrupt_Default_handler)(void);
    void(*I2C_Repot_Receive_Overflow)(void);       
#endif
    i2c_configs_t i2c_cfg;
}mssp_i2c_t;
/* section: functions Declarations */
/**
 * @brief: function to initialize I2C
 * @param i2c_obj: struct has all information about I2C
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType MSSP_I2C_Init (const mssp_i2c_t *i2c_obj);
/**
 * @brief: function to deinitialize I2C
 * @param i2c_obj: struct has all information about I2C
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType MSSP_I2C_Deinit (const mssp_i2c_t *i2c_obj) ;
/**
 * @brief: function to send start bit by I2C
 * @param i2c_obj: struct has all information about I2C
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType MSSP_I2C_Master_Send_Start (const mssp_i2c_t *i2c_obj);
/**
 * @brief: function to send repeated start bit by I2C
 * @param i2c_obj: struct has all information about I2C
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType MSSP_I2C_Master_Send_Repeated_Start (const mssp_i2c_t *i2c_obj);
/**
 * @brief: function to send stop bit by I2C
 * @param i2c_obj: struct has all information about I2C
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType MSSP_I2C_Mastelr_Send_Stop (const mssp_i2c_t *i2c_obj);
/**
 * @brief: function to send data by I2C
 * @param i2c_obj: struct has all information about I2C
 * @param i2c_data: data want to send 
 * @param ack: if data is _RECEIVED_FROM_SLAVE  or not 
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType MSSP_I2C_Write_POLLING (const mssp_i2c_t *i2c_obj, uint8 i2c_data,uint8 *ack);
/**
 * @brief: function to send data by I2C
 * @param i2c_obj: struct has all information about I2C
 * @param i2c_data: data want to send 
 * @param ack: if data is _RECEIVED_FROM_SLAVE  or not 
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType MSSP_I2C_Write_interrupt(const mssp_i2c_t *i2c_obj, uint8 i2c_data,uint8 *ack);
/**
 * @brief: function to read data by I2C
 * @param i2c_obj: struct has all information about I2C
 * @param i2c_data: pointer to save data want to read 
 * @param ack: choose master or slave to read  
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType MSSP_I2C_Read (const mssp_i2c_t *i2c_obj,uint8 ack, uint8 *i2c_data);
/**
 * function to call ISR
 */
void MSSP_I2C_ISR(void);
/**
 * function to call ISR
 */
void BUS_COLI_ISR(void);
#endif	/* HAL_I2C_H */

