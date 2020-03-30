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
	_boid->applyDamageToPlayer(_boid->m_myDesc.pPlayer,_boid);
}

ENUMSTATES StateExploding::onUpdate(Boid* _boid)
{
	//quisa meter un temporizador
	//agregar estado de muerte
	return ENUMSTATES::DEADSTATE;
}

void StateExploding::onExit(Boid* _boid)
{

}
