#include "stdafx.h"
#include "GameSimulation.h"
#include "Resource.h"
#include "Waktu.h"

GameSimulation::GameSimulationStatus GameSimulation::GameSimulationState = KMKMM;
std::vector<std::string> GameSimulation::FinalState;
bool GameSimulation::IsSebrang = false;
bool GameSimulation::IsCanClose = false;
int GameSimulation::DummyTimeCounter = 0;
std::vector<GameSimulation::Button> GameSimulation::ButtonItem;
int GameSimulation::AmountNorth = 0;
int GameSimulation::AmountSouth = 0;
int GameSimulation::AmountWest = 0;
int GameSimulation::AmountEast = 0;
bool GameSimulation::IsRotated = false;


void GameSimulation::Show(sf::RenderWindow& GameWindow)
{
	//variable
	sf::Event GameEvent;
	sf::Text Timer;
	sf::String Buffer;
	Waktu CounterTime;
	
	//text for timer
	Timer.setFont(Resource::SimulationFont);
	Timer.setCharacterSize(30);
	Timer.setColor(sf::Color::Black);
	Timer.setStyle(sf::Text::Bold);
	Timer.setPosition(750,15);

	//text for amount car from 4 direction
	sf::Text DirectionText;
	DirectionText.setFont(Resource::SimulationFont);
	DirectionText.setCharacterSize(15);
	DirectionText.setColor(sf::Color::Black);
	DirectionText.setStyle(sf::Text::Bold);
	DirectionText.setPosition(150,0);

	//set attribute
	SetAttribute();

	//buffer
	char buff[100];

	//set frame limit
	GameWindow.setFramerateLimit(60);

	//begin time
	Waktu::Begin();
	CounterTime.BeginNS();

	int iterator;
	
	while(true)
	{
		GameWindow.clear();
		GameWindow.draw(Resource::background);

		//get current event
		while(GameWindow.pollEvent(GameEvent))
		{
			if(GameEvent.type == sf::Event::Closed)
				return;
			else if(GameEvent.type == sf::Event::MouseButtonPressed)
			{
				sf::Vector2i i;
				i.x = GameEvent.mouseButton.x;
				i.y = GameEvent.mouseButton.y;
				if(Resource::sebrangRect.contains(i) && GameSimulationState == GameSimulation::HMHMM)
				{
					IsSebrang = true;
					DummyTimeCounter = CounterTime.GetWaktu();
				}
				else if(Resource::closeRect.contains(i) && IsCanClose)
				{
					return;
				}
				else
				{
					CaseHandlerButton(HandlerButton(i));
				}
			}
		}

		//rutin cek final state
		IsCanClose = CheckFinalState();

		//rutin car rect
		CarRectHandler();

		//moving car from north
		for(iterator = 0; iterator<AmountNorth;iterator++)
		{
			MoveCarNorth(GameWindow, iterator);
		}

		//moving car from south
		for(iterator = 0; iterator<AmountSouth;iterator++)
		{
			MoveCarSouth(GameWindow, iterator);
		}

		//moving car from west
		for(iterator = 0; iterator<AmountWest;iterator++)
		{
			MoveCarWest(GameWindow, iterator);
		}

		//moving car from east
		for(iterator = 0; iterator<AmountEast;iterator++)
		{
			if(iterator == 3 || iterator == 6 || iterator == 9)
			{
				MoveCarEastNorth(GameWindow,iterator);
			}
			else MoveCarEast(GameWindow, iterator);
		}

		//mouse hover
		hover(GameWindow);
		
		std::cout<<CounterTime.GetWaktu()<<std::endl;

		//handler State
		HandlerState(CounterTime);

		//begin the simulation
		Simulation(GameWindow,CounterTime);

		//get current time and set the timer
		sprintf_s<100>(buff,"%d",(int)Waktu::GetCurrentTime());
		Timer.setString(buff);

		//set string for direction text
		sprintf_s<100>(buff,"North = %d, South = %d\nWest = %d, East = %d", AmountNorth,AmountSouth,AmountWest,AmountEast);
		DirectionText.setString(buff);

		GameWindow.draw(DirectionText);
		GameWindow.draw(Timer);
		GameWindow.display();
	}
}

