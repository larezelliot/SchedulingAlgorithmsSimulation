// SimulationProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <queue>
#include "Qscheduler.h"
#include "CPU.h"
#include "IODevice.h"
#include "Process.h"
#include "Simulation.h"

int seed = 0, burstNumberMin=10, burstNumberMax=10, burstTimeMin=1, burstTimeMax=10, ioTimeMin=10, ioTimeMax=100, arrivalInterval=5, maximumProcesses = 250;

void introduceSimulationParameters() {
	std::cout << "Introducing Simulation Parameter:\n";
	std::cout << "NOTE: for ranges uses space separation and no parenthesis\n";
	std::cout << "\tNumber of bursts (min, max): ";
	std::cin >> burstNumberMin >> burstNumberMax;
	std::cout << "\tBurst time (min, max): ";
	std::cin >> burstTimeMin >> burstTimeMax;
	std::cout << "\tI/O time (min, max): ";
	std::cin >> ioTimeMin >> ioTimeMax;
	std::cout << "\tArrival Interval: ";
	std::cin >> arrivalInterval;
	std::cout << "\n\n";
}

void introduceSimulationConfiguration() {
	std::cout << "Introducing Simulation Configuration:\n";
	std::cout << "NOTE: for ranges uses space separation and no parenthesis\n";
	std::cout << "\tSeed: ";
	std::cin >> seed;
	std::cout << "\tMaximum Processes: ";
	std::cin >> maximumProcesses;
	std::cout << "\n\n";
}

int main()
{
	//introduceSimulationParameters();
	bool isMenuActive = true;

	while (isMenuActive) {
		int op = 0;

		system("cls");
		std::cout << "Simulation Project Main Menu:\n";
		std::cout << "\t1. Change Parameters\n";
		std::cout << "\t2. Change Configuration\n";
		std::cout << "\t3. Run for First In, Fist Out Scheduling\n";
		std::cout << "\t4. Run for Exponential Average Scheduling\n";
		std::cout << "\t5. Exit\n";

		std::cout << "Introduce an option: ";
		std::cin >> op;

		system("cls");

		switch (op)
		{
			case 1: {
				introduceSimulationParameters();
				system("PAUSE");
				break;
			}
			case 2: {
				introduceSimulationConfiguration();
				system("PAUSE");
				break;
			}
			case 3: {
				Simulation* simulation = new Simulation(seed, burstNumberMin, burstNumberMax, burstTimeMin, burstTimeMax, ioTimeMin, ioTimeMax, arrivalInterval, maximumProcesses, "FIFO");
				simulation->run();
				delete simulation;
				system("PAUSE");
				break;
			}
			case 4: {
				Simulation* simulation2 = new Simulation(seed, burstNumberMin, burstNumberMax, burstTimeMin, burstTimeMax, ioTimeMin, ioTimeMax, arrivalInterval, maximumProcesses, "ExpAvg");
				simulation2->run();
				delete simulation2;
				system("PAUSE");
				break;
			}
			case 5: {
				isMenuActive = false;
				system("PAUSE");
				break;
			}
		}
	}
}



