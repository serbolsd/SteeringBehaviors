#include "States.h"
#include "Boid.h"

StateShooting::StateShooting()
{
}

StateShooting::~StateShooting()
{
}

void StateShooting::onEnter(Boid* _boid)
{
}

ENUMSTATES StateShooting::onUpdate(Boid* _boid)
{
	if (!_boid->playerInRange(_boid->m_myDesc.pPlayer, _boid->m_myDesc.ratioToLooking))
		return ENUMSTATES::LOOKINGSTATE;
	_boid->rotateToObjetive(_boid->m_myDesc.pPlayer);
	if (_boid->lookingForPlayer(_boid->m_myDesc.pPlayer, _boid->m_myDesc.AngleToLookingInDegrees, _boid->m_myDesc.ratioToLooking))
	{

	}

	return ENUMSTATES::SHOOTINGSTATE;
}

void StateShooting::onExit(Boid* _boid)
{
	_boid->m_timeToRotate = _boid->m_elapsedTime + _boid->m_constTimeToRotate;
	_boid->goingToPos = false;
	_boid->m_waitingForNexRotate = true;
}
