/* 
 * File:   hal_gpio.c
 * Author: imina
 *
 * Created on November 9, 2023, 3:25 PM
 */

#include "hal_gpio.h"

volatile uint8 *tris_register[]={&TRISA,&TRISB,&TRISC,&TRISD,&TRISE};
volatile uint8 *lat_register[]={&LATA,&LATB,&LATC,&LATD,&LATE};
volatile uint8 *port_register[]={&PORTA,&PORTB,&PORTC,&PORTD,&PORTE};

/**
 * @brief:   function to initialize the direction and logic of the pin for the first time  
 * @param:   (_Pin_config): the struct which has all info about the pin
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
#if  GPIO_PORT_PIN_CONFIGRATION == CONFIG_ENABLE 
Std_ReturnType gpio_pin_initialize(const Pin_config_t *_Pin_config){
    Std_ReturnType ret = E_OK;
    if (NULL ==_Pin_config){
        ret = E_NOT_OK;
    }else
    {
        gpio_pin_direction_initialize(_Pin_config);
        gpio_pin_write_logic(_Pin_config,_Pin_config->logic);
    }
    return ret;
}
#endif

/**
 * @brief:  function to initialize the direction of the pin only 
 * @param:  (_Pin_config):pointer to struct which has all info about the pin 
 * @return: return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
#if  GPIO_PORT_PIN_CONFIGRATION == CONFIG_ENABLE 
Std_ReturnType gpio_pin_direction_initialize(const Pin_config_t *_Pin_config){
    Std_ReturnType ret = E_OK;
    if ((NULL ==_Pin_config) || (_Pin_config->Pin > PIN_MAX_NUMBER-1) ){
        ret = E_NOT_OK;
    }else
    {
        switch (_Pin_config->direction){
                case OUTPUT:
                    CLEAR_BIT(*tris_register[_Pin_config->port],_Pin_config->Pin);
                    break;
                case INPUT:
                    SET_BIT(*tris_register[_Pin_config->port],_Pin_config->Pin);
                    break;
                default: ret = E_NOT_OK;
        }
    }
    return ret;
}
#endif

/**
 * @brief:  function to get the direction of the pin and save it in pointer
 * @param:  (_Pin_config): the struct which has all info about the pin
 * @param:  (_Direction_status): pointer to save the direction status 
 * @return: return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
#if  GPIO_PORT_PIN_CONFIGRATION == CONFIG_ENABLE 
Std_ReturnType gpio_pin_get_direction_status(const Pin_config_t *_Pin_config,Direction_t *_Direction_status){
    Std_ReturnType ret = E_OK;
    if ((NULL ==_Pin_config) ||(NULL == _Direction_status)|| (_Pin_config->Pin > PIN_MAX_NUMBER-1)){
        ret = E_NOT_OK;
    }else
    {
        *_Direction_status=READ_BIT(*tris_register[_Pin_config->port],_Pin_config->Pin);
    }
    return ret;
}
#endif


/**
 * @brief:   function takes the logic of the user and write it 
 * @param:  (_Pin_config):pointer to struct which has all info about the pin 
 * @param:  (_Logic): variable to take the logic 
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
#if  GPIO_PORT_PIN_CONFIGRATION == CONFIG_ENABLE 
Std_ReturnType gpio_pin_write_logic(const Pin_config_t *_Pin_config,Logic_t _Logic){
    Std_ReturnType ret = E_OK;
    if ((NULL ==_Pin_config)){
        ret = E_NOT_OK;
    }else
    {
        switch (_Logic){
            case LOW:
                CLEAR_BIT(*lat_register[_Pin_config->port],_Pin_config->Pin);
                break;
            case HIGH:
                SET_BIT(*lat_register[_Pin_config->port],_Pin_config->Pin);
                break;
            default: ret = E_NOT_OK;
        }
    }
    
    return ret;
}
#endif


/**
 * @brief:  function read the logic and give it to the user
 * @param:  (_Pin_config):pointer to struct which has all info about the pin 
 * @param:  (_Logic): pointer to save the logic 
 * @return: return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
#if  GPIO_PORT_PIN_CONFIGRATION == CONFIG_ENABLE 
Std_ReturnType gpio_pin_read_logic(const Pin_config_t *_Pin_config,Logic_t *_Logic){
    Std_ReturnType ret = E_OK;
    if ((NULL ==_Pin_config) ||(NULL ==  _Logic)){
        ret = E_NOT_OK;
    }else
    {
        *_Logic = READ_BIT(*port_register[_Pin_config->port],_Pin_config->Pin);
    }
    
    return ret;
}
#endif


/**
 * @brief:   function to toggle logic 
 * @param:   (_Pin_config):pointer to struct which has all info about the pin 
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
#if  GPIO_PORT_PIN_CONFIGRATION == CONFIG_ENABLE 
Std_ReturnType gpio_pin_toggle_logic(const Pin_config_t *_Pin_config){
    Std_ReturnType ret = E_OK;
    if ((NULL ==_Pin_config)){
        ret = E_NOT_OK;
    }else
    {
        TOGGLE_BIT(*lat_register[_Pin_config->port],_Pin_config->Pin);
    }
    return ret;
}
#endif


/**
 * @brief function to initialize direction and logic of all pins in the port 
 * @param port: input the number of the port
 * @param _direction: (_direction): the number which can represent the directions of the pins
 * @param _Logic: (_Logic): logic to write in the pins
 * @return 
 */
