/**
 ******************************************************************************
 * @file      startup_lpc13xx.c
 * @author    Coocox
 * @version   V1.0
 * @date      24/02/2010
 * @brief     LPC13XX Devices Startup code.
 *            This module performs:
 *                - Set the initial SP
 *                - Set the vector table entries with the exceptions ISR address
 *                - Initialize data and bss
 *                - Setup the microcontroller system.
 *                - Call the application's entry point.
 *            After Reset the Cortex-M3 processor is in Thread mode,
 *            priority is Privileged, and the Stack is set to Main.
 *******************************************************************************
 */
 

/*----------Stack Configuration-----------------------------------------------*/  
#define STACK_SIZE       0x00000100      /*!< The Stack size suggest using even number    */
__attribute__ ((section(".co_stack")))
unsigned long pulStack[STACK_SIZE];      


/*----------Macro definition--------------------------------------------------*/  
#define WEAK __attribute__ ((weak))           


/*----------Declaration of the default fault handlers-------------------------*/  
/* System exception vector handler */
__attribute__ ((used))
void WEAK  Reset_Handler(void);   
void WEAK  NMI_Handler(void);       
void WEAK  HardFault_Handler(void); 
void WEAK  MemManage_Handler(void); 
void WEAK  BusFault_Handler(void);  
void WEAK  UsageFault_Handler(void);
void WEAK  SVC_Handler(void);       
void WEAK  DebugMon_Handler(void);  
void WEAK  PendSV_Handler(void);    
void WEAK  SysTick_Handler(void);   
void WEAK  WAKEUP_IRQHandler(void);
void WEAK  I2C_IRQHandler(void);
void WEAK  TIMER16_0_IRQHandler(void);
void WEAK  TIMER16_1_IRQHandler(void);
void WEAK  TIMER32_0_IRQHandler(void);
void WEAK  TIMER32_1_IRQHandler(void);
void WEAK  SSP_IRQHandler(void);
void WEAK  UART_IRQHandler(void);
void WEAK  USB_IRQHandler(void);
void WEAK  USB_FIQHandler(void);
void WEAK  ADC_IRQHandler(void);
void WEAK  WDT_IRQHandler(void);
void WEAK  BOD_IRQHandler(void);
void WEAK  FMC_IRQHandler(void);
void WEAK  PIOINT3_IRQHandler(void);
void WEAK  PIOINT2_IRQHandler(void);
void WEAK  PIOINT1_IRQHandler(void);
void WEAK  PIOINT0_IRQHandler(void);   


/*----------Symbols defined in linker script----------------------------------*/  
extern unsigned long _sidata;    /*!< Start address for the initialization 
                                      values of the .data section.            */
extern unsigned long _sdata;     /*!< Start address for the .data section     */    
extern unsigned long _edata;     /*!< End address for the .data section       */    
extern unsigned long _sbss;      /*!< Start address for the .bss section      */
extern unsigned long _ebss;      /*!< End address for the .bss section        */      
extern void _eram;               /*!< End address for ram                     */


/*----------Function prototypes-----------------------------------------------*/  
extern int main(void);           /*!< The entry point for the application.    */
extern void SystemInit(void);    /*!< Setup the microcontroller system(CMSIS) */
void Default_Reset_Handler(void);   /*!< Default reset handler                */
static void Default_Handler(void);  /*!< Default exception handler            */


/**
  *@brief The minimal vector table for a Cortex M3.  Note that the proper constructs
  *       must be placed on this to ensure that it ends up at physical address
  *       0x00000000.  
  */
