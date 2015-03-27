#pragma once
#include <sdl.h>


namespace Gengine
{
	// Game button
	class GButton
	{
	public:
		GButton();
		~GButton();

		// Set position of button
		void SetPosition(int x, int y);

		// Mouse events
		void EventHandler(SDL_Event* e);

		// Rendererer
		void Render();

	private:
		// TL /\  <
		SDL_Point gPosition;


	};
}