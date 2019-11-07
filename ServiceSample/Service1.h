#pragma once

class CService1 : public CServiceBase
{
public:
	CService1(void);
	~CService1(void);

	static CService1 *getInstance()
	{
		static CService1 service1;
		return &service1;
	}

	static VOID WINAPI Service1Main(DWORD dwArgc, LPTSTR* lpszArgv);
	static VOID WINAPI Service1CtrlHandler(DWORD dwCtrl);

	virtual void Run(DWORD dwArgc, LPTSTR* lpszArgv);
	virtual void Stop();

private:
	HANDLE m_hSvcStopEvent;
};
