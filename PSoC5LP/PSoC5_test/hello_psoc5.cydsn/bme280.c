// bme280.c

#include <project.h>
#include <stdlib.h>
#include <math.h>
#include "bme280.h"

// I2C result status
#define TRANSFER_CMPLT    (0x00u)
#define TRANSFER_ERROR    (0xFFu)

static uint8 _i2caddr;

void bme280_init(bme280_calib_data *data, uint8 i2caddr, uint8 Stanby_t, 
    uint8 filter, uint8 overS_T, uint8 overS_P, uint8 overS_H, uint8 mode)
{
    uint8 ID;
    uint8 ctrl_meas = (overS_T << 5) | (overS_P << 2) | mode;
    uint8 config    = (Stanby_t << 5) | (filter << 2);
    uint8 ctrl_hum  = overS_H;
    _i2caddr = i2caddr;

    ID = bme280_ReadReg(WHO_I_AM);
    if(ID != 0x60)
    {
        return;
    }
    //modd
    bme280_WriteReg(CTRL_HUM, 0x01);
    bme280_WriteReg(CTRL_MEAS, 0x27);
    bme280_WriteReg(CONFIG, 0xA0);

    //Calibration data
    bme280_readCoefficients(data);

}

// example bme280_write_buf( cmdbuf, sizeof(cmdbuf) ); 
static uint32 bme280_write_buf( uint8* buf, uint16_t size )
{
    
    uint32 status = TRANSFER_ERROR;
    uint32 i;

    status = I2C_MasterSendStart(_i2caddr, I2C_WRITE_XFER_MODE);
    if(I2C_MSTR_NO_ERROR == status)
    {
        for(i = 0; i<size; i++)
        {
            status = I2C_MasterWriteByte(buf[i]);
            if(status != I2C_MSTR_NO_ERROR)
            {
                break;
            }
        }
    }
    I2C_MasterSendStop();

    if( 0u == (I2C_MSTAT_ERR_XFER & I2C_MasterStatus()) ){
        // Check if all bytes was written 
        if( I2C_MasterGetWriteBufSize() == size ){
            status = TRANSFER_CMPLT;
        }
    }
    I2C_MasterClearStatus();

    return status;
}

void bme280_WriteReg(uint8 reg, uint8 value){
    uint8 Write_Buf[2]={0};
    Write_Buf[0]=reg;
    Write_Buf[1]=value;
    
    I2C_MasterWriteBuf(_i2caddr,(uint8 *)Write_Buf,2,I2C_MODE_COMPLETE_XFER);
    while((I2C_MasterStatus() & I2C_MSTAT_WR_CMPLT)==0){}
    
    return;
}

uint8 bme280_ReadReg(uint8 reg)
{
    uint8 Write_Buf[1]={0};
    Write_Buf[0]=reg;
    
    uint8 Read_Buf[1]={0};
    
    //Step1
    I2C_MasterWriteBuf(_i2caddr,(uint8 *)Write_Buf,1,I2C_MODE_NO_STOP);
    while((I2C_MasterStatus() & I2C_MSTAT_WR_CMPLT)==0){}
    
    //Step2
    I2C_MasterReadBuf(_i2caddr,(uint8 *)Read_Buf,1,I2C_MODE_REPEAT_START);
    while((I2C_MasterStatus() & I2C_MSTAT_RD_CMPLT)==0){}
    
    return Read_Buf[0];
}

void bme280_readCoefficients(bme280_calib_data *data)
{
    uint32 val[32] = {0};
    uint8 i = 0, j = 0, reg;
    reg = BME280_REGISTER_DIG_T1;
    //H1までread
    for(i=0;i<25;i++){
        val[i] = bme280_ReadReg(reg + i);
    }
    //H2~
    reg = BME280_REGISTER_DIG_H2;
    for(i=25;i<32;i++){
        val[i] = bme280_ReadReg(reg + j);
        j++;
    }
    
    data -> dig_T1 = (val[1] << 8) | val[0];
    data -> dig_T2 = (val[3] << 8) | val[2];
    data -> dig_T3 = (val[5] << 8) | val[4];
    data -> dig_P1 = (val[7] << 8) | val[6];
    data -> dig_P2 = (val[9] << 8) | val[8];
    data -> dig_P3 = (val[11]<< 8) | val[10];
    data -> dig_P4 = (val[13]<< 8) | val[12];
    data -> dig_P5 = (val[15]<< 8) | val[14];
    data -> dig_P6 = (val[17]<< 8) | val[16];
    data -> dig_P7 = (val[19]<< 8) | val[18];
    data -> dig_P8 = (val[21]<< 8) | val[20];
    data -> dig_P9 = (val[23]<< 8) | val[22];
    data -> dig_H1 = (uint8)val[24];
    data -> dig_H2 = (val[26]<< 8) | val[25];
    data -> dig_H3 =  val[27];
    data -> dig_H4 = (val[28]<< 4) | (0x0F & val[29]);
    data -> dig_H5 = (val[30] << 4) | ((val[29] >> 4) & 0x0F); 
    data -> dig_H6 =  val[31];
    
}

