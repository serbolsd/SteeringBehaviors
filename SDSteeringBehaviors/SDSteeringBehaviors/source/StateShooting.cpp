#include "States.h"
#include "Boid.h"

StateShooting::StateShooting()
{
}

StateShooting::~StateShooting()
{
}

State* StateShooting::update(Boid* _boid)
{
	prepare();
	//if (!_boid->playerInRange)
	//{
	//	return new StateLooking();
	//}
	//intance bullet
	return new StateShooting();
}
