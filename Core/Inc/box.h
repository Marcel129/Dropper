#ifndef INC_BOX_H_
#define INC_BOX_H_

#include "dropper.h"
#include "UART_communication.h"
#include "config.h"
#include "sensor.h"
#include "dcMotor.h"
#include "pusher.h"
#include "machineStates.h"
#include "usart.h"

typedef struct{
	dropper_t 	dropper;
	pusher_t	upperPusher, lowerPusher;
	UART_structure_t * box_Communication_Handler;
}box_t;

extern box_t box;

void box_Init();
void box_execCmd_StartMovePusher(box_t*, uint8_t pusherName, dcMotor_moveDirection_t dir);
void box_execCmd_StoptMovePusher(box_t*, uint8_t pusherName, dcMotor_moveDirection_t dir);
void box_execCmd_SowRow(box_t*, uint8_t channelNo);
void box_execCmd_PushEmptyMultiplat(box_t*);
void box_execCmd_PushFullMultiplat(box_t*);

// REMOTE COMMANDS FUNCTIONS
void _dropper_execCmd();

void _dropper_execCmd_Help(box_t*);
void _dropper_execCmd_GetStatus(box_t*);
void _dropper_execCmd_Sow(box_t*, uint8_t channelNo, uint8_t noOfSeeds);
void _dropper_execCmd_SowExt(box_t*, uint8_t channelNo, uint8_t noOfSeeds, uint8_t potNo);
void _dropper_execCmd_HomeDropper(box_t*);
void _dropper_execCmd_MoveDropper(box_t*, double distance_mm);
void _dropper_execCmd_Selftest(box_t*);

#endif /* INC_BOX_H_ */
