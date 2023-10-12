#pragma once
#include<map>
#include<string>
#include"../ECS/TextureManager.h"
#include"../ECS/Vector2D.h"
#include"../ECS/ECS.h"
class AssetManager
{
public:
	AssetManager(Manager* man);
	~AssetManager();
	void AddTexture(std::string id, const char* path);
	SDL_Texture* GetTexture(std::string id);
private:
	Manager* manager;
	std::map<std::string, SDL_Texture*> textures;
};
