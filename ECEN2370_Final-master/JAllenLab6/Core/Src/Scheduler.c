/*
 * Scheduler.c
 *
 *  Created on: Sep 10, 2024
 *      Author: jeffreya181
 */
#include "Scheduler.h"

static uint32_t scheduledEvents;

uint32_t getScheduledEvents(){
	uint32_t returnVal = scheduledEvents;
	return returnVal;
}

void addScheduledEvent(uint32_t event){
	scheduledEvents |= (event);
}

void removeSchedulerEvent(uint32_t event){
	scheduledEvents &= ~(event);
}





