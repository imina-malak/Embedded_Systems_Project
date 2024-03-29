/* 
 * File:   ecu_led.h
 * Author: imina
 *
 * Created on November 9, 2023, 4:32 PM
 */

#ifndef ECU_LED_H
#define	ECU_LED_H

/* section: Includes */

#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* section: Macro Declarations */

/* section: Macro functions Declarations */

/* section: Data type Declarations */
typedef enum{
    LED_OFF, 
    LED_ON
}led_status_t;

typedef struct{
    Pin_config_t led_config;
    uint8 led_status:1;            // determine the led status  (@led_status_t)
}led_t;
/* section: functions Declarations */
/**
 * @brief: function to initialize led
 * @param: led: the struct which has all info about the pin
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType led_initialize(const led_t *led);
/**
 * @brief: function to turn on led
 * @param: led: pointer to led
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType led_turn_on(const led_t *led);
/**
 * @brief: function to turn off led
 * @param: led: the struct which has all info about the pin
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType led_turn_off(const led_t *led);
/**
 * @brief: function to toggle led
 * @param: led: the struct which has all info about the pin
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType led_turn_toggle(const led_t *led);
#endif	/* ECU_LED_H */

