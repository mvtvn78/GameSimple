#pragma once
#include"../ECS/ECS.h"
#include"../ECS/Vector2D.h"

extern const int WIDTHSCREEN;
extern const int HEIGHTSCREEN;
class TransformComponent :public Component
{
public:
	Vector2D position;
	Vector2D velocity;
	int width = 32;
	int height = 32;
	int scale = 1;
	int speed = 10;
	TransformComponent()
	{
		position.Zero();
	}
	TransformComponent(float _x, float _y)
	{
		position.x = _x;
		position.y = _y;
	}
	TransformComponent(float _x, float _y, int _width, int _height, int _scale)
	{
		position.x = _x;
		position.y = _y;
		width = _width;
		height = _height;
		scale = _scale;
	}
	TransformComponent(int _scale)
	{
		scale = _scale;
		//Center player
		position.x = WIDTHSCREEN/2;
		position.y = HEIGHTSCREEN/2;
	}
	void init()override
	{
		velocity.Zero();
	}
	void updateComponnet()override
	{
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}
};