//
#include "TurretModule.h"
#include "../../Message System/CreateProjectile.h"
#include "../Ships/Enemies/Coral.h"

CTurretModule::CTurretModule()
{
	rotSpeed = SGD::PI;
	target = nullptr;
}


CTurretModule::~CTurretModule()
{
}

void CTurretModule::SetTarget(CShip* newTarget)
{
	if (target == newTarget)
		return;

	if (target)
		target->Release();

	target = newTarget;

	if (target)
		target->AddRef();
}

void  CTurretModule::Update(float dt)
{
	//Rotate toward target
	if (target)
	{
		SGD::Vector toTarget = target->GetPosition() - position;
		CEntity::rotateToward(toTarget, dt);

		rotOffset = rotation - owner->GetRotation();
	}
	CModule::Update(dt);
}
