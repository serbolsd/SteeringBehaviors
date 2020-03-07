#pragma once
#include "CDVectors.h"
class Boid;
class State
{
public:
	State();
	virtual ~State();
	virtual State* update(Boid* _boid) {};
	virtual void* prepare() { delete this; };
private:

};

class StateIdle :public State
{
public:
	StateIdle ();
	~StateIdle ();
	State* update(Boid* _boid) override;
private:
	

};

class Statechasing :public State
{
public:
	Statechasing();
	~Statechasing();
	State* update(Boid* _boid) override;
private:

};

class StateWalking :public State
{
public:
	StateWalking();
	~StateWalking();
	State* update(Boid* _boid) override;
private:

};

class StateShooting : public  State
{
public:
	StateShooting();
	~StateShooting();
	State* update(Boid* _boid) override;
private:

};

class StateExploding :public State
{
public:
	StateExploding();
	~StateExploding();
	State* update(Boid* _boid) override;
private:

};

class StateLooking :public State
{
public:
	StateLooking();
	~StateLooking();
	State* update(Boid* _boid) override;
private:

};