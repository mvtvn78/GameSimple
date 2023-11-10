#pragma once
#include"SDL.h"
class ColliderComponent;
class Collision
{
public:
	static bool AABB(const SDL_Rect& A, const SDL_Rect& B);
	static bool AABB(const ColliderComponent& colA, const ColliderComponent& colB);
	static bool CheckCollision(const SDL_Rect& a, const SDL_Rect& b);
	static bool CheckAbove(const SDL_Rect& a, const SDL_Rect& b);
	static bool CheckLeft(const SDL_Rect& a, const SDL_Rect& b);
	static bool CheckRight(const SDL_Rect& a, const SDL_Rect& b);
};
