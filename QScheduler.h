#pragma once
#include<vector>
#include<list>
#include "Process.h"
class QScheduler
{
	
public:

	virtual void addProcess(Process* process) = 0;

	virtual bool hasProcess() = 0;

	virtual Process* popProcess() = 0;

};


class FIFOScheduler : public QScheduler
{
private:
	std::queue<Process*> processes;


public:

	void addProcess(Process* process) {
		processes.push(process);
	}

	bool hasProcess() {
		return !processes.empty();
	}

	Process* popProcess() {
		Process* process = processes.front();
		processes.pop();
		return process;
	}
};



class ExpAvgScheduler :
	public QScheduler
{
private:
	std::priority_queue<Process*> processes;

public:

	void addProcess(Process* process) {
		processes.push(process);
	}

	bool hasProcess() {
		return !processes.empty();
	}

	Process* popProcess() {
		Process* process = processes.top();
		processes.pop();
		return process;
	}
};
