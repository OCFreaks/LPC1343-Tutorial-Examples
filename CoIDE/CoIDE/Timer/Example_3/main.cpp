/*(C) Umang Gajera - http://www.ocfreaks.com 2011-17.
http://www.ocfreaks.com/lpc1343-timer-programming-tutorial/
LPC1343 Timer example 3.

More Embedded tutorials @ http://www.ocfreaks.com/cat/embedded/
*/
#include <LPC13xx.h>

#define PRESCALE (72000-1) //72000 PCLK clock cycles to increment TC by 1

void initTimer0();

int main(void)
{
	//SystemInit(); //called by Startup Code before main(), hence no need to call again.
	LPC_GPIO0->DIR |= (1<<7); //set PIO0_7 as output
	initTimer0();

	while(1)
	{
		//Idle loop
	}
	//return 0; //normally this won't execute
}

void initTimer0(void)
{
	/*Assuming CCLK (System Clock) = 72Mhz (set by startup code)*/
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<9); //Enable 32Bit Timer0 Clock

	LPC_TMR32B0->CTCR = 0x0;
	LPC_TMR32B0->PR = PRESCALE; //Increment LPC_TMR32B0->TC at every 71999+1 clock cycles
	//72000 clock cycles @72Mhz = 1 mS

	LPC_TMR32B0->MR0 = 500; //Toggle Time in mS
	LPC_TMR32B0->MCR |= (1<<0) | (1<<1); // Interrupt & Reset on MR0 match
	LPC_TMR32B0->TCR |= (1<<1); //Reset Timer0

	NVIC_EnableIRQ(TIMER_32_0_IRQn); //Enable timer interrupt

	LPC_TMR32B0->TCR = 0x01; //Enable timer
}

extern "C" void TIMER32_0_IRQHandler(void) //Use extern "C" so C++ can link it properly, for C it is not required
{
	LPC_TMR32B0->IR |= (1<<0); //Clear MR0 Interrupt flag
	LPC_GPIO0->DATA ^= (1<<7); //Toggle LED
}
