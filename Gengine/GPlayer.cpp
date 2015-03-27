#pragma once
#include <string.h>
#include <GPlayer.h>
#include <SDL.h>
#include <Match.h>
#include "GActor.h"

using namespace std;

namespace Gengine
{
	int PLAYER_SPEED;
	void GPlayer::Initialize(Gengine::ActorType act, GTexture texture, Match* match, SDL_Point pos)
	{
		GActor::Initialize(act, texture, match, pos);

		aTexture.SetClips(64, 84);

		pHitBox.x = pos.x;
		pHitBox.y = pos.y;
		pHitBox.h = texture.GetHeight();
		pHitBox.w = texture.GetWidth();

		aVelocity.x = 0;
		aVelocity.y = 0;

		pTurnThumb.x = 0;
		pTurnThumb.y = 0;

		PLAYER_SPEED = 1;

		aIndex = act;
	}

	void GPlayer::DisposeController()
	{
		
		if (pController != nullptr)
		{
//			SDL_JoystickClose(pController);
//			pController = nullptr;
		}
		
	}

	void GPlayer::Move()
	{
		aPosition.x += aVelocity.x;
		pHitBox.x = aPosition.x;
		aPosition.y += aVelocity.y;
		pHitBox.y = aPosition.y;

		CheckWalls();
	}

	void GPlayer::CheckWalls()
{
		for (int i = 0; i < aMatch->WallCount(); i++)
		{
			SDL_Rect checkRect = aMatch->GetWall(i);
			// LEFT MOST BOUND
			if (pHitBox.x < 0)
			{
				aPosition.x -= aVelocity.x;
				pHitBox.x = aPosition.x;
			}
			// RIGHT MOST BOUND
			if ((pHitBox.x + pHitBox.w) > pField.w)
			{
				aPosition.x -= aVelocity.x;
				pHitBox.x = aPosition.x;
			}

			// 50 == wall height top
			if (pHitBox.y < 50)
			{
				aPosition.y -= aVelocity.y;
				pHitBox.y = aPosition.y;
			}

			if ((pHitBox.h + pHitBox.y) > Gengine::SCREEN_HEIGHT - 51)
			{
				aPosition.y -= aVelocity.y;
				pHitBox.y = aPosition.y;
			}
		}
	}

	void GPlayer::Update(Uint32 ticks)
	{
		// Joystick stuff
		//aDegrees = (atan2((double)pTurnThumb.y, (double)pTurnThumb.x) * (180.0 / M_PI));

		//if (pTurnThumb.x == 0 && pTurnThumb.y == 0)
			//aDegrees = 0;
		aDegrees = GetDegreesMouse() + 90;
			
		Move();
	}

	void GPlayer::Handle(SDL_Event* ev)
	{
		if (ev->type == SDL_JOYAXISMOTION)
		{
			if (ev->jaxis.which == 0)
			{
				if (ev->jaxis.axis == 0)
				{
					if (ev->jaxis.value < -Gengine::JOYSTICK_DEAD_ZONE)
						aVelocity.x -= PLAYER_SPEED;
					else if (ev->jaxis.value > Gengine::JOYSTICK_DEAD_ZONE)
						aVelocity.x += PLAYER_SPEED;
					else
						aVelocity.x = 0;
				}

				if (ev->jaxis.axis == 1)
				{
					if (ev->jaxis.value < -Gengine::JOYSTICK_DEAD_ZONE)
						aVelocity.y -= PLAYER_SPEED;
					else if (ev->jaxis.value > Gengine::JOYSTICK_DEAD_ZONE)
						aVelocity.y += PLAYER_SPEED;
					else
						aVelocity.y = 0;
				}

				if (ev->jaxis.axis == 2)
				{
					if (ev->jaxis.value < -Gengine::JOYSTICK_DEAD_ZONE)
						pTurnThumb.x = -1;
					else if (ev->jaxis.value > Gengine::JOYSTICK_DEAD_ZONE)
						pTurnThumb.x = 1;
					else
						pTurnThumb.x = 0;
				}

				if (ev->jaxis.axis == 3)
				{
					if (ev->jaxis.value < -Gengine::JOYSTICK_DEAD_ZONE)
						pTurnThumb.y = -1;
					else if (ev->jaxis.value > Gengine::JOYSTICK_DEAD_ZONE)
						pTurnThumb.y = 1;
					else
						pTurnThumb.y = 0;
				}
			}
		}
	}

	void GPlayer::Render(SDL_Renderer* renderer)
	{
		//printf("Drawing player %s on X: %s, Y: %s\n", aIndex, aPosition.x, aPosition.y);
		//this->aTexture.Render(renderer, aPosition.x, aPosition.y,aDegrees, 0, SDL_FLIP_NONE);
		this->aTexture.Render(renderer, aPosition.x, aPosition.y, aDegrees + 90, 0, SDL_FLIP_NONE);
		SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
		SDL_RenderDrawRect(renderer, &pField);
	}

	void GPlayer::Dispose()
	{
		DisposeController();
	}

}