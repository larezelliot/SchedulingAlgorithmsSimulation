#include "Process.h"
#include "ProcessState.h"


int Process::processCounter = 0;


void Process::completeBurst() {
	// updates the prediction factor using the exponential prediction
	timePrediction = alpha * burstTimes.front() + (1 - alpha) * timePrediction;

	// removes the burst form the queue
	burstTimes.pop();

	if (isCompleted())
		changeState(new ProcessTerminatedState(this));
	else
		changeState(new ProcessWaitingIOState(this));
}


void Process::receiveIO() {

	// removes the I/O form the queue
	IOTimes.pop();

	if (isCompleted())
		changeState(new ProcessTerminatedState(this));
	else
		changeState(new ProcessReadyState(this));
}


void Process::changeState(ProcessState* state) {
	delete currentState;
	currentState = state;
}


Process::Process(std::queue<int> burstTimes, std::queue<int> IOTimes) :
	processID(processCounter++),
	burstTimes(burstTimes),
	IOTimes(IOTimes) {

	changeState(new ProcessReadyState(this));
}


Process::~Process() {
	delete currentState;
}


bool Process::isCompleted()
{
	if (burstTimes.empty() && IOTimes.empty())
		return true;
	return false;
}


void Process::start() {
	changeState(new ProcessRunningState(this));
}


void Process::update()
{
	currentState->update();
}


void Process::printProcess()
{
	std::cout << "Process #" << processID << "\n";
	std::cout << "\t" << "Status: " << currentState->getName() << "\n";
	std::cout << "\t" << "Time Waiting: " << timeWaiting << "\n";
	std::cout << "\t" << "Time Running: " << timeRunning << "\n";
	std::cout << "\t" << "Time Waiting For I/O: " << timeIO << "\n\n";
}

std::string Process::getState() {
	return currentState->getName();
}


int Process::getID() {
	return processID;
}

