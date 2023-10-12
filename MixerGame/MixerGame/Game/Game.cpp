#include"Game.h"
#include<iostream>
#include"../Asset/AssetManager.h"
SDL_Renderer* Game::windowRender = NULL;
SDL_Event Game::events;

const int WIDTHSCREEN = 800;
const int HEIGHTSCREEN = 640;
SDL_RendererFlip FlipNone = SDL_FLIP_NONE;
SDL_RendererFlip FlipHorizontal = SDL_FLIP_HORIZONTAL;

Manager manager;
AssetManager* Game::asset = new AssetManager(&manager);
auto& player(manager.addEntity());
auto& enemy(manager.addEntity());

//Map* map;
bool Game::isRunning()
{
	return this->running;
}
void Game::frame()
{
	// declare FPS
	const int FPS = 60;
	// Frame Delay
	const int frameDelay = 1000 / FPS;
	Uint32 frameStart;
	int frametime;
	// Take miliseconds since SDL library intialization
	frameStart = SDL_GetTicks();
	// Take frametime current
	frametime = SDL_GetTicks() - frameStart;
	if (frameDelay > frametime)
	{
		SDL_Delay(frameDelay - frametime);
	}
}
Game::Game()
{
	window = NULL;
	running = true;
}

Game::~Game()
{

}
void Game::init(const char* title, int width, int heigh, bool isFullscreen)
{
	int fullscreen = SDL_WINDOW_SHOWN;
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		running = false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			std::cout << ("Warning: Linear texture filtering not enabled!");
		}
		if (isFullscreen == 1)
		{
			fullscreen = SDL_WINDOW_FULLSCREEN;
		}
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, heigh, fullscreen);
		if (window == NULL)
		{
			running = false;
		}
		else
		{
			windowRender = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (windowRender == NULL)
			{
				running = false;
			}
			else
			{
				SDL_SetRenderDrawColor(windowRender, 255, 255, 255, 255);
			}
		}
		/*asset->AddTexture("terran", "terrain_ss.png");
		asset->AddTexture("player", "player_idle.png");
		asset->AddTexture("enemy", "enemy.png");*/
		/*map = new Map("terran", 2, 32);
		map->LoadMap("map.map", 25, 20);*/
	}
}

void  Game::handleEvent()
{
	SDL_PollEvent(&events);
	if (events.type == SDL_QUIT)
	{
		running = false;
	}
}
void  Game::Update()
{
	manager.refresh();
	manager.managerUPDATE();

}
void  Game::Render()
{
	SDL_RenderClear(windowRender);
	manager.managerDRAW();
	SDL_RenderPresent(windowRender);
}
void  Game::close()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(windowRender);
	IMG_Quit();
	SDL_Quit();
}