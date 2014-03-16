// LampuLaluLintas.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Simulation.h"
#include "GameSimulation.h"

void Read()
{
	int i;
	std::string input;
	std::string tmp;
	std::vector<std::string> final;
	std::ifstream fin ("input.txt");
	fin >> input;
	fin >> input;
	fin >> tmp;
	for(i=0;i<=100;i++)
	{
		fin >> tmp;
		if(tmp.compare("[END]") == 0)
		{
			i = 100;
		}
		else final.push_back(tmp);
	}
	GameSimulation::StateInput(input,final);
}

int _tmain(int argc, _TCHAR* argv[])
{
	Read();
	Simulation::Start();
	return 0;
}

