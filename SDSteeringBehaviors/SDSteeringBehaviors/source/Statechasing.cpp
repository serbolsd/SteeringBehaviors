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
	return ENUMSTATES::CHASINGSTATE;
}

void Statechasing::onExit(Boid* _boid)
{
}