/* 
 * File:   mcal_external_interrupt.h
 * Author: imena
 *
 * Created on January 3, 2024, 8:45 PM
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H

/* section: Includes */
#include "mcal_interrupt_config.h"

/* section: Macro Declarations */
#define EXTERNAL_INTERRUPT_ENABLE  1
#define EXTERNAL_INTERRUPT_DISABLE 0

#define EXTERNAL_INTx_INTERRUPT_FEATURE_ENABLED      EXTERNAL_INTERRUPT_ENABLE
#define EXTERNAL_INTERRUPT_ONCHANGE_FEATURE_ENABLED  EXTERNAL_INTERRUPT_ENABLE

/* section: Macro functions Declarations */
#if EXTERNAL_INTx_INTERRUPT_FEATURE_ENABLED == EXTERNAL_INTERRUPT_ENABLE
#define EXT_INT0_INTERRUPT_ENABLED()      (INTCONbits.INT0E=1)
#define EXT_INT0_INTERRUPT_DISABLED()     (INTCONbits.INT0E=0)
#define EXT_INT0_INTERRUPT_FLAG_CLEAR()   (INTCONbits.INT0F=0)
#define EXT_INT0_INTERRUPT_RISING_EDGE()  (INTCON2bits.INTEDG0=1)
#define EXT_INT0_INTERRUPT_FAILING_EDGE() (INTCON2bits.INTEDG0=0)

#define EXT_INT1_INTERRUPT_ENABLED()      (INTCON3bits.INT1E=1)
#define EXT_INT1_INTERRUPT_DISABLED()     (INTCON3bits.INT1E=0)
#define EXT_INT1_INTERRUPT_FLAG_CLEAR()   (INTCON3bits.INT1F=0)
#define EXT_INT1_INTERRUPT_RISING_EDGE()  (INTCON2bits.INTEDG1=1)
#define EXT_INT1_INTERRUPT_FAILING_EDGE() (INTCON2bits.INTEDG1=0)

#define EXT_INT2_INTERRUPT_ENABLED()      (INTCON3bits.INT2E=1)
#define EXT_INT2_INTERRUPT_DISABLED()     (INTCON3bits.INT2E=0)
#define EXT_INT2_INTERRUPT_FLAG_CLEAR()   (INTCON3bits.INT2F=0)
#define EXT_INT2_INTERRUPT_RISING_EDGE()  (INTCON2bits.INTEDG2=1)
#define EXT_INT2_INTERRUPT_FAILING_EDGE() (INTCON2bits.INTEDG2=0)

#if INTERRUPT_PRIORITY_FEATURE_ENABLED == INTERRUPT_PRIORITY_ENABLED

#define EXT_INT1_INTERRUPT_HIGH_PRIORITY() (INTCON3bits.INT1IP=1)
#define EXT_INT1_INTERRUPT_LOW_PRIORITY()  (INTCON3bits.INT1IP=0)

#define EXT_INT2_INTERRUPT_HIGH_PRIORITY() (INTCON3bits.INT2IP=1)
#define EXT_INT2_INTERRUPT_LOW_PRIORITY()  (INTCON3bits.INT2IP=0)

#endif
#endif

#if EXTERNAL_INTERRUPT_ONCHANGE_FEATURE_ENABLED == INTERRUPT_PRIORITY_ENABLED
#define EXT_RBx_INTERRUPT_ENABLED()      (INTCONbits.RBIE=1)
#define EXT_RBx_INTERRUPT_DISABLED()     (INTCONbits.RBIE=0)
#define EXT_RBx_INTERRUPT_FLAG_CLEAR()   (INTCONbits.RBIF=0)
#define EXT_RBx_INTERRUPT_PULL_UP_ENABLED()   (INTCON2bits.RBPU= 0)
#define EXT_RBx_INTERRUPT_PULL_UP_DISABLED()  (INTCON2bits.RBPU= 1)


#if INTERRUPT_PRIORITY_FEATURE_ENABLED == INTERRUPT_PRIORITY_ENABLED
#define EXT_RBx_INTERRUPT_HIGH_PRIORITY() (INTCON2bits.RBIP=1)
#define EXT_RBx_INTERRUPT_LOW_PRIORITY()  (INTCON2bits.RBIP=0)
#endif
#endif

/* section: Data type Declarations */
typedef enum{
    INTERRUPT_FALLING_EDGE,
    INTERRUPT_RISING_EDGE,
}interrupt_intx_edge_t;

typedef enum{
    INTERRUPT_INT0, 
    INTERRUPT_INT1,  
    INTERRUPT_INT2,          
}interrupt_intx_src_t;

typedef enum{
    INTERRUPT_RB4, 
    INTERRUPT_RB5,  
    INTERRUPT_RB6,
    INTERRUPT_RB7,                      
}interrupt_rbx_src_t;

typedef struct{
    void(*EXT_INTX_INTERRUPT_HANDLER)(void);
    Pin_config_t external_int_config;
#if INTERRUPT_PRIORITY_FEATURE_ENABLED == INTERRUPT_PRIORITY_ENABLED    
    interrupt_priority_t external_int_priority;
#endif    
    interrupt_intx_edge_t external_int_edge;
    interrupt_intx_src_t external_int_source;
}intx_interrupt_t;

typedef struct{
    void(*EXT_RBX_INTERRUPT_HANDLER_RISING_EDGE)(void);
    void(*EXT_RBX_INTERRUPT_HANDLER_FAILING_EDGE)(void);
    Pin_config_t external_rb_config;
#if INTERRUPT_PRIORITY_FEATURE_ENABLED == INTERRUPT_PRIORITY_ENABLED    
    interrupt_priority_t external_rb_priority;   
#endif    
    interrupt_rbx_src_t external_rb_source;
}rbx_interrupt_t;

/* section: functions Declarations */

Std_ReturnType INTx_INTERRUPT_INITIALIZATION    (const intx_interrupt_t  *intx_object);
Std_ReturnType INTx_INTERRUPT_DEINITIALIZATION  (const intx_interrupt_t  *intx_object);
Std_ReturnType RBx_INTERRUPT_INITIALIZATION     (const rbx_interrupt_t   *rbx_object);
Std_ReturnType RBx_INTERRUPT_DEINITIALIZATION   (const rbx_interrupt_t   *rbx_object);
#endif	/* MCAL_EXTERNAL_INTERRUPT_H */

