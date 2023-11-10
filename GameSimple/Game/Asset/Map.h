#pragma once
#include<string>
class Map
{
public:
	std::string map1 = "F:\\Working\\GIT\\MixerGame\\MixerGame\\MixerGame\\Game\\Asset\\map\\map1.map";
	std::string map2 = "F:\\Working\\GIT\\MixerGame\\MixerGame\\MixerGame\\Game\\Asset\\map\\map2.map";
	std::string map3 = "F:\\Working\\GIT\\MixerGame\\MixerGame\\MixerGame\\Game\\Asset\\map\\map3.map";
	Map(std::string tI, int ms, int ts);
	~Map();
	void LoadMap(std::string path, int sizeX, int sizeY);
	void AddTitle(std::string path,int srcX, int srcY, int xpos, int ypos);
	std::size_t getIDMAP(std::string path);
	std::size_t getCollidersMAP(std::string path);
	std::size_t getIDMAPCurrent();
	std::size_t getColMapCurrentByID();
	void DrawTile();
	void DestroyTile();
	void Close();
	void DrawColliders();
private:
	std::size_t IDMAP;
	std::string texID;
	int mapScale;
	int tileSize;
};