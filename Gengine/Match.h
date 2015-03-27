#pragma once
#include <SDL.h>
#include <../Gengine/GTimer.h>
#include <../Gengine/Game.h>
#include <../Gengine/GActor.h>
#include <../Gengine/GPlayer.h>
#include <../Gengine/GTexture.h>
#include "../Gengine/GBall.h"

namespace Gengine
{
	class Match
	{
	private:
		GTexture* mBackground;
		bool mRunning;
		void RenderBackground();

		GPlayer mPlayers[1];
		GBall mBall;

		Uint32 mDuration;
		int mScoreLimit;
		Uint32 mStartTime = 0;
		SDL_Rect Walls[2];
	public:
		Match();
		~Match();

		// Initializes the match with duration, scoreLimit, background texture
		void Initialize(Uint32 duration, int scoreLimit, GTexture* backGround);
		// Start & countdown the match
		void CountDown(int delay);
		// Start the match, should be private
		void StartMatch();

		// Is the match ongoing?
		bool GetRunning() { return mRunning; };
		// Set the match running value
		void SetRunning(bool val) { mRunning = val; };

		// Render the match objects
		void Render(SDL_Renderer* renderer);
		// Update the match objects
		void Update();
		// Handle the incoming SDL events
		void Handle(SDL_Event* ev);
		// Handle joystick events
		void HandleJoystick(SDL_Event* ev);

		// Set local player to 0
		void SetLocal(GPlayer player);
		// Score on player
		void Score(GActor* scoreActor);
		// Get list of players
		GPlayer* Match::GetPlayers() { return mPlayers;  }

		// Get wall, index-based
		SDL_Rect GetWall(int index) { return Walls[index]; }
		int WallCount() { return sizeof(Walls); }

		// End the match
		void EndMatch();
		// Garbage disposal
		void Dispose();
	};

}
