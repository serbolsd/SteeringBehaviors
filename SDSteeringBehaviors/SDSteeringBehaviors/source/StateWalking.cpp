#include "States.h"
#include "Boid.h"

StateWalking::StateWalking()
{
}

StateWalking::~StateWalking()
{
}

void StateWalking::onEnter()
{
}

ENUMSTATES StateWalking::onUpdate(Boid* _boid)
{
	if (_boid->getDirection() == CD::CDVector2(0, 0))
	{
		return ENUMSTATES::IDLESTATE;
	}
	return ENUMSTATES::WALKINGSTATE;
}

void StateWalking::onExit()
{
}
