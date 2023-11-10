#pragma once
#include <SDL_mixer.h>
#include<string>
#include<iostream>
#include<bitset>
#define MAXSOUND 100
class Audio
{
private:
	Mix_Music* BgPlay;
	Mix_Chunk* ArraySound [MAXSOUND];
	std::size_t sizeSound = 0u;
	const char* ADAttackUp = "F:\\Working\\GIT\\MixerGame\\MixerGame\\MixerGame\\Game\\Asset\\Audio\\ADAttackUp.wav";
	const char* ADPlayerWalk = "F:\\Working\\GIT\\MixerGame\\MixerGame\\MixerGame\\Game\\Asset\\Audio\\ADWalk.wav";
	const char* ADWalkMapShenRon = "F:\\Working\\GIT\\MixerGame\\MixerGame\\MixerGame\\Game\\Asset\\Audio\\ADWalkMapShenRon.wav";
	const char* ADJump = "F:\\Working\\GIT\\MixerGame\\MixerGame\\MixerGame\\Game\\Asset\\Audio\\ADJump.wav";
	const char* ADShenRonEf = "F:\\Working\\GIT\\MixerGame\\MixerGame\\MixerGame\\Game\\Asset\\Audio\\ADShenRonEf.wav";

public:
	enum Sound : std::size_t
	{
		AttackUP,
		PlayerWalk,
		WalkMapShenRon,
		ShenRonEF,
		Jump,
	};
	//AUDIO MAP
	const char* MsMap1 = "F:\\Working\\GIT\\MixerGame\\MixerGame\\MixerGame\\Game\\Asset\\Audio\\ADMap1.mp3";
	const char* MsMap2 = "F:\\Working\\GIT\\MixerGame\\MixerGame\\MixerGame\\Game\\Asset\\Audio\\ADMap2.wav";
	const char* MsMap3 = "F:\\Working\\GIT\\MixerGame\\MixerGame\\MixerGame\\Game\\Asset\\Audio\\ADMap3.wav";
	const char* MsMapShenRon = "F:\\Working\\GIT\\MixerGame\\MixerGame\\MixerGame\\Game\\Asset\\Audio\\ADMapShenron.wav";
	//AUDIO SOUND
	Audio()
	{
		BgPlay = NULL;
		memset(ArraySound, NULL, MAXSOUND);
	}
	const char* getStrByID(int _id)
	{
		return (_id == 1) ? MsMap1 : (_id==2) ? MsMap2: (_id==3) ?MsMap3 : (_id==4) ? MsMapShenRon : "";
	}
	bool LoadSound(const char * t)
	{
		if (sizeSound == MAXSOUND)
		{
			std::cout << "Container IS FULL"<<std::endl;
			return false;
		}
		Mix_Chunk* temp = Mix_LoadWAV(t);
		ArraySound[sizeSound++] = temp;
		return true;
	}
	bool LoadFullSound()
	{
		std::bitset<MAXSOUND> check;
		check.set();
		check[sizeSound] = LoadSound(ADAttackUp);
		check[sizeSound] = LoadSound(ADPlayerWalk);
		check[sizeSound] = LoadSound(ADWalkMapShenRon);
		check[sizeSound] = LoadSound(ADShenRonEf);
		check[sizeSound] = LoadSound(ADJump);
		return check.all();
	}
	void PlaySound(std::size_t ID)
	{
		Mix_PlayChannel(-1, ArraySound[ID], 0);
	}
	bool LoadMusic(const char* t)
	{
		BgPlay = Mix_LoadMUS(t);
		if (BgPlay == NULL)
			std::cout << "PATH NOT FOUND " << t << std::endl;
		return BgPlay;
	}
	void PlayAndPauseMsBg()
	{
		if (BgPlay==NULL)
			std::cout << "Music Null" << std::endl;
		//If there is no music playing
		if (Mix_PlayingMusic() == 0)
		{
			//Play the music
			Mix_PlayMusic(BgPlay, -1);
		}
		//If music is being played
		else
		{
			//If the music is paused
			if (Mix_PausedMusic() == 1)
			{
				//Resume the music
				Mix_ResumeMusic();
			}
			//If the music is playing
			else
			{
				//Pause the music
				Mix_PauseMusic();
			}
		}
	}
	void StopAFreeMsBg()
	{
		Mix_HaltMusic();
		Mix_FreeMusic(BgPlay);
	}
	void CloseMusic()
	{
		Mix_FreeMusic(BgPlay);
		for (std::size_t i = 0; i < MAXSOUND; ++i)
		{
			Mix_FreeChunk(ArraySound[i]);
		}
		Mix_Quit();
	}
};
