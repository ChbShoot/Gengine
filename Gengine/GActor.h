#pragma once
#include <SDL.h>
#include <GTexture.h>

namespace Gengine
{
	class Match;
	enum ActorType
	{
		LOCAL,
		PLAYER,
		BALL
	};

	enum ActorFace
	{
		LEFT,
		RIGHT
	};


	///
	// Actors are any NPC/Player/Mob/Ball/Thing that moves and has a texture within the game. Maybe clouds will be actors too
	///
	class GActor
	{

	public:
		GActor();
		~GActor();
		// Initialize our actor with actor type, actor texture, playing match and position
		virtual void Initialize(Gengine::ActorType act, GTexture texture, Match* match, SDL_Point pos);
		// Render the actor
		virtual void Render(SDL_Renderer* renderer);
		// Handle the actor
		virtual void Handle(SDL_Event* ev);
		// Dispose the actor
		virtual void Dispose();
		// move the actor
		virtual void Move();

		double GetDegrees() { return aDegrees; }
		double GetDegreesMouse();
		GTexture* GetTexture() { return &aTexture;  }
		SDL_Point* GetPosition() { return &aPosition;  }
		SDL_Point* GetVelocity() { return &aVelocity; }
		bool CheckCollision(SDL_Rect aRect, SDL_Rect bRect);
		enum ActorType;
	protected:
		// aDirection: 0 = left, 1 = right
		ActorFace aDirection;
		int aOffSet;
		double aDegrees;
		int aIndex = aType;
		Gengine::ActorType aType;
		GTexture aTexture;
		SDL_Point aPosition;
		SDL_Point aVelocity;
		Match* aMatch;
	};
}
