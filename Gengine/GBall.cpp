#include "GBall.h"

namespace Gengine
{
	GBall::GBall(int width, int x, int y)
	{
		aPosition.x = x;
		aPosition.y = y;

		bHitBox.r = width;
		bHitBox.x = x;
		bHitBox.y = y;

		aVelocity.x = 0;
		aVelocity.y = 0;

	}


	GBall::GBall(int x, int y)
	{
		aPosition.x = x;
		aPosition.y = y;

		bHitBox.r = DEFAULT_BALL_WIDTH;
		bHitBox.x = x;
		bHitBox.y = y;

		aVelocity.x = 0;
		aVelocity.y = 0;
	}

	GBall::GBall()
	{
		aPosition.x = 0;
		aPosition.y = 0;

		bHitBox.r = DEFAULT_BALL_WIDTH;
		bHitBox.x = 0;
		bHitBox.y = 0;

		aVelocity.x = 0;
		aVelocity.y = 0;
	}

	GBall::~GBall()
	{
	}
}