#pragma once
#include "MemoryTracer.h"
#include <functional>
#include <stdlib.h>

class IMemoryAllocator
{
public:
	virtual void* New(size_t InSize) = 0;

	virtual void Delete(void* InAddress) = 0;
};

class DefaultMemoryAllocator : public IMemoryAllocator
{
public:
	virtual void* New(size_t InSize) override final
	{
		return malloc(InSize);
	}

	virtual void Delete(void* InAddress) override final
	{
		free(InAddress);
	}
};

class CustomMemoryAllocator : public IMemoryAllocator
{
public:
	virtual void* New(size_t InSize) override final
	{
		void* ptr = malloc(InSize);

		if(ptr && CMemoryTracer::IsVaild() )
			CMemoryTracer::GetInstance()->OnAllocated(ptr, InSize);

		return ptr;
	}

	virtual void Delete(void* InAddress) override final
	{
		free(InAddress);

		if(CMemoryTracer::IsVaild())
			CMemoryTracer::GetInstance()->OnDeallocated(InAddress);
	}
};

extern IMemoryAllocator* GMemoryAllocator;
extern IMemoryAllocator* GPrevMemoryAllocator;

void SetDefaultMemoryAllocator();
void SetCustomMemoryAllocator();
void DestoryMemoryAllocator();

void NotTraceAllocate(const std::function<void()>& InFunction);