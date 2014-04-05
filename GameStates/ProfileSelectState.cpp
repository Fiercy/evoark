#include "ProfileSelectState.h"
#include "../SGD Wrappers/SGD_InputManager.h"
#include "../SGD Wrappers/SGD_GraphicsManager.h"
#include "Game.h"
#include "../BitmapFont/BitmapFont.h"
#include "MainMenuState.h"
#include <string>

CProfileSelectState* CProfileSelectState::GetInstance()
{
	static CProfileSelectState instance;
	return &instance;
}

void CProfileSelectState::Enter()
{
	LoadProfiles();
	currentProfile = 0;
	renderedProfile = 0;
	transTimer = transDuration;
	state = MyState::Idle;

	font.Load("Resources/XML/font1.xml");
	std::vector<std::string> labels;
	labels.push_back("Play");
	labels.push_back("Create New");
	labels.push_back("Delete");
	labels.push_back("Cancel");
	labels.push_back("Main Menu");
	menu = new CMenu(&font,labels,"");
}

void CProfileSelectState::Exit()
{
	if (confirm)
	{
		delete confirm;
		confirm = nullptr;
	}
	delete menu;
	menu = nullptr;
	font.Unload();
}

bool CProfileSelectState::Input()
{
	if (state >= MyState::Menu)
		MenuInput();
	else
		SeletionInput();
	return true;
}

void CProfileSelectState::SeletionInput()
{
	SGD::InputManager* input = SGD::InputManager::GetInstance();
	if (input->IsKeyPressed(SGD::Key::RightArrow))
	{
		if (currentProfile >= 2)
			currentProfile = 0;
		else
			currentProfile++;
		state = MyState::Transition;
		transTimer = 0;
	}
	if (input->IsKeyPressed(SGD::Key::LeftArrow))
	{
		if (currentProfile <= 0)
			currentProfile = 2;
		else
			currentProfile--;
		state = MyState::Transition;
		transTimer = 0;
	}
	if (input->IsKeyPressed(SGD::Key::Enter))
	{
		state = MyState::Menu;
	}
}

void CProfileSelectState::MenuInput()
{
	if (state == MyState::ConfirmOverwrite)
	{
		switch (confirm->Input())
		{
		case 0:
		{
			delete confirm;
			confirm = nullptr;
			CGameplayState::GetInstance()->DeleteProfile(currentProfile+1);
			saveData profile = CreateProfile();
			profile.profile = currentProfile + 1;
			TutorialConfirmation();
			break;
		}
		case 1:
		{
			delete confirm;
			confirm = nullptr;
			state = MyState::Menu;
		}
		case -1:
		default:
			break;
		}
		return;
	}

	if (state == MyState::ConfirmDelete)
	{
		switch (confirm->Input())
		{
		case 0:
			CGameplayState::GetInstance()->DeleteProfile(currentProfile+1);
			profiles[currentProfile] = CreateProfile();
			profiles[currentProfile].profile = currentProfile + 1;
			//Don't break! They both delete confirm and change state beck to menu
		case 1:
			delete confirm;
			confirm = nullptr;
			state = MyState::Menu;
			break;
		case -1:
		default:
			break;
		}
		return;
	}

	if (state == MyState::ConfirmTutorial)
	{
		switch (confirm->Input())
		{
		case 0:
			CGameplayState::GetInstance()->SetLevel(Level::Gen1);
		case 1:
			Game::GetInstance()->PopState();
			Game::GetInstance()->PushState(CGameplayState::GetInstance());
			break;
		case 2:
			delete confirm;
			confirm = nullptr;
			break;
		case -1:
		default:
			break;
		}
		return;
	}

	switch (menu->Input())
	{
	case 0:
		CGameplayState::GetInstance()->SetSaveData(profiles[currentProfile]);
		Game::GetInstance()->PopState();
		Game::GetInstance()->PushState(CGameplayState::GetInstance());
		break;
	case 1:
	{
		std::vector<std::string> yesno;
		yesno.push_back("yes");
		yesno.push_back("no");
		confirm = new CMenu(&font,yesno,"Overwrite this profile?");
		state = MyState::ConfirmOverwrite;
		break;
	}
	case 2:
	{
		std::vector<std::string> yesno;
		yesno.push_back("yes");
		yesno.push_back("no");
		confirm = new CMenu(&font, yesno, "Delete this Profile?");
		state = MyState::ConfirmDelete;
		break;
	}
	case 3:
	{
		state = MyState::Idle;
		break;
	}
	case 4:
	{
		Game::GetInstance()->PopState();
		Game::GetInstance()->PushState(CMainMenuState::GetInstance());
		break;
	}
	case -1:
	default:
		break;
	}
}


