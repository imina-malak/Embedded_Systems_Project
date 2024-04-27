/* 
 * File:   mcal_interrupt_manager.h
 * Author: imena
 *
 * Created on January 3, 2024, 8:46 PM
 */

#ifndef MCAL_INTERRUPT_MANAGER_H
#define	MCAL_INTERRUPT_MANAGER_H


/* section: Includes */
#include "mcal_interrupt_config.h"


/* section: Macro Declarations */

/* section: Macro functions Declarations */

/* section: Data type Declarations */

/* section: functions Declarations */
void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);
void RB4_ISR(uint8 value);
void RB5_ISR(uint8 value);
void RB6_ISR(uint8 value);
void RB7_ISR(uint8 value);

void ADC_ISR(void);
void TIMER0_ISR(void);
void TIMER1_ISR(void);
void TIMER2_ISR(void);
void TIMER3_ISR(void);
void CCP1_ISR(void);
void CCP2_ISR(void);
void USART_TX_ISR(void);
void USART_RX_ISR(void);
void SPI_ISR(void);
void MSSP_I2C_ISR(void);
void BUS_COLI_ISR(void);

#endif	/* MCAL_INTERRUPT_MANAGER_H */

