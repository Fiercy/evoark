#include "Camera.h"
#include "GameStates\LevelStates\ILevelState.h"
#include "GameStates\Game.h"
CCamera::CCamera(IEntity* t = nullptr, SGD::Size screen = SGD::Size{})
{
	state = camState::unitiallized;
}

CCamera::~CCamera()
{
}

CCamera*	CCamera::GetInstance()
{
	static CCamera instance;
	return &instance;
}

bool		CCamera::Initiallize(IEntity* t, SGD::Size screen)
{
	if (state == camState::initiallized)
		return false;
	if (!t)
	{
		t = Game::GetInstance()->GetLevelState()->GetPlayer();
	}
	target = t;
	t->AddRef();

	if (screen == SGD::Size())
	{
		screen.width = Game::GetInstance()->GetScreenWidth();
		screen.height = Game::GetInstance()->GetScreenHeight();
	}
	screenSize = screen;
	pos = target->GetPosition();
	state = camState::initiallized;
	return true;
}

bool		CCamera::Terminate()
{
	if (state != camState::initiallized)
		return false;
	target->Release();
	state = camState::terminated;
	return true;
}

void CCamera::Update(float dt)
{
	if (state != camState::initiallized )
		return;

	SGD::Point tPos = target->GetPosition();
	//SGD::Vector mOffset = GetOffset();
	SGD::Vector mOffset = SGD::Vector{ screenSize.width, screenSize.height } / -2;
	SGD::Point dest = tPos + mOffset;//target->GetPosition() + GetOffset();

	if (pos == dest)
		return;
	
	SGD::Vector dir = dest - pos;
	dir.Normalize();
	dir *= speed;
	SGD::Point newPos = pos + dir*dt;
	if ((newPos - pos).ComputeLength() >= (dest - pos).ComputeLength())
	{
		pos = dest;
	}
	else
	{
		pos = newPos;
	}
}

void  CCamera::SetTarget(IEntity* t)
{
	if (state != camState::initiallized)
		return;
	if (!t)
		return;

	t->AddRef();
	target->Release();
	target = t;
}
