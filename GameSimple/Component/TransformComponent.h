#pragma once
#include"../ECS/ECS.h"
#include"../ECS/Vector2D.h"
#include<SDL.h>
#include"Collision.h"
extern const int WIDTHSCREEN;
extern const int HEIGHTSCREEN;


class TransformComponent :public Component
{
public:
	Vector2D position;
	Vector2D velocity;
	int width = 32;
	int height = 32;
	float scale = 1;
	int speed = 3;

	TransformComponent()
	{
		position.Zero();
	}
	TransformComponent(float _x, float _y)
	{
		position.x = _x;
		position.y = _y;
	}
	TransformComponent(float _x, float _y, int _width, int _height, float _scale)
	{
		position.x = _x;
		position.y = _y;
		width = _width;
		height = _height;
		scale = _scale;

	}
	void setPosition(Vector2D x)
	{
		position = x;
	}
	void setPosition(float _x,float _y)
	{
		position.x = _x;
		position.y = _y;
	}
	void setSpeed(int _s)
	{
		speed = _s;
	}
	void setScale(int _s)
	{
		scale = _s;
	}
	TransformComponent(float _scale)
	{
		scale = _scale;
		//Center player
		//position.x = WIDTHSCREEN/2;
		//position.y = HEIGHTSCREEN/2;
		position.Zero();
	}
	void init()override
	{
		velocity.Zero();
	}
	void updateComponnet()override
	{
		/*velocity.Normalize();*/
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}
};