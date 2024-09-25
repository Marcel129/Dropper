#ifndef INC_SENSOR_H_
#define INC_SENSOR_H_

#include "HardwareLogic.h"

typedef struct{
	GPIO_TypeDef * port;
	uint16_t pin;

	logicLOL_t logic;

} sensor_t;

void sensor_Init(sensor_t *, GPIO_TypeDef *, uint16_t, logicType_t);
GPIO_PinState sensor_getState(sensor_t *s);

#endif /* INC_SENSOR_H_ */
