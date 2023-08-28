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

#include "glower.h"
#include "fader.h"
    
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
    Fader_init();
    //Reconfigure ISRs with OS parameters.
    //This line MUST be called after the hardware driver initialisation!
    EE_system_init();

    //Start SysTick
	//Must be done here, because otherwise the isr vector is not overwritten yet
    EE_systick_start();  
	
    //Start the cyclic alarms 
    SetRelAlarm(alarm_fader, 5, 5);
    
    //Activate all extended and the background task
    ActivateTask(task_glower);
    ActivateTask(task_background);
    
    TerminateTask();
}

TASK(task_fader)
{
    Fader_LED();
    TerminateTask();
}

TASK(task_glower)
{
    RGB__Glower();
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
