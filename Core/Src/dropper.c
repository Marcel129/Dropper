#include "dropper.h"

uint32_t stepCounter = 0;
bool isSeedSown = false;
dropper_t dDropper;


void _dropper_StepIRQ(){
	++stepCounter;
}

void _dropper_SeedSensorIRQ(){
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

	Communication_Init(&huart1);

	dDropper.state = INITIALIZED;
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

void _dropper_SelfTest(){


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

	dropper_StartVibrate();
	HAL_Delay(1000);
	dropper_StopVibrate();
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

void _dropper_DropperSetMoveDirection(_stepperMoveDirection md){
	switch(md){
	case FORWARD:
		HAL_GPIO_WritePin(DROPPER_STEPPER_DIR_PORT, DROPPER_STEPPER_DIR_PIN, GPIO_PIN_RESET);
		break;
	case BACKWARD:
		HAL_GPIO_WritePin(DROPPER_STEPPER_DIR_PORT, DROPPER_STEPPER_DIR_PIN, GPIO_PIN_SET);
		break;
	}
}

void _dropper_DrumSetMoveDirection(_stepperMoveDirection md){
	switch(md){
	case FORWARD:
		HAL_GPIO_WritePin(PELLETED_SEEDS_STEPPER_DIR_PORT, PELLETED_SEEDS_STEPPER_EN_PIN, GPIO_PIN_RESET);
		break;
	case BACKWARD:
		HAL_GPIO_WritePin(PELLETED_SEEDS_STEPPER_DIR_PORT, PELLETED_SEEDS_STEPPER_EN_PIN, GPIO_PIN_SET);
		break;
	}
}

dropper_seedSowingStatus_t _dropper_RotateDrum_deg(float angle_deg){

	if(angle_deg < 0){
		_dropper_DrumSetMoveDirection(BACKWARD);
		angle_deg = -angle_deg;
	}
	else{
		_dropper_DrumSetMoveDirection(FORWARD);
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

void _dropper_MoveDropper_mm(double distance_mm){

	dDropper.state = WORKING;

	if(distance_mm < 0){
		_dropper_DropperSetMoveDirection(BACKWARD);
		distance_mm = -distance_mm;
	}
	else{
		_dropper_DropperSetMoveDirection(FORWARD);
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

dropper_seedSowingStatus_t _dropper_SowSeeds(dropper_ChannelName_t channel ){

	//pelleted seeds
	if(channel == CHANNEL_1 || channel == CHANNEL_2 || channel == CHANNEL_3){

		dropper_seedSowingStatus_t isSown = SEED_ERR;
		_stepperMoveDirection nextDirection = FORWARD;

		dropper_OpenChannel(channel);

		uint8_t moves = 0;

		while(moves < 12 && isSown == SEED_ERR){
			if(nextDirection == FORWARD){
				isSown = _dropper_RotateDrum_deg(30);
				nextDirection = BACKWARD;
				++moves;
			}
			else{
				isSown = _dropper_RotateDrum_deg(-15);
				nextDirection = FORWARD;
			}
		}

		dropper_StartVibrate();
		HAL_Delay(400);
		dropper_StopVibrate();

		dropper_CloseChannel(channel);

		return isSown;
	}

	//casual seeds
	else if(channel == CHANNEL_4 || channel == CHANNEL_5 || channel == CHANNEL_6){
		dropper_OpenChannel(channel);
		HAL_Delay(100); //wait until the channel is open
		dropper_StartVibrate(CASUAL);
		HAL_Delay(SOWING_TIME_FOR_CASUAL_SEEDS_MS);
		_dropper_StopVibrate(CASUAL);
		dropper_CloseChannel(channel);

		return SEED_SOWN;
	}
}

void _dropper_ShakeSeeds(uint32_t delayTime){
	dropper_StartVibrate(CASUAL);
	dropper_StartVibrate(PELLETED);

	HAL_Delay(delayTime);

	dropper_StopVibrate(CASUAL);
	dropper_StopVibrate(PELLETED);
}

void _dropper_Home(){

	uint32_t prevTime, currentTime;
	prevTime = currentTime = HAL_GetTick();

	while(dDropper.state != HOME){
		_dropper_MoveDropper_mm(-1);

		currentTime = HAL_GetTick();

		if(currentTime - prevTime > HOMING_TIMEOUT){
			dDropper.state = STATE_ERR;
			Communication_SendMsg(MOVING_ERROR_TIMEOUT_MSG);
			return;
		}
	}

	Communication_SendMsg(CMD_EXEC_SUCCESFULLY_MSG);
}

///////////////////////////////////////////////////////////////////////////////////////////

void _dropper_execCmd(){
	command cmd;
	int8_t paramsNo = Communication_DecodeMsg(&cmd);
	if(paramsNo == -1){
		Communication_SendMsg(REJECTION_MSG);
		return; //invalid command
	}

	else if(strcmp(cmd.cmdName, CMD_HOME) == 0){
		Communication_SendMsg(CONFIRMATION_MSG);
		_dropper_execCmd_HomeDropper();
	}

	else if(strcmp(cmd.cmdName, CMD_HELP) == 0){
		Communication_SendMsg(CONFIRMATION_MSG);
		_dropper_execCmd_Help();
	}

	else if(strcmp(cmd.cmdName, CMD_SEND_STATUS) == 0){
		Communication_SendMsg(CONFIRMATION_MSG);
		_dropper_execCmd_GetStatus();
	}

	else if(strcmp(cmd.cmdName, CMD_SELFTEST) == 0){
		Communication_SendMsg(CONFIRMATION_MSG);
		_dropper_execCmd_Selftest();
	}

	else if(strcmp(cmd.cmdName, CMD_PUSH_FULL_MULTIPLAT) == 0){
		Communication_SendMsg(CONFIRMATION_MSG);
		_box_execCmd_PushFullMultiplat();
	}

	else if(strcmp(cmd.cmdName, CMD_PUSH_EMPTY_MULTIPLAT) == 0){
		Communication_SendMsg(CONFIRMATION_MSG);
		_box_execCmd_PushEmptyMultiplat();
	}

	else if(strcmp(cmd.cmdName, CMD_MOVE_DROPPER) == 0){
		if(paramsNo != 1){
			Communication_SendMsg(INVALID_ARGUMET_MSG);
		}
		else{
			Communication_SendMsg(CONFIRMATION_MSG);
			_dropper_execCmd_MoveDropper(cmd.params[0]);
		}
	}

	else if(strcmp(cmd.cmdName, CMD_SOW_ROW) == 0){
		if(paramsNo != 1){
			Communication_SendMsg(INVALID_ARGUMET_MSG);
		}
		else{
			Communication_SendMsg(CONFIRMATION_MSG);
			_box_execCmd_SowRow((uint8_t)cmd.params[0]);
		}
	}

	else if(strcmp(cmd.cmdName, CMD_MOVE_PUSHER) == 0){
		if(paramsNo != 2){
			Communication_SendMsg(INVALID_ARGUMET_MSG);
		}
		else{
			Communication_SendMsg(CONFIRMATION_MSG);
			_box_execCmd_MovePusher((uint8_t)cmd.params[0], (_stepperMoveDirection)cmd.params[1]);
		}
	}

	else if(strcmp(cmd.cmdName, CMD_SOW) == 0){
		if(paramsNo != 2){
			Communication_SendMsg(INVALID_ARGUMET_MSG);
		}
		else{
			Communication_SendMsg(CONFIRMATION_MSG);
			_dropper_execCmd_Sow((uint8_t)cmd.params[0], (uint8_t)cmd.params[1]);
		}
	}

	else{
		Communication_SendMsg(REJECTION_MSG);
	}
}

void _dropper_execCmd_Help(){
	Communication_SendMsg(HELP_TEXT);
}

void _dropper_execCmd_GetStatus(){

}

void _dropper_execCmd_Sow(uint8_t channelNo, uint8_t noOfSeeds){
	if(channelNo > NUMBER_OF_CHANNELS || channelNo < 1){
		Communication_SendMsg(INVALID_ARGUMET_MSG);
		return;
	}

	if(noOfSeeds > MAX_SOWS_AT_ONCE) noOfSeeds = MAX_SOWS_AT_ONCE;

	for(uint8_t i = 0; i<noOfSeeds; i++){
		if(_dropper_SowSeeds((dropper_ChannelName_t)channelNo - 1) == SEED_SOWN){
			Communication_SendMsg(CMD_EXEC_SUCCESFULLY_MSG);
		}
		else{
			Communication_SendMsg(CMD_EXEC_FAILED_MSG);
		}
	}

}

void _dropper_execCmd_SowExt(uint8_t channelNo, uint8_t noOfSeeds, uint8_t potNo){

}

void _dropper_execCmd_HomeDropper(){
	_dropper_Home();
}

void _dropper_execCmd_MoveDropper(double distance_mm){
	_dropper_MoveDropper_mm(distance_mm);
}

void _dropper_execCmd_Selftest(){

	Communication_SendMsg(SELFTEST_INTRO);

	uint32_t prevTime, currentTime;
	SELFTEST_SINGLETEST_TIMEOUT_MS;
	prevTime = currentTime = HAL_GetTick();

	uint8_t tmbBuff[100] = {0};

	for(uint8_t i = 0; i<NUMBER_OF_CHANNELS; i++){

		HAL_GPIO_WritePin(dDropper.channels[i].port, dDropper.channels[i].pin, GPIO_PIN_RESET);
		msgLen = sprintf(tmbBuff, "Otwarto kanal %d   \r\n", i+1);
		Communication_SendMsg(tmbBuff);

		while(currentTime - prevTime < SELFTEST_SINGLETEST_TIMEOUT_MS){
			currentTime = HAL_GetTick();
			if(box_main_UART.msgReadyToRead){
				if(strncmp(box_main_UART.rxBuffer, "t", 1) == 0) {
					Communication_ClearRxBuffer();
					break;
				}
			}
		}
	}


	//	dropper_OpenChannel(CHANNEL_1);
	//	HAL_Delay(500);
	//	dropper_CloseChannel(CHANNEL_1);
	//	HAL_Delay(500);
	//	dropper_OpenChannel(CHANNEL_2);
	//	HAL_Delay(500);
	//	dropper_CloseChannel(CHANNEL_2);
	//	HAL_Delay(500);
	//	dropper_OpenChannel(CHANNEL_3);
	//	HAL_Delay(500);
	//	dropper_CloseChannel(CHANNEL_3);
	//	HAL_Delay(500);
	//	dropper_OpenChannel(CHANNEL_4);
	//	HAL_Delay(500);
	//	dropper_CloseChannel(CHANNEL_4);
	//	HAL_Delay(500);
	//	dropper_OpenChannel(CHANNEL_5);
	//	HAL_Delay(500);
	//	dropper_CloseChannel(CHANNEL_5);
	//	HAL_Delay(500);
	//	dropper_OpenChannel(CHANNEL_6);
	//	HAL_Delay(500);
	//	dropper_CloseChannel(CHANNEL_6);
	//	HAL_Delay(500);
	//
	//	_dropper_StartVibrate();
	//	HAL_Delay(1000);
	//	dropper_StopVibrate();
	//	HAL_Delay(500);
	//	//	dropper_StartVibrate(PELLETED);
	//	//	HAL_Delay(1000);
	//	//	dropper_StopVibrate(PELLETED);
	//
	//	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 49);
	//	stepCounter = 0;
	//	while(stepCounter < 6400);
	//	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
	//
	//	HAL_Delay(500);
	//
	//	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 49);
	//	stepCounter = 0;
	//	while(stepCounter < 6400);
	//	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0);
}


double _dropper_getChannelOffset(dropper_ChannelName_t channel){
	switch(channel){
	case CHANNEL_1: return FIRST_CHANNEL_OFFSET_MM;
	case CHANNEL_2: return SECOND_CHANNEL_OFFSET_MM;
	case CHANNEL_3: return THIRD_CHANNEL_OFFSET_MM;
	case CHANNEL_4: return FOURTH_CHANNEL_OFFSET_MM;
	case CHANNEL_5: return FIFTH_CHANNEL_OFFSET_MM;
	case CHANNEL_6: return SIXTH_CHANNEL_OFFSET_MM;
	default: return 0;
	}
}
