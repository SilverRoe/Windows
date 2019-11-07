#include "StdAfx.h"
#include "Service1.h"

CService1::CService1(void)
: m_hSvcStopEvent(NULL)
{
	m_strSvcName = L"Service1";
}

CService1::~CService1(void)
{
	OutputDebugInfo(L"Service1 begin to run...");
}

void CService1::Run( DWORD dwArgc, LPTSTR* lpszArgv )
{
	OutputDebugInfo(L"Service1 begin to run...");

	m_svcStatusHandle = RegisterServiceCtrlHandler(
		m_strSvcName.c_str(),
		CService1::Service1CtrlHandler);

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

void CService1::Stop()
{
	ReportSvcStatus(SERVICE_STOP_PENDING, NO_ERROR, 0);
	SetEvent(m_hSvcStopEvent);
	ReportSvcStatus(m_svcStatus.dwCurrentState, NO_ERROR, 0);
}

VOID WINAPI CService1::Service1Main( DWORD dwArgc, LPTSTR* lpszArgv )
{
	CService1::getInstance()->Run(dwArgc, lpszArgv);
}

VOID WINAPI CService1::Service1CtrlHandler( DWORD dwCtrl )
{
	switch (dwCtrl)
	{
	case SERVICE_CONTROL_STOP:
		CService1::getInstance()->Stop();
		return;
	case SERVICE_CONTROL_INTERROGATE:
		break;
	default:
		break;
	}
}