 /*----------------------------------------------------------------------------
   	[File Name]:    <MC1.h>

  	[Author]:       <AHMED KHALED>

 	[DATA CREATED]: <1/4/2021>

    [Description]:  <the header file for MC1>
 ------------------------------------------------------------------------------*/

#ifndef MC1_H_
#define MC1_H_

/*----------------------------------------------------------------------------------
                                 INCLUDES
 -----------------------------------------------------------------------------------*/
#define F_CPU 8000000UL
#include "uart.h"
#include "timer.h"
#include "keypad.h"
#include "lcd.h"



/*-----------------------------------------------------------------------------------
                            preprocessor macros
 ------------------------------------------------------------------------------------*/

#define MATCHED 0x01
#define UNMATCHED 0x00
#define LOGIN 0x11
#define CHANGE 0x22
#define NEW 0x33
#define Baud_Rate 9600
/*------------------------------------------------------------------------------------
                              FUNCTION prototypes
 -------------------------------------------------------------------------------------*/

void enter(void);
void signin(void);
void pass_config(void);
void begin(void);
void close(void);

#endif /* MC1_H_ */