void CProfileSelectState::Update(float dt)
{
	switch (state)
	{
	case MyState::Transition:
		transTimer += dt;
		if (transTimer >= transDuration)
		{
			if (renderedProfile == currentProfile - 1 || (renderedProfile == 2 && currentProfile == 0))
			{
				if (renderedProfile >= 2)
					renderedProfile = 0;
				else
					renderedProfile++;
			}
			else
			{
				if (renderedProfile <= 0)
					renderedProfile = 2;
				else
					renderedProfile--;
			}
			state = MyState::Idle;
		}
	default:
		return;
	}
}

void CProfileSelectState::Render()
{
	if (state == MyState::Transition)
	{
		TransitionRender();
		return;
	}

	//Render previous profile
	RenderProfile(currentProfile-1, previous);
	//Render next profile
	RenderProfile(currentProfile + 1, next);
	//Render center profile
	RenderProfile(currentProfile, current);

	if (state >= MyState::Menu)
	{
		menu->Render();
		if (state >= MyState::ConfirmOverwrite)
			confirm->Render();
	}
}

float floatLerp(float start, float end, float dt, float duration)
{
	float journey = end - start;
	float traveled = dt/duration;
	float position = start + journey * traveled;
	return position;
}

SGD::Point pointLerp(SGD::Point start, SGD::Point end, float dt, float duration)
{
	SGD::Point position;
	position.x = floatLerp(start.x, end.x, dt, duration);
	position.y = floatLerp(start.y, end.y, dt, duration);
	return position;
}

void CProfileSelectState::TransitionRender()
{
	SGD::Point renderedNext;
	SGD::Point renderedPrevious;
	SGD::Point renderedCurrent;
	bool lerpForward = renderedProfile == currentProfile - 1 || (renderedProfile == 2 && currentProfile == 0);

	if (lerpForward)
	{
		//Lerp forward a profile
		renderedNext = pointLerp(next, current, transTimer, transDuration);
		renderedPrevious = pointLerp(previous, next, transTimer, transDuration);
		renderedCurrent = pointLerp(current, previous, transTimer, transDuration);
	}
	else
	{
		renderedNext = pointLerp(next, previous, transTimer, transDuration);
		renderedPrevious = pointLerp(previous, current, transTimer, transDuration);
		renderedCurrent = pointLerp(current, next, transTimer, transDuration);
	}

	if (transTimer >= transDuration * 0.3f)
	{
		if (lerpForward)
		{
			RenderProfile(renderedProfile, renderedCurrent);
			RenderProfile(renderedProfile - 1, renderedPrevious);
			RenderProfile(renderedProfile + 1, renderedNext);
		}
		else
		{
			RenderProfile(renderedProfile + 1, renderedNext);
			RenderProfile(renderedProfile, renderedCurrent);
			RenderProfile(renderedProfile - 1, renderedPrevious);
		}
	}
	else
	{
		if (lerpForward)
		{
			RenderProfile(renderedProfile - 1, renderedPrevious);
			RenderProfile(renderedProfile, renderedCurrent);
			RenderProfile(renderedProfile + 1, renderedNext);
		}
		else
		{
			RenderProfile(renderedProfile - 1, renderedPrevious);
			RenderProfile(renderedProfile, renderedCurrent);
			RenderProfile(renderedProfile + 1, renderedNext);
		}
	}
}

void CProfileSelectState::LoadProfiles()
{
	profiles.clear();
	CGameplayState* loader = CGameplayState::GetInstance();
	for (unsigned int i = 1; i < 4; i++)
	{
		loader->SetProfile(i);
		profiles.push_back(loader->LoadProfile());
	}
	for (unsigned int i = 0; i < 3; i++)
	{
		if (profiles[i].profile == 0)
		{
			profiles[i] = CreateProfile();
			profiles[i].profile = i + 1;
		}
	}
}

