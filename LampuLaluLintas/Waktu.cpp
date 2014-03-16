#include "stdafx.h"
#include "Waktu.h"

sf::Clock Waktu::Elapsed;

Waktu::Waktu(){}

Waktu::~Waktu(){}

void Waktu::SetWaktu(int Waktu)
{
	this->waktu = Waktu;
}

int Waktu::GetWaktu()
{
	sf::Time Tempo;
	Tempo = ElapsedNS.getElapsedTime();
	waktu = Tempo.asSeconds();
	return waktu;
}

float Waktu::GetCurrentTime()
{
	sf::Time Tempo;
	Tempo = Elapsed.getElapsedTime();
	return Tempo.asSeconds();
}

void Waktu::Begin()
{
	Elapsed.restart();
}

void Waktu::BeginNS()
{
	ElapsedNS.restart();
	waktu = 0;
}

void Waktu::ResetNS(int time)
{
	if(GetWaktu() >= time) ElapsedNS.restart();
}