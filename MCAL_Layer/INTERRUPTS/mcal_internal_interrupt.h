/* 
 * File:   mcal_internal_interrupt.h
 * Author: imena
 *
 * Created on January 3, 2024, 8:45 PM
 */

#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H


/* section: Includes */
#include "mcal_interrupt_config.h"

/* section: Macro Declarations */
#define ADC_INTERRUPT_FEATURE_ENABLED   0x01
#define ADC_INTERRUPT_FEATURE_DISABLED  0x00

#define TIMER0_INTERRUPT_FEATURE_ENABLED   0x01
#define TIMER0_INTERRUPT_FEATURE_DISABLED  0x00

#define TIMER1_INTERRUPT_FEATURE_ENABLED   0x01
#define TIMER1_INTERRUPT_FEATURE_DISABLED  0x00

#define TIMER2_INTERRUPT_FEATURE_ENABLED   0x01
#define TIMER2_INTERRUPT_FEATURE_DISABLED  0x00

#define TIMER3_INTERRUPT_FEATURE_ENABLED   0x01
#define TIMER3_INTERRUPT_FEATURE_DISABLED  0x00

#define CCP1_INTERRUPT_FEATURE_ENABLED   0x01
#define CCP1_INTERRUPT_FEATURE_DISABLED  0x00

#define CCP2_INTERRUPT_FEATURE_ENABLED   0x01
#define CCP2_INTERRUPT_FEATURE_DISABLED  0x00

#define USART_RX_INTERRUPT_FEATURE_ENABLED   0x01
#define USART_RX_INTERRUPT_FEATURE_DISABLED  0x00

#define USART_TX_INTERRUPT_FEATURE_ENABLED   0x01
#define USART_TX_INTERRUPT_FEATURE_DISABLED  0x00


#define I2C_INTERRUPT_FEATURE_ENABLED        0x01
#define I2C_INTERRUPT_FEATURE_DISABLED       0x00


#define ADC_INTERRUPT_ENABLE_     ADC_INTERRUPT_FEATURE_ENABLED
#define TIMER0_INTERRUPT_ENABLE_  TIMER0_INTERRUPT_FEATURE_ENABLED
#define TIMER1_INTERRUPT_ENABLE_  TIMER1_INTERRUPT_FEATURE_ENABLED
#define TIMER2_INTERRUPT_ENABLE_  TIMER2_INTERRUPT_FEATURE_ENABLED
#define TIMER3_INTERRUPT_ENABLE_  TIMER3_INTERRUPT_FEATURE_ENABLED
#define CCP1_INTERRUPT_ENABLE_    CCP1_INTERRUPT_FEATURE_ENABLED
#define CCP2_INTERRUPT_ENABLE_    CCP2_INTERRUPT_FEATURE_ENABLED
#define USART_RX_INTERRUPT_ENABLE_    USART_RX_INTERRUPT_FEATURE_ENABLED
#define USART_TX_INTERRUPT_ENABLE_    USART_TX_INTERRUPT_FEATURE_ENABLED
#define I2C_INTERRUPT_ENABLE_         I2C_INTERRUPT_FEATURE_ENABLED


/* section: Macro functions Declarations */

#if ADC_INTERRUPT_ENABLE_ == ADC_INTERRUPT_FEATURE_ENABLED
#define ADC_INTERRUPT_ENABLE() (PIE1bits.ADIE = 1)
#define ADC_INTERRUPT_DISABLE() (PIE1bits.ADIE = 0)
#define ADC_INTERRUPT_CLEAR_FLAG() (PIR1bits.ADIF = 0)
#if INTERRUPT_PRIORITY_FEATURE_ENABLED == INTERRUPT_PRIORITY_ENABLED
#define ADC_INTERRUPT_SET_HIGH_PRIORITY() (IPR1bits.ADIP = 1)
#define ADC_INTERRUPT_SET_LOW_PRIORITY() (IPR1bits.ADIP  = 0)
#endif
#endif


