/***************************************************************
|	File:		Game.cpp
|	Author:		
|	Course:		SGD 1401
|	Purpose:	Game class controls the SGD wrappers
|				& runs the game state machine
***************************************************************/

#include "Game.h"

#include "../SGD Wrappers/SGD_AudioManager.h"
#include "../SGD Wrappers/SGD_GraphicsManager.h"
#include "../SGD Wrappers/SGD_InputManager.h"
#include "../SGD Wrappers/SGD_String.h"
#include "../Graphics/Particles/ParticleSystem.h"
#include "../SoundBox.h"

//#include "BitmapFont.h"
#include "GameState.h"
#include "MainMenuState.h"
#include "GameplayState.h"

#include <shlwapi.h>
#pragma comment(lib,"shlwapi.lib")
#include "shlobj.h"
#include <ctime>
#include <cstdlib>
#include <cassert>
#include <fstream>
#include <string>
using std::ifstream;
using std::string;

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

//testing
#include "../BitmapFont/BitmapFont.h"


/**************************************************************/
// Singleton
//	- instantiate the static member
/*static*/ Game* Game::s_pInstance = nullptr;

// GetInstance
//	- allocate the ONE instance & return it
/*static*/ Game* Game::GetInstance( void )
{
	if (s_pInstance == nullptr)
		s_pInstance = new Game;

	return s_pInstance;
}

// DeleteInstance
//	- deallocate the ONE instance
/*static*/ void Game::DeleteInstance( void )
{
	delete s_pInstance;
	s_pInstance = nullptr;
}


/**************************************************************/
// Initialize
//	- initialize the SGD wrappers
//	- load resources / assets
//	- allocate & initialize the game entities
bool Game::Initialize( int width, int height )
{
	// Seed First!
	srand( (unsigned int)time( nullptr ) );
	rand();

	// Store the size parameters
	m_nScreenWidth	= width;
	m_nScreenHeight = height;

	// Store the SGD singletons
	m_pAudio	      = SGD::AudioManager::GetInstance();
	m_pGraphics	      = SGD::GraphicsManager::GetInstance();
	m_pInput	      = SGD::InputManager::GetInstance();

	// Initialize each singleton
	if(   m_pAudio->Initialize() == false 
	   || m_pGraphics->Initialize( false ) == false 
	   || m_pInput->Initialize() == false )
	{
		return false;
	}

	
	CSoundBox::GetInstance()->Enter();

	std::string path = GetAppDataPath() + "optionsSave.xml";
	TiXmlDocument doc(path.c_str());
	if (doc.LoadFile())
	{
		TiXmlElement* root = doc.RootElement();
		if (root)
		{
			int sfxVolume, musicVolume;

			root->Attribute("sfx", &sfxVolume);
			root->Attribute("music", &musicVolume);
			std::string fullscrn;
			fullscrn = root->Attribute("fullscreen");
			if (fullscrn == "true") m_bWindowed = false;
			else m_bWindowed = true;

			m_pAudio->SetMasterVolume(SGD::AudioManager::VolumeType::MASTER_SOUND_EFFECTS, sfxVolume * 10);
			m_pAudio->SetMasterVolume(SGD::AudioManager::VolumeType::MASTER_MUSIC, musicVolume * 10);
		}
	}

	m_pGraphics->Resize(SGD::Size{ (float)m_nScreenWidth, (float)m_nScreenHeight }, m_bWindowed);
	if (!m_bWindowed)
	{
		//RECT winSize;
		//GetWindowRect(, &winSize);

		HWND hWnd = FindWindowA("EvoArk", "EvoArk");
		RECT winSize;
		GetWindowRect(hWnd, &winSize);
		ClipCursor(&winSize);
	}
//	m_hSfxMusic = m_pAudio->LoadAudio("resource/audio/JDS_backgroundMusic.xwm");
//	m_pAudio->SetMasterVolume(SGD::AudioManager::VolumeType::MASTER_MUSIC, m_nVolMusic);
//	m_pAudio->PlayAudio(m_hSfxMusic,true);

	// Allocate & initialize the font
	//m_pFont = new BitmapFont;
	//m_pFont->Initialize();
	Font.Load("Resources/XML/font.xml");
	FontSmall.Load("Resources/XML/font1.xml");
	FontPoiret.Load("Resources/XML/fontPoiret.xml");
	// Start the game in the Main Menu state
	//ChangeState(CTestLevelState::GetInstance());
	PushState(CMainMenuState::GetInstance());

	// Store the current time (in milliseconds)
	m_ulGameTime	= GetTickCount();


	return true;	// success!
}


