/* 
 * File:   ecu_dc_motor.h
 * Author: imina
 *
 * Created on December 5, 2023, 2:26 PM
 */

#ifndef ECU_DC_MOTOR_H
#define	ECU_DC_MOTOR_H

/* section: Includes */
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* section: Macro Declarations */
#define DC_MOTOR_ON_STATUS  0X01
#define DC_MOTOR_OFF_STATUS 0X00
/* section: Macro functions Declarations */

/* section: Data type Declarations */

typedef struct{
    Pin_config_t dc_motor_config[2];
}dc_motor_t;

/* section: functions Declarations */
/**
 * @brief: function to initialize DC_motor
 * @param: led: the struct which has all info about the pin
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType dc_motor_initialize(const dc_motor_t *motor);
/**
 * @brief: function to turn DC_motor right
 * @param: led: the struct which has all info about the pin
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType dc_motor_turn_right(const dc_motor_t *motor);
/**
 * @brief: function to turn DC_motor left
 * @param: led: the struct which has all info about the pin
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType dc_motor_turn_left(const dc_motor_t *motor);
/**
 * @brief: function to stop DC_motor
 * @param: led: the struct which has all info about the pin
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType dc_motor_turn_off(const dc_motor_t *motor);

#endif	/* ECU_DC_MOTOR_H */