void GameSimulation::SetAttribute()
{
	//set position for button north
	Resource::tambahnorth.setPosition(700,100);
	Resource::tambahnorthhover.setPosition(700,100);
	Resource::tambahnorthRect.height = (int)Resource::tambahnorth.getGlobalBounds().height;
	Resource::tambahnorthRect.width = (int)Resource::tambahnorth.getGlobalBounds().width;
	Resource::tambahnorthRect.left = (int)Resource::tambahnorth.getGlobalBounds().left;
	Resource::tambahnorthRect.top = (int)Resource::tambahnorth.getGlobalBounds().top;

	Resource::kurangnorth.setPosition(Resource::tambahnorth.getPosition().x,Resource::tambahnorth.getPosition().y+Resource::tambahnorth.getGlobalBounds().height+10);
	Resource::kurangnorthhover.setPosition(Resource::tambahnorth.getPosition().x,Resource::tambahnorth.getPosition().y+Resource::tambahnorth.getGlobalBounds().height+10);
	Resource::kurangnorthRect.height = (int)Resource::kurangnorth.getGlobalBounds().height;
	Resource::kurangnorthRect.width = (int)Resource::kurangnorth.getGlobalBounds().width;
	Resource::kurangnorthRect.left = (int)Resource::kurangnorth.getGlobalBounds().left;
	Resource::kurangnorthRect.top = (int)Resource::kurangnorth.getGlobalBounds().top;

	//set position for button south
	Resource::sebrang.setPosition(30,350);
	Resource::sebranghover.setPosition(30,350);
	Resource::sebrangRect.height = (int)Resource::sebrang.getGlobalBounds().height;
	Resource::sebrangRect.width = (int)Resource::sebrang.getGlobalBounds().width;
	Resource::sebrangRect.left = (int)Resource::sebrang.getGlobalBounds().left;
	Resource::sebrangRect.top = (int)Resource::sebrang.getGlobalBounds().top;

	Resource::tambahsouth.setPosition(Resource::sebrang.getPosition().x,Resource::sebrang.getPosition().y+Resource::sebrang.getGlobalBounds().height+10);
	Resource::tambahsouthhover.setPosition(Resource::sebrang.getPosition().x,Resource::sebrang.getPosition().y +Resource::sebrang.getGlobalBounds().height+10);
	Resource::tambahsouthRect.height = (int)Resource::tambahsouth.getGlobalBounds().height;
	Resource::tambahsouthRect.width = (int)Resource::tambahsouth.getGlobalBounds().width;
	Resource::tambahsouthRect.left = (int)Resource::tambahsouth.getGlobalBounds().left;
	Resource::tambahsouthRect.top = (int)Resource::tambahsouth.getGlobalBounds().top;

	Resource::kurangsouth.setPosition(Resource::tambahsouth.getPosition().x, Resource::tambahsouth.getPosition().y +Resource::tambahsouth.getGlobalBounds().height+10);
	Resource::kurangsouthhover.setPosition(Resource::tambahsouth.getPosition().x, Resource::tambahsouth.getPosition().y +Resource::tambahsouth.getGlobalBounds().height+10);
	Resource::kurangsouthRect.height = (int)Resource::kurangsouth.getGlobalBounds().height;
	Resource::kurangsouthRect.width = (int)Resource::kurangsouth.getGlobalBounds().width;
	Resource::kurangsouthRect.left = (int)Resource::kurangsouth.getGlobalBounds().left;
	Resource::kurangsouthRect.top = (int)Resource::kurangsouth.getGlobalBounds().top;

	//set position for button west
	Resource::tambahwest.setPosition(30,100);
	Resource::tambahwesthover.setPosition(30,100);
	Resource::tambahwestRect.height = (int)Resource::tambahwest.getGlobalBounds().height;
	Resource::tambahwestRect.width = (int)Resource::tambahwest.getGlobalBounds().width;
	Resource::tambahwestRect.left = (int)Resource::tambahwest.getGlobalBounds().left;
	Resource::tambahwestRect.top = (int)Resource::tambahwest.getGlobalBounds().top;

	Resource::kurangwest.setPosition(Resource::tambahwest.getPosition().x,Resource::tambahwest.getPosition().y+Resource::tambahwest.getGlobalBounds().height+10);
	Resource::kurangwesthover.setPosition(Resource::tambahwest.getPosition().x,Resource::tambahwest.getPosition().y+Resource::tambahwest.getGlobalBounds().height+10);
	Resource::kurangwestRect.height = (int)Resource::kurangwest.getGlobalBounds().height;
	Resource::kurangwestRect.width = (int)Resource::kurangwest.getGlobalBounds().width;
	Resource::kurangwestRect.left = (int)Resource::kurangwest.getGlobalBounds().left;
	Resource::kurangwestRect.top = (int)Resource::kurangwest.getGlobalBounds().top;

	//set position for button east
	Resource::tambaheast.setPosition(700,400);
	Resource::tambaheasthover.setPosition(700,400);
	Resource::tambaheastRect.height = (int)Resource::tambaheast.getGlobalBounds().height;
	Resource::tambaheastRect.width = (int)Resource::tambaheast.getGlobalBounds().width;
	Resource::tambaheastRect.left = (int)Resource::tambaheast.getGlobalBounds().left;
	Resource::tambaheastRect.top = (int)Resource::tambaheast.getGlobalBounds().top;

	Resource::kurangeast.setPosition(Resource::tambaheast.getPosition().x,Resource::tambaheast.getPosition().y+Resource::tambaheast.getGlobalBounds().height+10);
	Resource::kurangeasthover.setPosition(Resource::tambaheast.getPosition().x,Resource::tambaheast.getPosition().y+Resource::tambaheast.getGlobalBounds().height+10);
	Resource::kurangeastRect.height = (int)Resource::kurangeast.getGlobalBounds().height;
	Resource::kurangeastRect.width = (int)Resource::kurangeast.getGlobalBounds().width;
	Resource::kurangeastRect.left = (int)Resource::kurangeast.getGlobalBounds().left;
	Resource::kurangeastRect.top = (int)Resource::kurangeast.getGlobalBounds().top;

	//set position close button
	Resource::close.setPosition(Resource::kurangeast.getPosition().x,Resource::kurangeast.getPosition().y+Resource::kurangeast.getGlobalBounds().height+10);
	Resource::closehover.setPosition(Resource::kurangeast.getPosition().x,Resource::kurangeast.getPosition().y+Resource::kurangeast.getGlobalBounds().height+10);
	Resource::closeRect.height = (int)Resource::close.getGlobalBounds().height;
	Resource::closeRect.width = (int)Resource::close.getGlobalBounds().width;
	Resource::closeRect.left = (int)Resource::close.getGlobalBounds().left;
	Resource::closeRect.top = (int)Resource::close.getGlobalBounds().top;

	//adding the button to the array
	Button northPlusButton;
	Button northMinusButton;
	Button southPlusButton;
	Button southMinusButton;
	Button westPlusButton;
	Button westMinusButton;
	Button eastPlusButton;
	Button eastMinusButton;
	northPlusButton.rect = Resource::tambahnorthRect;
	northPlusButton.action = TambahNorth;
	northMinusButton.rect = Resource::kurangnorthRect;
	northMinusButton.action = KurangNorth;
	southPlusButton.rect = Resource::tambahsouthRect;
	southPlusButton.action = TambahSouth;
	southMinusButton.rect = Resource::kurangsouthRect;
	southMinusButton.action = KurangSouth;
	westPlusButton.rect = Resource::tambahwestRect;
	westPlusButton.action = TambahWest;
	westMinusButton.rect = Resource::kurangwestRect;
	westMinusButton.action = KurangWest;
	eastPlusButton.rect = Resource::tambaheastRect;
	eastPlusButton.action = TambahEast;
	eastMinusButton.rect = Resource::kurangeastRect;
	eastMinusButton.action = KurangEast;

	ButtonItem.push_back(northPlusButton);
	ButtonItem.push_back(northMinusButton);
	ButtonItem.push_back(southPlusButton);
	ButtonItem.push_back(southMinusButton);
	ButtonItem.push_back(westPlusButton);
	ButtonItem.push_back(westMinusButton);
	ButtonItem.push_back(eastPlusButton);
	ButtonItem.push_back(eastMinusButton);

	//set position for trafic light
	Resource::redyellowgoredpeoplenorth.setPosition(425,175);
	Resource::greengoredpeoplenorth.setPosition(425,175);
	Resource::redgogreenpeoplenorth.setPosition(425,175);
	Resource::redgoredpeoplenorth.setPosition(425,175);
	Resource::redyellowgoredpeoplesouth.setPosition(350,350);
	Resource::greengoredpeoplesouth.setPosition(350,350);
	Resource::redgogreenpeoplesouth.setPosition(350,350);
	Resource::redgoredpeoplesouth.setPosition(350,350);
	Resource::redwest.setPosition(350,250);
	Resource::greenwest.setPosition(350,250);
	Resource::redyellowwest.setPosition(350,250);
	Resource::redgoredright.setPosition(450,350);
	Resource::greengogreenright.setPosition(450,350);
	Resource::greengoredright.setPosition(450,350);
	Resource::redyellowgoredright.setPosition(450,350);

	//position for human
	Resource::humannorth.setPosition(425,220);
	Resource::humansouth.setPosition(350,330);
}

