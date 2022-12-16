#pragma once
#include "CallStackTracer.h"
#include "Typedef.h"
#include "UtilLog.h"
#include "Loger.h"
#include <stdlib.h>
#include <unordered_map>
#include "def.h"

class CMemoryTracer
{
private:
	class MemoryBlock 
	{
	public:
		int64			Id;
		size_t			Size;
		CallStackPtr	CallStack;
	};

	typedef std::unordered_map<const void*, MemoryBlock*> FMemoryBlockMap;

private:
	FMemoryBlockMap		MemoryBlockMap;
	std::thread::id		ThreadId;
	SymbolLookup		Lookup;
	unsigned long long	MemorySize;

private:
	CMemoryTracer();
	~CMemoryTracer();

	static CMemoryTracer* Instance;

public:
	static CMemoryTracer* GetInstance();

	static bool IsVaild();

	static void DestroyInstance();

	void Init();

	void OnAllocated(void* InAddress, size_t InSize);

	void OnDeallocated(void* InAddress);

	void PrintMemoryBlockAll();

private:
	void _PrintMemoryBlock(const MemoryBlock* InMemoryBlock);

	void _CreateMemoryLeakLogFile();
};