#include "StdAfx.h"
#include "ServiceBase.h"

CServiceBase::CServiceBase(void)
{
}

CServiceBase::~CServiceBase(void)
{
}

VOID CServiceBase::ReportSvcStatus( DWORD dwCurrentState, DWORD dwWin32ExitCode, DWORD dwWaitHint )
{
	static DWORD dwCheckPoint = 1; // TODO: to fix

	m_svcStatus.dwCurrentState = dwCurrentState;
	m_svcStatus.dwWin32ExitCode = dwWin32ExitCode;
	m_svcStatus.dwWaitHint = dwWaitHint;

	if (dwCurrentState == SERVICE_START_PENDING)
		m_svcStatus.dwControlsAccepted = 0;
	else m_svcStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;

	if ((dwCurrentState == SERVICE_RUNNING) ||
		(dwCurrentState == SERVICE_STOPPED))
		m_svcStatus.dwCheckPoint = 0;
	else m_svcStatus.dwCheckPoint = dwCheckPoint++;

	SetServiceStatus(m_svcStatusHandle, &m_svcStatus);
}

LPTSTR CServiceBase::GetServiceName()
{
	return &m_strSvcName[0];
}