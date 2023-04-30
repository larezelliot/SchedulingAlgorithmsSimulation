#pragma once
#include "Process.h"
#include "CPU.h"
#include <list>

class CPU;

class IODevice {
private:
	//CPU that manages the IO
	CPU* cpu;

	//contains process using IO
	std::list<Process*> processesInIO;
	
	//sends a process back to the CPU ready queue;
	void returnProcess(Process* process);

public:

	//Constructor
	IODevice(CPU* cpu) : cpu(cpu){

	}
	
	//adds a process to the IO device
	void addProcess(Process* process);
	

	//updates all devices waiting for I/O
	void update();

};