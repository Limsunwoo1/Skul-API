#pragma once

#define SINGLE(type)						\
public:										\
	static type* GetInstance()				\
	{										\
		static type* mInstance;				\
		if (mInstance == nullptr)			\
		{									\
			mInstance = new type();			\
			return mInstance;				\
		}									\
		return mInstance;					\
	}										\
											\
	static void DestroyInstance()			\
	{										\
	if (GetInstance())						\
		delete GetInstance();				\
	}										\
											\
private:									\
	type();									\
	~type();								\


#define KEY_PRESSE(KEY) sw::Input::GetInstance()->GetkeyState(KEY) == sw::eKeyState::PRESSED
#define KEY_DOWN(KEY) sw::Input::GetInstance()->GetkeyState(KEY) == sw::eKeyState::DOWN
#define KEY_UP(KEY) sw::Input::GetInstance()->GetkeyState(KEY) == sw:: eKeyState::UP

#ifdef _DEBUG						// 디버그 모드에서 사용할지 여부
//#	define USE_MEMORY_TRACE
#	define USE_LOGER
#else								// 릴리즈 모드에서 사용할지 여부
#	define USE_MEMORY_TRACE
//#	define USE_LOGER
#	define USE_CRASH_HANDLER		// 크래시 핸들러는 디버깅 모드에서는 동작안한다.
#endif

enum class eSceneType
{
	Logo,
	Start,
	Play,
	Play2,
	Ch2Boss,
	End,
	Tool,
	Max,
};

enum class ePenColor
{
	Red,
	Green,
	Blue,
	End,
};

enum class eBrushColor
{
	Transparent, // 투명
	Black,
	Gray, // 71, 71, 71
	White,
	End,
};

enum class eComponentType
{
	Rigidbody,
	Animator,
	Collider,
	Sound,
	End
};

#define COLLIDER_LAYER 16

enum class eColliderLayer : short
{
	Default,
	BackGround,
	Ground,
	Tile,
	StaticObject,
	Gate,
	Item,
	Monster,
	NamedMonster,
	BossMonster,
	Player,

	Monster_ProjecTile,
	NamedMonster_Monster_ProjecTile,
	BossMonster_ProjecTile,
	Player_ProjecTile,

	EFFECT,
	UI = COLLIDER_LAYER - 1,
	END = COLLIDER_LAYER,
};

enum class eCameraEffect
{
	FadeIn,
	FadeOut,
	None,
};

enum class ePlayerState
{
	IDLE,

	UP,
	DOWN,
	MOVE,

	JUMP,
	DOUBLEJUMP,

	SLIDING,
	DOUBLESLIDING,

	ATTACK,
	JUMPATTACK,

	SKILL_A,
	SKILL_B,

	SWITCH,
	HIT,
	DROP,

	END,
};

enum class eSkulHead
{
	Basic,
	Sword,
	Samurai,
	End,
};

enum class eUIType
{
	HP_PANEL,
	Character_Panel,
	Skil_Panel,
	Character_MainHead,
	Character,
	Skil,
	HP,
	MP,
	MonsterHp_Panel,
	MonsterHp,

	SHOP,
	INVENTORY,
	OPTION,


	END,
};

union ColliderID
{
	struct
	{
		UINT32 left;
		UINT32 right;
	};

	UINT64 ID;

	ColliderID()
	{

	}

	ColliderID(UINT32 Inleft, UINT32 Inright)
	{
		left = Inleft;
		right = Inright;
	}
};

typedef ColliderID TileID;

#define TILE_SIZE 32
#define TILE_SCALE 2

#define TILE_LINE_X 10
#define TILE_LINE_Y 4