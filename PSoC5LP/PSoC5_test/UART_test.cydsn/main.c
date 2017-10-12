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

int main(void)
{
    uint8 sw_flag;
    char uartchar;
    CyGlobalIntEnable; /* Enable global interrupts. */
    UART_1_Start();

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    UART_1_PutString("HelloWorld\n");
    for(;;)
    {
        /* Place your application code here. */
        uartchar = UART_1_GetChar();

        if (uartchar != 0)
        {
            UART_1_PutChar(uartchar);
            
            switch (uartchar)
            {
                case 'a':
                case 'A':
                { 
                    UART_1_PutString("\n push a \n"); break;
                }; break;
                
                case 'b':
                case 'B':
                { 
                    UART_1_PutString("\n push b :>"); break;
                }; break;
                    
                case '?': 
                    UART_1_PutString("Why hogehoge\n"); break;
                     
                case 'Y':
                    {}; break;
                    
                case 'Z':
                    {}; break;
                    
                default:
                    UART_1_PutString("\nSelect test :>"); break;
            }
        }
        if(SW_Read()==0)
            {
                if(sw_flag)
                {
                    UART_1_PutString("push button\n");
                }
                sw_flag = 0;
            }
            else
            {
                sw_flag = 1;
            }
    }
}

/* [] END OF FILE */
