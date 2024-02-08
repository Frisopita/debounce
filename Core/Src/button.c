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

Button_TypeDef button = {BUTTON_GPIO_Port, BUTTON_Pin, DEFAULT_DEBOUNCE_TIMEOUT_MS, 0, GPIO_PIN_RESET};

uint8_t button_read_debounce(void)
{
	uint32_t current_time = HAL_GetTick();
	uint8_t current_state = HAL_GPIO_ReadPin(button.port, button.pin);

	// Verificar si ha pasado el tiempo de debounce
	if (current_time - button.last_read_time >= button.debounce_time_ms) {
		// Si el estado actual es diferente al estado anterior
		if (current_state != button.last_state) {
			// Actualizar el último tiempo leído
			button.last_read_time = current_time;
			// Si el botón ha sido presionado
			if (current_state == GPIO_PIN_SET) {
				button.last_state = current_state;
				return PRESSED;
			}
			// Si el botón ha sido liberado
			else {
				button.last_state = current_state;
				return RELEASED;
			}
		}
	}
	return IDLE;

}

void button_handler(void)
{
	BUTTON_EVENT_ENUM_t event = button_read_debounce();
	//uint32_t current_time_handler = HAL_GetTick();
	//uint32_t last_action_time = 0;
	//uint32_t elapsed_time = current_time_handler - last_action_time;

	switch (event) {
	case PRESSED:
		//motorRight_on();
		//HAL_Delay(time_duration * 1000);
		//motorRight_off();
		break;
	case RELEASED:
		pump_on();
		HAL_Delay(time_duration * 1000);
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

