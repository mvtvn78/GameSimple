#pragma once
#include<SDL.h>
#include "..//ECS/TextureManager.h"
#include"..//ECS/ECS.h"
#include "TransformComponent.h"
#include"Animation.h"
#include"../Game/Asset/AssetManager.h"
#include<map>
#include"../Game/Game.h"
class SpriteComponent : public Component
{
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	bool animated = false;
	int frames = 1;
	int speed = 100;
	bool render = true;
public:
	int animIndex = 0;
	std::map<const char*, Animation> animations;
	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	bool SPRITEFLIPRIGHT()
	{
		return spriteFlip == SDL_FLIP_NONE;
	}
	void resetRender()
	{
		render = true;
	}
	void RenderFalse()
	{
		render = false;
	}
	bool SPRITEFLIPLEFT()
	{
		return spriteFlip == SDL_FLIP_HORIZONTAL;
	}
	SpriteComponent() = default;
	SpriteComponent(std::string id)
	{
		setText(id);
	}
	SpriteComponent( bool isAn)
	{
		animated = isAn;
	}
	~SpriteComponent()
	{
		SDL_DestroyTexture(texture);
	}
	
	void setAnimation(bool value)
	{
		animated = value;
	}
	void setFrameAttack(std::string id, int frame, int speed)
	{
		Animation Attack = Animation(id, frame, speed);
		animations.emplace("Attack", Attack);
	}
	void setFrameDead(std::string id, int frame, int speed)
	{
		Animation Dead = Animation(id, frame, speed);
		animations.emplace("Dead", Dead);
	}
	void setFrameIdle(std::string id, int frame, int speed)
	{
		Animation idle = Animation(id, frame, speed);
		animations.emplace("Idle", idle);
		Play("Idle");
	}
	void setFrameJumpBegin(std::string id, int frame, int speed)
	{
		Animation jump = Animation(id, frame, speed);
		animations.emplace("JumpBegin", jump);
	}
	void setFrameJumpEnd(std::string id, int frame, int speed)
	{
		Animation jump = Animation(id, frame, speed);
		animations.emplace("JumpEnd", jump);
	}
	void setFramePlayerMap(std::string id, int frame, int speed)
	{
		Animation ChangeMap = Animation(id, frame, speed);
		animations.emplace("ChangeMap", ChangeMap);
	}
	void SetFrameBeAttack(std::string id, int frame, int speed)
	{
		Animation beAttack = Animation(id, frame, speed);
		animations.emplace("beAttack", beAttack);
	}
	void setFrameWalk(std::string id, int frame, int speed)
	{
		Animation walk = Animation(id, frame, speed);
		animations.emplace("Walk", walk);
	}
	std::string getIdAni(const char* animName)
	{
		return animations[animName].id;
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
	void setIDAni(const char* animName,std::string _id)
	{
		animations[animName].id = _id;
		setText(_id);
	}
	void setFrameAni(const char* animName, int _frames)
	{
		animations[animName].frames = _frames;
	}
	void setSpeedAni(const char* animName, int _speed)
	{
		animations[animName].speed = _speed;
	}
	void Play(const char* animName)
	{
		setText(animations[animName].id);
		frames = animations[animName].frames;
		speed = animations[animName].speed;
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
		if(render)
			TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
	}
};