#ifndef _UART_LPC1343_H_
#define _UART_LPC1343_H_

/*(c) Umang Gajera - www.ocfreaks.com
 * UART init and write functions for printf()
 * http://www.ocfreaks.com/how-to-retarget-printf-using-uart-in-coocox-coide/
 * Adapted from:
 * http://www.ocfreaks.com/lpc1343-uart-programming-tutorial/
 * More Embedded stuff @ http://www.ocfreaks.com/cat/embedded/
 * License : GPL */

void initUART(void);
void uartWrite(char data);

#endif
