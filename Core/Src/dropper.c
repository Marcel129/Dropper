/*
 * dropper.c
 *
 *  Created on: Jul 21, 2024
 *      Author: Marcel
 */

#include "dropper.h"

uint32_t stepCounter = 0;

void _dropper_StepIRQ(){
	++stepCounter;
}

void _dropper_Init(){
	HAL_GPIO_WritePin(SEED_CHANNEL_1_PORT, SEED_CHANNEL_1_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(SEED_CHANNEL_2_PORT, SEED_CHANNEL_2_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(SEED_CHANNEL_3_PORT, SEED_CHANNEL_3_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(SEED_CHANNEL_4_PORT, SEED_CHANNEL_4_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(SEED_CHANNEL_5_PORT, SEED_CHANNEL_5_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(SEED_CHANNEL_6_PORT, SEED_CHANNEL_6_PIN, GPIO_PIN_SET);

	HAL_GPIO_WritePin(VIBRATE_MOTOR_FOR_PELLETED_SEEDS_PORT, VIBRATE_MOTOR_FOR_PELLETED_SEEDS_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(VIBRATE_MOTOR_FOR_CASUAL_SEEDS_PORT, VIBRATE_MOTOR_FOR_CASUAL_SEEDS_PIN, GPIO_PIN_SET);

	HAL_GPIO_WritePin(PELLETED_SEEDS_STEPPER_EN_PORT, PELLETED_SEEDS_STEPPER_EN_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PELLETED_SEEDS_STEPPER_DIR_PORT, PELLETED_SEEDS_STEPPER_DIR_PIN, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(DROPPER_STEPPER_EN_PORT, DROPPER_STEPPER_EN_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(DROPPER_STEPPER_DIR_PORT, DROPPER_STEPPER_DIR_PIN, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(RELAY_9_GPIO_Port, RELAY_9_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(RELAY_10_GPIO_Port, RELAY_10_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(RELAY_11_GPIO_Port, RELAY_11_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(RELAY_12_GPIO_Port, RELAY_12_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(RELAY_13_GPIO_Port, RELAY_13_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(RELAY_14_GPIO_Port, RELAY_14_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(RELAY_15_GPIO_Port, RELAY_15_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(RELAY_16_GPIO_Port, RELAY_16_Pin, GPIO_PIN_SET);

}

void _dropper_OpenChannel(_dropperChannelName dC){
	switch(dC){
	case CHANNEL_1:
		HAL_GPIO_WritePin(SEED_CHANNEL_1_PORT, SEED_CHANNEL_1_PIN, GPIO_PIN_RESET);
		break;
	case CHANNEL_2:
		HAL_GPIO_WritePin(SEED_CHANNEL_2_PORT, SEED_CHANNEL_2_PIN, GPIO_PIN_RESET);
		break;
	case CHANNEL_3:
		HAL_GPIO_WritePin(SEED_CHANNEL_3_PORT, SEED_CHANNEL_3_PIN, GPIO_PIN_RESET);
		break;
	case CHANNEL_4:
		HAL_GPIO_WritePin(SEED_CHANNEL_4_PORT, SEED_CHANNEL_4_PIN, GPIO_PIN_RESET);
		break;
	case CHANNEL_5:
		HAL_GPIO_WritePin(SEED_CHANNEL_5_PORT, SEED_CHANNEL_5_PIN, GPIO_PIN_RESET);
		break;
	case CHANNEL_6:
		HAL_GPIO_WritePin(SEED_CHANNEL_6_PORT, SEED_CHANNEL_6_PIN, GPIO_PIN_RESET);
		break;
	}
}
void _dropper_CloseChannel(_dropperChannelName dC){
	switch(dC){
	case CHANNEL_1:
		HAL_GPIO_WritePin(SEED_CHANNEL_1_PORT, SEED_CHANNEL_1_PIN, GPIO_PIN_SET);
		break;
	case CHANNEL_2:
		HAL_GPIO_WritePin(SEED_CHANNEL_2_PORT, SEED_CHANNEL_2_PIN, GPIO_PIN_SET);
		break;
	case CHANNEL_3:
		HAL_GPIO_WritePin(SEED_CHANNEL_3_PORT, SEED_CHANNEL_3_PIN, GPIO_PIN_SET);
		break;
	case CHANNEL_4:
		HAL_GPIO_WritePin(SEED_CHANNEL_4_PORT, SEED_CHANNEL_4_PIN, GPIO_PIN_SET);
		break;
	case CHANNEL_5:
		HAL_GPIO_WritePin(SEED_CHANNEL_5_PORT, SEED_CHANNEL_5_PIN, GPIO_PIN_SET);
		break;
	case CHANNEL_6:
		HAL_GPIO_WritePin(SEED_CHANNEL_6_PORT, SEED_CHANNEL_6_PIN, GPIO_PIN_SET);
		break;
	}
}

void _dropper_StartVibrate(_seedsType sT){
	switch(sT){
	case CASUAL:
		HAL_GPIO_WritePin(VIBRATE_MOTOR_FOR_PELLETED_SEEDS_PORT, VIBRATE_MOTOR_FOR_PELLETED_SEEDS_PIN, GPIO_PIN_RESET);
		break;
	case PELLETED:
		HAL_GPIO_WritePin(VIBRATE_MOTOR_FOR_CASUAL_SEEDS_PORT, VIBRATE_MOTOR_FOR_CASUAL_SEEDS_PIN, GPIO_PIN_RESET);
		break;
	}
}
void _dropper_StopVibrate(_seedsType sT){
	switch(sT){
	case CASUAL:
		HAL_GPIO_WritePin(VIBRATE_MOTOR_FOR_PELLETED_SEEDS_PORT, VIBRATE_MOTOR_FOR_PELLETED_SEEDS_PIN, GPIO_PIN_SET);
		break;
	case PELLETED:
		HAL_GPIO_WritePin(VIBRATE_MOTOR_FOR_CASUAL_SEEDS_PORT, VIBRATE_MOTOR_FOR_CASUAL_SEEDS_PIN, GPIO_PIN_SET);
		break;
	}
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

	_dropper_StartVibrate(CASUAL);
	HAL_Delay(1000);
	_dropper_StopVibrate(CASUAL);
	HAL_Delay(500);
	_dropper_StartVibrate(PELLETED);
	HAL_Delay(1000);
	_dropper_StopVibrate(PELLETED);

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
		HAL_GPIO_WritePin(PELLETED_SEEDS_STEPPER_DIR_PORT, DROPPER_STEPPER_DIR_PIN, GPIO_PIN_RESET);
		break;
	case BACKWARD:
		HAL_GPIO_WritePin(PELLETED_SEEDS_STEPPER_DIR_PORT, DROPPER_STEPPER_DIR_PIN, GPIO_PIN_SET);
		break;
	}
}

void _dropper_RotateDrum_deg(float angle_deg){

	if(angle_deg < 0){
		_dropper_DrumSetMoveDirection(BACKWARD);
	}
	else{
		_dropper_DrumSetMoveDirection(FORWARD);
	}

	uint32_t stepsToDo = (uint32_t)((angle_deg * (float)DRUM_STEPPER_MICROSTEPPING)/DEFAULT_ANGLE_PER_STEP);

	HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_1);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 49);
	stepCounter = 0;
	while(stepCounter < stepsToDo);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
	HAL_TIM_PWM_Stop_IT(&htim3, TIM_CHANNEL_1);
}

void _dropper_MoveDropper_mm(float distance_mm){

	if(distance_mm < 0){
		_dropper_DropperSetMoveDirection(BACKWARD);
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

void _dropper_SowSeeds(_dropperChannelName channel){

	//casula seeds
	if(channel == CHANNEL_1 || channel == CHANNEL_2 || channel == CHANNEL_3){
		_dropper_OpenChannel(channel);
		HAL_Delay(10);
		_dropper_StartVibrate(CASUAL);
		HAL_Delay(SOWING_TIME_FOR_CASUAL_SEEDS_MS);
		_dropper_StopVibrate(CASUAL);
		_dropper_CloseChannel(channel);
	}

	//pelleted seeds
	else if(channel == CHANNEL_1 || channel == CHANNEL_2 || channel == CHANNEL_3){

	}
}

void _dropper_ShakeSeeds(uint32_t delayTime){
	_dropper_StartVibrate(CASUAL);
	_dropper_StartVibrate(PELLETED);

	HAL_Delay(delayTime);

	_dropper_StopVibrate(CASUAL);
	_dropper_StopVibrate(PELLETED);
}

void _dropper_Home(){

}

