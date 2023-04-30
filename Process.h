#pragma once
#include <iostream>
#include "ProcessState.h"
#include <queue>


class ProcessState;


class Process
{
private:
	// gives access to private attributes to the different Process State classes
	friend class ProcessState;
	friend class ProcessReadyState;
	friend class ProcessRunningState;
	friend class ProcessWaitingIOState;
	friend class ProcessTerminatedState;

	// counts number of process that has been created in the program
	static int processCounter;

	// integer that identifies the process, uses the process Counter to assign it
	const int processID;

	// contains the time spent waiting to be run, running and waiting for IO
	int timeWaiting = 0;
	int timeRunning = 0;
	int timeIO = 0;

	// contains the burst and IO wait times in sequential order
	std::queue<int> burstTimes;
	std::queue<int> IOTimes;

	// contains information about the prediction (Used in Exponential Averaging)
	double timePrediction = 4;	//4 Quantums is the default prediction
	double alpha = 0.60;		//60% is the weight for the prediction calculation


	// contains information about the current state of the process and how it should behave
	ProcessState *currentState;

	// gets time of the next Bust in quantums
	int getBurst() {
		return burstTimes.front();
	}

	// gets time of the next I/O in quantums
	int getIO()
	{
		return IOTimes.front();
	}

	// pop the completed bust and sends the process to the next state
	void completeBurst();

	// pop the completed I/O and sends the process to the next state
	void receiveIO();

	// changes the state of the process
	void changeState(ProcessState* state);

public:
	// Constructor
	Process(std::queue<int> burstTimes, std::queue<int> IOTimes);

	// Destructor
	~Process();

	// gets time spent waiting in quantums
	int getTimeWaiting() {
		return timeWaiting;
	}

	// gets time spent running in quantums
	int getTimeRunning() {
		return timeRunning;
	}

	// gets time spent waiting for I/O in quantums
	int getTimeIO() {
		return timeIO;
	}

	// indicates if the process has been completed
	bool isCompleted();

	// gets the current state of the process as a string
	std::string getState();

	// starts the execution of a process
	void start();

	// update the state of the process by calling its state's updater
	void update();

	// converts a process to a string
	void printProcess();

	// converts a process to a string
	int getID();

	bool operator<(const Process& other) const{
		return timePrediction < other.timePrediction;
	}
};



