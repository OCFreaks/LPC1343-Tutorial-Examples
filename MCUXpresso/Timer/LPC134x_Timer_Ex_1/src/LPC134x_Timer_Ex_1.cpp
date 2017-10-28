/*(C) Umang Gajera - http://www.ocfreaks.com 2011-17.
http://www.ocfreaks.com/lpc1343-timer-programming-tutorial/
LPC1343 Timer example 1.

More Embedded tutorials @ http://www.ocfreaks.com/cat/embedded/
*/
#include <LPC13xx.h>

#define PRESCALE (72000-1) //72000 PCLK clock cycles to increment TC by 1

void delayMS(unsigned int milliseconds);
void initTimer0(void);

int main(void)
{
	//SystemInit(); //called by Startup Code before main(), hence no need to call again.
	initTimer0(); //Initialize Timer0
	LPC_GPIO0->DIR = (1<<7); //Configure PIO0_7 as output

	while(1)
	{
		LPC_GPIO0->DATA = (1<<7); //Turn LED ON
		delayMS(500); //0.5 Second(s) Delay
		LPC_GPIO0->DATA = ~(1<<7); //Turn OFF LED
		delayMS(500);
	}
	//return 0; //normally this wont execute ever
}

void initTimer0(void)
{
	/*Assuming PCLK (CLCK/System Clock) = 72Mhz (set by startup code)*/
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<9); //Enable 32Bit Timer0 Clock
	LPC_TMR32B0->CTCR = 0x0;
	LPC_TMR32B0->PR = PRESCALE; //Increment LPC_TMR32B0->TC at every 71999+1 clock cycles
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
