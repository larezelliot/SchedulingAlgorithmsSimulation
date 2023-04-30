#pragma once
#include "Simulation.h"

void Simulation::generateProcess()
{
	int burstNumber = rand() % (burstNumberMax - burstNumberMin + 1) + burstNumberMin;
	
	std::queue<int> burstTimes;
	std::queue<int> ioTimes;

	int burstTime = rand() % (burstTimeMax - burstTimeMin + 1) + burstTimeMin;
	int ioTime = rand() % (ioTimeMax - ioTimeMin + 1) + ioTimeMin;

	for (int i = 0; i < burstNumber; i++) {
		
		burstTimes.push(burstTime);

		ioTimes.push(ioTime);
	}

	Process* process = new Process(burstTimes, ioTimes);
	processes.push_back(process);
	cpu->addProcess(process);
}


Simulation::Simulation(int seed, int burstNumberMin, int burstNumberMax, int burstTimeMin, int burstTimeMax, int ioTimeMin, int ioTimeMax, int arrivalInterval, int maximumProcesses, std::string scheduler) :
	seed(seed),
	burstNumberMin(burstNumberMin),
	burstNumberMax(burstNumberMax),
	burstTimeMin(burstTimeMin),
	burstTimeMax(burstTimeMax),
	ioTimeMin(ioTimeMin),
	ioTimeMax(ioTimeMax),
	arrivalInterval(arrivalInterval),
	maximumProcesses(maximumProcesses),
	scheduler(scheduler)
{
	srand(seed);

	if (scheduler == "FIFO")
		cpu = new CPU(new FIFOScheduler());
	else
		cpu = new CPU(new ExpAvgScheduler());
}


Simulation::~Simulation()
{
	delete cpu;

	//HACK: Be careful in this part using foreach while dereferencing
	for (Process* process : processes)
		delete process;
}

void Simulation::run()
{
	int time = 0;
	generateProcess();
	int lastArrival = 0;

	
	std::cout << scheduler << "Simulation Started: (seed #" << seed << ")\n";
	std::cout << "0%______________________________________________________________________________________________100%\n";

	int jobsCompleted = 0;
	double nextMile = maximumProcesses/100;
	int i = 0;

	while(jobsCompleted < maximumProcesses) {
		if (lastArrival == arrivalInterval && processes.size()<maximumProcesses) {
			generateProcess();
			lastArrival = 0;
		}

		cpu->update();

		jobsCompleted = 0;
		for (Process* process : processes) {
			process->update();
			if (process->getState() == "Terminated")
				jobsCompleted++;
			//process->printProcess();
		}

		if (jobsCompleted >= nextMile) {
			std::cout << "*";
			nextMile += maximumProcesses / 100.00;
		}
		
		lastArrival++;
		time++;
	}
	std::cout << "\n";

	double avgRunningTime = 0;
	double avgIOTime = 0;
	double avgWaitTime = 0;
	jobsCompleted = 0;
	for (Process* process : processes)
		if (process->isCompleted()) {
			avgRunningTime += process->getTimeRunning();
			avgIOTime += process->getTimeIO();
			avgWaitTime += process->getTimeWaiting();
			jobsCompleted++;
		}
	avgRunningTime /= jobsCompleted;
	avgIOTime /= jobsCompleted;
	avgWaitTime /= jobsCompleted;

	std::cout << scheduler << " Simulation Completed: (seed #" <<  seed << ")\n";
	std::cout << "-----------------------------------------\n";
	std::cout << "\tTime Running: " << time << "\n";
	std::cout << "\tArrived Processes: " << processes.size() << "\n";
	std::cout << "\tNumber of Burst per Process: (" << burstNumberMin << ", " << burstNumberMax << ")\n";
	std::cout << "\tTime per Burst: (" << burstTimeMin << ", " << burstTimeMax << ")\n";
	std::cout << "\tTime per I/O wait: (" << ioTimeMin << ", " << ioTimeMax << ")\n";
	std::cout << "\tArrival Interval: " << arrivalInterval << "\n\n";

	std::cout << "\tJobs Completed: "<< jobsCompleted << "(" << 100.00*jobsCompleted/processes.size() << "%)\n";
	std::cout << "\tAverage Running Time per job: " << avgRunningTime << "\n";
	std::cout << "\tAverage I/O Time per job: " << avgIOTime << "\n";
	std::cout << "\tAverage Wait Time per job: "<< avgWaitTime <<"\n\n";
}
