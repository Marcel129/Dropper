#ifndef INC_MACHINESTATES_H_
#define INC_MACHINESTATES_H_

typedef enum {
	MACHINE_WORKING,
	MACHINE_ERROR,
	MACHINE_TIMEOUT,
	MACHINE_HOME
} machineState_t;

typedef enum {
	MOTOR_WORKING,
	MOTOR_OFF,
	MOTOR_ERROR
} motorState_t;

#endif /* INC_MACHINESTATES_H_ */
