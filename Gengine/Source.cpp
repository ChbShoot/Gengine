#pragma once

#include <SDL.h>
#include <stdio.h>
#include <string>
#include <Game.h>
#include "Constants.h"
using namespace std;

int main(int argc, char *args[])
{
	Gengine::Game GameInstance = Gengine::Game();
	if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0)
	{
		// Immediately prints error and backs out of the rest of execution
		printf("SDL Could not initialize! SDL_ERROR: %s\n", SDL_GetError());
		system("pause");
		return -1;
	}
	else
	{
		printf("Initialized SDL VIDEO\n");

		//if (SDL_InitSubSystem(SDL_INIT_JOYSTICK) < 0)
		{
			//printf("SDL_Joystick could not initialize! SDL_Error: %s\n", SDL_GetError());
			//system("pause");
			//return -1;
		}

		printf("Initialized Joysticks");
		if (GameInstance.Init())
		{
			GameInstance.GameLoop();
		}
	}

	system("pause");
	return 0;
}
