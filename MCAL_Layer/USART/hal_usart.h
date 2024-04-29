/* 
 * File:   hal_usart.h
 * Author: imena
 *
 * Created on February 7, 2024, 3:17 PM
 */

#ifndef HAL_USART_H
#define	HAL_USART_H

/* section: Includes */
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../INTERRUPTS/mcal_internal_interrupt.h"
#include "pic18f4620.h"
#include "hal_usart_cfg.h"

/* section: Macro Declarations */

#define EUSART_SYNCHRONOUS_MASTER_MODE    1
#define EUSART_SYNCHRONOUS_SLAVE_MODE     0

#define EUSART_SYNCHRONOUS_TX_ENABLE    1
#define EUSART_SYNCHRONOUS_TX_DISABLE   0

#define EUSART_SYNCHRONOUS_RX_ENABLE    3
#define EUSART_SYNCHRONOUS_RX_DISABLE   4

#define EUSART_SYNCHRONOUS_MASTER_ENABLES_SINGLE_RECEIVE     1
#define EUSART_SYNCHRONOUS_MASTER_DISABLES_SINGLE_RECEIVE    0


/* Selecting EUSART Working Mode */
#define EUSART_SYNCHRONOUS_MODE   1
#define EUSART_ASYNCHRONOUS_MODE  0 
/* Baud Rate Generator Asynchronous Speed Mode */
#define EUSART_ASYNCHRONOYS_HIGH_SPEED 1
#define EUSART_ASYNCHRONOUS_LOW_SPEED  0
/* Baud Rate Generator Register Size */
#define EUSART_16_BIT_BAUDRATE_GEN    1
#define EUSART_08_BIT_BAUDRNTE_GEN    0

#define EUSART_MODULE_ENABLE     1
#define EUSART_MODULE_DISABLE    0

/* EUSART Transmit Enable */
#define EUSART_ASYNCHRONOUS_TX_ENABLE    5
#define EUSART_ASYNCHRONOUS_TX_DISABLE   6
/* EUSART Transmit Interrupt Enable */
#define EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE     1
#define EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE    0
/* EUSART 9-Bit Transmit Enable */
#define EUSART_ASYNCHRONOUS_9Bit_TX_ENABLE         1
#define EUSART_ASYNCHRONOUS_9Bit_TX_DISABLE        0

/* EUSART RECEIVE Enable */
#define EUSART_ASYNCHRONOUS_RX_ENABLE    7
#define EUSART_ASYNCHRONOUS_RX_DISABLE   8
/* EUSART RECEIVE Interrupt Enable */
#define EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE     1
#define EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE    0
/* EUSART 9-Bit RECEIVE Enable */
#define EUSART_ASYNCHRONOUS_9Bit_RX_ENABLE         1
#define EUSART_ASYNCHRONOUS_9Bit_RX_DISABLE        0

/* EUSART_Framing_Error */
#define EUSART_FRAMING_ERROR_DETECTED    1
#define EUSART_FRAMING_ERROR_CLEARED     0
/* EUSART Overrun Error */
#define EUSART_OVERRUN_ERROR_DETECTED   1
#define EUSART_OVERRUN_ERROR_CLEARED    0

/* section: Macro functions Declarations */
#define EUSART_SERIAL_PORT_ENABLED()                                  (RCSTAbits.SPEN = 1) 
#define EUSART_SERIAL_PORT_DISABLED()                                 (RCSTAbits.SPEN = 0) 

#define EUSART_USART_9Bit_TX_ENABLED()                                (TXSTAbits.TX9 = 1)
#define EUSART_USART_9Bit_TX_DISABLED()                               (TXSTAbits.TX9 = 0)

#define EUSART_SYNCHRONOUS_MASTER_MODE_TX_ENABLED()                   (TXSTAbits.CSRC = 1)
#define EUSART_SYNCHRONOUS_SLAVE_MODE_TX_ENABLED()                    (TXSTAbits.CSRC = 0)


#define EUSART_USART_9Bit_RX_ENABLED()                                (RCSTAbits.RX9 = 1)
#define EUSART_USART_9Bit_RX_DISABLED()                               (RCSTAbits.RX9 = 0)

#define EUSART_USART_TX_ENABLED()                                     (TXSTAbits.TXEN = 1) 
#define EUSART_USART_TX_DISABLED()                                    (TXSTAbits.TXEN = 0) 

#define EUSART_SYNCHRONOUS_MODE_ENABLED()                             (TXSTAbits.SYNC = 1)
#define EUSART_ASYNCHRONOUS_MODE_ENABLED()                            (TXSTAbits.SYNC = 0)

#define EUSART_ASYNCHRONOYS_HIGH_SPEED_ENABLED()                      (TXSTAbits.BRGH = 1)
#define EUSART_ASYNCHRONOUS_LOW_SPEED_ENABLED()                       (TXSTAbits.BRGH = 0)

