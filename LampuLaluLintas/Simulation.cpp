#include "stdafx.h"
#include "Simulation.h"
#include "GameSimulation.h"
#include "Resource.h"

Simulation::SimulationStatus Simulation::SimulationState = Uninitialized;
sf::RenderWindow Simulation::MainWindow;

void Simulation::Start()
{
	MainWindow.create(sf::VideoMode(800,600),"Lampu Lalu Lintas");

	Resource::LoadResource();

	SimulationState = Playing;

	while(!IsExiting())
	{
		SimulationLoop();
	}
}

bool Simulation::IsExiting()
{
	if(SimulationState == Simulation::Exiting) return true;
	else return false;
}

void Simulation::SimulationLoop()
{
	switch(SimulationState)
	{
	case Simulation::Playing:
		{
			SimulationPlaying();
			break;
		}
	}
}

void Simulation::SimulationPlaying()
{
	GameSimulation::Show(MainWindow);
	SimulationState = Simulation::Exiting;
}