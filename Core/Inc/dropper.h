#ifndef DROPPER_H
#define DROPPER_H

#include "config.h"
#include "UART_communication.h"

////////////////		TYPES DEFINITIONS
typedef enum {
	CHANNEL_1,
	CHANNEL_2,
	CHANNEL_3,
	CHANNEL_4,
	CHANNEL_5,
	CHANNEL_6}
_dropperChannelName;

typedef enum {
	CHANNEL_OPENED,
	CHANNEL_CLOSED}
_dropperChannelStatus;

typedef enum {
	MOTOR_ON,
	MOTOR_OFF}
_dropperVibrateMotorStatus;

typedef enum{
	CASUAL,
	PELLETED}
_seedsType;

typedef enum{
	FORWARD,
	BACKWARD}
_stepperMoveDirection;

typedef enum {
	IDLE,
	INITIALIZED,
	WORKING,
	HOME,
	STATE_ERR}
_dropperState;

typedef enum {
	SEED_SOWN,
	SEED_ERR}
_seedSowingStatus;


////////////////		STRUCTURES DEFINITIONS

typedef struct{
	_dropperChannelName name;
	_seedsType seedType;
	_dropperChannelStatus status;

	GPIO_TypeDef * port;
	uint16_t pin;

} _dropperChannel;

typedef struct{
//	_seedsType seedType;
	GPIO_TypeDef * port;
	uint16_t pin;

	_dropperVibrateMotorStatus status;

}_dropperVibrateMotor;

typedef struct{
	_dropperState state;
	_dropperChannel channels [NUMBER_OF_CHANNELS];
	_dropperVibrateMotor vibrateMotor;

}_dropper;


////////////////		VARIABLES DECLARATIONS

extern uint32_t stepCounter;
extern bool isSeedSown;
extern _dropper dDropper;


////////////////		FUNCTIONS HEADERS

void _dropper_Init();
void _dropper_OpenChannel(_dropperChannelName);
void _dropper_CloseChannel(_dropperChannelName);
void _dropper_StartVibrate();
void _dropper_StopVibrate();
_seedSowingStatus _dropper_RotateDrum_deg(float);
void _dropper_MoveDropper_mm(float);
void _dropper_DropperSetMoveDirection(_stepperMoveDirection);
void _dropper_DrumSetMoveDirection(_stepperMoveDirection);

bool _dropper_SowSeeds(_dropperChannelName);
void _dropper_ShakeSeeds(uint32_t);
void _dropper_Home();

void _dropper_SelfTest();
void _dropper_StepIRQ();
void _dropper_SeedSensorIRQ();
void _dropper_HomingSensorIRQ();


// REMOTE COMMANDS FUNCTIONS
void _dropper_execCmd();

void _dropper_execCmd_Help();
void _dropper_execCmd_GetStatus();
void _dropper_execCmd_Sow(uint8_t channelNo, uint8_t noOfSeeds);
void _dropper_execCmd_SowExt(uint8_t channelNo, uint8_t noOfSeeds, uint8_t potNo);
void _dropper_execCmd_HomeDropper();
void _dropper_execCmd_MoveDropper(uint32_t distance_mm);

#define HELP_TEXT "AVAILABLE FUNCTIONS\r\n\
		H10 - help, list avaiable commands\r\n\
		G11 - home the dropper\r\n\
		G12 - send dropper status\r\n"

#endif //DROPPER_H
