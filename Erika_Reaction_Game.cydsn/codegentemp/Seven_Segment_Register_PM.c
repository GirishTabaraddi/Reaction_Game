/*******************************************************************************
* File Name: Seven_Segment_Register_PM.c
* Version 1.80
*
* Description:
*  This file contains the setup, control, and status commands to support 
*  the component operation in the low power mode. 
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Seven_Segment_Register.h"

/* Check for removal by optimization */
#if !defined(Seven_Segment_Register_Sync_ctrl_reg__REMOVED)

static Seven_Segment_Register_BACKUP_STRUCT  Seven_Segment_Register_backup = {0u};

    
/*******************************************************************************
* Function Name: Seven_Segment_Register_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Seven_Segment_Register_SaveConfig(void) 
{
    Seven_Segment_Register_backup.controlState = Seven_Segment_Register_Control;
}


/*******************************************************************************
* Function Name: Seven_Segment_Register_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*
*******************************************************************************/
void Seven_Segment_Register_RestoreConfig(void) 
{
     Seven_Segment_Register_Control = Seven_Segment_Register_backup.controlState;
}


/*******************************************************************************
* Function Name: Seven_Segment_Register_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component for entering the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Seven_Segment_Register_Sleep(void) 
{
    Seven_Segment_Register_SaveConfig();
}


/*******************************************************************************
* Function Name: Seven_Segment_Register_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component after waking up from the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Seven_Segment_Register_Wakeup(void)  
{
    Seven_Segment_Register_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
