#include "MemoryTracer.h"
#include "MemoryAllocator.h"
#include "UtilLog.h"
#include "Loger.h"
#include "UtilString.h"
#include <fstream>
#include <format>
#include <string>
#include <conio.h>

static int g_LastId = 0;
static int g_StartCallStackIndex = 3;
static int g_MaxCallStackIndex = 16;

CMemoryTracer* CMemoryTracer::Instance = nullptr;

CMemoryTracer::CMemoryTracer()
	: MemorySize(0)
{

}

CMemoryTracer::~CMemoryTracer()
{
#ifdef USE_LOGER
	PrintMemoryBlockAll();
#endif
	// 파일로 기록한다
	//_CreateMemoryLeakLogFile();  //파일로 기록하려면 CreatMemoryLeaK 함수 주석해지

	for (std::pair<const void*, MemoryBlock*> memoryBlockPair : MemoryBlockMap)
	{
		MemoryBlock* memoryBlock = memoryBlockPair.second;
		if (memoryBlock)
			delete memoryBlock;
	}

	MemoryBlockMap.clear();
}

CMemoryTracer* CMemoryTracer::GetInstance()
{
	if (!Instance)
	{
		Instance = new CMemoryTracer();
	}
	return Instance;
}

bool CMemoryTracer::IsVaild()
{
	return Instance ? true : false;
}

void CMemoryTracer::DestroyInstance()
{
	if (Instance)
	{
		delete Instance;
		Instance = nullptr;
	}
}

void CMemoryTracer::Init()
{
	ThreadId = std::this_thread::get_id();
}

void CMemoryTracer::OnAllocated(void* InAddress, size_t InSize)
{
	if (!InAddress || ThreadId != std::this_thread::get_id())
		return;

	SetDefaultMemoryAllocator();

	CallStack stack;

	MemorySize += InSize;

	MemoryBlock* memoryBlock = new MemoryBlock();
	memoryBlock->Size = InSize;
	memoryBlock->Id = g_LastId++;
	memoryBlock->CallStack = std::make_shared<CallStack>(stack);
	MemoryBlockMap[InAddress] = memoryBlock;

	SetCustomMemoryAllocator();
}

void CMemoryTracer::OnDeallocated(void* InAddress)
{
	if (ThreadId != std::this_thread::get_id())
		return;

	SetDefaultMemoryAllocator();

	auto iter = MemoryBlockMap.find(InAddress);
	if (iter != MemoryBlockMap.end())
	{
		MemoryBlock* memoryBlock = iter->second;
		MemorySize -= memoryBlock->Size;

		if (memoryBlock)
			delete memoryBlock;

		MemoryBlockMap.erase(iter);
	}

	SetCustomMemoryAllocator();
}

void CMemoryTracer::PrintMemoryBlockAll()
{
	if (MemoryBlockMap.empty())
		return;

	int index = 0;
	String logMessage = "Remain Object Count : " + std::to_string(MemoryBlockMap.size()) + "..";
	WARN_LOG(logMessage);
	logMessage = "Leak Memory Size: " + std::to_string(MemorySize) + " Bytes..";
	WARN_LOG(logMessage);
	for (const std::pair<const void*, MemoryBlock*>& memoryBlockPair : MemoryBlockMap)
	{
		String message = "Leak #" + std::to_string(index++);
		WARN_LOG(message);

		const MemoryBlock* memoryBlock = memoryBlockPair.second;
		_PrintMemoryBlock(memoryBlock);
	}
	WARN_LOG("End ==========================================");

	auto ret = _getch();
}

void CMemoryTracer::_PrintMemoryBlock(const MemoryBlock* InMemoryBlock)
{
	for (size_t i = g_StartCallStackIndex; i < InMemoryBlock->CallStack->GetCount(); ++i)
	{
		if (i > g_MaxCallStackIndex)
			break;;

		String message = Lookup.GetSymbolString((*InMemoryBlock->CallStack)[i]);
		if (!message.empty())
		{
			EMPTY_LOG("#" + std::to_string(i - g_StartCallStackIndex) + " : " + message);
		}
		else
		{
			EMPTY_LOG("#" + std::to_string(i - g_StartCallStackIndex) + " : 알수 없는 외부 코드");
		}
	}
	EMPTY_LOG("");
}

void CMemoryTracer::_CreateMemoryLeakLogFile()
{
	if (MemoryBlockMap.empty())
		return;

	::CreateDirectory(L"Log", NULL);

	SYSTEMTIME st = { 0 };
	::GetLocalTime(&st);
	std::wstring memoryLogFileName = STRING(L"Log/MemoryLeak %d-%d-%d %d-%d.txt", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute);
	std::ofstream file(memoryLogFileName.c_str(), std::ios_base::out);

	file << "Remain Object Count : " + std::to_string(MemoryBlockMap.size()) + ".." << "\n";
	file << "Leak Memory Size: " + std::to_string(MemorySize) + " Bytes.." << "\n";
	int index = 0;
	for (const std::pair<const void*, MemoryBlock*>& memoryBlockPair : MemoryBlockMap)
	{
		file << "Leak #" + std::to_string(index++) << "\n";

		const MemoryBlock* memoryBlock = memoryBlockPair.second;
		for (size_t i = g_StartCallStackIndex; i < memoryBlock->CallStack->GetCount(); ++i)
		{
			if (i > g_MaxCallStackIndex)
				break;;

			String message = Lookup.GetSymbolString((*memoryBlock->CallStack)[i]);
			if (!message.empty())
			{
				file << ("#" + std::to_string(i - g_StartCallStackIndex) + " : " + message) << "\n";
			}
			else
			{
				file << ("#" + std::to_string(i - g_StartCallStackIndex) + " : 알수 없는 외부 코드") << "\n";
			}
		}
	}
	file.close();
}
