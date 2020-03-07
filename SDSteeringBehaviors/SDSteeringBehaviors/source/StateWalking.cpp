#include "States.h"
#include "Boid.h"

StateWalking::StateWalking()
{
}

StateWalking::~StateWalking()
{
}

State* StateWalking::update(Boid* _boid)
{
	prepare();
	if (_boid->getDirection()==CD::CDVector2(0,0))
	{
		return new StateIdle();
	}
	return new StateWalking();
}
