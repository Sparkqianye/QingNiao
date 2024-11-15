// #ifndef PID_C_H
// #define PID_C_H

#ifndef PID_HPP
#define PID_HPP


#define PID_X_OUT_KP 0.0f
#define PID_X_OUT_KI 0.0f
#define PID_X_OUT_KD 0.0f
#define PID_X_OUT_MAX 1000
#define PID_X_OUT_MIN -1000
#define PID_X_OUT_SETPOINT 0.0f

#define PID_X_IN_KP 0.0f
#define PID_X_IN_KI 0.0f
#define PID_X_IN_KD 0.0f
#define PID_X_IN_MAX 1000
#define PID_X_IN_MIN -1000
#define PID_X_IN_SETPOINT 0.0f

#define PID_Y_OUT_KP 0.0f
#define PID_Y_OUT_KI 0.0f
#define PID_Y_OUT_KD 0.0f
#define PID_Y_OUT_MAX 1000
#define PID_Y_OUT_MIN -1000
#define PID_Y_OUT_SETPOINT 0.0f

#define PID_Y_IN_KP 0.0f
#define PID_Y_IN_KI 0.0f
#define PID_Y_IN_KD 0.0f
#define PID_Y_IN_MAX 1000
#define PID_Y_IN_MIN -1000
#define PID_Y_IN_SETPOINT 0.0f

#define PID_Z_OUT_KP 0.0f
#define PID_Z_OUT_KI 0.0f
#define PID_Z_OUT_KD 0.0f
#define PID_Z_OUT_MAX 1000
#define PID_Z_OUT_MIN -1000
#define PID_Z_OUT_SETPOINT 0.0f

#define PID_Z_IN_KP 0.0f
#define PID_Z_IN_KI 0.0f
#define PID_Z_IN_KD 0.0f
#define PID_Z_IN_MAX 1000
#define PID_Z_IN_MIN -1000
#define PID_Z_IN_SETPOINT 0.0f

#include "PID_C.hpp"

#ifdef __cplusplus
extern "C" {
#endif

   //  #include "stm32f4xx.h" 
   //  #include <stdio.h>
   //  #include <math.h>
// #ifdef __cplusplus
// }
// #endif

// #ifdef __cplusplus
// extern "C" {
// #endif

   void PIDX_get(float outputX, float dt_out, float dt_in, float outer_input, float outer_SetPoint, float inner_input, float inner_SetPoint);
   void PIDY_get(float outputY, float dt_out, float dt_in, float outer_input, float outer_SetPoint, float inner_input, float inner_SetPoint);
   void PIDZ_get(float outputZ, float dt_out, float dt_in, float outer_input, float outer_SetPoint, float inner_input, float inner_SetPoint);


#ifdef __cplusplus
}
#endif // __cplusplus


#endif // PID_C_H

