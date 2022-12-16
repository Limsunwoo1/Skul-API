#include "Loger.h"
#include "UtilLog.h"
#include "CallStackTracer.h"
#include "MemoryAllocator.h"
#include <Windows.h>
#include <mutex>
std::mutex logMutex;

static bool WaitEndThread = true;
static bool RunLogThread = true;

CLoger* CLoger::Instance = nullptr;

CLoger::CLoger()
	: LogThread(nullptr)
{

}

CLoger::~CLoger()
{
	logMutex.lock();
	logMutex.unlock();

	ThreadPtr endThread = new Thread(ThreadEnd);
	if (endThread)
		endThread->join();


	if (LogThread)
		delete LogThread;

	if (endThread)
		delete endThread;

	LogThread = nullptr;
}

CLoger* CLoger::GetInstance()
{
	if (!Instance)
	{
		SetDefaultMemoryAllocator();

		Instance = new CLoger();

		SetCustomMemoryAllocator();
	}
	return Instance;
}

void CLoger::DistroyInstance()
{
	if (GetInstance())
		delete GetInstance();
}


void CLoger::Init()
{
	SetDefaultMemoryAllocator();

	LogThread = new Thread(CLoger::LogUpdate);

	SetCustomMemoryAllocator();

	if (LogThread)
		LogThread->detach();

}

void CLoger::AddLogMessage(const LogMessage& InLogMessage)
{
	SetDefaultMemoryAllocator();

	ThreadPtr pushLogThread = new Thread(ThreadAddLog, InLogMessage);
	if (pushLogThread)
		pushLogThread->join();

	delete pushLogThread;

	SetCustomMemoryAllocator();
}

void CLoger::PushLogMessage(const LogMessage& InLogMessage)
{
	logMutex.lock();

	LogStack.push(InLogMessage);

	logMutex.unlock();
}

LogMessage CLoger::PopLogMessage()
{
	logMutex.lock();

	LogMessage message = LogStack.front();
	LogStack.pop();

	logMutex.unlock();
	return message;
}

void CLoger::AddCallStackLog()
{
	SymbolLookup lookup;
	CallStack stack;

	ETC3_LOG("Start Call Stack");
	for (size_t i = 2; i < stack.GetCount(); ++i)
	{
		String message = lookup.GetSymbolString(stack[i]);
		if (!message.empty())
			LOG(message.c_str());
	}
	ETC3_LOG("End Call Stack");
}

// LogUpdate 는 스태틱 함수기 때문에 멤버변수 바로 접근이 안된다
void CLoger::LogUpdate()
{
	while (RunLogThread)
	{
		if (LOG_STACK.size() == 0)
			continue;

		LogMessage message = LOGER->PopLogMessage();
		if (message.LogType == ELogType::Max)
			continue;

		String typeMessage = String(" [ ETC ] ");
		ELogColor logColorType = ELogColor::BLACK;
		if (message.LogType == ELogType::None)
		{
			typeMessage = String(" [ LOG ] ");
			logColorType = ELogColor::BLACK;
		}
		else if (message.LogType == ELogType::Warn)
		{
			typeMessage = String(" [ WARN ] ");
			logColorType = ELogColor::LIGHTRED;
		}
		else if (message.LogType == ELogType::Error)
		{
			typeMessage = String(" [ ERROR ] ");
			logColorType = ELogColor::RED;
		}
		else if (message.LogType == ELogType::Custom1)
		{
			logColorType = ELogColor::LIGHTBLUE;
		}
		else if (message.LogType == ELogType::Custom2)
		{
			logColorType = ELogColor::LIGHTGREEN;
		}
		else if (message.LogType == ELogType::Empty)
		{
			logColorType = ELogColor::BLACK;
		}
		else // ELogType::Custom3 || ELogType::Max
		{
			logColorType = ELogColor::LIGHTGRAY;
		}

		int logColor = (int)ELogColor::WHITE + (int)logColorType * 16;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), logColor);
		if (message.LogType == ELogType::Empty)
		{
			std::cout << message.Message << "\n";
		}
		else
		{
			std::cout << message.FunctionName << "() :: line : " << message.LineNumber << typeMessage;
			std::cout << message.Message << "\n";
		}
	}

	WaitEndThread = false;
	std::cout << "Log Thread End" << "\n";
}

void CLoger::ThreadAddLog(const LogMessage& InLogMessage)
{
	LOGER->PushLogMessage(InLogMessage);
}

void CLoger::ThreadEnd()
{
	RunLogThread = false;
	while (WaitEndThread)
	{
		std::cout << "WaitEndThread" << "\n";
	}
	std::cout << "ThreadEnd" << "\n";
}