void read_data(void)
{
    uint32 val[8];
    uint8 i, reg;
    reg = OUT_P_MSB;
    for(i=0;i<8;i++){
        val[i] = bme280_ReadReg(reg + i);
    }
    pres_raw = (val[0] << 12) | (val[1] << 4) | (val[2] >> 4);
    temp_raw = (val[3] << 12) | (val[4] << 4) | (val[5] >> 4);
    hum_raw  = (val[6] << 8) | val[7];
}

signed long int calibration_T(bme280_calib_data *data, signed long int adc_T)
{
    
    signed long int var1, var2, T;
    var1 = ((((adc_T >> 3) - ((signed long int)data -> dig_T1<<1))) * ((signed long int)data -> dig_T2)) >> 11;
    var2 = (((((adc_T >> 4) - ((signed long int)data -> dig_T1)) * ((adc_T>>4) - ((signed long int)data -> dig_T1))) >> 12) * ((signed long int)data -> dig_T3)) >> 14;
    
    t_fine = var1 + var2;
    T = (t_fine * 5 + 128) >> 8;
    return T; 
}

unsigned long int calibration_P(bme280_calib_data *data, signed long int adc_P)
{
    signed long int var1, var2;
    unsigned long int P;
    var1 = (((signed long int)t_fine)>>1) - (signed long int)64000;
    var2 = (((var1>>2) * (var1>>2)) >> 11) * ((signed long int)data -> dig_P6);
    var2 = var2 + ((var1*((signed long int)data -> dig_P5))<<1);
    var2 = (var2>>2)+(((signed long int)data -> dig_P4)<<16);
    var1 = (((data -> dig_P3 * (((var1>>2)*(var1>>2)) >> 13)) >>3) + ((((signed long int)data -> dig_P2) * var1)>>1))>>18;
    var1 = ((((32768+var1))*((signed long int)data -> dig_P1))>>15);
    if (var1 == 0)
    {
        return 0;
    }    
    P = (((unsigned long int)(((signed long int)1048576)-adc_P)-(var2>>12)))*3125;
    if(P<0x80000000)
    {
       P = (P << 1) / ((unsigned long int) var1);   
    }
    else
    {
        P = (P / (unsigned long int)var1) * 2;    
    }
    var1 = (((signed long int)data -> dig_P9) * ((signed long int)(((P>>3) * (P>>3))>>13)))>>12;
    var2 = (((signed long int)(P>>2)) * ((signed long int)data -> dig_P8))>>13;
    P = (unsigned long int)((signed long int)P + ((var1 + var2 + data -> dig_P7) >> 4));
    return P;
}

double ReadAltitude(double SeaLevel_Pres, double pressure)
{
    double altitude = 44330.0 * (1.0 - pow(pressure / SeaLevel_Pres, (1.0/5.255)));  
    return altitude;
}


unsigned long int calibration_H(bme280_calib_data *data, signed long int adc_H)
{
    signed long int v_x1;
    
    v_x1 = (t_fine - ((signed long int)76800));
    v_x1 = (((((adc_H << 14) -(((signed long int)data -> dig_H4) << 20) - (((signed long int)data -> dig_H5) * v_x1)) + 
              ((signed long int)16384)) >> 15) * (((((((v_x1 * ((signed long int)data -> dig_H6)) >> 10) * 
              (((v_x1 * ((signed long int)data -> dig_H3)) >> 11) + ((signed long int) 32768))) >> 10) + (( signed long int)2097152)) * 
              ((signed long int) data -> dig_H2) + 8192) >> 14));
   v_x1 = (v_x1 - (((((v_x1 >> 15) * (v_x1 >> 15)) >> 7) * ((signed long int)data -> dig_H1)) >> 4));
   v_x1 = (v_x1 < 0 ? 0 : v_x1);
   v_x1 = (v_x1 > 419430400 ? 419430400 : v_x1);
   return (unsigned long int)(v_x1 >> 12);   
}