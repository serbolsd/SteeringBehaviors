#include "States.h"
#include "Boid.h"

StateExploding::StateExploding()
{
}

StateExploding::~StateExploding()
{
}

void StateExploding::onEnter()
{
}

ENUMSTATES StateExploding::onUpdate(Boid* _boid)
{
	//_boid->player.addDamage(_damage);
	//destroy object
	return ENUMSTATES::EXPLOTINGSTATE;
}

void StateExploding::onExit()
{
}
