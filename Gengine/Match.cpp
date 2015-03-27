#pragma once
#include "Match.h"


namespace Gengine
{

	Match::Match()
	{
		// Our match has two horizontal walls at the top and bottom
		//////////////////////////////////////////////////////////////////////////




		// |                                                                  | //



		//////////////////////////////////////////////////////////////////////////

		// TOP
		Walls[0].h = 50;
		Walls[0].w = Gengine::SCREEN_WIDTH;
		Walls[0].x = 0;
		Walls[0].y = 0;

		// BOTTOM
		Walls[1].h = 50;
		Walls[1].w = Gengine::SCREEN_WIDTH;
		Walls[1].x = 0;
		Walls[1].y = Gengine::SCREEN_HEIGHT - Walls[1].h;

	}

	Match::~Match()
	{
	}

	void Match::Initialize(Uint32 duration, int scoreLimit, GTexture* backGround)
	{
		mDuration = duration;
		mScoreLimit = scoreLimit;
		mBackground = backGround;
	}

	void Match::CountDown(int delay)
	{
		GTimer cd = GTimer();
		cd.Start();
		while (cd.GetTicks() < (delay * 1000))
		{
			//////////////////////////////////////////////////////////////////////////
			// TODO: Do the actual countdown nonesense
			//////////////////////////////////////////////////////////////////////////
		}
		StartMatch();
	}

	// Start the match
	void Match::StartMatch()
	{
		mStartTime = SDL_GetTicks();

		SetRunning(true);
	}

	void Match::Render(SDL_Renderer* renderer)
	{
		// Render background first
		mBackground->Render(renderer, 0, 0);
		// Local player second, fix this with more actors
		//////////////////////////////////////////////////////////////////////////
		// TODO: Make actual array of actors and loop
		//////////////////////////////////////////////////////////////////////////
		mPlayers[0].Render(renderer);

		// Draw our walls
		if (sizeof(Walls) > 0)
		{
			for (int i = 0; i < sizeof(Walls) / sizeof(Walls[0]); i++)
			{
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderFillRect(renderer, &Walls[i]);
			}
		}
	}

	void Match::Update()
	{
		// End match, debug unused
		//if ((SDL_GetTicks() - mStartTime) >= mDuration)
		{
			//			printf("Game over");
			//EndMatch();
		}
		// Update current player
		mPlayers[0].Update(SDL_GetTicks() - mStartTime);
	}

	void Match::Handle(SDL_Event* ev)
	{
		// Make sure we have players to hand stuff
		if (GetRunning() && sizeof(mPlayers) > 0)
		{
			// If its a joystick, handle
			if (ev->type == SDL_JOYDEVICEADDED || ev->type == SDL_JOYDEVICEREMOVED || ev->type == SDL_JOYAXISMOTION)
				HandleJoystick(ev);
		}
	}

	void Match::HandleJoystick(SDL_Event* ev)
	{
		// Added joystick
		if (ev->type == SDL_JOYDEVICEADDED)
		{
			SDL_JoyDeviceEvent* e = (SDL_JoyDeviceEvent*)ev;
			SDL_Joystick* joystick = SDL_JoystickOpen(e->which);
			if (joystick)
			{
				mPlayers[(int)e->which].SetController(joystick);
			}
			else
			{
				printf("SDL_JOYDEVICEADDED FAILED\n");
			}
		}
		// Remove joystick
		if (ev->type == SDL_JOYDEVICEREMOVED)
		{
			SDL_JoyDeviceEvent* e = (SDL_JoyDeviceEvent*)ev;
			mPlayers[(int)e->which].DisposeController();
		}
		// Joystick thumbstick motion
		if (ev->type == SDL_JOYAXISMOTION)
		{
			mPlayers[((SDL_JoyAxisEvent*)ev)->which].Handle(ev);
		}
	}

	// Score 1 point on scoreActor
	void Match::Score(Gengine::GActor* scoreActor)
	{
		/////////////////////////////////////////////////////////////////////////
		// TODO: actually add scoring system
		//////////////////////////////////////////////////////////////////////////
	}

	void Match::EndMatch()
	{
		// End the match
		SetRunning(false);
	}

	void Match::Dispose()
	{
		if (sizeof(mPlayers) > 0 && !GetRunning())
		{
			mPlayers[0].Dispose();
		}
	}

	void Match::SetLocal(GPlayer player)
	{
		// Our 0-index is always our local player
		mPlayers[0] = player;
	}

}
