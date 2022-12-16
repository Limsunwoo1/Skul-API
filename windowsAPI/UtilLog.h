#pragma once
#include "Loger.h"

#define _QUOTE(x)			# x
#define QUOTE(x)			_QUOTE(x)

#define __FILE__LINE__		__FILE__ "(" QUOTE(__LINE__) ") : "
#define FILE_LINE			message(__FILE__LINE__)

#define todo(x)				message(__FILE__LINE__"[ TODO ] " ##x "\n")
#define fixme(x)			message(__FILE__LINE__"[ FIXME ] " ##x "\n")

#ifdef USE_LOGER
#	define LOG_TODO(x)		__pragma(todo(x))
#	define LOG_FIXME(x)		__pragma(fixme(x))
#else
#	define LOG_TODO(x)
#	define LOG_FIXME(x)
#endif

#define LOGER				CLoger::GetInstance()
#define LOG_STACK			CLoger::GetInstance()->GetLogStack()
#define LOG_MUTEX			CLoger::GetInstance()->GetLogMutex()

#ifdef USE_LOGER
#	define LOG(x)			LOGER->AddLogMessage(LogMessage(ELogType::None, __FUNCTION__, __LINE__, x));
#	define WARN_LOG(x)		LOGER->AddLogMessage(LogMessage(ELogType::Warn, __FUNCTION__, __LINE__, x));
#	define ERROR_LOG(x)		LOGER->AddLogMessage(LogMessage(ELogType::Error, __FUNCTION__, __LINE__, x));
#	define ETC1_LOG(x)		LOGER->AddLogMessage(LogMessage(ELogType::Custom1, __FUNCTION__, __LINE__, x));
#	define ETC2_LOG(x)		LOGER->AddLogMessage(LogMessage(ELogType::Custom2, __FUNCTION__, __LINE__, x));
#	define ETC3_LOG(x)		LOGER->AddLogMessage(LogMessage(ELogType::Custom3, __FUNCTION__, __LINE__, x));
#	define EMPTY_LOG(x)		LOGER->AddLogMessage(LogMessage(ELogType::Empty, __FUNCTION__, __LINE__, x));
#else
#	define LOG(x)
#	define WARN_LOG(x)
#	define ERROR_LOG(x)
#	define ETC1_LOG(x)
#	define ETC2_LOG(x)
#	define ETC3_LOG(x)
#	define EMPTY_LOG(x)	
#endif