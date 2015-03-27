#include "Game.h"
#include <Match.h>
#include <GPlayer.h>
#include <GActor.h>
#include <SDL.h>
#include <SDL_thread.h>
#include <GTimer.h>
#include <SDL_ttf.h>
#include <sstream>

namespace Gengine
{
	// Ticks per Frame
	double SCREEN_TICKS_PER_FRAME;
	// Kill switch
	bool QUIT;

	// Game SDL window
	SDL_Window* gWindow;
	// Game draw surface on window
	SDL_Surface* gWindowSurface;
	// Game renderer
	SDL_Renderer* gRenderer;

	// Game global font
	TTF_Font* gFont;

	// Text for time
	std::stringstream txtAvgFps;

	// Current match
	Match curMatch;

	// Timer for FPS cal
	GTimer FPSTimer;
	// Timer for frame cal
	GTimer DrawCap;

	// Player 1
	GPlayer curPlayer;
	// Texture for SNGuy
	GTexture gSNGuy;

	// Texture for game background
	GTexture gBackground;

	// Texture surface for FPS renderings
	GTexture gFPSText;



	int FPS;

	Game::Game()
	{
		// Calculate how many ms each frame should be
		SCREEN_TICKS_PER_FRAME = 1000.f / Gengine::SCREEN_FPS;
		// Set kill switch to false
		QUIT = false;
		// Set current fps to 0
		FPS = 0;

	}

	Game::~Game()
	{
		// Dispose game
		Dispose();
	}

	bool Game::Init()
	{
		// Initialize stuff to null
		gWindow = NULL;
		gWindowSurface = NULL;
		gRenderer = NULL;
		gFont = NULL;
		bool success = true;

		// Start counting time since game started
		FPSTimer.Start();

		// If it fails, it returns a negative number

		// Create Window
		gWindow = SDL_CreateWindow("Gengine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			Gengine::SCREEN_WIDTH, Gengine::SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		// If Window didn't initialize
		if (gWindow == NULL)
		{
			printf("Window could not be created!!! SDL_ERROR: %s\n", SDL_GetError());
			success = false;
			return success;
		}
		printf("Created Window\n");
		// Create Renderer
		this->gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);


		// If renderer didn't initialize
		if (gRenderer == NULL)
		{
			printf("SDL_Renderer could not be created! SDL_error %s\n", SDL_GetError());
			success = false;
			return success;
		}

		// PNG loading
		int imgFlags = IMG_INIT_PNG;

		// If SDL_Image didn't initialize
		if (!(IMG_Init(imgFlags) & imgFlags))
		{
			printf("SDL_image could not initialize PNG. SDL_image Error: %s\n", IMG_GetError);
			success = false;
			return success;
		}
		printf("Initialized SDL_Image : PNG\n");

		// If font didn't initialize
		if (TTF_Init() == -1)
		{
			printf("SDL_ttf could not initialize! SDL_ttf ERROR: %s\n", TTF_GetError());
			success = false;
			return success;
		}

		// Get surface for window
		gWindowSurface = SDL_GetWindowSurface(gWindow);


		// If we don't have any joysticks 
		if (SDL_NumJoysticks() < 1)
		{
			printf("No joysticks connected!\n");
		}

		// Make sure SDL is initialized before loading media
		SDL_Delay(500);

		// Load our resources
		//////////////////////////////////////////////////////////////////////////
		/// TODO: move to new factory
		//////////////////////////////////////////////////////////////////////////
		if (!LoadMedia())
		{
			printf("Could not load media!\n");
			success = false;
			return success;
		}

		SDL_Rect field;

		// Player 1
		// Initialize player field
		field.x = 0;
		field.y = 50;
		field.h = Gengine::SCREEN_HEIGHT - 100;
		field.w = Gengine::SCREEN_WIDTH / 2;
		curPlayer = GPlayer("SNGGuy", field);
		SDL_Point midScreenPoint = { Gengine::SCREEN_WIDTH / 4, Gengine::SCREEN_HEIGHT / 2 };

		// Start the match
		curPlayer.Initialize(Gengine::ActorType::LOCAL, gSNGuy, &curMatch, midScreenPoint);
		curMatch.Initialize(10000, 10, &gBackground);
		curMatch.SetLocal(curPlayer);
		curMatch.CountDown(5);
		return success;
	}

