
// Includes needed
#pragma once
// SDL engine
#include <SDL.h>
// Load PNG images
#include <SDL_Image.h>
// String
#include <string>
// Gengine Texture class
#include <GTexture.h>
// Stds
#include <stdlib.h>

using namespace std;

namespace Gengine
{
	class Game
	{
	public:
		Game(int width, int height);
		virtual ~Game();

		// Store game window width
		int SCREEN_WIDTH;

		// Store game window height
		int SCREEN_HEIGHT;

		// Kill switch literally
		bool QUIT;

		// Gametime update
		/// TODO: Add GameTime ticker as parameter with set value & so can use for logic
		bool Update();

		// Get rid of everything
		void Dispose();

		// Initialize the engines
		bool Init();

		// Called on update, used to draw
		bool Draw();

		// Load media at the start
		bool LoadMedia();

		SDL_Renderer* Game::getRenderer() { return gRenderer; }
	private:
		// The dude spritesheet
		GTexture gSNGuy;
		// The background
		GTexture gBackground;
		/// Window
		SDL_Window* gWindow;
		/// Surface on the window
		SDL_Surface* gWindowSurface;

		// Renderer on the surface on the window
		SDL_Renderer* gRenderer;
	};
};