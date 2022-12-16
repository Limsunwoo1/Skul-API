#include "MemoryAllocator.h"

extern IMemoryAllocator* GMemoryAllocator = new DefaultMemoryAllocator();

extern IMemoryAllocator* GDefaultMemoryAllocator = GMemoryAllocator;
extern IMemoryAllocator* GCustomMemoryAllocator = new CustomMemoryAllocator();

// 아무런 기능이 없는 일반적인 메모리 얼로케이터
void SetDefaultMemoryAllocator()
{
#ifdef USE_MEMORY_TRACE
	GMemoryAllocator = GDefaultMemoryAllocator;
#endif
	return;
}

// new, delete 연산시 MemoryTracer 에게 메모리 할당 및 해제 정보를 넘겨줄 수 있는 메모리 얼로케이터
void SetCustomMemoryAllocator()
{
#ifdef USE_MEMORY_TRACE
	GMemoryAllocator = GCustomMemoryAllocator;
#endif
	return;
}

void DestoryMemoryAllocator()
{
	// GMemoryAllocator 를 nullptr 로 하지 않으면 다른 얼로케이터가 delete 되는 순간 로직이 꼬인다
	GMemoryAllocator = nullptr;

	if (GCustomMemoryAllocator)
		delete GCustomMemoryAllocator;

	if (GDefaultMemoryAllocator)
		delete GDefaultMemoryAllocator;

	GDefaultMemoryAllocator = GCustomMemoryAllocator = nullptr;
}

// 인자로 넣은 함수에서 실행되는 모든 new, delete 는 MemoryTracer 가 추적하지 않는다
// 주의) 해당 함수 내부에서 특정 객체가 new 만 이루어지거나 delete 만 이루어지는경우 정상 동작 보장은 안됨
void NotTraceAllocate(const std::function<void()>& InFunction)
{
	SetDefaultMemoryAllocator();

	InFunction();

	SetCustomMemoryAllocator();
}
