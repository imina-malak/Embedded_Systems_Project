/* 
 * File:   ecu_chr_lcd.h
 * Author: imina
 *
 * Created on December 18, 2023, 7:05 PM
 */

#include "ecu_chr_lcd.h"

/**
 * @brief function to write command or data in 4-bit character lcd 
 * @param lcd :the struct which has all info about the pin
 * @param command: selected command to write 
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform
 */
static Std_ReturnType lcd_send_4bits(const chr_lcd_4bit_t *lcd, uint8 command_data);
/**
 * @brief function to enable signal to send data or command 
 * @param lcd :the struct which has all info about the pin
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
static Std_ReturnType lcd_4bits_enable_signal(const chr_lcd_4bit_t *lcd);

/**
 * @brief function to enable signal to send data or command 
 * @param lcd :the struct which has all info about the pin
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
static Std_ReturnType lcd_8bits_enable_signal(const chr_lcd_8bit_t *lcd);
/**
 * @brief function to set cursor position to start saving data 
 * @param lcd :the struct which has all info about the pin
 * @param row : the row you want to display on 
 * @param column: the column you want to display on 
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
static Std_ReturnType lcd_8bits_set_cursor(const chr_lcd_8bit_t *lcd,uint8 row,uint8 column);
/**
 * @brief
 * @param lcd
 * @param row
 * @param column
 * @return 
 */
static Std_ReturnType lcd_4bits_set_cursor(const chr_lcd_4bit_t *lcd,uint8 row,uint8 column);



/**
 * @brief function to initialize the 4-bit character lcd
 * @param lcd :the struct which has all info about the pin
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType lcd_4bit_initialize(const chr_lcd_4bit_t *lcd){
    Std_ReturnType ret = E_OK;
    if ((NULL == lcd)){
        ret = E_NOT_OK;
    }else
    {   
        ret = gpio_pin_initialize(&(lcd->lcd_en));
        ret = gpio_pin_initialize(&(lcd->lcd_rs));
        for(uint8 c =0;c<4;c++){
            ret=gpio_pin_initialize(&(lcd->lcd_config[c]));
        }
        __delay_ms(20);
        ret = lcd_4bit_send_command(lcd,LCD_FUNCTION_8BIT_2LINE);
        __delay_ms(5);
        ret = lcd_4bit_send_command(lcd,LCD_FUNCTION_8BIT_2LINE);     
        __delay_us(150);
        ret = lcd_4bit_send_command(lcd,LCD_FUNCTION_8BIT_2LINE);  
        ret = lcd_4bit_send_command(lcd,LCD_CLEAR);  
        ret = lcd_4bit_send_command(lcd,LCD_CURSOR_HOME);  
        ret = lcd_4bit_send_command(lcd,LCD_INCREMENT_ENTRY_MODE);  
        ret = lcd_4bit_send_command(lcd,LCD_DISPLAY_ON_CURSOR_OFF);  
        ret = lcd_4bit_send_command(lcd,LCD_FUNCTION_4BIT_2LINE);  
        ret = lcd_4bit_send_command(lcd,0x80); 
    }
    return ret;
}

/**
 * @brief function to send command in the 4-bit character lcd
 * @param lcd :the struct which has all info about the pin
 * @param command: selected command to write 
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType lcd_4bit_send_command(const chr_lcd_4bit_t *lcd, uint8 command){
    Std_ReturnType ret = E_OK;
    if ((NULL == lcd)){
        ret = E_NOT_OK;
    }else
    {
        ret = gpio_pin_write_logic(&(lcd->lcd_rs),LOW);
        ret = lcd_send_4bits((lcd),(command>>4));
        ret = lcd_4bits_enable_signal((lcd));
        ret = lcd_send_4bits((lcd),command);
        ret = lcd_4bits_enable_signal((lcd));
    }
    return ret;    
}
/**
 * @brief function to send character in the 4-bit character lcd
 * @param lcd :the struct which has all info about the pin
 * @param data: character you want to display
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType lcd_4bit_send_char_data(const chr_lcd_4bit_t *lcd, uint8 data){
    Std_ReturnType ret = E_OK;
    if ((NULL == lcd)){
        ret = E_NOT_OK;
    }else
    {
        ret = gpio_pin_write_logic(&(lcd->lcd_rs),HIGH);
        ret = lcd_send_4bits((lcd),data>>4);
        ret = lcd_4bits_enable_signal((lcd));
        ret = lcd_send_4bits((lcd),data);
        ret = lcd_4bits_enable_signal((lcd));
    }
    return ret;    
}
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
Std_ReturnType lcd_4bit_send_data_char_position(const chr_lcd_4bit_t *lcd,uint8 row, uint8 column ,uint8 data){
    Std_ReturnType ret = E_OK;
    if ((NULL == lcd)){
        ret = E_NOT_OK;
    }else
    {    
        ret = lcd_4bits_set_cursor(lcd,row,column);
        ret = lcd_4bit_send_char_data(lcd,data);
    }
    return ret;    
}
/**
 * @brief function to send string in the 4-bit character lcd
 * @param lcd :the struct which has all info about the pin
 * @param string : string you want to display
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType lcd_4bit_send_string_data(const chr_lcd_4bit_t *lcd, uint8 *string){
    Std_ReturnType ret = E_OK;
    if ((NULL == lcd)||(NULL == string)){
        ret = E_NOT_OK;
    }else
    {    
        while(*string){
            ret=lcd_4bit_send_char_data(lcd,*string++);
        }
    }
    return ret;    
}
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
Std_ReturnType lcd_4bit_send_data_string_position(const chr_lcd_4bit_t *lcd,uint8 row, uint8 column ,uint8 *string){
    Std_ReturnType ret = E_OK;
    if ((NULL == lcd)||(NULL == string)){
        ret = E_NOT_OK;
    }else
    {    
        ret = lcd_4bits_set_cursor(lcd,row,column);
        ret= lcd_4bit_send_string_data(lcd,string);
    }
    return ret;    
}
/**
 * @brief function to send custom character in the 4-bit character lcd
 * @param lcd :the struct which has all info about the pin
 * @param row : the row you want to display on 
 * @param column: the column you want to display on 
 * @param c_chr: the list which form the custom character 
 * @param mempos: memory position 
 * @return 
 */
