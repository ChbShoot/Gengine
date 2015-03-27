#pragma once
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <Game.h>
//#include <ImageFactory.h>
#include <string>

namespace Gengine
{
	class GTexture
	{
	public:

		GTexture();
		virtual ~GTexture();
		// Disposes things
		void Dispose();
		/// Render function
		// gRenderer - Renderer
		// x - X position
		// y - Y Position
		// clip - Rectangle for sprite sheeting
		// angle - Rotation
		// center - Center
		// flip - Flip
		void Render(SDL_Renderer* gRenderer, int x, int y, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
		// Loads texture from file
		bool LoadTexture(SDL_Renderer* gRenderer, std::string path);


		bool LoadFromRenderedText(SDL_Renderer* gRenderer, TTF_Font* gFont, std::string textureText, SDL_Color colorText);

		// Get texture width
		int GetWidth() { return gWidth; }
		// Get texture height
		int GetHeight() { return gHeight; }

		int GetFrame() { return gFrame; }


		// Set blend mode
		void SetBlendMode(SDL_BlendMode blending);

		// Set color morph
		void SetColor(Uint8 red, Uint8 green, Uint8 blue);

		// Set texture alpha
		void SetAlpha(Uint8 alpha);

		// Set the animation clips
		void SetClips(int cWidth, int cHeight);
	private:
		SDL_Texture* gTexture;
		SDL_Rect gRectFrames[8];
		int gWidth;
		int gHeight;
		int gFrame;
		int gFrameTotal;
	};
}

