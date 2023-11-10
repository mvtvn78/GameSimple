#include"Variables.h"
#include <sstream>
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
bool onground = false;
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
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0"))
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
			windowRender = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |SDL_RENDERER_PRESENTVSYNC);
			if (windowRender == NULL)
			{
				running = false;
			}
			else
			{
				SDL_SetRenderDrawColor(windowRender, 255, 255, 255, 255);
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					running = false;
				}
				if (TTF_Init() == -1)
				{
					std::cout << "Error : SDL_TTF" << std::endl;
					running = false;
				}
			}
		}
		GameRun();
	}
}
void Game::GameRun()
{
	//Enemy
	asset->AddTexture("Enemy1_Idle", "F:\\Working\\GIT\\MixerGame\\MixerGame\\MixerGame\\Game\\Asset\\Element\\enemy1_idle.png");
	asset->AddTexture("Enemy1_Attack", "F:\\Working\\GIT\\MixerGame\\MixerGame\\MixerGame\\Game\\Asset\\Element\\enemy1_attack.png");
	asset->AddTexture("Enemy1_Walk", "F:\\Working\\GIT\\MixerGame\\MixerGame\\MixerGame\\Game\\Asset\\Element\\enemy1_walk.png");
	
	asset->AddTexture("Enemy2_Idle", "F:\\Working\\GIT\\MixerGame\\MixerGame\\MixerGame\\Game\\Asset\\Element\\wolf2_idle.png");
	asset->AddTexture("Enemy2_Attack", "F:\\Working\\GIT\\MixerGame\\MixerGame\\MixerGame\\Game\\Asset\\Element\\wolf2_attack.png");
	asset->AddTexture("Enemy2_Walk", "F:\\Working\\GIT\\MixerGame\\MixerGame\\MixerGame\\Game\\Asset\\Element\\wolf2_walk.png");

	asset->AddTexture("Enemy3_Idle-red", "F:\\Working\\GIT\\MixerGame\\MixerGame\\MixerGame\\Game\\Asset\\Element\\wolf3_idle-red.png");
	asset->AddTexture("Enemy3_Attack-red", "F:\\Working\\GIT\\MixerGame\\MixerGame\\MixerGame\\Game\\Asset\\Element\\wolf3_attack-red.png");
	asset->AddTexture("Enemy3_Walk-red", "F:\\Working\\GIT\\MixerGame\\MixerGame\\MixerGame\\Game\\Asset\\Element\\wolf3_walk-red.png");
	 heal = new HealPlayer();

	//Initialize MAP
	ManagerMap = new HandleMap();
	//Font
	asset->AddFont("Arial", "F:\\Working\\GIT\\MixerGame\\MixerGame\\MixerGame\\Game\\Asset\\font\\arial.ttf", 16);
	asset->AddFont("GameTTF", "F:\\Working\\GIT\\MixerGame\\MixerGame\\MixerGame\\Game\\Asset\\font\\game.ttf",16);
	//ASSET MAP
	asset->AddTexture("tileset", "F:\\Working\\GIT\\MixerGame\\MixerGame\\MixerGame\\Game\\Asset\\map\\tileset.png");
	asset->AddTexture("background", "F:\\Working\\GIT\\MixerGame\\MixerGame\\MixerGame\\Game\\Asset\\map\\bg.png");
	asset->AddTexture("backgroundSHENROn", "F:\\Working\\GIT\\MixerGame\\MixerGame\\MixerGame\\Game\\Asset\\map\\bggoirong.png");
	asset->AddTexture("envir", "F:\\Working\\GIT\\MixerGame\\MixerGame\\MixerGame\\Game\\Asset\\map\\light-sheet.png");
	//ASSET ELEMENT
	asset->AddTexture("player", "F:\\Working\\GIT\\MixerGame\\MixerGame\\MixerGame\\Game\\Asset\\Element\\player32x32-ngoiyen.png");
	asset->AddTexture("playerAttack", "F:\\Working\\GIT\\MixerGame\\MixerGame\\MixerGame\\Game\\Asset\\Element\\player32x32-attackpng.png");
	asset->AddTexture("playerJump", "F:\\Working\\GIT\\MixerGame\\MixerGame\\MixerGame\\Game\\Asset\\Element\\player32x32-jump.png");
	asset->AddTexture("AnimJumpBegin","F:\\Working\\GIT\\MixerGame\\MixerGame\\MixerGame\\Game\\Asset\\Element\\jump_air.png");
	asset->AddTexture("AnimJumpEnd", "F:\\Working\\GIT\\MixerGame\\MixerGame\\MixerGame\\Game\\Asset\\Element\\jump_end.png");
	asset->AddTexture("playerKame", "F:\\Working\\GIT\\MixerGame\\MixerGame\\MixerGame\\Game\\Asset\\Element\\player32x32-kame.png");
	asset->AddTexture("playerWalk", "F:\\Working\\GIT\\MixerGame\\MixerGame\\MixerGame\\Game\\Asset\\Element\\player32x32-walk.png");
	asset->AddTexture("AnimplayerMap", "F:\\Working\\GIT\\MixerGame\\MixerGame\\MixerGame\\Game\\Asset\\Element\\player-changemap.png");
	asset->AddTexture("AnimAttack", "F:\\Working\\GIT\\MixerGame\\MixerGame\\MixerGame\\Game\\Asset\\Element\\animation_attack.png");
	asset->AddTexture("playerAnimBeAttack", "F:\\Working\\GIT\\MixerGame\\MixerGame\\MixerGame\\Game\\Asset\\Element\\playerAnimBeAttack.png");
	asset->AddTexture("markques", "F:\\Working\\GIT\\MixerGame\\MixerGame\\MixerGame\\Game\\Asset\\map\\markquestion.png");
	asset->AddTexture("playerDead", "F:\\Working\\GIT\\MixerGame\\MixerGame\\MixerGame\\Game\\Asset\\Element\\player_dead.png");


	asset->AddTexture("godNamek", "F:\\Working\\GIT\\MixerGame\\MixerGame\\MixerGame\\Game\\Asset\\Element\\thuongde.png");
	asset->AddTexture("shenron", "F:\\Working\\GIT\\MixerGame\\MixerGame\\MixerGame\\Game\\Asset\\Element\\rongthan.png");
	asset->AddTexture("7ball", "F:\\Working\\GIT\\MixerGame\\MixerGame\\MixerGame\\Game\\Asset\\Element\\7ball.png");
	asset->AddTexture("Anim7ball", "F:\\Working\\GIT\\MixerGame\\MixerGame\\MixerGame\\Game\\Asset\\Element\\7ballanimation.png");
	asset->AddTexture("AnimKame", "F:\\Working\\GIT\\MixerGame\\MixerGame\\MixerGame\\Game\\Asset\\Element\\animation_kame.png");
	asset->AddTexture("Kame", "F:\\Working\\GIT\\MixerGame\\MixerGame\\MixerGame\\Game\\Asset\\Element\\kame1.png");
	asset->AddTexture("chuongkhi", "F:\\Working\\GIT\\MixerGame\\MixerGame\\MixerGame\\Game\\Asset\\Element\\chuongkhi.png");
	asset->AddTexture("message", "F:\\Working\\GIT\\MixerGame\\MixerGame\\MixerGame\\Game\\Asset\\Element\\message.png");
	asset->AddTexture("HeadUpPlayer", "F:\\Working\\GIT\\MixerGame\\MixerGame\\MixerGame\\Game\\Asset\\Element\\HeadUpPlayer.png");
	asset->AddTexture("HeadUpEnemy", "F:\\Working\\GIT\\MixerGame\\MixerGame\\MixerGame\\Game\\Asset\\Element\\HeadUpEnemy.png");

	//MAP
	map = new Map("tileset", 1, 64);
	map->LoadMap(map3, 25, 20);
	//BACKGROUND and enviroment
	bg.addComponent<TransformComponent>(0, 0, VIEWWIDTH, VIEWHEIGHT, 1);
	bg.addComponent<SpriteComponent>().setText("background");
	er.addComponent<TransformComponent>(0, 0, VIEWWIDTH, VIEWHEIGHT, 1);
	er.addComponent<SpriteComponent>().setText("envir");
	//Player
	player.addComponent<TransformComponent>(0, 0, WIDTHPLAYER,HEIGHTPLAYER, SCALEPLAYER);
	player.getComponet<TransformComponent>().setPosition(ManagerMap->getPositionCurrent());
	player.getComponet<TransformComponent>().setSpeed(SpeedPlayer);
	player.addComponent<SpriteComponent>(true);
	player.getComponet<SpriteComponent>().setFrameWalk("playerWalk", 4, Speed100);
	player.getComponet<SpriteComponent>().setFrameJumpBegin("AnimJumpBegin", 3, 1);
	player.getComponet<SpriteComponent>().setFrameJumpEnd("AnimJumpEnd", 1, 50);
	player.getComponet<SpriteComponent>().setFrameIdle("player", 2, Speed100);
	player.getComponet<SpriteComponent>().setFramePlayerMap("AnimplayerMap",3,Speed100);
	player.getComponet<SpriteComponent>().SetFrameBeAttack("playerAnimBeAttack", 5, Speed100);
	player.getComponet<SpriteComponent>().setFrameDead("playerDead", 10, Speed100);

	player.addComponent<KeyboardController>();
	player.getComponet<KeyboardController>().SetMapCurrent(ManagerMap->getCurrentMap());
	player.addComponent<ColliderComponent>("player", ManagerMap->getPositionCurrent().x, ManagerMap->getPositionCurrent().y, XYPLAYERCOLLIDER, XYPLAYERCOLLIDER);
	player.getComponet<ColliderComponent>().setWH(XYPLAYERCOLLIDER, XYPLAYERCOLLIDER);
	//Label
	SDL_Color Red = { 255,0,0,255 };
	SDL_Color Blue = { 0, 0, 255,255 };
	label.addComponent<UILabel>(10, 10, "teststring", "GameTTF", Blue);
	Message.addComponent<UILabel>(400, 10, "Mvt", "GameTTF", Red);
	//Enemy Map1
	enemy1Map1.addComponent<TransformComponent>(0, 0, DIMENSION64, DIMENSION64, 2);
	enemy1Map1.getComponet<TransformComponent>().setPosition(EnemyX1, EnemyY1);
	enemy1Map1.getComponet<TransformComponent>().setSpeed(SpeedPlayer);
	enemy1Map1.addComponent<SpriteComponent>(true);
	enemy1Map1.getComponet<SpriteComponent>().setFrameAttack("Enemy1_Attack", 5, Speed100);
	enemy1Map1.getComponet<SpriteComponent>().setFrameIdle("Enemy1_Idle", 2, Speed100);
	enemy1Map1.addGroup(Game::groupMapEnemy1);
	enemy1Map1.addComponent<ColliderComponent>("Enemy1Map1", EnemyX1, EnemyY1, DIMENSION64 * 2, DIMENSION64 * 2);

	enemy2Map1.addComponent<TransformComponent>(0, 0, DIMENSION64, DIMENSION64, 2);
	enemy2Map1.getComponet<TransformComponent>().setPosition(EnemyX1+300*1, EnemyY1);
	enemy2Map1.getComponet<TransformComponent>().setSpeed(SpeedPlayer);
	enemy2Map1.addComponent<SpriteComponent>(true);
	enemy2Map1.getComponet<SpriteComponent>().setFrameAttack("Enemy1_Attack", 5, Speed100);
	enemy2Map1.getComponet<SpriteComponent>().setFrameIdle("Enemy1_Idle", 2, Speed100);
	enemy2Map1.addGroup(Game::groupMapEnemy1);
	enemy2Map1.addComponent<ColliderComponent>("Enemy2Map1", EnemyX1 + 300 *1, EnemyY1, DIMENSION64 * 2, DIMENSION64 * 2);

	enemy3Map1.addComponent<TransformComponent>(0, 0, DIMENSION64, DIMENSION64, 2);
	enemy3Map1.getComponet<TransformComponent>().setPosition(EnemyX1 + 300 * 2, EnemyY1);
	enemy3Map1.getComponet<TransformComponent>().setSpeed(SpeedPlayer);
	enemy3Map1.addComponent<SpriteComponent>(true);
	enemy3Map1.getComponet<SpriteComponent>().setFrameAttack("Enemy1_Attack", 5, Speed100);
	enemy3Map1.getComponet<SpriteComponent>().setFrameIdle("Enemy1_Idle", 2, Speed100);
	enemy3Map1.addGroup(Game::groupMapEnemy1);
	enemy3Map1.addComponent<ColliderComponent>("Enemy3Map1", EnemyX1 + 300 * 2, EnemyY1, DIMENSION64 * 2, DIMENSION64 * 2);

	enemy4Map1.addComponent<TransformComponent>(0, 0, DIMENSION64, DIMENSION64, 2);
	enemy4Map1.getComponet<TransformComponent>().setPosition(EnemyX1 + 300 * 3, EnemyY1);
	enemy4Map1.getComponet<TransformComponent>().setSpeed(SpeedPlayer);
	enemy4Map1.addComponent<SpriteComponent>(true);
	enemy4Map1.getComponet<SpriteComponent>().setFrameAttack("Enemy1_Attack", 5, Speed100);
	enemy4Map1.getComponet<SpriteComponent>().setFrameIdle("Enemy1_Idle", 2, Speed100);
	enemy4Map1.addGroup(Game::groupMapEnemy1);
	enemy4Map1.addComponent<ColliderComponent>("Enemy4Map1", EnemyX1 + 300 * 3, EnemyY1, DIMENSION64 * 2, DIMENSION64 * 2);
	//Enemy Map 2
	enemy1Map2.addComponent<TransformComponent>(0, 0, DIMENSION64, HEIGHTENEYMY, 1);
	enemy1Map2.getComponet<TransformComponent>().setPosition(EnemyX2, EnemyY2);
	enemy1Map2.getComponet<TransformComponent>().setSpeed(SpeedPlayer);
	enemy1Map2.addComponent<SpriteComponent>(true);
	enemy1Map2.getComponet<SpriteComponent>().setFrameAttack("Enemy2_Attack", 5, Speed100);
	enemy1Map2.getComponet<SpriteComponent>().setFrameIdle("Enemy2_Idle", 4, Speed100);
	enemy1Map2.addGroup(Game::groupMapEnemy2);
	enemy1Map2.addComponent<ColliderComponent>("Enemy1Map2", EnemyX2, EnemyY2, DIMENSION64 * 1, HEIGHTENEYMY * 1);
	
	enemy2Map2.addComponent<TransformComponent>(0, 0, DIMENSION64, HEIGHTENEYMY, 1);
	enemy2Map2.getComponet<TransformComponent>().setPosition(EnemyX2+300, EnemyY2);
	enemy2Map2.getComponet<TransformComponent>().setSpeed(SpeedPlayer);
	enemy2Map2.addComponent<SpriteComponent>(true);
	enemy2Map2.getComponet<SpriteComponent>().setFrameAttack("Enemy2_Attack", 5, Speed100);
	enemy2Map2.getComponet<SpriteComponent>().setFrameIdle("Enemy2_Idle", 4, Speed100);
	enemy2Map2.addGroup(Game::groupMapEnemy2);
	enemy2Map2.addComponent<ColliderComponent>("Enemy2Map2", EnemyX2 + 300, EnemyY2, DIMENSION64 * 1, HEIGHTENEYMY * 1);

	enemy3Map2.addComponent<TransformComponent>();
	enemy3Map2.addComponent<TransformComponent>(0, 0, DIMENSION64, HEIGHTENEYMY, 1);
	enemy3Map2.getComponet<TransformComponent>().setPosition(EnemyX2 + 300 * 2, EnemyY2);
	enemy3Map2.getComponet<TransformComponent>().setSpeed(SpeedPlayer);
	enemy3Map2.addComponent<SpriteComponent>(true);
	enemy3Map2.getComponet<SpriteComponent>().setFrameAttack("Enemy2_Attack", 5, Speed100);
	enemy3Map2.getComponet<SpriteComponent>().setFrameIdle("Enemy2_Idle", 4, Speed100);
	enemy3Map2.addGroup(Game::groupMapEnemy2);
	enemy3Map2.addComponent<ColliderComponent>("Enemy3Map2", EnemyX2 + 300 * 2, EnemyY2, DIMENSION64 * 1, HEIGHTENEYMY * 1);

	enemy4Map2.addComponent<TransformComponent>();
	enemy4Map2.addComponent<TransformComponent>(0, 0, DIMENSION64, HEIGHTENEYMY, 1);
	enemy4Map2.getComponet<TransformComponent>().setPosition(EnemyX2 + 300 * 3, EnemyY2);
	enemy4Map2.getComponet<TransformComponent>().setSpeed(SpeedPlayer);
	enemy4Map2.addComponent<SpriteComponent>(true);
	enemy4Map2.getComponet<SpriteComponent>().setFrameAttack("Enemy2_Attack", 5, Speed100);
	enemy4Map2.getComponet<SpriteComponent>().setFrameIdle("Enemy2_Idle", 4, Speed100);
	enemy4Map2.addGroup(Game::groupMapEnemy2);
	enemy4Map2.addComponent<ColliderComponent>("Enemy4Map2", EnemyX2 + 300 * 3, EnemyY2, DIMENSION64 * 1, HEIGHTENEYMY * 1);

	//Enemy Map 3
	enemy1Map3.addComponent<TransformComponent>(0, 0, DIMENSION64, HEIGHTENEYMY, 1);
	enemy1Map3.getComponet<TransformComponent>().setPosition(EnemyX3, EnemyY3);
	enemy1Map3.getComponet<TransformComponent>().setSpeed(SpeedPlayer);
	enemy1Map3.addComponent<SpriteComponent>(true);
	enemy1Map3.getComponet<SpriteComponent>().setFrameAttack("Enemy3_Attack-red", 5, Speed100);
	enemy1Map3.getComponet<SpriteComponent>().setFrameIdle("Enemy3_Idle-red",4, Speed100);
	enemy1Map3.addGroup(Game::groupMapEnemy3);
	enemy1Map3.addComponent<ColliderComponent>("Enemy1Map3", EnemyX3, EnemyY3, DIMENSION64 * 1, HEIGHTENEYMY * 1);

	enemy2Map3.addComponent<TransformComponent>(0, 0, DIMENSION64, HEIGHTENEYMY, 1);
	enemy2Map3.getComponet<TransformComponent>().setPosition(EnemyX3 +300, EnemyY3);
	enemy2Map3.getComponet<TransformComponent>().setSpeed(SpeedPlayer);
	enemy2Map3.addComponent<SpriteComponent>(true);
	enemy2Map3.getComponet<SpriteComponent>().setFrameAttack("Enemy3_Attack-red", 5, Speed100);
	enemy2Map3.getComponet<SpriteComponent>().setFrameIdle("Enemy3_Idle-red", 4, Speed100);
	enemy2Map3.addGroup(Game::groupMapEnemy3);
	enemy2Map3.addComponent<ColliderComponent>("Enemy2Map3", EnemyX3 + 300, EnemyY3, DIMENSION64 * 1, HEIGHTENEYMY * 1);

	enemy3Map3.addComponent<TransformComponent>(0, 0, DIMENSION64, HEIGHTENEYMY, 1);
	enemy3Map3.getComponet<TransformComponent>().setPosition(EnemyX3 +300*2, EnemyY3);
	enemy3Map3.getComponet<TransformComponent>().setSpeed(SpeedPlayer);
	enemy3Map3.addComponent<SpriteComponent>(true);
	enemy3Map3.getComponet<SpriteComponent>().setFrameAttack("Enemy3_Attack-red", 5, Speed100);
	enemy3Map3.getComponet<SpriteComponent>().setFrameIdle("Enemy3_Idle-red", 4, Speed100);
	enemy3Map3.addGroup(Game::groupMapEnemy3);
	enemy3Map3.addComponent<ColliderComponent>("Enemy3Map3", EnemyX3 + 300 * 2, EnemyY3, DIMENSION64 * 1, HEIGHTENEYMY * 1);

	enemy4Map3.addComponent<TransformComponent>(0, 0, DIMENSION64, HEIGHTENEYMY, 1);
	enemy4Map3.getComponet<TransformComponent>().setPosition(EnemyX3 +300*3, EnemyY3);
	enemy4Map3.getComponet<TransformComponent>().setSpeed(SpeedPlayer);
	enemy4Map3.addComponent<SpriteComponent>(true);
	enemy4Map3.getComponet<SpriteComponent>().setFrameAttack("Enemy3_Attack-red", 5, Speed100);
	enemy4Map3.getComponet<SpriteComponent>().setFrameIdle("Enemy3_Idle-red", 4, Speed100);
	enemy4Map3.addGroup(Game::groupMapEnemy3);
	enemy4Map3.addComponent<ColliderComponent>("Enemy4Map3", EnemyX3 + 300 * 3, EnemyY3, DIMENSION64 * 1, HEIGHTENEYMY * 1);

	// godNamek
	godNamek.addComponent<TransformComponent>(GodNamekX, GodNamekY, 64, 64, 2);
	godNamek.addComponent<SpriteComponent>( true);
	godNamek.getComponet<SpriteComponent>().setFrameIdle("godNamek", 2, Speed100);
	godNamek.addComponent<ColliderComponent>("GodNamek", GodNamekX, GodNamekY, 64 * 2, 64 * 2);
	markQuestion.addComponent<TransformComponent>(GodNamekX +40, GodNamekY - 30, 16, 16, 2);
	markQuestion.addComponent<SpriteComponent>(false);
	markQuestion.getComponet<SpriteComponent>().setText("markques");
	//SHENRON
	shenron.addComponent<TransformComponent>(SHENRONX, SHENRONY,WIDTHSHENRON, HEIGHTSHENRON,3);
	shenron.addComponent<SpriteComponent>( true);
	shenron.getComponet<SpriteComponent>().setFrameIdle("shenron", 2, Speed100);
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
	SDL_Rect playerCol = player.getComponet<ColliderComponent>().collider;
	Vector2D playerPosition = player.getComponet<TransformComponent>().position;

	std::stringstream ss;
	ss  <<"Map : "<< ManagerMap->getAmountOfMap()<<" - HP : "<<heal->HPPlayer;
	label.getComponet<UILabel>().SetLabelText(ss.str(), "Arial");
	std::stringstream ss1;
	ss1 << "Mvt";
	Message.getComponet<UILabel>().SetLabelText(ss1.str(), "GameTTF");
	static bool flagShenRon = false;
	static int x = 0;
	player.getComponet<TransformComponent>().position.y += 4;
	SDL_Rect* playerRect = &player.getComponet<ColliderComponent>().collider;
	//REFRESH AND UPDATE
	manager.refresh();
	manager.managerUPDATE();
	
	// HANDLE COLLISION HANDLE ENEMY
	std::size_t GroupIDEnemy = Game::groupUnknow;
	if (ManagerMap->getCurrentMap() == 1)
	{
		GroupIDEnemy = Game::groupMapEnemy1;
	}
	else if (ManagerMap->getCurrentMap() == 2)
	{
		GroupIDEnemy = Game::groupMapEnemy2;
	}
	else if (ManagerMap->getCurrentMap() == 3)
	{
		GroupIDEnemy = Game::groupMapEnemy3;
	}
	
	auto& enemies = manager.getEntityByGroup(GroupIDEnemy);
	for (auto& c : enemies)
	{
		SDL_Rect Ccol = c->getComponet<ColliderComponent>().collider;
		if (Collision::CheckCollision(*playerRect, Ccol))
		{
			std::cout << "Player Hit " << c->getComponet<ColliderComponent>().tag << std::endl;
			if (player.getComponet<SpriteComponent>().SPRITEFLIPRIGHT())
			{
				c->getComponet<SpriteComponent>().spriteFlip = SDL_FLIP_HORIZONTAL;
			}
			else
			{
				c->getComponet<SpriteComponent>().spriteFlip = SDL_FLIP_NONE;
			}
			c->getComponet<SpriteComponent>().Play("Attack");
			if (Game::events.type == SDL_KEYDOWN)
			{
				switch (Game::events.key.keysym.sym)
				{
				case SDLK_a:
					c->getComponet<SpriteComponent>().RenderFalse();
					c->setDeadTrue();
					c->getComponet<ColliderComponent>().setAtiveFalse();
					break;
				default:
					break;
				}
			}
			if (heal->isHPDead())
			{
				running = false;
			}
			else
			{
				
				heal->HPPlayer -= 3;
				player.getComponet<SpriteComponent>().Play("beAttack");
			}
		}
		else
		{
			c->getComponet<SpriteComponent>().Play("Idle");
		}
	}
	bool Change = true;
	for (auto& c : enemies)
	{
		if (c->isDead())
		{
			Change = false;
			break;
		}
	}

	// beyond window limit
	if (player.getComponet<TransformComponent>().position.x < 0)
		player.getComponet<TransformComponent>().position.x = 0;
	if (player.getComponet<TransformComponent>().position.y < 0)
		player.getComponet<TransformComponent>().position.y = 0;
	int IDMapChange = ManagerMap->GetRanDomMapExcept();
	bool ChangeMapCondtion = player.getComponet<TransformComponent>().position.x + player.getComponet<TransformComponent>().width * player.getComponet<TransformComponent>().scale > VIEWWIDTH;
	if (ChangeMapCondtion && flagShenRon)
	{
		player.getComponet<TransformComponent>().position.x = VIEWWIDTH - player.getComponet<TransformComponent>().width * player.getComponet<TransformComponent>().scale;
	}
	else if ( ChangeMapCondtion && !flagShenRon && Change)
	{
		player.getComponet<SpriteComponent>().Play("ChangeMap");
		map->DestroyTile();
		for (auto& c : enemies)
		{
			c->getComponet<SpriteComponent>().resetRender();
			c->setDeadFalse();
			c->getComponet<ColliderComponent>().setAtiveTrue();
		}
		map->LoadMap(ManagerMap->getStringMapByIndx(IDMapChange), 25, 20);
		player.getComponet<TransformComponent>().position = ManagerMap->getPositionCurrent();
		
		player.getComponet<KeyboardController>().SetMapCurrent(ManagerMap->getCurrentMap());
	}
	if (ManagerMap->MapisFull() && !flagShenRon) 
	{
		ss1 << "VICTORY";
		Message.getComponet<UILabel>().SetLabelText(ss1.str(), "GameTTF");
		player.getComponet<SpriteComponent>().Play("ChangeMap");
		player.getComponet<TransformComponent>().position = MAPSHENRONXY;
		player.getComponet<KeyboardController>().SetMapCurrent(4);
		map->Close();
		flagShenRon = true;
	}
	//HANDLE CAMERA
	camera.x = player.getComponet<TransformComponent>().position.x - WIDTHSCREEN/2;
	camera.y = player.getComponet<TransformComponent>().position.y - HEIGHTSCREEN/2;
	if (camera.x < 0)
		camera.x = 0;
	if (camera.y < 0)
		camera.y = 0;
	if (camera.x > camera.w)
		camera.x = camera.w;
	if (camera.y > camera.h)
		camera.y = camera.h;
}
//Function Thread
int threadFunction(void* data)
{
	std::size_t GroupIDEnemy = Game::groupUnknow;
	if(ManagerMap->getCurrentMap() == 1)
	{
		GroupIDEnemy = Game::groupMapEnemy1;
	}
	else if (ManagerMap->getCurrentMap() == 2)
	{
		GroupIDEnemy = Game::groupMapEnemy2;
	}
	else if(ManagerMap->getCurrentMap()==3 )
	{
		GroupIDEnemy = Game::groupMapEnemy3;
	}
	
	auto& enemies = manager.getEntityByGroup(GroupIDEnemy);
	//BACKGROUND DRAW
	if (ManagerMap->MapisFull())
	{
		bg.getComponet<SpriteComponent>().setText("backgroundSHENROn");
	}
	bg.draw();
	if (!ManagerMap->MapisFull())
	{
		er.draw();
		//BACKGROUND TILE
		map->DrawTile();
		//BACKGROUND Collider
		map->DrawColliders();
	}
	else
	{
		//Render God of earth and shenron
		godNamek.draw();
		markQuestion.draw();
		shenron.draw();
		//Render Player
	}
	player.draw();
	for (auto& en : enemies)
	{
		en->draw();
	}
	label.draw();
	Message.draw();
	//Update Window
	return 0;
}
void  Game::Render()
{
	SDL_RenderClear(windowRender);
	//THREAD
	int data = 101;
	threadID = SDL_CreateThread(threadFunction, "LazyThread", (void*)data);
	SDL_WaitThread(threadID, NULL);
	SDL_RenderPresent(windowRender);
}
void  Game::close()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(windowRender);
	IMG_Quit();
	SDL_Quit();
}