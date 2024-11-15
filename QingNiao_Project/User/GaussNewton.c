#include "GaussNewton.h"
#include "stm32f4xx.h" 
#include <stdio.h>
#include <math.h>

#define G 1.00

int invert_flag = 2;

float ideal_a_matrix[6][3] = {
    {0, 0, G},
    {0, 0,-G},
    {0, G, 0},
    {0,-G, 0},
    {G, 0, 0},
    {-G, 0, 0}
};

float measure[6][3] = {0};

//diff matrix 赋值
float diff[6][3] = {0};

void measure_diff_a_init()
{
    for(int i = 0; i < 6; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            diff[i][j] = 0.0;
            measure[i][j] = 0.0;
        }
    }
}


//for delta Beta Beta_alpha matrix
float delta[6] = {0.0};
float Beta_alpha[6] = {0};
float Beta[6] = {0};

void delta_Beta_init()
{
    for(int i = 0; i < 3; i++)
    {
        Beta_alpha[i] = 0.0;
        Beta[i] = 0.0;
        delta[i] = 0.0;
    }
    for(int i = 3; i < 6; i++)
    {
        Beta_alpha[i] = 1.0;
        Beta[i] = 1.0;
        delta[i] = 0.0;
    }
}



uint8_t current_index = 0;

//matrix residual 赋值, residual为某特定解下方程的误差 
float residual[6];
void DR_a_init(float data_ax, float data_ay, float data_az)
{
    current_index = current_index % 6;

    measure[current_index][0] = data_ax;
    measure[current_index][1] = data_ay;
    measure[current_index][2] = data_az;

    diff[current_index][0] = (measure[current_index][0] - Beta[0])*Beta[3];
    diff[current_index][1] = (measure[current_index][1] - Beta[1])*Beta[4];
    diff[current_index][2] = (measure[current_index][2] - Beta[2])*Beta[5];

    residual[current_index] = 1-diff[current_index][0]*diff[current_index][0]
                                -diff[current_index][1]*diff[current_index][1]
                                -diff[current_index][2]*diff[current_index][2];
    current_index++;
}

//初解βα
//β = βα - [ J_r^T * J_r ]^-1   *   [J_r^T * R]
//delta = [Jr(βα)^T Jr(βα)]^-1  Jr(βα)^T r(βα)


float Jr[6][6];
//Jr(βα)^T Jr(βα) 6x6 6x6 = 6x6
float Jr_T_Jr[6][6] = {0};
//Jr(βα)^T r(βα) 6x6 6x1 = 6x1 r为某特定解下方程的误差
float Jr_T_R[6] = {0};

float J_invert[6][6] = {0};

void J_a_init()
{
    for(int i = 0; i < 6; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            Jr[i][j] = 0.0;
            Jr_T_Jr[i][j] = 0.0;
            J_invert[i][j] = 0.0;
        }
        Jr_T_R[i] = 0.0;
    }
}

void GuassNewton_init()
{
    measure_diff_a_init();
    delta_Beta_init();
    J_a_init();
}


void GaussNewton()
{
    

    //J_r
    for(uint8_t i = 0; i < 6; i++)
    {
        Jr[i][0] = ( 2*diff[i][0] - 2*Beta[0] )*Beta[3]*Beta[3];
        Jr[i][1] = ( 2*diff[i][1] - 2*Beta[1] )*Beta[4]*Beta[4];
        Jr[i][2] = ( 2*diff[i][2] - 2*Beta[2] )*Beta[5]*Beta[5];
        Jr[i][3] = -2*(diff[i][0] - Beta[0] )*(diff[i][0] - Beta[0] )*Beta[3];
        Jr[i][4] = -2*(diff[i][1] - Beta[1] )*(diff[i][1] - Beta[1] )*Beta[4];
        Jr[i][5] = -2*(diff[i][2] - Beta[2] )*(diff[i][2] - Beta[2] )*Beta[5];
    }

    //Jr(βα)^T Jr(βα) 6x6 6x6 = 6x6
    //float Jr_T_Jr[6][6] = {0};
    //Jr(βα)^T r(βα) 6x6 6x1 = 6x1 r为某特定解下方程的误差
    //float Jr_T_R[6] = {0};
    for (uint8_t i = 0; i < 6; i++)
    {
        Jr_T_R[i] =0;
        for(uint8_t j = 0; j < 6; j++)
        {
            Jr_T_Jr[i][j] =0;
            for(uint8_t k = 0; k < 6; k++)
            {
                Jr_T_Jr[i][j] += Jr[k][i] * Jr[k][j];
            }
            Jr_T_R[i] += Jr[j][i] * residual[j];
        }
    }

    //[Jr(βα)^T Jr(βα)]^-1
    invert_matrix(Jr_T_Jr,J_invert,6);

    //delta = [Jr(βα)^T Jr(βα)]^-1  Jr(βα)^T r(βα)
    //即delta = J_invert Jr_T_R
    for (uint8_t i = 0; i < 6; i++) {
        for (uint8_t j = 0; j < 6; j++) {
            delta[i] += J_invert[i][j] * Jr_T_R[j];
        }
    }

    //β = βα - delta
    for (uint8_t i = 0; i < 6; i++) 
    {
        Beta[i] = Beta_alpha[i] - delta[i];
        //βα更新 
        Beta_alpha[i] = Beta[i];
    }

}

// float aX_correction = 0.0f;
// float aY_correction = 0.0f;
// float aZ_correction = 0.0f;



//................................................................
//................................................................
//求逆矩阵[Jr(βα)^T Jr(βα)]^-1
int invert_matrix(float matrix[6][6], float inverse[6][6], int n) {
    // 创建扩展矩阵
    float augmented[6][2 * 6];
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            augmented[i][j] = matrix[i][j];
        }
        for (int j = 0; j < n; j++) {
            augmented[i][j + n] = (i == j) ? 1 : 0;  // 单位矩阵
        }
    }

    // 高斯消元
    for (int i = 0; i < n; i++) {
        // 找到主元
        float MEl = fabs(augmented[i][i]);
        int MRow = i;
        for (int k = i + 1; k < n; k++) {
            if (fabs(augmented[k][i]) > MEl) {
                MEl = fabs(augmented[k][i]);
                MRow = k;
            }
        }
        // 交换最大行与当前行
        for (int k = i; k < 2 * n; k++) {
            float tmp = augmented[MRow][k];
            augmented[MRow][k] = augmented[i][k];
            augmented[i][k] = tmp;
        }
        // 将主元变为1
        float divisor = augmented[i][i];
        if (divisor == 0) {
            invert_flag = 0;
            return 0;  // 矩阵不可逆
        }
        for (int k = 0; k < 2 * n; k++) {
            augmented[i][k] /= divisor;
        }

        // 消去其他行的当前列
        for (int k = 0; k < n; k++) {
            if (k != i) {
                float factor = augmented[k][i];
                for (int j = 0; j < 2 * n; j++) {
                    augmented[k][j] -= factor * augmented[i][j];
                }
            }
        }
    }

    // 提取逆矩阵
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            inverse[i][j] = augmented[i][j+6];//调整下降方向，已删
        }
    }
    invert_flag = 1;
    return 1;  // 矩阵逆运算成功
}


void a_correction(float ax, float ay, float az)
{
    aX_correction = (ax - Beta[0])*Beta[3];
    aY_correction = (ay - Beta[1])*Beta[4];
    aZ_correction = (az - Beta[2])*Beta[5];
}


