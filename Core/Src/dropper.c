#include "dropper.h"

uint32_t stepCounter = 0;
bool isSeedSown = false;
_dropper dDropper;


void _dropper_StepIRQ(){
	++stepCounter;
}

void _dropper_SeedSensorIRQ(){
	isSeedSown = true;
}

void _dropper_HomingSensorIRQ(){
	dDropper.state = HOME;
}

void _dropper_Init(){

	dDropper.channels[0].name = CHANNEL_1;
	dDropper.channels[0].port = SEED_CHANNEL_1_PORT;
	dDropper.channels[0].pin = SEED_CHANNEL_1_PIN;
	dDropper.channels[0].seedType = PELLETED;
	dDropper.channels[0].status = CHANNEL_CLOSED;

	dDropper.channels[1].name = CHANNEL_2;
	dDropper.channels[1].port = SEED_CHANNEL_2_PORT;
	dDropper.channels[1].pin = SEED_CHANNEL_2_PIN;
	dDropper.channels[1].seedType = PELLETED;
	dDropper.channels[1].status = CHANNEL_CLOSED;

	dDropper.channels[2].name = CHANNEL_3;
	dDropper.channels[2].port = SEED_CHANNEL_3_PORT;
	dDropper.channels[2].pin = SEED_CHANNEL_3_PIN;
	dDropper.channels[2].seedType = PELLETED;
	dDropper.channels[2].status = CHANNEL_CLOSED;

	dDropper.channels[3].name = CHANNEL_4;
	dDropper.channels[3].port = SEED_CHANNEL_4_PORT;
	dDropper.channels[3].pin = SEED_CHANNEL_4_PIN;
	dDropper.channels[3].seedType = CASUAL;
	dDropper.channels[3].status = CHANNEL_CLOSED;

	dDropper.channels[4].name = CHANNEL_5;
	dDropper.channels[4].port = SEED_CHANNEL_5_PORT;
	dDropper.channels[4].pin = SEED_CHANNEL_5_PIN;
	dDropper.channels[4].seedType = CASUAL;
	dDropper.channels[4].status = CHANNEL_CLOSED;

	dDropper.channels[5].name = CHANNEL_6;
	dDropper.channels[5].port = SEED_CHANNEL_6_PORT;
	dDropper.channels[5].pin = SEED_CHANNEL_6_PIN;
	dDropper.channels[5].seedType = CASUAL;
	dDropper.channels[5].status = CHANNEL_CLOSED;

	dDropper.vibrateMotor.port = VIBRATE_MOTOR_FOR_CASUAL_SEEDS_PORT;
	dDropper.vibrateMotor.pin = VIBRATE_MOTOR_FOR_CASUAL_SEEDS_PIN;
	dDropper.vibrateMotor.status = MOTOR_OFF;

	dDropper.drumMotor.enPort = PELLETED_SEEDS_STEPPER_EN_PORT;
	dDropper.drumMotor.enPin = PELLETED_SEEDS_STEPPER_EN_PIN;
	dDropper.drumMotor.dirPort = PELLETED_SEEDS_STEPPER_DIR_PORT;
	dDropper.drumMotor.dirPin = PELLETED_SEEDS_STEPPER_DIR_PIN;
	dDropper.drumMotor.timerHandler = &htim3;
	dDropper.drumMotor.timerChannel = TIM_CHANNEL_1;
	dDropper.drumMotor.invertAxis = false;

	dDropper.dropperMotor.enPort = DROPPER_STEPPER_EN_PORT;
	dDropper.dropperMotor.enPin = DROPPER_STEPPER_EN_PIN;
	dDropper.dropperMotor.dirPort = DROPPER_STEPPER_DIR_PORT;
	dDropper.dropperMotor.dirPin = DROPPER_STEPPER_DIR_PIN;
	dDropper.dropperMotor.timerHandler = &htim3;
	dDropper.dropperMotor.timerChannel = TIM_CHANNEL_1;
	dDropper.dropperMotor.invertAxis = false;

	for(uint8_t i = 0; i<NUMBER_OF_CHANNELS; i++){
		HAL_GPIO_WritePin(dDropper.channels[i].port, dDropper.channels[i].pin, GPIO_PIN_SET);
	}

	HAL_GPIO_WritePin(dDropper.vibrateMotor.port, dDropper.vibrateMotor.pin, GPIO_PIN_SET);

	HAL_GPIO_WritePin(dDropper.drumMotor.enPort, dDropper.drumMotor.enPin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(dDropper.drumMotor.dirPort, dDropper.drumMotor.dirPin, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(dDropper.dropperMotor.enPort, dDropper.dropperMotor.enPin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(dDropper.dropperMotor.dirPort, dDropper.dropperMotor.dirPin, GPIO_PIN_RESET);

	//turn off other relays
	HAL_GPIO_WritePin(RELAY_8_GPIO_Port, RELAY_8_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(RELAY_9_GPIO_Port, RELAY_9_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(RELAY_10_GPIO_Port, RELAY_10_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(RELAY_11_GPIO_Port, RELAY_11_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(RELAY_12_GPIO_Port, RELAY_12_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(RELAY_13_GPIO_Port, RELAY_13_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(RELAY_14_GPIO_Port, RELAY_14_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(RELAY_15_GPIO_Port, RELAY_15_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(RELAY_16_GPIO_Port, RELAY_16_Pin, GPIO_PIN_SET);

	UART_Init(&huart1);

	dDropper.state = INITIALIZED;
}


void _dropper_OpenChannel(_dropperChannelName dC){
	HAL_GPIO_WritePin(dDropper.channels[dC].port, dDropper.channels[dC].pin, GPIO_PIN_RESET);
	dDropper.channels[dC].status = CHANNEL_OPENED;
}

void _dropper_CloseChannel(_dropperChannelName dC){
	HAL_GPIO_WritePin(dDropper.channels[dC].port, dDropper.channels[dC].pin, GPIO_PIN_SET);
	dDropper.channels[dC].status = CHANNEL_CLOSED;
}

void _dropper_StartVibrate(){
	HAL_GPIO_WritePin(dDropper.vibrateMotor.port, dDropper.vibrateMotor.pin, GPIO_PIN_RESET);
	dDropper.vibrateMotor.status = MOTOR_ON;
}
void _dropper_StopVibrate(){
	HAL_GPIO_WritePin(dDropper.vibrateMotor.port, dDropper.vibrateMotor.pin, GPIO_PIN_SET);
	dDropper.vibrateMotor.status = MOTOR_OFF;
}

void _dropper_SelfTest(){
	_dropper_OpenChannel(CHANNEL_1);
	HAL_Delay(500);
	_dropper_CloseChannel(CHANNEL_1);
	HAL_Delay(500);
	_dropper_OpenChannel(CHANNEL_2);
	HAL_Delay(500);
	_dropper_CloseChannel(CHANNEL_2);
	HAL_Delay(500);
	_dropper_OpenChannel(CHANNEL_3);
	HAL_Delay(500);
	_dropper_CloseChannel(CHANNEL_3);
	HAL_Delay(500);
	_dropper_OpenChannel(CHANNEL_4);
	HAL_Delay(500);
	_dropper_CloseChannel(CHANNEL_4);
	HAL_Delay(500);
	_dropper_OpenChannel(CHANNEL_5);
	HAL_Delay(500);
	_dropper_CloseChannel(CHANNEL_5);
	HAL_Delay(500);
	_dropper_OpenChannel(CHANNEL_6);
	HAL_Delay(500);
	_dropper_CloseChannel(CHANNEL_6);
	HAL_Delay(500);

	_dropper_StartVibrate();
	HAL_Delay(1000);
	_dropper_StopVibrate();
	HAL_Delay(500);

	_dropper_RotateDrum_deg(90);
	_dropper_RotateDrum_deg(-90);

	HAL_Delay(500);
}

void _dropper_setStepperMoveDirection(_dropperStepperMotor * stepper,_stepperMoveDirection md){
	switch(md){
	case FORWARD:
		if(!stepper->invertAxis){
			HAL_GPIO_WritePin(stepper->dirPort, stepper->dirPin, GPIO_PIN_SET);
		}
		else{
			HAL_GPIO_WritePin(stepper->dirPort, stepper->dirPin, GPIO_PIN_RESET);
		}
		break;
	case BACKWARD:
		if(!stepper->invertAxis){
			HAL_GPIO_WritePin(stepper->dirPort, stepper->dirPin, GPIO_PIN_RESET);
		}
		else{
			HAL_GPIO_WritePin(stepper->dirPort, stepper->dirPin, GPIO_PIN_SET);
		}
		break;
	}
}

_seedSowingStatus _dropper_RotateDrum_deg(float angle_deg){

	if(angle_deg < 0){
		_dropper_setStepperMoveDirection(&(dDropper.drumMotor), BACKWARD);
		angle_deg = -angle_deg;
	}
	else{
		_dropper_setStepperMoveDirection(&(dDropper.drumMotor), FORWARD);
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

void _dropper_MoveDropper_mm(float distance_mm){

	if(distance_mm < 0){
//		_dropper_DropperSetMoveDirection(BACKWARD);
		_dropper_setStepperMoveDirection(&dDropper.dropperMotor, BACKWARD);
		distance_mm = -distance_mm;
	}
	else{
//		_dropper_DropperSetMoveDirection(FORWARD);
		_dropper_setStepperMoveDirection(&dDropper.dropperMotor, FORWARD);
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

bool _dropper_SowSeeds(_dropperChannelName channel ){

	//pelleted seeds
	if(channel == CHANNEL_1 || channel == CHANNEL_2 || channel == CHANNEL_3){

		_seedSowingStatus isSown = SEED_ERR;
		_stepperMoveDirection nextDirection = FORWARD;

		_dropper_OpenChannel(channel);

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

		_dropper_StartVibrate();
		HAL_Delay(400);
		_dropper_StopVibrate();

		_dropper_CloseChannel(channel);

		return isSown;
	}

	//casual seeds
	else if(channel == CHANNEL_4 || channel == CHANNEL_5 || channel == CHANNEL_6){
		_dropper_OpenChannel(channel);
		HAL_Delay(100); //wait until the channel is open
		_dropper_StartVibrate(CASUAL);
		HAL_Delay(SOWING_TIME_FOR_CASUAL_SEEDS_MS);
		_dropper_StopVibrate(CASUAL);
		_dropper_CloseChannel(channel);

		return SEED_SOWN;
	}
}

void _dropper_ShakeSeeds(uint32_t delayTime){
	_dropper_StartVibrate();

	HAL_Delay(delayTime);

	_dropper_StopVibrate();
}

void _dropper_Home(){

}

///////////////////////////////////////////////////////////////////////////////////////////

void _dropper_execCmd(){
	command cmd;
	int8_t paramsNo = decodeMsg(&cmd);
	if(paramsNo == -1){
		UART_sendMsg(REJECTION_MSG);
		return; //invalid command
	}

	if(strcmp(cmd.cmdName, CMD_HOME) == 0){
		UART_sendMsg(CONFIRMATION_MSG);
		_dropper_execCmd_HomeDropper();
	}
	else if(strcmp(cmd.cmdName, CMD_HELP) == 0){
		UART_sendMsg(CONFIRMATION_MSG);
		_dropper_execCmd_Help();
	}
	else if(strcmp(cmd.cmdName, CMD_SEND_STATUS) == 0){
		UART_sendMsg(CONFIRMATION_MSG);
		_dropper_execCmd_GetStatus();
	}
	else if(strcmp(cmd.cmdName, CMD_SELFTEST) == 0){
			UART_sendMsg(CONFIRMATION_MSG);
			_dropper_execCmd_Selftest();
		}
	else if(strcmp(cmd.cmdName, CMD_SOW) == 0){
		if(paramsNo != 2){
			UART_sendMsg(INVALID_ARGUMET_MSG);
		}
		else{
			UART_sendMsg(CONFIRMATION_MSG);
			_dropper_execCmd_Sow((uint8_t)cmd.params[0], (uint8_t)cmd.params[1]);
		}
	}
	else{
		UART_sendMsg(REJECTION_MSG);
	}
}

void _dropper_execCmd_Help(){
	UART_sendMsg(HELP_TEXT);
}

void _dropper_execCmd_GetStatus(){

}

void _dropper_execCmd_Sow(uint8_t channelNo, uint8_t noOfSeeds){
	if(channelNo > NUMBER_OF_CHANNELS || channelNo < 1){
		UART_sendMsg(INVALID_ARGUMET_MSG);
		return;
	}

	if(noOfSeeds > MAX_SOWS_AT_ONCE) noOfSeeds = MAX_SOWS_AT_ONCE;

	for(uint8_t i = 0; i<noOfSeeds; i++){
		if(_dropper_SowSeeds((_dropperChannelName)channelNo - 1) == SEED_SOWN){
			UART_sendMsg(CMD_EXEC_SUCCESFULLY_MSG);
		}
		else{
			UART_sendMsg(CMD_EXEC_FAILED_MSG);
		}
	}

}

void _dropper_execCmd_SowExt(uint8_t channelNo, uint8_t noOfSeeds, uint8_t potNo){

}

void _dropper_execCmd_HomeDropper(){

}

void _dropper_execCmd_MoveDropper(uint32_t distance_mm){

}

void _dropper_execCmd_Selftest(){
	_dropper_SelfTest();
	UART_sendMsg(CMD_EXEC_SUCCESFULLY_MSG);
}
