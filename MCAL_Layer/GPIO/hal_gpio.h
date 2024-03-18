/* 
 * File:   hal_gpio.h
 * Author: imina
 *
 * Created on November 9, 2023, 3:51 PM
 */

#ifndef HAL_GPIO_H
#define	HAL_GPIO_H

/* section: Includes */

#include "pic18f4620.h"
#include "../mcal_std_types.h"

/* section: Macro Declarations */
#define BIT_MASK                    (uint8)1
#define PORT_MASK                   0xFF
#define PORT_MAX_NUMBER             5
#define PIN_MAX_NUMBER              8
#define GPIO_PORT_PIN_CONFIGRATION  CONFIG_ENABLE 
#define GPIO_PORT_CONFIGRATION      CONFIG_ENABLE 

/* section: Macro functions Declarations */
//To write 1 in the bit
#define SET_BIT(REG,BIT_POSN)             (REG |= (BIT_MASK<<BIT_POSN))
//To write 0 in the bit
#define CLEAR_BIT(REG,BIT_POSN)           (REG &= ~(BIT_MASK<<BIT_POSN))
//To toggle the logic in the bit
#define TOGGLE_BIT(REG,BIT_POSN)          (REG ^= (BIT_MASK<<BIT_POSN))
//To read the logic of the bit
#define READ_BIT(REG,BIT_POSN)            ((REG>>BIT_POSN)&BIT_MASK)

/* section: Data type Declarations */
typedef enum{
    LOW=0,
    HIGH
}Logic_t;
typedef enum{
    OUTPUT=0,
    INPUT
}Direction_t;
typedef enum{
    PIN0=0,
    PIN1,
    PIN2,
    PIN3,
    PIN4,
    PIN5,
    PIN6,
    PIN7
}Pin_index_t;
typedef enum{
    PORTA_INDEX=0, 
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX,
    PORTE_INDEX
}Port_index_t;
typedef struct{
    uint8 port:       3; // number of the port(0 to 4)(@Port_index_t)
    uint8 Pin:        3; // number of the port(0 to 7)(@Pin_index_t) 
    uint8 direction:  1; // determine the direction   (@Direction_t)
    uint8 logic:      1; // determine the logic       (@Logic_t)
}Pin_config_t;

/* section: functions Declarations */
#if  GPIO_PORT_PIN_CONFIGRATION == CONFIG_ENABLE 

/**
 * @brief:   function to initialize the direction and logic of the pin for the first time  
 * @param:   (_Pin_config): the struct which has all info about the pin
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType gpio_pin_initialize(const Pin_config_t *_Pin_config);
/**
 * @brief:  function to initialize the direction of the pin only 
 * @param:  (_Pin_config):pointer to struct which has all info about the pin 
 * @return: return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType gpio_pin_direction_initialize(const Pin_config_t *_Pin_config);
/**
 * @brief:  function to get the direction of the pin and save it in pointer
 * @param:  (_Pin_config): the struct which has all info about the pin
 * @param:  (_Direction_status): pointer to save the direction status 
 * @return: return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType gpio_pin_get_direction_status(const Pin_config_t *_Pin_config,Direction_t *_Direction_status);

/**
 * @brief:   function takes the logic of the user and write it 
 * @param:  (_Pin_config):pointer to struct which has all info about the pin 
 * @param:  (_Logic): variable to take the logic 
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType gpio_pin_write_logic(const Pin_config_t *_Pin_config,Logic_t _Logic);
/**
 * @brief:  function read the logic and give it to the user
 * @param:  (_Pin_config):pointer to struct which has all info about the pin 
 * @param:  (_Logic): pointer to save the logic 
 * @return: return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType gpio_pin_read_logic(const Pin_config_t *_Pin_config,Logic_t *_Logic);
/**
 * @brief:   function to toggle logic 
 * @param:   (_Pin_config):pointer to struct which has all info about the pin 
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType gpio_pin_toggle_logic(const Pin_config_t *_Pin_config);
#endif


#if  GPIO_PORT_CONFIGRATION == CONFIG_ENABLE 

/**
 * @brief function to initialize direction and logic of all pins in the port 
 * @param port: input the number of the port
 * @param _direction: (_direction): the number which can represent the directions of the pins
 * @param _Logic: (_Logic): logic to write in the pins
 * @return 
 */
Std_ReturnType gpio_port_initialize(const Port_index_t port, uint8 _direction,uint8 _Logic);
/**
 * @brief: initialize the port(all pins) inside with the value from the user  
 * @param:  (port): input the number of the port
 * @param:  (_direction): the number which can represent the directions of the pins 
 * @return: return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType gpio_port_direction_initialize(const Port_index_t port, uint8 _direction);
/**
 * @brief: function to read directions of all pins only 
 * @param: (port): input the number of the port
 * @param: (direction_status): pointer can hold the data inside the port 
 * @return 
 */
Std_ReturnType gpio_port_get_direction_status(const Port_index_t port, uint8 *direction_status );
/**
 * @brief: function to write in all pins all at once  
 * @param: (port)  :number of the port 
 * @param: (_Logic): logic to write in the pins 
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType gpio_port_write_logic(const Port_index_t port,uint8 _Logic);
/**
 * @brief:   function to read in all pins all at once 
 * @param:   (port)  :number of the port 
 * @param:   (_Logic): pointer to save the logic of the pins 
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType gpio_port_read_logic(const Port_index_t port,uint8 *_Logic);
/**
 * @brief:   function to toggle all the logic pins 
 * @param:   (port)  :number of the port 
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType gpio_port_toggle_logic(const Port_index_t port);
#endif

#endif	/* HAL_GPIO_H */