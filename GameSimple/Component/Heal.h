#pragma once
const int MAXHP = 460;
class HealPlayer
{
public:
	int HPPlayer;
	HealPlayer()
	{
		 HPPlayer= MAXHP;

	}
	
	bool isHPDead()
	{
		return HPPlayer <= 0;
	}
	bool isAlive()
	{
		return HPPlayer > 0;
	}
	
};