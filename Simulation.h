#pragma once
#include <list>
#include <stdlib.h>
#include "CPU.h"
#include "Process.h"

class Simulation
{
private:
	//CPU used in the simulation
	CPU* cpu;

	//Contains the processes created in the simulation
	std::list<Process*> processes;

	//The range for number of burst in the processes
	int burstNumberMin;
	int burstNumberMax;

	//The range for burst time in the processes, measured in time
	int burstTimeMin;
	int burstTimeMax;

	//The range for I/O time in the processes, measured in time
	int ioTimeMin;
	int ioTimeMax;

	//Interval in which processes arrive
	int arrivalInterval;
	
	int maximumProcesses;

	int seed;

	std::string scheduler;

	//Creates a Process
	void generateProcess();


public:
	//Construct a simulation
	Simulation(int seed, int burstNumberMin, int burstNumberMax, int burstTimeMin, int burstTimeMax, int ioTimeMin, int ioTimeMax, int arrivalInterval, int maximumProcesses, std::string scheduler);

	//Destructor
	~Simulation();

	//Run a simulation for a given amount of quantums
	void run();
};