Std_ReturnType lcd_4bit_send_data_costum_position(const chr_lcd_4bit_t *lcd,uint8 row, uint8 column ,uint8 c_chr[],uint8 mempos){
    Std_ReturnType ret = E_OK;
    if ((NULL == lcd)){
        ret = E_NOT_OK;
    }else
    {    
        lcd_4bit_send_command(lcd,(CGRAM_START +(mempos*8)));
        for(uint8 i=0;i<8;i++){
            lcd_4bit_send_char_data(lcd,c_chr[i]);
        }
        lcd_4bit_send_data_char_position(lcd,row,column,mempos);        
    }
    return ret;    
}

/**
 * @brief function to initialize the 8-bit character lcd
 * @param lcd :the struct which has all info about the pin
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType lcd_8bit_initialize(const chr_lcd_8bit_t *lcd){
    Std_ReturnType ret = E_OK;
    if ((NULL == lcd)){
        ret = E_NOT_OK;
    }else
    {   ret = gpio_pin_initialize(&(lcd->lcd_en));
        ret = gpio_pin_initialize(&(lcd->lcd_rs));
        for(uint8 c =0;c<8;c++){
            ret=gpio_pin_initialize(&(lcd->lcd_config[c]));
        }      
        __delay_ms(20);
        ret = lcd_8bit_send_command(lcd,LCD_FUNCTION_8BIT_2LINE);
        __delay_ms(5);
        ret = lcd_8bit_send_command(lcd,LCD_FUNCTION_8BIT_2LINE);
        __delay_us(150);
        ret = lcd_8bit_send_command(lcd,LCD_FUNCTION_8BIT_2LINE);
        ret = lcd_8bit_send_command(lcd,LCD_CLEAR);
        ret = lcd_8bit_send_command(lcd,LCD_CURSOR_HOME);
        ret = lcd_8bit_send_command(lcd,LCD_INCREMENT_ENTRY_MODE);
        ret = lcd_8bit_send_command(lcd,LCD_DISPLAY_ON_CURSOR_OFF);
        ret = lcd_8bit_send_command(lcd,LCD_FUNCTION_8BIT_2LINE);
        ret = lcd_8bit_send_command(lcd,DDRAM_START);
    }
    return ret;    
}

/**
 * @brief function to send command in the 8-bit character lcd
 * @param lcd :the struct which has all info about the pin
 * @param command: selected command to write 
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType lcd_8bit_send_command(const chr_lcd_8bit_t *lcd, uint8 command){
    Std_ReturnType ret = E_OK;
    if (NULL == lcd){
        ret = E_NOT_OK;
    }else
    {    
        ret = gpio_pin_write_logic(&(lcd->lcd_rs),LOW);
        for(uint8 i=0; i<8 ;i++){
            ret = gpio_pin_write_logic(&(lcd->lcd_config[i]),( (command>>i)&(uint8)0x01 ));
        }
        ret = lcd_8bits_enable_signal((lcd));
    }
    return ret;    
}

/**
 * @brief function to send character in the 8-bit character lcd
 * @param lcd :the struct which has all info about the pin
 * @param data: character you want to display
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType lcd_8bit_send_char_data(const chr_lcd_8bit_t *lcd, uint8 data){
    Std_ReturnType ret = E_OK;
    if ((NULL == lcd)){
        ret = E_NOT_OK;
    }else
    {    
        ret = gpio_pin_write_logic(&(lcd->lcd_rs),HIGH);
        for(uint8 i=0; i<8 ;i++){
            ret = gpio_pin_write_logic(&(lcd->lcd_config[i]),( (data>>i)& (uint8)0x01 ));
        }
        ret = lcd_8bits_enable_signal((lcd));
    }
    return ret;    
}

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
Std_ReturnType lcd_8bit_send_data_char_position(const chr_lcd_8bit_t *lcd,uint8 row, uint8 column ,uint8 data){
    Std_ReturnType ret = E_OK;
    if ((NULL == lcd)){
        ret = E_NOT_OK;
    }else
    {    
        ret = lcd_8bits_set_cursor(lcd,row,column);
        ret = lcd_8bit_send_char_data(lcd,data);
    }
    return ret;    
}

/**
 * @brief function to send string in the 8-bit character lcd
 * @param lcd :the struct which has all info about the pin
 * @param string : string you want to display
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
Std_ReturnType lcd_8bit_send_string_data(const chr_lcd_8bit_t *lcd, uint8 *string){
    Std_ReturnType ret = E_OK;
    if ((NULL == lcd)||(NULL==string)){
        ret = E_NOT_OK;
    }else
    {    
        while(*string){
            ret=lcd_8bit_send_char_data(lcd,*string++);
        }
    }
    return ret;    
}
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
Std_ReturnType lcd_8bit_send_data_string_position(const chr_lcd_8bit_t *lcd,uint8 row, uint8 column ,uint8 *string){
    Std_ReturnType ret = E_OK;
    if ((NULL == lcd)||(NULL==string)){
        ret = E_NOT_OK;
    }else
    {
        ret = lcd_8bits_set_cursor(lcd,row,column);
        lcd_8bit_send_string_data(lcd,string);
    }
    return ret;    
}
/**
 * @brief function to send custom character in specific position in the 8-bit character lcd
 * @param lcd :the struct which has all info about the pin
 * @param row : the row you want to display on 
 * @param column: the column you want to display on 
 * @param c_chr: the list which form the custom character 
 * @param mempos: memory position 
 * @return 
 */
