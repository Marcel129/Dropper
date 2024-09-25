#ifndef DROPPER_H
#define DROPPER_H

#include <dcMotor.h>
#include <HardwareLogic.h>
#include <sensor.h>
#include <machineStates.h>
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

	sensor_t homingSensor;

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
void dropper_DropperSetMoveDirection(dropper_t * , dcMotor_moveDirection_t);
void dropper_DrumSetMoveDirection(dropper_t * , dcMotor_moveDirection_t);
void dropper_MoveDropper_mm(dropper_t * ,double);
dropper_seedSowingStatus_t dropper_RotateDrum_deg(dropper_t *, float);
double dropper_getChannelOffset(dropperChannel_t *);
void dropper_Home(dropper_t *);

dropper_seedSowingStatus_t dropper_SowSeeds(dropper_t *, dropperChannel_t *);
//void _dropper_ShakeSeeds(uint32_t);

void dropper_SelfTest(dropper_t *);
void dropper_StepIRQ(dropper_t *);
void dropper_SeedSensorIRQ(dropper_t *);

#endif //DROPPER_H
