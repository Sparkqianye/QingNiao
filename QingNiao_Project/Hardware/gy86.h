#include "stm32f4xx.h"                  // Device header

void I2C_WriteReg(uint8_t NAMEWriteAddress,uint8_t RegAddress,uint8_t Data);

uint8_t I2C_ReadReg(uint8_t NAMEWriteAddress,uint8_t NAMEReadAddress,uint8_t RegAddress);

void HMC5883L_Init(void);

void MPU6000_Init(void);

void GY86_Init(void);

void HMC5883L_GetData(int16_t*AccX,int16_t*AccY,int16_t*AccZ);

void MPU6000_GetData(int16_t*AccX,int16_t*AccY,int16_t*AccZ,int16_t*GyroX,int16_t*GyroY,int16_t*GyroZ);

uint8_t MPU6000_GetID(void);

uint8_t HMC5883L_GetState(void);

