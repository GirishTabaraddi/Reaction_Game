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
#include "fader.h"
#include "project.h"
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



/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/


/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/

/**
 * The function starts the PWM for all the LEDs
 * @param no prameter
 * @return RC_SUCCESS if ok
 */
RC_t Fader_Start()
{
    //PWM_Led_Red_Start();
    //PWM_Led_Yellow_Start();
    //PWM_Led_Green_Start();
    
    return RC_SUCCESS;
}

/**
 * Initialize each LEDs to OFF state.
 * @param none
 * @return RC_SUCCESS if ok.
 */
RC_t Fader_init()
{
    PWM1_WriteCompare(0);
    PWM2_WriteCompare(0);
    PWM3_WriteCompare(0);
    
    return RC_SUCCESS;
}

RC_t Fader_LED()
{
    for(int i = 0; i < 255; i++)
    {
        PWM1_Start();
        //Turn ON Red LED
        PWM1_WriteCompare(i);
        CyDelay(5);
    }
    
    for(int i = 255; i > 0; i--)
    {
        PWM2_Start();
        //along with Turn OFF Red LED, Turn ON Yellow LED.
        PWM1_WriteCompare(i);
        PWM2_WriteCompare(255-i);
        CyDelay(5);
    }

    for(int i = 0; i < 255; i++)
    {
        PWM3_Start();
        //along with Turn OFF Yellow LED, Turn ON Green LED.
        PWM2_WriteCompare(255-i);
        PWM3_WriteCompare(i);
        CyDelay(5);
    }
    
    for(int i = 255; i > 0; i--)
    {
        //Turn OFF Green LED
        PWM3_WriteCompare(i);
        CyDelay(5);
    }    
    return RC_SUCCESS;
}
