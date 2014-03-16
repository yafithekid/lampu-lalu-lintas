#pragma once

class Simulation
{
public:
	enum SimulationStatus{Playing,Exiting,Uninitialized};
	static void Start();
	static bool IsExiting();
	static void SimulationLoop();
	static void SimulationPlaying();

private:
	static SimulationStatus SimulationState;
	static sf::RenderWindow MainWindow;
};