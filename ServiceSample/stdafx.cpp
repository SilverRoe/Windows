// stdafx.cpp : source file that includes just the standard includes
// ServiceSample.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file

void OutputDebugInfo(LPCTSTR szFormat, ...)
{
	va_list args;
	va_start(args, szFormat);

	wchar_t szBuffer[1028] = {0};
	wvsprintfW(szBuffer, szFormat, args);
	OutputDebugString(szBuffer);

	va_end(args);
}