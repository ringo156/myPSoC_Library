/*******************************************************************************
* File Name: emFile_MMC_HW_SPI.c
* Version 1.20
*
* Description:
*  Contains a set of File System APIs that implements SPI mode driver operation.
*
* Note:
*
********************************************************************************
* Copyright 2011-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "FS.h"
#include "emFile.h"
#include "MMC_X_HW.h"
#include "project.h"


/*********************************************************************
*             Macros
*********************************************************************/
/* in mV, example means 3.3V */
#define emFile_MMC_DEFAULT_SUPPLY_VOLTAGE    (3300u)

/* Max. startup frequency (KHz) */
#define emFile_STARTUP_FREQ                   (400u)


/*********************************************************************
*       Static data
*********************************************************************/

static char emFile_isInited0;

#if (emFile_NUMBER_SD_CARDS >= 2u)

    static char emFile_isInited1;

#endif /* (emFile_NUMBER_SD_CARDS >= 2u) */

#if (emFile_NUMBER_SD_CARDS >= 3u)

    static char emFile_isInited2;

#endif /* (emFile_NUMBER_SD_CARDS >= 3u) */

#if (emFile_NUMBER_SD_CARDS == 4u)

    static char emFile_isInited3;

#endif /* (emFile_NUMBER_SD_CARDS == 4u) */


