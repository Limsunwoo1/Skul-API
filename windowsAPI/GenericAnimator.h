#pragma once
#include <functional>

// Invalid 값이라는거는 작동하지 않는 무의미한 상태를 나타내는 아이디
const	int InvalidHandleId = 0;
static	int HandleId = 0;

// 매 틱 혹은 애니메이션이 끝났을때 호출하는 함수 타입
typedef std::function<void(float)> FAnimEvent;

// 애니메이션이 어떻게 변화하는지
enum class EAnimType {
	Linear,				// 일단 단순하게 선형보간 천천히 균일하게 증가
	Max,
};

typedef struct _AnimatorParam
{
	int Handle;
	EAnimType AnimType;

	float StartValue;
	float EndValue;

	float DurationTime;

	FAnimEvent DurationFunc;
	FAnimEvent CompleteFunc;

	_AnimatorParam() : Handle(InvalidHandleId), AnimType(EAnimType::Linear), StartValue(0.f), EndValue(1.f), DurationTime(1.f), DurationFunc(nullptr), CompleteFunc(nullptr) {}

}AnimatorParam;

class GenericAnimator
{
private:
	AnimatorParam Param;

	float StartValue;
	float CurValue;
	float EndValue;

	float AccTime;
	float EndTime;

public:
	GenericAnimator();
	~GenericAnimator();

	bool Start(const AnimatorParam& InParam);
	void Update(float InDeltaTime);

	bool IsRunning();
	void Stop(bool InCompleteEvent = false);
};