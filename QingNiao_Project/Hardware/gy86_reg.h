#ifndef __GY86_REG_H
#define __GY86_REG_H

//HMC5883L_NAME
#define HMC5883L_READ_ADDRESS 0x3D
#define HMC5883L_WRITE_ADDRESS 0x3C
//HMC5883L寄存器地址
#define HMC5883L_CON_REG_A									0x00
#define HMC5883L_CON_REG_B									0x01
#define HMC5883L_MODE_REG										0x02

#define HMC5883L_DATA_OUTPUT_X_MSB_REG			0x03
#define HMC5883L_DATA_OUTPUT_X_LSB_REG			0x04
#define HMC5883L_DATA_OUTPUT_Z_MSB_REG			0x05
#define HMC5883L_DATA_OUTPUT_Z_LSB_REG			0x06
#define HMC5883L_DATA_OUTPUT_Y_MSB_REG			0x07
#define HMC5883L_DATA_OUTPUT_Y_LSB_REG			0x08

#define HMC5883L_STATUS_REG									0x09
#define HMC5883L_IDENT_REG_A								0x10
#define HMC5883L_IDENT_REG_B								0x11
#define HMC5883L_IDENT_REG_C								0x12

//MPU6000_NAME
#define MPU6000_ADDRESS 0xD0
//MPU6000寄存器地址
#define MPU6000_SMPRT_DIV                   0x19  //用于指定生成采样率的陀螺仪输出速率的分频器
#define MPU6000_CONFIG                      0x1A
#define MPU6000_GYRO_CONFIG                 0x1B  //陀螺仪自检
#define MPU6000_ACCEL_CONFIG                0x1C  //加速度计自检

#define MPU6000_PWR_MGMT_1                  0x6B
#define MPU6000_PWR_MGMT_2                  0x6C
#define MPU6000_WHO_AM_I                    0x75

#define MPU6000_ACCEL_XOUT_H                0x3B
#define MPU6000_ACCEL_XOUT_L                0x3C
#define MPU6000_ACCEL_YOUT_H                0x3D
#define MPU6000_ACCEL_YOUT_L                0x3E
#define MPU6000_ACCEL_ZOUT_H                0x3F
#define MPU6000_ACCEL_ZOUT_L                0x40
#define MPU6000_GYRO_XOUT_H                 0x43
#define MPU6000_GYRO_XOUT_L                 0x44
#define MPU6000_GYRO_YOUT_H                 0x45
#define MPU6000_GYRO_YOUT_L                 0x46
#define MPU6000_GYRO_ZOUT_H                 0x47
#define MPU6000_GYRO_ZOUT_L                 0x48

#define MPU6000_INT_PIN_CFG                 0x37
#define MPU6000_USER_CTRL                   0x6A


#endif

