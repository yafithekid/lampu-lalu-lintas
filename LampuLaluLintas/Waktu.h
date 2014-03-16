#pragma once

class Waktu
{
public:
	Waktu();
	~Waktu();
	void SetWaktu(int Waktu);
	int GetWaktu();
	static float GetCurrentTime();
	static void Begin();
	void BeginNS();
	void ResetNS(int time);
private:
	int waktu;
	static sf::Clock Elapsed;
	sf::Clock ElapsedNS;
};