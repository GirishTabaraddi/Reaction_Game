/*******************************************************************************
* File Name: Seven_Segment_Register.h  
* Version 1.80
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CONTROL_REG_Seven_Segment_Register_H) /* CY_CONTROL_REG_Seven_Segment_Register_H */
#define CY_CONTROL_REG_Seven_Segment_Register_H

#include "cyfitter.h"

#if ((CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3) || \
     (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC4) || \
     (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5))
    #include "cytypes.h"
#else
    #include "syslib/cy_syslib.h"
#endif

    
/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 controlState;

} Seven_Segment_Register_BACKUP_STRUCT;


/***************************************
*         Function Prototypes 
***************************************/

void    Seven_Segment_Register_Write(uint8 control) ;
uint8   Seven_Segment_Register_Read(void) ;

void Seven_Segment_Register_SaveConfig(void) ;
void Seven_Segment_Register_RestoreConfig(void) ;
void Seven_Segment_Register_Sleep(void) ; 
void Seven_Segment_Register_Wakeup(void) ;


/***************************************
*            Registers        
***************************************/

/* Control Register */
#define Seven_Segment_Register_Control        (* (reg8 *) Seven_Segment_Register_Sync_ctrl_reg__CONTROL_REG )
#define Seven_Segment_Register_Control_PTR    (  (reg8 *) Seven_Segment_Register_Sync_ctrl_reg__CONTROL_REG )

#endif /* End CY_CONTROL_REG_Seven_Segment_Register_H */


/* [] END OF FILE */
