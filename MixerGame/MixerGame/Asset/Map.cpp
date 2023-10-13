#include"Map.h"
#include"../Game/Game.h"
#include<fstream>
#include"../ECS/ECS.h"
#include"../Componnet/Components.h"
extern Manager manager;

Map::Map(std::string tI, int ms, int ts) : texID(tI), mapScale(ms), tileSize(ts)
{

}
Map::~Map()
{
}
void Map::LoadMap(std::string path, int sizeX, int sizeY)
{
	char c;
	std::fstream mapFile;
	mapFile.open(path);
	int srcX, scrY;
	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			scrY = 0;
			mapFile.get(c);
			int Irow = atoi(&c);
			Irow--;
			srcX =  Irow* tileSize;
			AddTitle(srcX, scrY, x * tileSize * mapScale, y * tileSize * mapScale);
			mapFile.ignore();
		}
	}
	/*mapFile.ignore();*/
	/*for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(c);
			if (c == '1')
			{
				auto& tcol(manager.addEntity());
				tcol.addComponent<ColliderComponent>("terrain", x * (tileSize * mapScale), y * (tileSize * mapScale), tileSize * mapScale);
				tcol.addGroup(Game::groupMapColliders);
			}
			mapFile.ignore();
		}
	}*/
	mapFile.close();
}

void Map::AddTitle(int srcX, int srcY, int xpos, int ypos)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, tileSize, mapScale, texID);
	tile.addGroup(Game::groupMap);
}