/*----------------------------------------------------------------------------
   	[File Name]:    <uart.h>

  	[Author]:       <AHMED KHALED>

 	[DATA CREATED]: <1/4/2021>

    [Description]:  <the header file for uart>
 ------------------------------------------------------------------------------*/
#ifndef UART_H_
#define UART_H_

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"

#define M2_READY 0x10

typedef enum
{
	FIVE_BITS, SIX_BITS, SEVEN_BITS, EIGHT_BITS
}Bit_Data_Type;

typedef enum
{
	DISABLED, RESERVED, EVEN, ODD
}Parity_Bit_Mode;

typedef enum
{
	ONE_BIT, TWO_BIT
}Stop_Bits;


typedef struct
{
	Parity_Bit_Mode PBM;     // PBM: Parity Bit Mode
	Stop_Bits SB;		     // SB: Stop Bits
	Bit_Data_Type NODB;      // NODB: Number of Data Bits
	uint32 BAUD_RATE;        // BR: Baud Rate
}UART_ConfigStruct;



void UART_Init(const UART_ConfigStruct * ptr_config);
void SEND_DATA_UART(volatile const uint8 a_DATA);
uint8 RECEIVE_DATA_UART(void);
void SEND_STRING_UART(const uint8 *STR);
void RECEIVE_STRING_UART(uint8 *Str);


#endif /* UART_H_ */
