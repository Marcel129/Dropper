#include "box.h"

box_t box;

void _dropper_HomingSensorIRQ(){
	box.dropper.state = MACHINE_HOME;
}

void box_Init(){

	//PIN ASSIGMENT
	box.lowerPusher.minEndstop.port = EMPTY_MULTIPLAT_PUSHER_MIN_ENDSTOP_PORT;
	box.lowerPusher.minEndstop.pin = EMPTY_MULTIPLAT_PUSHER_MIN_ENDSTOP_PIN;
	box.lowerPusher.maxEndstop.port = EMPTY_MULTIPLAT_PUSHER_MAX_ENDSTOP_PORT;
	box.lowerPusher.maxEndstop.pin = EMPTY_MULTIPLAT_PUSHER_MAX_ENDSTOP_PIN;
	box.lowerPusher.homingTimeout = HOMING_LOWER_PUSHER_MAX_TIMEOUT_MS;

	box.lowerPusher.motor.forwardPort = LOWER_PUSHER_MOVE_FORWARD_PORT;
	box.lowerPusher.motor.forwardPin = LOWER_PUSHER_MOVE_FORWARD_Pin;
	box.lowerPusher.motor.backwardPort = LOWER_PUSHER_MOVE_BACKWARD_PORT;
	box.lowerPusher.motor.backwardPin = LOWER_PUSHER_MOVE_BACKWARD_Pin;
	HW_logic_setLogic(&(box.lowerPusher.motor.logic), LOW_IS_ACTVE);


	box.upperPusher.minEndstop.port = FULL_MULTIPLAT_PUSHER_MIN_ENDSTOP_PORT;
	box.upperPusher.minEndstop.pin = FULL_MULTIPLAT_PUSHER_MIN_ENDSTOP_PIN;
	box.upperPusher.maxEndstop.port = FULL_MULTIPLAT_PUSHER_MAX_ENDSTOP_PORT;
	box.upperPusher.maxEndstop.pin = FULL_MULTIPLAT_PUSHER_MAX_ENDSTOP_PIN;
	box.upperPusher.homingTimeout = HOMING_UPPER_PUSHER_MAX_TIMEOUT_MS;

	box.upperPusher.motor.forwardPort = UPPER_PUSHER_MOVE_FORWARD_PORT;
	box.upperPusher.motor.forwardPin = UPPER_PUSHER_MOVE_FORWARD_Pin;
	box.upperPusher.motor.backwardPort = UPPER_PUSHER_MOVE_BACKWARD_PORT;
	box.upperPusher.motor.backwardPin = UPPER_PUSHER_MOVE_BACKWARD_Pin;
	HW_logic_setLogic(&(box.upperPusher.motor.logic), LOW_IS_ACTVE);


	box.dropper.channels[0].name = CHANNEL_1;
	box.dropper.channels[0].port = SEED_CHANNEL_1_PORT;
	box.dropper.channels[0].pin = SEED_CHANNEL_1_PIN;
	box.dropper.channels[0].seedType = PELLETED;
	box.dropper.channels[0].status = CHANNEL_CLOSED;

	box.dropper.channels[1].name = CHANNEL_2;
	box.dropper.channels[1].port = SEED_CHANNEL_2_PORT;
	box.dropper.channels[1].pin = SEED_CHANNEL_2_PIN;
	box.dropper.channels[1].seedType = PELLETED;
	box.dropper.channels[1].status = CHANNEL_CLOSED;

	box.dropper.channels[2].name = CHANNEL_3;
	box.dropper.channels[2].port = SEED_CHANNEL_3_PORT;
	box.dropper.channels[2].pin = SEED_CHANNEL_3_PIN;
	box.dropper.channels[2].seedType = PELLETED;
	box.dropper.channels[2].status = CHANNEL_CLOSED;

	box.dropper.channels[3].name = CHANNEL_4;
	box.dropper.channels[3].port = SEED_CHANNEL_4_PORT;
	box.dropper.channels[3].pin = SEED_CHANNEL_4_PIN;
	box.dropper.channels[3].seedType = CASUAL;
	box.dropper.channels[3].status = CHANNEL_CLOSED;

	box.dropper.channels[4].name = CHANNEL_5;
	box.dropper.channels[4].port = SEED_CHANNEL_5_PORT;
	box.dropper.channels[4].pin = SEED_CHANNEL_5_PIN;
	box.dropper.channels[4].seedType = CASUAL;
	box.dropper.channels[4].status = CHANNEL_CLOSED;

	box.dropper.channels[5].name = CHANNEL_6;
	box.dropper.channels[5].port = SEED_CHANNEL_6_PORT;
	box.dropper.channels[5].pin = SEED_CHANNEL_6_PIN;
	box.dropper.channels[5].seedType = CASUAL;
	box.dropper.channels[5].status = CHANNEL_CLOSED;


	box.dropper.vibrateMotor.forwardPort = VIBRATE_MOTOR_FOR_CASUAL_SEEDS_PORT;
	box.dropper.vibrateMotor.forwardPin = VIBRATE_MOTOR_FOR_CASUAL_SEEDS_PIN;
	HW_logic_setLogic(&(box.dropper.vibrateMotor.logic), LOW_IS_ACTVE);


	box.box_Communication_Handler = &box_main_UART;
	Communication_Init(&(box.box_Communication_Handler), &huart1);

	//HW INITIALIZING
	for(uint8_t i = 0; i<NUMBER_OF_CHANNELS; i++){
		dropper_CloseChannel(&(box.dropper.channels[i]));
	}

	dcMotor_stop(&(box.dropper.vibrateMotor));
	dcMotor_stop(&(box.upperPusher.motor));
	dcMotor_stop(&(box.lowerPusher.motor));

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

void _box_execCmd_SowRow(uint8_t channelNo){

	static uint8_t rowNo = 0;
	double distanceToGo = 0;

	if(rowNo == 0){
		_dropper_execCmd_HomeDropper();
		rowNo = 1;
	}

	if(rowNo == 1){
		_dropper_MoveDropper_mm(DISTANCE_TO_THE_FIRST_POT_MM + _dropper_getChannelOffset(channelNo));
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
		if(_dropper_SowSeeds(channelNo) != SEED_SOWN){
			if(++trials > NUMBER_OF_SOWING_TRIALS){
				trials = 0;
				Communication_SendMsg(&(box.box_Communication_Handler), "Sowing fail\r\n");
			}
			else{
				--i;
				continue;
			}
		}

		if(i == 3) break;// skip last move
		_dropper_MoveDropper_mm(distanceToGo);
	}

	if(++rowNo > 5)	rowNo = 0;

	Communication_SendMsg(&(box.box_Communication_Handler), CMD_EXEC_SUCCESFULLY_MSG);
}

void _box_execCmd_PushEmptyMultiplat(){

	uint32_t prevTime, currentTime;
	prevTime = currentTime = HAL_GetTick();

	HAL_GPIO_WritePin(LOWER_PUSHER_MOVE_BACKWARD_PORT, LOWER_PUSHER_MOVE_BACKWARD_Pin, GPIO_PIN_RESET);

	while(HAL_GPIO_ReadPin(EMPTY_MULTIPLAT_PUSHER_MIN_ENDSTOP_PORT, EMPTY_MULTIPLAT_PUSHER_MIN_ENDSTOP_PIN) == GPIO_PIN_SET){
		currentTime = HAL_GetTick();
		if(currentTime - prevTime > PUSHING_EMPTY_MULTIPLAT_MAX_TIMEOUT_MS){
			Communication_SendMsg(&(box.box_Communication_Handler), MOVING_ERROR_TIMEOUT_MSG);
			return;
		}
	}

	HAL_GPIO_WritePin(LOWER_PUSHER_MOVE_BACKWARD_PORT, LOWER_PUSHER_MOVE_BACKWARD_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LOWER_PUSHER_MOVE_FORWARD_PORT, LOWER_PUSHER_MOVE_FORWARD_Pin, GPIO_PIN_RESET);

	prevTime = currentTime = HAL_GetTick();

	while(HAL_GPIO_ReadPin(EMPTY_MULTIPLAT_PUSHER_MAX_ENDSTOP_PORT, EMPTY_MULTIPLAT_PUSHER_MAX_ENDSTOP_PIN) == GPIO_PIN_SET){
		currentTime = HAL_GetTick();
		if(currentTime - prevTime > PUSHING_EMPTY_MULTIPLAT_MAX_TIMEOUT_MS){
			Communication_SendMsg(&(box.box_Communication_Handler), MOVING_ERROR_TIMEOUT_MSG);
			return;
		}
	}

	HAL_GPIO_WritePin(LOWER_PUSHER_MOVE_FORWARD_PORT, LOWER_PUSHER_MOVE_FORWARD_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LOWER_PUSHER_MOVE_BACKWARD_PORT, LOWER_PUSHER_MOVE_BACKWARD_Pin, GPIO_PIN_RESET);

	prevTime = currentTime = HAL_GetTick();

	while(HAL_GPIO_ReadPin(EMPTY_MULTIPLAT_PUSHER_MIN_ENDSTOP_PORT, EMPTY_MULTIPLAT_PUSHER_MIN_ENDSTOP_PIN) == GPIO_PIN_SET){
		currentTime = HAL_GetTick();
		if(currentTime - prevTime > PUSHING_EMPTY_MULTIPLAT_MAX_TIMEOUT_MS){
			Communication_SendMsg(&(box.box_Communication_Handler), MOVING_ERROR_TIMEOUT_MSG);
			return;
		}
	}

	HAL_GPIO_WritePin(LOWER_PUSHER_MOVE_BACKWARD_PORT, LOWER_PUSHER_MOVE_BACKWARD_Pin, GPIO_PIN_SET);

	Communication_SendMsg(&(box.box_Communication_Handler), CMD_EXEC_SUCCESFULLY_MSG);
}

void _box_execCmd_PushFullMultiplat(){

}
