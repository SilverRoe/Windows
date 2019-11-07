// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <Windows.h>
#include <stdio.h>
#include <tchar.h>
#include <strsafe.h>

#include <string>
#include <map>
using namespace std;

#pragma comment(lib, "advapi32.lib")

#include "IService.h"
#include "ServiceBase.h"

extern void OutputDebugInfo(LPCTSTR szFormat, ...);
