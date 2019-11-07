#pragma once

class CService2 : public CServiceBase
{
public:
	CService2(void);
	~CService2(void);

	static CService2 *getInstance()
	{
		static CService2 service2;
		return &service2;
	}

	static VOID WINAPI Service2Main(DWORD dwArgc, LPTSTR* lpszArgv);
	static VOID WINAPI Service2CtrlHandler(DWORD dwCtrl);

	virtual void Run(DWORD dwArgc, LPTSTR* lpszArgv);
	virtual void Stop();

private:
	HANDLE m_hSvcStopEvent;
};
