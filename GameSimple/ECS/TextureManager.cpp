#include"../Game/Game.h"
#include"TextureManager.h"
SDL_Texture* TextureManager::loadTexture(const char* fileName)
{

	SDL_Surface* tmp = IMG_Load(fileName);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::windowRender, tmp);
	SDL_FreeSurface(tmp);
	if (tex == NULL)
		std::cout << "NOT FOUND Path " << fileName << std::endl;
	return tex;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(Game::windowRender, tex, &src, &dest, NULL, NULL, flip);
}