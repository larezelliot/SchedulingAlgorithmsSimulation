#pragma once
#include "Process.h"

class Process;

//Base State Class
class ProcessState
{
protected:
	//Process for context of the state
	Process* process;

	//Name of the state
	const std::string name;
	
	//Time running current state;
	int currentTime = 0;

public:
	ProcessState(Process* process, std::string name);

	virtual void update() = 0;

	std::string getName() const {
		return name;
	}
};


//State for Processes waiting to be executed
class ProcessReadyState : public ProcessState
{
public:
	ProcessReadyState(Process* process) : ProcessState(process, "Ready") {

	}

	void update();
};


//State for Processes being run
class ProcessRunningState : public ProcessState
{
public:
	ProcessRunningState(Process* process) :
		ProcessState(process, "Running") {

	}

	void update();
};


//State for Processes waiting for I/O
class ProcessWaitingIOState : public ProcessState
{
public:
	ProcessWaitingIOState(Process* process) :
		ProcessState(process, "Waiting I/O") {

	}

	void update();
};


//State for Processes terminated
class ProcessTerminatedState : public ProcessState
{
public:
	ProcessTerminatedState(Process* process) :
		ProcessState(process, "Terminated") {

	}

	void update();
};