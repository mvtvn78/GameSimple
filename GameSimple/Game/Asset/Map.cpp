#include"Map.h"
#include"../Game.h"
#include<fstream>
#include"../../ECS/ECS.h"
#include"../../Component/Components.h"
#include"../../Game/HandleMap.h"

extern Manager manager;
extern HandleMap* ManagerMap;
Map::Map(std::string tI, int ms, int ts) : texID(tI), mapScale(ms), tileSize(ts)
{
	IDMAP = 0;
}
Map::~Map()
{
	
}
void Map::LoadMap(std::string path, int sizeX, int sizeY)
{
	
	bool Success = ManagerMap->addMapIntoList(path);
	if (Success)
	{
		char c;
		std::fstream mapFile;
		mapFile.open(path);
		int srcX, scrY;
		scrY = 0;
		for (int y = 0; y < sizeY; y++)
		{
			for (int x = 0; x < sizeX; x++)
			{
				mapFile.get(c);
				int Irow = atoi(&c);
				// Add collider for map 
				if (Irow == 2 || Irow == 9)
				{
					auto& tcol(manager.addEntity());
					tcol.addComponent<ColliderComponent>("terrain", x * (tileSize * mapScale), y * (tileSize * mapScale), tileSize * mapScale);
					std::size_t getCl = getCollidersMAP(path);
					if (getCl == Game::groupUnknow)
						return;
					tcol.addGroup(getCl);
				}

				--Irow;
				if (Irow != -1)
				{
					srcX = Irow * tileSize;
					AddTitle(path,srcX, scrY, x * tileSize * mapScale, y * tileSize * mapScale);
				}
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
}

void Map::AddTitle(std::string path,int srcX, int srcY, int xpos, int ypos)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, tileSize, mapScale, texID);
	std::size_t getID = getIDMAP(path);
	if (getID == Game::groupUnknow)
		return;
	IDMAP = getID;
	tile.addGroup(getID);
}

std::size_t Map::getIDMAP(std::string path)
{
	return path == map1 ? Game::groupMap1 : path == map2 ? Game::groupMap2 : path == map3 ? Game::groupMap3 : Game::groupUnknow;
}

std::size_t Map::getCollidersMAP(std::string path)
{
	return path == map1 ? Game::groupMapColliders1 : path == map2 ? Game::groupMapColliders2 : path == map3 ? Game::groupMapColliders3 : Game::groupUnknow;
}

std::size_t Map::getIDMAPCurrent()
{
	return IDMAP;
}

std::size_t Map::getColMapCurrentByID()
{
	return IDMAP == Game::groupMap1 ? Game::groupMapColliders1 : IDMAP == Game::groupMap2 ? Game::groupMapColliders2 : IDMAP == Game::groupMap3 ? Game::groupMapColliders3 : Game::groupUnknow;
}

void Map::DrawTile()
{
	auto& tiles = manager.getEntityByGroup(getIDMAPCurrent());
	for (auto& tl : tiles)
	{
		tl->draw();
	}
}

void Map::DestroyTile()
{
	std::size_t getID = getIDMAPCurrent();
	auto& deletedGroup = manager.getEntityByGroup(getID);
	for (auto& dl : deletedGroup)
	{
		dl->delGroup(Game::groupMapColliders1);
	}
}

void Map::Close()
{
	std::size_t getID = getIDMAPCurrent();
	auto& deletedGroupTile = manager.getEntityByGroup(getID);
	auto& deletedGroupCol = manager.getEntityByGroup(getColMapCurrentByID());
	for (auto& dl : deletedGroupTile)
	{
		dl->destroy();
	}
	for (auto& cl : deletedGroupTile)
	{
		cl->destroy();
	}
}

void Map::DrawColliders()
{
	auto& collider = manager.getEntityByGroup(getColMapCurrentByID());
	for (auto& cl : collider)
	{
		cl ->draw();
	}
}