__attribute__ ((used,section(".isr_vector")))
void (* const g_pfnVectors[])(void) =
{	
  /*----------Core Exceptions------------------------------------------------ */
  (void *)&pulStack[STACK_SIZE],     /*!< The initial stack pointer         */
  Reset_Handler,             /*!< Reset Handler                               */
  NMI_Handler,               /*!< NMI Handler                                 */
  HardFault_Handler,         /*!< Hard Fault Handler                          */
  MemManage_Handler,         /*!< MPU Fault Handler                           */
  BusFault_Handler,          /*!< Bus Fault Handler                           */
  UsageFault_Handler,        /*!< Usage Fault Handler                         */
  0,0,0,0,                   /*!< Reserved                                    */
  SVC_Handler,               /*!< SVCall Handler                              */
  DebugMon_Handler,          /*!< Debug Monitor Handler                       */
  0,                         /*!< Reserved                                    */
  PendSV_Handler,            /*!< PendSV Handler                              */
  SysTick_Handler,           /*!< SysTick Handler                             */
  
  /*----------External Exceptions---------------------------------------------*/
  WAKEUP_IRQHandler,         /*!< 16+ 0: Wakeup PIO0.0                        */
  WAKEUP_IRQHandler,         /*!< 16+ 1: Wakeup PIO0.1                        */    
  WAKEUP_IRQHandler,         /*!< 16+ 2: Wakeup PIO0.2                        */
  WAKEUP_IRQHandler,         /*!< 16+ 3: Wakeup PIO0.3                        */
  WAKEUP_IRQHandler,         /*!< 16+ 4: Wakeup PIO0.4                        */ 
  WAKEUP_IRQHandler,         /*!< 16+ 5: Wakeup PIO0.5                        */
  WAKEUP_IRQHandler,         /*!< 16+ 6: Wakeup PIO0.6                        */ 
  WAKEUP_IRQHandler,         /*!< 16+ 7: Wakeup PIO0.7                        */
  WAKEUP_IRQHandler,         /*!< 16+ 8: Wakeup PIO0.8                        */
  WAKEUP_IRQHandler,         /*!< 16+ 9: Wakeup PIO0.9                        */
  WAKEUP_IRQHandler,         /*!< 16+10: Wakeup PIO0.10                       */
  WAKEUP_IRQHandler,         /*!< 16+11: Wakeup PIO0.11                       */
  WAKEUP_IRQHandler,         /*!< 16+12: Wakeup PIO1.0                        */
  WAKEUP_IRQHandler,         /*!< 16+13: Wakeup PIO1.1                        */
  WAKEUP_IRQHandler,         /*!< 16+14: Wakeup PIO1.2                        */
  WAKEUP_IRQHandler,         /*!< 16+15: Wakeup PIO1.3                        */ 
  WAKEUP_IRQHandler,         /*!< 16+16: Wakeup PIO1.4                        */
  WAKEUP_IRQHandler,         /*!< 16+17: Wakeup PIO1.5                        */
  WAKEUP_IRQHandler,         /*!< 16+18: Wakeup PIO1.6                        */
  WAKEUP_IRQHandler,         /*!< 16+19: Wakeup PIO1.7                        */
  WAKEUP_IRQHandler,         /*!< 16+20: Wakeup PIO1.8                        */
  WAKEUP_IRQHandler,         /*!< 16+21: Wakeup PIO1.9                        */ 
  WAKEUP_IRQHandler,         /*!< 16+22: Wakeup PIO1.10                       */
  WAKEUP_IRQHandler,         /*!< 16+23: Wakeup PIO1.11                       */
  WAKEUP_IRQHandler,         /*!< 16+24: Wakeup PIO2.0                        */
  WAKEUP_IRQHandler,         /*!< 16+25: Wakeup PIO2.1                        */
  WAKEUP_IRQHandler,         /*!< 16+26: Wakeup PIO2.2                        */
  WAKEUP_IRQHandler,         /*!< 16+27: Wakeup PIO2.3                        */ 
  WAKEUP_IRQHandler,         /*!< 16+28: Wakeup PIO2.4                        */
  WAKEUP_IRQHandler,         /*!< 16+29: Wakeup PIO2.5                        */
  WAKEUP_IRQHandler,         /*!< 16+30: Wakeup PIO2.6                        */
  WAKEUP_IRQHandler,         /*!< 16+31: Wakeup PIO2.7                        */ 
  WAKEUP_IRQHandler,         /*!< 16+32: Wakeup PIO2.8                        */
  WAKEUP_IRQHandler,         /*!< 16+33: Wakeup PIO2.9                        */
  WAKEUP_IRQHandler,         /*!< 16+34: Wakeup PIO2.10                       */ 
  WAKEUP_IRQHandler,         /*!< 16+35: Wakeup PIO2.11                       */
  WAKEUP_IRQHandler,         /*!< 16+36: Wakeup PIO3.0                        */
  WAKEUP_IRQHandler,         /*!< 16+37: Wakeup PIO3.1                        */
  WAKEUP_IRQHandler,         /*!< 16+38: Wakeup PIO3.2                        */ 
  WAKEUP_IRQHandler,         /*!< 16+39: Wakeup PIO3.3                        */
  I2C_IRQHandler,            /*!< 16+40: I2C                                  */    
  TIMER16_0_IRQHandler,      /*!< 16+41: 16-bit Counter-Timer 0               */    
  TIMER16_1_IRQHandler,      /*!< 16+42: 16-bit Counter-Timer 1               */ 
  TIMER32_0_IRQHandler,      /*!< 16+43: 32-bit Counter-Timer 0               */
  TIMER32_1_IRQHandler,      /*!< 16+44: 32-bit Counter-Timer 1               */
  SSP_IRQHandler,            /*!< 16+45: SSP                                  */
  UART_IRQHandler,           /*!< 16+46: UART                                 */    
  USB_IRQHandler,            /*!< 16+47: USB IRQ                              */
  USB_FIQHandler,            /*!< 16+48: USB FIQ                              */
  ADC_IRQHandler,            /*!< 16+49: A/D Converter                        */
  WDT_IRQHandler,            /*!< 16+50: Watchdog Timer                       */
  BOD_IRQHandler,            /*!< 16+51: Brown Out Detect                     */
  FMC_IRQHandler,            /*!< 16+52: IP2111 Flash Memory Controller       */ 
  PIOINT3_IRQHandler,        /*!< 16+53: PIO INT3                             */ 
  PIOINT2_IRQHandler,        /*!< 16+54: PIO INT2                             */  
  PIOINT1_IRQHandler,        /*!< 16+55: PIO INT1                             */
  PIOINT0_IRQHandler,        /*!< 16+56: PIO INT0                             */
};                 


