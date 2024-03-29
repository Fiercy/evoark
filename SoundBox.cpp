#include "SoundBox.h"


CSoundBox::CSoundBox()
{

}

CSoundBox::~CSoundBox()
{
}

CSoundBox* CSoundBox::GetInstance(void)
{
	static CSoundBox instance;
	return &instance;
}

void CSoundBox::Enter()
{
	audio = SGD::AudioManager::GetInstance();
	uiHighlightSFX = audio->LoadAudio("Resources/Audio/UIHighlight.wav");
	uiFailureSFX = audio->LoadAudio("Resources/Audio/UIFailure.wav");
	uiSuccessSFX = audio->LoadAudio("Resources/Audio/UISuccess.wav");
	uiEnterSFX = audio->LoadAudio("Resources/Audio/UIEnter.wav");
	uiSwishSFX = audio->LoadAudio("Resources/Audio/Swish.wav");

	playerLaserSFX = audio->LoadAudio("Resources/Audio/LaserFire1.wav");
	playerLaserFinalSFX = audio->LoadAudio("Resources/Audio/PlayerLaser2.wav");
	playerMissileSFX = audio->LoadAudio("Resources/Audio/PlayerMissile.wav");

	playerWarpSFX = audio->LoadAudio("Resources/Audio/PlayerWarp.wav");
	playerWellSFX = audio->LoadAudio("Resources/Audio/PlayerWell3Sec.wav");
	playerPushSFX = audio->LoadAudio("Resources/Audio/PlayerPush.wav");

	playerLevelUpSFX = audio->LoadAudio("Resources/Audio/PlayerLevelUp.wav");

	enemyHullDamageSFX = audio->LoadAudio("Resources/Audio/EnemyHullDamage.wav");
	enemyShieldDamageSFX = audio->LoadAudio("Resources/Audio/EnemyShieldDamage.wav");


	missileHitSFX = audio->LoadAudio("Resources/Audio/MissileHit.wav");


	copperheadExplosion = audio->LoadAudio("Resources/Audio/CopperheadExplosion.wav");
	cobraExlosion       = audio->LoadAudio("Resources/Audio/CobraExplosion.wav");
	mediumExplosion     = audio->LoadAudio("Resources/Audio/Mamba&PlayerExplosion.wav");
	coralExplosion      = audio->LoadAudio("Resources/Audio/CoralExplosion.wav");
	moccasinExplosion   = audio->LoadAudio("Resources/Audio/MoccasinExplosion.wav");




	creamMusic = audio->LoadAudio("Resources/Audio/cream.xwm");
	ambientMusic = audio->LoadAudio("Resources/Audio/ambientSpace.xwm");
	slowTranceMusic = audio->LoadAudio("Resources/Audio/slowTrance.xwm");
	
}

void CSoundBox::Exit()
{
	audio->UnloadAudio(uiHighlightSFX);
	audio->UnloadAudio(uiFailureSFX);
	audio->UnloadAudio(uiSuccessSFX);
	audio->UnloadAudio(uiEnterSFX);
	audio->UnloadAudio(uiSwishSFX);
	audio->UnloadAudio(playerLaserSFX);
	audio->UnloadAudio(playerLaserFinalSFX);
	audio->UnloadAudio(playerMissileSFX);
	audio->UnloadAudio(playerWarpSFX);
	audio->UnloadAudio(playerWellSFX);
	audio->UnloadAudio(playerPushSFX);
	audio->UnloadAudio(playerLevelUpSFX);
	audio->UnloadAudio(enemyHullDamageSFX);
	audio->UnloadAudio(enemyShieldDamageSFX);
	audio->UnloadAudio(creamMusic);
	audio->UnloadAudio(slowTranceMusic);
	audio->UnloadAudio(ambientMusic);

	audio->UnloadAudio(copperheadExplosion);
	audio->UnloadAudio(cobraExlosion);
	audio->UnloadAudio(mediumExplosion);
	audio->UnloadAudio(coralExplosion);
	audio->UnloadAudio(moccasinExplosion);

	audio->UnloadAudio(missileHitSFX);
}

void CSoundBox::Play(int _soundEnum, bool _loop)
{
	SGD::HAudio soundToPlay = SGD::INVALID_HANDLE;
	switch (_soundEnum)
	{
	case uiHighlight:
		soundToPlay = uiHighlightSFX;
		break;
	case uiSuccess:
		soundToPlay = uiSuccessSFX;
		break;
	case uiFailure:
		soundToPlay = uiFailureSFX;
		break;
	case uiEnter:
		soundToPlay = uiEnterSFX;
		break;
	case uiSwish:
		soundToPlay = uiSwishSFX;
		break;
	case playerLaser:
		soundToPlay = playerLaserSFX;
		break;
	case playerLaserFinal:
		soundToPlay = playerLaserFinalSFX;
		break;
	case playerMissile:
		soundToPlay = playerMissileSFX;
		break;
	case playerWarp:
		soundToPlay = playerWarpSFX;
		break;
	case playerWell:
		soundToPlay = playerWellSFX;
		break;
	case playerPush:
		soundToPlay = playerPushSFX;
		break;
	case playerLevelUp:
		soundToPlay = playerLevelUpSFX;
		break;
	case enemyHullDamage:
		soundToPlay = enemyHullDamageSFX;
		break;
	case enemyShieldDamage:
		soundToPlay = enemyShieldDamageSFX;
		break;
	case cream:
		soundToPlay = creamMusic;
		break;
	case ambient:
		if (audio->IsAudioPlaying(slowTranceMusic)) audio->StopAudio(slowTranceMusic);
		soundToPlay = ambientMusic;
		break;
	case slowTrance:
		if (audio->IsAudioPlaying(ambientMusic)) audio->StopAudio(ambientMusic);
		soundToPlay = slowTranceMusic;
		break;
	case missileHit:
		soundToPlay = missileHitSFX;
		break;
	case copperheadE:
		soundToPlay = copperheadExplosion;
		break;
	case cobraE:
		soundToPlay = cobraExlosion;
		break;
	case mExplosion:
		soundToPlay = mediumExplosion;
		break;
	case cExplosion:
		soundToPlay = coralExplosion;
		break;
	case bossExplosion:
		soundToPlay = moccasinExplosion;
		break;

	default:
		break;
	}

	if (_loop && audio->IsAudioPlaying(soundToPlay))
		return;
	audio->PlayAudio(soundToPlay, _loop);
}
