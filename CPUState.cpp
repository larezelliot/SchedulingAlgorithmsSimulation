#include "CPUState.h"


void CPUReadyState::update()
{
	cpu->masterClock++;

	if (cpu->scheduler->hasProcess()) {
		cpu->currentProcess = cpu->scheduler->popProcess();
		cpu->currentProcess->start();
		cpu->changeState(new CPURunningState(cpu));
	}
}


void CPURunningState::update()
{
	cpu->masterClock++;

	if (cpu->currentProcess->getState() == "Ready") {
		cpu->currentProcess->start();
	}
	else if (cpu->currentProcess->getState() == "Running") {

	}
	else if (cpu->currentProcess->getState() == "Waiting I/O") {
		cpu->sendProcessToIO();
		cpu->currentProcess = nullptr;
		if (cpu->scheduler->hasProcess()) {
			cpu->currentProcess = cpu->scheduler->popProcess();
			cpu->currentProcess->start();
			cpu->changeState(new CPURunningState(cpu));
		}
		else
			cpu->changeState(new CPUReadyState(cpu));
	}
	else if (cpu->currentProcess->getState() == "Terminated") {
		cpu->currentProcess = nullptr;
		cpu->changeState(new CPUReadyState(cpu));
	}
}
