/**
* \file <filename>
* \author <author-name>
* \date <date>
*
* \brief <Symbolic File name>
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

/*****************************************************************************/
/* Include files                                                             */
/*****************************************************************************/
#include "seven_segment.h"
#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*****************************************************************************/
/* Local pre-processor symbols/macros ('#define')                            */
/*****************************************************************************/

/*****************************************************************************/
/* Global variable definitions (declared in header file with 'extern')       */
/*****************************************************************************/

/*****************************************************************************/
/* Local type definitions ('typedef')                                        */
/*****************************************************************************/

typedef enum
{
    GAME__ISIDLE,                   /**< Waiting for Button press to start the game. */
    GAME__ISWAITINGRANDOMTIME,      /**< Waiting for Random time. */
    GAME__ISWAITINGBUTTON           /**< Waiting for User Button(1/2) press. */
} GAME__State_t;
    

/*****************************************************************************/
/* Local variable definitions ('static')                                     */
/*****************************************************************************/

static GAME__State_t GAME__State = GAME__ISIDLE;

static uint16_t random_7segment_value = 0;

char buffer[32];

/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/

//All state machine action are static functions
//e.g. GAME__StartRandomTimer

/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/

RC_t GAME__StartRandomTimer(uint16 mintimeInms, uint16 maxtimeInms)
{
    //First get a random number
    uint32 randomTime = rand() % (maxtimeInms - mintimeInms) + mintimeInms;
//    UART_LOG_PutString("Random time: ");
//    itoa(randomTime,buffer,10);
//    UART_LOG_PutString(buffer);
//    UART_LOG_PutString("\n");
    //Then set the timout using cydelay
    //CyDelay(randomTime * 1000);
    
    //This alarm fires an event timeout after waiting randomly from 1s-3s. This alarm is called only once.
    SetRelAlarm(alarm_wait3s, randomTime*1000, 0);
    
    return RC_SUCCESS;
}

RC_t GAME__ShowRandom7SegmentValue()
{
    random_7segment_value = rand()%2;
    
    Seven_Segment_Write(Seven_Segment_Left, (random_7segment_value+1));
    Seven_Segment_Write(Seven_Segment_Right, (random_7segment_value+1));
    
    return RC_SUCCESS;
}

boolean_t GAME__CorrectButton(EventMaskType event_state)
{ 
    if((random_7segment_value+1) == 2 && event_state & ev_Button1)
        return TRUE;
    else if((random_7segment_value+1) == 1 && event_state & ev_Button2)
        return TRUE;
    else
        return FALSE;
}

RC_t GAME__Play(GAME_event_t Game, EventMaskType ev_State)
{
    switch (GAME__State)
    {
        case GAME__ISIDLE :
            if (Game == GAME_BUTTON)
            {
                // If the event received is Button, we need to generate random wait time (1s - 3s)
                // then set the game state to wait for random time.
                GAME__StartRandomTimer(1,3);
                GAME__State = GAME__ISWAITINGRANDOMTIME; 
                //SetEvent(task_control, ev_Timeout);
            }
            break;
            
        case GAME__ISWAITINGRANDOMTIME:
            if (Game == GAME_TIMEOUT)
            {
                // If the game is waiting for randomtime, then we need to show random 7segment value 
                // and set the game to user button wait state
                CancelAlarm(alarm_wait3s);
                GAME__ShowRandom7SegmentValue();
                GAME__State = GAME__ISWAITINGBUTTON; 
                SetRelAlarm(alarm_wait1s,1000,0);
                
                  temp1 = sys_tick_count;
//                GAME__Show("temp1 value: ");
//                itoa(temp1,buffer,10);
//                UART_LOG_PutString(buffer);
//                GAME__Show("\n");
//                
//                GAME__Show(" sys tick count@7: ");
//                itoa(sys_tick_count,buffer,10);
//                UART_LOG_PutString(buffer);
//                GAME__Show("\n");
            }
            break;
            
        case GAME__ISWAITINGBUTTON:
            if (Game == GAME_BUTTON)
            {
                if (GAME__CorrectButton(ev_State))
                {
                    GAME__Show("\nGreat!! - Correct Button Pressed\n");
                    correct_button_pressed++;
                    
                      temp2 = sys_tick_count;
//                    GAME__Show("temp2 value: ");
//                    itoa(temp2,buffer,10);
//                    UART_LOG_PutString(buffer);
//                    GAME__Show("\n");
//                    
//                    GAME__Show(" sys tick count@CB: ");
//                    itoa(sys_tick_count,buffer,10);
//                    UART_LOG_PutString(buffer);
//                    GAME__Show("\n");
                    
                    reaction_time = temp2 - temp1;
                    GAME__Show("Reaction time(ms): ");
                    itoa(reaction_time,buffer,10);
                    UART_LOG_PutString(buffer);
                    GAME__Show("\n");
                }
                else
                {
                    GAME__Show("\nOopss!! - Wrong Button Pressed\n");
                }
                GAME__State = GAME__ISIDLE;
                CancelAlarm(alarm_wait1s);
                
                SevenSegmentClear(Seven_Segment_Left);
                SevenSegmentClear(Seven_Segment_Right);
                
                GAME__DisplayResult();
            }   
    }
    return RC_SUCCESS;
}
void GAME__DisplayTime()
{
    GAME__Show("\n\nEND OF THE GAME\n");
    GAME__Show("\nBelow are your Reaction Game Results.....\n");
    GAME__Show("\nFINAL SCORE - Correct number of button pressed is: ");
    itoa(correct_button_pressed,buffer,10);
    UART_LOG_PutString(buffer);
    UART_LOG_PutString("\n");
    
    GAME__Show("Total Reaction time of the Game(ms): ");
    itoa(sys_tick_count,buffer,10);
    UART_LOG_PutString(buffer);
    GAME__Show("\n");
    
    GAME__Show("Average Reaction time of the Game(ms): ");
    average_game_time = sys_tick_count/GAME_ROUNDS;
    itoa(average_game_time,buffer,10);
    UART_LOG_PutString(buffer);
    GAME__Show("\n");
}

void GAME__DisplayResult()
{
    game_rounds++;
    if(game_rounds <= GAME_ROUNDS)
    {
        GAME__Show("\nReaction test program ROUND ");
        itoa(game_rounds,buffer,10);
        UART_LOG_PutString(buffer);
        UART_LOG_PutString("\n");
        GAME__Show("Press one of the two buttons to start the round...\n");
    }
}
void GAME__Show(char str [])
{
    UART_LOG_PutString(str);
}