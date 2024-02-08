/*
 * motor.h
 *
 *  Created on: Feb 6, 2024
 *      Author: FridaAndrade
 */

#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_

void motorRight_on(void);
void motorRight_off(void);
void motorLeft_on(void);
void motorLeft_off(void);
void motor_setVelocityRight(uint8_t vel);
void motor_setVelocityLeft(uint8_t vel);

#endif /* INC_MOTOR_H_ */