/**************************************************************/
// Main
//	- update the SGD wrappers
//	- update the game entities
//	- render the game entities
int Game::Main( void )
{
	if( m_pAudio->Update() == false 
	   ||m_pGraphics->Update() == false 
	   || m_pInput->Update() == false )
	{
		return -10;		// abort!
	}


	// Current time
	unsigned long now = GetTickCount();
	float elapsedTime = (now - m_ulGameTime) / 1000.0f;
	m_ulGameTime = now;

	// Cap the elapsed time to 1/8th of a second
	if( elapsedTime > 0.125f )
		elapsedTime = 0.125f;
#if !ARCADE
	if (m_pInput->IsKeyDown(SGD::Key::Alt) == true
		&& m_pInput->IsKeyPressed(SGD::Key::Enter) == true)
	{
		m_bWindowed = !m_bWindowed;
		m_pGraphics->Resize(SGD::Size{ (float)m_nScreenWidth, (float)m_nScreenHeight }, m_bWindowed);

		if (!m_bWindowed)
		{
			//RECT winSize;
			//GetWindowRect(, &winSize);
			
			HWND hWnd = FindWindowA("EvoArk", "EvoArk");
			RECT winSize;
			GetWindowRect(hWnd, &winSize);
			ClipCursor(&winSize);
		}

		return 0;
	}
#endif

	// Let the current state handle input
	if( m_qStates.back()->Input() == false )
		return 1;	// exit success!


	// Update & render the current state
	m_qStates[m_qStates.size()-1]->Update( elapsedTime );
	for (unsigned int i = 0; i < m_qStates.size(); i++)
	{
		m_qStates[i]->Render();
	}
	return 0;		// keep playing!
}


/**************************************************************/
// Terminate
//	- deallocate game entities
//	- unload resources / assets
//	- terminate the SGD wrappers
void Game::Terminate( void )
{
	while (!m_qStates.empty())
		PopState();

	Font.Unload();
	FontSmall.Unload();
	FontPoiret.Unload();
	// Exit the current state
	//while (!m_qStates.empty())
	//{

	//}

	// Terminate & deallocate the font
	//	m_pFont->Terminate();
	//	delete m_pFont;
	//	m_pFont = nullptr;


	//m_pAudio->UnloadAudio(m_hSfxMusic);
	CSoundBox::GetInstance()->Exit();

	// Terminate & deallocate the SGD wrappers
	m_pAudio->Terminate();
	m_pAudio = nullptr;
	SGD::AudioManager::DeleteInstance();
	
	m_pGraphics->Terminate();
	m_pGraphics = nullptr;
	SGD::GraphicsManager::DeleteInstance();

	m_pInput->Terminate();
	m_pInput = nullptr;
	SGD::InputManager::DeleteInstance();


}

/**************************************************************/
// ChangeState
//	- exit the current state to release resources
//	- enter the new state to allocate resources
//	- DANGER! Exiting the current state can CRASH the program!
//	  The state can ONLY be exited from the
//	  Input, Update, and Render methods!!!
//void Game::ChangeState( IGameState* pNewState )
//{
//	// Exit the old state
//	if( m_pCurrState != nullptr )
//		m_pCurrState->Exit();
//
//	// Store the new state
//	m_pCurrState = pNewState;
//
//	// Enter the new state
//	if( m_pCurrState != nullptr )
//		m_pCurrState->Enter();
//}

bool Game::PushState(IGameState* newState)
{
	if (!newState)
		//Why'd a null even get in here?? Account for everything.
		return false;
	m_qStates.push_back(newState);
	newState->Enter();
	return true;
}

void Game::PopState()
{
	m_qStates.back()->Exit();
	m_qStates.pop_back();
	//m_qStates.resize(m_qStates.size());
}

ILevelState* Game::GetLevelState()
{
	ILevelState* lState;
	for (unsigned int i = 0; i < m_qStates.size(); i++)
	{
		lState = dynamic_cast<ILevelState*>(m_qStates[i]);
		if (lState != nullptr)
			return lState;
	}
	return nullptr;
}

std::string Game::GetAppDataPath()
{
	HRESULT safeCheck;
	std::ostringstream oss;
	char path[MAX_PATH];
	LPWSTR wszPath = nullptr;
	size_t size;

	safeCheck = SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, 0, &wszPath);

	wcstombs_s(&size, path, MAX_PATH, wszPath, MAX_PATH);

	if (safeCheck == S_OK)
		oss << path;
	string pathToReturn = oss.str();

	pathToReturn += "\\Eclipse Games\\EvoArk\\";
	
	SHCreateDirectoryExA(nullptr, pathToReturn.c_str(), 0);

	return pathToReturn;
}