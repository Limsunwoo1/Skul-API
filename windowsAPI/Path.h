#pragma once
#include "UtilString.h"
// 리소스 경로
// 기본 스컬
#define BASICSKUL_R_PATH(path) STRING(L"..\\Resource\\Animation\\BasicSkul\\R_Basic\\%s", path)
#define BASICSKUL_L_PATH(path) STRING(L"..\\Resource\\Animation\\BasicSkul\\L_Basic\\%s", path)
// 소드 스컬
#define SWORDSKUL_R_PATH(path) STRING(L"..\\Resource\\Animation\\SwordSkul\\R_Sword\\%s", path)
#define SWORDSKUL_L_PATH(path) STRING(L"..\\Resource\\Animation\\SwordSkul\\L_Sword\\%s", path)
// 사무라이
#define SAMURAI_R_PATH(path) STRING(L"..\\Resource\\Animation\\Samurai\\R_Samurai\\%s", path)
#define SAMURAI_L_PATH(path) STRING(L"..\\Resource\\Animation\\Samurai\\L_Samurai\\%s", path)
// 소드 몬스터
#define SWORDMONSTER_R_PATH(path) STRING(L"..\\Resource\\Animation\\Monster\\2_Stage\\R_knightMonster\\%s", path)
#define SWORDMONSTER_L_PATH(path) STRING(L"..\\Resource\\Animation\\Monster\\2_Stage\\L_knightMonster\\%s", path)
// 도끼 몬스터
#define AXEMONSTER_R_PATH(path) STRING(L"..\\Resource\\Animation\\Monster\\2_Stage\\R_AxeMonster\\%s", path)
#define AXEMONSTER_L_PATH(path) STRING(L"..\\Resource\\Animation\\Monster\\2_Stage\\L_AxeMonster\\%s", path)
// 메이드 몬스터 1
#define MAIDMONSTER_1_R_PATH(path) STRING(L"..\\Resource\\Animation\\Monster\\2_Stage\\R_Maid_1\\%s", path)
#define MAIDMONSTER_1_L_PATH(path) STRING(L"..\\Resource\\Animation\\Monster\\2_Stage\\L_Maid_1\\%s", path)
// 2ChBoss
#define LEIANABOSS_GOLD_PATH STRING(L"..\\Resource\\Animation\\2CH_Boss\\Gold\\")

// 스컬 공용 이펙트
// 대쉬스모크
#define L_SKUL_DASHSMOKE STRING(L"L_DashSmoke")
#define R_SKUL_DASHSMOKE STRING(L"R_DashSmoke")
// 점프스모크
#define SKUL_JUMPSMOKE STRING(L"JumpSmoke")

// EFFECT KEY
// 기본스컬 공격시 피격 이펙트
#define L_BASICSKUL_HITEFT STRING(L"L_BasicSkul_HitEft")
#define R_BASICSKUL_HITEFT STRING(L"R_BasicSkul_HitEft")
// 소드스컬 슬래쉬 이펙트
#define L_SWORDSKUL_SLASHEFT STRING(L"L_SwordSkul_SlashEft")
#define R_SWORDSKUL_SLASHEFT STRING(L"R_SwordSkul_SlashEft")
