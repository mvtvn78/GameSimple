#pragma once
#include"../Game/Game.h"
#include"../ECS/ECS.h"
#include"TransformComponent.h"
#include"SpriteComponent.h"
#include"Audio.h"
class KeyboardController :public Component
{
public:
	Audio *audio;
	SDL_KeyCode keyCurrent= SDLK_UNKNOWN;
	TransformComponent* transform;
	bool isJump=true;
	int mapCurrent = 0;
	//Animation
	SpriteComponent* sprite;
	~KeyboardController() override
	{
		audio->CloseMusic();
	}
	void init() override
	{
		transform = &entity->getComponet<TransformComponent>();
		sprite = &entity->getComponet<SpriteComponent>();
		audio = new Audio();
		if (!audio->LoadFullSound())
		{
			std::cout << "FAILED LOAD FULL SOUND" << std::endl;
		}
	}
	bool handleJumpShenRon()
	{
		bool cl = transform->position.y >= 1115;	
		if (cl)
		{
			transform->position.y = 1115;
			if (keyCurrent == SDLK_UP)
			{
				sprite->Play("Idle");

				keyCurrent = SDLK_UNKNOWN;
			}
		}
		return cl;
	}
	bool handleJumpMAP1()
	{
		bool cl = transform->position.y >= 1025;
		if (cl)
		{
			transform->position.y = 1025;
			if (keyCurrent == SDLK_UP)
			{
				sprite->Play("Idle");

				keyCurrent = SDLK_UNKNOWN;
			}
		}
		return cl;
	}
	bool handleJumpMAP2()
	{
		bool cl =  transform->position.y >= 710;
		if (cl)
		{
			transform->position.y = 710;
			if (keyCurrent == SDLK_UP )
			{
				sprite->Play("Idle");

				keyCurrent = SDLK_UNKNOWN;
			}
		}
		return cl;
	}
	bool handleJumpMAP3()
	{ 
		bool xposFl = transform->position.x >= 240;
		bool xpos = transform->position.x <= 230;
		bool cl = transform->position.y >= 770;
		bool ypos = transform->position.y >= 770 + 64;
		if (cl&&xpos)
		{
			transform->position.y = 770;
			if (keyCurrent == SDLK_UP )
			{
				sprite->Play("Idle");
				keyCurrent = SDLK_UNKNOWN;
			}
		}
		if (ypos&& xposFl)
		{
			transform->position.y = 770 + 64;
			if (keyCurrent == SDLK_UP)
			{
				sprite->Play("Idle");

				keyCurrent = SDLK_UNKNOWN;
			}
		}
		return cl && xpos || ypos&& xposFl;
	}
	
	void SetMapCurrent(int _z)
	{
		mapCurrent = _z;
		audio->StopAFreeMsBg();
		audio->LoadMusic(audio->getStrByID(_z));
		audio->PlayAndPauseMsBg();
	}
	
	void HandleKeyPress()
	{
		if (mapCurrent == 1)
			isJump = handleJumpMAP1();
		else if (mapCurrent ==2)
			 isJump = handleJumpMAP2();
		else if (mapCurrent == 3)
			isJump = handleJumpMAP3();
		else if (mapCurrent == 4)
			isJump = handleJumpShenRon();
		if (Game::events.type == SDL_KEYDOWN)
		{
			switch (Game::events.key.keysym.sym)
			{
			
			case SDLK_UP:
				if (isJump)
				{
					transform->velocity.y = -10;
					sprite->Play("JumpBegin");
					isJump = false;
					audio->PlaySound(Audio::Jump);
				}
				break;
			case SDLK_LEFT:
				
				if (isJump)
				{
					sprite->Play("Walk");
					if (Game::events.key.repeat == 0)
					{
						if (mapCurrent == 4)
							audio->PlaySound(Audio::WalkMapShenRon);

						audio->PlaySound(Audio::PlayerWalk);
					}
				}
				
				transform->velocity.x = -1;
				sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
				break;
			case SDLK_RIGHT:
				if (isJump)
				{
					sprite->Play("Walk");
					if (Game::events.key.repeat == 0)
					{
						if (mapCurrent == 4)
							audio->PlaySound(Audio::WalkMapShenRon);

						audio->PlaySound(Audio::PlayerWalk);
					}
				}
				transform->velocity.x = 1;
				sprite->spriteFlip = SDL_FLIP_NONE;
				break;
			
			default:
				break;
			}
		}
		if (isJump)
		{
			transform->velocity.y = 0;
			if (mapCurrent == 4)
				audio->PlaySound(Audio::ShenRonEF);
		}
		if (Game::events.type == SDL_KEYUP)
		{
			switch (Game::events.key.keysym.sym)
			{
			
			case SDLK_UP:
				if (!isJump)
				{
					transform->velocity.y = 3;
					sprite->Play("JumpEnd");
				}
				keyCurrent = SDLK_UP;
				break;
			case SDLK_LEFT:
				transform->velocity.x = 0;
				if (isJump)
					sprite->Play("Idle");
				if (!keyCurrent == SDLK_UP)
					keyCurrent = SDLK_LEFT;
				break;
			case SDLK_RIGHT:
				transform->velocity.x = 0;
				if (isJump)
					sprite->Play("Idle");
				if (!keyCurrent == SDLK_UP)
					keyCurrent = SDLK_RIGHT;
				break;
			
			default:
				break;
			}

			

		}
	}
	void updateComponnet() override
	{
		HandleKeyPress();
	}
};
