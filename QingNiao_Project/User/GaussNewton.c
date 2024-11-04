#include "GaussNewton.h"
#include "stm32f4xx.h" 
#include <stdio.h>
#include <math.h>

#define G 9.81

double ideal_a_matrix[6][3] = {
    {0, 0, G},
    {0, 0,-G},
    {0, G, 0},
    {0,-G, 0},
    {G, 0, 0},
    {-G, 0, 0}
};

double measure[6][3] = {0};

//diff matrix 赋值
double diff[6][3] = {0};

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

uint8_t current_index = 0;

//matrix residual 赋值, residual为某特定解下方程的误差 
double residual[6];
void DR_a_init(double data_ax, double data_ay, double data_az)
{
    current_index = current_index % 6;

    measure[current_index][0] = data_ax;
    measure[current_index][1] = data_ay;
    measure[current_index][2] = data_az;

    diff[current_index][0] = measure[current_index][0] - ideal_a_matrix[current_index][0];
    diff[current_index][1] = measure[current_index][1] - ideal_a_matrix[current_index][1];
    diff[current_index][2] = measure[current_index][2] - ideal_a_matrix[current_index][2];

    residual[current_index] = sqrt(
    diff[current_index][0] * diff[current_index][0] +
    diff[current_index][1] * diff[current_index][1] +
    diff[current_index][2] * diff[current_index][2]
    );

    current_index++;
}


//for delta Beta Beta_alpha matrix
double delta[6] = {0.0};
double Beta_alpha[6] = {0};
double Beta[6] = {0};

void delta_Beta_init()
{
    for(int i = 0; i < 6; i++)
    {
        Beta_alpha[i] = 0.0;
        Beta[i] = 0.0;
        delta[i] = 0.0;
    }
}
//初解βα
//β = βα - [ J_r^T * J_r ]^-1   *   [J_r^T * R]
//delta = [Jr(βα)^T Jr(βα)]^-1  Jr(βα)^T r(βα)


double Jr[6][6];
//Jr(βα)^T Jr(βα) 6x6 6x6 = 6x6
double Jr_T_Jr[6][6] = {0};
//Jr(βα)^T r(βα) 6x6 6x1 = 6x1 r为某特定解下方程的误差
double Jr_T_R[6] = {0};

double J_invert[6][6] = {0};

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
        for(uint8_t j = 0; j < 3; j++)
        {
            //fill the Jacobian matrix with partial derivatives
            Jr[i][j] = 2*Beta_alpha[j+3]*Beta_alpha[j+3]*diff[i][j];
            Jr[i][j+3] = -2*Beta_alpha[j+3]*diff[i][j]*diff[i][j];
        }
    }

    //Jr(βα)^T Jr(βα) 6x6 6x6 = 6x6
    //double Jr_T_Jr[6][6] = {0};
    //Jr(βα)^T r(βα) 6x6 6x1 = 6x1 r为某特定解下方程的误差
    //double Jr_T_R[6] = {0};
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

void a_correction(double data_ax, double data_ay, double data_az)
{
    mpuX_correction = (data_ax - Beta[0])*Beta[3];
    mpuY_correction = (data_ay - Beta[1])*Beta[4];
    mpuZ_correction = (data_az - Beta[2])*Beta[5];
}


//................................................................
//................................................................
//求逆矩阵[Jr(βα)^T Jr(βα)]^-1
int invert_matrix(double A[6][6], double invA[6][6], int n) {
    double augmented[6][12] = {0};  // 扩展矩阵 [A | I]

    // 构建扩展矩阵
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            augmented[i][j] = A[i][j];
            augmented[i][j + n] = (i == j) ? 1.0 : 0.0;
        }
    }


    // 高斯-约旦消元法
    for (int i = 0; i < n; i++) {
        // 寻找最大值以避免除以小数
        double max_val = fabs(augmented[i][i]);
        int max_row = i;
        for (int k = i + 1; k < n; k++) {
            if (fabs(augmented[k][i]) > max_val) {
                max_val = fabs(augmented[k][i]);
                max_row = k;
            }
        }

        // 如果主元素为0，矩阵不可逆
        if (max_val == 0) {
            return 0;
        }

        // 交换行
        if (max_row != i) {
            for (int j = 0; j < 2 * n; j++) {
                double temp = augmented[i][j];
                augmented[i][j] = augmented[max_row][j];
                augmented[max_row][j] = temp;
            }
        }

        // 归一化主元素
        double pivot = augmented[i][i];
        for (int j = 0; j < 2 * n; j++) {
            augmented[i][j] /= pivot;
        }

        // 消元
        for (int k = 0; k < n; k++) {
            if (k != i) {
                double factor = augmented[k][i];
                for (int j = 0; j < 2 * n; j++) {
                    augmented[k][j] -= factor * augmented[i][j];
                }
            }
        }
    }

    // 提取逆矩阵
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            invA[i][j] = augmented[i][j + n];
        }
    }

    return 1;
}


