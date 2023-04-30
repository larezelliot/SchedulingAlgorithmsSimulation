#include "IODevice.h"
#include "CPU.h"

void IODevice::returnProcess(Process* process)
{
	if (process->getState() == "Ready")
		cpu->addProcess(process);
	processesInIO.remove(process);
}


void IODevice::addProcess(Process* process)
{
	processesInIO.push_back(process);
}


void IODevice::update()
{
	std::list<Process*> processesCopy(processesInIO);
	for (Process* process : processesCopy) {
		if (process->getState() == "Ready")
			returnProcess(process);
		if (process->getState() == "Terminated")
			processesInIO.remove(process);
	}
}
