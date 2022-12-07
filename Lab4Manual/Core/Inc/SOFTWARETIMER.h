/*
 * SOFTWARE_TIMER.h
 *
 *  Created on: Nov 5, 2022
 *      Author: WELCOME
 */

#ifndef INC_SOFTWARETIMER_H_
#define INC_SOFTWARETIMER_H_

extern int timer1_flag;
extern int timer2_flag;

void setTimer1(int duration);
void setTimer2(int duration);

void clearTimer1();
void clearTimer2();

void timerRun();

#endif /* INC_SOFTWARETIMER_H_ */
