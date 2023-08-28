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
#include "project.h"
#include "seven_segment.h"

/*****************************************************************************/
/* Local pre-processor symbols/macros ('#define')                            */
/*****************************************************************************/

/*****************************************************************************/
/* Global variable definitions (declared in header file with 'extern')       */
/*****************************************************************************/

/*****************************************************************************/
/* Local type definitions ('typedef')                                        */
/*****************************************************************************/

/*****************************************************************************/
/* Local variable definitions ('static')                                     */
/*****************************************************************************/
const static uint8_t Seven_Segment_Lookup [] = {
    0b00111111, // 0
    0b00000110, // 1
    0b01011011, // 2
    0b01001111, // 3
    0b01100110, // 4
    0b01101101, // 5
    0b01111101, // 6
    0b00000111, // 7
    0b01111111, // 8
    0b01101111, // 9
    0x77,       // a
    0x7c,       // b
    0x39,       // c
    0x5e,       // d
    0x79,       // e
    0x71,       // f
};

/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/


/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/

/**
 * This function initializes the seven segment displays needed for the game.
 * @param None
 * @return RC_t Success, if the function executes without any error.
 */
RC_t SevenSegment_init()
{
    SevenSegmentClear(Seven_Segment_Left);
    SevenSegmentClear(Seven_Segment_Right);
    return RC_SUCCESS;
}

/**
 * This function is used to clear the 7 segment displays.
 * @param Segement_ID - takes the left or right display as parameter
 * @return RC_t Success, if the function executes without any error.
 */
RC_t SevenSegmentClear(mySeven_t Segement_ID)
{
    if(Segement_ID == Seven_Segment_Left)
    {
        SEVEN_Select_Write(1);   
    }
    else
    {
        SEVEN_Select_Write(0);
    }
    Seven_Segment_Register_Write(0);
    
    return RC_SUCCESS;
}

/**
 * This function writes a value to the selected display
 * @param pass the mySeven_t id from the enum
 * @param value to be displayed 
 * @return Success, if the function executes without any error.
 */
RC_t Seven_Segment_Write(mySeven_t Segment_ID, uint8_t value)
{
    SEVEN_Select_Write(Segment_ID);
    
    uint8_t Letter_to_print = Seven_Segment_Lookup[value];
    Seven_Segment_Register_Write(Letter_to_print);
    
    if(Letter_to_print > 0xff) return RC_ERROR_BAD_PARAM;
    
    return RC_SUCCESS;
}

/**
 * This function prints the numbers on the selected display
 * @param pass the mySeven_t id from the enum
 * @return Success, if the function executes without any error.
 */
RC_t Seven_Segment_Print(mySeven_t Segment_ID)
{
    for(uint8_t i = 0; i < 16; i++)
    {
        Seven_Segment_Write(Segment_ID, i);
        CyDelay(1000);
    }
    
    return RC_SUCCESS;   
}