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
#include "glower.h"
#include "project.h"

#include "glower.h"
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
const RGB__Glow_t RGB_glowtable_1[9] = {
//Red   Green   Blue    TimeInMS
{ 255,  0,      0,      5000},
{ 0,    255,    0,      5000},
{ 0,    0,      255,    5000},
{ 0,    0,      0,      100},
{ 255,  255,    255,    100},
{ 0,    0,      0,      100},
{ 255,  255,    255,    100},
{ 0,    0,      0,      100},
{ 255,  255,    255,    100}
};



void RGB__Glower()
{   
    static uint16_t i = 0;
    RGB_Red_Write(RGB_glowtable_1[i].RGB__RedValue);
    RGB_Green_Write(RGB_glowtable_1[i].RGB__GreenValue);
    RGB_Blue_Write(RGB_glowtable_1[i].RGB__BlueValue);

    if( i == 8)
    {
        i = 0;
    }
    else
    {
        i++;
    }
    CancelAlarm(alarm_glower_delay);
    SetRelAlarm(alarm_glower_delay, RGB_glowtable_1[i].RGB__Delay, 0);
}


//uint16 RGB__Delay()
//{
//    static uint16 i = 0;
//    uint16_t delay = 1;
//    
//    RGB_Red_Write(RGB_glowtable_1[i].RGB__RedValue);
//    RGB_Green_Write(RGB_glowtable_1[i].RGB__GreenValue);
//    RGB_Blue_Write(RGB_glowtable_1[i].RGB__BlueValue);
//    delay = RGB_glowtable_1[i].RGB__Delay;
//    
//    if( i == 8 )
//    {
//        i = 0;
//    }
//    else
//    {
//        i++;
//    }
//    return delay;
//}

//void RGB__Glower()
//{
//    static uint16_t RGB_delay = 0;
//    if(RGB_delay == 0)
//    {
//        RGB_delay = (RGB__Delay())/10;
//    }
//    RGB_delay--;
//    uint16_t delay= 0;
//    delay = RGB__Delay();
//    CancelAlarm(alarm_glower_delay);
//    SetRelAlarm(alarm_glower_delay, delay, delay);
    
    
//    RGB_Red_Write(RGB_glowtable_1[i].RGB__RedValue);
//    RGB_Green_Write(RGB_glowtable_1[i].RGB__GreenValue);
//    RGB_Blue_Write(RGB_glowtable_1[i].RGB__BlueValue);
//    //CyDelay(RGB_glowtable_1[i].RGB__Delay);
//    SetRelAlarm(alarm_glower_delay, RGB_glowtable_1[i].RGB__Delay, 0);
//    if(i == 8)
//    {
//        i = 0;
//    }
//    else
//    {
//        i++;
//    }
//}