void GameSimulation::hover(sf::RenderWindow& GameWindow)
{
	if(Resource::sebrangRect.contains(sf::Mouse::getPosition(GameWindow)))
	{
		GameWindow.draw(Resource::sebranghover);
		if(IsCanClose)
		{
			GameWindow.draw(Resource::closehover);
		}
		else GameWindow.draw(Resource::close);
		//button north
		GameWindow.draw(Resource::tambahnorth);
		GameWindow.draw(Resource::kurangnorth);
		//button south
		GameWindow.draw(Resource::tambahsouth);
		GameWindow.draw(Resource::kurangsouth);
		//button west
		GameWindow.draw(Resource::tambahwest);
		GameWindow.draw(Resource::kurangwest);
		//button east
		GameWindow.draw(Resource::tambaheast);
		GameWindow.draw(Resource::kurangeast);
	}
	else
	{
		switch(HandlerButton(sf::Mouse::getPosition(GameWindow)))
		{
			case GameSimulation::TambahNorth:
			{
				GameWindow.draw(Resource::sebrang);
				if(IsCanClose)
				{
					GameWindow.draw(Resource::closehover);
				}
				else GameWindow.draw(Resource::close);
				//button north
				GameWindow.draw(Resource::tambahnorthhover);
				GameWindow.draw(Resource::kurangnorth);
				//button south
				GameWindow.draw(Resource::tambahsouth);
				GameWindow.draw(Resource::kurangsouth);
				//button west
				GameWindow.draw(Resource::tambahwest);
				GameWindow.draw(Resource::kurangwest);
				//button east
				GameWindow.draw(Resource::tambaheast);
				GameWindow.draw(Resource::kurangeast);	
				break;
			}
			case GameSimulation::KurangNorth:
			{
				GameWindow.draw(Resource::sebrang);
				if(IsCanClose)
				{
					GameWindow.draw(Resource::closehover);
				}
				else GameWindow.draw(Resource::close);
				//button north
				GameWindow.draw(Resource::tambahnorth);
				GameWindow.draw(Resource::kurangnorthhover);
				//button south
				GameWindow.draw(Resource::tambahsouth);
				GameWindow.draw(Resource::kurangsouth);
				//button west
				GameWindow.draw(Resource::tambahwest);
				GameWindow.draw(Resource::kurangwest);
				//button east
				GameWindow.draw(Resource::tambaheast);
				GameWindow.draw(Resource::kurangeast);	
				break;
			}
			case GameSimulation::TambahSouth:
			{
				GameWindow.draw(Resource::sebrang);
				if(IsCanClose)
				{
					GameWindow.draw(Resource::closehover);
				}
				else GameWindow.draw(Resource::close);
				//button north
				GameWindow.draw(Resource::tambahnorth);
				GameWindow.draw(Resource::kurangnorth);
				//button south
				GameWindow.draw(Resource::tambahsouthhover);
				GameWindow.draw(Resource::kurangsouth);
				//button west
				GameWindow.draw(Resource::tambahwest);
				GameWindow.draw(Resource::kurangwest);
				//button east
				GameWindow.draw(Resource::tambaheast);
				GameWindow.draw(Resource::kurangeast);	
				break;
			}
			case GameSimulation::KurangSouth:
			{
				GameWindow.draw(Resource::sebrang);
				if(IsCanClose)
				{
					GameWindow.draw(Resource::closehover);
				}
				else GameWindow.draw(Resource::close);
				//button north
				GameWindow.draw(Resource::tambahnorth);
				GameWindow.draw(Resource::kurangnorth);
				//button south
				GameWindow.draw(Resource::tambahsouth);
				GameWindow.draw(Resource::kurangsouthhover);
				//button west
				GameWindow.draw(Resource::tambahwest);
				GameWindow.draw(Resource::kurangwest);
				//button east
				GameWindow.draw(Resource::tambaheast);
				GameWindow.draw(Resource::kurangeast);	
				break;
			}
			case GameSimulation::TambahWest:
			{
				GameWindow.draw(Resource::sebrang);
				if(IsCanClose)
				{
					GameWindow.draw(Resource::closehover);
				}
				else GameWindow.draw(Resource::close);
				//button north
				GameWindow.draw(Resource::tambahnorth);
				GameWindow.draw(Resource::kurangnorth);
				//button south
				GameWindow.draw(Resource::tambahsouth);
				GameWindow.draw(Resource::kurangsouth);
				//button west
				GameWindow.draw(Resource::tambahwesthover);
				GameWindow.draw(Resource::kurangwest);
				//button east
				GameWindow.draw(Resource::tambaheast);
				GameWindow.draw(Resource::kurangeast);	
				break;
			}
			case GameSimulation::KurangWest:
			{
				GameWindow.draw(Resource::sebrang);
				if(IsCanClose)
				{
					GameWindow.draw(Resource::closehover);
				}
				else GameWindow.draw(Resource::close);
				//button north
				GameWindow.draw(Resource::tambahnorth);
				GameWindow.draw(Resource::kurangnorth);
				//button south
				GameWindow.draw(Resource::tambahsouth);
				GameWindow.draw(Resource::kurangsouth);
				//button west
				GameWindow.draw(Resource::tambahwest);
				GameWindow.draw(Resource::kurangwesthover);
				//button east
				GameWindow.draw(Resource::tambaheast);
				GameWindow.draw(Resource::kurangeast);	
				break;
			}
			case GameSimulation::TambahEast:
			{
				GameWindow.draw(Resource::sebrang);
				if(IsCanClose)
				{
					GameWindow.draw(Resource::closehover);
				}
				else GameWindow.draw(Resource::close);
				//button north
				GameWindow.draw(Resource::tambahnorth);
				GameWindow.draw(Resource::kurangnorth);
				//button south
				GameWindow.draw(Resource::tambahsouth);
				GameWindow.draw(Resource::kurangsouth);
				//button west
				GameWindow.draw(Resource::tambahwest);
				GameWindow.draw(Resource::kurangwest);
				//button east
				GameWindow.draw(Resource::tambaheasthover);
				GameWindow.draw(Resource::kurangeast);	
				break;
			}
			case GameSimulation::KurangEast:
			{
				GameWindow.draw(Resource::sebrang);
				if(IsCanClose)
				{
					GameWindow.draw(Resource::closehover);
				}
				else GameWindow.draw(Resource::close);
				//button north
				GameWindow.draw(Resource::tambahnorth);
				GameWindow.draw(Resource::kurangnorth);
				//button south
				GameWindow.draw(Resource::tambahsouth);
				GameWindow.draw(Resource::kurangsouth);
				//button west
				GameWindow.draw(Resource::tambahwest);
				GameWindow.draw(Resource::kurangwest);
				//button east
				GameWindow.draw(Resource::tambaheast);
				GameWindow.draw(Resource::kurangeasthover);	
				break;
			}
			default:
				{
					GameWindow.draw(Resource::sebrang);
					if(IsCanClose)
					{
						GameWindow.draw(Resource::closehover);
					}
					else GameWindow.draw(Resource::close);
					//button north
					GameWindow.draw(Resource::tambahnorth);
					GameWindow.draw(Resource::kurangnorth);
					//button south
					GameWindow.draw(Resource::tambahsouth);
					GameWindow.draw(Resource::kurangsouth);
					//button west
					GameWindow.draw(Resource::tambahwest);
					GameWindow.draw(Resource::kurangwest);
					//button east
					GameWindow.draw(Resource::tambaheast);
					GameWindow.draw(Resource::kurangeast);	
					break;
				}
		}
	}
}

