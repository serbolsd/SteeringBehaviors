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
	_boid->m_timeToChasing += _boid->m_elapsedTime;
}

ENUMSTATES Statechasing::onUpdate(Boid* _boid)
{
	if (_boid->m_elapsedTime< _boid->m_timeToChasing)
	{
		_boid->m_myDesc.shapeColor.r += 15;
		_boid->m_myDesc.shapeColor.b -= 15;
		_boid->m_shape.setFillColor( _boid->m_myDesc.shapeColor);
		return ENUMSTATES::CHASINGSTATE;
	}
	switch (_boid->getTypeBoid())
	{
	case TYPEBOID::TANK:
		if (_boid->isPlayerNear(_boid->m_myDesc.pPlayer))
		{
			return ENUMSTATES::EXPLOTINGSTATE;
		}
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