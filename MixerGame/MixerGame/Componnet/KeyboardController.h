#pragma once
#include"../Game/Game.h"
#include"../ECS/ECS.h"
#include"TransformComponent.h"
#include"SpriteComponent.h"

class KeyboardController :public Component
{
public:
	TransformComponent* transform;
	//Animation
	SpriteComponent* sprite;
	void init() override
	{
		transform = &entity->getComponet<TransformComponent>();
		sprite = &entity->getComponet<SpriteComponent>();
	}
	void updateComponnet() override
	{
		
			if (Game::events.type == SDL_KEYDOWN)
			{
				switch (Game::events.key.keysym.sym)
				{
				case SDLK_UP:
					transform->velocity.y = -1;
					/*sprite->Play("Walk");*/
					break;
				case SDLK_LEFT:
					transform->velocity.x = -1;
					/*sprite->Play("Walk");*/
					sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
					break;
				case SDLK_DOWN:
					transform->velocity.y = 1;
					/*sprite->Play("Walk");*/
					break;
				case SDLK_RIGHT:
					transform->velocity.x = 1;
					sprite->spriteFlip = SDL_FLIP_NONE;
					/*	sprite->Play("Walk");*/
					break;
				default:
					break;
				}
			}
			if (Game::events.type == SDL_KEYUP)
			{
				switch (Game::events.key.keysym.sym)
				{
				case SDLK_UP:
					transform->velocity.y = 0;
					/*sprite->Play("Idle");*/
					break;
				case SDLK_LEFT:
					transform->velocity.x = 0;
				/*	sprite->Play("Idle");*/
					/*sprite->spriteFlip = SDL_FLIP_NONE;*/
					break;
				case SDLK_DOWN:
					transform->velocity.y = 0;
					/*sprite->Play("Idle");*/
					break;
				case SDLK_RIGHT:
					transform->velocity.x = 0;
					/*sprite->Play("Idle");*/
					break;
				default:
					break;
				}
			}
		
	}
};