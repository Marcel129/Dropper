#include "dropper.h"

uint32_t stepCounter = 0;
bool isSeedSown = false;
dropper_t dDropper;


void dropper_StepIRQ(dropper_t * dropper){
	++stepCounter;
}

void dropper_SeedSensorIRQ(dropper_t * dropper){
	isSeedSown = true;
}

void _dropper_Init(){

//	dDropper.channels[0].name = CHANNEL_1;
//	dDropper.channels[0].port = SEED_CHANNEL_1_PORT;
//	dDropper.channels[0].pin = SEED_CHANNEL_1_PIN;
//	dDropper.channels[0].seedType = PELLETED;
//	dDropper.channels[0].status = CHANNEL_CLOSED;
//
//	dDropper.channels[1].name = CHANNEL_2;
//	dDropper.channels[1].port = SEED_CHANNEL_2_PORT;
//	dDropper.channels[1].pin = SEED_CHANNEL_2_PIN;
//	dDropper.channels[1].seedType = PELLETED;
//	dDropper.channels[1].status = CHANNEL_CLOSED;
//
//	dDropper.channels[2].name = CHANNEL_3;
//	dDropper.channels[2].port = SEED_CHANNEL_3_PORT;
//	dDropper.channels[2].pin = SEED_CHANNEL_3_PIN;
//	dDropper.channels[2].seedType = PELLETED;
//	dDropper.channels[2].status = CHANNEL_CLOSED;
//
//	dDropper.channels[3].name = CHANNEL_4;
//	dDropper.channels[3].port = SEED_CHANNEL_4_PORT;
//	dDropper.channels[3].pin = SEED_CHANNEL_4_PIN;
//	dDropper.channels[3].seedType = CASUAL;
//	dDropper.channels[3].status = CHANNEL_CLOSED;
//
//	dDropper.channels[4].name = CHANNEL_5;
//	dDropper.channels[4].port = SEED_CHANNEL_5_PORT;
//	dDropper.channels[4].pin = SEED_CHANNEL_5_PIN;
//	dDropper.channels[4].seedType = CASUAL;
//	dDropper.channels[4].status = CHANNEL_CLOSED;
//
//	dDropper.channels[5].name = CHANNEL_6;
//	dDropper.channels[5].port = SEED_CHANNEL_6_PORT;
//	dDropper.channels[5].pin = SEED_CHANNEL_6_PIN;
//	dDropper.channels[5].seedType = CASUAL;
//	dDropper.channels[5].status = CHANNEL_CLOSED;


//	for(uint8_t i = 0; i<NUMBER_OF_CHANNELS; i++){
//		HAL_GPIO_WritePin(dDropper.channels[i].port, dDropper.channels[i].pin, GPIO_PIN_SET);
//	}

//	dDropper.vibrateMotor.port = VIBRATE_MOTOR_FOR_CASUAL_SEEDS_PORT;
//	dDropper.vibrateMotor.pin = VIBRATE_MOTOR_FOR_CASUAL_SEEDS_PIN;
//	dDropper.vibrateMotor.status = MOTOR_OFF;

//	HAL_GPIO_WritePin(VIBRATE_MOTOR_FOR_CASUAL_SEEDS_PORT, VIBRATE_MOTOR_FOR_CASUAL_SEEDS_PIN, GPIO_PIN_SET);

//	HAL_GPIO_WritePin(PELLETED_SEEDS_STEPPER_EN_PORT, PELLETED_SEEDS_STEPPER_EN_PIN, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(PELLETED_SEEDS_STEPPER_DIR_PORT, PELLETED_SEEDS_STEPPER_DIR_PIN, GPIO_PIN_RESET);
//
//	HAL_GPIO_WritePin(DROPPER_STEPPER_EN_PORT, DROPPER_STEPPER_EN_PIN, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(DROPPER_STEPPER_DIR_PORT, DROPPER_STEPPER_DIR_PIN, GPIO_PIN_RESET);

//	HAL_GPIO_WritePin(UPPER_PUSHER_MOVE_FORWARD_PORT, UPPER_PUSHER_MOVE_FORWARD_Pin, GPIO_PIN_SET);
//	HAL_GPIO_WritePin(UPPER_PUSHER_MOVE_BACKWARD_PORT, UPPER_PUSHER_MOVE_BACKWARD_Pin, GPIO_PIN_SET);
//	HAL_GPIO_WritePin(LOWER_PUSHER_MOVE_FORWARD_PORT, LOWER_PUSHER_MOVE_FORWARD_Pin, GPIO_PIN_SET);
//	HAL_GPIO_WritePin(LOWER_PUSHER_MOVE_BACKWARD_PORT, LOWER_PUSHER_MOVE_BACKWARD_Pin, GPIO_PIN_SET);

//	//turn off other relays
//	HAL_GPIO_WritePin(RELAY_8_GPIO_Port, RELAY_8_Pin, GPIO_PIN_SET);
//	HAL_GPIO_WritePin(RELAY_11_GPIO_Port, RELAY_11_Pin, GPIO_PIN_SET);
//	HAL_GPIO_WritePin(RELAY_12_GPIO_Port, RELAY_12_Pin, GPIO_PIN_SET);
//	HAL_GPIO_WritePin(RELAY_13_GPIO_Port, RELAY_13_Pin, GPIO_PIN_SET);
//	HAL_GPIO_WritePin(RELAY_14_GPIO_Port, RELAY_14_Pin, GPIO_PIN_SET);

//	Communication_Init(&huart1);
//
//	dDropper.state = INITIALIZED;
}


