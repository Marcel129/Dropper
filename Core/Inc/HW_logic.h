#ifndef INC_HW_LOGIC_H_
#define INC_HW_LOGIC_H_

#include "gpio.h"

typedef enum {HIGH_IS_ACTVE, LOW_IS_ACTVE}
logicType_t;

typedef struct{
	GPIO_PinState activeState, inactiveState;
	logicType_t logicType;
}logic_t;

void HW_logic_setLogic(logic_t*, logicType_t);
logicType_t HW_logic_invertLogic(logic_t*); //return setted logic

#endif /* INC_HW_LOGIC_H_ */
