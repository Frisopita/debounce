/*
 * button.c
 *
 *  Created on: Feb 6, 2024
 *      Author: FridaAndrade
 */
#include "main.h"
#include "button.h"
#include "motor.h"
#include "pump.h"
#include "led.h"

int time_duration = 5;

Button_TypeDef button;

uint8_t button_read_debounce(void)
{
	if(HAL_GetTick() - button.debounceTick > DEFAULT_DEBOUNCE_TIMEOUT_MS)
	{
		button.debounceTick = HAL_GetTick();
		button.state = HAL_GPIO_ReadPin(button.port, button.pin);
		if( button.state == GPIO_PIN_SET)
		{
			//Pressed
			//HAL_GPIO_WritePin(DBG_LED_GPIO_Port, DBG_LED_Pin, GPIO_PIN_SET);
			button.pressedTick = HAL_GetTick();
		}
		if(HAL_GPIO_ReadPin(button.port, button.pin) == GPIO_PIN_RESET)
		{
			//Released
			//HAL_GPIO_WritePin(DBG_LED_GPIO_Port, DBG_LED_Pin, GPIO_PIN_RESET);
			button.releasedTick = HAL_GetTick();
			if(button.releasedTick > button.pressedTick)
			{
				button.pressedTime = button.releasedTick - button.pressedTick;
			}
			else if(button.releasedTick < button.pressedTick)
			{
				button.pressedTime = ((0xFFFFFFFF - button.releasedTick) - button.pressedTick) + 1;
			}
			else
			{
				button.pressedTime = 0;
			}

			if(button.pressedTime > DEFAULT_LONG_HOLD_TIMEOUT)
			{
				button.event = LONG_CLICK;
				button.hasPendingAction = true;
			}
			else if(button.pressedTime > DEFAULT_HOLD_TIMEOUT_MS)
			{
				button.event = PRESSED;
				button.hasPendingAction = true;

			}
			else if(button.pressedTime > DEFAULT_CLICK_TIMEOUT_MS)
			{
				button.event = RELEASED;
				button.hasPendingAction = true;
			}
		}

	}
}

void button_handler(void)
{
	BUTTON_EVENT_ENUM_t event = button_read_debounce();
	//uint32_t current_time_handler = HAL_GetTick();
	//uint32_t last_action_time = 0;
	//uint32_t elapsed_time = current_time_handler - last_action_time;

	switch (event) {
	case PRESSED:
		motorRight_on();
		HAL_Delay(time_duration * 1000);
		motorRight_off();
		break;
	case RELEASED:
		led_on();
		pump_on();
		HAL_Delay(time_duration * 1000);
		led_off();
		pump_off();
		/*motorRight_on();
		motorLeft_off();
		HAL_Delay(time_duration * 1000);
		motorRight_on();
		motorLeft_off();
		HAL_Delay(1000);
		motorRight_off();
		motorLeft_on();
		HAL_Delay(time_duration * 1000);
		led_off();
		pump_off();
		motorRight_off();
		motorLeft_off();*/
		break;
	case LONG_CLICK:
		led_on();
		HAL_Delay(time_duration * 1000);
		led_off();
		/*pump_on();
		motorRight_on();
		motorLeft_off();
		HAL_Delay(time_duration * 1000);
		motorRight_off();
		motorLeft_off();
		HAL_Delay(1000);
		motorRight_off();
		motorLeft_on();
		HAL_Delay(time_duration * 1000);
		led_off();
		pump_off();
		motorRight_off();
		motorLeft_off();*/

	default:
		break;
	}
}

