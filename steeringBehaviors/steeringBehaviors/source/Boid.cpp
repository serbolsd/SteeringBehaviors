#include "Boid.h"

Boid::Boid()
{
}

Boid::~Boid()
{
}

CD::CDVector2 Boid::seek(CD::CDVector2 PosA, CD::CDVector2 PosB, float Impetu)
{
	CD::CDVector2 Dir = PosB - PosA;
	Dir.normalize();
	CD::CDVector2 F = Dir * Impetu;
	return F;
}

CD::CDVector2 Boid::flee(CD::CDVector2 PosA, CD::CDVector2 PosB, float Impetu)
{
	CD::CDVector2 Dir = PosA - PosB;
	Dir.normalize();
	CD::CDVector2 F = Dir * Impetu;
	return F;
}

CD::CDVector2 Boid::fleeRatio(CD::CDVector2 PosA, CD::CDVector2 PosB, float Impetu, float ratio)
{
	CD::CDVector2 Dir = PosA - PosB;
	CD::CDVector2 F = {0,0};
	if (Dir.length()>ratio)
	{
		Dir.normalize();
		F = Dir * Impetu;
	}
	return F;
}

CD::CDVector2 Boid::arrive(CD::CDVector2 PosA, CD::CDVector2 PosB, float Impetu, float ratio)
{
	CD::CDVector2 Dir = PosB - PosA;
	float tempImpetu = Impetu;
	if (Dir.length()<ratio)
	{
		Impetu = Dir.length() / ratio;
	}
	Dir.normalize();
	CD::CDVector2 F = Dir * Impetu;
	return F;
}

CD::CDVector2 Boid::persu(CD::CDVector2 PosA, CD::CDVector2 PosB, CD::CDVector2 DirB, float speedB, float TimeProyection, float Impetu)
{
	CD::CDVector2 PP = ( DirB * speedB * TimeProyection ) + PosB;
	CD::CDVector2 Dir = PosB - PosA;
	Dir.normalize();
	CD::CDVector2 F = Dir * Impetu;
	return F;
}