	float avgFPS;
	// Some threadding nonsense
	extern "C" int handleSDLEvent(void* data);
	extern "C" int handleDraw(void* data);
	void Game::GameLoop()
	{
		FPSTimer.Start();
		while (!QUIT)
		{
			// Start counting how long frame took
			DrawCap.Start();
			// Calculate FPS
			avgFPS = FPS / (FPSTimer.GetTicks() / 1000.f);


			SDL_Event e;
			// Update user action loop
			while (SDL_PollEvent(&e))
			{
				switch (e.type)
				{
				case SDL_QUIT:
					QUIT = true;
					break;
					// Some debug logic
				case SDL_KEYDOWN:
					if (e.key.keysym.sym == SDLK_ESCAPE)
					{
						QUIT = true;
						break;
					}
					if (e.key.keysym.sym == SDLK_p)
					{
						SDL_Rect field;

						// Player 1
						field.x = 0;
						field.y = 50;
						field.h = Gengine::SCREEN_HEIGHT - 50;
						field.w = Gengine::SCREEN_WIDTH / 2;
						curPlayer = GPlayer("SNGGuy", field);
						SDL_Point midScreenPoint = { Gengine::SCREEN_WIDTH / 4, Gengine::SCREEN_HEIGHT / 2 };

						curPlayer.Initialize(Gengine::ActorType::LOCAL, gSNGuy, &curMatch, midScreenPoint);
						curMatch.Initialize(10000, 10, &gBackground);
						curMatch.SetLocal(curPlayer);
						curMatch.CountDown(5);
						break;
					}
					break;
				// All the players really need to handle atm
				case SDL_JOYDEVICEADDED:
				case SDL_JOYDEVICEREMOVED:
				case SDL_JOYAXISMOTION:
					if (curMatch.GetRunning())
						curMatch.Handle(&e);
					break;
					/*
					SDL_Thread* handleThread = SDL_CreateThread(handleSDLEvent, "HandleSDL", (void*)&e);
					SDL_WaitThread(handleThread, NULL);
					break;
					*/
				}
			}

			if (curMatch.GetRunning())
				curMatch.Update();

			Draw();

			int frameTicks = DrawCap.GetTicks();
			DrawCap.Stop();
			if (frameTicks < SCREEN_TICKS_PER_FRAME)
			{
				SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
			}

			FPS++;
		}
	}
	extern "C" int handleSDLEvent(void* data)
	{
		SDL_Event* datas = static_cast<SDL_Event *>(data);
		if (curMatch.GetRunning())
			curMatch.Handle(datas);

		return curMatch.GetRunning();
	}

	void Game::Draw()
	{
		// Clear to cornflower blue because XNA tears
		//SDL_SetRenderDrawColor(gRenderer, 0x69, 0x9c, 0xEF, 0xFF);

		// Clear to white cause yeah
		//SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);


		// Load the curFPS texture SDL_TTF
		txtAvgFps.str("");
		txtAvgFps << "Average FPS: " << avgFPS;
		if (!gFPSText.LoadFromRenderedText(gRenderer, gFont, txtAvgFps.str().c_str(), { 0, 0, 0, 255 }))
		{
			printf("Unable to make FPS text\n");
		}

		// If we're in a match, render
		if (curMatch.GetRunning())
			curMatch.Render(gRenderer);

		// Render the FPS text
		gFPSText.Render(gRenderer, 15, 15);

		// Draw
		SDL_RenderPresent(gRenderer);
	}

	// Garbage dump
	void Game::Dispose()
	{
		TTF_CloseFont(gFont);
		gFont = NULL;

		if (&curMatch != NULL)
		{
			if (curMatch.GetRunning())
				curMatch.Dispose();
		}

		gSNGuy.Dispose();
		gBackground.Dispose();

		SDL_DestroyWindow(gWindow);
		SDL_DestroyRenderer(gRenderer);

		gRenderer = NULL;
		gWindow = NULL;

		SDL_Quit();
		TTF_Quit();
		IMG_Quit();
	}

	bool Game::LoadMedia()
	{
		// Loads media
		bool success = true;

		gSNGuy = GTexture();
		if (gSNGuy.LoadTexture(gRenderer, "D:\\Tools\\sprites\\spritesheetwalker.png"))
		{
			printf("Loaded Image %s...\n", "sngguy.png");
		}
		else
		{
			success = false;
		}




		gBackground = GTexture();
		if (gBackground.LoadTexture(gRenderer, "D:\\Tools\\sprites\\shrektBg.png"))
		{
			printf("Loaded Image %s...\n", "background.png");
		}
		else
		{
			printf("Unable to load Image %s...\n", "background.png");
			success = false;
		}


		gFont = TTF_OpenFont("lazy.ttf", 18);
		if (gFont == NULL)
		{
			printf("Unable to load lazy font! SDL_ttf ERROR: %s\n", TTF_GetError());
			success = false;
		}
		else
		{
			SDL_Color txtColor = { 0, 0, 0 };
		}

		return success;
	}
};