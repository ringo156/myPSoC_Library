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
#include "ssd1306.h"
#include "bme280.h"
#include "mpu6050.h"
#include <stdio.h>

#define DISPLAY_ADDRESS 0x3C
#define BME280_ADDR  0x76
#define numberOfTests   100

void output_uint8(uint8 res);
void init(bme280_calib_data *data);

int16_t CAX, CAY, CAZ; //current acceleration values
int16_t CGX, CGY, CGZ; //current gyroscope values
int16_t CT;            //current temperature
   
float   AXoff, AYoff, AZoff; //accelerometer offset values
float   GXoff, GYoff, GZoff; //gyroscope offset values

float   AX, AY, AZ; //acceleration floats
float   GX, GY, GZ; //gyroscope floats

int main(void)
{
    int32_t get, mV;
    uint32 id;
    uint32 status;
    int16_t temp;
    uint8 data[36] = {0};
    signed long int temp_cal, press_cal;
    double temp_act = 0.0, press_act;
    char val[50];
    bme280_calib_data test;
    
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    init(&test);  

    for(;;)
    {
        
        read_data();
        temp_cal = calibration_T(&test, temp_raw);
        press_cal = calibration_P(&test, pres_raw);
        press_act = (double)press_cal / 100.0;
        temp_act = (double)temp_cal / 100.0;
        
        sprintf(val, "TEMP:%2.2f\n", temp_act);
        UART_1_PutString(val);
        /*
        display_clear();
        gfx_setCursor(0,0);
        gfx_print(val);
        */
        //
        //sprintf(val, "temp:%2.2d", temp);
        //gfx_print(val);
        //display_update();
        //CyDelay(10);

        
            
        CyDelay(500);

    }
}

void init(bme280_calib_data *data){
    uint8_t osrs_t = 1;             //Temperature oversampling x 1
    uint8_t osrs_p = 1;             //Pressure oversampling x 1
    uint8_t osrs_h = 1;             //Humidity oversampling x 1
    uint8_t mode = 3;               //Normal mode
    uint8_t t_sb = 5;               //Tstandby 1000ms
    uint8_t filter = 0;             //Filter off 
    uint32 id;
    char buf[40];
    uint16 i;
    
    ADC_DelSig_1_Start();
    I2C_Start();
    UART_1_Start();
    UART_1_PutString("Hello World\n");
    display_init(DISPLAY_ADDRESS);
    display_clear();
    gfx_setTextSize(2);
    gfx_setTextColor(WHITE);
    gfx_setCursor(0,0);
    gfx_println("hello");
    display_update();
    CyDelay(100);
    bme280_init(data, BME280_ADDR, t_sb, filter, osrs_t, osrs_p, osrs_h, mode);
        
    //id = bme280_read_ID();
    //sprintf(buf, "ID = %lu\n", id);
    //UART_1_PutString(buf);
    
}

void output_uint8(uint8 res){
    char val[30];

    sprintf(val, "%d\n", res);
    UART_1_PutString(val);
}

/* [] END OF FILE */
