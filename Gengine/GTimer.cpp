#include "GTimer.h"

namespace Gengine
{
	GTimer::GTimer()
	{
		tStartTicks = 0;
		tPausedTicks = 0;

		tPaused = false;
		tStarted = false;
	}


	void GTimer::Start()
	{
		tStarted = true;
		tPaused = false;

		tStartTicks = SDL_GetTicks();
		tPausedTicks = 0;
	}

	void GTimer::Pause()
	{
		if (tStarted && !tPaused)
		{
			tPaused = true;

			tPausedTicks = SDL_GetTicks() - tStartTicks;
			tStartTicks = 0;
		}
	}

	void GTimer::Unpause()
	{
		if (tStarted && tPaused)
		{
			tPaused = false;

			tStartTicks = SDL_GetTicks() - tPausedTicks;
			tPausedTicks = 0;
		}
	}

	void GTimer::Stop()
	{
		tStarted = false;
		tPaused = false;

		tStartTicks = 0;
		tPausedTicks = 0;
	}

	Uint32 GTimer::GetTicks()
	{
		if (tStarted)
			return tPaused ? tPausedTicks : (SDL_GetTicks() - tStartTicks);
		else
			return 0;
	}
}