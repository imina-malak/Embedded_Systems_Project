/* 
 * File:   ecu_chr_lcd.h
 * Author: imina
 *
 * Created on December 18, 2023, 7:05 PM
 */

#ifndef ECU_CHR_LCD_H
#define	ECU_CHR_LCD_H

/* section: Includes */

#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* section: Macro Declarations */

#define LCD_CLEAR                                0x01
#define LCD_CURSOR_HOME                          0x02
#define LCD_DECREMENT_ENTRY_MODE                 0x04
#define LCD_INCREMENT_ENTRY_MODE                 0x06
#define LCD_DISPLAY_OFF_CURSOR_OFF               0x08
#define LCD_DISPLAY_ON_CURSOR_OFF                0x0C
#define LCD_DISPLAY_ON_CURSOR_ON_BLINK_OFF       0x0E
#define LCD_DISPLAY_ON_CURSOR_ON_BLINK_ON        0x0F
#define LCD_SHIFT_DISPLAY_ON_RIGHT_SHIFT         0x1C
#define LCD_SHIFT_DISPLAY_ON_LEFT_SHIFT          0x18
#define LCD_FUNCTION_4BIT_2LINE                  0x28
#define LCD_FUNCTION_8BIT_2LINE                  0x38
#define CGRAM_START                              0X40
#define DDRAM_START                              0X80

/* section: Macro functions Declarations */

/* section: Data type Declarations */
typedef struct{
    Pin_config_t lcd_rs;
    Pin_config_t lcd_en;
    Pin_config_t lcd_config[4];     
}chr_lcd_4bit_t;

typedef struct{
    Pin_config_t lcd_rs;
    Pin_config_t lcd_en;
    Pin_config_t lcd_config[8];     
}chr_lcd_8bit_t;

/* section: functions Declarations */

/**
 * @brief function to initialize the 4-bit character lcd
 * @param lcd :the struct which has all info about the pin
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType lcd_4bit_initialize(const chr_lcd_4bit_t *lcd);
/**
 * @brief function to send command in the 4-bit character lcd
 * @param lcd :the struct which has all info about the pin
 * @param command: selected command to write 
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType lcd_4bit_send_command(const chr_lcd_4bit_t *lcd, uint8 command);

/**
 * @brief function to send character in the 4-bit character lcd
 * @param lcd :the struct which has all info about the pin
 * @param data: character you want to display
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType lcd_4bit_send_char_data(const chr_lcd_4bit_t *lcd, uint8 data);
/**
 * @brief function to send character in specific position in the 4-bit character lcd
 * @param lcd :the struct which has all info about the pin
 * @param row : the row you want to display on 
 * @param column: the column you want to display on 
 * @param data : character you want to display
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType lcd_4bit_send_data_char_position(const chr_lcd_4bit_t *lcd,uint8 row, uint8 column ,uint8 data);
/**
 * @brief function to send string in the 4-bit character lcd
 * @param lcd :the struct which has all info about the pin
 * @param string : string you want to display
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType lcd_4bit_send_string_data(const chr_lcd_4bit_t *lcd, uint8 *string);
/**
 * @brief function to send string in specific position the 4-bit character lcd
 * @param lcd :the struct which has all info about the pin
 * @param row : the row you want to display on 
 * @param column: the column you want to display on 
 * @param data : string you want to display
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType lcd_4bit_send_data_string_position(const chr_lcd_4bit_t *lcd,uint8 row, uint8 column ,uint8 *string);
/**
 * @brief function to send custom character in the 4-bit character lcd
 * @param lcd :the struct which has all info about the pin
 * @param row : the row you want to display on 
 * @param column: the column you want to display on 
 * @param c_chr: the list which form the custom character 
 * @param mempos: memory position 
 * @return 
 */
Std_ReturnType lcd_4bit_send_data_costum_position(const chr_lcd_4bit_t *lcd,uint8 row, uint8 column ,uint8 c_chr[],uint8 mempos);

/**
 * @brief function to initialize the 8-bit character lcd
 * @param lcd :the struct which has all info about the pin
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType lcd_8bit_initialize(const chr_lcd_8bit_t *lcd);
/**
 * @brief function to send command in the 8-bit character lcd
 * @param lcd :the struct which has all info about the pin
 * @param command: selected command to write 
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType lcd_8bit_send_command(const chr_lcd_8bit_t *lcd, uint8 command);
/**
 * @brief function to send character in the 8-bit character lcd
 * @param lcd :the struct which has all info about the pin
 * @param data: character you want to display
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType lcd_8bit_send_char_data(const chr_lcd_8bit_t *lcd, uint8 data);
/**
 * @brief function to send character in specific position in the 8-bit character lcd
 * @param lcd :the struct which has all info about the pin
 * @param row : the row you want to display on 
 * @param column: the column you want to display on 
 * @param data : character you want to display
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType lcd_8bit_send_data_char_position(const chr_lcd_8bit_t *lcd,uint8 row, uint8 column ,uint8 data);
/**
 * @brief function to send string in the 8-bit character lcd
 * @param lcd :the struct which has all info about the pin
 * @param string : string you want to display
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType lcd_8bit_send_string_data(const chr_lcd_8bit_t *lcd, uint8 *string);
/**
 * @brief function to send string in specific position the 8-bit character lcd
 * @param lcd :the struct which has all info about the pin
 * @param row : the row you want to display on 
 * @param column: the column you want to display on 
 * @param data : string you want to display
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType lcd_8bit_send_data_string_position(const chr_lcd_8bit_t *lcd,uint8 row, uint8 column ,uint8 *string);
/**
 * @brief function to send custom character in the 8-bit character lcd
 * @param lcd :the struct which has all info about the pin
 * @param row : the row you want to display on 
 * @param column: the column you want to display on 
 * @param c_chr: the list which form the custom character 
 * @param mempos: memory position 
 * @return 
 */
Std_ReturnType lcd_8bit_send_data_costum_position(const chr_lcd_8bit_t *lcd,uint8 row, uint8 column ,uint8 c_chr[],uint8 mempos);



/**
 * @brief : function to byte short to string to display it 
 * @param value: byte value that you want to convert 
 * @param string : pointer to array that you want to display 
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */ 
Std_ReturnType convert_byte_to_string(uint8 value,uint8 *string);
/**
 * @brief : function to convert short to string to display it 
 * @param value: short value that you want to convert 
 * @param string : pointer to array that you want to display 
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */ 
Std_ReturnType convert_short_to_string(uint16 value,uint8 *string);
/**
 * @brief : function to convert int to string to display it 
 * @param value: int value that you want to convert 
 * @param string : pointer to array that you want to display 
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */ 
Std_ReturnType convert_int_to_string(uint32 value,uint8 *string);


#endif	/* ECU_CHR_LCD_H */

