#pragma once

#include "Waktu.h"

class GameSimulation
{
public:
	enum GameSimulationStatus{KMKMM, HMHMM, MMMMM, HKHMM, MKMMM, MHMMH,MHMKH,MHMKM,MHMHM,KHKHM};
	static void Show(sf::RenderWindow& GameWindow);
	static void SetAttribute();
	static void hover(sf::RenderWindow& GameWindow);
	static void Simulation(sf::RenderWindow& GameWindow, Waktu CounterTime);
	static void HandlerState(Waktu& CounterTime);
	static void MoveHuman(sf::RenderWindow& GameWindow, Waktu CounterTime);
	static void MoveCarNorth(sf::RenderWindow& GameWindow, int i);
	static void MoveCarSouth(sf::RenderWindow& GameWindow, int i);
	static void MoveCarWest(sf::RenderWindow& GameWindow, int i);
	static void MoveCarEast(sf::RenderWindow& GameWindow, int i);
	static void MoveCarEastNorth(sf::RenderWindow& GameWindow, int i);
	static void StateInput(std::string input, std::vector<std::string> final);
	static bool CheckFinalState();

	enum ButtonAction{TambahNorth,KurangNorth,TambahSouth,KurangSouth,TambahWest,KurangWest,TambahEast,KurangEast,Nothing};
	struct Button
	{
		sf::IntRect rect;
		ButtonAction action;
	};

	static GameSimulationStatus GameSimulationState;
private:
	static std::vector<std::string> FinalState;
	static bool IsSebrang;
	static bool IsCanClose;
	static int DummyTimeCounter;
	static std::vector<Button> ButtonItem;

	static ButtonAction HandlerButton(sf::Vector2i i);
	static void CaseHandlerButton(ButtonAction Action);
	static void CarRectHandler();
	static bool IsInSquare(sf::IntRect x);

	static bool IsRotated;
	static int AmountNorth;
	static int AmountSouth;
	static int AmountWest;
	static int AmountEast;
};