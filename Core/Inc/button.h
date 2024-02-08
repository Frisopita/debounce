/*
 * button.h
 *
 *  Created on: Feb 6, 2024
 *      Author: FridaAndrade
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include <stdbool.h>

#define N_BUTTONS 1

#define DEFAULT_DEBOUNCE_TIMEOUT_MS 50UL
#define DEFAULT_CLICK_TIMEOUT_MS 150UL
#define DEFAULT_HOLD_TIMEOUT_MS 750UL
#define DEFAULT_LONG_HOLD_TIMEOUT 3000UL
#define DEFAULT_HOLD_REPEAT_PERIOD 200UL
#define DEFAULT_LONG_HOLD_REPEAT_PERIOD 50UL

typedef enum
{
	IDLE,
	PRESSED,
	RELEASED,
	LONG_CLICK,
	CLICK,
	HOLD,
}BUTTON_EVENT_ENUM_t;

typedef struct {
	GPIO_TypeDef * port;
	uint16_t pin;
	uint32_t pressedTime;
	uint32_t debounceTick;
	uint32_t pressedTick;
	uint32_t releasedTick;
	uint8_t state;
	bool isDefined;
	bool hasPendingAction;
	BUTTON_EVENT_ENUM_t event;
} Button_TypeDef;



uint8_t button_read_debounce(void);
void button_handler(void);

#endif /* INC_BUTTON_H_ */
