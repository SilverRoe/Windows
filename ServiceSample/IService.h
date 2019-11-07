#pragma once

class IService
{
public:
	virtual LPTSTR GetServiceName() = 0;
	virtual void Run(DWORD dwArgc, LPTSTR* lpszArgv) = 0;
	virtual void Stop() = 0;
};