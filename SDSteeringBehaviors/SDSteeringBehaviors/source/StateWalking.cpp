#include "States.h"
#include "Boid.h"

StateWalking::StateWalking()
{
}

StateWalking::~StateWalking()
{
}

void StateWalking::onEnter(Boid* _boid)
{
}

ENUMSTATES StateWalking::onUpdate(Boid* _boid)
{
	if (_boid->getDirection() == CD::CDVector2(0, 0))
	{
		return ENUMSTATES::IDLESTATE;
	}
	CD::CDVector2 pointToSeek=_boid->getDirection()+_boid->getPosition();
	_boid->newDirection+=_boid->seek(pointToSeek, _boid->m_myDesc.seek.impetu);
	
	return ENUMSTATES::WALKINGSTATE;
}

void StateWalking::onExit(Boid* _boid)
{
}
