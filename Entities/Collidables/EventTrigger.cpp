#include "EventTrigger.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../SGD Wrappers/SGD_InputManager.h"
#include "../../GameStates/Game.h"
#include "../../WinMain.h"

void EventTrigger::HandleCollision(IEntity* other)
{
	if (other->GetType() == (int)EntityType::Player || other->GetType() == (int)EntityType::Shield)
	{
		colliding = true;
	}
	
}

void EventTrigger::Render()
{
	if (colliding)
	{
		SGD::Size screenSize = { (float)Game::GetInstance()->GetScreenWidth(), (float)Game::GetInstance()->GetScreenHeight() };
		SGD::GraphicsManager* graphics = SGD::GraphicsManager::GetInstance();
		switch (triggerType)
		{
		case (int)triggerID::tutMovement:
			graphics->DrawRectangle(SGD::Rectangle{ { screenSize.width * .30f, screenSize.height * .6f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .15f } }, { 200, 0, 0, 0 }, { 200, 255, 255, 255 }, 2);
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .62f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "Basic Movement");
			if (SGD::InputManager::GetInstance()->IsControllerConnected(0))
			{
				Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .66f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "Left Joystick to move.");
				Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .69f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "Right Joystick to aim.");
			}
			else
				Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .66f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "WASD to move. Mouse to aim.");
			break;
		case (int)triggerID::tutLasers:
			graphics->DrawRectangle(SGD::Rectangle{ { screenSize.width * .30f, screenSize.height * .6f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .15f } }, { 200, 0, 0, 0 }, { 200, 255, 255, 255 }, 2);
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .62f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "Lasers");
			if (SGD::InputManager::GetInstance()->IsControllerConnected(0))
			{
				if (ARCADE == 1)
					Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .68f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "Left Red to fire lasers.");
				else
					Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .68f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "Right Trigger to fire lasers.");
			}
			else
				Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .68f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "Left click to fire lasers.");
			break;
		case (int)triggerID::tutMissiles:
			graphics->DrawRectangle(SGD::Rectangle{ { screenSize.width * .30f, screenSize.height * .6f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .15f } }, { 200, 0, 0, 0 }, { 200, 255, 255, 255 }, 2);
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .62f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "Missiles");
			if (SGD::InputManager::GetInstance()->IsControllerConnected(0))
			{
				if (ARCADE == 1)
					Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .68f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "Right Red to fire missiles.");
				else
					Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .68f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "Left Trigger to fire missiles.");
			}
			else
				Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .68f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "Right click to fire missiles.");
			break;
		case (int)triggerID::tutWarp:
			graphics->DrawRectangle(SGD::Rectangle{ { screenSize.width * .30f, screenSize.height * .6f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .15f } }, { 200, 0, 0, 0 }, { 200, 255, 255, 255 }, 2);
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .60f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "Warp");
			if (SGD::InputManager::GetInstance()->IsControllerConnected(0))
			{
				if (ARCADE == 1)
					Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .63f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "Button 2 to Warp.");
				else
					Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .63f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "Click LS to Warp.");
			}
			else
				Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .63f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "Hit Space to Warp.");

			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .67f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "Warping allows you");
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .69f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "to evade incoming fire.");
			break;
		case (int)triggerID::tutWell:
			graphics->DrawRectangle(SGD::Rectangle{ { screenSize.width * .30f, screenSize.height * .6f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .15f } }, { 200, 0, 0, 0 }, { 200, 255, 255, 255 }, 2);
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .60f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "Well");
			if (SGD::InputManager::GetInstance()->IsControllerConnected(0))
			{
				if (ARCADE == 1)
					Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .63f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "Button 0 for Gravity Well.");
				else
					Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .63f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "LB to spawn a Gravity Well.");
			}
			else
				Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .63f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "Hit Q to spawn a Gravity Well.");
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .67f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "Gravity Well will suck in everything");
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .69f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "of appropriate size.");
			break;
		case (int)triggerID::tutPush:
			graphics->DrawRectangle(SGD::Rectangle{ { screenSize.width * .30f, screenSize.height * .6f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .15f } }, { 200, 0, 0, 0 }, { 200, 255, 255, 255 }, 2);
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .60f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "Push");
			if (SGD::InputManager::GetInstance()->IsControllerConnected(0))
			{
				if (ARCADE == 1)
					Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .63f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "Button 1 for Gravity Push.");
				else
					Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .63f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "RB to use Gravity Push.");
			}
			else
				Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .63f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "Hit E to use Gravity Push.");
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .67f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "Gravity Push will reflect everything");
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .69f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "in an arc in front of you.");
			break;
		case (int)triggerID::tutArrows:
			graphics->DrawRectangle(SGD::Rectangle{ { screenSize.width * .30f, screenSize.height * .6f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .15f } }, { 200, 0, 0, 0 }, { 200, 255, 255, 255 }, 2);
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .60f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "Arrow Indicators");
			if (SGD::InputManager::GetInstance()->IsControllerConnected(0))
			{
				if (ARCADE == 1)
					Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .63f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "Button 3 to toggle the compass.");
				else
					Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .63f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "Select to toggle the compass.");
			}
			else
				Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .63f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "Hit Tab to toggle the compass.");
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .67f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "Arrows point to current objectives.");
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .69f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "Toggle them on/off at any time.");
			break;
		case (int)triggerID::tutArrowsTwo:
			graphics->DrawRectangle(SGD::Rectangle{ { screenSize.width * .30f, screenSize.height * .6f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .15f } }, { 200, 0, 0, 0 }, { 200, 255, 255, 255 }, 2);
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .60f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "Arrow Indicators");
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .63f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "Yellow - Stargate");
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .65f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "Red - Enemy Flock");
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .67f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "Orange - Coordinator");
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .69f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "Blue - Allied Ship");
			break;
		case (int)triggerID::tutCoordinator:
			graphics->DrawRectangle(SGD::Rectangle{ { screenSize.width * .30f, screenSize.height * .6f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .15f } }, { 200, 0, 0, 0 }, { 200, 255, 255, 255 }, 2);
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .60f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "Coordinator");
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .63f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "Coordinators handle enemy back-up");
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .65f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "calls. Killing them prevents these");
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .67f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "calls as well as provides you with");
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .69f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "arrows to remaining enemy flocks.");
			break;
		case (int)triggerID::tutHuman:
			graphics->DrawRectangle(SGD::Rectangle{ { screenSize.width * .30f, screenSize.height * .6f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .15f } }, { 200, 0, 0, 0 }, { 200, 255, 255, 255 }, 2);
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .60f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "Human Ship");
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .63f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "Saving human ships will reward");
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .65f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "you with experience,");
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .67f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "as well as provide more aid");
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .69f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "in the final battle.");
			
			//drawing human
			graphics->DrawRectangle(SGD::Rectangle{ { screenSize.width * .20f, screenSize.height * .6f }, SGD::Size{ screenSize.width * .08f, screenSize.height * .15f } }, { 200, 0, 0, 0 }, { 200, 255, 255, 255 }, 2);

			graphics->DrawTextureSection(CEntityManager::GetInstance()->GetImages()[(int)EntityType::Human], { screenSize.width * .212f, screenSize.height * .63f }, { 0, 0, 60, 70 }, 0, {}, { 230, 255, 255, 255 }, { .75f, .75f });
			break;
		case (int)triggerID::tutUpgrade:
			graphics->DrawRectangle(SGD::Rectangle{ { screenSize.width * .30f, screenSize.height * .6f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .15f } }, { 200, 0, 0, 0 }, { 200, 255, 255, 255 }, 2);
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .60f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "Upgrades");
			if (SGD::InputManager::GetInstance()->IsControllerConnected(0))
			{
				Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .63f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "Hit Start for the Upgrade menu.");
			}
			else
				Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .63f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "Press Escape for the Upgrade menu.");
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .67f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "Each level you gain one perk.");
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .69f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "Spend them wisely!");
			break;
		case (int)triggerID::tutBoss:
			graphics->DrawRectangle(SGD::Rectangle{ { screenSize.width * .30f, screenSize.height * .6f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .15f } }, { 200, 0, 0, 0 }, { 200, 255, 255, 255 }, 2);
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .60f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "Boss");
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .63f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "Each level has a boss with a");
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .65f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "unique mechanic. Remember to");
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .67f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "use your abilities!");
			break;
		case (int)triggerID::tutStargate:
			graphics->DrawRectangle(SGD::Rectangle{ { screenSize.width * .30f, screenSize.height * .6f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .15f } }, { 200, 0, 0, 0 }, { 200, 255, 255, 255 }, 2);
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .60f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "Stargate");
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .63f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "After defeating a boss, the");
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .65f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "Stargate opens. The Stargate will");
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .67f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "take you tothe next level.");
			break;
		case (int)triggerID::finalLevel:
			graphics->DrawRectangle(SGD::Rectangle{ { screenSize.width * .3f, screenSize.height * .6f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .15f } }, { 200, 0, 0, 0 }, { 200, 255, 255, 255 }, 2);
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .60f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "Front Lines");
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .63f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "You've made it to the front lines!");
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .65f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "Help save the remaining human ships");
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .30f, screenSize.height * .67f }, SGD::Size{ screenSize.width * .4f, screenSize.height * .05f } }, "from alien forces!");
			break;
		default:
			break;
		}
	}

	colliding = false;
}