Std_ReturnType gpio_port_initialize(const Port_index_t port, uint8 _direction,uint8 _Logic) {
    Std_ReturnType ret = E_OK;
    if(port > PORT_MAX_NUMBER-1){
        ret= E_NOT_OK;
    }else{
        gpio_port_direction_initialize(port,_direction);
        gpio_port_write_logic(port,_Logic);
    }
      
}


/**
 * @brief: initialize the port(all pins) inside with the value from the user  
 * @param:  (port): input the number of the port
 * @param:  (_direction): the number which can represent the directions of the pins 
 * @return: return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
#if  GPIO_PORT_CONFIGRATION == CONFIG_ENABLE 
Std_ReturnType gpio_port_direction_initialize(const Port_index_t port, uint8 _direction){
    Std_ReturnType ret = E_OK;
    if(port > PORT_MAX_NUMBER-1){
        ret = E_NOT_OK;
    }
    else
    {
        *tris_register[port]=_direction;
    }
    return ret;
}
#endif

/**
 * @brief: function to read directions of all pins only 
 * @param: (port): input the number of the port
 * @param: (direction_status): pointer can hold the data inside the port 
 * @return 
 */
#if  GPIO_PORT_CONFIGRATION == CONFIG_ENABLE 
Std_ReturnType gpio_port_get_direction_status(const Port_index_t port, uint8 *direction_status ){
    Std_ReturnType ret = E_OK;
    if ((NULL == direction_status)&&(port > PORT_MAX_NUMBER-1)){
        ret = E_NOT_OK;
    }else
    {
        *direction_status= *tris_register[port];
    }
    return ret;
}
#endif

/**
 * @brief: function to write in all pins all at once  
 * @param: (port)  :number of the port 
 * @param: (_Logic): logic to write in the pins 
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
#if  GPIO_PORT_CONFIGRATION == CONFIG_ENABLE 
Std_ReturnType gpio_port_write_logic(const Port_index_t port,uint8 _Logic){
    Std_ReturnType ret = E_OK;
    if (port > PORT_MAX_NUMBER-1){
        ret = E_NOT_OK;
    }else
    {
        *lat_register[port]=_Logic;
    }
    

    return ret;
}
#endif

/**
 * @brief:   function to read in all pins all at once 
 * @param:   (port)  :number of the port 
 * @param:   (_Logic): pointer to save the logic of the pins 
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
#if  GPIO_PORT_CONFIGRATION == CONFIG_ENABLE 
Std_ReturnType gpio_port_read_logic(const Port_index_t port,uint8 *_Logic){
    Std_ReturnType ret = E_OK;
    if ((NULL ==_Logic)&&(port > PORT_MAX_NUMBER-1)){
        ret = E_NOT_OK;
    }else
    {
        *_Logic=*lat_register[port];
    }
    
    return ret;
}
#endif

/**
 * @brief:   function to toggle all the logic pins 
 * @param:   (port)  :number of the port 
 * @return:  return the status of the function 
 *              (E_OK):     the function done successfully 
 *              (E_NOT_OK): the function has issue to perform 
 */
#if  GPIO_PORT_CONFIGRATION == CONFIG_ENABLE 
Std_ReturnType gpio_port_toggle_logic(const Port_index_t port){
    Std_ReturnType ret = E_OK;
    if (port > PORT_MAX_NUMBER-1){
        ret = E_NOT_OK;
    }else
    {
        *lat_register[port] = *lat_register[port] ^ PORT_MASK; ;
    }

    return ret;
}
#endif
