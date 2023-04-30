#include "CPU.h"


void CPU::changeState(CPUState* state) {
	delete currentState;
	currentState = state;
}


void CPU::update()
{
	ioDevice->update();
	currentState->update();
}


void CPU::addProcess(Process* process)
{
	scheduler->addProcess(process);
}


void CPU::addProcesses(std::vector<Process*> processes)
{
	for (Process* process : processes)
		addProcess(process);
}


void CPU::printCPU()
{
	std::cout << "CPU (" << masterClock << ")\n";

	if (currentState)
		std::cout << "\tState: " << currentState->getName() << "\n";

	if (currentProcess)
		std::cout << "\tProcess Running: " << currentProcess->getID() << "\n";
}


CPU::CPU(QScheduler* scheduler) : scheduler(scheduler)
{
	ioDevice = new IODevice(this);

	changeState(new CPUReadyState(this));
}


CPU::~CPU()
{
	delete currentState;
	delete ioDevice;
	delete scheduler;
}


void CPU::sendProcessToIO()
{
	ioDevice->addProcess(currentProcess);
	currentProcess = nullptr;
}

