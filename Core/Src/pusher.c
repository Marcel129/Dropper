#include "pusher.h"

void pusher_Move(pusher_t * pusher, dcMotor_moveDirection_t dir){
	dcMotor_start(&(pusher->motor), dir);
}

void pusher_Stop(pusher_t * pusher){
	dcMotor_stop(&(pusher->motor));
}

machineState_t pusher_HomeToMin(pusher_t * pusher){
	uint32_t prevTime, currTime;
	prevTime = currTime = HAL_GetTick();

	dcMotor_start(&(pusher->motor), DCMOTOR_BACKWARD);

	while(sensor_getState(&(pusher->minEndstop)) != pusher->minEndstop.logic.activeState){
		currTime = HAL_GetTick();

		if(currTime - prevTime > pusher->homingTimeout){
			dcMotor_stop(&(pusher->motor));
			return MACHINE_TIMEOUT;
		}
	}

	dcMotor_stop(&(pusher->motor));
	return MACHINE_WORKING;
}

machineState_t pusher_HomeToMax(pusher_t * pusher){
	uint32_t prevTime, currTime;
	prevTime = currTime = HAL_GetTick();

	dcMotor_start(&(pusher->motor), DCMOTOR_FORWARD);

	while(sensor_getState(&(pusher->maxEndstop)) != pusher->maxEndstop.logic.activeState){
		currTime = HAL_GetTick();

		if(currTime - prevTime > pusher->homingTimeout){
			dcMotor_stop(&(pusher->motor));
			return MACHINE_TIMEOUT;
		}
	}

	dcMotor_stop(&(pusher->motor));
	return MACHINE_WORKING;
}
