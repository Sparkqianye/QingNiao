#ifndef GAUSSNEWTON_H
#define GAUSSNEWTON_H

#include <stdint.h>
#include <math.h> 

 extern float aX,aY,aZ,gyX,gyY,gyZ;
 extern float aX_correction,aY_correction,aZ_correction,gyroX_correction,gyroY_correction,gyroZ_correction;


// 理想加速度矩阵
extern float ideal_a_matrix[6][3];

// 测量值矩阵
extern float measure[6][3];

// 差值矩阵
extern float diff[6][3];

// 当前索引
extern uint8_t current_index;

// 残差矩阵
extern float residual[6];

// Δβ, βα, β 矩阵
extern float delta[6];
extern float Beta_alpha[6];
extern float Beta[6];

// Jacobian 矩阵及其相关矩阵
extern float Jr[6][6];
extern float Jr_T_Jr[6][6];
extern float Jr_T_R[6];
extern float J_invert[6][6];

// 初始化测量和差值矩阵
void measure_diff_a_init();

// 初始化残差矩阵
void DR_a_init(float data_ax, float data_ay, float data_az);

// 初始化 Δβ, βα, β 矩阵
void delta_Beta_init();

// 初始化 Jacobian 矩阵及其相关矩阵
void J_a_init();

void GuassNewton_init();

// 高斯牛顿迭代算法
void GaussNewton();

// 矩阵求逆函数
int invert_matrix(float A[6][6], float invA[6][6], int n);


void a_correction(float ax, float ay, float az);

#endif // GAUSSNEWTON_H
