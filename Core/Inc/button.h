/*
 * button.h
 *
 *  Created on: Feb 6, 2024
 *      Author: FridaAndrade
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#define N_BUTTONS 1

#define DEFAULT_DEBOUNCE_TIMEOUT_MS 50UL
#define DEFAULT_CLICK_TIMEOUT_MS 150UL
#define DEFAULT_HOLD_TIMEOUT_MS 750UL
#define DEFAULT_LONG_HOLD_TIMEOUT 30000UL
#define DEFAULT_HOLD_REPEAT_PERIOD 200UL
#define DEFAULT_LONG_HOLD_REPEAT_PERIOD 50UL

typedef struct {
    GPIO_TypeDef * port;
    uint16_t pin;
    uint32_t debounce_time_ms;
    uint32_t last_read_time;
    uint8_t last_state;
} Button_TypeDef;

typedef enum
{
	IDLE,
    RELEASED,
    DEBOUNCE,
    PRESSED,
    LONG_CLICK,
}BUTTON_EVENT_ENUM_t;

uint8_t button_read_debounce(void);
void button_handler(void);

#endif /* INC_BUTTON_H_ */
