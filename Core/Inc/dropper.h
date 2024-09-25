#ifndef DROPPER_H
#define DROPPER_H

#include "config.h"
#include "HW_logic.h"
#include "dcMotor.h"
#include "UART_communication.h"
#include "machineStates.h"

////////////////		TYPES DEFINITIONS
typedef enum {
	CHANNEL_1,
	CHANNEL_2,
	CHANNEL_3,
	CHANNEL_4,
	CHANNEL_5,
	CHANNEL_6}
dropper_ChannelName_t;

typedef enum {
	CHANNEL_OPENED,
	CHANNEL_CLOSED}
dropper_ChannelStatus_t;

typedef enum{
	CASUAL,
	PELLETED}
dropper_SeedType_t;

typedef enum {
	SEED_SOWN,
	SEED_ERR}
dropper_seedSowingStatus_t;


////////////////		STRUCTURES DEFINITIONS

typedef struct{
	dropper_ChannelName_t name;
	dropper_SeedType_t seedType;
	dropper_ChannelStatus_t status;

	GPIO_TypeDef * port;
	uint16_t pin;

	logic_t lg;

} dropperChannel_t;

typedef struct{
	dropperChannel_t channels [NUMBER_OF_CHANNELS];
	dcMotor_t vibrateMotor;

	machineState_t state;

} dropper_t;


////////////////		VARIABLES DECLARATIONS

extern uint32_t stepCounter;
extern bool isSeedSown;
extern dropper_t dDropper;


////////////////		FUNCTIONS HEADERS

void _dropper_Init();
void dropper_OpenChannel(dropperChannel_t *);
void dropper_CloseChannel(dropperChannel_t *);
void dropper_StartVibrate(dropper_t * );
void dropper_StopVibrate(dropper_t * );
void _dropper_DropperSetMoveDirection(_stepperMoveDirection);
void _dropper_DrumSetMoveDirection(_stepperMoveDirection);
void _dropper_MoveDropper_mm(double);
dropper_seedSowingStatus_t _dropper_RotateDrum_deg(float);
double _dropper_getChannelOffset(dropper_ChannelName_t channel);

dropper_seedSowingStatus_t _dropper_SowSeeds(dropper_ChannelName_t);
void _dropper_ShakeSeeds(uint32_t);

void _dropper_SelfTest();
void _dropper_StepIRQ();
void _dropper_SeedSensorIRQ();
void _dropper_HomingSensorIRQ();

#endif //DROPPER_H