/*******************************************************************************
* Function Name: emFile_Init
********************************************************************************
*
* Summary:
*  Initialize SPI Masters.
*
* Parameters:
*  Unit - Unit (SPIM) number.
*
* Return:
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
static void emFile_Init(U8 Unit) CYREENTRANT
{
    switch(Unit)
    {
    case 0u:
        #if(SPI_BLOCK_USED == UDB_SPI_BLOCK)
            if (emFile_isInited0 == 0u)
            {
                /* Indicate that SPI 0 was initialized */
                emFile_isInited0 = 1u;

                /* Initialize SPI */

                /* Stop the clock to set a required divider */
               emFile_UDB_SPI_clk_1_Stop();

                /* Set the inital clock frequency to 400 KHz */
               emFile_UDB_SPI_clk_1_SetDividerValue(CYDEV_BCLK__HFCLK__KHZ/emFile_STARTUP_FREQ);

                /* Start the clock */
               emFile_UDB_SPI_clk_1_Start();

                /* Start SPI 0 */
                emFile_UDB_SPI_0_Start();
            }
        #else
            if (emFile_isInited0 == 0u)
            {
                /* Indicate that SPI 0 was initialized */
                emFile_isInited0 = 1u;

                /* Initialize SPI */

                /* Stop the clock to set a required divider */
               emFile_SCB_SPI_clk_1_Stop();

                /* Set the inital clock frequency to 400 KHz */
               emFile_SCB_SPI_clk_1_SetDividerValue(((uint32)CYDEV_BCLK__HFCLK__KHZ * SCB_SPI_OVERSAMPLING_FACTOR_GUI/emFile_STARTUP_FREQ));

                /* Start the clock */
               emFile_SCB_SPI_clk_1_Start();

                /* Start SPI 0 */
                emFile_SCB_SPI_0_Start();
            }            
        #endif /* (SPI_BLOCK_USED == UDB_SPI_BLOCK) */

        break;

        #if (emFile_NUMBER_SD_CARDS >= 2u)

            case 1u:
                #if(SPI_BLOCK_USED == UDB_SPI_BLOCK)
                    if (emFile_isInited1 == 0u)
                    {
                        /* Indicate that SPI 1 was initialized */
                        emFile_isInited1 = 1u;

                        /* Stop the clock to set a required divider */
                       emFile_UDB_SPI_clk_2_Stop();

                        /* Set the inital clock frequency to 400 KHz */
                       emFile_UDB_SPI_clk_2_SetDividerValue(CYDEV_BCLK__HFCLK__KHZ/emFile_STARTUP_FREQ);

                        /* Start the clock */
                       emFile_UDB_SPI_clk_2_Start();

                        /* Start SPI 1 */
                        emFile_UDB_SPI_1_Start();
                    }
                #else
                    if (emFile_isInited1 == 0u)
                    {
                        /* Indicate that SPI 1 was initialized */
                        emFile_isInited1 = 1u;

                        /* Initialize SPI */

                        /* Stop the clock to set a required divider */
                       emFile_SCB_SPI_clk_2_Stop();

                        /* Set the inital clock frequency to 400 KHz */
                       emFile_SCB_SPI_clk_2_SetDividerValue(((uint32)CYDEV_BCLK__HFCLK__KHZ * SCB_SPI_OVERSAMPLING_FACTOR_GUI)/emFile_STARTUP_FREQ));

                        /* Start the clock */
                       emFile_SCB_SPI_clk_2_Start();

                        /* Start SPI 1 */
                        emFile_SCB_SPI_1_Start();
                    }                     
                #endif /*(SPI_BLOCK_USED == UDB_SPI_BLOCK) */

                break;

        #endif /* (emFile_NUMBER_SD_CARDS >= 2u) */

        #if (emFile_NUMBER_SD_CARDS >= 3u)

            case 2u:
                #if(SPI_BLOCK_USED == UDB_SPI_BLOCK)
                    if (emFile_isInited2 == 0u)
                    {
                        /* Indicate that SPI 2 was initialized */
                        emFile_isInited2 = 1u;

                        /* Stop the clock to set a required divider */
                       emFile_UDB_SPI_clk_3_Stop();

                        /* Set the inital clock frequency to 400 KHz */
                       emFile_UDB_SPI_clk_3_SetDividerValue(CYDEV_BCLK__HFCLK__KHZ/emFile_STARTUP_FREQ);

                        /* Start the clock */
                       emFile_UDB_SPI_clk_3_Start();

                        /* Start SPI 2 */
                        emFile_UDB_SPI_2_Start();
                    }
                #else
                    if (emFile_isInited2 == 0u)
                    {
                        /* Indicate that SPI 2 was initialized */
                        emFile_isInited2 = 1u;

                        /* Initialize SPI */

                        /* Stop the clock to set a required divider */
                       emFile_SCB_SPI_clk_3_Stop();

                        /* Set the inital clock frequency to 400 KHz */
                       emFile_SCB_SPI_clk_3_SetDividerValue(((uint32)CYDEV_BCLK__HFCLK__KHZ * SCB_SPI_OVERSAMPLING_FACTOR_GUI)/emFile_STARTUP_FREQ));

                        /* Start the clock */
                       emFile_SCB_SPI_clk_3_Start();

                        /* Start SPI 2 */
                        emFile_SCB_SPI_2_Start();
                    }                    
                #endif /* (SPI_BLOCK_USED == UDB_SPI_BLOCK) */

                break;

        #endif /* (emFile_NUMBER_SD_CARDS >= 3u) */

        #if (emFile_NUMBER_SD_CARDS == 4u)

            case 3u:
                #if(SPI_BLOCK_USED == UDB_SPI_BLOCK)
                    if (emFile_isInited3 == 0u)
                    {
                        /* Indicate that SPI 3 was initialized */
                        emFile_isInited3 = 1u;

                        /* Stop the clock to set a required divider */
                       emFile_UDB_SPI_clk_4_Stop();

                        /* Set the inital clock frequency to 400 KHz */
                       emFile_UDB_SPI_clk_4_SetDividerValue(CYDEV_BCLK__HFCLK__KHZ/emFile_STARTUP_FREQ);

                        /* Start the clock */
                       emFile_UDB_SPI_clk_4_Start();

                        /* Start SPI 3 */
                        emFile_UDB_SPI_3_Start();
                    }
                #else
                    if (emFile_isInited3 == 0u)
                    {
                        /* Indicate that SPI 3 was initialized */
                        emFile_isInited3 = 1u;

                        /* Initialize SPI */

                        /* Stop the clock to set a required divider */
                       emFile_SCB_SPI_clk_4_Stop();

                        /* Set the inital clock frequency to 400 KHz */
                       emFile_SCB_SPI_clk_4_SetDividerValue(((uint32)CYDEV_BCLK__HFCLK__KHZ * SCB_SPI_OVERSAMPLING_FACTOR_GUI)/emFile_STARTUP_FREQ));

                        /* Start the clock */
                       emFile_SCB_SPI_clk_4_Start();

                        /* Start SPI 3 */
                        emFile_SCB_SPI_3_Start();
                    }                    
                #endif /* (SPI_BLOCK_USED == UDB_SPI_BLOCK) */

                break;

        #endif /* (emFile_NUMBER_SD_CARDS == 4u) */

    default:
        #if(SPI_BLOCK_USED == UDB_SPI_BLOCK)
            if (emFile_isInited0 == 0u)
            {
                /* Indicate that SPI 0 was initialized */
                emFile_isInited0 = 1u;

                /* Stop the clock to set a required divider */
               emFile_UDB_SPI_clk_1_Stop();

                /* Set the inital clock frequency to 400 KHz */
               emFile_UDB_SPI_clk_1_SetDividerValue(CYDEV_BCLK__HFCLK__KHZ/emFile_STARTUP_FREQ);

                /* Start the clock */
               emFile_UDB_SPI_clk_1_Start();

                /* Start SPI 0 */
                emFile_UDB_SPI_0_Start();
            }
        #else
            if (emFile_isInited0 == 0u)
            {
                /* Indicate that SPI 0 was initialized */
                emFile_isInited0 = 1u;

                /* Initialize SPI */

                /* Stop the clock to set a required divider */
               emFile_SCB_SPI_clk_1_Stop();

                /* Set the inital clock frequency to 400 KHz */
               emFile_SCB_SPI_clk_1_SetDividerValue(((uint32)CYDEV_BCLK__HFCLK__KHZ * SCB_SPI_OVERSAMPLING_FACTOR_GUI/emFile_STARTUP_FREQ));

                /* Start the clock */
               emFile_SCB_SPI_clk_1_Start();

                /* Start SPI 0 */
                emFile_SCB_SPI_0_Start();
            }            
        #endif /* (SPI_BLOCK_USED == UDB_SPI_BLOCK) */
        
        break;
      }
}


