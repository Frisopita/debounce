/*
 * led.c
 *
 *  Created on: Feb 6, 2024
 *      Author: FridaAndrade
 */
#include "main.h"
#include "led.h"

void led_on(void)
{
	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, SET);
}

void led_off(void)
{
	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, RESET);
}

