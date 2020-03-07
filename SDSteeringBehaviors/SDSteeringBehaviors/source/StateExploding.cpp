#include "States.h"
#include "Boid.h"

StateExploding::StateExploding()
{
}

StateExploding::~StateExploding()
{
}

State* StateExploding::update(Boid* _boid)
{
	prepare();
	
	//_boid->player.addDamage(_damage);
	//destroy object
}
