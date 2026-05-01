
//Includes
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "PumpMotor.h"

//Private Includes
#include <string.h>
#include <stdio.h>
#include <math.h>

//Variables
 uint32_t kTimeUpdateInterval = 0
 uint32_t kUpdateChange = 1
 uint32_t kFinalStartFrequency = 0
 uint32_t kEndFrequency = 0

void StartMotorPWM(void){
    //Start PWM which starts stepping
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
}

void UpdateFrequency(uint32_t frequency){
	uint32_t CCRValue = (frequency + 1) /2;
	__HAL_TIM_SET_AUTORELOAD(&htim2, frequency);
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, CCRValue);
	HAL_TIM_GenerateEvent(&htim2, TIM_EVENTSOURCE_UPDATE);
}

uint32_t GetFrequency(void){
    return __HAL_TIM_GET_AUTORELOAD(&htim2);
}

//could potentially have this function return a string 
//so when it finishes that string can be printed to console
void StartPump(void) {
    //tim2 is currently set to tick every microsecond
    //we want to ramp up frequency a certain amount per a certain amount of time
    //until it reaches a certain frequency and then we end function
    static uint32_t frequency = 0;
    static uint32_t lastUpdate = 0;

    if (frequency < kFinalStartFrequency) {
        
        currentTime = HAL_GetTick();

        if (lastUpdate - currentTime >= kTimeUpdateInterval) {
            frequency += kUpdateIncrease;
            UpdateFrequency(frequency);
        }
    }
}

void EndPump(void) {

    static uint32_t frequency = GetFrequency();
    static uint32_t lastUpdate = 0;

    if (frequency > kEndFrequency) {
        
        currentTime = HAL_GetTick();

        if (lastUpdate - currentTime >= kTimeUpdateInterval) {
            frequency -= kUpdateIncrease;
            UpdateFrequency(frequency);
        }
    }
}



void UpdatePID(int error) {

}