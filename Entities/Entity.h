#pragma once
#include "IEntity.h"
#include "../SGD Wrappers/SGD_Geometry.h"


//Entity, GravityProjectile, and Ship should all return BaseClass to let us know that the entity SHOULD have a more specific type.
enum class EntityType { BaseClass, Laser, Missile, Push, Well, Player, Human, Copperhead, Cobra, Mamba, Coral, Moccasin, Coordinator, Count };
class CEntity :
	public IEntity
{
protected:
	SGD::HTexture image = SGD::INVALID_HANDLE;
	SGD::Point position = SGD::Point{0,0};
	SGD::Vector velocity = SGD::Vector{0,0};
	SGD::Vector gravVec = SGD::Vector{ 0, 0 };
	float rotation = 0.0f;
	SGD::Size size = SGD::Size{ 16, 16 };
	SGD::Size imageSize = SGD::Size{383, 415};
	unsigned int refCount = 1;

public:
	CEntity();
	virtual ~CEntity();

	virtual void Update(float dt) override;
	virtual void Render() override;

	//Accessors
	virtual int				GetType() override {return (int)EntityType::BaseClass;}
	virtual SGD::HTexture	GetImage() override {return image;}
	virtual SGD::Point		GetPosition() {return position;}
	virtual SGD::Vector		GetVelocity() override { return velocity; }
	virtual float			GetRotation() override { return rotation; }
	virtual SGD::Size		GetSize()	  override { return size; }
	virtual SGD::Vector		GetGravVec() override {return gravVec;}

	//Mutators
	virtual void SetImage(SGD::HTexture newImage)override {image = newImage;}
	virtual void SetPosition(SGD::Point newPos)	override {position = newPos;}
	virtual void SetVelocity(SGD::Vector newVel)override {velocity = newVel;}
	virtual void SetRotation(float newRot)		override {rotation = newRot;}
	virtual void SetSize(SGD::Size newSize)		override {size = newSize;}
	virtual void AddGravity(SGD::Vector grav) override {}

	virtual void HandleCollision() override;

	virtual void AddRef() final;
	virtual void Release() final;
};