void GameSimulation::Simulation(sf::RenderWindow& GameWindow,Waktu CounterTime)
{
	switch (GameSimulation::GameSimulationState)
	{
	case GameSimulation::KMKMM:
		{
			GameWindow.draw(Resource::redyellowgoredpeoplenorth);
			GameWindow.draw(Resource::redyellowgoredpeoplesouth);
			GameWindow.draw(Resource::redwest);
			GameWindow.draw(Resource::redgoredright);
			break;
		}
	case GameSimulation::HMHMM:
		{
			GameWindow.draw(Resource::greengoredpeoplenorth);
			GameWindow.draw(Resource::greengoredpeoplesouth);
			GameWindow.draw(Resource::redwest);
			GameWindow.draw(Resource::redgoredright);
			break;
		}
	case GameSimulation::HKHMM:
		{
			GameWindow.draw(Resource::greengoredpeoplenorth);
			GameWindow.draw(Resource::greengoredpeoplesouth);
			GameWindow.draw(Resource::redwest);
			GameWindow.draw(Resource::redyellowgoredright);
			break;
		}
	case GameSimulation::MKMMM:
		{
			GameWindow.draw(Resource::redgoredpeoplenorth);
			GameWindow.draw(Resource::redgoredpeoplesouth);
			GameWindow.draw(Resource::redwest);
			GameWindow.draw(Resource::redyellowgoredright);
			break;
		}
	case GameSimulation::MHMMH:
		{
			GameWindow.draw(Resource::redgoredpeoplenorth);
			GameWindow.draw(Resource::redgoredpeoplesouth);
			GameWindow.draw(Resource::redwest);
			GameWindow.draw(Resource::greengogreenright);
			break;
		}
	case GameSimulation::MHMKH:
		{
			GameWindow.draw(Resource::redgoredpeoplenorth);
			GameWindow.draw(Resource::redgoredpeoplesouth);
			GameWindow.draw(Resource::redyellowwest);
			GameWindow.draw(Resource::greengogreenright);
			break;
		}
	case GameSimulation::MHMKM:
		{
			GameWindow.draw(Resource::redgoredpeoplenorth);
			GameWindow.draw(Resource::redgoredpeoplesouth);
			GameWindow.draw(Resource::redyellowwest);
			GameWindow.draw(Resource::greengoredright);
			break;
		}
	case GameSimulation::MHMHM:
		{
			GameWindow.draw(Resource::redgoredpeoplenorth);
			GameWindow.draw(Resource::redgoredpeoplesouth);
			GameWindow.draw(Resource::greenwest);
			GameWindow.draw(Resource::greengoredright);
			break;
		}
	case GameSimulation::KHKHM:
		{
			GameWindow.draw(Resource::redyellowgoredpeoplenorth);
			GameWindow.draw(Resource::redyellowgoredpeoplesouth);
			GameWindow.draw(Resource::greenwest);
			GameWindow.draw(Resource::greengoredright);
			break;
		}
	case GameSimulation::MMMMM:
		{
			MoveHuman(GameWindow,CounterTime);
			GameWindow.draw(Resource::redgogreenpeoplenorth);
			GameWindow.draw(Resource::redgogreenpeoplesouth);
			GameWindow.draw(Resource::redwest);
			GameWindow.draw(Resource::redgoredright);
			break;
		}
	}
}

void GameSimulation::HandlerState(Waktu& CounterTime)
{
	if(IsSebrang && GameSimulationState == GameSimulation::HMHMM)
	{
		GameSimulationState = GameSimulation::MMMMM;
		IsSebrang = false;
	}
	else if(GameSimulationState == GameSimulation::MMMMM && CounterTime.GetWaktu() - DummyTimeCounter >= 20)
	{
		if(105 - DummyTimeCounter >= 20)
		{
			GameSimulationState = GameSimulation::HMHMM;
		}
		else
		{
			GameSimulationState = GameSimulation::HKHMM;
			CounterTime.BeginNS();
		}
	}
	else if(((AmountNorth > 10 || AmountSouth > 10) && (AmountWest == 0 || AmountEast == 0 || AmountNorth >=2*(AmountEast+AmountWest) || AmountNorth >=2*(AmountEast+AmountWest)
			|| AmountSouth >= 2*(AmountEast+AmountWest) || AmountSouth >= 2*(AmountEast+AmountWest)))
			&& (GameSimulationState == GameSimulation::MHMMH || GameSimulationState == GameSimulation::MHMKH
			|| GameSimulationState == GameSimulation::MHMKM || GameSimulationState == GameSimulation::MHMHM
			|| GameSimulationState == GameSimulation::KHKHM))
	{
		GameSimulationState = GameSimulation::KMKMM;
		CounterTime.BeginNS();
	}

	else if(GameSimulationState == GameSimulation::KMKMM && CounterTime.GetWaktu() >= 5)
	{
		GameSimulationState = GameSimulation::HMHMM;
		CounterTime.BeginNS();
	}
	else if(GameSimulationState == GameSimulation::HMHMM && CounterTime.GetWaktu()>=105)
	{
		GameSimulationState = GameSimulation::HKHMM;
		CounterTime.BeginNS();
	}
	else if(GameSimulationState == GameSimulation::HKHMM && CounterTime.GetWaktu()>=5)
	{
		GameSimulationState = GameSimulation::MKMMM;
		CounterTime.BeginNS();
	}
	else if(GameSimulationState == GameSimulation::MKMMM && CounterTime.GetWaktu()>=5)
	{
		GameSimulationState = GameSimulation::MHMMH;
		CounterTime.BeginNS();
	}
	else if(GameSimulationState == GameSimulation::MHMMH && CounterTime.GetWaktu()>=25)
	{
		GameSimulationState = GameSimulation::MHMKH;
		CounterTime.BeginNS();
	}
	else if(GameSimulationState == GameSimulation::MHMKH && CounterTime.GetWaktu()>=5)
	{
		GameSimulationState = GameSimulation::MHMKM;
		CounterTime.BeginNS();
	}
	else if(GameSimulationState == GameSimulation::MHMKM && CounterTime.GetWaktu()>=5)
	{
		GameSimulationState = GameSimulation::MHMHM;
		CounterTime.BeginNS();
	}
	else if(GameSimulationState == GameSimulation::MHMHM && CounterTime.GetWaktu()>=75)
	{
		GameSimulationState = GameSimulation::KHKHM;
		CounterTime.BeginNS();
	}
	else if(GameSimulationState == GameSimulation::KHKHM && CounterTime.GetWaktu()>=5)
	{
		GameSimulationState = GameSimulation::KMKMM;
		CounterTime.BeginNS();
	}
}

