/*******************************************************************************
* File Name: emFile_PM.c
* Version 1.20
*
* Description:
*  This file provides the API source code for Power Management of the emFile
*  component.
*
* Note:
*
*******************************************************************************
* Copyright 2011-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include <project.h>
#include "emFile.h"

/*******************************************************************************
* Function Name: emFile_SaveConfig
********************************************************************************
*
* Summary:
*  Saves SPI Masters configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
void emFile_SaveConfig(void) 
{
    #if(SPI_BLOCK_USED == UDB_SPI_BLOCK)
        #if(emFile_NUMBER_SD_CARDS == 4u)
            emFile_UDB_SPI_0_SaveConfig();
            emFile_UDB_SPI_1_SaveConfig();
            emFile_UDB_SPI_2_SaveConfig();
            emFile_UDB_SPI_3_SaveConfig();
        #elif(emFile_NUMBER_SD_CARDS == 3u)
            emFile_UDB_SPI_0_SaveConfig();
            emFile_UDB_SPI_1_SaveConfig();
            emFile_UDB_SPI_2_SaveConfig();
        #elif(emFile_NUMBER_SD_CARDS == 2u)
            emFile_UDB_SPI_0_SaveConfig();
            emFile_UDB_SPI_1_SaveConfig();
        #else
            emFile_UDB_SPI_0_SaveConfig();
        #endif /* (emFile_NUMBER_SD_CARDS == 4u) */
    #endif /* (SPI_BLOCK_USED == UDB_SPI_BLOCK) */
}


/*******************************************************************************
* Function Name: emFile_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores SPI Masters configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  If this API is called without first calling SaveConfig then in the following
*  registers will be default values from Customizer:
*
*******************************************************************************/
void emFile_RestoreConfig(void) 
{
    #if(SPI_BLOCK_USED == UDB_SPI_BLOCK)
        #if(emFile_NUMBER_SD_CARDS == 4u)
            emFile_UDB_SPI_0_RestoreConfig();
            emFile_UDB_SPI_1_RestoreConfig();
            emFile_UDB_SPI_2_RestoreConfig();
            emFile_UDB_SPI_3_RestoreConfig();
        #elif(emFile_NUMBER_SD_CARDS == 3u)
            emFile_UDB_SPI_0_RestoreConfig();
            emFile_UDB_SPI_1_RestoreConfig();
            emFile_UDB_SPI_2_RestoreConfig();
        #elif(emFile_NUMBER_SD_CARDS == 2u)
            emFile_UDB_SPI_0_RestoreConfig();
            emFile_UDB_SPI_1_RestoreConfig();
        #else
            emFile_UDB_SPI_0_RestoreConfig();
        #endif /* (emFile_NUMBER_SD_CARDS == 4u) */
    #endif /* (SPI_BLOCK_USED == UDB_SPI_BLOCK) */
}


/*******************************************************************************
* Function Name: emFile_Sleep
********************************************************************************
*
* Summary:
*  Prepare emFile to go to sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
void emFile_Sleep(void) 
{
    #if(SPI_BLOCK_USED == UDB_SPI_BLOCK)
        #if(emFile_NUMBER_SD_CARDS == 4u)
            emFile_UDB_SPI_0_Sleep();
            emFile_UDB_SPI_1_Sleep();
            emFile_UDB_SPI_2_Sleep();
            emFile_UDB_SPI_3_Sleep();
        #elif(emFile_NUMBER_SD_CARDS == 3u)
            emFile_UDB_SPI_0_Sleep();
            emFile_UDB_SPI_1_Sleep();
            emFile_UDB_SPI_2_Sleep();
        #elif(emFile_NUMBER_SD_CARDS == 2u)
            emFile_UDB_SPI_0_Sleep();
            emFile_UDB_SPI_1_Sleep();
        #else
            emFile_UDB_SPI_0_Sleep();
        #endif /* (emFile_NUMBER_SD_CARDS == 4u) */
    #elif(SPI_BLOCK_USED == SCB_SPI_BLOCK)
        #if(emFile_NUMBER_SD_CARDS == 4u)
            emFile_SCB_SPI_0_Sleep();
            emFile_SCB_SPI_1_Sleep();
            emFile_SCB_SPI_2_Sleep();
            emFile_SCB_SPI_3_Sleep();
        #elif(emFile_NUMBER_SD_CARDS == 3u)
            emFile_SCB_SPI_0_Sleep();
            emFile_SCB_SPI_1_Sleep();
            emFile_SCB_SPI_2_Sleep();
        #elif(emFile_NUMBER_SD_CARDS == 2u)
            emFile_SCB_SPI_0_Sleep();
            emFile_SCB_SPI_1_Sleep();
        #else
            emFile_SCB_SPI_0_Sleep();
        #endif /* (emFile_NUMBER_SD_CARDS == 4u) */      
    #endif /* (SPI_BLOCK_USED == UDB_SPI_BLOCK) */
}


/*******************************************************************************
* Function Name: emFile_Wakeup
********************************************************************************
*
* Summary:
*  Prepare SPIM Components to wake up.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
void emFile_Wakeup(void) 
{
    #if(SPI_BLOCK_USED == UDB_SPI_BLOCK)
        #if(emFile_NUMBER_SD_CARDS == 4u)
            emFile_UDB_SPI_0_Wakeup();
            emFile_UDB_SPI_1_Wakeup();
            emFile_UDB_SPI_2_Wakeup();
            emFile_UDB_SPI_3_Wakeup();
        #elif(emFile_NUMBER_SD_CARDS == 3u)
            emFile_UDB_SPI_0_Wakeup();
            emFile_UDB_SPI_1_Wakeup();
            emFile_UDB_SPI_2_Wakeup();
        #elif(emFile_NUMBER_SD_CARDS == 2u)
            emFile_UDB_SPI_0_Wakeup();
            emFile_UDB_SPI_1_Wakeup();
        #else
            emFile_UDB_SPI_0_Wakeup();
        #endif /* (emFile_NUMBER_SD_CARDS == 4u) */
    #elif(SPI_BLOCK_USED == SCB_SPI_BLOCK)
        #if(emFile_NUMBER_SD_CARDS == 4u)
            emFile_SCB_SPI_0_Wakeup();
            emFile_SCB_SPI_1_Wakeup();
            emFile_SCB_SPI_2_Wakeup();
            emFile_SCB_SPI_3_Wakeup();
        #elif(emFile_NUMBER_SD_CARDS == 3u)
            emFile_SCB_SPI_0_Wakeup();
            emFile_SCB_SPI_1_Wakeup();
            emFile_SCB_SPI_2_Wakeup();
        #elif(emFile_NUMBER_SD_CARDS == 2u)
            emFile_SCB_SPI_0_Wakeup();
            emFile_SCB_SPI_1_Wakeup();
        #else
            emFile_SCB_SPI_0_Wakeup();
        #endif /* (emFile_NUMBER_SD_CARDS == 4u) */        
    #endif /* (SPI_BLOCK_USED == UDB_SPI_BLOCK) */
}


/* [] END OF FILE */
