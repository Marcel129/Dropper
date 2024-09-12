#include "UART_communication.h"

UART_structure _dropper_UART;

void UART_Init(UART_HandleTypeDef *huart){
	clearRxBuffer();
	clearTxBuffer();

	_dropper_UART.UART_Handler = huart;
	HAL_UART_Receive_IT(_dropper_UART.UART_Handler, &(_dropper_UART.rxTmpChar), 1);
}

HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(huart->Instance == _dropper_UART.UART_Handler->Instance){
		if(_dropper_UART.rxTmpChar == '\n' || _dropper_UART.rxTmpChar == '\r'){
			_dropper_UART.msgReadyToRead = true;
		}
		else{
			_dropper_UART.rxBuffer[_dropper_UART.rxBuffCursor] = _dropper_UART.rxTmpChar;
			_dropper_UART.rxBuffCursor = ((++_dropper_UART.rxBuffCursor)%RX_BUFFER_SIZE);
		}
		HAL_UART_Receive_IT(_dropper_UART.UART_Handler, &(_dropper_UART.rxTmpChar), 1);
	}
}

void clearRxBuffer(){
	_dropper_UART.rxTmpChar = 0;
	_dropper_UART.rxBuffCursor = 0;
	_dropper_UART.msgReadyToRead = false;
	for(uint8_t i = 0; i<RX_BUFFER_SIZE; i++){
		_dropper_UART.rxBuffer[i] = 0;
	}
}

void clearTxBuffer(){
	for(uint8_t i = 0; i<TX_BUFFER_SIZE; i++){
		_dropper_UART.txBuffer[i] = 0;
	}
}

int8_t decodeMsg(command *cmd){

	uint8_t *p = NULL, *p_prev = NULL, tmpBuff[20] = {0};
	int8_t paramIdx = 0;

	for(uint8_t i = 0; i<CMD_NAME_LENGHT_T; i++)cmd->cmdName[i] = 0;
	for(uint8_t i = 0; i<CMD_PARAMS_NUMBER_T; i++)cmd->params[i] = 0;

	p = strchr(_dropper_UART.rxBuffer, ' ');
	strncpy(cmd->cmdName, _dropper_UART.rxBuffer, 3);
	if(p == NULL) {
		clearRxBuffer();
		return 0;//no arguments
	}
	else if(p - _dropper_UART.rxBuffer != 3){
		clearRxBuffer();
		return -1; //cmd name is not valid, abort
	}

	while(p != NULL){
		p_prev = p + 1;
		p = strchr( p + 1, ' ' );
		if(p == NULL){
			strcpy(tmpBuff, p_prev);
		}
		else{
			int8_t len = p - p_prev;
			strncpy(tmpBuff, p_prev, len);
		}
		cmd->params[paramIdx++] = atof(tmpBuff);

		if(paramIdx >= 5) {
			clearRxBuffer();
			return paramIdx;//too many arguments
		}

		for(uint8_t i = 0; i<20; i++) tmpBuff[i] = 0;
	}

	clearRxBuffer();
	return paramIdx;
}

void UART_sendMsg(uint8_t * msg){
	clearTxBuffer();
	uint16_t msgLen = strlen(msg);
	//prevention from too large messages
	if(msgLen > TX_BUFFER_SIZE) msgLen = TX_BUFFER_SIZE;
	strncpy(_dropper_UART.txBuffer, msg, msgLen);
	HAL_UART_Transmit(_dropper_UART.UART_Handler, _dropper_UART.txBuffer, msgLen, 100);
}







