#include"Collision.h"
#include"ColliderComponent.h"
bool Collision::AABB(const SDL_Rect& A, const SDL_Rect& B)
{
	if (A.x + A.w >= B.x && B.x + B.w >= A.x && A.y + A.h >= B.y && B.y + B.h >= A.y)
	{
		return true;
	}
	return false;
}
bool Collision::AABB(const ColliderComponent& colA, const ColliderComponent& colB)
{
	if (AABB(colA.collider, colB.collider))
	{
		std::cout << colA.tag << " hit " << colB.tag << std::endl;
		return true;
	}
	return false;
}

bool Collision::CheckCollision(const SDL_Rect& a, const SDL_Rect& b)
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //If any of the sides from A are outside of B
    if (bottomA <= topB)
    {
        return false;
    }

    if (topA >= bottomB)
    {
        return false;
    }

    if (rightA <= leftB)
    {
        return false;
    }

    if (leftA >= rightB)
    {
        return false;
    }

    return true;
}

bool Collision::CheckAbove(const SDL_Rect& a, const SDL_Rect& b)
{
    return a.y + a.h >= b.y && CheckCollision(a,b);
}

bool Collision::CheckLeft(const SDL_Rect& a, const SDL_Rect& b)
{
    return a.x + a.w ==b.x  && CheckCollision(a, b);
}

bool Collision::CheckRight(const SDL_Rect& a, const SDL_Rect& b)
{
    return a.x  <= b.x + b.w && CheckCollision(a, b);
}