#if TIMER0_INTERRUPT_ENABLE_ == TIMER0_INTERRUPT_FEATURE_ENABLED
#define TIMER0_INTERRUPT_ENABLE()  (INTCONbits.TMR0IE = 1)
#define TIMER0_INTERRUPT_DISABLE() (INTCONbits.TMR0IE = 0)
#define TIMER0_INTERRUPT_CLEAR_FLAG() (INTCONbits.TMR0IF = 0)
#if INTERRUPT_PRIORITY_FEATURE_ENABLED == INTERRUPT_PRIORITY_ENABLED
#define TIMER0_INTERRUPT_SET_HIGH_PRIORITY() (INTCON2bits.TMR0IP = 1)
#define TIMER0_INTERRUPT_SET_LOW_PRIORITY() (INTCON2bits.TMR0IP  = 0)
#endif
#endif



#if TIMER1_INTERRUPT_ENABLE_ == TIMER1_INTERRUPT_FEATURE_ENABLED
#define TIMER1_INTERRUPT_ENABLE()  (PIE1bits.TMR1IE = 1)
#define TIMER1_INTERRUPT_DISABLE() (PIE1bits.TMR1IE = 0)
#define TIMER1_INTERRUPT_CLEAR_FLAG() (PIR1bits.TMR1IF = 0)
#if INTERRUPT_PRIORITY_FEATURE_ENABLED == INTERRUPT_PRIORITY_ENABLED
#define TIMER1_INTERRUPT_SET_HIGH_PRIORITY() (IPR1bits.TMR1IP = 1)
#define TIMER1_INTERRUPT_SET_LOW_PRIORITY() (IPR1bits.TMR1IP  = 0)
#endif
#endif


#if TIMER2_INTERRUPT_ENABLE_ == TIMER2_INTERRUPT_FEATURE_ENABLED
#define TIMER2_INTERRUPT_ENABLE()  (PIE1bits.TMR2IE = 1)
#define TIMER2_INTERRUPT_DISABLE() (PIE1bits.TMR2IE = 0)
#define TIMER2_INTERRUPT_CLEAR_FLAG() (PIR1bits.TMR2IF = 0)
#if INTERRUPT_PRIORITY_FEATURE_ENABLED == INTERRUPT_PRIORITY_ENABLED
#define TIMER2_INTERRUPT_SET_HIGH_PRIORITY() (IPR1bits.TMR2IP = 1)
#define TIMER2_INTERRUPT_SET_LOW_PRIORITY() (IPR1bits.TMR2IP  = 0)
#endif
#endif



#if TIMER3_INTERRUPT_ENABLE_ == TIMER3_INTERRUPT_FEATURE_ENABLED
#define TIMER3_INTERRUPT_ENABLE()  (PIE2bits.TMR3IE = 1)
#define TIMER3_INTERRUPT_DISABLE() (PIE2bits.TMR3IE = 0)
#define TIMER3_INTERRUPT_CLEAR_FLAG() (PIR2bits.TMR3IF = 0)
#if INTERRUPT_PRIORITY_FEATURE_ENABLED == INTERRUPT_PRIORITY_ENABLED
#define TIMER3_INTERRUPT_SET_HIGH_PRIORITY() (IPR2bits.TMR3IP = 1)
#define TIMER3_INTERRUPT_SET_LOW_PRIORITY() (IPR2bits.TMR3IP  = 0)
#endif
#endif



#if CCP1_INTERRUPT_ENABLE_ == CCP1_INTERRUPT_FEATURE_ENABLED
#define CCP1_INTERRUPT_ENABLE()  (PIE1bits.CCP1IE = 1)
#define CCP1_INTERRUPT_DISABLE() (PIE1bits.CCP1IE = 0)
#define CCP1_INTERRUPT_CLEAR_FLAG() (PIR1bits.CCP1IF = 0)
#if INTERRUPT_PRIORITY_FEATURE_ENABLED == INTERRUPT_PRIORITY_ENABLED
#define CCP1_INTERRUPT_SET_HIGH_PRIORITY() (IPR1bits.CCP1IP = 1)
#define CCP1_INTERRUPT_SET_LOW_PRIORITY() (IPR1bits.CCP1IP = 0)
#endif
#endif


