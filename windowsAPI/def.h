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
	static void DistroyInstance()			\
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

enum class eSceneType
{
	Logo,
	Title,
	Play,
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
	Transparent, // ≈ı∏Ì
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
	Player,
	Monster,

	Player_ProjectTile,
	Monster_ProjectTile,

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

	SKILL_1,
	SKILL_2,

	SWITCH,
	HIT,
	DROP,

	END,
};

enum class eUIType
{
	HP,
	MP,
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