/*******************************************************************************
* Function Name: emFile_ReadWriteSPI
********************************************************************************
*
* Summary:
*  Reads and Writes data via SPI.
*
* Parameters:
*  Unit - Unit number;
*  Data - data to be written.
*
* Return:
*  Data received from SD card.
*
* Reentrant:
*  No
*
*******************************************************************************/
static U8 emFile_ReadWriteSPI(U8 Unit, U8 Data) CYREENTRANT
{
    U8 spiData;
    
    #if(SPI_BLOCK_USED == SCB_SPI_BLOCK)
        uint32 scbData = (uint32)Data;
    #endif /* (SPI_BLOCK_USED == SCB_SPI_BLOCK) */

    switch(Unit)
    {
    case 0u:

        #if(SPI_BLOCK_USED == SCB_SPI_BLOCK)
            /* Send Data */
            emFile_SCB_SPI_0_SpiUartWriteTxData(scbData);

            /* Read data */
            scbData = emFile_SCB_SPI_0_SpiUartReadRxData(); 
            
            spiData = scbData;
        #else
            /* Send Data */
            emFile_UDB_SPI_0_WriteTxData(Data);

            /* Wait until all bits are shifted */
            while (0u == (emFile_UDB_SPI_0_STS_SPI_DONE & emFile_UDB_SPI_0_ReadTxStatus()));

            /* Read data */
            spiData = emFile_UDB_SPI_0_ReadRxData();            
        #endif /* (SPI_BLOCK_USED == SCB_SPI_BLOCK) */ 

        break;

    #if (emFile_NUMBER_SD_CARDS >= 2u)

        case 1u:

            #if(SPI_BLOCK_USED == SCB_SPI_BLOCK)
                /* Send Data */
                emFile_SCB_SPI_1_SpiUartWriteTxData(scbData);

                /* Read data */
                scbData = emFile_SCB_SPI_1_SpiUartReadRxData(); 
                
                spiData = scbData;
            #else
                /* Send Data */
                emFile_UDB_SPI_1_WriteTxData(Data);

                /* Wait until all bits are shifted */
                while (0u == (emFile_UDB_SPI_1_STS_SPI_DONE & emFile_UDB_SPI_1_ReadTxStatus()));

                /* Read data */
                spiData = emFile_UDB_SPI_1_ReadRxData();            
            #endif /* (SPI_BLOCK_USED == SCB_SPI_BLOCK) */ 

            break;

    #endif /* (emFile_NUMBER_SD_CARDS >= 2u) */

    #if (emFile_NUMBER_SD_CARDS >= 3u)

        case 2u:

            #if(SPI_BLOCK_USED == SCB_SPI_BLOCK)
                /* Send Data */
                emFile_SCB_SPI_2_SpiUartWriteTxData(scbData);

                /* Read data */
                scbData = emFile_SCB_SPI_2_SpiUartReadRxData(); 
                
                spiData = scbData;
            #else
                /* Send Data */
                emFile_UDB_SPI_2_WriteTxData(Data);

                /* Wait until all bits are shifted */
                while (0u == (emFile_UDB_SPI_2_STS_SPI_DONE & emFile_UDB_SPI_2_ReadTxStatus()));

                /* Read data */
                spiData = emFile_UDB_SPI_2_ReadRxData();            
            #endif /* (SPI_BLOCK_USED == SCB_SPI_BLOCK) */ 

            break;

    #endif /* (emFile_NUMBER_SD_CARDS >= 2u) */

    #if (emFile_NUMBER_SD_CARDS >= 4u)

        case 3u:

            #if(SPI_BLOCK_USED == SCB_SPI_BLOCK)
                /* Send Data */
                emFile_SCB_SPI_3_SpiUartWriteTxData(scbData);

                /* Read data */
                scbData = emFile_SCB_SPI_3_SpiUartReadRxData(); 
                
                spiData = scbData;
            #else
                /* Send Data */
                emFile_UDB_SPI_3_WriteTxData(Data);

                /* Wait until all bits are shifted */
                while (0u == (emFile_UDB_SPI_3_STS_SPI_DONE & emFile_UDB_SPI_3_ReadTxStatus()));

                /* Read data */
                spiData = emFile_UDB_SPI_3_ReadRxData();            
            #endif /* (SPI_BLOCK_USED == SCB_SPI_BLOCK) */ 

            break;

    #endif /* (emFile_NUMBER_SD_CARDS >= 4u) */

    default:

        #if(SPI_BLOCK_USED == SCB_SPI_BLOCK)
            /* Send Data */
            emFile_SCB_SPI_0_SpiUartWriteTxData(scbData);

            /* Read data */
            scbData = emFile_SCB_SPI_0_SpiUartReadRxData(); 
            
            spiData = scbData;
        #else
            /* Send Data */
            emFile_UDB_SPI_0_WriteTxData(Data);

            /* Wait until all bits are shifted */
            while (0u == (emFile_UDB_SPI_0_STS_SPI_DONE & emFile_UDB_SPI_0_ReadTxStatus()));

            /* Read data */
            spiData = emFile_UDB_SPI_0_ReadRxData();            
        #endif /* (SPI_BLOCK_USED == SCB_SPI_BLOCK) */ 
        
        break;
    }

    return(spiData);
}

