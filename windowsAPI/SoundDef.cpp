#pragma once
#include "SoundDef.h"
#include "Sound.h"

namespace sw
{
	void SoundInit()
	{
		MainTitleSound.LoadWavFile(L"..\\Resource\\Sound\\MainTitle\\MainTitle.wav");
		MainTitleSound.SetVolume(20);
		MainTitleSound.SetKey(L"LogoSound");

		Ch1Sound.LoadWavFile(L"..\\Resource\\Sound\\Ch1\\Chapter1.wav");
		Ch1Sound.SetVolume(20);
		Ch1Sound.SetKey(L"Ch1Sound");

		BossSound.LoadWavFile(L"..\\Resource\\Sound\\Chapter2_Boss.wav");
		BossSound.SetVolume(20);
		BossSound.SetKey(L"BossSound");

		DashSound.LoadWavFile(L"..\\Resource\\Sound\\Dash\\Dash_Small.wav");
		DashSound.SetVolume(20);
		DashSound.SetKey(L"DashSound");

		JumpSound.LoadWavFile(L"..\\Resource\\Sound\\Jump\\Default_Jump_Air.wav");
		JumpSound.SetVolume(10);
		JumpSound.SetKey(L"JumpSound");

		DropHead.LoadWavFile(L"..\\Resource\\Sound\\Leiana_Intro_TakeOff.wav");
		DropHead.SetVolume(10);
		DropHead.SetKey(L"DropHead");
		/////////////////////////////////////////////////////////////////////////////////
		BasicSkulAttackA.LoadWavFile(L"..\\Resource\\Sound\\Basic\\Attack\\Skul_Atk 1.wav");
		BasicSkulAttackA.SetVolume(10);
		BasicSkulAttackA.SetKey(L"BasicAttackA");

		BasicSkulAttackB.LoadWavFile(L"..\\Resource\\Sound\\Basic\\Attack\\Skul_Atk 2.wav");
		BasicSkulAttackB.SetVolume(10);
		BasicSkulAttackB.SetKey(L"BasicAttackA");

		/// ///////////////////////////////////////////////////////////////////////////////
		SwordSkulSKillA.LoadWavFile(L"..\\Resource\\Sound\\Sword\\Skill\\SkeletonSword_ThawSlash.wav");
		SwordSkulSKillA.SetVolume(10);
		SwordSkulSKillA.SetKey(L"SwordSkulSkillA");

		SwordSkulSKillB.LoadWavFile(L"..\\Resource\\Sound\\Sword\\Skill\\SkeletonSpear_EnhancedRush.wav");
		SwordSkulSKillB.SetVolume(10);
		SwordSkulSKillB.SetKey(L"SwordSkulSkillB");

		SwordSkulSwitch.LoadWavFile(L"..\\Resource\\Sound\\Sword\\Skill\\021_FirstHero_P1_Enhanced_Rush_Finish_a_v1.wav");
		SwordSkulSwitch.SetVolume(10);
		SwordSkulSwitch.SetKey(L"SwordSkulSwitch");

		SwordSkulAttackA.LoadWavFile(L"..\\Resource\\Sound\\Sword\\Attack\\Atk_Sword_Small 3.wav");
		SwordSkulAttackA.SetVolume(10);
		SwordSkulAttackA.SetKey(L"SwordSkulAttackA");

		SwordSkulAttackB.LoadWavFile(L"..\\Resource\\Sound\\Sword\\Attack\\Atk_Sword_Small 4.wav");
		SwordSkulAttackB.SetVolume(10);
		SwordSkulAttackB.SetKey(L"SwordSkulAttackB");

		SwordSkulAttackC.LoadWavFile(L"..\\Resource\\Sound\\Sword\\Attack\\Atk_Sword_Small 5.wav");
		SwordSkulAttackC.SetVolume(10);
		SwordSkulAttackC.SetKey(L"SwordSkulAttackC");
		////////////////////////////////////////////////////////////////////// /
		SamuraiSkulAttackA.LoadWavFile(L"..\\Resource\\Sound\\samurai\\Attack\\Atk_Sword_Small 2.wav");
		SamuraiSkulAttackA.SetVolume(10);
		SamuraiSkulAttackA.SetKey(L"SamuraiSkulAttackA");

		SamuraiSkulAttackB.LoadWavFile(L"..\\Resource\\Sound\\samurai\\Attack\\Atk_Sword_Small 1.wav");
		SamuraiSkulAttackB.SetVolume(10);
		SamuraiSkulAttackB.SetKey(L"SamuraiSkulAttackB");

		SamuraiSkulAttackC.LoadWavFile(L"..\\Resource\\Sound\\samurai\\Attack\\Arm_AirAttackSmall.wav");
		SamuraiSkulAttackC.SetVolume(10);
		SamuraiSkulAttackC.SetKey(L"SamuraiSkulAttackC");

		SamuraiSkulSkillA.LoadWavFile(L"..\\Resource\\Sound\\samurai\\skill\\Samurai_2_FullMoonilseom_Ready.wav");
		SamuraiSkulSkillA.SetVolume(10);
		SamuraiSkulSkillA.SetKey(L"SamuraiSkulSkillA");

		SamuraiSkulSkillAHit.LoadWavFile(L"..\\Resource\\Sound\\samurai\\skill\\Samurai_IlSeomHit.wav");
		SamuraiSkulSkillAHit.SetVolume(10);
		SamuraiSkulSkillAHit.SetKey(L"SamuraiSkulSkillAHit");

		SamuraiSkulSkillAWind.LoadWavFile(L"..\\Resource\\Sound\\samurai\\Wind 2 - low volume.wav");
		SamuraiSkulSkillAWind.SetVolume(20);
		SamuraiSkulSkillAWind.SetKey(L"SamuraiSkulSkillAWind");

		SamuraiSkulSKillB.LoadWavFile(L"..\\Resource\\Sound\\samurai\\skill\\Samurai_Parry.wav");
		SamuraiSkulSKillB.SetVolume(10);
		SamuraiSkulSKillB.SetKey(L"SamuraiSkulSKillB");

		SamuraiSkulSwitch.LoadWavFile(L"..\\Resource\\Sound\\samurai\\Skill\\Atk_Sword_Thin.wav");
		SamuraiSkulSwitch.SetVolume(10);
		SamuraiSkulSwitch.SetKey(L"SamuraiSkulSwitch");
		///////////////////////////////////////////////////////////////////////////////////
	}
};