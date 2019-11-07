#include "StdAfx.h"
#include "Service2.h"

CService2::CService2(void)
: m_hSvcStopEvent(NULL)
{
	m_strSvcName = L"Service2";
}

CService2::~CService2(void)
{
}

void CService2::Run( DWORD dwArgc, LPTSTR* lpszArgv )
{
	OutputDebugInfo(L"Service2 begin to run...");

	m_svcStatusHandle = RegisterServiceCtrlHandler(
		m_strSvcName.c_str(),
		CService2::Service2CtrlHandler);

	if (!m_svcStatusHandle)
	{
		OutputDebugInfo(L"RegisterServiceCtrlHandler, Gle:0x%08x", GetLastError());
		return;
	}

	m_svcStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
	m_svcStatus.dwServiceSpecificExitCode = 0;

	ReportSvcStatus(SERVICE_START_PENDING, NO_ERROR, 3000);

	m_hSvcStopEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	if (m_hSvcStopEvent == NULL)
	{
		ReportSvcStatus(SERVICE_STOPPED, NO_ERROR, 0);
		return;
	}
	ReportSvcStatus(SERVICE_RUNNING, NO_ERROR, 0);

	while (1)
	{
		WaitForSingleObject(m_hSvcStopEvent, INFINITE);
		ReportSvcStatus(SERVICE_STOPPED, NO_ERROR, 0);
		return;
	}
}

void CService2::Stop()
{
	ReportSvcStatus(SERVICE_STOP_PENDING, NO_ERROR, 0);
	SetEvent(m_hSvcStopEvent);
	ReportSvcStatus(m_svcStatus.dwCurrentState, NO_ERROR, 0);
}

VOID WINAPI CService2::Service2Main( DWORD dwArgc, LPTSTR* lpszArgv )
{
	CService2::getInstance()->Run(dwArgc, lpszArgv);
}

VOID WINAPI CService2::Service2CtrlHandler( DWORD dwCtrl )
{
	switch (dwCtrl)
	{
	case SERVICE_CONTROL_STOP:
		CService2::getInstance()->Stop();
		return;
	case SERVICE_CONTROL_INTERROGATE:
		break;
	default:
		break;
	}
}