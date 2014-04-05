#include "../SGD Wrappers/SGD_InputManager.h"
#include "../SGD Wrappers/SGD_GraphicsManager.h"
#include "../SoundBox.h"
#include <sstream>
#include "UpgradeState.h"
#include "Game.h"

CUpgradeState::CUpgradeState()
{
}


CUpgradeState::~CUpgradeState()
{
}

CUpgradeState* CUpgradeState::GetInstance()
{
	static CUpgradeState instance;
	return &instance;
}

bool CUpgradeState::Input()
{
	SGD::InputManager* input = SGD::InputManager::GetInstance();

	if (input->IsKeyPressed(SGD::Key::Escape) || input->IsButtonPressed(0, 1))
	{
		Game::GetInstance()->PopState();
		return true;
	}

	if (input->GetMouseMovement() != SGD::Vector{ 0, 0 })
	{
		SGD::Point mousePos = input->GetMousePosition();
		for (unsigned int i = 0; i < buttons.size(); i++)
		{
			if (mousePos.IsWithinRectangle(buttons[i]))
			{
				if (cursor != i)
					CSoundBox::GetInstance()->Play(CSoundBox::sounds::uiHighlight, false);
				cursor = i;
				return true;
			}
		}
		cursor = -1;
	}

	if (input->IsKeyPressed(SGD::Key::Up) || input->IsDPadPressed(0, SGD::DPad::Up))
	{
		if (cursor == laserThree || cursor == missileThree || cursor == warpThree || cursor == wellThree || cursor == pushThree)
			cursor -= 2;
		else
			cursor++;
		CSoundBox::GetInstance()->Play(CSoundBox::sounds::uiHighlight, false);
	}

	else if (input->IsKeyPressed(SGD::Key::Down) || input->IsDPadPressed(0, SGD::DPad::Down))
	{
		if (cursor == laserOne || cursor == missileOne || cursor == warpOne || cursor == wellOne || cursor == pushOne)
			cursor += 2;
		else
			cursor--;
		CSoundBox::GetInstance()->Play(CSoundBox::sounds::uiHighlight, false);
	}

	else if (input->IsKeyPressed(SGD::Key::Right) || input->IsDPadPressed(0, SGD::DPad::Right))
	{
		if (cursor == pushOne || cursor == pushTwo || cursor == pushThree)
			cursor -= 12;
		else
			cursor += 3;
		CSoundBox::GetInstance()->Play(CSoundBox::sounds::uiHighlight, false);
	}

	else if (input->IsKeyPressed(SGD::Key::Left) || input->IsDPadPressed(0, SGD::DPad::Left))
	{
		if (cursor == laserOne || cursor == laserTwo || cursor == laserThree)
			cursor += 12;
		else
			cursor -= 3;
		CSoundBox::GetInstance()->Play(CSoundBox::sounds::uiHighlight, false);
	}

	if (input->IsKeyPressed(SGD::Key::Enter) || input->IsButtonPressed(0, 0) || input->IsKeyPressed(SGD::Key::MouseLeft))
	{
		switch (cursor)
		{
		case laserOne:
			if (player->GetPerks() > 0 && player->GetLaserLevel() == 0)
			{
				player->LaserLevelUp();
				player->RemovePerk();
				CSoundBox::GetInstance()->Play(CSoundBox::sounds::uiSuccess, false);
			}
			else
				CSoundBox::GetInstance()->Play(CSoundBox::sounds::uiFailure, false);

			break;
		case laserTwo:
			if (player->GetPerks() > 0 && player->GetLaserLevel() == 1)
			{
				player->LaserLevelUp();
				player->RemovePerk();
				CSoundBox::GetInstance()->Play(CSoundBox::sounds::uiSuccess, false);
			}
			else
				CSoundBox::GetInstance()->Play(CSoundBox::sounds::uiFailure, false);
			break;
		case laserThree:
			if (player->GetPerks() > 1 && player->GetLaserLevel() == 2)
			{
				player->LaserLevelUp();
				player->RemovePerk(); player->RemovePerk();
				CSoundBox::GetInstance()->Play(CSoundBox::sounds::uiSuccess, false);
			}
			else
				CSoundBox::GetInstance()->Play(CSoundBox::sounds::uiFailure, false);
			break;
		case missileOne:
			if (player->GetPerks() > 0 && player->GetMissileLevel() == 0)
			{
				player->MissileLevelUp();
				player->RemovePerk();
				CSoundBox::GetInstance()->Play(CSoundBox::sounds::uiSuccess, false);
			}
			else
				CSoundBox::GetInstance()->Play(CSoundBox::sounds::uiFailure, false);
			break; 
		case missileTwo:
			if (player->GetPerks() > 0 && player->GetMissileLevel() == 1)
			{
				player->MissileLevelUp();
				player->RemovePerk();
				CSoundBox::GetInstance()->Play(CSoundBox::sounds::uiSuccess, false);
			}
			else
				CSoundBox::GetInstance()->Play(CSoundBox::sounds::uiFailure, false);
			break;
		case missileThree:
			if (player->GetPerks() > 1 && player->GetMissileLevel() == 2)
			{
				player->MissileLevelUp();
				player->RemovePerk(); player->RemovePerk();
				CSoundBox::GetInstance()->Play(CSoundBox::sounds::uiSuccess, false);
			}
			else
				CSoundBox::GetInstance()->Play(CSoundBox::sounds::uiFailure, false);
			break;
		case wellOne:
			if (player->GetPerks() > 0 && player->GetWellLevel() == 0)
			{
				player->WellLevelUp();
				player->RemovePerk();
				CSoundBox::GetInstance()->Play(CSoundBox::sounds::uiSuccess, false);
			}
			else
				CSoundBox::GetInstance()->Play(CSoundBox::sounds::uiFailure, false);
			break;
		case wellTwo:
			if (player->GetPerks() > 0 && player->GetWellLevel() == 1)
			{
				player->WellLevelUp();
				player->RemovePerk();
				CSoundBox::GetInstance()->Play(CSoundBox::sounds::uiSuccess, false);
			}
			else
				CSoundBox::GetInstance()->Play(CSoundBox::sounds::uiFailure, false);
			break;
		case wellThree:
			if (player->GetPerks() > 1 && player->GetWellLevel() == 2)
			{
				player->WellLevelUp();
				player->RemovePerk(); player->RemovePerk();
				CSoundBox::GetInstance()->Play(CSoundBox::sounds::uiSuccess, false);
			}
			else
				CSoundBox::GetInstance()->Play(CSoundBox::sounds::uiFailure, false);
			break;
		case pushOne:
			if (player->GetPerks() > 0 && player->GetPushLevel() == 0)
			{
				player->PushLevelUp();
				player->RemovePerk();
				CSoundBox::GetInstance()->Play(CSoundBox::sounds::uiSuccess, false);
			}
			else
				CSoundBox::GetInstance()->Play(CSoundBox::sounds::uiFailure, false);
			break;
		case pushTwo:
			if (player->GetPerks() > 0 && player->GetPushLevel() == 1)
			{
				player->PushLevelUp();
				player->RemovePerk();
				CSoundBox::GetInstance()->Play(CSoundBox::sounds::uiSuccess, false);
			}
			else
				CSoundBox::GetInstance()->Play(CSoundBox::sounds::uiFailure, false);
			break;
		case pushThree:
			if (player->GetPerks() > 1 && player->GetPushLevel() == 2)
			{
				player->PushLevelUp();
				player->RemovePerk(); player->RemovePerk();
				CSoundBox::GetInstance()->Play(CSoundBox::sounds::uiSuccess, false);
			}
			else
				CSoundBox::GetInstance()->Play(CSoundBox::sounds::uiFailure, false);
			break;
		case warpOne:
			if (player->GetPerks() > 0 && player->GetWarpLevel() == 0)
			{
				player->WarpLevelUp();
				player->RemovePerk();
				CSoundBox::GetInstance()->Play(CSoundBox::sounds::uiSuccess, false);
			}
			else
				CSoundBox::GetInstance()->Play(CSoundBox::sounds::uiFailure, false);
			break;
		case warpTwo:
			if (player->GetPerks() > 0 && player->GetWarpLevel() == 1)
			{
				player->WarpLevelUp();
				player->RemovePerk();
				CSoundBox::GetInstance()->Play(CSoundBox::sounds::uiSuccess, false);
			}
			else
				CSoundBox::GetInstance()->Play(CSoundBox::sounds::uiFailure, false);
			break;
		case warpThree:
			if (player->GetPerks() > 1 && player->GetWarpLevel() == 2)
			{
				player->WarpLevelUp();
				player->RemovePerk(); player->RemovePerk();
				CSoundBox::GetInstance()->Play(CSoundBox::sounds::uiSuccess, false);
			}
			else
				CSoundBox::GetInstance()->Play(CSoundBox::sounds::uiFailure, false);
			break;
		default:
			break;
		}
	}

	return true;
}

