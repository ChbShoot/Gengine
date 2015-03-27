#pragma once
#include <SDL.h>

namespace Gengine 
{
	class GTimer
	{
	public:

		GTimer();

		void Start();
		void Stop();
		void Pause();
		void Unpause();

		Uint32 GetTicks();

		bool IsStarted() { return tStarted; }
		bool IsPaused() { return tPaused && tStarted; }

	private:
		Uint32 tStartTicks;
		Uint32 tPausedTicks;

		bool tPaused;
		bool tStarted;
	};
}
