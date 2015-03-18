#pragma once
#include <string>
#include <SDL.h>
#include <SDL_image.h>
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
		void Render(SDL_Renderer* gRenderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
		// Loads texture from file
		bool LoadTexture(SDL_Renderer* gRenderer, std::string path);

		// Get texture width
		int GTexture::getWidth();
		// Get texture height
		int GTexture::getHeight();

		// Set blend mode
		void GTexture::SetBlendMode(SDL_BlendMode blending);

		// Set color morph
		void GTexture::SetColor(Uint8 red, Uint8 green, Uint8 blue);

		// Set texture alpha
		void GTexture::SetAlpha(Uint8 alpha);
		std::string path;
	private:
		SDL_Texture* gTexture;
		int gWidth;
		int gHeight;
	};
}

