#ifndef GAUSSNEWTON_H
#define GAUSSNEWTON_H

#include <stdint.h>
#include <math.h>

#define G 9.81

extern double mpuX,mpuY,mpuZ,gyroX,gyroY,gyroZ;
extern double mpuX_correction,mpuY_correction,mpuZ_correction,gyroX_correction,gyroY_correction,gyroZ_correction;


// 理想加速度矩阵
extern double ideal_a_matrix[6][3];

// 测量值矩阵
extern double measure[6][3];

// 差值矩阵
extern double diff[6][3];

// 当前索引
extern uint8_t current_index;

// 残差矩阵
extern double residual[6];

// Δβ, βα, β 矩阵
extern double delta[6];
extern double Beta_alpha[6];
extern double Beta[6];

// Jacobian 矩阵及其相关矩阵
extern double Jr[6][6];
extern double Jr_T_Jr[6][6];
extern double Jr_T_R[6];
extern double J_invert[6][6];

// 初始化测量和差值矩阵
void measure_diff_a_init();

// 初始化残差矩阵
void DR_a_init(double data_ax, double data_ay, double data_az);

// 初始化 Δβ, βα, β 矩阵
void delta_Beta_init();

// 初始化 Jacobian 矩阵及其相关矩阵
void J_a_init();

void GuassNewton_init();

// 高斯牛顿迭代算法
void GaussNewton();

// 矩阵求逆函数
int invert_matrix(double A[6][6], double invA[6][6], int n);

#endif // GAUSSNEWTON_H
