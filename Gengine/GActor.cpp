#include <GActor.h>

namespace Gengine
{
	int ACTOR_VEL = 5;
	const bool DEBUG = true;

	GActor::GActor()
	{
		aPosition = { 0, 0 };
		aVelocity = { 0, 0 };
		aDegrees = 0;
		aMatch = NULL;

		aDirection = RIGHT;
		aOffSet = 0;
	}


	GActor::~GActor()
	{

	}

	void GActor::Initialize(Gengine::ActorType act, GTexture texture, Match* match, SDL_Point pos)
	{
		aType = act;
		aTexture = texture;
		aPosition = pos;
		aVelocity = { 0, 0 };
		aMatch = match;
	}

	void GActor::Render(SDL_Renderer* renderer)
	{
		//aTexture.Render(renderer, aPosition.x, aPosition.y, );
		//aTexture.Render(renderer, aPosition.x, aPosition.y, 0);
	}

	// TODO:
	///
	void GActor::Move()
	{

	}

	bool GActor::CheckCollision(SDL_Rect aRect, SDL_Rect bRect)
	{
		int aLeft, aRight, aTop, aBot;
		int bLeft, bRight, bTop, bBot;

		aLeft = aRect.x;
		aRight = aRect.x + aRect.w;
		aTop = aRect.y;
		aBot = aRect.y + aRect.h;

		bLeft = bRect.x;
		bRight = bRect.x + bRect.w;
		bTop = bRect.y;
		bBot = bRect.y + bRect.h;

		if (aBot <= bTop)
			return false;
		if (aTop >= bBot)
			return false;
		if (aRight <= aLeft)
			return false;
		if (aLeft >= bRight)
			return false;
		return true;
	}


	double GActor::GetDegreesMouse()
	{
		SDL_Point mouse;
		SDL_GetMouseState(&mouse.x, &mouse.y);

		SDL_Point delta;
		delta.x = aPosition.x;
		delta.y = aPosition.y;

		delta.x -= mouse.x;
		delta.y -= mouse.y;

		return (atan2(delta.y, delta.x)*180.00000 / 3.1416);
	}


	void GActor::Handle(SDL_Event* ev)
	{
		
	}


	void GActor::Dispose()
	{
		
		aTexture.Dispose();
	}

}
