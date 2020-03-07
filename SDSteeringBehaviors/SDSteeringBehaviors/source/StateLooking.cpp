#include "States.h"
#include "Boid.h"

StateLooking::StateLooking()
{
}

StateLooking::~StateLooking()
{
}

State* StateLooking::update(Boid* _boid)
{
	prepare();
	//if (_boid->IsWatchingPlayer)
	//{
	//	return new StateShooting();
	//}
	return new StateLooking();
}
