#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
#include <SDL_thread.h>
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
	static SDL_Rect camera;
	enum Grouplabel :std::size_t
	{
		groupUnknow,
		groupMap1,
		groupMap2,
		groupMap3,
		groupPlayers,
		groupEnemies,
		groupMapColliders1,
		groupMapColliders2,
		groupMapColliders3,
		groupMapEnemy1,
		groupMapEnemy2,
		groupMapEnemy3,
		groupDead,

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