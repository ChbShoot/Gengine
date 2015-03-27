#pragma once
#include "GTexture.h"
#include <SDL_ttf.h>

namespace Gengine
{
	GTexture::GTexture()
	{
		gTexture = NULL;
		gWidth = 0;
		gHeight = 0;
		gFrame = 0;
		gFrameTotal = 0;
	}

	void GTexture::Render(SDL_Renderer* gRenderer, int x, int y, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
		//		printf("W: %s, H: %s", getWidth(), getHeight());

  		SDL_Rect renderQuad = { x, y, GetWidth(), GetHeight() };

		SDL_Rect* clip = NULL;
		
		if (gFrameTotal > 0)
			clip = &gRectFrames[gFrame];

		if (clip != NULL && clip != nullptr)
		{
			renderQuad.w = clip->w;
			renderQuad.h = clip->h;
		}


		int ER = SDL_RenderCopyEx(gRenderer, gTexture, ((gFrameTotal > 0 || clip != NULL || clip != nullptr) ? &gRectFrames[gFrame] : 0), &renderQuad, angle, center, flip);
		if (ER < 0)
		{
			printf("ERROR RENDERING! %s", SDL_GetError());
		}

		gFrame++;

		if (gFrame > (gFrameTotal - 1))
			gFrame = 0;
	}


	bool GTexture::LoadTexture(SDL_Renderer* gRenderer, std::string path)
	{
		Dispose();
		SDL_Surface* loadedSurface = IMG_Load(path.c_str());
		SDL_Texture* tempText = NULL;
		if (loadedSurface == NULL)
		{
			printf("Unable to load image %s! SDL_image Error %s\n", path.c_str(), IMG_GetError());
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
//#ifdef SD_TTF_H
	bool GTexture::LoadFromRenderedText(SDL_Renderer* gRenderer, TTF_Font* gFont, std::string textureText, SDL_Color colorText)
	{
		Dispose();

		SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), colorText);
		if (textSurface == NULL)
		{
			printf("Unable to render text surface! SDL_ttf ERROR: %s\n", TTF_GetError());
		}
		else
		{
			gTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
			if (gTexture == NULL)
			{
				printf("Unable to create texture from rendered text! SDL ERROR: %s\n", SDL_GetError());
			}
			else 
			{
				gWidth = textSurface->w;
				gHeight = textSurface->h;
			}

			SDL_FreeSurface(textSurface);
		}

		return gTexture != NULL;
	}
//#endif

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

	void GTexture::SetClips(int cWidth, int cHeight)
	{

		gFrameTotal = gWidth / cWidth;

		for (int i = 0; i < gFrameTotal; i++)
		{
			gRectFrames[i].x = i * cWidth;
			gRectFrames[i].y = 0;
			gRectFrames[i].w = cWidth;
			gRectFrames[i].h = cHeight;
		}
	}

	GTexture::~GTexture()
	{
		//Dispose();
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