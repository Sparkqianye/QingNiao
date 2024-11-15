#ifndef _MAIN_H_
#define _MAIN_H_


#include "stm32f4xx.h"                  // Device header
#include "Delay.h"
#include "gy86.h"
#include "gy86_reg.h"
#include "Serial.h"
#include "Receiver.h"
#include "PWM.h"
#include "GaussNewton.h"
#include "PID_C.hpp"

// extern  void PIDX_get(float outputX, float dt_out, float dt_in, float outer_input, float outer_SetPoint, float inner_input, float inner_SetPoint);
// extern  void PIDY_get(float outputY, float dt_out, float dt_in, float outer_input, float outer_SetPoint, float inner_input, float inner_SetPoint);
// extern  void PIDZ_get(float outputZ, float dt_out, float dt_in, float outer_input, float outer_SetPoint, float inner_input, float inner_SetPoint);

extern float aX_correction,aY_correction,aZ_correction,gyroX_correction,gyroY_correction,gyroZ_correction;

void TimingDelay_Decrement(void);
static void Delay(__IO uint32_t nTime);

#endif  // _MAIN_H_


