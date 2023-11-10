#pragma once

#include "../ECS/ECS.h"
#include "../Game/Asset/AssetManager.h"
#include "../Game/Game.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class UILabel : public Component
{
public:
	UILabel(int xpos, int ypos, std::string text, std::string font, SDL_Color& colour) :
		labelText(text), labelFont(font), textColour(colour)
	{
		position.x = xpos;
		position.y = ypos;

		SetLabelText(labelText, labelFont);
	}
	~UILabel()
	{}

	void SetLabelText(std::string text, std::string font)
	{
		SDL_Surface* surf = TTF_RenderText_Blended(Game::asset->GetFont(font), text.c_str(), textColour);
		labelTexture = SDL_CreateTextureFromSurface(Game::windowRender, surf);
		SDL_FreeSurface(surf);

		SDL_QueryTexture(labelTexture, nullptr, nullptr, &position.w, &position.h);
	}

	void drawComponnet() override
	{
		SDL_RenderCopy(Game::windowRender, labelTexture, nullptr, &position);
	}

private:
	SDL_Rect position;
	std::string labelText;
	std::string labelFont;
	SDL_Color textColour;
	SDL_Texture* labelTexture;
};
