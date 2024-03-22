// global.h

#ifndef GLOBAL_H
#define GLOBAL_H

#include "stm32f7xx_hal.h"
#include "cmsis_os.h"
#include "main.h"

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;

extern osThreadId_t HC_SR04_TaskHandle;

void trigger_HCSR04(void);
void delay_us(uint32_t us);

extern float dist_cm;
float getDistance(void);

#endif // GLOBAL_H
