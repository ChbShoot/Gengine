#pragma once
#include "Game.h"

namespace Gengine
{
	// Incoming window size
	int SCREEN_WIDTH, SCREEN_HEIGHT;

	// Speed move multiplier for our little guy
	const int SPEED_MULTIPLIER = 25;
	// Alpha value, transparency 
	Uint8 ALPHAPLIER = 255;
	// Mood is sprite animation
	int x = 0, y = 0, mood = 0;

	// Kill switch
	bool QUIT;

	// Main window
	SDL_Window* gWindow;
	// Drawing surface on window
	SDL_Surface* gWindowSurface;
	// Drawer
	SDL_Renderer* gRenderer;

	// Our guy
	GTexture gSNGuy;
	// Sprite locations
	SDL_Rect gSNGuySpriteLocs[6];
	// Holds the scenery
	GTexture gBackground;

	Game::Game(int width, int height)
	{
		SCREEN_WIDTH = width;
		SCREEN_HEIGHT = height;
		QUIT = false;
	}

	Game::~Game()
	{
		Dispose();
	}

	bool Game::Init()
	{
		gWindow = NULL;
		gWindowSurface = NULL;
		gRenderer = NULL;
		bool success = true;

		// If it fails, it returns a negative number
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			// Immidiately prints error and backs out of the rest of execution
			printf("SDL Could not initialize! SDL_ERROR: %s\n", SDL_GetError());
			success = false;
			return success;
		}
		else
		{
			printf("Initialized SDL\n");
			// Create Window
			gWindow = SDL_CreateWindow("Gengine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
				SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
			if (gWindow == NULL)
			{
				printf("Window could not be created!!! SDL_ERROR: %s\n", SDL_GetError());
				success = false;
				return success;
			}
			printf("Created Window\n");
			// Create Renderer
			this->gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

			if (gRenderer == NULL)
			{
				printf("SDL_Renderer could not be created! SDL_error %s\n", SDL_GetError());
				success = false;
				return success;
			}

			// PNG loading
			int imgFlags = IMG_INIT_PNG;

			if (!(IMG_Init(imgFlags) & imgFlags))
			{
				printf("SDL_image could not initialzie PNG. SDL_image Error: %s\n", IMG_GetError);
				success = false;
				return success;
			}
			printf("Initialized SDL_Image : PNG\n");

			// Get surface for window
			gWindowSurface = SDL_GetWindowSurface(gWindow);

			if (!LoadMedia())
			{
				printf("Could not load media!");
				success = false;
				return success;
			}
		}

		return success;
	}

	bool Game::Update()
	{
		// just gives us random number between 1-5
		mood = rand() % 6;
		SDL_Event e;
		// Update user action loop
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
				QUIT = true;

			else if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.sym)
				{
				default:
					break;
				case SDLK_ESCAPE:
					QUIT = true;
					break;
				case SDLK_RIGHT:
					x += SPEED_MULTIPLIER;
					break;
				case SDLK_LEFT:
					x -= SPEED_MULTIPLIER;
					break;
				case SDLK_UP:
					y += SPEED_MULTIPLIER;
					break;
				case SDLK_DOWN:
					y -= SPEED_MULTIPLIER;
					break;
				case SDLK_SPACE:
					ALPHAPLIER--;
					break;
				}
			}
		}

		Draw();
		return QUIT;
	}

	bool Game::Draw()
	{
		// Clear to cornflower blue because XNA tears
		SDL_SetRenderDrawColor(gRenderer, 0x69, 0x9c, 0xEF, 0xFF);
		SDL_RenderClear(gRenderer);


		// Set background (0,0)
		gBackground.Render(gRenderer, NULL, 0, 0);
		gSNGuy.SetAlpha(ALPHAPLIER);
		// Render dudes
		gSNGuy.Render(gRenderer, x, y, &gSNGuySpriteLocs[mood]);

		// Draw
		SDL_RenderPresent(gRenderer);

		return true;
	}

	void Game::Dispose()
	{
		gSNGuy.Dispose();
		gBackground.Dispose();

		SDL_DestroyWindow(gWindow);
		SDL_DestroyRenderer(gRenderer);

		gRenderer = NULL;
		gWindow = NULL;

		SDL_Quit();
		IMG_Quit();
	}

	bool Game::LoadMedia()
	{
		// Loads media
		bool success = true;

		gSNGuy = GTexture();
		if (gSNGuy.LoadTexture(gRenderer, "spritesheet.png"))
		{
			printf("Loaded Image %s...\n", "spritesheet.png");

			for (int i = 0; i < 6; i++)
			{
				gSNGuySpriteLocs[i].x = i * 64;
				gSNGuySpriteLocs[i].y = 0;
				gSNGuySpriteLocs[i].w = 64;
				gSNGuySpriteLocs[i].h = 32;
			}
		}
		else
		{
			printf("Unable to load Image %s...\n", "spritesheet.png");
			success = false;
		}

		gBackground = GTexture();
		if (gBackground.LoadTexture(gRenderer, "background.png"))
		{
			printf("Loaded Image %s...\n", "background.png");
		}
		else
		{
			printf("Unable to load Image %s...\n",  "background.png");
			success = false;
		}

		return success;
	}
};