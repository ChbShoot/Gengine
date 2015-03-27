#pragma once
#include <GTexture.h>
#include <SDL.h>

namespace Gengine
{
	// Texture Button
	class TButton
	{
	public:
		// We use these two to make the GTexture
		TButton();

		// Destructo
		~TButton();

		// Dispose things
		void Dispose();

		bool Init(SDL_Renderer* gRenderer, std::string path);

		GTexture GetTexture() { return bTexture;  }
		int GetWidth() { return bWidth; }
		int GetHeight() { return bHeight; }
	private:
		GTexture bTexture;
		int bWidth, bHeight;
	};

}