/*******************************************************************************
* Function Name: FS_MMC_HW_X_EnableCS
********************************************************************************
*
* Summary:
*  FS low level function. Sets the card slot active using the
*  chip select (CS) line.
*
* Parameters:
*  Unit      - Device Index.
*
* Return:
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
void FS_MMC_HW_X_EnableCS(U8 Unit)
{
    switch(Unit)
    {
        case 0u:

            /* Set CS to 0 */
            
            #if(SPI_BLOCK_USED == UDB_SPI_BLOCK)
                emFile_UDB_SPI_CS_0_Write(0u);
            #else
                emFile_SCB_SPI_CS_0_Write(0u);
            #endif /* (SPI_BLOCK_USED == UDB_SPI_BLOCK) */            

            break;

        #if (emFile_NUMBER_SD_CARDS >= 2u)

            case 1u:

                #if(SPI_BLOCK_USED == UDB_SPI_BLOCK)
                    emFile_UDB_SPI_CS_1_Write(0u);
                #else
                    emFile_SCB_SPI_CS_1_Write(0u);
                #endif /* (SPI_BLOCK_USED == UDB_SPI_BLOCK) */   

                break;

        #endif /* (emFile_NUMBER_SD_CARDS >= 2u) */

        #if (emFile_NUMBER_SD_CARDS >= 3u)

            case 2u:

                #if(SPI_BLOCK_USED == UDB_SPI_BLOCK)
                    emFile_UDB_SPI_CS_2_Write(0u);
                #else
                    emFile_SCB_SPI_CS_2_Write(0u);
                #endif /* (SPI_BLOCK_USED == UDB_SPI_BLOCK) */   

                break;

        #endif /* (emFile_NUMBER_SD_CARDS >= 3u) */

        #if (emFile_NUMBER_SD_CARDS == 4u)

            case 3u:

                #if(SPI_BLOCK_USED == UDB_SPI_BLOCK)
                    emFile_UDB_SPI_CS_3_Write(0u);
                #else
                    emFile_SCB_SPI_CS_3_Write(0u);
                #endif /* (SPI_BLOCK_USED == UDB_SPI_BLOCK) */   

                break;

        #endif /* (emFile_NUMBER_SD_CARDS == 4u) */

        default:

            #if(SPI_BLOCK_USED == UDB_SPI_BLOCK)
                emFile_UDB_SPI_CS_0_Write(0u);
            #else
                emFile_SCB_SPI_CS_0_Write(0u);
            #endif /* (SPI_BLOCK_USED == UDB_SPI_BLOCK) */   

            break;
    }
}


