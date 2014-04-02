//
#include "Enemy.h"
#include "../../../Event System/EventID.h"
#include "../../../Event System/CustomEvent.h"
#include "../../../GameStates/Game.h"
#include "../../../Event System/EventManager.h"
#include "../../../Message System/CreateProjectile.h"
#include "../../../SGD Wrappers/SGD_GraphicsManager.h"
CEnemy::CEnemy()
{
	CEventManager::GetInstance().Register(dynamic_cast<Listener*>(this), EventID::position);
}


CEnemy::~CEnemy()
{
	CEventManager::GetInstance().Unregister(dynamic_cast<Listener*>(this), EventID::position);
}

void CEnemy::Update(float dt)
{
	if (damaged > 0)
		damaged -= dt;
	if (damaged < 0)
		damaged = 0;

	if (target)
	{
		SGD::Vector tarDir = target->GetPosition() - position;
		tarDir.Normalize();
		rotateToward(tarDir, dt);
	}

	//Comment out later:
	if (target)
	{
		SGD::Vector dir = target->GetPosition() - position;
		if (dir.ComputeLength() > 100)
		{
			dir.Normalize();
			velocity = dir * speed;
		}
		else velocity = {0,0};
	}
	else
	{
		velocity = { 0, 0 };
	}
}

void CEnemy::Render()
{
	SGD::Size scale = SGD::Size{ size.width / imageSize.width, size.height / imageSize.height };
	//CCamera* cam = Game::GetInstance()->GetLevelState()->GetCam();
	//SGD::GraphicsManager::GetInstance()->DrawTextureSection(image, position - size/2, SGD::Rectangle(SGD::Point{0,0},imageSize), rotation, imageSize / 2, SGD::Color{}, SGD::Size{scale, scale});
	SGD::Point renderPoint = offsetToCamera();
	//SGD::GraphicsManager::GetInstance()->DrawTextureSection(image, renderPoint,SGD::Rectangle{SGD::Point{0,0}, imageSize}, rotation, imageSize/2, {}, scale);
	SGD::Color col = {};
	if (damaged > 0)
	{
		col = { 155, 155, 155 };
	}
	SGD::GraphicsManager::GetInstance()->DrawTexture(image, renderPoint, rotation, imageSize / 2, col, scale);
}

void CEnemy::SetTarget(CShip* newTarget)
{
	if (target == newTarget)
		return;

	if (target)
		target->Release();

	if (newTarget)
		newTarget->AddRef();

	target = newTarget;
}

void CEnemy::HandleEvent(CCustomEvent* e)
{
	EventID id = e->GetID();
	switch (id)
	{
	case EventID::position:
	{
							  IEntity* other = dynamic_cast<IEntity*> (e->GetSender());
							  EntityType otherType = (EntityType)other->GetType();
							  if (otherType == EntityType::Human || otherType == EntityType::Player)
								  DetectShip(dynamic_cast<CShip*>(other));

							  //detect projectiles and collidables
							  break;							  
	}
	}
}

void CEnemy::DetectShip(CShip* other)
{
	SGD::Point pos = other->GetPosition();
	SGD::Vector toTarget = pos - position;

	SGD::Vector forward = { 0, -1 };
	forward.Rotate(rotation);
	//"delta rotation" the amount of rotation it will take to face the target.
	float angle = forward.ComputeAngle(toTarget);
	if (angle >= SGD::PI / 4.0f)
		return;

	float distance = toTarget.ComputeLength();
	if (distance >= SGD::Vector{ (float)Game::GetInstance()->GetScreenWidth(), (float)Game::GetInstance()->GetScreenHeight() }.ComputeLength() * 0.25f)
		return;

	SetTarget(other);

}

void CEnemy::TakeDamage(int damage, bool collision)
{
	//if (shield > 0)
	//{
	//	shield -= damage;
	//	damage -= shield;
	//}
	//
	//if (damage <= 0)
	//{
	//	return;
	//}
	if (collision)
		damage *= COLLISION_MODIFIER;
	hull -= damage;
	damaged = .15f;
	if (hull <= 0)
	{

		SelfDestruct();
	}
}

