#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
class AssetManager;
class Game
{
private:
	SDL_Window* window;
	bool running;
public:
	static SDL_Renderer* windowRender;
	static SDL_Event events;
	static AssetManager* asset;
	enum Grouplabel :std::size_t
	{
		groupMap,
		groupPlayers,
		groupEnemies,
		groupColliders,
	};
	Game();
	~Game();
	void init(const char* title, int width, int heigh, bool isFullscreen);
	void handleEvent();
	void Update();
	void Render();
	void close();
	bool isRunning();
	void frame();
	void GameRun();
};