/*******************************************************************************
* Function Name: FS_MMC_HW_X_DisableCS
********************************************************************************
*
* Summary:
*  FS low level function. Clears the card slot inactive using the
*  chip select (CS) line.
*
* Parameters:
*  Unit      - Device Index.
*
* Return:
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
void FS_MMC_HW_X_DisableCS(U8 Unit)
{
    switch(Unit)
    {
    case 0u:
        #if(SPI_BLOCK_USED == UDB_SPI_BLOCK)
            emFile_UDB_SPI_CS_0_Write(1u);
        #else
            emFile_SCB_SPI_CS_0_Write(1u);
        #endif /* (SPI_BLOCK_USED == UDB_SPI_BLOCK) */
        
        break;

    #if (emFile_NUMBER_SD_CARDS >= 2u)

        case 1u:            
            #if(SPI_BLOCK_USED == UDB_SPI_BLOCK)
                emFile_UDB_SPI_CS_1_Write(1u);
            #else
                emFile_SCB_SPI_CS_1_Write(1u);
            #endif /* (SPI_BLOCK_USED == UDB_SPI_BLOCK) */

            break;

    #endif /* (emFile_NUMBER_SD_CARDS >= 2u) */

    #if (emFile_NUMBER_SD_CARDS >= 3u)

        case 2u:

            #if(SPI_BLOCK_USED == UDB_SPI_BLOCK)
                emFile_UDB_SPI_CS_2_Write(1u);
            #else
                emFile_SCB_SPI_CS_2_Write(1u);
            #endif /* (SPI_BLOCK_USED == UDB_SPI_BLOCK) */

            break;

    #endif /* (emFile_NUMBER_SD_CARDS >= 3u) */

    #if (emFile_NUMBER_SD_CARDS == 4u)

        case 3u:

            #if(SPI_BLOCK_USED == UDB_SPI_BLOCK)
                emFile_UDB_SPI_CS_3_Write(1u);
            #else
                emFile_SCB_SPI_CS_3_Write(1u);
            #endif /* (SPI_BLOCK_USED == UDB_SPI_BLOCK) */

            break;

    #endif /* (emFile_NUMBER_SD_CARDS == 4u) */

    default:

            #if(SPI_BLOCK_USED == UDB_SPI_BLOCK)
                emFile_UDB_SPI_CS_0_Write(1u);
            #else
                emFile_SCB_SPI_CS_0_Write(1u);
            #endif /* (SPI_BLOCK_USED == UDB_SPI_BLOCK) */
        
        break;
    }
}


