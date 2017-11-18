/*(c) Umang Gajera - www.ocfreaks.com
 * UART init and write functions for printf()
 * http://www.ocfreaks.com/how-to-retarget-printf-using-uart-in-coocox-coide/
 * Adapted from:
 * http://www.ocfreaks.com/lpc1343-uart-programming-tutorial/
 * More Embedded stuff @ http://www.ocfreaks.com/cat/embedded/
 * License : GPL */

#include <stdio.h>
#include "lpc13xx.h"
#include "uart.h"

#define THRE        (1<<5) /*Transmit Holding Register Empty*/
#define MULVAL      1
#define DIVADDVAL   0
#define Ux_FIFO_EN  (1<<0)
#define Rx_FIFO_RST (1<<1)
#define Tx_FIFO_RST (1<<2)
#define DLAB_BIT    (1<<7)


void initUART(void) /*Sets up UART @ 115200 baud rate using UART_PCLK=72Mhz*/
{
	/*Assuming CCLK=72Mhz!*/

	/*UART CLOCK Enable Sequence Step 1 - Select TXD,RXD functions*/
	LPC_IOCON->PIO1_6 = 0x1; //Select RXD for PIO1_6
	LPC_IOCON->PIO1_7 = 0x1; //Select RXD for PIO2_6

	/*UART CLOCK Enable Sequence Step 2 - Set Divider & Enable Clock*/
	LPC_SYSCON->UARTCLKDIV = 1; //Set Divider by 1, so UART_PCLK=CCLK
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<12);//Enable UART clock

	LPC_UART->LCR = 3 | DLAB_BIT ; /* 8 bits, no Parity, 1 Stop bit & DLAB set to 1  */
	LPC_UART->DLL = 39;
	LPC_UART->DLM = 0;

	LPC_UART->FCR |= Ux_FIFO_EN | Rx_FIFO_RST | Tx_FIFO_RST;
	LPC_UART->FDR = (MULVAL<<4) | DIVADDVAL; /* MULVAL=15(bits - 7:4) , DIVADDVAL=2(bits - 3:0)  */
	LPC_UART->LCR &= ~(DLAB_BIT);
	/*Now since we have applied DLL and DLM we now lock or freeze those values by disabling DLAB i.e DLAB=0
	Baud= ~115200. Now we can perform UART communication!*/
}

void uartWrite(char cChar) //Send a single character, called by PrintChar() defined in printf.c
{
	while ( !(LPC_UART->LSR & THRE) ); // wait till the THR is empty
	// now we can write to the queue
	LPC_UART->THR = cChar;
}
