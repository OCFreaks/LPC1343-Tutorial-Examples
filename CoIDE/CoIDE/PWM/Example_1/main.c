/*(C) Umang Gajera - www.ocfreaks.com
http://www.ocfreaks.com/lpc1343-pwm-programming-tutorial/
LPC1343 PWM Tutorial Example 1 - LED Dimming using PWM.
License: GPL.
More Embedded tutorials @ http://www.ocfreaks.com/cat/embedded/
*/

#include <lpc13xx.h>

#define PRESCALE_US (72-1) //Used by PWM (32bit-TMR0 in PWM Mode)
#define PRESCALE_MS (72000-1) //Used by 32Bit-TMR1 for generating delay
#define PWM_PERIOD 1000 //in micro-seconds

void init32BitTMR0_PWM(void);
inline void updatePulseWidth(unsigned int pulseWidth);
void delayMS(unsigned int milliseconds);
void init32BitTMR1(void);

int main(void)
{
	//SystemInit(); //called by Startup Code before main(), hence no need to call again.

	int pulseWidths[] = {
			PWM_PERIOD-0,PWM_PERIOD-250,
			PWM_PERIOD-500,PWM_PERIOD-750,
			PWM_PERIOD-1000}; //Inverted Pulse Widths for varying LED Brightness
	//Note: PWM_PERIOD-0 = LED almost OFF, PWM_PERIOD-1000 = LED Brightest!
	//PWM Pulses in LPC1343 are Right-Aligned or "inverted"!
	const int numPulseWidths = 5;
	int count=1;
	int dir=0; //direction, 0 = Increasing, 1 = Decreasing

	init32BitTMR0_PWM(); //Initialise CT32B0 as PWM
	init32BitTMR1(); //Used by delayMS()

	while(1)
	{
		updatePulseWidth(pulseWidths[count]); //Update LED Pulse Width
		delayMS(500);

		if(count == (numPulseWidths-1) || count == 0)
		{
			dir = !dir; //Toggle direction if we have reached count limit
		}

		if(dir) count--;
		else count++;
	}
  //return 0; //normally this won't execute ever
}

void init32BitTMR0_PWM(void)
{
	/*Assuming CCLK (System Clock) = 72Mhz (set by startup code)*/
	LPC_IOCON->PIO1_6 |= 0x2; //Select CT32B0_MAT0 (MAT0.0) function for PWM O/P, Marked as RXD on LPCXpresso Board
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<9); //Enable 32Bit-TMR0 Clock
	LPC_TMR32B0->CTCR = 0x0;
	LPC_TMR32B0->PR = PRESCALE_US; //Increment TC at every 71999+1 clock cycles
	//72000 clock cycles @72Mhz = 1 mS
	LPC_TMR32B0->MR3 = PWM_PERIOD; //1ms Period duration
	LPC_TMR32B0->MR0 = PWM_PERIOD-250; //Default TOFF time in mS
	LPC_TMR32B0->MCR = (1<<10); //Reset on MR3 Match

	LPC_TMR32B0->PWMC = 0x1; //Enable PWM Mode for MAT0.0 (on PIO1_6)

	LPC_TMR32B0->TCR = 0x02; //Reset Timer
	LPC_TMR32B0->TCR = 0x01; //Enable timer
}

inline void updatePulseWidth(unsigned int pulseWidth)
{
	LPC_TMR32B0->MR0 = pulseWidth; //Update MR1 with new value
}

void delayMS(unsigned int milliseconds) //Using 16bit-TMR0
{
	LPC_TMR32B1->TCR = 0x02; //Reset Timer
	LPC_TMR32B1->TCR = 0x01; //Enable timer

	while(LPC_TMR32B1->TC < milliseconds); //wait until timer counter reaches the desired delay

	LPC_TMR32B1->TCR = 0x00; //Disable timer
}

void init32BitTMR1(void)
{
	/*Assuming CCLK (System Clock) = 72Mhz (set by startup code)*/
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<10); //Enable 32Bit-TMR0 Clock
	LPC_TMR32B1->CTCR = 0x0;
	LPC_TMR32B1->PR = PRESCALE_MS; //Increment TC at every 71999+1 clock cycles
	//72000 clock cycles @72Mhz = 1 mS
	LPC_TMR32B1->TCR = 0x02; //Reset Timer
}