Std_ReturnType lcd_8bit_send_data_costum_position(const chr_lcd_8bit_t *lcd,uint8 row, uint8 column ,uint8 c_chr[],uint8 mempos){
    Std_ReturnType ret = E_OK;
    if ((NULL == lcd)){
        ret = E_NOT_OK;
    }else
    {    
        lcd_8bit_send_command(lcd,(CGRAM_START +(mempos*8)));
        for(uint8 i=0;i<8;i++){
            lcd_8bit_send_char_data(lcd,c_chr[i]);
        }
        lcd_8bit_send_data_char_position(lcd,row,column,mempos);
    }
    return ret;    
}


/**
 * @brief : function to byte short to string to display it 
 * @param value: byte value that you want to convert 
 * @param string : pointer to array that you want to display 
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */ 
Std_ReturnType convert_byte_to_string(uint8 value,uint8 *string){
    Std_ReturnType ret = E_OK;
    uint8 counter=0;
    uint8 temp_string[4]={0};
    if ((NULL == string)){
        ret = E_NOT_OK;
    }else
    {
        memset(string,' ',3*sizeof(uint8));
        string[3]='\0';
        sprintf((char*)temp_string,"%i",value);
        while(temp_string[counter]!='\0'){
            string[counter] = temp_string[counter];
            counter++;
        }
        
    } 
    return ret;        
}


/**
 * @brief : function to convert short to string to display it 
 * @param value: short value that you want to convert 
 * @param string : pointer to array that you want to display 
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */ 
Std_ReturnType convert_short_to_string(uint16 value,uint8 *string){
    Std_ReturnType ret = E_OK;
    uint8 counter=0;
    uint8 temp_string[6]={0};
    if ((NULL == string)){
        ret = E_NOT_OK;
    }else
    {
        memset(string,' ',5*sizeof(uint8));
        string[5]='\0';
        sprintf((char*)temp_string,"%i",value);
        while(temp_string[counter]!='\0'){
            string[counter] = temp_string[counter];
            counter++;
        }
        
    } 
    return ret;         
}

