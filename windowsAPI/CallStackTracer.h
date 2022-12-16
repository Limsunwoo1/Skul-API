#pragma once
#include "Typedef.h"
#include <Windows.h>
#include <DbgHelp.h>
#include <memory>
#pragma comment(lib, "dbghelp.lib")

class CallStack
{
public:
	static const size_t MaxStackDepth = 16U;

private:
	void*	AddressList[MaxStackDepth];
	ULONG	Hash;
	size_t	Count;

public:
	// 생성되는 시점에 스택을 역추적해온다
	explicit CallStack()
	{
		Count = CaptureStackBackTrace(0, MaxStackDepth, AddressList, &Hash);
	}

	void* operator[] (const size_t InIndex) const { return AddressList[InIndex]; }

	ULONG GetHash() const { return Hash; }
	size_t GetCount() const { return Count; }
};

typedef std::shared_ptr<CallStack> CallStackPtr;

struct SymbolBuffer : public SYMBOL_INFO
{
	SymbolBuffer()
	{
		MaxNameLen = static_cast<ULONG>(BufferSize);
		SizeOfStruct = sizeof(SYMBOL_INFO);
	}

	static const size_t BufferSize = 256U;
	char Buffer[BufferSize] = {};
};

class SymbolLookup
{
public:
	SymbolLookup() : Handle(GetCurrentProcess())
	{
		SymInitialize(Handle, nullptr, TRUE);
		SymSetOptions(SYMOPT_LOAD_LINES);
	}

	String GetSymbolString(void* InAddress) const;

private:
	const static size_t StrBufferSize = 1024U;

private:
	HANDLE Handle;
};