GameSimulation::ButtonAction GameSimulation::HandlerButton(sf::Vector2i i)
{
	std::vector<Button>::iterator it;
	for(it = ButtonItem.begin(); it != ButtonItem.end(); it++)
	{
		if((*it).rect.contains(i))
			return (*it).action;
	}
	return Nothing;
}

void GameSimulation::CaseHandlerButton(GameSimulation::ButtonAction Action)
{
	switch(Action)
	{
		case GameSimulation::TambahNorth:
		{
			if(AmountNorth < 11)
				AmountNorth++;
			break;
		}
		case GameSimulation::KurangNorth:
		{
			if(AmountNorth>0)
			{
				Resource::Arraycarnorth[AmountNorth-1].sprite.setPosition(395,0);
				AmountNorth--;
			}
			break;
		}
		case GameSimulation::TambahSouth:
		{
			if(AmountSouth<11)
				AmountSouth++;
			break;
		}
		case GameSimulation::KurangSouth:
		{
			if(AmountSouth>0)
			{
				Resource::Arraycarsouth[AmountSouth-1].sprite.setPosition(355,600);
				AmountSouth--;
			}
			break;
		}
		case GameSimulation::TambahWest:
		{
			if(AmountWest < 11)
				AmountWest++;
			break;
		}
		case GameSimulation::KurangWest:
		{
			if(AmountWest > 0)
			{
				Resource::Arraycarwest[AmountWest-1].sprite.setPosition(0,255);
				AmountWest--;
			}
			break;
		}
		case GameSimulation::TambahEast:
		{
			if(AmountEast < 11)
				AmountEast++;
			break;
		}
		case GameSimulation::KurangEast:
		{
			if(AmountEast > 0)
			{
				Resource::Arraycareast[AmountEast-1].sprite.setPosition(800,295);
				AmountEast--;
			}
			break;
		}
	}
}

void GameSimulation::MoveHuman(sf::RenderWindow& GameWindow, Waktu CounterTime)
{
	if(Resource::humansouth.getPosition().x <= 475 && CounterTime.GetWaktu() - DummyTimeCounter >= 3)
	{
		Resource::humannorth.move(-0.5,0);
		Resource::humansouth.move(0.5,0);
		GameWindow.draw(Resource::humannorth);
		GameWindow.draw(Resource::humansouth);
	}
	else
	{
		Resource::humannorth.setPosition(425,220);
		Resource::humansouth.setPosition(350,330);
	}
}

void GameSimulation::MoveCarNorth(sf::RenderWindow& GameWindow, int i)
{
	bool IsIntersectZero = AmountNorth > 1 && i == 0 && Resource::Arraycarnorth[i].rect.intersects(Resource::Arraycarnorth[AmountNorth-1].rect);
	bool IsIntersectNotZero = i > 0 && (Resource::Arraycarnorth[i].rect.intersects(Resource::Arraycarnorth[i-1].rect));
	bool IsIntersectInitZero = i == 0 && AmountNorth == 2;
	bool IsOutSquareAndRed = IsInSquare(Resource::Arraycarnorth[i].rect) && !Resource::Arraycarnorth[i].IsMoveInSquare && (GameSimulationState != GameSimulation::HMHMM && GameSimulationState != GameSimulation::HKHMM);
	bool IsInSquareAndRed = IsInSquare(Resource::Arraycarnorth[i].rect)  && (GameSimulationState == GameSimulation::HMHMM || GameSimulationState == GameSimulation::HKHMM);
	bool IsOutSquareAndNotRed = !IsInSquare(Resource::Arraycarnorth[i].rect) && (GameSimulationState != GameSimulation::HMHMM || GameSimulationState != GameSimulation::HKHMM);


	if(IsIntersectNotZero && !IsIntersectInitZero)
	{
		Resource::Arraycarnorth[i].sprite.move(0,0);
		GameWindow.draw(Resource::Arraycarnorth[i].sprite);
	} 
	else if (IsIntersectZero && !IsIntersectInitZero)
	{	
		Resource::Arraycarnorth[i].sprite.move(0,0);
		GameWindow.draw(Resource::Arraycarnorth[i].sprite);
	} 
	else if(IsOutSquareAndRed)
	{
		Resource::Arraycarnorth[i].sprite.move(0,0);
		GameWindow.draw(Resource::Arraycarnorth[i].sprite);
	}
	else if(IsInSquareAndRed)
	{
		Resource::Arraycarnorth[i].IsMoveInSquare = true;
		Resource::Arraycarnorth[i].sprite.move(0,1);
		if(Resource::Arraycarnorth[i].sprite.getPosition().y+Resource::Arraycarnorth[i].sprite.getGlobalBounds().height >= 650)
		{
			Resource::Arraycarnorth[i].sprite.setPosition(395,0);
		}
		GameWindow.draw(Resource::Arraycarnorth[i].sprite);
	}
	else if(IsOutSquareAndNotRed)
	{
		Resource::Arraycarnorth[i].IsMoveInSquare = false;
		Resource::Arraycarnorth[i].sprite.move(0,1);
		if(Resource::Arraycarnorth[i].sprite.getPosition().y+Resource::Arraycarnorth[i].sprite.getGlobalBounds().height >= 650)
		{
			Resource::Arraycarnorth[i].sprite.setPosition(395,0);
		}
		GameWindow.draw(Resource::Arraycarnorth[i].sprite);
	}
	else
	{
		Resource::Arraycarnorth[i].sprite.move(0,1);
		if(Resource::Arraycarnorth[i].sprite.getPosition().y+Resource::Arraycarnorth[i].sprite.getGlobalBounds().height >= 650)
		{
			Resource::Arraycarnorth[i].sprite.setPosition(395,0);
		}
		GameWindow.draw(Resource::Arraycarnorth[i].sprite);
	}
}

