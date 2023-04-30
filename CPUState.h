#pragma once
#include "CPU.h"

class CPU;

//Virtual base class for managing CPU states updates
class CPUState
{
protected:
	//CPU is the one in the current state (context of the state)
	CPU* cpu;
	const std::string name;

public:
	CPUState(CPU* cpu, std::string name) : cpu(cpu), name(name) {

	}

	//updates the CPU by one Quantum
	virtual void update() = 0;

	//gets state name
	std::string getName() const {
		return name;
	}
};

//The CPU is ready to run processes
class CPUReadyState : public CPUState
{
public:
	CPUReadyState(CPU* cpu) : CPUState(cpu, "Ready") {

	}

	void update();
};

//The CPU is running a process
class CPURunningState : public CPUState
{
public:
	CPURunningState(CPU* cpu) : CPUState(cpu, "Running") {

	}

	void update();
};