#define EUSART_SYNCHRONOUS_MASTER_ENABLES_SINGLE_RECEIVE_ENABLED()    (RCSTAbits.SREN = 1)
#define EUSART_SYNCHRONOUS_MASTER_DISABLES_SINGLE_RECEIVE_ENABLED()   (RCSTAbits.SREN = 0)

#define EUSART_USART_RX_ENABLED()                                     (RCSTAbits.CREN = 1)
#define EUSART_USART_RX_DISABLED()                                    (RCSTAbits.CREN = 0)

#define EUSART_SYNCHRONOUS_ENABLED_CONTINUOUS_RECEIVE()               (RCSTAbits.CREN = 1)
#define EUSART_SYNCHRONOUS_DISABLED_CONTINUOUS_RECEIVE()              (RCSTAbits.CREN = 0)

#define EUSART_16_BIT_BAUD_RATE_GENERATOR()                           (BAUDCONbits.BRG16 = 1) 
#define EUSART_8_BIT_BAUD_RATE_GENERATOR()                            (BAUDCONbits.BRG16 = 0) 

/* section: Data type Declarations */

typedef enum{
    BAUDRATE_ASYN_8BIT_LOW_SPEED,
    BAUDRATE_ASYN_8BIT_HIGH_SPEED,
    BAUDRATE_ASYN_16BIT_LOW_SPEED,
    BAUDRATE_ASYN_16BIT_HIGH_SPEED,
    BAUDRATE_SYN_8BIT,
    BAUDRATE_SYN_16BIT
}baudrate_gen_t;
typedef struct{
    uint8 usart_tx_reserved:1;
    uint8 usart_tx_enable: 4;
    uint8 usart_tx_9bit_enable: 1;
    uint8 usart_tx_sync_master_mode:1;
    interrupt_priority_t usart_tx_priority;    
}usart_tx_cfg_t;
typedef struct {
    uint8 usart_rx_reserved: 2;
    uint8 usart_rx_enable: 4;
    uint8 usart_rx_9bit_enable: 1;
    interrupt_priority_t usart_rx_priority;
}usart_rx_cfg_t;

typedef union {
    struct {
        uint8 usart_tx_reserved:6;
        uint8 usart_ferr :1;
        uint8 usart_oerr: 1 ;
    };
    uint8 status;
}usart_error_status_t;

typedef struct {
    uint32 baudrate;
    baudrate_gen_t  baudrate_cfg;
    usart_tx_cfg_t  usart_tx_cfg;
    usart_rx_cfg_t  usart_rx_cfg;
    usart_error_status_t usart_error_status;
    void (*USART_TX_HANDLER)(void);
    void (*USART_RX_HANDLER)(void);
    void (*USART_FRAMING_ERROR_HANDLER)(void);
    void (*USART_OVERRUN_ERROR_HANDLER)(void);
}usart_t;

/* section: functions Declarations */

/**
 * @brief: function to initialize USART
 * @param usart: struct has all information about USART
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType USART_INIT(const usart_t *usart);
/**
 * @brief: function to deinitialize USART
 * @param usart: struct has all information about USART
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType USART_DEINIT(const usart_t *usart);
/**
 * @brief: function to send data by USART
 * @param usart: struct has all information about USART
 * @param value: byte you want to send
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType USART_TRANSMIT_BYTE_BLOCKING(const usart_t *usart,uint8 value );
/**
 * @brief: function to send data by USART BUT LOOP IN MAIN
 * @param usart: struct has all information about USART
 * @param value: byte you want to send
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType USART_TRANSMIT_BYTE_NOT_BLOCKING(const usart_t *usart,uint8 value );
/**
 * @brief: function to send data by USART
 * @param usart: struct has all information about USART
 * @param value: text you want to send
 * @param len: length of the text 
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType USART_TRANSMIT_STRING_BLOCKING(const usart_t *usart,uint8 *value,uint16 len);
/**
 * @brief: function to send data by USART BUT LOOP IN MAIN
 * @param usart: struct has all information about USART
 * @param value: text you want to send
 * @param len: length of the text 
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType USART_TRANSMIT_STRING_NOT_BLOCKING(const usart_t *usart,uint8 *value,uint16 len);
/**
 * @brief: function to receive data by USART
 * @param usart: struct has all information about USART
 * @param value: byte was sent 
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType USART_RECEIVE_BYTE_BLOCKING(const usart_t *usart, uint8 *value);
/**
 * @brief: function to receive data by USART BUT LOOP IN MAIN
 * @param usart: struct has all information about USART
 * @param value: byte was sent 
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType USART_RECEIVE_BYTE_NOT_BLOCKING(const usart_t *usart, uint8 *value);
/**
 *  TX INTERRUPT SERVICE ROUTINE
 */
void USART_TX_ISR(void);
/**
 * RX INTERRUPT SERVICE ROUTINE function
 */
void USART_RX_ISR(void);

#endif	/* HAL_USART_H */

