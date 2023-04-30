#include "ProcessState.h"


ProcessState::ProcessState(Process* process, std::string name) : process(process), name(name)
{
}


void ProcessReadyState::update()
{
	currentTime++;
	process->timeWaiting++;
}


void ProcessRunningState::update()
{
	currentTime++;
	process->timeRunning++;

	if (currentTime >= process->getBurst())
		process->completeBurst();
}


void ProcessWaitingIOState::update()
{
	currentTime++;
	process->timeIO++;

	if (currentTime >= process->getIO())
		process->receiveIO();
}


void ProcessTerminatedState::update()
{
	currentTime++;
}
