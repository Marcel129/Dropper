#include "box.h"

box_t box;

void dropper_HomingSensorIRQ(box_t * mBox){
	mBox->dropper.state = MACHINE_HOME;
}

void box_Init(box_t * mBox){

	//PIN ASSIGMENT
	mBox->lowerPusher.minEndstop.port = EMPTY_MULTIPLAT_PUSHER_MIN_ENDSTOP_PORT;
	mBox->lowerPusher.minEndstop.pin = EMPTY_MULTIPLAT_PUSHER_MIN_ENDSTOP_PIN;
	mBox->lowerPusher.maxEndstop.port = EMPTY_MULTIPLAT_PUSHER_MAX_ENDSTOP_PORT;
	mBox->lowerPusher.maxEndstop.pin = EMPTY_MULTIPLAT_PUSHER_MAX_ENDSTOP_PIN;
	mBox->lowerPusher.homingTimeout = HOMING_LOWER_PUSHER_MAX_TIMEOUT_MS;

	mBox->lowerPusher.motor.forwardPort = LOWER_PUSHER_MOVE_FORWARD_PORT;
	mBox->lowerPusher.motor.forwardPin = LOWER_PUSHER_MOVE_FORWARD_Pin;
	mBox->lowerPusher.motor.backwardPort = LOWER_PUSHER_MOVE_BACKWARD_PORT;
	mBox->lowerPusher.motor.backwardPin = LOWER_PUSHER_MOVE_BACKWARD_Pin;
	HW_logic_setLogic(&(mBox->lowerPusher.motor.logic), LOW_IS_ACTVE);


	mBox->upperPusher.minEndstop.port = FULL_MULTIPLAT_PUSHER_MIN_ENDSTOP_PORT;
	mBox->upperPusher.minEndstop.pin = FULL_MULTIPLAT_PUSHER_MIN_ENDSTOP_PIN;
	mBox->upperPusher.maxEndstop.port = FULL_MULTIPLAT_PUSHER_MAX_ENDSTOP_PORT;
	mBox->upperPusher.maxEndstop.pin = FULL_MULTIPLAT_PUSHER_MAX_ENDSTOP_PIN;
	mBox->upperPusher.homingTimeout = HOMING_UPPER_PUSHER_MAX_TIMEOUT_MS;

	mBox->upperPusher.motor.forwardPort = UPPER_PUSHER_MOVE_FORWARD_PORT;
	mBox->upperPusher.motor.forwardPin = UPPER_PUSHER_MOVE_FORWARD_Pin;
	mBox->upperPusher.motor.backwardPort = UPPER_PUSHER_MOVE_BACKWARD_PORT;
	mBox->upperPusher.motor.backwardPin = UPPER_PUSHER_MOVE_BACKWARD_Pin;
	HW_logic_setLogic(&(mBox->upperPusher.motor.logic), LOW_IS_ACTVE);


	mBox->dropper.channels[0].name = CHANNEL_1;
	mBox->dropper.channels[0].port = SEED_CHANNEL_1_PORT;
	mBox->dropper.channels[0].pin = SEED_CHANNEL_1_PIN;
	mBox->dropper.channels[0].seedType = PELLETED;
	mBox->dropper.channels[0].status = CHANNEL_CLOSED;

	mBox->dropper.channels[1].name = CHANNEL_2;
	mBox->dropper.channels[1].port = SEED_CHANNEL_2_PORT;
	mBox->dropper.channels[1].pin = SEED_CHANNEL_2_PIN;
	mBox->dropper.channels[1].seedType = PELLETED;
	mBox->dropper.channels[1].status = CHANNEL_CLOSED;

	mBox->dropper.channels[2].name = CHANNEL_3;
	mBox->dropper.channels[2].port = SEED_CHANNEL_3_PORT;
	mBox->dropper.channels[2].pin = SEED_CHANNEL_3_PIN;
	mBox->dropper.channels[2].seedType = PELLETED;
	mBox->dropper.channels[2].status = CHANNEL_CLOSED;

	mBox->dropper.channels[3].name = CHANNEL_4;
	mBox->dropper.channels[3].port = SEED_CHANNEL_4_PORT;
	mBox->dropper.channels[3].pin = SEED_CHANNEL_4_PIN;
	mBox->dropper.channels[3].seedType = CASUAL;
	mBox->dropper.channels[3].status = CHANNEL_CLOSED;

	mBox->dropper.channels[4].name = CHANNEL_5;
	mBox->dropper.channels[4].port = SEED_CHANNEL_5_PORT;
	mBox->dropper.channels[4].pin = SEED_CHANNEL_5_PIN;
	mBox->dropper.channels[4].seedType = CASUAL;
	mBox->dropper.channels[4].status = CHANNEL_CLOSED;

	mBox->dropper.channels[5].name = CHANNEL_6;
	mBox->dropper.channels[5].port = SEED_CHANNEL_6_PORT;
	mBox->dropper.channels[5].pin = SEED_CHANNEL_6_PIN;
	mBox->dropper.channels[5].seedType = CASUAL;
	mBox->dropper.channels[5].status = CHANNEL_CLOSED;


	mBox->dropper.vibrateMotor.forwardPort = VIBRATE_MOTOR_FOR_CASUAL_SEEDS_PORT;
	mBox->dropper.vibrateMotor.forwardPin = VIBRATE_MOTOR_FOR_CASUAL_SEEDS_PIN;
	HW_logic_setLogic(&(mBox->dropper.vibrateMotor.logic), LOW_IS_ACTVE);


	mBox->box_Communication_Handler = &box_main_UART;
	Communication_Init(&(mBox->box_Communication_Handler), &huart1);

	//HW INITIALIZING
	for(uint8_t i = 0; i<NUMBER_OF_CHANNELS; i++){
		dropper_CloseChannel(&(mBox->dropper.channels[i]));
	}

	dcMotor_stop(&(mBox->dropper.vibrateMotor));
	dcMotor_stop(&(mBox->upperPusher.motor));
	dcMotor_stop(&(mBox->lowerPusher.motor));

	HAL_GPIO_WritePin(PELLETED_SEEDS_STEPPER_EN_PORT, PELLETED_SEEDS_STEPPER_EN_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PELLETED_SEEDS_STEPPER_DIR_PORT, PELLETED_SEEDS_STEPPER_DIR_PIN, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(DROPPER_STEPPER_EN_PORT, DROPPER_STEPPER_EN_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(DROPPER_STEPPER_DIR_PORT, DROPPER_STEPPER_DIR_PIN, GPIO_PIN_RESET);

	//turn off other relays
	HAL_GPIO_WritePin(RELAY_8_GPIO_Port, RELAY_8_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(RELAY_11_GPIO_Port, RELAY_11_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(RELAY_12_GPIO_Port, RELAY_12_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(RELAY_13_GPIO_Port, RELAY_13_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(RELAY_14_GPIO_Port, RELAY_14_Pin, GPIO_PIN_SET);
}

void box_execCmd_SowRow(box_t * mBox, uint8_t channelNo){

	static uint8_t rowNo = 0;
	double distanceToGo = 0;

	if(rowNo == 0){
		_dropper_execCmd_HomeDropper(&mBox->dropper);
		rowNo = 1;
	}

	if(rowNo == 1){
		dropper_MoveDropper_mm(&mBox->dropper, DISTANCE_TO_THE_FIRST_POT_MM + dropper_getChannelOffset(channelNo));
		distanceToGo = DISTANCE_BETWEEN_CENTERS_OF_TWO_POTS_MM;
	}
	else if(rowNo == 3 || rowNo == 5){
		distanceToGo = DISTANCE_BETWEEN_CENTERS_OF_TWO_POTS_MM;
	}
	else if(rowNo == 2 || rowNo == 4){
		distanceToGo = -DISTANCE_BETWEEN_CENTERS_OF_TWO_POTS_MM;
	}

	uint8_t trials = 0;
	for(uint8_t i=0; i<4; ++i){
		if(dropper_SowSeeds(&mBox->dropper, &mBox->dropper.channels[channelNo]) != SEED_SOWN){
			if(++trials > NUMBER_OF_SOWING_TRIALS){
				trials = 0;
				Communication_SendMsg(&(mBox->box_Communication_Handler), "Sowing fail\r\n");
			}
			else{
				--i;
				continue;
			}
		}

		if(i == 3) break;// skip last move
		dropper_MoveDropper_mm(&mBox->dropper, distanceToGo);
	}

	if(++rowNo > 5)	rowNo = 0;

	Communication_SendMsg(&(mBox->box_Communication_Handler), CMD_EXEC_SUCCESFULLY_MSG);
}

void box_execCmd_PushEmptyMultiplat(box_t * mBox){

	uint32_t prevTime, currentTime;
	prevTime = currentTime = HAL_GetTick();

	HAL_GPIO_WritePin(LOWER_PUSHER_MOVE_BACKWARD_PORT, LOWER_PUSHER_MOVE_BACKWARD_Pin, GPIO_PIN_RESET);

	while(HAL_GPIO_ReadPin(EMPTY_MULTIPLAT_PUSHER_MIN_ENDSTOP_PORT, EMPTY_MULTIPLAT_PUSHER_MIN_ENDSTOP_PIN) == GPIO_PIN_SET){
		currentTime = HAL_GetTick();
		if(currentTime - prevTime > PUSHING_EMPTY_MULTIPLAT_MAX_TIMEOUT_MS){
			Communication_SendMsg(&(mBox->box_Communication_Handler), MOVING_ERROR_TIMEOUT_MSG);
			return;
		}
	}

	HAL_GPIO_WritePin(LOWER_PUSHER_MOVE_BACKWARD_PORT, LOWER_PUSHER_MOVE_BACKWARD_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LOWER_PUSHER_MOVE_FORWARD_PORT, LOWER_PUSHER_MOVE_FORWARD_Pin, GPIO_PIN_RESET);

	prevTime = currentTime = HAL_GetTick();

	while(HAL_GPIO_ReadPin(EMPTY_MULTIPLAT_PUSHER_MAX_ENDSTOP_PORT, EMPTY_MULTIPLAT_PUSHER_MAX_ENDSTOP_PIN) == GPIO_PIN_SET){
		currentTime = HAL_GetTick();
		if(currentTime - prevTime > PUSHING_EMPTY_MULTIPLAT_MAX_TIMEOUT_MS){
			Communication_SendMsg(&(mBox->box_Communication_Handler), MOVING_ERROR_TIMEOUT_MSG);
			return;
		}
	}

	HAL_GPIO_WritePin(LOWER_PUSHER_MOVE_FORWARD_PORT, LOWER_PUSHER_MOVE_FORWARD_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LOWER_PUSHER_MOVE_BACKWARD_PORT, LOWER_PUSHER_MOVE_BACKWARD_Pin, GPIO_PIN_RESET);

	prevTime = currentTime = HAL_GetTick();

	while(HAL_GPIO_ReadPin(EMPTY_MULTIPLAT_PUSHER_MIN_ENDSTOP_PORT, EMPTY_MULTIPLAT_PUSHER_MIN_ENDSTOP_PIN) == GPIO_PIN_SET){
		currentTime = HAL_GetTick();
		if(currentTime - prevTime > PUSHING_EMPTY_MULTIPLAT_MAX_TIMEOUT_MS){
			Communication_SendMsg(&(mBox->box_Communication_Handler), MOVING_ERROR_TIMEOUT_MSG);
			return;
		}
	}

	HAL_GPIO_WritePin(LOWER_PUSHER_MOVE_BACKWARD_PORT, LOWER_PUSHER_MOVE_BACKWARD_Pin, GPIO_PIN_SET);

	Communication_SendMsg(&(mBox->box_Communication_Handler), CMD_EXEC_SUCCESFULLY_MSG);
}

void box_execCmd_PushFullMultiplat(box_t * mBox){

}


///////////////////////////////////////////////////////////////////////////////////////////

void _dropper_execCmd(box_t * mBox){
	command cmd;
	int8_t paramsNo = Communication_DecodeMsg(&mBox->box_Communication_Handler, &cmd);
	if(paramsNo == -1){
		Communication_SendMsg(&mBox->box_Communication_Handler, REJECTION_MSG);
		return; //invalid command
	}

	else if(strcmp(cmd.cmdName, CMD_HOME) == 0){
		Communication_SendMsg(&mBox->box_Communication_Handler, CONFIRMATION_MSG);
		_dropper_execCmd_HomeDropper(mBox);
	}

	else if(strcmp(cmd.cmdName, CMD_HELP) == 0){
		Communication_SendMsg(&mBox->box_Communication_Handler, CONFIRMATION_MSG);
		_dropper_execCmd_Help(mBox);
	}

	else if(strcmp(cmd.cmdName, CMD_SEND_STATUS) == 0){
		Communication_SendMsg(&mBox->box_Communication_Handler, CONFIRMATION_MSG);
		_dropper_execCmd_GetStatus(mBox);
	}

	else if(strcmp(cmd.cmdName, CMD_SELFTEST) == 0){
		Communication_SendMsg(&mBox->box_Communication_Handler, CONFIRMATION_MSG);
		_dropper_execCmd_Selftest(mBox);
	}

	else if(strcmp(cmd.cmdName, CMD_PUSH_FULL_MULTIPLAT) == 0){
		Communication_SendMsg(&mBox->box_Communication_Handler, CONFIRMATION_MSG);
		box_execCmd_PushFullMultiplat(mBox);
	}

	else if(strcmp(cmd.cmdName, CMD_PUSH_EMPTY_MULTIPLAT) == 0){
		Communication_SendMsg(&mBox->box_Communication_Handler, CONFIRMATION_MSG);
		box_execCmd_PushEmptyMultiplat(mBox);
	}

	else if(strcmp(cmd.cmdName, CMD_MOVE_DROPPER) == 0){
		if(paramsNo != 1){
			Communication_SendMsg(&mBox->box_Communication_Handler, INVALID_ARGUMET_MSG);
		}
		else{
			Communication_SendMsg(&mBox->box_Communication_Handler, CONFIRMATION_MSG);
			_dropper_execCmd_MoveDropper(mBox, cmd.params[0]);
		}
	}

	else if(strcmp(cmd.cmdName, CMD_SOW_ROW) == 0){
		if(paramsNo != 1){
			Communication_SendMsg(&mBox->box_Communication_Handler, INVALID_ARGUMET_MSG);
		}
		else{
			Communication_SendMsg(&mBox->box_Communication_Handler, CONFIRMATION_MSG);
			box_execCmd_SowRow(mBox, (uint8_t)cmd.params[0]);
		}
	}

	else if(strcmp(cmd.cmdName, CMD_MOVE_PUSHER) == 0){
		if(paramsNo != 2){
			Communication_SendMsg(&mBox->box_Communication_Handler, INVALID_ARGUMET_MSG);
		}
		else{
			Communication_SendMsg(&mBox->box_Communication_Handler, CONFIRMATION_MSG);
			_box_execCmd_MovePusher(mBox, (uint8_t)cmd.params[0], (dcMotor_moveDirection_t)cmd.params[1]);
		}
	}

	else if(strcmp(cmd.cmdName, CMD_SOW) == 0){
		if(paramsNo != 2){
			Communication_SendMsg(&mBox->box_Communication_Handler, INVALID_ARGUMET_MSG);
		}
		else{
			Communication_SendMsg(&mBox->box_Communication_Handler, CONFIRMATION_MSG);
			_dropper_execCmd_Sow(mBox, (uint8_t)cmd.params[0], (uint8_t)cmd.params[1]);
		}
	}

	else{
		Communication_SendMsg(&mBox->box_Communication_Handler, REJECTION_MSG);
	}
}

void _dropper_execCmd_Help(box_t * mBox){
	Communication_SendMsg(&mBox->box_Communication_Handler, HELP_TEXT);
}

void _dropper_execCmd_GetStatus(box_t * mBox){

}

void _dropper_execCmd_Sow(box_t * mBox, uint8_t channelNo, uint8_t noOfSeeds){
	if(channelNo > NUMBER_OF_CHANNELS || channelNo < 1){
		Communication_SendMsg(&mBox->box_Communication_Handler, INVALID_ARGUMET_MSG);
		return;
	}

	if(noOfSeeds > MAX_SOWS_AT_ONCE) noOfSeeds = MAX_SOWS_AT_ONCE;

	for(uint8_t i = 0; i<noOfSeeds; i++){
		if(dropper_SowSeeds(&mBox->dropper,&mBox->dropper.channels[channelNo - 1]) == SEED_SOWN){
			Communication_SendMsg(&mBox->box_Communication_Handler, CMD_EXEC_SUCCESFULLY_MSG);
		}
		else{
			Communication_SendMsg(&mBox->box_Communication_Handler, CMD_EXEC_FAILED_MSG);
		}
	}

}

void _dropper_execCmd_SowExt(box_t * mBox, uint8_t channelNo, uint8_t noOfSeeds, uint8_t potNo){

}

void _dropper_execCmd_HomeDropper(box_t * mBox){
	dropper_Home(&mBox->dropper&mBox->dropper);
}

void _dropper_execCmd_MoveDropper(box_t * mBox, double distance_mm){
	dropper_MoveDropper_mm(&mBox->dropper, distance_mm);
}

void _dropper_execCmd_Selftest(box_t * mBox){

	Communication_SendMsg(&mBox->box_Communication_Handler, SELFTEST_INTRO);

	uint32_t prevTime, currentTime, msgLen;
	SELFTEST_SINGLETEST_TIMEOUT_MS;
	prevTime = currentTime = HAL_GetTick();

	uint8_t tmbBuff[100] = {0};

	for(uint8_t i = 0; i<NUMBER_OF_CHANNELS; i++){

		HAL_GPIO_WritePin(dDropper.channels[i].port, dDropper.channels[i].pin, GPIO_PIN_RESET);
		msgLen = sprintf(tmbBuff, "Otwarto kanal %d   \r\n", i+1);
		Communication_SendMsg(&mBox->box_Communication_Handler, tmbBuff);

		while(currentTime - prevTime < SELFTEST_SINGLETEST_TIMEOUT_MS){
			currentTime = HAL_GetTick();
			if(box_main_UART.msgReadyToRead){
				if(strncmp(box_main_UART.rxBuffer, "t", 1) == 0) {
					Communication_ClearRxBuffer(&mBox->box_Communication_Handler, );
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
