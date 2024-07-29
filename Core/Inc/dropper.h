#ifndef DROPPER_H
#define DROPPER_H

#include "config.h"

////////////////		VARIABLES DECLARATIONS
extern uint32_t stepCounter;


////////////////		TYPES DECLARATIONS
typedef enum {
	CHANNEL_1,
	CHANNEL_2,
	CHANNEL_3,
	CHANNEL_4,
	CHANNEL_5,
	CHANNEL_6}
_dropperChannelName;

typedef enum{CASUAL, PELLETED}
_seedsType;

typedef enum{FORWARD, BACKWARD}
_stepperMoveDirection;

typedef enum {IDLE, WORKING, ERROR}
_dropperState;


////////////////		STRUCTURES DECLARATIONS

typedef struct{
	_seedsType sType;
	_dropperChannelName chName;
	GPIO_TypeDef * chPort;
	uint16_t chPin;
} _dropperChannel;

typedef struct{
	_seedsType sType;
	GPIO_TypeDef * chPort;
	uint16_t chPin;
}_dropperVibrateMotor;

typedef struct {
	_dropperState currentState;
	bool sowingPelletedSeedError;
	bool homingError;
}_atateStructure;

typedef struct{
	_dropperState dState;
	_dropperChannel channels [NUMBER_OF_CHANNELS];
	_dropperVibrateMotor vibrateMotors [NUMBER_OF_VIBRATE_MOTORS];
}_dropperChannel;


////////////////		FUNCTIONS DECLARATIONS

void _dropper_Init();
void _dropper_OpenChannel(_dropperChannelName);
void _dropper_CloseChannel(_dropperChannelName);
void _dropper_StartVibrate(_seedsType);
void _dropper_StopVibrate(_seedsType);
void _dropper_RotateDrum_deg(float);
void _dropper_MoveDropper_mm(float);
void _dropper_DropperSetMoveDirection(_stepperMoveDirection);
void _dropper_DrumSetMoveDirection(_stepperMoveDirection);

void _dropper_SowSeeds(_dropperChannelName);
void _dropper_ShakeSeeds(uint32_t);
void _dropper_Home();

void _dropper_SelfTest();
void _dropper_StepIRQ();

#endif
