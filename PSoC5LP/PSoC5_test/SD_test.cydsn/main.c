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
#include "FS.h"

int main(void)
{
    char sdVolName[10];
    FS_FILE *pFile;
    CyGlobalIntEnable; /* Enable global interrupts. */
    LED_Write(1);
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    UART_Start();
    UART_PutString("PSoC5lp Start\n");
    FS_Init();
    FS_GetVolumeName(0u, &sdVolName[0], 9u);
    UART_PutString(sdVolName);
    UART_PutString("\n");
    CyDelay(100);
    FS_FormatSD(sdVolName);
    UART_PutString("SDFormat\n");
    CyDelay(100);
    FS_MkDir("Dir");
    CyDelay(100);
    pFile = FS_FOpen("Test.txt", "w");
    CyDelay(100);
    //pFile = FS_FOpen("\\Dir\\Test.txt", "w");
    FS_Write(pFile, "Hello SD", 8u);
    CyDelay(100);
    FS_FClose(pFile);
    
    LED_Write(0);

    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