/*******************************************************************************
* Function Name: FS_MMC_HW_X_IsWriteProtected
********************************************************************************
*
* Summary:
*  FS low level function. Returns the state of the physical write
*  protection of the SD cards.
*
* Parameters:
*  Unit      - Device Index.
*
* Return:
*    1       - the card is write protected;
*    0       - the card is not write protected.
*
* Reentrant:
*  No
*
*******************************************************************************/
int FS_MMC_HW_X_IsWriteProtected(U8 Unit)
{
   int wpState;

    switch(Unit)
    {
    case 0u:

        #if (emFile_WP0_EN)

            /* Based on physical switch state */
              wpState = (int)emFile_WP_0_Read();

        #else

            wpState = 0;

        #endif /* (emFile_WP0_EN) */

        break;

    #if (emFile_NUMBER_SD_CARDS >= 2u)

        case 1u:

            #if (emFile_WP1_EN)

                   /* Based on physical switch state */
                wpState = (int)emFile_WP_1_Read();

            #else

                wpState = 0;

            #endif /* (emFile_WP1_EN) */

            break;

    #endif /* (emFile_NUMBER_SD_CARDS >= 2u) */

    #if (emFile_NUMBER_SD_CARDS >= 3u)

        case 2u:

            #if (emFile_WP2_EN)

                  /* Based on physical switch state */
                wpState = (int)emFile_WP_2_Read();

            #else

                wpState = 0;

            #endif /* (emFile_WP2_EN) */

            break;

    #endif /* (emFile_NUMBER_SD_CARDS >= 3u) */

    #if (emFile_NUMBER_SD_CARDS == 4u)

        case 3u:

            #if (emFile_WP3_EN)

                /* Based on physical switch state */
                wpState = (int)emFile_WP_3_Read();

            #else

                wpState = 0;

            #endif /* (emFile_WP3_EN) */

            break;

    #endif /* (emFile_NUMBER_SD_CARDS == 4u) */

    default:

        #if (emFile_WP0_EN)

              /* Based on physical switch state */
            wpState = (int)emFile_WP_0_Read();

        #else

            wpState = 0;

        #endif /* (emFile_WP0_EN) */
        
        break;
    }

    return(wpState);
}


