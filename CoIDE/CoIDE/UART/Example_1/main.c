/*(C) Umang Gajera - www.ocfreaks.com
 * LPC1343 Basic UART Tutorial - Example 1 Source Code.
 * http://www.ocfreaks.com/lpc1343-uart-programming-tutorial/
 * More Embedded tutorials @ www.ocfreaks.com/cat/embedded/
 * License : GPL.*/

#include <lpc13xx.h>

#define THRE        (1<<5) //Transmit Holding Register Empty
#define MULVAL      1
#define DIVADDVAL   0
#define Ux_FIFO_EN  (1<<0)
#define Rx_FIFO_RST (1<<1)
#define Tx_FIFO_RST (1<<2)
#define DLAB_BIT    (1<<7)
#define LINE_FEED   0x0A //LF, For Linux, MAC and Windows Terminals
#define CARRIAGE_RETURN 0x0D //CR, For Windows Terminals (CR+LF).

void initUART(void);
void uartWrite(char data);

int main(void)
{
	//SystemInit(); //This already gets called by CMSIS Startup Code.
	char msg[] = { 'H','e','l','l','o',' ','f','r','o','m',' ','L','P','C','1','3','4','3','\0' };
	int count=0;

	initUART();

	while(1)
	{
		while( msg[count]!='\0' )
		{
			uartWrite(msg[count]);
			count++;
		}
		//Send NEW Line Character(s) i.e. "\n"
		uartWrite(CARRIAGE_RETURN); //Comment this for Linux or MacOS
		uartWrite(LINE_FEED); //Windows uses CR+LF for newline.
		count=0; // reset counter
	}
	//return 0; //This won't execute normally
}

void uartWrite(char txData)
{
	while(!(LPC_UART->LSR & THRE)); //wait until THR is empty
	//now we can write to Tx FIFO
	LPC_UART->THR = txData;
}

void initUART(void)
{
	/*Assuming CCLK=UART_PCLK=72Mhz!*/

	//UART CLOCK Enable Sequence Step 1 - Select TXD,RXD functions
	LPC_IOCON->PIO1_6 = 0x1; //Select RXD for PIO1_6
	LPC_IOCON->PIO1_7 = 0x1; //Select RXD for PIO2_6

	//UART CLOCK Enable Sequence Step 2 - Set Divider & Enable Clock
	LPC_SYSCON->UARTCLKDIV = 1; //Set Divider by 1, so UART_PCLK=CCLK
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<12);//Enable UART clock

	LPC_UART->LCR = 3 | DLAB_BIT ; /* 8 bits, no Parity, 1 Stop bit & DLAB set to 1  */
	LPC_UART->DLL = 39; /*see tutorial for calculations*/
	LPC_UART->DLM = 0;

	LPC_UART->FCR |= Ux_FIFO_EN | Rx_FIFO_RST | Tx_FIFO_RST;
	LPC_UART->FDR = (MULVAL<<4) | DIVADDVAL; /* MULVAL=15(bits - 7:4) , DIVADDVAL=2(bits - 3:0)  */
	LPC_UART->LCR &= ~(DLAB_BIT);
	//Now since we have applied DLL and DLM we now lock or freeze those values by disabling DLAB i.e DLAB=0
	//Baud= ~115200. Now we can perform UART communication!
}
