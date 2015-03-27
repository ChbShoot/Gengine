#pragma once
#include <Constants.h>
#include <GActor.h>

namespace Gengine
{
	class GBall : public GActor
	{

		const int DEFAULT_BALL_WIDTH = 15;
	public:
		GBall();
		GBall(int x, int y);
		GBall(int width, int x, int y);
		~GBall();
	private:
	    double bDegrees;
		Circle bHitBox;
	};
}