void GameSimulation::MoveCarSouth(sf::RenderWindow& GameWindow, int i)
{
	bool IsIntersectZero = AmountSouth > 1 && i == 0 && Resource::Arraycarsouth[i].rect.intersects(Resource::Arraycarsouth[AmountSouth-1].rect);
	bool IsIntersectNotZero = i != 0 && Resource::Arraycarsouth[i].rect.intersects(Resource::Arraycarsouth[i-1].rect);
	bool IsIntersectInitZero = i == 0 && AmountSouth == 2;
	bool IsOutSquareAndRed = IsInSquare(Resource::Arraycarsouth[i].rect) && !Resource::Arraycarsouth[i].IsMoveInSquare && (GameSimulationState != GameSimulation::HMHMM && GameSimulationState != GameSimulation::HKHMM);
	bool IsInSquareAndRed = IsInSquare(Resource::Arraycarsouth[i].rect) && (GameSimulationState == GameSimulation::HMHMM || GameSimulationState == GameSimulation::HKHMM);
	bool IsOutSquareAndNotRed = !IsInSquare(Resource::Arraycarsouth[i].rect) && (GameSimulationState != GameSimulation::HMHMM || GameSimulationState != GameSimulation::HKHMM);
	
	if(IsIntersectNotZero && !IsIntersectInitZero)
	{
		Resource::Arraycarsouth[i].sprite.move(0,0);
		GameWindow.draw(Resource::Arraycarsouth[i].sprite);
	}
	else if (IsIntersectZero && !IsIntersectInitZero)
	{
		Resource::Arraycarsouth[i].sprite.move(0,0);
		GameWindow.draw(Resource::Arraycarsouth[i].sprite);
	} 
	else if(IsOutSquareAndRed)
	{
		Resource::Arraycarsouth[i].sprite.move(0,0);
		GameWindow.draw(Resource::Arraycarsouth[i].sprite);
	}
	else if(IsInSquareAndRed)
	{
		Resource::Arraycarsouth[i].IsMoveInSquare = true;
		Resource::Arraycarsouth[i].sprite.move(0,-1);
		if(Resource::Arraycarsouth[i].sprite.getPosition().y+Resource::Arraycarsouth[i].sprite.getGlobalBounds().height <= -50)
		{
			Resource::Arraycarsouth[i].sprite.setPosition(355,600);
		}
		GameWindow.draw(Resource::Arraycarsouth[i].sprite);
	}
	else if(IsOutSquareAndNotRed)
	{
		Resource::Arraycarsouth[i].IsMoveInSquare = false;
		Resource::Arraycarsouth[i].sprite.move(0,-1);
		if(Resource::Arraycarsouth[i].sprite.getPosition().y+Resource::Arraycarsouth[i].sprite.getGlobalBounds().height <= -50)
		{
			Resource::Arraycarsouth[i].sprite.setPosition(355,600);
		}
		GameWindow.draw(Resource::Arraycarsouth[i].sprite);
	}
	else
	{
		Resource::Arraycarsouth[i].sprite.move(0,-1);
		if(Resource::Arraycarsouth[i].sprite.getPosition().y+Resource::Arraycarsouth[i].sprite.getGlobalBounds().height <= -50)
		{
			Resource::Arraycarsouth[i].sprite.setPosition(355,600);
		}
		GameWindow.draw(Resource::Arraycarsouth[i].sprite);
	}
}

void GameSimulation::MoveCarWest(sf::RenderWindow& GameWindow, int i)
{
	bool IsIntersectZero = AmountWest > 1 && i == 0 && Resource::Arraycarwest[i].rect.intersects(Resource::Arraycarwest[AmountWest-1].rect);
	bool IsIntersectNotZero = i != 0 && Resource::Arraycarwest[i].rect.intersects(Resource::Arraycarwest[i-1].rect);
	bool IsIntersectInitZero = i == 0 && AmountWest == 2;
	bool IsOutSquareAndRed = IsInSquare(Resource::Arraycarwest[i].rect) && !Resource::Arraycarwest[i].IsMoveInSquare && (GameSimulationState != GameSimulation::MHMHM && GameSimulationState != KHKHM);
	bool IsInSquareAndRed = IsInSquare(Resource::Arraycarwest[i].rect) && (GameSimulationState == GameSimulation::MHMHM || GameSimulationState == KHKHM);
	bool IsOutSquareAndNotRed = !IsInSquare(Resource::Arraycarwest[i].rect) && (GameSimulationState != GameSimulation::MHMHM || GameSimulationState != KHKHM);

	if(IsIntersectNotZero && !IsIntersectInitZero)
	{
		Resource::Arraycarwest[i].sprite.move(0,0);
		GameWindow.draw(Resource::Arraycarwest[i].sprite);
	}
	else if (IsIntersectZero && !IsIntersectInitZero)
	{
		Resource::Arraycarwest[i].sprite.move(0,0);
		GameWindow.draw(Resource::Arraycarwest[i].sprite);
	} 
	else if(IsOutSquareAndRed)
	{
		Resource::Arraycarwest[i].sprite.move(0,0);
		GameWindow.draw(Resource::Arraycarwest[i].sprite);
	}
	else if(IsInSquareAndRed)
	{
		Resource::Arraycarwest[i].IsMoveInSquare = true;
		Resource::Arraycarwest[i].sprite.move(1,0);
		if(Resource::Arraycarwest[i].sprite.getPosition().x+Resource::Arraycarwest[i].sprite.getGlobalBounds().width >= 850)
		{
			Resource::Arraycarwest[i].sprite.setPosition(0,255);
		}
		GameWindow.draw(Resource::Arraycarwest[i].sprite);
	}
	else if(IsOutSquareAndNotRed)
	{
		Resource::Arraycarwest[i].IsMoveInSquare = false;
		Resource::Arraycarwest[i].sprite.move(1,0);
		if(Resource::Arraycarwest[i].sprite.getPosition().x+Resource::Arraycarwest[i].sprite.getGlobalBounds().width >= 850)
		{
			Resource::Arraycarwest[i].sprite.setPosition(0,255);
		}
		GameWindow.draw(Resource::Arraycarwest[i].sprite);
	}
	else
	{
		Resource::Arraycarwest[i].sprite.move(1,0);
		if(Resource::Arraycarwest[i].sprite.getPosition().x+Resource::Arraycarwest[i].sprite.getGlobalBounds().width >= 850)
		{
			Resource::Arraycarwest[i].sprite.setPosition(0,255);
		}
		GameWindow.draw(Resource::Arraycarwest[i].sprite);
	}
}