/*******************************************************************************
* Function Name: FS_MMC_HW_X_SetMaxSpeed
********************************************************************************
*
* Summary:
*  FS low level function. Sets the SPI interface to a maximum frequency.
*  Make sure that you set the frequency lower or equal but never higher
*  than the given value. Recommended startup frequency is 100kHz - 400kHz.
*
* Parameters:
*  Unit             - Device Index;
*  MaxFreq          - SPI clock frequency in kHz.
*
* Return:
*  max. frequency   - the maximum frequency set in kHz;
*  0                - the frequency could not be set.
*
* Reentrant:
*  No
*
*******************************************************************************/
U16 FS_MMC_HW_X_SetMaxSpeed(U8 Unit, U16 MaxFreq)
{
    U16 freq;
    U32 divResult;

    if(MaxFreq < emFile_STARTUP_FREQ)
    {
        MaxFreq = emFile_STARTUP_FREQ;
    }
    else if(MaxFreq > emFile_MAX_SPI_FREQ)
    {
        MaxFreq = emFile_MAX_SPI_FREQ;
    }
    else
    {
        /* Do nothing */
    }
    
    #if(SPI_BLOCK_USED == UDB_SPI_BLOCK)
        freq = MaxFreq << 1u;

        divResult = ((U32) CYDEV_BCLK__HFCLK__KHZ)/((U32) freq);

        switch(Unit)
        {
            case 0u:
               emFile_UDB_SPI_clk_1_Stop();
               emFile_UDB_SPI_clk_1_SetDividerValue((U16)divResult);    /* update the frequency */
               emFile_UDB_SPI_clk_1_Start();
                break;

            #if (emFile_NUMBER_SD_CARDS >= 2u)

            case 1u:

               emFile_UDB_SPI_clk_2_Stop();
               emFile_UDB_SPI_clk_2_SetDividerValue((U16)divResult);    /* update the frequency */
               emFile_UDB_SPI_clk_2_Start();
                break;

            #endif /* (emFile_NUMBER_SD_CARDS >= 2u) */

            #if (emFile_NUMBER_SD_CARDS >= 3u)

            case 2u:

               emFile_UDB_SPI_clk_3_Stop();
               emFile_UDB_SPI_clk_3_SetDividerValue((U16)divResult);    /* update the frequency */
               emFile_UDB_SPI_clk_3_Start();
                break;

            #endif /* (emFile_NUMBER_SD_CARDS >= 3u) */

            #if (emFile_NUMBER_SD_CARDS == 4u)

            case 3u:

               emFile_UDB_SPI_clk_4_Stop();
               emFile_UDB_SPI_clk_4_SetDividerValue((U16)divResult);    /* update the frequency */
               emFile_UDB_SPI_clk_4_Start();
                break;

            #endif /* (emFile_NUMBER_SD_CARDS == 4u) */

            default:
               emFile_UDB_SPI_clk_1_Stop();
               emFile_UDB_SPI_clk_1_SetDividerValue((U16)divResult);    /* update the frequency */
               emFile_UDB_SPI_clk_1_Start();
                break;
        }
    #elif(SPI_BLOCK_USED == SCB_SPI_BLOCK)
        freq = MaxFreq * SCB_SPI_OVERSAMPLING_FACTOR_GUI;

        divResult = ((U32) CYDEV_BCLK__HFCLK__KHZ)/((U32) freq);

        switch(Unit)
        {
            case 0u:
               
               emFile_SCB_SPI_clk_1_SetDividerValue((U16)divResult);    /* update the frequency */
               
                break;

            #if (emFile_NUMBER_SD_CARDS >= 2u)

            case 1u:

               
               emFile_SCB_SPI_clk_2_SetDividerValue((U16)divResult);    /* update the frequency */
               
                break;

            #endif /* (emFile_NUMBER_SD_CARDS >= 2u) */

            #if (emFile_NUMBER_SD_CARDS >= 3u)

            case 2u:

               
               emFile_SCB_SPI_clk_3_SetDividerValue((U16)divResult);    /* update the frequency */
               
                break;

            #endif /* (emFile_NUMBER_SD_CARDS >= 3u) */

            #if (emFile_NUMBER_SD_CARDS == 4u)

            case 3u:

               
               emFile_SCB_SPI_clk_4_SetDividerValue((U16)divResult);    /* update the frequency */
               
                break;

            #endif /* (emFile_NUMBER_SD_CARDS == 4u) */

            default:
               
               emFile_SCB_SPI_clk_1_SetDividerValue((U16)divResult);    /* update the frequency */
               
                break;
        }        
    #endif /* (SPI_BLOCK_USED == UDB_SPI_BLOCK) */

    return (MaxFreq);

}


