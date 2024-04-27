/* 
 * File:   mcal_interrupt_manager.h
 * Author: imena
 *
 * Created on January 3, 2024, 8:45 PM
 */

#include "mcal_interrupt_manager.h"

static volatile uint8 rb4_flag = 1,rb5_flag = 1,rb6_flag = 1,rb7_flag = 1;


#if INTERRUPT_PRIORITY_FEATURE_ENABLED == INTERRUPT_PRIORITY_ENABLED

void __interrupt() Interrupt_High (void){
    if( (INTERRUPT_ENABLED == INTCONbits.INT0IE )&&(INTERRUPT_OCCURED ==INTCONbits.INT0IF ) ){
        INT0_ISR();}
    else if( (INTERRUPT_ENABLED == INTCON3bits.INT1E)&&(INTERRUPT_OCCURED ==INTCON3bits.INT1F) ){
        INT1_ISR();}   
    else if( (INTERRUPT_ENABLED == INTCON3bits.INT2IE )&&(INTERRUPT_OCCURED ==INTCON3bits.INT2IF ) ){
        INT2_ISR();}
    
    else if( (INTERRUPT_ENABLED == INTCONbits.RBIE )&&(INTERRUPT_OCCURED ==INTCONbits.RBIF) && (PORTBbits.RB4 == HIGH)  &&(rb4_flag == HIGH) ){
        rb4_flag = 0;
        RB4_ISR(HIGH);}
    else if( (INTERRUPT_ENABLED == INTCONbits.RBIE )&&(INTERRUPT_OCCURED == INTCONbits.RBIF) && (PORTBbits.RB4 == LOW) &&(rb4_flag == LOW) ) {
        rb4_flag = 1;
        RB4_ISR(LOW);}
    else if( (INTERRUPT_ENABLED == INTCONbits.RBIE )&&(INTERRUPT_OCCURED ==INTCONbits.RBIF) && (PORTBbits.RB5 == HIGH)  &&(rb5_flag == HIGH) ){
        rb5_flag = 0;
        RB5_ISR(HIGH);}
    else if( (INTERRUPT_ENABLED == INTCONbits.RBIE )&&(INTERRUPT_OCCURED == INTCONbits.RBIF) && (PORTBbits.RB5 == LOW) &&(rb5_flag == LOW) ){
        rb5_flag = 1;
        RB5_ISR(LOW);}
    else if( (INTERRUPT_ENABLED == INTCONbits.RBIE )&&(INTERRUPT_OCCURED ==INTCONbits.RBIF) && (PORTBbits.RB6 == HIGH)  &&(rb6_flag == HIGH) ){
        rb6_flag = 0;
        RB6_ISR(HIGH);}
    else if( (INTERRUPT_ENABLED == INTCONbits.RBIE )&&(INTERRUPT_OCCURED == INTCONbits.RBIF) && (PORTBbits.RB6 == LOW) &&(rb6_flag == LOW) ) {
        rb6_flag = 1;
        RB6_ISR(LOW);}
    else if( (INTERRUPT_ENABLED == INTCONbits.RBIE )&&(INTERRUPT_OCCURED ==INTCONbits.RBIF) && (PORTBbits.RB7 == HIGH)  &&(rb7_flag == HIGH) ){
        rb7_flag = 0;
        RB7_ISR(HIGH);}
    else if( (INTERRUPT_ENABLED == INTCONbits.RBIE )&&(INTERRUPT_OCCURED == INTCONbits.RBIF) && (PORTBbits.RB7 == LOW) &&(rb7_flag == LOW) ){
        rb7_flag = 1;
        RB7_ISR(LOW);}
    
    
    else if( (INTERRUPT_ENABLED == PIE1bits.ADIE )&& (INTERRUPT_OCCURED == PIR1bits.ADIF )){
        ADC_ISR();  }       
    
    else if( (INTERRUPT_ENABLED == INTCONbits.TMR0IE)&& (INTERRUPT_OCCURED == INTCONbits.TMR0IF )){
        TIMER0_ISR();  }       
    else if( (INTERRUPT_ENABLED == PIE1bits.TMR1IE)&& (INTERRUPT_OCCURED == PIR1bits.TMR1IF  )){
        TIMER1_ISR();  }  

    else if( (INTERRUPT_ENABLED == PIE1bits.TMR2IE)&& (INTERRUPT_OCCURED == PIR1bits.TMR2IF  )){
        TIMER2_ISR();  }   
    
    else if( (INTERRUPT_ENABLED == PIE2bits.TMR3IE)&& (INTERRUPT_OCCURED == PIR2bits.TMR3IF  )){
        TIMER3_ISR();  }  
    
    else if( (INTERRUPT_ENABLED == PIE1bits.CCP1IE)&& (INTERRUPT_OCCURED == PIR1bits.CCP1IF )){
        CCP1_ISR();  }       
    
    else if( (INTERRUPT_ENABLED == PIE2bits.CCP2IE)&& (INTERRUPT_OCCURED == PIR2bits.CCP2IF )){
        CCP2_ISR();  }   

    else if( (INTERRUPT_ENABLED == PIE1bits.TXIE)&& (INTERRUPT_OCCURED == PIR1bits.TXIF)){
        USART_TX_ISR();  } 
    
    else if( (INTERRUPT_ENABLED == PIE1bits.RCIE)&& (INTERRUPT_OCCURED == PIR1bits.RCIF )){
        USART_RX_ISR();  }  

    else if( (INTERRUPT_ENABLED == PIE1bits.SSPIE)&& (INTERRUPT_OCCURED == PIR1bits.SSPIF )){
        SPI_ISR();  } 

    
    else{}
}
void __interrupt(low_priority) Interrupt_Low (void){
    if( (INTERRUPT_ENABLED == INTCONbits.INT0IE )&&(INTERRUPT_OCCURED ==INTCONbits.INT0IF ) ){
        INT0_ISR();}
    else if( (INTERRUPT_ENABLED == INTCON3bits.INT1E)&&(INTERRUPT_OCCURED ==INTCON3bits.INT1F) ){
        INT1_ISR();}   
    else if( (INTERRUPT_ENABLED == INTCON3bits.INT2IE )&&(INTERRUPT_OCCURED ==INTCON3bits.INT2IF ) ){
        INT2_ISR();}
    
    else if( (INTERRUPT_ENABLED == INTCONbits.RBIE )&&(INTERRUPT_OCCURED ==INTCONbits.RBIF) && (PORTBbits.RB4 == HIGH)  &&(rb4_flag == HIGH) ){
        rb4_flag = 0;
        RB4_ISR(HIGH);}
    else if( (INTERRUPT_ENABLED == INTCONbits.RBIE )&&(INTERRUPT_OCCURED == INTCONbits.RBIF) && (PORTBbits.RB4 == LOW) &&(rb4_flag == LOW) ) {
        rb4_flag = 1;
        RB4_ISR(LOW);}
    else if( (INTERRUPT_ENABLED == INTCONbits.RBIE )&&(INTERRUPT_OCCURED ==INTCONbits.RBIF) && (PORTBbits.RB5 == HIGH)  &&(rb5_flag == HIGH) ){
        rb5_flag = 0;
        RB5_ISR(HIGH);}
    else if( (INTERRUPT_ENABLED == INTCONbits.RBIE )&&(INTERRUPT_OCCURED == INTCONbits.RBIF) && (PORTBbits.RB5 == LOW) &&(rb5_flag == LOW) ){
        rb5_flag = 1;
        RB5_ISR(LOW);}
    else if( (INTERRUPT_ENABLED == INTCONbits.RBIE )&&(INTERRUPT_OCCURED ==INTCONbits.RBIF) && (PORTBbits.RB6 == HIGH)  &&(rb6_flag == HIGH) ){
        rb6_flag = 0;
        RB6_ISR(HIGH);}
    else if( (INTERRUPT_ENABLED == INTCONbits.RBIE )&&(INTERRUPT_OCCURED == INTCONbits.RBIF) && (PORTBbits.RB6 == LOW) &&(rb6_flag == LOW) ) {
        rb6_flag = 1;
        RB6_ISR(LOW);}
    else if( (INTERRUPT_ENABLED == INTCONbits.RBIE )&&(INTERRUPT_OCCURED ==INTCONbits.RBIF) && (PORTBbits.RB7 == HIGH)  &&(rb7_flag == HIGH) ){
        rb7_flag = 0;
        RB7_ISR(HIGH);}
    else if( (INTERRUPT_ENABLED == INTCONbits.RBIE )&&(INTERRUPT_OCCURED == INTCONbits.RBIF) && (PORTBbits.RB7 == LOW) &&(rb7_flag == LOW) ){
        rb7_flag = 1;
        RB7_ISR(LOW);}

    else if( (INTERRUPT_ENABLED == PIE1bits.ADIE )&& (INTERRUPT_OCCURED == PIR1bits.ADIF )){
        ADC_ISR();  }     
    
    else if( (INTERRUPT_ENABLED == INTCONbits.TMR0IE)&& (INTERRUPT_OCCURED == INTCONbits.TMR0IF )){
        TIMER0_ISR();  }       
    else if( (INTERRUPT_ENABLED == PIE1bits.TMR1IE)&& (INTERRUPT_OCCURED == PIR1bits.TMR1IF  )){
        TIMER1_ISR();  }  

    else if( (INTERRUPT_ENABLED == PIE1bits.TMR2IE)&& (INTERRUPT_OCCURED == PIR1bits.TMR2IF  )){
        TIMER2_ISR();  }   
    
    else if( (INTERRUPT_ENABLED == PIE2bits.TMR3IE)&& (INTERRUPT_OCCURED == PIR2bits.TMR3IF  )){
        TIMER3_ISR();  }
    
    else if( (INTERRUPT_ENABLED == PIE1bits.CCP1IE)&& (INTERRUPT_OCCURED == PIR1bits.CCP1IF )){
        CCP1_ISR();  }       
    
    else if( (INTERRUPT_ENABLED == PIE2bits.CCP2IE)&& (INTERRUPT_OCCURED == PIR2bits.CCP2IF )){
        CCP2_ISR();  } 
    
    
    else if( (INTERRUPT_ENABLED == PIE1bits.TXIE)&& (INTERRUPT_OCCURED == PIR1bits.TXIF)){
        USART_TX_ISR();  } 
    
    else if( (INTERRUPT_ENABLED == PIE1bits.RCIE)&& (INTERRUPT_OCCURED == PIR1bits.RCIF )){
        USART_RX_ISR();  }  

    else if( (INTERRUPT_ENABLED == PIE1bits.SSPIE)&& (INTERRUPT_OCCURED == PIR1bits.SSPIF )){
        SPI_ISR();  } 
    
    else{}
}

