#include <SDL.h>
#include <stdio.h>
#include <string>
#include <Game.h>

using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 640;
int main(int argc, char *argv[])
{
	Gengine::Game* GameInstance = new Gengine::Game(SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!GameInstance->Init())
		printf("Failed to initialize!! \n");
	else
	{
		printf("Gengine Initialized, window and screen surface created \n");
	}

	while (!GameInstance->Update())
	{
		
	}
	return 0;
}
