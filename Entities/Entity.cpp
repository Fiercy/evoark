//
#include "Entity.h"
#include "../SGD Wrappers/SGD_GraphicsManager.h"
#include <algorithm>
#include "../Camera.h"
#include "../GameStates/ILevelState.h"
#include "../GameStates/Game.h"
#include "../Message System/DestroyEntityMessage.h"
#include "../Event System/EventManager.h"
CEntity::CEntity()
{

}


CEntity::~CEntity()
{

}

SGD::Point CEntity::offsetToCamera()
{
	return (position - (size/2)) + CCamera::GetInstance()->GetOffset();
}

void CEntity::rotateToward(SGD::Vector direction, float dt)
{
	SGD::Vector up = SGD::Vector{ 0, -1 };
	SGD::Vector forward = up;
	forward.Rotate(rotation);

	float angleBetween = forward.ComputeAngle(direction);
	if (angleBetween > rotSpeed * dt)
		angleBetween = rotSpeed * dt;

	if (forward.ComputeSteering(direction) < 0)
		angleBetween = -angleBetween;

	rotation += angleBetween;

	if (rotation < 0)
		rotation += SGD::PI * 2;
	else if (rotation >= SGD::PI * 2)
		rotation -= SGD::PI * 2;
}

void	CEntity::Update(float dt)
{
	position += (velocity) * dt;
	position += gravVec * dt;
	Clamp();

	//Why is this here? It's not being used...
	//float gravSpeed = gravVec.ComputeLength();	
	//float mySpeed = velocity.ComputeLength();
	
	if (gravVec != SGD::Vector{ 0, 0 })
	{
		gravVec -= (gravVec * GRAVDECAY);
		if (gravVec.ComputeLength() <= 5)
		{
			gravVec = SGD::Vector{0,0};
		}
	}
}

void	CEntity::Render()
{

	SGD::Size scale = SGD::Size{size.width / imageSize.width, size.height / imageSize.height};
	//CCamera* cam = Game::GetInstance()->GetLevelState()->GetCam();
	//SGD::GraphicsManager::GetInstance()->DrawTextureSection(image, position - size/2, SGD::Rectangle(SGD::Point{0,0},imageSize), rotation, imageSize / 2, SGD::Color{}, SGD::Size{scale, scale});
	SGD::Point renderPoint = offsetToCamera();
	//SGD::GraphicsManager::GetInstance()->DrawTextureSection(image, renderPoint,SGD::Rectangle{SGD::Point{0,0}, imageSize}, rotation, imageSize/2, {}, scale);

	SGD::GraphicsManager::GetInstance()->DrawTexture(image, renderPoint, rotation, imageSize/2, {}, scale);

	//Paint rect
	//SGD::Rectangle colRect = GetRect();
	//colRect.Offset(CCamera::GetInstance()->GetOffset());
	//SGD::GraphicsManager::GetInstance()->DrawRectangle(colRect, SGD::Color(255, 0, 0));
}

void CEntity::SetImage(SGD::HTexture newImage)// {image = newImage;}
{
	image = newImage;
	SGD::GraphicsManager* graphics = SGD::GraphicsManager::GetInstance();
	//Why is this a vector?
	SGD::Vector texData = graphics->GetTextureData(image);
	imageSize = {texData.x, texData.y};
}

void	CEntity::HandleCollision(IEntity* other)
{
	//Should never collide with anything.
	//TODO: Review catch/throw, and throw an error here
}

void CEntity::Clamp()
{
	SGD::Size world = Game::GetInstance()->GetLevelState()->GetWorldSize();
	SGD::Rectangle box = GetRect();

	if (box.left < 0)
	{
		position.x = size.width/2;
	}

	if (box.top < 0)
	{
		position.y = size.height/2;
	}

	if (box.right > world.width)
	{
		position.x = world.width - size.width/2;
	}

	if (box.bottom > world.height)
	{
		position.y = world.height - size.height/2;
	}
}


void	CEntity::AddRef()
{
	refCount++;
}

void	CEntity::Release()
{
	refCount--;
	if (refCount <= 0)
		delete this;
	else
		refCount = refCount;
}

void CEntity::SelfDestruct()
{
	if (destroying)
		return;

	DestroyEntityMessage* msg = new DestroyEntityMessage(this);
	msg->QueueMessage();
	destroying = true;
	Listener* l = dynamic_cast<Listener*>(this);
	if (l)
		CEventManager::GetInstance().UnregisterAll(l);
}