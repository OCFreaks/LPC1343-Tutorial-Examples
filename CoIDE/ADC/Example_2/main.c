/*(C) Umang Gajera - www.ocfreaks.com
LPC1343 ADC Interrupt Example Source Code for CooCox CoIDE
http://www.ocfreaks.com/lpc1343-adc-programming-tutorial/
More Embedded tutorials @ www.ocfreaks.com/cat/embedded/
License : GPL.*/

#include <lpc13xx.h>
#include <stdio.h>
#include "ocf_lpc134x_lib.h" //contains code for UART and Timer.

/* Check http://www.ocfreaks.com/retarget-printf-using-uart-coocox-coide/
 * on how to retarget printf() in coocox CoIDE */

#define VREF       3.3 //Reference Voltage at VREFP pin, given VREFN = 0V(GND)
#define ADC_CLK_EN (1<<13) //Enable ADC clock
#define SEL_AD0    (1<<0) //Select Channel AD0
#define CLKDIV     15 // ADC clock-divider (ADC_CLOCK=PCLK/CLKDIV+1), yields 4.5Mhz ADC clock
#define ADC_PWRUP  (~(1<<4)) //setting it to 0 will power it up
#define START_CNV  (1<<24) //001 for starting the conversion immediately
#define ADC_DONE   (1U<<31) //define it as unsigned value or compiler will throw warning
#define ADC_BURST  (1<<16) //Enable burst(hardware) mode
#define ADCR_SETUP_BURST ((CLKDIV<<8) | ADC_BURST)

int AD0Result=0;

int main(void)
{
	//SystemInit(); //Gets called by Startup code, sets CCLK=100Mhz, PCLK=25Mhz
	initUART(); //Initialize UART printf()
	initTimer0(); //For delayMS()

	LPC_SYSCON->PDRUNCFG &= ADC_PWRUP; //Power-up ADC Block
	LPC_SYSCON->SYSAHBCLKCTRL |= ADC_CLK_EN; //Enable ADC clock
	LPC_ADC->CR = ADCR_SETUP_BURST | SEL_AD0; //Setup ADC Block

	/* Now select AD0 function and set ADMODE=0 PIO0_11(P0.11) */
	//LPC_IOCON->R_PIO0_11 = 0x2; //Uncomment this if NOT using CoIDE, see tutorial for more.
	LPC_IOCON->JTAG_TDI_PIO0_11 = 0x2; //comment this if NOT using CoIDE.

	LPC_ADC->INTEN = SEL_AD0; //Enable AD0 Interrupt, set ADGINTEN to 0
	NVIC_EnableIRQ(ADC_IRQn); //Enable ADC IRQ
	
	float voltage = 0;

	printf("OCFreaks.com LPC134x ADC Interrupt Tutorial Example.\n\r");
	printf("BURST/Hardware-Controlled ADC Mode on AD0 Channel.\n\r");
	while(1)
	{
		voltage = ((float)AD0Result * VREF) / 1024;
		printf("AD0 = %dmV\n\r" , (int)(voltage*1000)); //Print millivolts
		delayMS(500); //Slowing down Updates to 2 Updates per second
	}
	//return 0; //This won't execute
}

void ADC_IRQHandler(void)
{
	unsigned long ADC_GDR_Read = LPC_ADC->GDR;
	int channel = (ADC_GDR_Read>>24) & 0x7; //Extract Channel Number
	int currentResult = (ADC_GDR_Read>>6) & 0x3FF; //Extract Conversion Result

	if(channel == 0)
	{
		AD0Result = LPC_ADC->DR0; //Dummy Read to Clear Done bit
		AD0Result = currentResult;
	}
}
