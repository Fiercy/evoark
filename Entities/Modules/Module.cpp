//
#include "Module.h"
#include "../Ships/Enemies/Coral.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../Graphics/Particles/ParticleSystem.h"
#include "../../SoundBox.h"
CModule::CModule()
{
	owner = nullptr;
	hullMax = 500;
	hull = hullMax;
}


CModule::~CModule()
{
}

void CModule::SetOwner(CCoral* newVal)
{
	if (owner == newVal)
		return;

	if (owner)
		owner->Release();

	owner = newVal;

	if (owner)
		owner->AddRef();
}

void CModule::Update(float dt)
{
	if (damaged > 0)
		damaged -= dt;
	if (damaged < 0)
		damaged = 0;

	timer += dt;
	SGD::Vector rotatedOffset = posOffset;
	rotatedOffset.Rotate(owner->GetRotation());
	position = owner->GetPosition() + rotatedOffset;

	rotation = owner->GetRotation() + rotOffset;
}

void CModule::Render()
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

void CModule::TakeDamage(int damage, bool collision)
{
	damage -= owner->RequestShield(damage);
	if (collision)
		damage = int((float)damage * COLLISION_MODIFIER);
	hull -= damage;
	damaged = .15f;
	if (hull <= 0)
	{

		if (this->GetType() == (int)EntityType::BaseModule)
		{
			if (owner->GetType() == (int)EntityType::Coral)
			{
				CSoundBox::GetInstance()->Play(CSoundBox::sounds::cExplosion, false);
				CParticleSystem::GetInstance()->AddEmitter(23, this);
				CParticleSystem::GetInstance()->AddEmitter(24, this);
				CParticleSystem::GetInstance()->AddEmitter(25, this);
				CParticleSystem::GetInstance()->RemoveEmitter(this);
			}

			if (owner->GetType() == (int)EntityType::Moccasin)
			{
				CSoundBox::GetInstance()->Play(CSoundBox::sounds::bossExplosion, false);
				CParticleSystem::GetInstance()->AddEmitter(26, this);
				CParticleSystem::GetInstance()->AddEmitter(27, this);
				CParticleSystem::GetInstance()->RemoveEmitter(this);
			}
		}

		SelfDestruct();
	}
}

void CModule::Activate()
{

}

void CModule::ReleaseOwner()
{
	if (!owner)
		return;
	owner->Release();
}

void CModule::SelfDestruct()
{
	owner->DestroyModule(this);
}