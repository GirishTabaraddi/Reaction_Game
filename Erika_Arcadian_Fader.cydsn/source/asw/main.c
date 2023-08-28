/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include "global.h"
#include "derivate.h"

#include "fader.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
char buffer1[32];

uint16_t sys_tick_count = 0;


//ISR which will increment the systick counter every ms
ISR(systick_handler)
{  
    CounterTick(cnt_systick); 
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    //Set systick period to 1 ms. Enable the INT and start it.
	EE_systick_set_period(MILLISECONDS_TO_TICKS(1, BCLK__BUS_CLK__HZ));
	EE_systick_enable_int();
   
    // Start Operating System
    for(;;)	    
    	StartOS(OSDEFAULTAPPMODE);
        
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
}

/********************************************************************************
 * Task Definitions
 ********************************************************************************/
TASK(task_init)
{
    //Fader_Start();
    UART_LOG_Start();
    
    //Reconfigure ISRs with OS parameters.
    //This line MUST be called after the hardware driver initialisation!
    EE_system_init();

    //Start SysTick
	//Must be done here, because otherwise the isr vector is not overwritten yet
    EE_systick_start();  
	
    //Start the cyclic alarms 
    SetRelAlarm(alarm_timer_tick, 1, 1);
    SetRelAlarm(alarm_init, 1, 1);
    
    //Activate all extended and the background task
    ActivateTask(task_background);
    
    TerminateTask();
}

TASK(task_timer)
{
    //RGB_Red_Write(255);
    sys_tick_count++;
//                UART_LOG_PutString("systickcount value: ");
//        itoa(sys_tick_count,buffer1,10);
//        UART_LOG_PutString(buffer1);
//        UART_LOG_PutString("\n");
}

TASK(task_fader)
{
    static uint16_t Fader__Brightness = 0;
    static uint16_t i = 0;
    
    i = sys_tick_count % 5;

    if(i == 0)
    {
        Fader__Brightness++;
        if(Fader__Brightness >= 0 && Fader__Brightness < 255)
        {
            PWM_Led_Red_Start();
            PWM_Led_Red_WriteCompare(LED__Pulse_Width[Fader__Brightness]); //0 to 255
            PWM_Led_Yellow_WriteCompare(0);
            PWM_Led_Green_WriteCompare(LED__Pulse_Width[(255 - Fader__Brightness)]);
        }
        else if(Fader__Brightness >= 255 && Fader__Brightness < 510)
        {
            PWM_Led_Yellow_Start();
            PWM_Led_Red_WriteCompare(LED__Pulse_Width[(510 - Fader__Brightness)]); //255 to 0
            PWM_Led_Yellow_WriteCompare(LED__Pulse_Width[(Fader__Brightness - 255)]); //0 to 255
            PWM_Led_Green_WriteCompare(0);
        }
        else if(Fader__Brightness >= 510 && Fader__Brightness < 765)
        {
            PWM_Led_Green_Start();
            PWM_Led_Red_WriteCompare(0);
            PWM_Led_Yellow_WriteCompare(LED__Pulse_Width[(765 - Fader__Brightness)]); //255 to 0
            PWM_Led_Green_WriteCompare(LED__Pulse_Width[(Fader__Brightness - 510)]); //0 to 255
        }
        else
        {
            Fader__Brightness = 0;
        }
//        UART_LOG_PutString("i value after mod 5: ");
//        itoa(Fader__Brightness,buffer1,10);
//        UART_LOG_PutString(buffer1);
//        UART_LOG_PutString("\n");
    }
    TerminateTask();
}

TASK(task_background)
{
    while(1)
    {
        //do something with low prioroty
        __asm("nop");
    }
}

/* [] END OF FILE */
