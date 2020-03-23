#include "States.h"
#include "Boid.h"

StateExploding::StateExploding()
{
}

StateExploding::~StateExploding()
{
}

void StateExploding::onEnter(Boid* _boid)
{
}

ENUMSTATES StateExploding::onUpdate(Boid* _boid)
{
	//_boid->player.addDamage(_damage);
	//destroy object
	return ENUMSTATES::EXPLOTINGSTATE;
}

void StateExploding::onExit(Boid* _boid)
{
}