void CUpgradeState::Update(float dt)
{
	//Um...
}

void CUpgradeState::Render()
{
	int screenWidth = Game::GetInstance()->GetScreenWidth();
	int screenHeight = Game::GetInstance()->GetScreenHeight();
	SGD::GraphicsManager* graphics = SGD::GraphicsManager::GetInstance();
	graphics->DrawRectangle({ 0, 0, (float)Game::GetInstance()->GetScreenWidth(), (float)Game::GetInstance()->GetScreenHeight() }, { 0, 0, 0 });
	Game::GetInstance()->FontPoiret.WriteCenter({ screenWidth * .10f, screenHeight * .65f, screenWidth * .25f,  screenHeight * .75f }, "Lasers");
	Game::GetInstance()->FontPoiret.WriteCenter({ screenWidth * .25f, screenHeight * .65f, screenWidth * .40f,  screenHeight * .75f }, "Missiles");
	Game::GetInstance()->FontPoiret.WriteCenter({ screenWidth * .40f, screenHeight * .65f, screenWidth * .55f,  screenHeight * .75f }, "Warp");
	Game::GetInstance()->FontPoiret.WriteCenter({ screenWidth * .55f, screenHeight * .65f, screenWidth * .70f,  screenHeight * .75f }, "Well");
	Game::GetInstance()->FontPoiret.WriteCenter({ screenWidth * .70f, screenHeight * .65f, screenWidth * .85f,  screenHeight * .75f }, "Push");

	// draw upgrade boxes / icons
	graphics->DrawTexture(iconTexture, { screenWidth * .15f, screenHeight * .25f });
	graphics->DrawTexture(iconTexture, { screenWidth * .15f, screenHeight * .4f });
	graphics->DrawTexture(iconTexture, { screenWidth * .15f, screenHeight * .55f });
	graphics->DrawTexture(iconTexture, { screenWidth * .30f, screenHeight * .25f });
	graphics->DrawTexture(iconTexture, { screenWidth * .30f, screenHeight * .4f });
	graphics->DrawTexture(iconTexture, { screenWidth * .30f, screenHeight * .55f });
	graphics->DrawTexture(iconTexture, { screenWidth * .45f, screenHeight * .25f });
	graphics->DrawTexture(iconTexture, { screenWidth * .45f, screenHeight * .4f });
	graphics->DrawTexture(iconTexture, { screenWidth * .45f, screenHeight * .55f });
	graphics->DrawTexture(iconTexture, { screenWidth * .60f, screenHeight * .25f });
	graphics->DrawTexture(iconTexture, { screenWidth * .60f, screenHeight * .4f });
	graphics->DrawTexture(iconTexture, { screenWidth * .60f, screenHeight * .55f });
	graphics->DrawTexture(iconTexture, { screenWidth * .75f, screenHeight * .25f });
	graphics->DrawTexture(iconTexture, { screenWidth * .75f, screenHeight * .4f });
	graphics->DrawTexture(iconTexture, { screenWidth * .75f, screenHeight * .55f });

	switch (player->GetLaserLevel())
	{
	case 0:
		graphics->DrawRectangle({ { screenWidth * .15f, screenHeight * .55f }, SGD::Size{ 64, 64 } }, { 200, 200, 200, 150 });
	case 1:
		graphics->DrawRectangle({ { screenWidth * .15f, screenHeight * .4f }, SGD::Size{ 64, 64 } }, { 200, 200, 200, 150 });
	case 2:
		graphics->DrawRectangle({ { screenWidth * .15f, screenHeight * .25f }, SGD::Size{ 64, 64 } }, { 200, 200, 200, 150 });
		break;
	default:
		break;
	}

	switch (player->GetMissileLevel())
	{
	case 0:
		graphics->DrawRectangle({ { screenWidth * .3f, screenHeight * .55f }, SGD::Size{ 64, 64 } }, { 200, 200, 200, 150 });
	case 1:
		graphics->DrawRectangle({ { screenWidth * .3f, screenHeight * .4f }, SGD::Size{ 64, 64 } }, { 200, 200, 200, 150 });
	case 2:
		graphics->DrawRectangle({ { screenWidth * .3f, screenHeight * .25f }, SGD::Size{ 64, 64 } }, { 200, 200, 200, 150 });
		break;
	default:
		break;
	}

	switch (player->GetWarpLevel())
	{
	case 0:
		graphics->DrawRectangle({ { screenWidth * .45f, screenHeight * .55f }, SGD::Size{ 64, 64 } }, { 200, 200, 200, 150 });
	case 1:
		graphics->DrawRectangle({ { screenWidth * .45f, screenHeight * .4f }, SGD::Size{ 64, 64 } }, { 200, 200, 200, 150 });
	case 2:
		graphics->DrawRectangle({ { screenWidth * .45f, screenHeight * .25f }, SGD::Size{ 64, 64 } }, { 200, 200, 200, 150 });
		break;
	default:
		break;
	}

	switch (player->GetWellLevel())
	{
	case 0:
		graphics->DrawRectangle({ { screenWidth * .6f, screenHeight * .55f }, SGD::Size{ 64, 64 } }, { 200, 200, 200, 150 });
	case 1:
		graphics->DrawRectangle({ { screenWidth * .6f, screenHeight * .4f }, SGD::Size{ 64, 64 } }, { 200, 200, 200, 150 });
	case 2:
		graphics->DrawRectangle({ { screenWidth * .6f, screenHeight * .25f }, SGD::Size{ 64, 64 } }, { 200, 200, 200, 150 });
		break;
	default:
		break;
	}

	switch (player->GetPushLevel())
	{
	case 0:
		graphics->DrawRectangle({ { screenWidth * .75f, screenHeight * .55f }, SGD::Size{ 64, 64 } }, { 200, 200, 200, 150 });
	case 1:
		graphics->DrawRectangle({ { screenWidth * .75f, screenHeight * .4f }, SGD::Size{ 64, 64 } }, { 200, 200, 200, 150 });
	case 2:
		graphics->DrawRectangle({ { screenWidth * .75f, screenHeight * .25f }, SGD::Size{ 64, 64 } }, { 200, 200, 200, 150 });
		break;
	default:
		break;
	}

	switch (cursor)
	{
	case laserOne:
		graphics->DrawRectangle({ { screenWidth * .22f, screenHeight * .52f }, SGD::Size{ 150, 100 } }, { 200, 0, 0, 0 }, { 255, 255, 255 }, 1);
		Game::GetInstance()->FontSmall.WriteCenter({ { screenWidth * .22f, screenHeight * .48f }, SGD::Size{ 150, 100 } }, "Laser I");
		Game::GetInstance()->FontSmall.WriteCenter({ { screenWidth * .22f, screenHeight * .54f }, SGD::Size{ 150, 100 } }, "Increased Damage");

		break;
	case laserTwo:
		graphics->DrawRectangle({ { screenWidth * .22f, screenHeight * .37f }, SGD::Size{ 150, 100 } }, { 200, 0, 0, 0 }, { 255, 255, 255 }, 1);
		Game::GetInstance()->FontSmall.WriteCenter({ { screenWidth * .22f, screenHeight * .33f }, SGD::Size{ 150, 100 } }, "Laser II");
		Game::GetInstance()->FontSmall.WriteCenter({ { screenWidth * .22f, screenHeight * .37f }, SGD::Size{ 150, 100 } }, "Additional");
		Game::GetInstance()->FontSmall.WriteCenter({ { screenWidth * .22f, screenHeight * .39f }, SGD::Size{ 150, 100 } }, "Laser Cannon");

		break;
	case laserThree:
		graphics->DrawRectangle({ { screenWidth * .22f, screenHeight * .22f }, SGD::Size{ 150, 100 } }, { 200, 0, 0, 0 }, { 255, 255, 255 }, 1);
		Game::GetInstance()->FontSmall.WriteCenter({ { screenWidth * .22f, screenHeight * .18f }, SGD::Size{ 150, 100 } }, "Laser III");
		Game::GetInstance()->FontSmall.WriteCenter({ { screenWidth * .22f, screenHeight * .22f }, SGD::Size{ 150, 100 } }, "Increased Damage");
		Game::GetInstance()->FontSmall.WriteCenter({ { screenWidth * .22f, screenHeight * .24f }, SGD::Size{ 150, 100 } }, "Increased Firerate");
		break;
	case missileOne:
		graphics->DrawRectangle({ { screenWidth * .37f, screenHeight * .52f }, SGD::Size{ 150, 100 } }, { 200, 0, 0, 0 }, { 255, 255, 255 }, 1);
		Game::GetInstance()->FontSmall.WriteCenter({ { screenWidth * .37f, screenHeight * .48f }, SGD::Size{ 150, 100 } }, "Missile I");
		Game::GetInstance()->FontSmall.WriteCenter({ { screenWidth * .37f, screenHeight * .54f }, SGD::Size{ 150, 100 } }, "Increased Damage");
		break;
	case missileTwo:
		graphics->DrawRectangle({ { screenWidth * .37f, screenHeight * .37f }, SGD::Size{ 150, 100 } }, { 200, 0, 0, 0 }, { 255, 255, 255 }, 1);
		Game::GetInstance()->FontSmall.WriteCenter({ { screenWidth * .37f, screenHeight * .33f }, SGD::Size{ 150, 100 } }, "Missile II");
		Game::GetInstance()->FontSmall.WriteCenter({ { screenWidth * .37f, screenHeight * .37f }, SGD::Size{ 150, 100 } }, "Additional");
		Game::GetInstance()->FontSmall.WriteCenter({ { screenWidth * .37f, screenHeight * .39f }, SGD::Size{ 150, 100 } }, "Missile Launcher");
		break;
	case missileThree:
		graphics->DrawRectangle({ { screenWidth * .37f, screenHeight * .22f }, SGD::Size{ 150, 100 } }, { 200, 0, 0, 0 }, { 255, 255, 255 }, 1);
		Game::GetInstance()->FontSmall.WriteCenter({ { screenWidth * .37f, screenHeight * .18f }, SGD::Size{ 150, 100 } }, "Missile III");
		Game::GetInstance()->FontSmall.WriteCenter({ { screenWidth * .37f, screenHeight * .22f }, SGD::Size{ 150, 100 } }, "Missiles track");
		Game::GetInstance()->FontSmall.WriteCenter({ { screenWidth * .37f, screenHeight * .24f }, SGD::Size{ 150, 100 } }, "nearby enemies");
		break;
	case warpOne:
		graphics->DrawRectangle({ { screenWidth * .52f, screenHeight * .52f }, SGD::Size{ 150, 100 } }, { 200, 0, 0, 0 }, { 255, 255, 255 }, 1);
		Game::GetInstance()->FontSmall.WriteCenter({ { screenWidth * .52f, screenHeight * .48f }, SGD::Size{ 150, 100 } }, "Warp I");
		Game::GetInstance()->FontSmall.WriteCenter({ { screenWidth * .52f, screenHeight * .54f }, SGD::Size{ 150, 100 } }, "Reduced Cooldown");
		break;
	case warpTwo:
		graphics->DrawRectangle({ { screenWidth * .52f, screenHeight * .37f }, SGD::Size{ 150, 100 } }, { 200, 0, 0, 0 }, { 255, 255, 255 }, 1);
		Game::GetInstance()->FontSmall.WriteCenter({ { screenWidth * .52f, screenHeight * .33f }, SGD::Size{ 150, 100 } }, "Warp II");
		Game::GetInstance()->FontSmall.WriteCenter({ { screenWidth * .52f, screenHeight * .39f }, SGD::Size{ 150, 100 } }, "Increased Strength");
		break;
	case warpThree:
		graphics->DrawRectangle({ { screenWidth * .52f, screenHeight * .22f }, SGD::Size{ 150, 100 } }, { 200, 0, 0, 0 }, { 255, 255, 255 }, 1);
		Game::GetInstance()->FontSmall.WriteCenter({ { screenWidth * .52f, screenHeight * .18f }, SGD::Size{ 150, 100 } }, "Warp III");
		Game::GetInstance()->FontSmall.WriteCenter({ { screenWidth * .52f, screenHeight * .22f }, SGD::Size{ 150, 100 } }, "Invulnerability");
		Game::GetInstance()->FontSmall.WriteCenter({ { screenWidth * .52f, screenHeight * .24f }, SGD::Size{ 150, 100 } }, "during Warp");
		break;
	case wellOne:
		graphics->DrawRectangle({ { screenWidth * .44f, screenHeight * .52f }, SGD::Size{ 150, 100 } }, { 200, 0, 0, 0 }, { 255, 255, 255 }, 1);
		Game::GetInstance()->FontSmall.WriteCenter({ { screenWidth * .44f, screenHeight * .48f }, SGD::Size{ 150, 100 } }, "Gravity Well I");
		Game::GetInstance()->FontSmall.WriteCenter({ { screenWidth * .44f, screenHeight * .54f }, SGD::Size{ 150, 100 } }, "Increased Radius");
		break;
	case wellTwo:
		graphics->DrawRectangle({ { screenWidth * .44f, screenHeight * .37f }, SGD::Size{ 150, 100 } }, { 200, 0, 0, 0 }, { 255, 255, 255 }, 1);
		Game::GetInstance()->FontSmall.WriteCenter({ { screenWidth * .44f, screenHeight * .33f }, SGD::Size{ 150, 100 } }, "Gravity Well II");
		Game::GetInstance()->FontSmall.WriteCenter({ { screenWidth * .44f, screenHeight * .39f }, SGD::Size{ 150, 100 } }, "Increased Strength");
		break;
	case wellThree:
		graphics->DrawRectangle({ { screenWidth * .44f, screenHeight * .22f }, SGD::Size{ 150, 100 } }, { 200, 0, 0, 0 }, { 255, 255, 255 }, 1);
		Game::GetInstance()->FontSmall.WriteCenter({ { screenWidth * .44f, screenHeight * .18f }, SGD::Size{ 150, 100 } }, "Gravity Well III");
		Game::GetInstance()->FontSmall.WriteCenter({ { screenWidth * .44f, screenHeight * .22f }, SGD::Size{ 150, 100 } }, "Gravity Well");
		Game::GetInstance()->FontSmall.WriteCenter({ { screenWidth * .44f, screenHeight * .24f }, SGD::Size{ 150, 100 } }, "explodes upon");
		Game::GetInstance()->FontSmall.WriteCenter({ { screenWidth * .44f, screenHeight * .26f }, SGD::Size{ 150, 100 } }, "expiring");
		break;
	case pushOne:
		graphics->DrawRectangle({ { screenWidth * .59f, screenHeight * .52f }, SGD::Size{ 150, 100 } }, { 200, 0, 0, 0 }, { 255, 255, 255 }, 1);
		Game::GetInstance()->FontSmall.WriteCenter({ { screenWidth * .59f, screenHeight * .48f }, SGD::Size{ 150, 100 } }, "Gravity Push I");
		Game::GetInstance()->FontSmall.WriteCenter({ { screenWidth * .59f, screenHeight * .54f }, SGD::Size{ 150, 100 } }, "Larger Arc");
		break;
	case pushTwo:
		graphics->DrawRectangle({ { screenWidth * .59f, screenHeight * .37f }, SGD::Size{ 150, 100 } }, { 200, 0, 0, 0 }, { 255, 255, 255 }, 1);
		Game::GetInstance()->FontSmall.WriteCenter({ { screenWidth * .59f, screenHeight * .33f }, SGD::Size{ 150, 100 } }, "Gravity Push II");
		Game::GetInstance()->FontSmall.WriteCenter({ { screenWidth * .59f, screenHeight * .39f }, SGD::Size{ 150, 100 } }, "Increased Strength");
		break;
	case pushThree:
		graphics->DrawRectangle({ { screenWidth * .59f, screenHeight * .22f }, SGD::Size{ 150, 100 } }, { 200, 0, 0, 0 }, { 255, 255, 255 }, 1);
		Game::GetInstance()->FontSmall.WriteCenter({ { screenWidth * .59f, screenHeight * .18f }, SGD::Size{ 150, 100 } }, "Gravity Push III");
		Game::GetInstance()->FontSmall.WriteCenter({ { screenWidth * .59f, screenHeight * .22f }, SGD::Size{ 150, 100 } }, "Gravity Push");
		Game::GetInstance()->FontSmall.WriteCenter({ { screenWidth * .59f, screenHeight * .24f }, SGD::Size{ 150, 100 } }, "expands in a");
		Game::GetInstance()->FontSmall.WriteCenter({ { screenWidth * .59f, screenHeight * .26f }, SGD::Size{ 150, 100 } }, "full circle");
		break;
	}

	// draw selected box
	if (cursor != -1)
		graphics->DrawRectangle({ { screenWidth * .15f * (cursor / 3 + 1), screenHeight * (.55f - (cursor % 3) * .15f) }, SGD::Size{ 64, 64 } }, { 50, 255, 255, 255 }, { 255, 255, 255 }, 2);
	std::ostringstream perksToSpend;
	perksToSpend << "Perks to spend: " << player->GetPerks();
	Game::GetInstance()->FontSmall.Write({ screenWidth * .7f, screenHeight * .9f }, perksToSpend.str().c_str());
}

void CUpgradeState::Enter()
{
	iconTexture = SGD::GraphicsManager::GetInstance()->LoadTexture("Resources/Graphics/upgradeIcon.png");
	player = CEntityManager::GetInstance()->GetPlayer();

	for (int i = 0; i < 15; i++)
	{
		buttons.push_back({ SGD::Point{ Game::GetInstance()->GetScreenWidth() * .15f * (i / 3 + 1), Game::GetInstance()->GetScreenHeight() * (.55f - (i % 3) * .15f) }, SGD::Size{ 64, 64 } });
	}
}

void CUpgradeState::Exit()
{
	SGD::GraphicsManager::GetInstance()->UnloadTexture(iconTexture);
}