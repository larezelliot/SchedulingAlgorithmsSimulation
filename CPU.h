#pragma once
#include "Process.h"
#include "CPUState.h"
#include "QScheduler.h"
#include "IODevice.h"

class CPUState;
class IODevice;

class CPU
{
private:
	
	//CPU States
	friend class CPUState;
	friend class CPUReadyState;
	friend class CPURunningState;

	//state of the CPU
	CPUState* currentState;

	//contains the CPU time counter
	int masterClock = 0;

	//IO Device
	IODevice* ioDevice = nullptr;

	//processes that is being executed
	Process* currentProcess = nullptr;

	//gets the processes ready to be executed
	QScheduler* scheduler;

	//changes the state of the processor
	void changeState(CPUState* state);

	//sends a process to the IO Device
	void sendProcessToIO();


public:

	//class constructor
	CPU(QScheduler* scheduler);

	//class destructor
	~CPU();

	//updates the CPU by calling it's state updaters
	void update();

	//adds a process to the CPU
	void addProcess(Process* process);

	//adds multiple processes to the CPU
	void addProcesses(std::vector<Process*> process);

	//prints the CPU with all the information about it current state
	void printCPU();
};
