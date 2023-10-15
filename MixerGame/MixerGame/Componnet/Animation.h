#pragma once
struct Animation
{
	int index;
	int frames;
	int speed;

	Animation()
	{

	}
	Animation(int i, int f, int s)
	{
		// index : index row
		index = i;
		// frame : number of all frame in animation
		frames = f;
		speed = s;
	}
};