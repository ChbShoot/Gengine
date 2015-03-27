#include "TButton.h"
namespace Gengine
{

	TButton::TButton()
	{
	}


	TButton::~TButton()
	{
	}

	bool TButton::Init(SDL_Renderer* gRenderer, std::string path)
	{
		bool success = true;

		bTexture = GTexture();
		if (bTexture.LoadTexture(gRenderer, path))
		{
			printf("Loaded Image %s...\n", "background.png");
		}
		else
		{
			printf("Unable to load Image %s...\n", "background.png");
			success = false;
		}

		return success;
	}
}