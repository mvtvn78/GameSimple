#pragma once
#include"../ECS/ECS.h"
#include"TransformComponent.h"
#include"SpriteComponent.h"
#include<SDL.h>
#include"../Game/Asset/AssetManager.h"
class TileComponent : public Component
{
public:
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	Vector2D position;
	TileComponent() = default;
	~TileComponent()
	{
		SDL_DestroyTexture(texture);
	}
	TileComponent(int srcX, int srcY, int xpos, int ypos, int _size, int _scale, std::string id)
	{
		texture = Game::asset->GetTexture(id);
		srcRect.x = srcX;
		srcRect.y = srcY;

		position.x = xpos;
		position.y = ypos;

		srcRect.w = srcRect.h = _size;

		destRect.x = xpos;
		destRect.y = ypos;

		destRect.w = destRect.h = _size * _scale;
	}
	void updateComponnet() override
	{
		destRect.x = position.x - Game::camera.x;
		destRect.y = position.y - Game::camera.y;
	}
	void drawComponnet() override
	{
		TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
	}
};