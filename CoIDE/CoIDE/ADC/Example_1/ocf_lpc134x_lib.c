/* Basic Support Library for OCFreaks LPC176x Tutorial Examples @ www.ocfreaks.com
Adapted from:
http://www.ocfreaks.com/lpc1343-uart-programming-tutorial/
http://www.ocfreaks.com/lpc1343-timer-programming-tutorial/
More Embedded stuff @ http://www.ocfreaks.com/cat/embedded/ 
*/

#include <lpc13xx.h>
#include "ocf_lpc134x_lib.h"
#include <stdio.h>

void initUART(void)
{
	/*Assuming CCLK=72Mhz!*/

	//UART CLOCK Enable Sequence Step 1 - Select TXD,RXD functions
	LPC_IOCON->PIO1_6 = 0x1; //Select RXD for PIO1_6
	LPC_IOCON->PIO1_7 = 0x1; //Select RXD for PIO2_6

	//UART CLOCK Enable Sequence Step 2 - Set Divider & Enable Clock
	LPC_SYSCON->UARTCLKDIV = 1; //Set Divider by 1, so UART_PCLK=CCLK
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<12);//Enable UART clock

	LPC_UART->LCR = 3 | DLAB_BIT ; /* 8 bits, no Parity, 1 Stop bit & DLAB set to 1  */
	LPC_UART->DLL = 39;
	LPC_UART->DLM = 0;

	LPC_UART->FCR |= Ux_FIFO_EN | Rx_FIFO_RST | Tx_FIFO_RST;
	LPC_UART->FDR = (MULVAL<<4) | DIVADDVAL; /* MULVAL=15(bits - 7:4) , DIVADDVAL=2(bits - 3:0)  */
	LPC_UART->LCR &= ~(DLAB_BIT);
	//Now since we have applied DLL and DLM we now lock or freeze those values by disabling DLAB i.e DLAB=0
	//Baud= ~115200. Now we can perform UART communication!
}

void initTimer0(void)
{
	/*Assuming CCLK (System Clock) = 72Mhz (set by startup code)*/
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<9);
	LPC_TMR32B0->CTCR = 0x0;
	LPC_TMR32B0->PR = PRESCALE; //Increment TC at every 71999+1 clock cycles
	//72000 clock cycles @72Mhz = 1 mS
	LPC_TMR32B0->TCR = 0x02; //Reset Timer
}

void delayMS(unsigned int milliseconds) //Using Timer0
{
	LPC_TMR32B0->TCR = 0x02; //Reset Timer
	LPC_TMR32B0->TCR = 0x01; //Enable timer
	while(LPC_TMR32B0->TC < milliseconds); //wait until timer counter reaches the desired delay
	LPC_TMR32B0->TCR = 0x00; //Disable timer
}

void uartWrite(char cChar)
{
	while ( !(LPC_UART->LSR & THRE) ); // wait till the THR is empty
	// now we can write to the queue
	LPC_UART->THR = cChar;

	/*if( cChar == '\n' ) //Send <CR+LF>
	{
		LPC_UART->THR = CARRIAGE_RETURN;
		while( !(LPC_UART->LSR & THRE ));
		LPC_UART->THR = LINE_FEED;
	}
	else
	{
		 LPC_UART->THR = cChar;
	}*/
}