saveData CProfileSelectState::CreateProfile()
{
	saveData profile;
	profile.currLevel = Level::Tutorial;

	profile.playerStat.level = 1;
	profile.playerStat.exp = 0;
	profile.playerStat.expRequired = 100;
	profile.playerStat.laserLevel = 0;
	profile.playerStat.missileLevel = 0;
	profile.playerStat.perks = 15;
	profile.playerStat.pushLevel = 0;
	profile.playerStat.warpLevel = 0;
	profile.playerStat.wellLevel = 0;

	profile.waveStat.alliesSaved = 0;
	profile.waveStat.enemiesKilled = 0;

	profile.world.saved = false;

	return profile;
}

void CProfileSelectState::RenderProfile(int index, SGD::Point pos)
{
	SGD::GraphicsManager::GetInstance()->DrawRectangle(SGD::Rectangle{ pos, SGD::Size{375,200} }, SGD::Color(0,0, 155));
	if (index > 2)
		index = 0;
	if (index < 0)
		index = 2;

	SGD::Point fontCursor = pos;
	saveData profile = profiles[index];
	std::string text = "Profile " + std::to_string(profile.profile);
	font.Write(fontCursor, text);
	fontCursor.y += font.ComputeStringSpace(text).height;
	fontCursor.y += 10;
	float topline = fontCursor.y;

	text = "Player Level: " + std::to_string(profile.playerStat.level);
	font.Write(fontCursor, text);
	fontCursor.y += font.ComputeStringSpace(text).height;
	fontCursor.y += 10;

	text = "Laser Level: " + std::to_string(profile.playerStat.laserLevel);
	font.Write(fontCursor, text);
	fontCursor.y += font.ComputeStringSpace(text).height;
	fontCursor.y += 10;

	text = "Missile Level: " + std::to_string(profile.playerStat.missileLevel);
	font.Write(fontCursor, text);
	fontCursor.y += font.ComputeStringSpace(text).height;
	fontCursor.y += 10;

	text = "Well Level: " + std::to_string(profile.playerStat.wellLevel);
	font.Write(fontCursor, text);
	fontCursor.y += font.ComputeStringSpace(text).height;
	fontCursor.y += 10;

	text = "Push Level: " + std::to_string(profile.playerStat.pushLevel);
	font.Write(fontCursor, text);
	fontCursor.y += font.ComputeStringSpace(text).height;
	fontCursor.y += 10;

	text = "Warp Level: " + std::to_string(profile.playerStat.warpLevel);
	font.Write(fontCursor, text);
	fontCursor.y += font.ComputeStringSpace(text).height;
	fontCursor.y += 10;

	fontCursor.y = topline;
	fontCursor.x += 200;

	text = "Experience: " + std::to_string(profile.playerStat.exp) + "/" + std::to_string(profile.playerStat.expRequired);
	font.Write(fontCursor, text);
	fontCursor.y += font.ComputeStringSpace(text).height;
	fontCursor.y += 10;

	text = "Perks: " + std::to_string(profile.playerStat.perks);
	font.Write(fontCursor, text);
	fontCursor.y += font.ComputeStringSpace(text).height;
	fontCursor.y += 10;

	text = "Sectors from home:\n" + std::to_string(int(Level::Final) - int(profile.currLevel));
	font.Write(fontCursor, text);
	fontCursor.y += font.ComputeStringSpace(text).height;
	fontCursor.y += 10;

	text = "Allies Rescued: " + std::to_string(profile.waveStat.alliesSaved);
	font.Write(fontCursor, text);
	fontCursor.y += font.ComputeStringSpace(text).height;
	fontCursor.y += 10;

	text = "Enemies Killed: " + std::to_string(profile.waveStat.enemiesKilled);
	font.Write(fontCursor, text);
	fontCursor.y += font.ComputeStringSpace(text).height;
	fontCursor.y += 10;
}

void CProfileSelectState::TutorialConfirmation()
{
	std::vector<std::string> buttons;
	buttons.push_back("Yes");
	buttons.push_back("No");
	buttons.push_back("Cancel");
	
	confirm = new CMenu(&font, buttons, "Skip Tutorial?");
	state = MyState::ConfirmTutorial;
}
