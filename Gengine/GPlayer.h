#pragma once
#include <GActor.h>
#include <SDL.h>
#include <string.h>

namespace Gengine
{
	class GPlayer : public Gengine::GActor
	{
	public:
		GPlayer::GPlayer()
 		{
			pName = "";
			pType = PLAYER;
			pController = NULL;
		}
		GPlayer::GPlayer(std::string name, SDL_Rect playingField)
		{
			pName = name;
			pType = PLAYER;
			pField = playingField;
		}
		~GPlayer() { }

		void Initialize(Gengine::ActorType act, GTexture texture, Match* match, SDL_Point pos);

		void Render(SDL_Renderer* renderer);

		void Handle(SDL_Event* ev);
		void Move();
		void Update(Uint32 ticks);

		void GPlayer::SetController(SDL_Joystick* joy) { pController = joy;  }
		void Dispose();
		void DisposeController();
		void CheckWalls();
	private:
		std::string pName;
		Gengine::ActorType pType;
		SDL_Rect pField;
		SDL_Rect pHitBox;
		SDL_Joystick* pController;

		SDL_Point pTurnThumb;

		
	};
}
