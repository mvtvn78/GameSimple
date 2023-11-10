#pragma once
struct Animation
{
	//int index;
	int frames;
	int speed;
	std::string id;
	Animation()
	{
		/*index = 0;*/
		frames = 0;
		speed = 0;
		id = "";
	}
	Animation(std::string _id, int f, int s)
	{
		id = _id;
		// index : index row
	/*	index = i;*/
		// frame : number of all frame in animation
		frames = f;
		speed = s;
	}
};