/**
 * @brief : function to convert int to string to display it 
 * @param value: int value that you want to convert 
 * @param string : pointer to array that you want to display 
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */ 
Std_ReturnType convert_int_to_string(uint32 value,uint8 *string){
    Std_ReturnType ret = E_OK;
    uint8 counter=0;
    uint8 temp_string[11]={0};
    if ((NULL == string)){
        ret = E_NOT_OK;
    }else
    {
        memset(string,' ',10*sizeof(uint8));
        string[10]='\0';
        sprintf((char*)temp_string,"%i",value);
        while(temp_string[counter]!='\0'){
            string[counter] = temp_string[counter];
            counter++;
        }
        
    } 
    return ret;        
}


/**
 * @brief function to write command or data in 4-bit character lcd 
 * @param lcd :the struct which has all info about the pin
 * @param command: selected command to write 
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform
 */
static Std_ReturnType lcd_send_4bits(const chr_lcd_4bit_t *lcd, uint8 command_data){
    Std_ReturnType ret = E_OK;
    if ((NULL == lcd)){
        ret = E_NOT_OK;
    }else
    {
        ret = gpio_pin_write_logic(&(lcd->lcd_config[0]),( (command_data>>0)& (uint8)0x01 ));
        ret = gpio_pin_write_logic(&(lcd->lcd_config[1]),( (command_data>>1)& (uint8)0x01 ));
        ret = gpio_pin_write_logic(&(lcd->lcd_config[2]),( (command_data>>2)& (uint8)0x01 ));
        ret = gpio_pin_write_logic(&(lcd->lcd_config[3]),( (command_data>>3)& (uint8)0x01 ));   
    }
    return ret;     
}


/**
 * @brief function to enable signal to send data or command 
 * @param lcd :the struct which has all info about the pin
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
static Std_ReturnType lcd_4bits_enable_signal(const chr_lcd_4bit_t *lcd){
    Std_ReturnType ret = E_OK;
    if ((NULL == lcd)){
        ret = E_NOT_OK;
    }else
    {
        ret = gpio_pin_write_logic(&(lcd->lcd_en),HIGH);
        __delay_us(5);
        ret = gpio_pin_write_logic(&(lcd->lcd_en),LOW);
    }
    return ret;     
    
}

/**
 * @brief function to enable signal to send data or command 
 * @param lcd :the struct which has all info about the pin
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
static Std_ReturnType lcd_8bits_enable_signal(const chr_lcd_8bit_t *lcd){
    Std_ReturnType ret = E_OK;
    if ((NULL == lcd)){
        ret = E_NOT_OK;
    }else
    {
        ret = gpio_pin_write_logic(&(lcd->lcd_en),HIGH);
        __delay_us(5);
        ret = gpio_pin_write_logic(&(lcd->lcd_en),LOW);
    }
    return ret;     
}
/**
 * @brief function to set cursor position to start saving data 
 * @param lcd :the struct which has all info about the pin
 * @param row : the row you want to display on 
 * @param column: the column you want to display on 
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
static Std_ReturnType lcd_8bits_set_cursor(const chr_lcd_8bit_t *lcd,uint8 row,uint8 column){
    Std_ReturnType ret = E_OK;
    column--;    
    if ((NULL == lcd)){
        ret = E_NOT_OK;
    }else
    {
        switch (row){
            case 1: ret= lcd_8bit_send_command(lcd,(0x80 + column ));break;
            case 2: ret= lcd_8bit_send_command(lcd,(0xc0 + column ));break;
            case 3: ret= lcd_8bit_send_command(lcd,(0x94 + column ));break;
            case 4: ret= lcd_8bit_send_command(lcd,(0xd4 + column ));break;
        }
    }
    return ret;     
}

/**
 * @brief function to set cursor position to start saving data 
 * @param lcd :the struct which has all info about the pin
 * @param row : the row you want to display on 
 * @param column: the column you want to display on 
 * @return the status of the function 
 *            (E_OK):     the function done successfully 
 *            (E_NOT_OK): the function has issue to perform 
 */
static Std_ReturnType lcd_4bits_set_cursor(const chr_lcd_4bit_t *lcd,uint8 row,uint8 column){
    Std_ReturnType ret = E_OK;
    column--;    
    if ((NULL == lcd)){
        ret = E_NOT_OK;
    }else
    {
        switch (row){
            case 1: ret= lcd_4bit_send_command(lcd,(0x80 + column ));break;
            case 2: ret= lcd_4bit_send_command(lcd,(0xc0 + column ));break;
            case 3: ret= lcd_4bit_send_command(lcd,(0x94 + column ));break;
            case 4: ret= lcd_4bit_send_command(lcd,(0xd4 + column ));break;
        }
    }
    return ret;      
}