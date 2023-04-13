 /*----------------------------------------------------------------------------
   	[File Name]:    <MC2.h>

  	[Author]:       <AHMED KHALED>

 	[DATA CREATED]: <1/4/2021>

    [Description]:  <the header file for MC2>
 ------------------------------------------------------------------------------*/
#ifndef MC2_H_
#define MC2_H_

/*----------------------------------------------------------------------------------
                                 INCLUDES
 -----------------------------------------------------------------------------------*/
#define F_CPU 8000000UL
#include "micro_config.h"
#include "common_macros.h"
#include "timer.h"
#include "external_eeprom.h"
#include "UART.h"
#include "std_types.h"
#include "i2c.h"

/*-----------------------------------------------------------------------------------
                            preprocessor macros
 ------------------------------------------------------------------------------------*/

#define READY 0x10
#define MATCHED 0x01
#define UNMATCHED 0x00
#define LOGIN 0x11
#define CHANGE 0x22
#define NEW 0x33
#define Baud_Rate 9600
/*------------------------------------------------------------------------------------
                              FUNCTION prototypes
 -------------------------------------------------------------------------------------*/

void matched(void);
void unmatched(void);
void recievepass(void);
void checkpass(void);
void login (void);
void Motorstop(void);
void Motorstart(void);
void buzzerstart(void);
void buzzerstop(void);
void motortoggle(void);
void motorreverse(void);

#endif /* MC2_H_ */
