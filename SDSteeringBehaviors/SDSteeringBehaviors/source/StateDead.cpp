#include <States.h>
#include <Boid.h>

StateDead::StateDead()
{
}

StateDead::~StateDead()
{
}

void StateDead::onEnter(Boid* _boid)
{
	_boid->m_isDead = true;
}

ENUMSTATES StateDead::onUpdate(Boid* _boid)
{
	return ENUMSTATES::DEADSTATE;
}

void StateDead::onExit(Boid* _boid)
{
}
