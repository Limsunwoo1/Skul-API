#include "MemoryAllocator.h"

//extern IMemoryAllocator* GMemoryAllocator = new DefaultMemoryAllocator();

//extern IMemoryAllocator* GDefaultMemoryAllocator = GMemoryAllocator;
//extern IMemoryAllocator* GCustomMemoryAllocator = new CustomMemoryAllocator();

// �ƹ��� ����� ���� �Ϲ����� �޸� ���������
//void SetDefaultMemoryAllocator()
//{
//#ifdef USE_MEMORY_TRACE
//	GMemoryAllocator = GDefaultMemoryAllocator;
//#endif
//	return;
//}
//
//// new, delete ����� MemoryTracer ���� �޸� �Ҵ� �� ���� ������ �Ѱ��� �� �ִ� �޸� ���������
//void SetCustomMemoryAllocator()
//{
//#ifdef USE_MEMORY_TRACE
//	GMemoryAllocator = GCustomMemoryAllocator;
//#endif
//	return;
//}

void DestoryMemoryAllocator()
{
	// GMemoryAllocator �� nullptr �� ���� ������ �ٸ� ��������Ͱ� delete �Ǵ� ���� ������ ���δ�
	//GMemoryAllocator = nullptr;

	//if (GCustomMemoryAllocator)
		//delete GCustomMemoryAllocator;

	// (GDefaultMemoryAllocator)
		// GDefaultMemoryAllocator;

	//GDefaultMemoryAllocator = GCustomMemoryAllocator = nullptr;
}

// ���ڷ� ���� �Լ����� ����Ǵ� ��� new, delete �� MemoryTracer �� �������� �ʴ´�
// ����) �ش� �Լ� ���ο��� Ư�� ��ü�� new �� �̷�����ų� delete �� �̷�����°�� ���� ���� ������ �ȵ�
void NotTraceAllocate(const std::function<void()>& InFunction)
{
	//SetDefaultMemoryAllocator();

	//InFunction();

	//SetCustomMemoryAllocator();
}
