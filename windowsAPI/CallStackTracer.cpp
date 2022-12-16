#include "CallStackTracer.h"
#include "UtilLog.h"

String SymbolLookup::GetSymbolString(void* InAddress) const
{
	if (!InAddress)
		return "";

	DWORD displacement = 0;
	DWORD64 addr = reinterpret_cast<DWORD64>(InAddress);
	SymbolBuffer symbol;
	char buffer[StrBufferSize] = { 0, };

	IMAGEHLP_LINE64 line;
	line.SizeOfStruct = sizeof(IMAGEHLP_LINE64);

	SymFromAddr(Handle, addr, 0, &symbol);

	bool ret = SymGetLineFromAddr64(Handle, addr, &displacement, &line);
	if (ret)
		sprintf_s(buffer, StrBufferSize, "%s(%d) : %s", line.FileName, line.LineNumber, symbol.Name);
	else
		return "";

	return String(buffer);
}
