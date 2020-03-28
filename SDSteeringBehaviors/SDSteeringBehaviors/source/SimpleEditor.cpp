#include <SimpleEditor.h>

SimpleEditor::SimpleEditor()
{
}

SimpleEditor::~SimpleEditor()
{
}

void SimpleEditor::Init(const float& windlength, const float& windWidth,float *_deltaTime)
{
	playerDesc.globalTime = _deltaTime;
	playerDesc.Direction = { 0 ,0 };
	playerDesc.Position = { windlength/2,windlength/2 };
	playerDesc.Speed = 10;
	playerDesc.ratio = 10;
	playerDesc.masa = 0.7;
	playerDesc.seek.impetu = 10;
	playerDesc.ptr_obstacles = &m_vectorpObstacles;
	playerDesc.obstacleEvadeDimentions.impetu = 15;
	//playerDesc.pStateMachine = &g_stateMachine;
	playerDesc.BoidType = TYPEBOID::PLAYER;
	playerDesc.pWalls = &m_vectorpWalls;
	m_player->Init(playerDesc);
}

void SimpleEditor::Update()
{
}

void SimpleEditor::render(sf::RenderWindow& _wind)
{
}

void SimpleEditor::onDelete()
{
}
