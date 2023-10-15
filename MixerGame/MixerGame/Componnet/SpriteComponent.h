#pragma once
#include<SDL.h>
#include "..//ECS/TextureManager.h"
#include"..//ECS/ECS.h"
#include "TransformComponent.h"
#include"Animation.h"
#include"../Asset/AssetManager.h"
#include<map>
#include"../Game/Game.h"
class SpriteComponent : public Component
{
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	bool animated = false;
	int frames = 0;
	int speed = 100;
public:
	int animIndex = 0;
	std::map<const char*, Animation> animations;
	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	SpriteComponent() = default;
	SpriteComponent(std::string id)
	{
		setText(id);
	}
	SpriteComponent(std::string id, bool isAnimated)
	{
		animated = isAnimated;
		Animation idle = Animation(0, 10, 100);
		animations.emplace("Idle", idle);
		Play("Idle");
		setText(id);
	}
	~SpriteComponent()
	{
		SDL_DestroyTexture(texture);
	}
	void setText(std::string  path)
	{
		texture = Game::asset->GetTexture(path);
	}
	void init() override
	{
		transform = &entity->getComponet<TransformComponent>(); // lấy địa chỉ 
		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;
	}
	void updateComponnet() override
	{
		if (animated)
		{
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}
		srcRect.y = animIndex * transform->height;
		destRect.x = static_cast<int>(transform->position.x) - Game::camera.x;
		destRect.y = static_cast<int>(transform->position.y) - Game::camera.y;
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->width * transform->scale;
	}
	void drawComponnet() override
	{
		TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
	}
	void Play(const char* animName)
	{
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;
	}
};