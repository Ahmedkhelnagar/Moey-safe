/*----------------------------------------------------------------------------
   	[File Name]:    <uart.c>

  	[Author]:       <AHMED KHALED>

 	[DATA CREATED]: <1/4/2021>

    [Description]:  <the source file for uart>
 ------------------------------------------------------------------------------*/

#include "UART.h"


void UART_Init(const UART_ConfigStruct * ptr_config)
{
	uint16 baud;
	float32 fbaud;

	/* U2X = 1 for double transmission speed */
	UCSRA = (1<<U2X);

	/************************** UCSRB Description **************************
	 * RXCIE = 0 Disable USART RX Complete Interrupt Enable
	 * TXCIE = 0 Disable USART Tx Complete Interrupt Enable
	 * UDRIE = 0 Disable USART Data Register Empty Interrupt Enable
	 * RXEN  = 1 Receiver Enable
	 * RXEN  = 1 Transmitter Enable
	 * UCSZ2 bits combined with UCSZ21:0 in the UCSRC sets the number
	   of data bits in a frame the receiver and transmitter use.
	   You can also use BIT5, BIT6, BIT7, BIT8, BIT9 for a_NUM_DATA_BITS
	 * RXB8 & TXB8 not used for 8-bit data mode
	 ***********************************************************************/
	UCSRB = (1 << RXEN) | (1 << TXEN);

	/************************** UCSRC Description **************************
	 * URSEL   = 1 The URSEL must be one when writing the UCSRC
	 * UMSEL   = 0 Asynchronous Operation, 1 synchronous Operation.
	   You can also use Synchronous and Asynchronous for a_SYNC.
	 * UPM1:0 for parity bit, You can also use DISABLE_PARITY,
	   EVEN_PARITY, ODD_PARITY for
	 * USBS    = 0 One stop bit
	 * UCSZ1:0 = 11 For 8-bit data mode
	 * UCPOL   = 0 Used with the Synchronous operation only
	 ***********************************************************************/
	UCSRC = (1 << URSEL) |  ((ptr_config -> SB) << USBS);
	UCSRC = (UCSRC & 0xCF) |(((ptr_config -> PBM) & 0x03) << 4);
	UCSRC = (UCSRC & 0xF9) |(((ptr_config -> NODB) & 0x03) << 1);

	fbaud = (F_CPU / ((ptr_config -> BAUD_RATE) * 8)) - 1;
	baud = (uint32)(fbaud + 0.5);

	UBRRL = baud;
	UBRRH = baud >> 8;
}


void SEND_DATA_UART(volatile const uint8 a_DATA){
	/* UDRE flag is set when the Tx buffer (UDR) is empty and ready for
	 * transmitting a new byte so wait until this flag is set to one */
	while (BIT_IS_CLEAR(UCSRA, UDRE)){}
	/* Put the required data in the UDR register and it also clear the UDRE flag as
	 * the UDR register is not empty now */
	UDR = a_DATA;
}

uint8 RECEIVE_DATA_UART(void){
	/* RXC flag is set when the UART receive data so wait until this
	 * flag is set to one */
	while(BIT_IS_CLEAR(UCSRA, RXC)){}
	/* Read the received data from the Rx buffer (UDR) and the RXC flag
	   will be cleared after read this data */
	return UDR;
}

void SEND_STRING_UART(const uint8 *STR){
	uint8 count = 0;
	while (STR[count] != '\0'){
		SEND_DATA_UART(STR[count]);
		count++;
	}
}

void SEND_BYTE_UART(volatile const uint8 a_DATA){
	while (BIT_IS_CLEAR(UCSRA, UDRE)){}
	UDR = a_DATA;
}

void RECEIVE_STRING_UART(uint8 *Str){
	uint8 count = 0;
	Str[count] = RECEIVE_DATA_UART();
	while(Str[count] != '\n')
	{
		count++;
		Str[count] = RECEIVE_DATA_UART();
	}
	Str[count] = '\0';
}

