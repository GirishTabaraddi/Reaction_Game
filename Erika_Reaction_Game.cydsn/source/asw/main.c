/**
* \file main
* \author Peter Fromm
* \date 5.12.2019
*
* \brief Demonstrator for critical regions
*
* The file contains two cyclic tasks, whioch both access the same UART to create a critical region
* Depending on priority and timing configuration, the data may get corrupted.
*
* \note <notes>
* \todo <todos>
* \warning <warnings, e.g. dependencies, order of execution etc.>
*
*  Changelog:\n
*  - <version; data of change; author>
*            - <description of the change>
*
* \copyright Copyright ©2016
* Department of electrical engineering and information technology, Hochschule Darmstadt - University of applied sciences (h_da). All Rights Reserved.
* Permission to use, copy, modify, and distribute this software and its documentation for educational, and research purposes in the context of non-commercial
* (unless permitted by h_da) and official h_da projects, is hereby granted for enrolled students of h_da, provided that the above copyright notice,
* this paragraph and the following paragraph appear in all copies, modifications, and distributions.
* Contact Prof.Dr.-Ing. Peter Fromm, peter.fromm@h-da.de, Birkenweg 8 64295 Darmstadt - GERMANY for commercial requests.
*
* \warning This software is a PROTOTYPE version and is not designed or intended for use in production, especially not for safety-critical applications!
* The user represents and warrants that it will NOT use or redistribute the Software for such purposes.
* This prototype is for research purposes only. This software is provided "AS IS," without a warranty of any kind.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "project.h"
#include "global.h"

#include "seven_segment.h"
#include "button.h"         
#include "game.h"
#include "fader.h"
#include "glower.h"

volatile uint16_t sys_tick_count = 0;

//ISR which will increment the systick counter every ms
ISR(systick_handler)
{  
    CounterTick(cnt_systick); 
}

int main()
{
    srand(time(0));
    CyGlobalIntEnable; /* Enable global interrupts. */
   
    //Set systick period to 1 ms. Enable the INT and start it.
	EE_systick_set_period(MILLISECONDS_TO_TICKS(1, BCLK__BUS_CLK__HZ));
	EE_systick_enable_int();
   
    // Start Operating System
    for(;;)	    
    	StartOS(OSDEFAULTAPPMODE);
}

void unhandledException()
{
    //Ooops, something terrible happened....check the call stack to see how we got here...
    __asm("bkpt");
}

/********************************************************************************
 * Task Definitions
 ********************************************************************************/

TASK(task_init)
{
    //Init MCAL Drivers
    UART_LOG_Start();
    SevenSegment_init();
    
    //Reconfigure ISRs with OS parameters.
    //This line MUST be called after the hardware driver initialisation!
    EE_system_init();

    //Start SysTick
	//Must be done here, because otherwise the isr vector is not overwritten yet
    EE_systick_start();  
	
    //Start the cyclic alarms 
    SetRelAlarm(alarm_timer_tick, 1, 1);
    SetRelAlarm(alarm_fader, 5, 5);
    SetRelAlarm(alarm_glower, 10, 10);
    
    //Activate all extended and the background task
    ActivateTask(task_control);
    ActivateTask(task_background);
    
    game_rounds = 1;
    correct_button_pressed = 0;
    GAME__Show("============================================================\n");
    GAME__Show("             Welcome to The Reaction Game!\n");
    GAME__Show("============================================================\n");
    GAME__Show("Reaction test program ROUND 1\n");
    GAME__Show("Press one of the two buttons to start the round...\n");
    
    TerminateTask();
    
}

//TASK(task_input)
//{
//    if(BUTTON_IsPressed(BUTTON_1) == 1)
//    {
//        SetEvent(task_control, ev_Button1);
//    }
//    if(BUTTON_IsPressed(BUTTON_2) == 1)
//    {
//        SetEvent(task_control, ev_Button2);
//    }
//    TerminateTask();
//}

TASK(task_timer)
{
    sys_tick_count++;
}

TASK(task_control)
{
    EventMaskType ev = 0;
    
    // At the inital stage, set the Game to GAME_NOEVENT,
    // as we dont have any event fired.
    GAME_event_t Game = GAME_NOEVENT; 
    
    while(game_rounds <= GAME_ROUNDS)
    {
        WaitEvent(ev_Button1 | ev_Button2 | ev_Timeout | ev_wait1s);
        GetEvent(task_control, &ev);
        
        if(ev & ev_wait1s)
        {
            GAME__Show("Too Slow...\n");
            break;
        }
        if((ev & ev_Button1) | (ev & ev_Button2))
        {
            //GAME__Show("Button pressed");
            // If any one of the Button event is fired, set the GAME_BUTTON to Game.
            Game = GAME_BUTTON; 
        }
        else if(ev & ev_Timeout)
        {
            //GAME__Show("Waiting for Random Time...\n");
            Game = GAME_TIMEOUT;
        }
        if(Game != GAME_NOEVENT)
        {
            GAME__Play(Game,ev);
        }
        ClearEvent(ev); // Clear the event that has been set from the top. After this line ev will have no event(0)
    }
    GAME__DisplayTime();
    
    TerminateTask();
}

TASK(task_fader)
{
    Fader_Set();
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


/********************************************************************************
 * ISR Definitions
 ********************************************************************************/


ISR2(isr_button)
{
    if(BUTTON_IsPressed(BUTTON_1) == 1)
    {
        SetEvent(task_control, ev_Button1);
    }
    if(BUTTON_IsPressed(BUTTON_2) == 1)
    {
        SetEvent(task_control, ev_Button2);
    }   
}

/* [] END OF FILE */
