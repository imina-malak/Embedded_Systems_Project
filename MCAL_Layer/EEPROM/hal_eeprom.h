/* 
 * File:   hal_eeprom.h
 * Author: imina
 *
 * Created on January 14, 2024, 9:10 PM
 */

#ifndef HAL_EEPROM_H
#define	HAL_EEPROM_H

/* section: Includes */
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../INTERRUPTS/mcal_internal_interrupt.h"
/* section: Macro Declarations */
#define ACCESS_FLASH_PROGRAM_MEMORY  1
#define ACCESS_DATA_EEPROM_MEMORY    0

#define ACCESS_CONFIGIRATION_REGISTER 1
#define ACCESS_FLASH_EEPROM_MEMORY 0

#define ALLOWS_WRITES_CYCLES   1
#define INHBITS_WRITES_CYCLES  0

#define INITIATE_WRITES  1
#define INITIATE_READ    1

/* section: Macro functions Declarations */

/* section: Data type Declarations */

/* section: functions Declarations */
/**
 * 
 * @param address :the address to read data from  
 * @param data: any data you want save
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType EEPROM_READ_BYTE  (uint16 address , uint8 *data);
/**
 * 
 * @param address :the address to write data
 * @param data: any data you want save
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType EEPROM_WRITE_BYTE (uint16 address , uint8 data);
 

#endif	/* HAL_EEPROM_H */

