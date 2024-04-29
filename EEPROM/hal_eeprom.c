/* 
 * File:   hal_eeprom.c
 * Author: imina
 *
 * Created on January 14, 2024, 9:10 PM
 */
#include "hal_eeprom.h"

/**
 * 
 * @param address :the address to read data from  
 * @param data: any data you want save
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType EEPROM_READ_BYTE   (uint16 address , uint8 *data){
    Std_ReturnType ret = E_OK;
    EEADRH = (uint8)((address>>8) & 0x03);
    EEADR =  (uint8)((address) & 0xff);
    EECON1bits.EEPGD=ACCESS_DATA_EEPROM_MEMORY; 
    EECON1bits.CFGS=ACCESS_FLASH_EEPROM_MEMORY;      
    EECON1bits.RD=INITIATE_READ;
    NOP();
    NOP();
    *data=EEDATA;
    return ret;
}
/**
 * 
 * @param address :the address to write data
 * @param data: any data you want save
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType EEPROM_WRITE_BYTE  (uint16 address , uint8 data){
    Std_ReturnType ret = E_OK;
    if (NULL == data){
        ret = E_NOT_OK;
    }else
    {
    uint8 Global_interrupt_status = INTCONbits.GIE;
    EEADRH = (uint8)((address>>8) & 0x03);
    EEADR = (uint8)((address) & 0xff);
    EEDATA = data;
    EECON1bits.EEPGD=ACCESS_DATA_EEPROM_MEMORY; 
    EECON1bits.CFGS=ACCESS_FLASH_EEPROM_MEMORY;    
    EECON1bits.WREN=ALLOWS_WRITES_CYCLES;        
    INTCONbits.GIE = 0;
    EECON2 = 0X55;
    EECON2 = 0XAA;
    EECON1bits.WR =INITIATE_WRITES;
    while(EECON1bits.WR);
    EECON1bits.WREN=INHBITS_WRITES_CYCLES;        
    INTCONbits.GIE = Global_interrupt_status; 
    }
    return ret;  
}
 
