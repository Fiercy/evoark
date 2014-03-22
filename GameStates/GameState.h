#pragma once
#include "IGameState.h"
#include "../SGD Wrappers/SGD_Handle.h"
#include "../Entities/EntityManager.h"
#include "../SGD Wrappers/SGD_Geometry.h"
#include "../SGD Wrappers/SGD_Color.h"
#include "../Entities/Ships/Player.h"
#include <vector>
#include <string>
#include "../Graphics/Particles/ParticleSystem.h"
#include "../SGD Wrappers/SGD_Message.h"

class CFlyweight;
class CEmitter;
class CParticleSystem;


class CTestLevelState :
	public IGameState
{
public:
	static CTestLevelState* GetInstance(void);


	virtual void	Enter(void)				override;
	virtual void	Exit(void)				override;
	virtual bool	Input(void)				override;
	virtual void	Update(float dt)	override;
	virtual void	Render(void)				override;
	static void MessageProc(const SGD::Message* msg);



private:

	CTestLevelState();
	virtual ~CTestLevelState();

	int m_nScreenHeight = 0;
	int m_nScreenWidth = 0;
	SGD::HTexture BackgroundImage;
	CEntityManager* EntityManager;
	SGD::GraphicsManager* graphics;

	CEntity* player = nullptr;

	// level creation
	enum Objects { PLAYER, COPPERHEAD, COBRA, MAMBA, CORAL, MOCASSIN, ASTEROID, NONE, NUM_OBJECTS };

	struct Quadrant
	{
		int x;
		int y;
		int possibleObjects;
		Objects objType;
		int objectAmount;
	};

	void		Generate();
	int m_nQuadWidth = 0;
	int m_nQuadHeight = 0;
	int m_nNumQuadsWidth = 0;
	int m_nNumQuadsHeight = 0;

	typedef std::vector<Quadrant> QuadCol;
	typedef std::vector<QuadCol> World;
	//QuadRow quadRow;
	World world;
	



	// xml test
	bool	LoadXMLLevel(const char* pXMLFile);
	
	

	CParticleSystem pSystem;


};

