/*
 * pump.c
 *
 *  Created on: Feb 6, 2024
 *      Author: FridaAndrade
 */
#include "main.h"
#include "pump.h"

void pump_on(void)
{
	HAL_GPIO_WritePin(PUMP_GPIO_Port, PUMP_Pin, SET);
}

void pump_off(void)
{
	HAL_GPIO_WritePin(PUMP_GPIO_Port, PUMP_Pin, RESET);
}

void pump_setVelocity(uint8_t vel)
{
	HAL_GPIO_WritePin(PUMP_GPIO_Port, PUMP_Pin, vel);
}
