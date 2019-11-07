#include "StdAfx.h"
#include "ServiceMgr.h"
#include "Service1.h"
#include "Service2.h"

CServiceMgr::CServiceMgr(void)
{
}

CServiceMgr::~CServiceMgr(void)
{
}

void CServiceMgr::InstallService( const wstring& strSvcName, const wstring& strSvcParam )
{
	SC_HANDLE schSCManager;
	SC_HANDLE schService;
	TCHAR szPath[MAX_PATH] = {0};

	if (!GetModuleFileName(NULL, szPath, MAX_PATH))
	{
		OutputDebugInfo(L"Cannot install service (%d)\n", GetLastError());
		return;
	}

	wstring strPath = L"\"";
	strPath.append(szPath);
	if (!strSvcParam.empty())
	{
		strPath.append(L" ");
		strPath.append(strSvcParam);
	}
	strPath.append(L"\"");

	schSCManager = OpenSCManager(
		NULL,
		NULL,
		SC_MANAGER_ALL_ACCESS);
	if (NULL == schSCManager)
	{
		OutputDebugInfo(L"OpenSCManager failed (%d)\n", GetLastError());
		return;
	}

	schService = CreateService(
		schSCManager,
		strSvcName.c_str(),
		strSvcName.c_str(),
		SERVICE_ALL_ACCESS,
		SERVICE_WIN32_SHARE_PROCESS,
		SERVICE_DEMAND_START,
		SERVICE_ERROR_NORMAL,
		strPath.c_str(),
		NULL,
		NULL,
		NULL,
		NULL,
		NULL);

	if (schService == NULL)
	{
		OutputDebugInfo(L"CreateService failed (%d)\n", GetLastError());
		CloseServiceHandle(schSCManager);
		return;
	}
	else
	{
		OutputDebugInfo(L"Service:%s installed successfully\n", strSvcName);
	}

	CloseServiceHandle(schService);
	CloseServiceHandle(schSCManager);
}

void CServiceMgr::StartService( const wstring& strSvcName )
{
	// TODO: StartService
}

void CServiceMgr::StopService( const wstring& strSvcName )
{
	// TODO: StopService
}

void CServiceMgr::DeleteService( const wstring& strSvcName )
{
	// TODO: DeleteService
}

void CServiceMgr::StartServiceControlDispater()
{
	//Sleep(20000);
	SERVICE_TABLE_ENTRY DispatchTable[] = 
	{
		{ CService1::getInstance()->GetServiceName(), (LPSERVICE_MAIN_FUNCTION)CService1::Service1Main},
		{ CService2::getInstance()->GetServiceName(), (LPSERVICE_MAIN_FUNCTION)CService2::Service2Main},
		{ NULL, NULL}
	};

	if (!StartServiceCtrlDispatcher(DispatchTable))
	{
		OutputDebugInfo(L"StartServiceCtrlDispatcher failed.Gle:0x%08x", GetLastError());
	}
}