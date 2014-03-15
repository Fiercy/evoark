#pragma once
#include "Flyweight.h"
#include "../../SGD Wrappers/SGD_Color.h"
#include "../../SGD Wrappers/SGD_Geometry.h"
class CParticle
{
private:
	//CFlyweight * particleInfo;
	SGD::Color curColor;
	SGD::Point curPosition;
	float      m_fCurLife;
	float      m_fCurVelX;
	float      m_fCurVelY;
	float      m_fCurScale;







public:
	CParticle();
	CParticle(SGD::Color cColor, SGD::Point cPosition, 
		float CurLife,
		float CurVelX, float CurVelY, 
		float CurScale
		);


	virtual ~CParticle();





	//CFlyweight* GetParticleInfo(){ return particleInfo; }


	SGD::Color GetCurColor() { return curColor; }
	SGD::Point GetCurPos()   { return curPosition; }

	float GetCurLife()       { return m_fCurLife; }
	//float GetEndLife()       { return m_fEndLife; }

	float GetCurVelX()       { return m_fCurVelX; }
	float GetCurVelY()       { return m_fCurVelY; }
	float GetCurScale()      { return m_fCurScale; }

	void SetCurColor(SGD::Color c) { curColor = c; }
	void SetCurPos(SGD::Point p)   { curPosition = p; }

	void SetCurLife(float sLife)    { m_fCurLife = sLife; }
	//void SetEndLife(float eLife)    { m_fEndLife = eLife; }


	void SetCurVelX(float velX)    { m_fCurVelX = velX; }
	void SetCurVelY(float velY)    { m_fCurVelY = velY; }
	void SetCurScale(float scale)  { m_fCurScale = scale; }


};
