/* 
 * File:   std_libraries.h
 * Author: imena
 *
 * Created on November 9, 2023, 4:11 PM
 */

#ifndef STD_LIBRARIES_H
#define	STD_LIBRARIES_H

/* section: Includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* section: Macro Declarations */
#define STD_HIGH      0x01
#define STD_LOW       0x00

#define STD_ON        0x01
#define STD_OFF       0x00

#define STD_ACTIVE    0x01
#define STD_IDLE      0x00

#define E_NOT_OK      (Std_ReturnType)0X00
#define E_OK          (Std_ReturnType)0x01

#define CONFIG_ENABLE   0x01
#define CONFIG_DISABLE  0x00
/* section: Macro functions Declarations */


/* section: Data type Declarations */
typedef unsigned char  uint8;
typedef unsigned short uint16;
typedef unsigned int   uint32;
typedef signed char    sint8;
typedef signed short   sint16;
typedef signed int     sint32;
typedef uint8          Std_ReturnType;
/* section: functions Declarations */
#endif	/* STD_LIBRARIES_H */

