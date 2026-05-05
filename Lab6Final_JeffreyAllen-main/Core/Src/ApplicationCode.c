/*
 * ApplicationCode.c
 *
 *  Created on: Sep 10, 2024
 *      Author: jeffreya181
 */
#include "ApplicationCode.h"

void applicationInit(){

#if	USE_INTERRUPT_FOR_BUTTON == ACTIVE_INTERRUPT
	applicationInterruptInit();
	addScheduledEvent(DELAY_TIME_EVENT);
#else
	applicationButtonInit();
	addScheduledEvent(BUTTON_POLL_EVENT);
	removeSchedulerEvent(DELAY_TIME_EVENT);
#endif

	//redLEDInit();
	greenLEDInit();
	deactivateGreenLED();
	//addScheduledEvent(LED_TOGGLE_EVENT);
}

void greenLEDInit(){
	LED_Init(GREEN_LED);
}

void redLEDInit(){
	LED_Init(RED_LED);
}

void toggleLED(){
	toggleGreenLED();
	toggleRedLED();
}

void toggleGreenLED(){
	ToggleLED(GREEN_LED);
}

void toggleRedLED(){
	ToggleLED(RED_LED);
}

void activateGreenLED(){
	ToggleLED(GREEN_LED);
	//TurnOnLED(GREEN_LED);
}

void activateRedLED(){
	TurnOnLED(RED_LED);
}

void deactivateGreenLED(){
	TurnOffLED(GREEN_LED);
}

void deactivateRedLED(){
	TurnOffLED(RED_LED);
}

void appDelay(uint32_t delay){
	char standardDelay[NAME_LENGTH] = "Jeffrey";
	[[maybe_unused]] char destinationArray[NAME_LENGTH];

	for(int i = 0; i < delay; i++){
		for(int j = 0; j < NAME_LENGTH; j++){
			destinationArray[j] = standardDelay[j];
		}
	}
}

void applicationButtonInit() {
	init_Button();
}
void executeButtonPollingRoutine() {

	if(isButtonPressed()) {
		activateGreenLED();
	} else {
		deactivateGreenLED();
	}

}

void applicationInterruptInit() {
	Button_Interrupt();
}

void EXTI0_IRQHandler(){
	Interrupt_Disable(EXTI0_IRQ_NUMBER);
	Interrupt_Clear_Pending(EXTI0_IRQ_NUMBER);
	Interrupt_Clear_Pending_EXTI(GPIO_PIN_NUM_13);
	ToggleLED(GREEN_LED);
	Interrupt_Enable(EXTI0_IRQ_NUMBER);
}
