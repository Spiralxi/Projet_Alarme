/*
 * PollingRoutines.c
 *
 *  Created on: Mar 15, 2024
 *      Author: erwan
 */
#include "main.h"
#include "PollingRoutines.h"
#include "cmsis_os.h"

extern CRC_HandleTypeDef hcrc;

extern DMA2D_HandleTypeDef hdma2d;

extern I2C_HandleTypeDef hi2c3;

extern LTDC_HandleTypeDef hltdc;

extern QSPI_HandleTypeDef hqspi;

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;

extern osSemaphoreId_t binarySemUltrasonHandle;



volatile uint8_t trigger_sonar = 0;
volatile uint8_t capture = 0;
uint32_t IC_Val1 = 0;
uint32_t IC_Val2 = 0;
uint32_t cnt_diff = 0;
uint8_t Is_First_Captured = 0;
float dist_cm  = 0;

void delay_us (uint32_t);
void trig_HCSR04(void);

void PollingInit()
{
	HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_1);
	HAL_TIM_Base_Start(&htim2);
	HAL_TIM_Base_Start_IT(&htim3);

	// Fixe le mode de capture à "front montant"
	//(inutile en fait, c'est le mode par défaut)
	__HAL_TIM_SET_CAPTUREPOLARITY(&htim1, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_RISING);


   }

void PollingRoutine()
{
	osSemaphoreRelease(binarySemUltrasonHandle);
    if(trigger_sonar){ // Si interruption de dépassement du timer "
       trigger_sonar = 0; // Réamorce pour un prochain appui
       trig_HCSR04(); // Lance une mesure avec le sonar
    }

   // Si occurrence interruption de capture du timer 1
    else if(capture){

        capture = 0;
        // Si la première valeur (front montant) n'a pas été capturée        if (!Is_First_Captured){
            //Capture la première valeur
            IC_Val1 = HAL_TIM_ReadCapturedValue(&htim1, TIM_CHANNEL_1);
            // Mémorise la capture
            Is_First_Captured = 1;
            // Change le mode de capture à "front descendant"
            __HAL_TIM_SET_CAPTUREPOLARITY(&htim1, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_FALLING);
        }
    // Si la première capture est déjà faite
            else if (Is_First_Captured) {
                // Capture la deuxième valeur
                IC_Val2 = HAL_TIM_ReadCapturedValue(&htim1, TIM_CHANNEL_1);
                // Remet le compteur CNT à 0
                __HAL_TIM_SET_COUNTER(&htim1, 0);
                // Si les deux captures se sont déroulées entre 0 et CNT Max
                if (IC_Val2 > IC_Val1 ){
                    cnt_diff = IC_Val2-IC_Val1;
                }
                // Sinon
                else if (IC_Val1 > IC_Val2)
                {
                    cnt_diff = (65535 - IC_Val1) + IC_Val2;
                }
                // Calcul de la distance en cm (0.17 cm = 34000 (cm/s) * cnt_diff (µs))
               dist_cm = cnt_diff * .017;
               // Signale que l'on peut procéder à une nouvelle capture
               Is_First_Captured = 0;
               // Change le mode de capture à "front montant"
               __HAL_TIM_SET_CAPTUREPOLARITY(&htim1, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_RISING);
               // Désactive l’interruption de capture
               __HAL_TIM_DISABLE_IT(&htim1, TIM_IT_CC1);
           }
    char buffer[30];
    int length = snprintf(buffer, sizeof(buffer), "Distance: %.2f cm\r\n", dist_cm);
    HAL_UART_Transmit(&huartx, (uint8_t*)buffer, length, HAL_MAX_DELAY); // Remplacez huartx par votre instance UART.

}

void trig_HCSR04(void) {
    HAL_GPIO_WritePin(TRIG_GPIO_GPIO_Port, TRIG_GPIO_Pin, GPIO_PIN_SET);
    delay_us(10);
    HAL_GPIO_WritePin(TRIG_GPIO_GPIO_Port, TRIG_GPIO_Pin, GPIO_PIN_RESET);
    __HAL_TIM_ENABLE_IT(&htim1, TIM_IT_CC1);
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if ( htim->Instance == TIM1) {
       if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) {
           capture = 1;}
        }
}
void delay_us (uint32_t us) {
	__HAL_TIM_SET_COUNTER(&htim2,0);
	while (__HAL_TIM_GET_COUNTER(&htim2) < us);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */
    if ( htim->Instance == TIM3) {
        trigger_sonar = 1;
    }
  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM6) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}


