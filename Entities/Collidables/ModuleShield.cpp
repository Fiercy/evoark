#include "ModuleShield.h"
#include "../Ships/Ship.h"
#include "../Ships/Enemies/Moccasin.h"
#include "Asteroid.h"
#include "../Projectiles/Laser.h"
#include "../Modules/ShieldModule.h"
#include "../Ships/Ship.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"


void CModuleShield::Update(float dt)
{
	if (dynamic_cast<CShieldModule*>(m_pOwner)->GetShield() > 0)
	{
		position = m_pOwnerShip->GetPosition();
	}
}

void CModuleShield::HandleCollision(IEntity* other)
{
	//Is the other object a ship?
	if (dynamic_cast<CShieldModule*>(m_pOwner)->GetShield() > 0 )
	{
		if (other->GetType() == (int)EntityType::Laser || other->GetType() == (int)EntityType::Missile /*|| other->GetType() == (int)EntityType::Push*/ )
		{
			CLaser* l = dynamic_cast<CLaser*>(other);
			if (l->GetOwner() == m_pOwnerShip)
				return;
		}

		if (m_pOwnerShip->GetType() == (int)EntityType::Moccasin)
		{
			if (dynamic_cast<CMoccasin*>(m_pOwnerShip)->GetLevel() == 1)
			{
				if (other->GetType() == (int)EntityType::Asteroid)
				{
					dynamic_cast<CShieldModule*>(m_pOwner)->HandleCollision(other);
					other->HandleCollision(dynamic_cast<CShieldModule*>(m_pOwner));
				}
				else if (other->GetType() == (int)EntityType::Laser)
					other->SelfDestruct();
			}
			else
			{
				dynamic_cast<CShieldModule*>(m_pOwner)->HandleCollision(other);
				other->HandleCollision(dynamic_cast<CShieldModule*>(m_pOwner));
			}
			
		}
		else
		{
			dynamic_cast<CShieldModule*>(m_pOwner)->HandleCollision(other);
			other->HandleCollision(dynamic_cast<CShieldModule*>(m_pOwner));
		}	
	}
}

void CModuleShield::Render()
{
	if (dynamic_cast<CShieldModule*>(m_pOwner)->GetShield() > 0)
	{
		SGD::Size scale = SGD::Size{ size.width / imageSize.width, size.height / imageSize.height };
		SGD::Point renderPoint = offsetToCamera();
		SGD::GraphicsManager::GetInstance()->DrawTexture(image, renderPoint, rotation, imageSize / 2, {}, scale);
	}
}