void dropper_OpenChannel(dropperChannel_t * dc){
	HAL_GPIO_WritePin(dc->port, dc->pin, dc->lg.activeState);
	dc->status = CHANNEL_OPENED;
}

void dropper_CloseChannel(dropperChannel_t * dc){
	HAL_GPIO_WritePin(dc->port, dc->pin, dc->lg.inactiveState);
	dc->status = CHANNEL_CLOSED;
}

void dropper_StartVibrate(dropper_t * d){
	HAL_GPIO_WritePin(d->vibrateMotor.forwardPort, d->vibrateMotor.forwardPin, d->vibrateMotor.logic.activeState);
}
void dropper_StopVibrate(dropper_t * d){
	HAL_GPIO_WritePin(d->vibrateMotor.forwardPort, d->vibrateMotor.forwardPin, d->vibrateMotor.logic.inactiveState);
}

void dropper_SelfTest(dropper_t * dropper){


	dropper_OpenChannel(CHANNEL_1);
	HAL_Delay(500);
	dropper_CloseChannel(CHANNEL_1);
	HAL_Delay(500);
	dropper_OpenChannel(CHANNEL_2);
	HAL_Delay(500);
	dropper_CloseChannel(CHANNEL_2);
	HAL_Delay(500);
	dropper_OpenChannel(CHANNEL_3);
	HAL_Delay(500);
	dropper_CloseChannel(CHANNEL_3);
	HAL_Delay(500);
	dropper_OpenChannel(CHANNEL_4);
	HAL_Delay(500);
	dropper_CloseChannel(CHANNEL_4);
	HAL_Delay(500);
	dropper_OpenChannel(CHANNEL_5);
	HAL_Delay(500);
	dropper_CloseChannel(CHANNEL_5);
	HAL_Delay(500);
	dropper_OpenChannel(CHANNEL_6);
	HAL_Delay(500);
	dropper_CloseChannel(CHANNEL_6);
	HAL_Delay(500);

	dropper_StartVibrate(dropper);
	HAL_Delay(1000);
	dropper_StopVibrate(dropper);
	HAL_Delay(500);

	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 49);
	stepCounter = 0;
	while(stepCounter < 6400);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);

	HAL_Delay(500);

	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 49);
	stepCounter = 0;
	while(stepCounter < 6400);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0);
}

void dropper_DropperSetMoveDirection(dropper_t * dropper, dcMotor_moveDirection_t md){
	switch(md){
	case DCMOTOR_FORWARD:
		HAL_GPIO_WritePin(DROPPER_STEPPER_DIR_PORT, DROPPER_STEPPER_DIR_PIN, GPIO_PIN_RESET);
		break;
	case DCMOTOR_BACKWARD:
		HAL_GPIO_WritePin(DROPPER_STEPPER_DIR_PORT, DROPPER_STEPPER_DIR_PIN, GPIO_PIN_SET);
		break;
	}
}

void dropper_DrumSetMoveDirection(dropper_t * dropper, dcMotor_moveDirection_t md){
	switch(md){
	case DCMOTOR_FORWARD:
		HAL_GPIO_WritePin(PELLETED_SEEDS_STEPPER_DIR_PORT, PELLETED_SEEDS_STEPPER_EN_PIN, GPIO_PIN_RESET);
		break;
	case DCMOTOR_BACKWARD:
		HAL_GPIO_WritePin(PELLETED_SEEDS_STEPPER_DIR_PORT, PELLETED_SEEDS_STEPPER_EN_PIN, GPIO_PIN_SET);
		break;
	}
}

