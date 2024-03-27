/* 
 * File:   ecu_seven_seg.h
 * Author: imina
 *
 * Created on December 10, 2023, 7:44 PM
 */

#ifndef ECU_SEVEN_SEG_H
#define	ECU_SEVEN_SEG_H

/* section: Includes */

#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* section: Macro Declarations */

/* section: Macro functions Declarations */

/* section: Data type Declarations */

typedef enum {
    SEGEMENT_COMMON_ANODE,
    SEGEMENT_COMMON_CATHODE,            
}segement_type_t;

typedef struct{
    Pin_config_t segemet_pins[4];
    segement_type_t segement_type;
}segement_t;
/* section: functions Declarations */

/**
 * @brief: function to initialize the 7-segment
 * @param segement : the struct which has all info about the pins
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType seven_segement_initialize(const segement_t *segement);
/**
 * @brief: function to write specific number on seven-segment
 * @param segement: the struct which has all info about the pins
 * @param num: the number which the user want to display  
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType seven_segement_write_number (const segement_t *segement,uint8 num);


#endif	/* ECU_SEVEN_SEG_H */

