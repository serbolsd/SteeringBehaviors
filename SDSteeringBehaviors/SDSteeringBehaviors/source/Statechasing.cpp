#include "States.h"
#include "Boid.h"

Statechasing::Statechasing()
{
}

Statechasing::~Statechasing()
{
}

void Statechasing::onEnter(Boid* _boid)
{
}

ENUMSTATES Statechasing::onUpdate(Boid* _boid)
{
	switch (_boid->getTypeBoid())
	{
	case TYPEBOID::TANK:
		_boid->newDirection += _boid->persu(_boid->m_myDesc.pPlayer->getPosition(),
			_boid->m_myDesc.pPlayer->getDirection(),
			_boid->m_myDesc.pPlayer->getSpeed(),
			_boid->m_myDesc.persu.timeProyection,
			_boid->m_myDesc.persu.impetu);
		_boid->updateForWalking();
		break;
	case TYPEBOID::SCIENTIFIC:
		break;
	default:
		break;
	}
	return ENUMSTATES::CHASINGSTATE;
}

void Statechasing::onExit(Boid* _boid)
{
}