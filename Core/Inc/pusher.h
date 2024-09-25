#ifndef INC_PUSHER_H_
#define INC_PUSHER_H_

#include "dcMotor.h"
#include "sensor.h"
#include "machineStates.h"

typedef struct{
	sensor_t	minEndstop, maxEndstop;
	dcMotor_t	motor;

	uint32_t homingTimeout;
} pusher_t;

void pusher_Move(pusher_t *, dcMotor_moveDirection_t);
void pusher_Stop(pusher_t *);
machineState_t pusher_HomeToMin(pusher_t *);
machineState_t pusher_HomeToMax(pusher_t *);

#endif /* INC_PUSHER_H_ */