void GameSimulation::MoveCarEast(sf::RenderWindow& GameWindow,int i)
{
	bool IsIntersectZero = AmountEast > 1 && i == 0 && Resource::Arraycareast[i].rect.intersects(Resource::Arraycareast[AmountEast-1].rect);
	bool IsIntersectNotZero = i != 0 && Resource::Arraycareast[i].rect.intersects(Resource::Arraycareast[i-1].rect);
	bool IsIntersectInitZero = i == 0 && AmountEast == 2;
	bool IsOutSquareAndRed = IsInSquare(Resource::Arraycareast[i].rect) && !Resource::Arraycareast[i].IsMoveInSquare && (GameSimulationState != GameSimulation::MHMHM && GameSimulationState != MHMKH  && GameSimulationState != MHMMH && GameSimulationState != KHKHM && GameSimulationState != MHMKM);
	bool IsInSquareAndRed = IsInSquare(Resource::Arraycareast[i].rect) && (GameSimulationState == GameSimulation::MHMHM || GameSimulationState == MHMKH || GameSimulationState == MHMMH  || GameSimulationState == KHKHM || GameSimulationState == MHMKM);
	bool IsOutSquareAndNotRed = !IsInSquare(Resource::Arraycareast[i].rect) && (GameSimulationState != GameSimulation::MHMHM || GameSimulationState != MHMKH || GameSimulationState != MHMMH  || GameSimulationState != KHKHM || GameSimulationState != MHMKM);

	if(IsIntersectNotZero && !IsIntersectInitZero)
	{
		Resource::Arraycareast[i].sprite.move(0,0);
		GameWindow.draw(Resource::Arraycareast[i].sprite);
	}
	else if (IsIntersectZero && !IsIntersectInitZero)
	{
		Resource::Arraycareast[i].sprite.move(0,0);
		GameWindow.draw(Resource::Arraycareast[i].sprite);
	} 
	else if(IsOutSquareAndRed)
	{
		Resource::Arraycareast[i].sprite.move(0,0);
		GameWindow.draw(Resource::Arraycareast[i].sprite);
	}
	else if(IsInSquareAndRed)
	{
		Resource::Arraycareast[i].IsMoveInSquare = true;
		Resource::Arraycareast[i].sprite.move(-1,0);
		if(Resource::Arraycareast[i].sprite.getPosition().x+Resource::Arraycareast[i].sprite.getGlobalBounds().width <= -50)
		{
			Resource::Arraycareast[i].sprite.setPosition(800,295);
		}
		GameWindow.draw(Resource::Arraycareast[i].sprite);
	}
	else if(IsOutSquareAndNotRed)
	{
		Resource::Arraycareast[i].IsMoveInSquare = false;
		Resource::Arraycareast[i].sprite.move(-1,0);
		if(Resource::Arraycareast[i].sprite.getPosition().x+Resource::Arraycareast[i].sprite.getGlobalBounds().width <= -50)
		{
			Resource::Arraycareast[i].sprite.setPosition(800,295);
		}
		GameWindow.draw(Resource::Arraycareast[i].sprite);
	}
	else
	{
		Resource::Arraycareast[i].sprite.move(-1,0);
		if(Resource::Arraycareast[i].sprite.getPosition().x+Resource::Arraycareast[i].sprite.getGlobalBounds().width <= -50)
		{
			Resource::Arraycareast[i].sprite.setPosition(800,295);
		}
		GameWindow.draw(Resource::Arraycareast[i].sprite);
	}
}

void GameSimulation::MoveCarEastNorth(sf::RenderWindow& GameWindow, int i)
{
	bool IsIntersectZero = AmountEast > 1 && i == 0 && Resource::Arraycareast[i].rect.intersects(Resource::Arraycareast[AmountEast-1].rect);
	bool IsIntersectNotZero = i > 1 && (Resource::Arraycareast[i].rect.intersects(Resource::Arraycareast[i-1].rect)|| Resource::Arraycareast[i].rect.intersects(Resource::Arraycareast[i-2].rect) || Resource::Arraycareast[i].rect.intersects(Resource::Arraycareast[i-3].rect));
	bool IsOutSquareAndRed = IsInSquare(Resource::Arraycareast[i].rect) && Resource::Arraycareast[i].IsMoveInSquare && (GameSimulationState != MHMKH  && GameSimulationState != MHMMH);
	bool IsInSquareAndRed = IsInSquare(Resource::Arraycareast[i].rect) && (GameSimulationState == MHMKH  && GameSimulationState == MHMMH);
	bool IsOutSquareAndNotRed = !IsInSquare(Resource::Arraycareast[i].rect) && (GameSimulationState != MHMKH  && GameSimulationState != MHMMH);
	bool IsRightRed = GameSimulationState == GameSimulation::MHMHM || GameSimulationState == GameSimulation::MHMKM || GameSimulationState == GameSimulation::KHKHM || GameSimulationState == GameSimulation::KMKMM;
	if(IsIntersectNotZero)
	{
		Resource::Arraycareast[i].sprite.move(0,0);
		GameWindow.draw(Resource::Arraycareast[i].sprite);
	}
	else if (IsIntersectZero)
	{
		Resource::Arraycareast[i].sprite.move(0,0);
		GameWindow.draw(Resource::Arraycareast[i].sprite);
	} 
	else if(IsOutSquareAndRed)
	{
		if(IsRightRed) MoveCarEast(GameWindow,i);
		else
		{
			Resource::Arraycareast[i].sprite.move(0,0);
			GameWindow.draw(Resource::Arraycareast[i].sprite);
		}
	}
	else if(IsInSquareAndRed)
	{
		if(IsRightRed && !Resource::Arraycareast[i].IsMoveToNorth) MoveCarEast(GameWindow,i);
		else
		{
			Resource::Arraycareast[i].IsMoveInSquare = true;
			if(Resource::Arraycareast[i].sprite.getPosition().x+Resource::Arraycareast[i].sprite.getGlobalBounds().width <= 450)
			{
				if(!Resource::Arraycareast[i].IsRotate)
				{
					Resource::Arraycareast[i].IsRotate = true;
					Resource::Arraycareast[i].sprite.rotate(90);
					Resource::Arraycareast[i].IsMoveToNorth = true;
				}
				Resource::Arraycareast[i].sprite.move(0,-1);
				if(Resource::Arraycareast[i].sprite.getPosition().y+Resource::Arraycareast[i].sprite.getGlobalBounds().width <= -50)
				{
					Resource::Arraycareast[i].sprite.rotate(270);
					Resource::Arraycareast[i].sprite.setPosition(800,295);
					Resource::Arraycareast[i].IsRotate = false;
					Resource::Arraycareast[i].IsMoveToNorth = false;
				}
			}
			else
			{
				Resource::Arraycareast[i].sprite.move(-1,0);
			}
		GameWindow.draw(Resource::Arraycareast[i].sprite);
		}
	}
	else if(IsOutSquareAndNotRed)
	{
		Resource::Arraycareast[i].IsMoveInSquare = false;
		if(IsRightRed && !Resource::Arraycareast[i].IsMoveToNorth) MoveCarEast(GameWindow,i);
		else
		{
			if(Resource::Arraycareast[i].sprite.getPosition().x+Resource::Arraycareast[i].sprite.getGlobalBounds().width <= 450)
			{
				if(!Resource::Arraycareast[i].IsRotate)
				{
					Resource::Arraycareast[i].IsRotate = true;
					Resource::Arraycareast[i].sprite.rotate(90);
					Resource::Arraycareast[i].IsMoveToNorth = true;
				}
				Resource::Arraycareast[i].sprite.move(0,-1);
				if(Resource::Arraycareast[i].sprite.getPosition().y+Resource::Arraycareast[i].sprite.getGlobalBounds().width <= -50)
				{
					Resource::Arraycareast[i].sprite.rotate(270);
					Resource::Arraycareast[i].sprite.setPosition(800,295);
					Resource::Arraycareast[i].IsRotate = false;
					Resource::Arraycareast[i].IsMoveToNorth = false;
				}
			}
			else
			{
				Resource::Arraycareast[i].sprite.move(-1,0);
			}
		GameWindow.draw(Resource::Arraycareast[i].sprite);
		}
	}
	else
	{
		if(IsRightRed && !Resource::Arraycareast[i].IsMoveToNorth) MoveCarEast(GameWindow,i);
		else
		{
			if(Resource::Arraycareast[i].sprite.getPosition().x+Resource::Arraycareast[i].sprite.getGlobalBounds().width <= 450)
			{
				if(!Resource::Arraycareast[i].IsRotate)
				{
					Resource::Arraycareast[i].IsRotate = true;
					Resource::Arraycareast[i].sprite.rotate(90);
					Resource::Arraycareast[i].IsMoveToNorth = true;
				}
				Resource::Arraycareast[i].sprite.move(0,-1);
				if(Resource::Arraycareast[i].sprite.getPosition().y+Resource::Arraycareast[i].sprite.getGlobalBounds().width <= -50)
				{
					Resource::Arraycareast[i].sprite.rotate(270);
					Resource::Arraycareast[i].sprite.setPosition(800,295);
					Resource::Arraycareast[i].IsRotate = false;
					Resource::Arraycareast[i].IsMoveToNorth = false;
				}
			}
			else
			{
				Resource::Arraycareast[i].sprite.move(-1,0);
			}
		GameWindow.draw(Resource::Arraycareast[i].sprite);
		}
	}
}

