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
	//if (!_boid->playerInRange)
	//{
	//	return ENUMSTATES::LOOKINGSTATE;
	//}
	//intance bullet
	return ENUMSTATES::SHOOTINGSTATE;
}

void StateShooting::onExit(Boid* _boid)
{
}
