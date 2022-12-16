#pragma once
#include <iostream>
#include <thread>
#include <queue>
#include "def.h"

typedef std::string  String;


enum class ELogType {
	None,		// 일반적인 상황에 출력하는 로그			( 중요도 낮음 )
	Warn,		// 경고 상황에 출력하는 로그				( 중요도 중간 )
	Error,		// 에러 상황에 출력하는 로그				( 중요도 높음, 치명적인 상황 )
	Custom1,	// 개발 중에 특별하게 확인이 필요한 로그1	( 중요도 미정 )
	Custom2,	// 개발 중에 특별하게 확인이 필요한 로그2	( 중요도 미정 )
	Custom3,	// 개발 중에 특별하게 확인이 필요한 로그3	( 중요도 미정 )
	Empty,		// 함수이름, 라인명 없이 메시지만 띄우는 로그
	Max,
};

enum class ELogColor {
	BLACK = 0,
	BLUE = 1,
	GREEN = 2,
	CYAN = 3,
	RED = 4,
	MAGENTA = 5,
	BROWN = 6,
	LIGHTGRAY = 7,
	DARKGRAY = 8,
	LIGHTBLUE = 9,
	LIGHTGREEN = 10,
	LIGHTCYAN = 11,
	LIGHTRED = 12,
	LIGHTMAGENTA = 13,
	YELLOW = 14,
	WHITE = 15,
};

class LogMessage {
public:
	ELogType	LogType;
	String		FunctionName;
	int			LineNumber;
	String		Message;

public:
	LogMessage() : LogType(ELogType::Max), FunctionName(), LineNumber(0), Message() {}
	LogMessage(ELogType InType, String InFunction, int InLineNumber, String InMessage)
		: LogType(InType), FunctionName(InFunction), LineNumber(InLineNumber), Message(InMessage) {}
	~LogMessage() {}
};

class CLoger
{
private:
	typedef std::thread				Thread;
	typedef std::thread* ThreadPtr;
	typedef std::queue<LogMessage>	FLogStack;

private:
	CLoger();
	~CLoger();

	static CLoger* Instance;
public:
	static CLoger* GetInstance();
	static void DistroyInstance();
private:
	ThreadPtr	LogThread;
	FLogStack	LogStack;

public:
	void Init();

	void AddLogMessage(const LogMessage& InLogMessage);
	void PushLogMessage(const LogMessage& InLogMessage);
	LogMessage PopLogMessage();

	void AddCallStackLog();

	const FLogStack& GetLogStack() const { return LogStack; }

	static void LogUpdate();
	static void ThreadAddLog(const LogMessage& InLogMessage);
	static void ThreadEnd();
};
