#ifndef UART_COMMUNICATION_H
#define UART_COMMUNICATION_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "usart.h"

#define RX_BUFFER_SIZE 200
#define TX_BUFFER_SIZE 200

typedef struct{
	uint8_t txBuffer [RX_BUFFER_SIZE];
	uint8_t rxBuffer [TX_BUFFER_SIZE];
	uint8_t rxTmpChar;
	uint8_t rxBuffCursor;
	bool msgReadyToRead;

	UART_HandleTypeDef* UART_Handler;
} UART_structure_t;

#define CMD_NAME_LENGHT_T 4
#define CMD_PARAMS_NUMBER_T 5

typedef struct{
	uint8_t cmdName[CMD_NAME_LENGHT_T];
	double params[CMD_PARAMS_NUMBER_T];
} command;

extern UART_structure_t box_main_UART;

void Communication_Init(UART_structure_t *, UART_HandleTypeDef *huart);
void Communication_ClearRxBuffer(UART_structure_t *);
void Communication_ClearTxBuffer(UART_structure_t *);
void Communication_SendMsg(UART_structure_t *, uint8_t * msg);

//return number of correnctly read params
int8_t Communication_DecodeMsg(UART_structure_t *, command *cmd);

/////////////////////////////////////////////////////////////
#define CMD_HELP 					"H10"
#define CMD_HOME 					"H11"
#define CMD_SEND_STATUS 			"S10"
#define CMD_SOW						"S11"
#define CMD_SELFTEST				"S12"
#define CMD_MOVE_DROPPER			"M10"
#define CMD_MOVE_PUSHER 			"M11"

#define CMD_SOW_ROW					"S13"
#define CMD_PUSH_FULL_MULTIPLAT		"P10"
#define CMD_PUSH_EMPTY_MULTIPLAT	"P11"

#define CONFIRMATION_MSG			"OK\r\n"
#define REJECTION_MSG				"NOK\r\n"
#define INVALID_ARGUMET_MSG			"INVALID PARAMS\r\n"
#define CMD_EXEC_SUCCESFULLY_MSG	"CMD DONE, SUCCESS\r\n"
#define CMD_EXEC_FAILED_MSG			"CMD DONE, FAILURE\r\n"
#define MOVING_ERROR_TIMEOUT_MSG	"ERROR DURING MOVE, TIME OUT\r\n"

//#define HELP_TEXT "AVAILABLE FUNCTIONS\r\n\
//		H10 - help, list avaiable commands\r\n\
//		G11 - home the dropper\r\n\
//		G12 - send dropper status\r\n"

#define HELP_TEXT "AVAILABLE FUNCTIONS\r\n\
		H10 - help, list of avaiable commands\r\n\
		H11 - home the dropper, not implemented yet\r\n\
		S10 - send dropper status, not implemented yet\r\n\
		S11 [channel name] [number of seeds] - sow seeds from given channel,\
			example: S11 1 1 sow 1 seed from the channel 1\r\n\
		S12 - dropper selftest, not implemented yet\r\n"

#define SELFTEST_INTRO "Rozpoczeto procedure autotestu. \
		Elementu ukladu beda testowane sekwencyjnie.\r\n \
		Po kazdym tescie wysli 't' lub poczekaj 5s aby przejsc dalej.\r\n"

#endif //UART_COMMUNICATION_H
