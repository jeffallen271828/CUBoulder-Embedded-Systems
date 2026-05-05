/*
 * Scheduler.h
 *
 *  Created on: Sep 10, 2024
 *      Author: jeffreya181
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

//#include <stdint.h>
#include "Matrixdef.h"

#define LED_TOGGLE_EVENT (1 << 0)
#define DELAY_TIME_EVENT (1 << 1)
#define MATRIX_UPDATE_EVENT (1 << 2)

uint32_t getScheduledEvents();
void addScheduledEvent(uint32_t event);
void removeSchedulerEvent(uint32_t event);

#endif /* SCHEDULER_H_ */
