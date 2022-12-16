#include "CrashHandler.h"
#include "MemoryAllocator.h"
#include "UtilString.h"
#include <fstream>

CCrashHandler* volatile CCrashHandler::Instance = nullptr;
std::mutex CCrashHandler::Mutex;

CCrashHandler::CCrashHandler()
{

}

CCrashHandler::~CCrashHandler()
{

}

CCrashHandler* volatile CCrashHandler::GetInstance()
{
	if (Instance == nullptr)
	{
		std::lock_guard<std::mutex> lock(Mutex);
		Instance = new CCrashHandler();
	}

	return Instance;
}

// 크래시 핸들러를 초기화한다.
void CCrashHandler::Init()
{
	PrevFilter = ::SetUnhandledExceptionFilter(Exception_Callback);
}

// 핸들링 되지 않은 익셉션 상황 ( 크래시 ) 가 발생하는 경우 수행하는 로직
LONG CCrashHandler::Exception_Callback(__in struct _EXCEPTION_POINTERS* InExceptionPtr)
{
	do {
		if (InExceptionPtr == nullptr)
			break;

		SYSTEMTIME st = { 0 };
		::GetLocalTime(&st);
		::CreateDirectory(L"Log", NULL);

		wstring crashLogFileName = STRING(L"Log/Crash %d-%d-%d %d-%d.txt", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute);
		wstring crashDumpFileName = STRING(L"Log/Crash %d-%d-%d %d-%d.dmp", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute);
		std::ofstream file(crashLogFileName.c_str(), std::ios_base::out);
		SymbolLookup lookup;
		CallStack stack;
		int index = 0;
		for (size_t i = 1; i < stack.GetCount(); ++i)
		{
			String message = lookup.GetSymbolString(stack[i]);
			if (!message.empty())
				file << "#" << index++ << " : " << message.c_str() << "\n";
			else
				file << "#" << index++ << " : " << "알 수 없는 외부코드 \n";
		}
		file.close();

		HANDLE dumpFileHandle = ::CreateFile(
			crashDumpFileName.c_str(),
			GENERIC_WRITE,
			0,
			nullptr,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			nullptr
		);

		if (dumpFileHandle == INVALID_HANDLE_VALUE)
			break;

		MINIDUMP_EXCEPTION_INFORMATION exceptionInfo = { 0 };

		exceptionInfo.ThreadId = ::GetCurrentThreadId();
		exceptionInfo.ExceptionPointers = InExceptionPtr;
		exceptionInfo.ClientPointers = FALSE;

		if (!::MiniDumpWriteDump(
			::GetCurrentProcess(),
			::GetCurrentProcessId(),
			dumpFileHandle,
			MINIDUMP_TYPE::MiniDumpNormal,
			&exceptionInfo,
			nullptr,
			nullptr
		))
		{
			break;
		}

	} while (false);

	return CCrashHandler::GetInstance()->PrevFilter ?
		CCrashHandler::GetInstance()->PrevFilter(InExceptionPtr) :
		EXCEPTION_EXECUTE_HANDLER;
}