/**
  * @brief  This is the code that gets called when the processor first
  *         starts execution following a reset event. Only the absolutely
  *         necessary set is performed, after which the application
  *         supplied main() routine is called. 
  * @param  None
  * @retval None
  */
void Default_Reset_Handler(void)
{
  /* Initialize data and bss */
  unsigned long *pulSrc, *pulDest;

  /* Copy the data segment initializers from flash to SRAM */
  pulSrc = &_sidata;

  for(pulDest = &_sdata; pulDest < &_edata; )
  {
    *(pulDest++) = *(pulSrc++);
  }
  
  /* Zero fill the bss segment.  This is done with inline assembly since this
     will clear the value of pulDest if it is not kept in a register. */
  __asm("  ldr     r0, =_sbss\n"
        "  ldr     r1, =_ebss\n"
        "  mov     r2, #0\n"
        "  .thumb_func\n"
        "zero_loop:\n"
        "    cmp     r0, r1\n"
        "    it      lt\n"
        "    strlt   r2, [r0], #4\n"
        "    blt     zero_loop");

  /* Setup the microcontroller system. */
  SystemInit();
	
  /* Call the application's entry point.*/
  main();
}


/**
  *@brief Provide weak aliases for each Exception handler to the Default_Handler. 
  *       As they are weak aliases, any function with the same name will override 
  *       this definition.
  */
#pragma weak Reset_Handler = Default_Reset_Handler
#pragma weak NMI_Handler = Default_Handler     
#pragma weak HardFault_Handler = Default_Handler     
#pragma weak MemManage_Handler = Default_Handler     
#pragma weak BusFault_Handler = Default_Handler      
#pragma weak UsageFault_Handler = Default_Handler    
#pragma weak SVC_Handler = Default_Handler           
#pragma weak DebugMon_Handler = Default_Handler      
#pragma weak PendSV_Handler = Default_Handler        
#pragma weak SysTick_Handler = Default_Handler       
#pragma weak WAKEUP_IRQHandler = Default_Handler
#pragma weak I2C_IRQHandler = Default_Handler
#pragma weak TIMER16_0_IRQHandler = Default_Handler
#pragma weak TIMER16_1_IRQHandler = Default_Handler
#pragma weak TIMER32_0_IRQHandler = Default_Handler
#pragma weak TIMER32_1_IRQHandler = Default_Handler
#pragma weak SSP_IRQHandler = Default_Handler
#pragma weak UART_IRQHandler = Default_Handler
#pragma weak USB_IRQHandler = Default_Handler
#pragma weak USB_FIQHandler = Default_Handler
#pragma weak ADC_IRQHandler = Default_Handler
#pragma weak WDT_IRQHandler = Default_Handler
#pragma weak BOD_IRQHandler = Default_Handler
#pragma weak FMC_IRQHandler = Default_Handler
#pragma weak PIOINT3_IRQHandler = Default_Handler
#pragma weak PIOINT2_IRQHandler = Default_Handler
#pragma weak PIOINT1_IRQHandler = Default_Handler
#pragma weak PIOINT0_IRQHandler = Default_Handler     


/**
  * @brief  This is the code that gets called when the processor receives an 
  *         unexpected interrupt.  This simply enters an infinite loop, 
  *         preserving the system state for examination by a debugger.
  * @param  None
  * @retval None  
  */
static void Default_Handler(void) 
{
  /* Go into an infinite loop. */
  while (1) 
  {
  }
}

/*********************** (C) COPYRIGHT 2009 Coocox ************END OF FILE*****/
