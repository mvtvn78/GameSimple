#include"./Game/main.h"
int main(int args, char* argv[])
{
	Game* game = new Game();
	game->init("Mvt", WIDTHSCREEN, HEIGHTSCREEN, 0);
	while (game->isRunning())
	{
		game->handleEvent();
		game->Update();
		game->Render();
		game->frame();
	}
	game->close();
	return 0;
}