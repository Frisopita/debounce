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

Button_TypeDef button = {BUTTON_GPIO_Port, BUTTON_Pin, DEFAULT_DEBOUNCE_TIMEOUT_MS, 0, GPIO_PIN_RESET};

uint8_t isEvent = 0;
extern int time_duration;
extern uint8_t isButton;

uint8_t button_read_debounce(void)
{
	uint8_t current_state = HAL_GPIO_ReadPin(button.port, button.pin);
	uint32_t current_time = HAL_GetTick();
	isEvent = 0;

	if (current_state != button.last_state){
		button.last_state = current_state;
		isEvent = 1;
		if (current_time - button.last_read_time >= DEFAULT_DEBOUNCE_TIMEOUT_MS){
			button.last_read_time = current_time;

			if (current_state == GPIO_PIN_SET)
			{
				button.pressedTick = current_time;
			}
			else
			{
				button.releasedTick = current_time;
				if (button.releasedTick - button.pressedTick >= DEFAULT_LONG_HOLD_TIMEOUT )
				{
					button.event = LONG_CLICK;
				}
				else
				{
					button.event = RELEASED;
				}
			}
		}
	}
	return isEvent;
}

void button_handler(void)
{
	if (button_read_debounce())
	{
		switch (button.event)
		{
		case IDLE:
		{
			isButton = 0;
			break;
		}
		case RELEASED:
		{
			isButton = 1;
			button.event = IDLE;
			break;
		}
		case PRESSED:
		{
			isButton = 2;
			button.event = IDLE;
			break;
		}
		case LONG_CLICK:
		{
			isButton = 3;
			button.event = IDLE;
			break;
		}
		default:
			break;
		}

	}


}

