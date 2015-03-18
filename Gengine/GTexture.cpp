#include <Game.h>
#include "GTexture.h"

namespace Gengine
{
	GTexture::GTexture()
	{
		gTexture = NULL;
		gWidth = 0;
		gHeight = 0;
	}

	void GTexture::Render(SDL_Renderer* gRenderer, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
 	{
//		printf("W: %s, H: %s", getWidth(), getHeight());

		SDL_Rect renderQuad = { x, y, getWidth(), getHeight()};

		if (clip != NULL)
		{
			renderQuad.w = clip->w;
			renderQuad.h = clip->h;
		}

		SDL_RenderCopyEx(gRenderer,gTexture, clip, &renderQuad, angle, center, flip);
	}

	 
	bool GTexture::LoadTexture(SDL_Renderer* gRenderer, std::string path)
	{
		Dispose();
		SDL_Surface* loadedSurface = IMG_Load(path.c_str());
		SDL_Texture* tempText = NULL;
		if (loadedSurface == NULL)
		{
			printf("Unable to load image %s! SDL_image Erorr %s\n", path.c_str(), IMG_GetError());
		}
		else
		{

			SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
			tempText = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
			if (tempText == NULL)
			{
				printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
			}
			else
			{
				this->gWidth = loadedSurface->w;
				this->gHeight = loadedSurface->h;
			}

			SDL_FreeSurface(loadedSurface);
		}

		gTexture = tempText;
		return gTexture != NULL;
	}
	int GTexture::getWidth() {
		return gWidth;
	};
	int GTexture::getHeight() {
		return gHeight;
	};

	void GTexture::SetColor(Uint8 red, Uint8 green, Uint8 blue)
	{
		// Modulate the texture
		SDL_SetTextureColorMod(gTexture, red, green, blue);
	}

	void GTexture::SetAlpha(Uint8 alpha)
	{
		// Modify the alpha value
		SDL_SetTextureAlphaMod(gTexture, alpha);
	}

	GTexture::~GTexture()
	{
		Dispose();
	}

	void GTexture::Dispose()
	{
		if (gTexture != NULL)
		{
			SDL_DestroyTexture(gTexture);
			gTexture = NULL;
			gWidth = 0;
			gHeight = 0;
		}
	}

}