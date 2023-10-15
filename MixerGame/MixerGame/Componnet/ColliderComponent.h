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
	void init() override
	{
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponet<TransformComponent>();
		srcR = { 0,0,32,32 };
		destR = { collider.x,collider.y,collider.w,collider.h };
	}

	void drawComponnet()
	{
		///*TextureManager::Draw(tex, srcR, destR, SDL_FLIP_NONE);*/
	}
	void updateComponnet() override
	{
		if (tag != "terrain")
		{
			collider.x = static_cast<int>(transform->position.x);
			collider.y = static_cast<int>(transform->position.y);
			collider.w = transform->width * transform->scale;
			collider.h = transform->height * transform->scale;
		}
		destR.x = collider.x - Game::camera.x;
		destR.y = collider.y - Game::camera.y;
	}
};