#else
void __interrupt() Interrupt0 (void){
    
    if( (INTERRUPT_ENABLED == INTCONbits.INT0IE )&&(INTERRUPT_OCCURED ==INTCONbits.INT0IF ) ){
        INT0_ISR();}
    else if( (INTERRUPT_ENABLED == INTCON3bits.INT1E)&&(INTERRUPT_OCCURED ==INTCON3bits.INT1F) ){
        INT1_ISR();}
    else if( (INTERRUPT_ENABLED == INTCON3bits.INT2IE )&&(INTERRUPT_OCCURED ==INTCON3bits.INT2IF ) ){
        INT2_ISR();}
        
    else if( (INTERRUPT_ENABLED == INTCONbits.RBIE )&&(INTERRUPT_OCCURED ==INTCONbits.RBIF) && (PORTBbits.RB4 == HIGH)  &&(rb4_flag == HIGH) ){
        rb4_flag = 0;
        RB4_ISR(HIGH);}
    else if( (INTERRUPT_ENABLED == INTCONbits.RBIE )&&(INTERRUPT_OCCURED == INTCONbits.RBIF) && (PORTBbits.RB4 == LOW) &&(rb4_flag == LOW) ) {
        rb4_flag = 1;
        RB4_ISR(LOW);}
    else if( (INTERRUPT_ENABLED == INTCONbits.RBIE )&&(INTERRUPT_OCCURED ==INTCONbits.RBIF) && (PORTBbits.RB5 == HIGH)  &&(rb5_flag == HIGH) ){
        rb5_flag = 0;
        RB5_ISR(HIGH);}
    else if( (INTERRUPT_ENABLED == INTCONbits.RBIE )&&(INTERRUPT_OCCURED == INTCONbits.RBIF) && (PORTBbits.RB5 == LOW) &&(rb5_flag == LOW) ){
        rb5_flag = 1;
        RB5_ISR(LOW);}
    else if( (INTERRUPT_ENABLED == INTCONbits.RBIE )&&(INTERRUPT_OCCURED ==INTCONbits.RBIF) && (PORTBbits.RB6 == HIGH)  &&(rb6_flag == HIGH) ){
        rb6_flag = 0;
        RB6_ISR(HIGH);}
    else if( (INTERRUPT_ENABLED == INTCONbits.RBIE )&&(INTERRUPT_OCCURED == INTCONbits.RBIF) && (PORTBbits.RB6 == LOW) &&(rb6_flag == LOW) ) {
        rb6_flag = 1;
        RB6_ISR(LOW);}
    else if( (INTERRUPT_ENABLED == INTCONbits.RBIE )&&(INTERRUPT_OCCURED ==INTCONbits.RBIF) && (PORTBbits.RB7 == HIGH)  &&(rb7_flag == HIGH) ){
        rb7_flag = 0;
        RB7_ISR(HIGH);}
    else if( (INTERRUPT_ENABLED == INTCONbits.RBIE )&&(INTERRUPT_OCCURED == INTCONbits.RBIF) && (PORTBbits.RB7 == LOW) &&(rb7_flag == LOW) ){
        rb7_flag = 1;
        RB7_ISR(LOW);  }       

    
    
    else if( (INTERRUPT_ENABLED == PIE1bits.ADIE )&& (INTERRUPT_OCCURED == PIR1bits.ADIF )){
        ADC_ISR();  }      

    else if( (INTERRUPT_ENABLED == INTCONbits.TMR0IE)&& (INTERRUPT_OCCURED == INTCONbits.TMR0IF )){
        TIMER0_ISR();  }     

    else if( (INTERRUPT_ENABLED == PIE1bits.TMR1IE)&& (INTERRUPT_OCCURED == PIR1bits.TMR1IF  )){
        TIMER1_ISR();  }  

    else if( (INTERRUPT_ENABLED == PIE1bits.TMR2IE)&& (INTERRUPT_OCCURED == PIR1bits.TMR2IF  )){
        TIMER2_ISR();  }   
    
    else if( (INTERRUPT_ENABLED == PIE2bits.TMR3IE)&& (INTERRUPT_OCCURED == PIR2bits.TMR3IF  )){
        TIMER3_ISR();  }     
    
    
    else if( (INTERRUPT_ENABLED == PIE1bits.CCP1IE)&& (INTERRUPT_OCCURED == PIR1bits.CCP1IF )){
        CCP1_ISR();  }       
    
    else if( (INTERRUPT_ENABLED == PIE2bits.CCP2IE)&& (INTERRUPT_OCCURED == PIR2bits.CCP2IF )){
        CCP2_ISR();  }   

    else if( (INTERRUPT_ENABLED == PIE1bits.TXIE)&& (INTERRUPT_OCCURED == PIR1bits.TXIF)){
        USART_TX_ISR();  } 
    
    else if( (INTERRUPT_ENABLED == PIE1bits.RCIE)&& (INTERRUPT_OCCURED == PIR1bits.RCIF )){
        USART_RX_ISR();  }     

    else if( (INTERRUPT_ENABLED == PIE1bits.SSPIE)&& (INTERRUPT_OCCURED == PIR1bits.SSPIF )){
        SPI_ISR();  } 
    
    else if( (INTERRUPT_ENABLED == PIE1bits.SSPIE)&& (INTERRUPT_OCCURED == PIR1bits.SSPIF )){
        MSSP_I2C_ISR();  }     
    
    else if( (INTERRUPT_ENABLED == PIE2bits.BCLIE)&& (INTERRUPT_OCCURED == PIR2bits.BCLIF )){
        BUS_COLI_ISR();  }     
    else{}

}

#endif