/*******************************************************************************
* Function Name: FS_MMC_HW_X_SetVoltage
********************************************************************************
*
* Summary:
*  FS low level function. Be sure that your card slot si within the given
*  voltage range. Return 1 if your slot can support the required voltage,
*  and if not, return 0.
*
* Parameters:
*  Unit             - Device Index;
*  Vmin             - Minimum supply voltage in mV;
*  Vmin             - Maximum supply voltage in mV.
*
* Return:
*  1                - the card slot supports the voltage range;
*  0                - the card slot does not support the voltage range.
*
* Reentrant:
*  No
*
*******************************************************************************/
int FS_MMC_HW_X_SetVoltage(U8 Unit, U16 Vmin, U16 Vmax)
{
    int result;

    switch(Unit)
    {
    case 0u:

    case 1u:

    case 2u:

    case 3u:

        if((Vmin <= emFile_MMC_DEFAULT_SUPPLY_VOLTAGE) &&
            (emFile_MMC_DEFAULT_SUPPLY_VOLTAGE <= Vmax))
        {
            result = emFile_RET_SUCCCESS;
        }
        else
        {
            result = emFile_RET_FAIL;
        }

        break;

    default:

        if((Vmin <= emFile_MMC_DEFAULT_SUPPLY_VOLTAGE) &&
            (emFile_MMC_DEFAULT_SUPPLY_VOLTAGE <= Vmax))
        {
            result = emFile_RET_SUCCCESS;
        }
        else
        {
            result = emFile_RET_FAIL;
        }
        
        break;
    }

    return(result);
}


/*******************************************************************************
* Function Name: FS_MMC_HW_X_IsPresent
********************************************************************************
*
* Summary:
*  Returns the state of the media. If you do not know the state, return
*  FS_MEDIA_STATE_UNKNOWN and the higher layer will try to figure out if
*  a media is present.
*
* Parameters:
*  Unit                      - Device Index.
*
* Return:
*  FS_MEDIA_STATE_UNKNOWN    - Media state is unknown;
*  FS_MEDIA_NOT_PRESENT      - Media is not present;
*  FS_MEDIA_IS_PRESENT       - Media is present.
*
* Reentrant:
*  No
*
*******************************************************************************/
int FS_MMC_HW_X_IsPresent(U8 Unit)
{
     int result;

    emFile_Init(Unit);

    switch(Unit)
    {
    case 0u:

    case 1u:

    case 2u:

    case 3u:

        result = FS_MEDIA_STATE_UNKNOWN;
        break;

    default:

        result = FS_MEDIA_STATE_UNKNOWN;
        break;
    }

    return(result);
}


/*******************************************************************************
* Function Name: FS_MMC_HW_X_Read
********************************************************************************
*
* Summary:
*  FS low level function. Reads a specified number of bytes from MMC card to 
*  buffer.
*
* Parameters:
*    Unit             - Device Index;
*    pData            - Pointer to a data buffer;
*    NumBytes         - Number of bytes.
*
* Return:
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
void  FS_MMC_HW_X_Read (U8 Unit, U8 * pData, int NumBytes)
{
    do
    {
        *pData++ = emFile_ReadWriteSPI(Unit, 0xff);
    } while (--NumBytes);
}

/*******************************************************************************
* Function Name: FS_MMC_HW_X_Write
********************************************************************************
*
* Summary:
*  FS low level function. Writes a specified number of bytes from
*  data buffer to the MMC/SD card.
*
* Parameters:
*    Unit             - Device Index;
*    pData            - Pointer to a data buffer;
*    NumBytes         - Number of bytes.
*
* Return:
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
void  FS_MMC_HW_X_Write(U8 Unit, const U8 * pData, int NumBytes) 
{
    do
    {
        emFile_ReadWriteSPI(Unit, *pData++);
    } while (--NumBytes);
}



/* [] END OF FILE */
