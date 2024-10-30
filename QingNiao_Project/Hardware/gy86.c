#include "stm32f4xx.h"                  // Device header
#include "My_I2C.h"
#include "gy86_reg.h"
#include "Delay.h"

void I2C_WriteReg(uint8_t NAMEWriteAddress,uint8_t RegAddress,uint8_t Data)
{
    MyI2C_Start();
		MyI2C_SendByte(NAMEWriteAddress);
		MyI2C_ReceiveAck();
		MyI2C_SendByte(RegAddress);
		MyI2C_ReceiveAck();
		MyI2C_SendByte(Data);
		MyI2C_ReceiveAck();
		MyI2C_Stop();
}

uint8_t I2C_ReadReg(uint8_t NAMEWriteAddress,uint8_t NAMEReadAddress,uint8_t RegAddress)
{
		uint8_t Data;
		
		MyI2C_Start();
		MyI2C_SendByte(NAMEWriteAddress);
		MyI2C_ReceiveAck();
		MyI2C_SendByte(RegAddress);
		MyI2C_ReceiveAck();
		
		MyI2C_Start();
		MyI2C_SendByte(NAMEReadAddress | 0x01);
		MyI2C_ReceiveAck();
		Data = MyI2C_ReceiveByte();
		MyI2C_SendAck(1);
    MyI2C_Stop();
				
		return Data;
}

void HMC5883L_Init(void)
{
	MyI2C_Init();
	
	I2C_WriteReg(HMC5883L_WRITE_ADDRESS,HMC5883L_CON_REG_A,0x70);
	I2C_WriteReg(HMC5883L_WRITE_ADDRESS,HMC5883L_CON_REG_B,0x40);
	I2C_WriteReg(HMC5883L_WRITE_ADDRESS,HMC5883L_MODE_REG	,0x00);
}

void MPU6000_Init(void)
{
	MyI2C_Init();
	
	I2C_WriteReg(MPU6000_ADDRESS,MPU6000_PWR_MGMT_1,0x01);
	I2C_WriteReg(MPU6000_ADDRESS,MPU6000_PWR_MGMT_2,0x00);
	I2C_WriteReg(MPU6000_ADDRESS,MPU6000_SMPRT_DIV,0x09);
	I2C_WriteReg(MPU6000_ADDRESS,MPU6000_CONFIG	,0x06);
	I2C_WriteReg(MPU6000_ADDRESS,MPU6000_GYRO_CONFIG,0x18);
	I2C_WriteReg(MPU6000_ADDRESS,MPU6000_ACCEL_CONFIG,0x18);
  I2C_WriteReg(MPU6000_ADDRESS,MPU6000_INT_PIN_CFG,0x02);
  I2C_WriteReg(MPU6000_ADDRESS,MPU6000_USER_CTRL,0x00);
  
}

void GY86_Init(void)
{
  HMC5883L_Init();
  MPU6000_Init();
}

void HMC5883L_GetData(int16_t*AccX,int16_t*AccY,int16_t*AccZ)
{
	uint8_t DataM,DataL;
	
	DataM = I2C_ReadReg(HMC5883L_WRITE_ADDRESS,HMC5883L_READ_ADDRESS,HMC5883L_DATA_OUTPUT_X_MSB_REG);
	DataL = I2C_ReadReg(HMC5883L_WRITE_ADDRESS,HMC5883L_READ_ADDRESS,HMC5883L_DATA_OUTPUT_X_LSB_REG);
	*AccX = (DataM << 8 | DataL);
	
	DataM = I2C_ReadReg(HMC5883L_WRITE_ADDRESS,HMC5883L_READ_ADDRESS,HMC5883L_DATA_OUTPUT_Y_MSB_REG);
	DataL = I2C_ReadReg(HMC5883L_WRITE_ADDRESS,HMC5883L_READ_ADDRESS,HMC5883L_DATA_OUTPUT_Y_LSB_REG);
	*AccY = (DataM << 8 | DataL);
	
	
	DataM = I2C_ReadReg(HMC5883L_WRITE_ADDRESS,HMC5883L_READ_ADDRESS,HMC5883L_DATA_OUTPUT_Z_MSB_REG);
	DataL = I2C_ReadReg(HMC5883L_WRITE_ADDRESS,HMC5883L_READ_ADDRESS,HMC5883L_DATA_OUTPUT_Z_LSB_REG);
	*AccZ = (DataM << 8 | DataL);

}

void MPU6000_GetData(int16_t*AccX,int16_t*AccY,int16_t*AccZ,int16_t*GyroX,int16_t*GyroY,int16_t*GyroZ)
{
	uint8_t DataH,DataL;
	
	DataH = I2C_ReadReg(MPU6000_ADDRESS,MPU6000_ADDRESS,MPU6000_ACCEL_XOUT_H);
	DataL = I2C_ReadReg(MPU6000_ADDRESS,MPU6000_ADDRESS,MPU6000_ACCEL_XOUT_L);
	*AccX = (DataH << 8 | DataL);
	
	DataH = I2C_ReadReg(MPU6000_ADDRESS,MPU6000_ADDRESS,MPU6000_ACCEL_YOUT_H);
	DataL = I2C_ReadReg(MPU6000_ADDRESS,MPU6000_ADDRESS,MPU6000_ACCEL_YOUT_L);
	*AccY = (DataH << 8 | DataL);
	
	DataH = I2C_ReadReg(MPU6000_ADDRESS,MPU6000_ADDRESS,MPU6000_ACCEL_ZOUT_H);
	DataL = I2C_ReadReg(MPU6000_ADDRESS,MPU6000_ADDRESS,MPU6000_ACCEL_ZOUT_L);
	*AccZ = (DataH << 8 | DataL);
  
  DataH = I2C_ReadReg(MPU6000_ADDRESS,MPU6000_ADDRESS,MPU6000_GYRO_XOUT_H);
	DataL = I2C_ReadReg(MPU6000_ADDRESS,MPU6000_ADDRESS,MPU6000_GYRO_XOUT_L);
	*GyroX = (DataH << 8 | DataL);
  
  DataH = I2C_ReadReg(MPU6000_ADDRESS,MPU6000_ADDRESS,MPU6000_GYRO_YOUT_H);
	DataL = I2C_ReadReg(MPU6000_ADDRESS,MPU6000_ADDRESS,MPU6000_GYRO_YOUT_L);
	*GyroY = (DataH << 8 | DataL);
  
  DataH = I2C_ReadReg(MPU6000_ADDRESS,MPU6000_ADDRESS,MPU6000_GYRO_ZOUT_H);
	DataL = I2C_ReadReg(MPU6000_ADDRESS,MPU6000_ADDRESS,MPU6000_GYRO_ZOUT_L);
	*GyroZ = (DataH << 8 | DataL);
	
}

uint8_t MPU6000_GetID(void)
{
	return I2C_ReadReg(MPU6000_ADDRESS,MPU6000_ADDRESS,MPU6000_WHO_AM_I);
}

uint8_t HMC5883L_GetState(void)
{
  return I2C_ReadReg(HMC5883L_WRITE_ADDRESS,HMC5883L_READ_ADDRESS,HMC5883L_STATUS_REG);
}
