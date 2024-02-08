/*
 * motor.c
 *
 *  Created on: Feb 6, 2024
 *      Author: FridaAndrade
 */
#include "main.h"
#include "motor.h"

extern TIM_HandleTypeDef htim1;
uint32_t maxduty = 0;
uint32_t duty = 0;

void motorRight_on(void)
{
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
}

void motorRight_off(void)
{
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
}

void motorLeft_on(void)
{
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
}

void motorLeft_off(void)
{
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2);
}

void motor_setVelocityRight(uint8_t vel)
{
	maxduty = htim1.Instance->ARR;
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	duty = (vel*100)/maxduty;
	htim1.Instance->CCR1 = duty;

}

void motor_setVelocityLeft(uint8_t vel)
{
	maxduty = htim1.Instance->ARR;
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
	duty = (vel*100)/maxduty;
	htim1.Instance->CCR2 = duty;

}



