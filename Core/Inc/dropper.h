#ifndef DROPPER_H
#define DROPPER_H

#include "config.h"

typedef enum {CHANNEL_1, CHANNEL_2, CHANNEL_3, CHANNEL_4, CHANNEL_5, CHANNEL_6}
_dropperChannel;

typedef enum{CASUAL, PELLETED}
_seedsType;

extern uint32_t stepCounter;

void _dropper_Init();
void _dropper_OpenChannel(_dropperChannel);
void _dropper_CloseChannel(_dropperChannel);
void _dropper_StartVibrate(_seedsType);
void _dropper_StopVibrate(_seedsType);
void _dropper_RotateTheDrum(float);

void _dropper_SelfTest();

void _dropper_StepIRQ();

#endif