#if CCP2_INTERRUPT_ENABLE_ == CCP2_INTERRUPT_FEATURE_ENABLED
#define CCP2_INTERRUPT_ENABLE()  (PIE2bits.CCP2IE = 1)
#define CCP2_INTERRUPT_DISABLE() (PIE2bits.CCP2IE = 0)
#define CCP2_INTERRUPT_CLEAR_FLAG() (PIR2bits.CCP2IF = 0)
#if INTERRUPT_PRIORITY_FEATURE_ENABLED == INTERRUPT_PRIORITY_ENABLED
#define CCP2_INTERRUPT_SET_HIGH_PRIORITY() (IPR2bits.CCP2IP = 1)
#define CCP2_INTERRUPT_SET_LOW_PRIORITY() (IPR2bits.CCP2IP = 0)
#endif
#endif


#if USART_TX_INTERRUPT_ENABLE_  == USART_TX_INTERRUPT_FEATURE_ENABLED
#define USART_TX_INTERRUPT_ENABLE()  (PIE1bits.TXIE = 1)
#define USART_TX_INTERRUPT_DISABLE() (PIE1bits.TXIE = 0)
#if INTERRUPT_PRIORITY_FEATURE_ENABLED == INTERRUPT_PRIORITY_ENABLED
#define USART_TX_INTERRUPT_SET_HIGH_PRIORITY() (IPR1bits.TXIP = 1)
#define USART_TX_INTERRUPT_SET_LOW_PRIORITY()  (IPR1bits.TXIP = 0)
#endif
#endif


#if USART_RX_INTERRUPT_ENABLE_  == USART_RX_INTERRUPT_FEATURE_ENABLED
#define USART_RX_INTERRUPT_ENABLE()  (PIE1bits.RCIE = 1)
#define USART_RX_INTERRUPT_DISABLE() (PIE1bits.RCIE = 0)
#if INTERRUPT_PRIORITY_FEATURE_ENABLED == INTERRUPT_PRIORITY_ENABLED
#define USART_RX_INTERRUPT_SET_HIGH_PRIORITY() (IPR1bits.RCIP = 1)
#define USART_RX_INTERRUPT_SET_LOW_PRIORITY() (IPR1bits.RCIP = 0)
#endif
#endif



#if I2C_INTERRUPT_ENABLE_ ==  I2C_INTERRUPT_FEATURE_ENABLED
#define I2C_INTERRUPT_ENABLE()               (PIE1bits.SSPIE = 1)
#define I2C_BUS_COLI_INTERRUPT_ENABLE()      (PIE2bits.BCLIE = 1)

#define I2C_INTERRUPT_DISABLE()               (PIE1bits.SSPIE = 0)
#define I2C_BUS_COLI_INTERRUPT_DISABLE()      (PIE2bits.BCLIE = 0)

#define I2C_INTERRUPT_CLEAR_FLAG()           (PIR1bits.SSPIF = 0)
#define I2C_BUS_COLI_INTERRUPT_CLEAR_FLAG()  (PIR2bits.BCLIF = 0)

#if INTERRUPT_PRIORITY_FEATURE_ENABLED == INTERRUPT_PRIORITY_ENABLED
#define I2C_INTERRUPT_SET_HIGH_PRIORITY()          (IPR1bits.SSPIP = 1)
#define I2C_BUS_COLI_INTERRUPT_SET_HIGH_PRIORITY() (IPR2bits.BCLIP = 1)

#define I2C_INTERRUPT_SET_LOW_PRIORITY()           (IPR1bits.SSPIP = 0)
#define I2C_BUS_COLI_INTERRUPT_SET_LOW_PRIORITY()  (IPR2bits.BCLIP = 0)
#endif
#endif

/* section: Data type Declarations */

/* section: functions Declarations */


#endif	/* MCAL_INTERNAL_INTERRUPT_H */
