#pragma once
#include<cstring>
#include<cstdlib>
#include<ctime>
#include"../ECS/Vector2D.h"
class HandleMap
{
private:
	int MapHandle[7];
	int indx;
public:
	//Path Map
	std::string map1 = "F:\\Working\\GIT\\MixerGame\\MixerGame\\MixerGame\\Game\\Asset\\map\\map1.map";
	std::string map2 = "F:\\Working\\GIT\\MixerGame\\MixerGame\\MixerGame\\Game\\Asset\\map\\map2.map";
	std::string map3 = "F:\\Working\\GIT\\MixerGame\\MixerGame\\MixerGame\\Game\\Asset\\map\\map3.map";
	//Map Constain
	const Vector2D MAP1XY = Vector2D(0, 1025);
	const Vector2D MAP2XY = Vector2D(0, 710);
	const Vector2D MAP3XY = Vector2D(0, 770);
	HandleMap()
	{
		indx = -1;
		memset(MapHandle, 0, sizeof(MapHandle));
	}
	bool MapisFull()
	{
		return indx > 6;
	}
	Vector2D getPositionCurrent()
	{
		int ID = getCurrentMap();
		return (ID == 1) ? MAP1XY : (ID == 2) ? MAP2XY : (ID == 3) ? MAP3XY : Vector2D(-1, -1);
	}
	bool addMapIntoList(std::string map)
	{
		int _x = 0;
		if (map == map1)
			_x = 1;
		else if (map == map2)
			_x = 2;
		else if (map == map3)
			_x = 3;
		++indx;
		if (indx == 7)
			return false;
		MapHandle[indx] = _x;
		return true;
	}
	std::string getStringMapByIndx(int _i)
	{
		return (_i == 1) ? map1 : (_i == 2) ? map2 : (_i == 3) ? map3 : "";
	}
	int GetRanDomMapExcept()
	{
		int MapIdCurrent = getCurrentMap();
		if (MapIdCurrent != 0)
		{
			int i = 1, j = 3;
			srand(time(NULL));
			int indx = MapIdCurrent;
			while (indx == MapIdCurrent)
			{
				indx = rand() % (j - i + 1) + i;
			}
			return indx;
		}
		return -1;
	}
	int getAmountOfMap()
	{
		return indx;
	}
	int getCurrentMap()
	{
		return MapHandle[indx];
	}
	
};