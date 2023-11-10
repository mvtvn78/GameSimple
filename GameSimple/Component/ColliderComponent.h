#pragma once
#include"SDL.h"
#include"..//ECS/ECS.h"
#include<string>
#include"TransformComponent.h"
#include "../Game/Game.h"
#include"..//ECS/TextureManager.h"
class ColliderComponent :public Component
{
public:
	SDL_Rect collider;
	std::string tag;
	SDL_Texture* tex;
	SDL_Rect srcR, destR;
	TransformComponent* transform;
	int width=0;
	int height=0;
	bool Active= true;
	void setAtiveTrue()
	{
		Active = true;
	}
	void setAtiveFalse()
	{
		Active = false;
	}
	ColliderComponent(std::string t)
	{
		tag = t;
	}
	ColliderComponent(std::string t, int xpos, int ypos, int size)
	{
		tag = t;
		collider.x = xpos;
		collider.y = ypos;
		collider.h = collider.w = size;
	}
	ColliderComponent(std::string t, int xpos, int ypos, int width,int height)
	{
		tag = t;
		collider.x = xpos;
		collider.y = ypos;
		collider.w = width;
		collider.h = height;
	}
	void setWH(int _w,int _h)
	{
		width = _w;
		height = _h;
	}
	
	void init() override
	{
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponet<TransformComponent>();
		srcR = { 0,0,64,64 };
		destR = { collider.x,collider.y,collider.w,collider.h };
		tex = TextureManager::loadTexture("F:\\Working\\GIT\\MixerGame\\MixerGame\\MixerGame\\Game\\Asset\\Element\\ColliderBug.png");
	}

	void drawComponnet()
	{
		if(Active)
			TextureManager::Draw(tex, srcR, destR, SDL_FLIP_NONE);
	}
	void updateComponnet() override
	{
		if (Active)
		{
			if (tag != "terrain")
			{
				if (tag == "player")
				{
					collider.x = static_cast<int>(transform->position.x) + 10;
					collider.y = static_cast<int>(transform->position.y) + 10;
				}
				else
				{
					collider.x = static_cast<int>(transform->position.x);
					collider.y = static_cast<int>(transform->position.y);
				}
				if (width == 0 && height == 0)
				{
					collider.w = transform->width * transform->scale;
					collider.h = transform->height * transform->scale;
				}
				else
				{
					collider.w = width;
					collider.h = height;
				}

			}
			destR.x = collider.x - Game::camera.x;
			destR.y = collider.y - Game::camera.y;
		}
		else
		{
			collider.x =collider.y = collider.w =collider.h= -100;
		}
	}
};