dropper_seedSowingStatus_t dropper_RotateDrum_deg(dropper_t * dropper, float angle_deg){

	if(angle_deg < 0){
		dropper_DrumSetMoveDirection(dropper, DCMOTOR_BACKWARD);
		angle_deg = -angle_deg;
	}
	else{
		dropper_DrumSetMoveDirection(dropper, DCMOTOR_FORWARD);
	}

	uint32_t stepsToDo = (uint32_t)((angle_deg * (float)DRUM_STEPPER_MICROSTEPPING)/DEFAULT_ANGLE_PER_STEP);

	HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_1);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 49);
	stepCounter = 0;
	isSeedSown = false;

	while(stepCounter < stepsToDo){
		if(isSeedSown){
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
			HAL_TIM_PWM_Stop_IT(&htim3, TIM_CHANNEL_1);
			return SEED_SOWN;
		}
	}

	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
	HAL_TIM_PWM_Stop_IT(&htim3, TIM_CHANNEL_1);
	return SEED_ERR;
}

void dropper_MoveDropper_mm(dropper_t * dropper, double distance_mm){

	dropper->state = MACHINE_WORKING;

	if(distance_mm < 0){
		dropper_DropperSetMoveDirection(dropper, DCMOTOR_BACKWARD);
		distance_mm = -distance_mm;
	}
	else{
		dropper_DropperSetMoveDirection(dropper, DCMOTOR_FORWARD);
	}

	float distancePerStep_mm = (DEFAULT_ANGLE_PER_STEP*PI*(float)DROPPER_STEPPER_PULLEY_DIAMETER_MM)/360.0;
	uint32_t stepsToDo = (uint32_t)((distance_mm * (float)DRUM_STEPPER_MICROSTEPPING)/distancePerStep_mm);

	HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_2);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 49);
	stepCounter = 0;
	while(stepCounter < stepsToDo);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0);
	HAL_TIM_PWM_Stop_IT(&htim3, TIM_CHANNEL_2);
}

dropper_seedSowingStatus_t dropper_SowSeeds(dropper_t * dropper, dropperChannel_t * channel ){

	//pelleted seeds
	if(channel->name == CHANNEL_1 || channel->name == CHANNEL_2 || channel->name == CHANNEL_3){

		dropper_seedSowingStatus_t isSown = SEED_ERR;
		dcMotor_moveDirection_t nextDirection = DCMOTOR_FORWARD;

		dropper_OpenChannel(channel);

		uint8_t moves = 0;

		while(moves < 12 && isSown == SEED_ERR){
			if(nextDirection == DCMOTOR_FORWARD){
				isSown = dropper_RotateDrum_deg(dropper, 30);
				nextDirection = DCMOTOR_BACKWARD;
				++moves;
			}
			else{
				isSown = dropper_RotateDrum_deg(dropper, -15);
				nextDirection = DCMOTOR_FORWARD;
			}
		}

		dropper_StartVibrate(dropper);
		HAL_Delay(400);
		dropper_StopVibrate(dropper);

		dropper_CloseChannel(channel);

		return isSown;
	}

	//casual seeds
	else if(channel->name == CHANNEL_4 || channel->name == CHANNEL_5 || channel->name == CHANNEL_6){
		dropper_OpenChannel(channel);
		HAL_Delay(100); //wait until the channel is open
		dropper_StartVibrate(CASUAL);
		HAL_Delay(SOWING_TIME_FOR_CASUAL_SEEDS_MS);
		_dropper_StopVibrate(CASUAL);
		dropper_CloseChannel(channel);

		return SEED_SOWN;
	}
}

//void _dropper_ShakeSeeds(uint32_t delayTime){
//	dropper_StartVibrate(CASUAL);
//	dropper_StartVibrate(PELLETED);
//
//	HAL_Delay(delayTime);
//
//	dropper_StopVibrate(CASUAL);
//	dropper_StopVibrate(PELLETED);
//}

void dropper_Home(dropper_t * dropper){

	uint32_t prevTime, currentTime;
	prevTime = currentTime = HAL_GetTick();

	while(dDropper.state != MACHINE_HOME){
		dropper_MoveDropper_mm(dropper, -1);

		currentTime = HAL_GetTick();

		if(currentTime - prevTime > HOMING_TIMEOUT){
			dDropper.state = MACHINE_ERROR;
			return;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////




double dropper_getChannelOffset(dropperChannel_t * channel){
	switch(channel->name){
	case CHANNEL_1: return FIRST_CHANNEL_OFFSET_MM;
	case CHANNEL_2: return SECOND_CHANNEL_OFFSET_MM;
	case CHANNEL_3: return THIRD_CHANNEL_OFFSET_MM;
	case CHANNEL_4: return FOURTH_CHANNEL_OFFSET_MM;
	case CHANNEL_5: return FIFTH_CHANNEL_OFFSET_MM;
	case CHANNEL_6: return SIXTH_CHANNEL_OFFSET_MM;
	default: return 0;
	}
}
