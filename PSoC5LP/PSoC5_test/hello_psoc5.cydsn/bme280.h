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

#ifndef _BME280_H
#define _BME280_H

#define BME280_REGISTER_DIG_T1  0x88
#define BME280_REGISTER_DIG_T2  0x8A
#define BME280_REGISTER_DIG_T3  0x8C

#define BME280_REGISTER_DIG_P1  0x8E
#define BME280_REGISTER_DIG_P2  0x90
#define BME280_REGISTER_DIG_P3  0x92
#define BME280_REGISTER_DIG_P4  0x94
#define BME280_REGISTER_DIG_P5  0x96
#define BME280_REGISTER_DIG_P6  0x98
#define BME280_REGISTER_DIG_P7  0x9A
#define BME280_REGISTER_DIG_P8  0x9C
#define BME280_REGISTER_DIG_P9  0x9E

#define BME280_REGISTER_DIG_H1  0xA1
#define BME280_REGISTER_DIG_H2  0xE1
#define BME280_REGISTER_DIG_H3  0xE3
#define BME280_REGISTER_DIG_H4  0xE4
#define BME280_REGISTER_DIG_H5  0xE5
#define BME280_REGISTER_DIG_H6  0xE7

#define WHO_I_AM    0xD0
#define CTRL_HUM    0xF2
#define CTRL_MEAS   0xF4
#define CONFIG      0xF5
#define OUT_P_MSB   0xF7
#define OUT_P_LSB   0xF8
#define OUT_P_XLSB  0xF9
#define OUT_T_MSB   0xFA
#define OUT_T_LSB   0xFB
#define OUT_T_XLSB  0xFC
#define OUT_H_MSB   0xFD
#define OUT_H_LSB   0xFE

unsigned long int hum_raw, temp_raw, pres_raw, t_fine;

typedef struct
{
  uint16_t dig_T1;
  int16_t  dig_T2;
  int16_t  dig_T3;
  
  uint16_t dig_P1;
  int16_t  dig_P2;
  int16_t  dig_P3;
  int16_t  dig_P4;
  int16_t  dig_P5;
  int16_t  dig_P6;
  int16_t  dig_P7;
  int16_t  dig_P8;
  int16_t  dig_P9;
  
  uint8_t  dig_H1;
  int16_t  dig_H2;
  uint8_t  dig_H3;
  int16_t  dig_H4;
  int16_t  dig_H5;
  int8_t   dig_H6;
} bme280_calib_data;

void output_uint8(uint8 res);
void bme280_init(bme280_calib_data *data, uint8 i2caddr, uint8 Stanby_t, 
    uint8 filter, uint8 overS_T, uint8 overS_P, uint8 overS_H, uint8 mode);
void bme280_readCoefficients(bme280_calib_data *data);
void read_data(void);

signed long int calibration_T(bme280_calib_data *data, signed long int adc_T);
unsigned long int calibration_P(bme280_calib_data *data, signed long int adc_P);
unsigned long int calibration_H(bme280_calib_data *data, signed long int adc_H);
double ReadAltitude(double SeaLevel_Pres, double pressure);
static uint32 bme280_write_buf( uint8* buf, uint16_t size );
void bme280_WriteReg(uint8 reg, uint8 value);
uint8 bme280_ReadReg(uint8 reg);

#endif // _BME280_H