#include "States.h"
#include "Boid.h"

Statechasing::Statechasing()
{
}

Statechasing::~Statechasing()
{
}

State* Statechasing::update(Boid* _boid)
{
	prepare();
	//if (_boid->inRangePlayer)
	//{
	//	return new StateExploding();
	//}
	//persu player;
	return new Statechasing();
}
