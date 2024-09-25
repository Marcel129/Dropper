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

void box_Init();
void _box_execCmd_StartMovePusher(uint8_t pusherName, dcMotor_moveDirection_t dir);
void _box_execCmd_StoptMovePusher(uint8_t pusherName, dcMotor_moveDirection_t dir);
void _box_execCmd_SowRow(uint8_t channelNo);
void _box_execCmd_PushEmptyMultiplat();
void _box_execCmd_PushFullMultiplat();

// REMOTE COMMANDS FUNCTIONS
void _dropper_execCmd();

void _dropper_execCmd_Help();
void _dropper_execCmd_GetStatus();
void _dropper_execCmd_Sow(uint8_t channelNo, uint8_t noOfSeeds);
void _dropper_execCmd_SowExt(uint8_t channelNo, uint8_t noOfSeeds, uint8_t potNo);
void _dropper_execCmd_HomeDropper();
void _dropper_execCmd_MoveDropper(double distance_mm);
void _dropper_execCmd_Selftest();

#endif /* INC_BOX_H_ */