void GameSimulation::CarRectHandler()
{
	int i = 0;
	for(i=0; i<=10;i++)
	{
		Resource::Arraycarnorth[i].rect.height = (int)Resource::Arraycarnorth[i].sprite.getGlobalBounds().height;
		Resource::Arraycarnorth[i].rect.width = (int)Resource::Arraycarnorth[i].sprite.getGlobalBounds().width;
		Resource::Arraycarnorth[i].rect.left = (int)Resource::Arraycarnorth[i].sprite.getGlobalBounds().left;
		Resource::Arraycarnorth[i].rect.top = (int)Resource::Arraycarnorth[i].sprite.getGlobalBounds().top;
	}
	for(i=0; i<=10;i++)
	{
		Resource::Arraycarsouth[i].rect.height = (int)Resource::Arraycarsouth[i].sprite.getGlobalBounds().height;
		Resource::Arraycarsouth[i].rect.width = (int)Resource::Arraycarsouth[i].sprite.getGlobalBounds().width;
		Resource::Arraycarsouth[i].rect.left = (int)Resource::Arraycarsouth[i].sprite.getGlobalBounds().left;
		Resource::Arraycarsouth[i].rect.top = (int)Resource::Arraycarsouth[i].sprite.getGlobalBounds().top;
	}
	for(i=0; i<=10;i++)
	{
		Resource::Arraycarwest[i].rect.height = (int)Resource::Arraycarwest[i].sprite.getGlobalBounds().height;
		Resource::Arraycarwest[i].rect.width = (int)Resource::Arraycarwest[i].sprite.getGlobalBounds().width;
		Resource::Arraycarwest[i].rect.left = (int)Resource::Arraycarwest[i].sprite.getGlobalBounds().left;
		Resource::Arraycarwest[i].rect.top = (int)Resource::Arraycarwest[i].sprite.getGlobalBounds().top;
	}
	for(i=0; i<=10;i++)
	{
		Resource::Arraycareast[i].rect.height = (int)Resource::Arraycareast[i].sprite.getGlobalBounds().height;
		Resource::Arraycareast[i].rect.width = (int)Resource::Arraycareast[i].sprite.getGlobalBounds().width;
		Resource::Arraycareast[i].rect.left = (int)Resource::Arraycareast[i].sprite.getGlobalBounds().left;
		Resource::Arraycareast[i].rect.top = (int)Resource::Arraycareast[i].sprite.getGlobalBounds().top;
	}
}

bool GameSimulation::IsInSquare(sf::IntRect x)
{
	sf::Vector2i position;
	sf::Vector2i size;
	position.x = 334;
	position.y = 232;
	size.x = 135;
	size.y = 135;
	sf::IntRect TrafficRect(position,size);
	if(TrafficRect.intersects(x))
		return true;
	else return false;
}

void GameSimulation::StateInput(std::string input, std::vector<std::string> final)
{
	FinalState = final;
	if(input.compare("KMKMM") == 0)
	{
		GameSimulationState = GameSimulation::KMKMM;
	}
	else if(input.compare("HMHMM") == 0)
	{
		GameSimulationState = GameSimulation::HMHMM;
	}
	else if(input.compare("MMMMM") == 0)
	{
		GameSimulationState = GameSimulation::MMMMM;
	}
	else if(input.compare("HKHMM") == 0)
	{
		GameSimulationState = GameSimulation::HKHMM;
	}
	else if(input.compare("MKMMM") == 0)
	{
		GameSimulationState = GameSimulation::MKMMM;
	}
	else if(input.compare("MHMMH") == 0)
	{
		GameSimulationState = GameSimulation::MHMMH;
	}
	else if(input.compare("MHMKH") == 0)
	{
		GameSimulationState = GameSimulation::MHMKH;
	}
	else if(input.compare("MHMKM") == 0)
	{
		GameSimulationState = GameSimulation::MHMKM;
	}
	else if(input.compare("MHMHM") == 0)
	{
		GameSimulationState = GameSimulation::MHMHM;
	}
	else if(input.compare("KHKHM") == 0)
	{
		GameSimulationState = GameSimulation::KHKHM;
	}
	else
	{
		std::cout<<"File Input Salah!" << std::endl;
		assert(false);
	}
}

bool GameSimulation::CheckFinalState()
{
	int i;
	if((int)FinalState.size() == 0) 
	{
		std::cout<<"File Input Salah!"<<std::endl;
		assert(false);
	}
	for(i=0;i<(int)FinalState.size();i++)
	{
		if(FinalState[i].compare("KMKMM") == 0 && GameSimulationState == GameSimulation::KMKMM)
		{
			return true;
		}
		else if(FinalState[i].compare("HMHMM") == 0 && GameSimulationState == GameSimulation::HMHMM)
		{
			return true;
		}
		else if(FinalState[i].compare("MMMMM") == 0 && GameSimulationState == GameSimulation::MMMMM)
		{
			return true;
		}
		else if(FinalState[i].compare("HKHMM") == 0 && GameSimulationState == GameSimulation::HKHMM)
		{
			return true;
		}
		else if(FinalState[i].compare("MKMMM") == 0 && GameSimulationState == GameSimulation::MKMMM)
		{
			return true;
		}
		else if(FinalState[i].compare("MHMMH") == 0 && GameSimulationState == GameSimulation::MHMMH)
		{
			return true;
		}
		else if(FinalState[i].compare("MHMKH") == 0 && GameSimulationState == GameSimulation::MHMKH)
		{
			 return true;
		}
		else if(FinalState[i].compare("MHMKM") == 0 && GameSimulationState == GameSimulation::MHMKM)
		{
			return true;
		}
		else if(FinalState[i].compare("MHMHM") == 0 && GameSimulationState == GameSimulation::MHMHM)
		{
			return true;
		}
		else if(FinalState[i].compare("KHKHM") == 0 && GameSimulationState == GameSimulation::KHKHM)
		{
			return true;
		}
	}
	return false;
}