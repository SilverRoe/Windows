#pragma once

class CServiceBase : public IService
{
public:
	CServiceBase(void);
	~CServiceBase(void);

	virtual LPTSTR GetServiceName();
	VOID ReportSvcStatus(DWORD dwCurrentState, DWORD dwWin32ExitCode, DWORD dwWaitHint);

protected:
	SERVICE_STATUS_HANDLE m_svcStatusHandle;
	SERVICE_STATUS m_svcStatus;

	wstring m_strSvcName;
};
