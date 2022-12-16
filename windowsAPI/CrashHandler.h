#pragma once
#include <windows.h>
#include <mutex>
#include <iostream>

#pragma warning(push)
#pragma warning(disable: 4091)
#include <dbghelp.h>
#pragma warning(pop)

#pragma comment(lib, "Dbghelp.lib")


class CCrashHandler
{
private:
	static CCrashHandler* volatile	Instance;
	static std::mutex				Mutex;

	CCrashHandler();
	~CCrashHandler();

public:
	static CCrashHandler* volatile GetInstance();

private:
	LPTOP_LEVEL_EXCEPTION_FILTER	PrevFilter;

public:
	void Init();

	static LONG WINAPI Exception_Callback(
		__in struct _EXCEPTION_POINTERS* InExceptionPtr
	);
};

