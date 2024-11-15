//#include "PID.hpp"
#include "PID_C.hpp"
using namespace std;

class PID {
private:
    float Kp;          // 比例系数
    float Ki;          // 积分系数
    float Kd;          // 微分系数

    float input; // 实际值（输入值）
    float SetPoint;    // 目标值

    float minv;
    float maxv;

    float integral;      // 积分值
    float derivative;   // 微分值
    float err;         // 当前误差
    //float errLast;     // 上次误差
    float errPrev;     // 上一次误差

    
public:

    float out;
    // 构造函数 
    PID(float Kp, float Ki, float Kd, float input, float SetPoint, float Minv, float Maxv)
        : Kp(Kp), Ki(Ki), Kd(Kd), input(input), SetPoint(SetPoint), minv(Minv), maxv(Maxv),
          integral(0.0f), derivative(0.0f), err(0.0f), errPrev(0.0f) {}
    
    // 控制函数
    float pid_output(float dt);

    float limit(float x) // 速度限制
    {
        return x < minv ? minv : (x > maxv ? maxv : x);
    }

};

float PID::pid_output(float dt)
{
    integral = 0.0f;
    derivative = 0.0f;
    err = SetPoint - input;

    // 计算积分项
    integral += err * dt;

    // 计算微分项
    derivative = (err - errPrev) / dt;

    // 计算输出
    float output = Kp * err + Ki * integral + Kd * derivative;

    // 限制输出在指定范围内
    output = limit(output);

    // 记录上一次的误差
    errPrev = err;

    return output;
}

void PIDX_get(float outputX, float dt_out, float dt_in, float outer_input, float outer_SetPoint, float inner_input, float inner_SetPoint)
    {
        PID PIDX_outer( PID_X_OUT_KP, PID_X_OUT_KI, PID_X_OUT_KD, outer_input, outer_SetPoint, PID_X_OUT_MIN, PID_X_OUT_MAX);

        inner_input = PIDX_outer.pid_output(dt_out);
        PID PIDX_inner(PID_X_IN_KP, PID_X_IN_KI, PID_X_IN_KD, inner_input, inner_SetPoint, PID_X_IN_MIN, PID_X_IN_MAX);

        outputX = PIDX_inner.pid_output(dt_in);
    }

    //将Pitch角作为outer_inputY,将接收机数据（解析出来的目标Pitch角度）作为outer_SetPointY，
    //将陀螺仪测得的Pitch角速度作为inner_inputY，在函数内计算外环输出，放进inner_SetPointY,
    //输出结果（Pitch角角加速度）放进PID_out_Y
void PIDY_get(float outputY, float dt_out, float dt_in, float outer_input, float outer_SetPoint, float inner_input, float inner_SetPoint)
    {
        PID PIDY_outer( PID_Y_OUT_KP, PID_Y_OUT_KI, PID_Y_OUT_KD, outer_input, outer_SetPoint, PID_Y_OUT_MIN, PID_Y_OUT_MAX);

        inner_input = PIDY_outer.pid_output(dt_out);
        PID PIDY_inner(PID_Y_IN_KP, PID_Y_IN_KI, PID_Y_IN_KD, inner_input, inner_SetPoint, PID_Y_IN_MIN, PID_Y_IN_MAX);

        outputY = PIDY_inner.pid_output(dt_in);
    }

    //将Yaw角作为outer_inputZ,将接收机数据（解析出来的目标Yaw角度）作为outer_SetPointZ，
    //将陀螺仪测得的Yaw角速度作为inner_inputZ，在函数内计算外环输出，放进inner_SetPointZ,
    //输出结果（Yaw角角加速度）放进PID_out_Z
void PIDZ_get(float outputZ, float dt_out, float dt_in, float outer_input, float outer_SetPoint, float inner_input, float inner_SetPoint)
    {
        PID PIDZ_outer( PID_Z_OUT_KP, PID_Z_OUT_KI, PID_Z_OUT_KD, outer_input, outer_SetPoint, PID_Z_OUT_MIN, PID_Z_OUT_MAX);

        inner_input = PIDZ_outer.pid_output(dt_out);
        PID PIDZ_inner(PID_Z_IN_KP, PID_Z_IN_KI, PID_Z_IN_KD, inner_input, inner_SetPoint, PID_Z_IN_MIN, PID_Z_IN_MAX);

        outputZ = PIDZ_inner.pid_output(dt_in);
    }


