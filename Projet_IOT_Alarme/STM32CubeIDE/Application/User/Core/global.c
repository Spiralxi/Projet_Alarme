// global.c

#include "global.h"

// Cette fonction sera utilisée pour générer une impulsion de déclenchement pour le HC-SR04
void trigger_HCSR04(void) {
    HAL_GPIO_WritePin(TRIG_GPIO_GPIO_Port, TRIG_GPIO_Pin, GPIO_PIN_SET);
    delay_us(10);  // 10 microsecondes
    HAL_GPIO_WritePin(TRIG_GPIO_GPIO_Port, TRIG_GPIO_Pin, GPIO_PIN_RESET);
}


// Fonction de délai en microsecondes
void delay_us(uint32_t us) {
    __HAL_TIM_SET_COUNTER(&htim2, 0);
    while (__HAL_TIM_GET_COUNTER(&htim2) < us);
}

float getDistance(void) {
    return dist_cm;
}
