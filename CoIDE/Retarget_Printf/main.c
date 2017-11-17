/*(c) Umang Gajera - www.ocfreaks.com
 * Retarget Printf() using UART in CoIDE tutorial
 * http://www.ocfreaks.com/how-to-retarget-printf-using-uart-in-coocox-coide/
 * Adapted from:
 * http://www.ocfreaks.com/lpc1343-uart-programming-tutorial/
 * More Embedded stuff @ http://www.ocfreaks.com/cat/embedded/
 * License : GPL */

#include <stdio.h>
#include "lpc13xx.h"
#include "uart.h"

int main(void)
{
	/*SystemInit(); gets called boot code and sets CCLK=72Mhz*/
	initUART(); /*Init UART before calling printf()!*/
	/*UART Baud = 115200*/

	int num = 1343;
	int num2 = -99;
	int numh = 0x3CA;
	char string1[] = "This is a String";

	printf("Hi. I am printf() sending output over UART!\n\r");
	printf("I have been called for:\n\r");
	printf("OCFreaks.com - retarget printf() in CoIDE tutorial.\n\r");

	printf("num = %d\n\r",num);
	printf("num2 = %i\n\r",num2);
	printf("numh(hex) = %X\n\r",numh);
	printf("string1 = %s\n\r",string1);

    while(1);

   /*return 0; This won't execute*/
}
