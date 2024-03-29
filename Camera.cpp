#include "Camera.h"
#include "GameStates\ILevelState.h"
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
		screen.width = (float)Game::GetInstance()->GetScreenWidth();
		screen.height = (float)Game::GetInstance()->GetScreenHeight();
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

void CCamera::clamp()
{
	SGD::Size world = Game::GetInstance()->GetLevelState()->GetWorldSize();
	SGD::Rectangle box = GetBoxInWorld();
	
	if (box.left < 0)
	{
		pos.x = 0;
	}

	if (box.top < 0)
	{
		pos.y = 0;
	}

	if (box.right > world.width)
	{
		pos.x = world.width - screenSize.width;
	}

	if (box.bottom > world.height)
	{
		pos.y = world.height - screenSize.height;
	}
}

void CCamera::Update(float dt)
{
	if (state != camState::initiallized )
		return;

	//if (locked)
	//{
	//	pos = target->GetPosition() - screenSize/2;
	//	clamp();
	//	return;
	//}

	SGD::Point tPos = target->GetPosition();
	//SGD::Vector mOffset = GetOffset();
	SGD::Vector mOffset = SGD::Vector{ screenSize.width, screenSize.height } / -2;
	SGD::Point dest = tPos + mOffset;//target->GetPosition() + GetOffset();

	//if (target->GetPosition().x < Game::GetInstance()->GetScreenWidth() * .5f ||
	//	target->GetPosition().x > Game::GetInstance()->GetLevelState()->GetWorldSize().width - Game::GetInstance()->GetScreenWidth() * .5f ||
	//	target->GetPosition().y < Game::GetInstance()->GetScreenHeight() * .5f ||
	//	target->GetPosition().y > Game::GetInstance()->GetLevelState()->GetWorldSize().height - Game::GetInstance()->GetScreenHeight() * .5f)
	//	return;	

	if (pos == dest)
		return;
	
	SGD::Vector dir = dest - pos;
	dir.Normalize();
	dir *= speed;
	SGD::Point newPos = pos + dir*dt;

	float val = (newPos - dest).ComputeLength();

	if (abs(val) <= 5.0f)
	{
		pos = dest;
		//locked = true;
	}
	else
	{
		pos = newPos;
	}

	clamp();
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

	//locked = false;
}
