#include "States.h"
#include "Boid.h"

StateLooking::StateLooking()
{
}

StateLooking::~StateLooking()
{
}

void StateLooking::onEnter(Boid* _boid)
{
}

ENUMSTATES StateLooking::onUpdate(Boid* _boid)
{
	//if (_boid->IsWatchingPlayer)
	//{
	//	return ENUMSTATES::SHOOTINGSTATE;
	//}
	return ENUMSTATES::LOOKINGSTATE;
}

void StateLooking::onExit(Boid* _boid)
{
}