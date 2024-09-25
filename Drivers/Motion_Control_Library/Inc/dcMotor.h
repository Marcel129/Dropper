#ifndef INC_DCMOTOR_H_
#define INC_DCMOTOR_H_

//#include "gpio.h"
#include <HardwareLogic.h>

typedef enum {DCMOTOR_FORWARD, DCMOTOR_BACKWARD}
dcMotor_moveDirection_t;

typedef struct{

	GPIO_TypeDef * forwardPort, * backwardPort;
	uint16_t forwardPin, backwardPin;

	logicLOL_t logic;

} dcMotor_t;

void dcMotor_Init(dcMotor_t * dcM,
		GPIO_TypeDef *,uint16_t, GPIO_TypeDef *,uint16_t,
		logicType_t);
void dcMotor_start(dcMotor_t *, dcMotor_moveDirection_t);
void dcMotor_stop(dcMotor_t *);

#endif /* INC_DCMOTOR_H_ */
