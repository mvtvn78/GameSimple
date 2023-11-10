#pragma once
#include"Game.h"
#include<iostream>
#include"Asset/Map.h"
#include"Asset/AssetManager.h"
#include"../ECS/ECS.h"
#include"../Component/Components.h"
#include"../Component/Collision.h"
#include"HandleMap.h"
SDL_Renderer* Game::windowRender = NULL;
SDL_Event Game::events;
// CONSTANT DECLARE
const int VIEWWIDTH = 1600;
const int VIEWHEIGHT = 1280;
const int WIDTHSCREEN = VIEWWIDTH / 2;
const int HEIGHTSCREEN = VIEWHEIGHT / 2;
//ENEMY
const int EnemyX3 = 378;
const int EnemyY3 = 834;

const int EnemyX2= 400;
const int EnemyY2 = 710;
const int Speed100 = 100;
const int EnemyX1 = 400;
const int EnemyY1 = 1025-60;
const int HEIGHTENEYMY = 32;
const int DIMENSION64 = 64;

const int PlayerMapShenRonX = 100;
const int PlayerMapShenRonY = 1115;
const int WIDTHPLAYER = 32;
const int HEIGHTPLAYER = 40;
const float SCALEPLAYER = 2;
const int XYPLAYERCOLLIDER = 50;
const int SpeedPlayer = 6;
const int GodNamekX = 779;
const int GodNamekY = 1039;

const int SHENRONX = 600;
const int SHENRONY = 800;
const int WIDTHSHENRON = 128;
const int HEIGHTSHENRON = 256;
int MaxMapShenron = 1140;
//HEADUP 
const SDL_Rect headUpPlayer = {0,0,272,100};
const SDL_Rect headUpEnemy = {292,120,264,40};
//Map Constain
const Vector2D MAPSHENRONXY = Vector2D(PlayerMapShenRonX, PlayerMapShenRonY);
// CAMERA AND MANAGER DECLERATION
SDL_Rect Game::camera = { 0,0,WIDTHSCREEN,HEIGHTSCREEN };
SDL_RendererFlip FlipNone = SDL_FLIP_NONE;
SDL_RendererFlip FlipHorizontal = SDL_FLIP_HORIZONTAL;
Manager manager;
AssetManager* Game::asset = new AssetManager(&manager);
auto& player(manager.addEntity());
auto& godNamek(manager.addEntity());
auto& shenron(manager.addEntity());
//Enemy Map1
auto& enemy1Map1(manager.addEntity());
auto& enemy2Map1(manager.addEntity());
auto& enemy3Map1(manager.addEntity());
auto& enemy4Map1(manager.addEntity());
//Enemy Map 2
auto& enemy1Map2(manager.addEntity());
auto& enemy2Map2(manager.addEntity());
auto& enemy3Map2(manager.addEntity());
auto& enemy4Map2(manager.addEntity());
//Enemy Map 3
auto& enemy1Map3(manager.addEntity());
auto& enemy2Map3(manager.addEntity());
auto& enemy3Map3(manager.addEntity());
auto& enemy4Map3(manager.addEntity());
bool isShenron = false;
auto& bg(manager.addEntity());
auto& er(manager.addEntity());
auto& headupPlayer(manager.addEntity());
auto& heaupEnemy(manager.addEntity());
auto& markQuestion(manager.addEntity());
//Manager Map
HandleMap* ManagerMap;
//Map* map;
Map* map = NULL;
std::string map1 = "F:\\Working\\GIT\\MixerGame\\MixerGame\\MixerGame\\Game\\Asset\\map\\map1.map";
std::string map2 = "F:\\Working\\GIT\\MixerGame\\MixerGame\\MixerGame\\Game\\Asset\\map\\map2.map";
std::string map3 = "F:\\Working\\GIT\\MixerGame\\MixerGame\\MixerGame\\Game\\Asset\\map\\map3.map";
SDL_Thread* threadID = NULL;
//Label
auto& label(manager.addEntity());
auto& Message(manager.addEntity());
HealPlayer* heal = NULL;
