// ServiceSample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ServiceMgr.h"
#include "Service1.h"
#include "Service2.h"


/* 一个多服务共享进程的例子 */
int _tmain(int argc, _TCHAR* argv[])
{
	OutputDebugInfo(L"test:%d", 1);

	map<wstring, wstring> mapCmd;
	for (int i = 0; i < argc; i++)
	{
		if (wcsncmp(L"-", argv[i], 1) != 0)
			continue;

		wstring strArg = argv[i];
		int nIndex = strArg.find(L"=");
		if (nIndex != wstring::npos)
		{
			wstring key = strArg.substr(0, nIndex);
			wstring value = strArg.substr(nIndex+1, wstring::npos);
			mapCmd.insert(make_pair(key, value));
		}
		else
		{
			mapCmd.insert(make_pair(strArg, L""));
		}
	}

	CServiceMgr serviceMgr;
	if (mapCmd.empty())
	{
		serviceMgr.StartServiceControlDispater();
	}
	else
	{
		const wstring keyInstall = L"-install";
		const wstring keyStart = L"-start";
		const wstring keyStop = L"-stop";
		const wstring keyDelete = L"-delete";
		const wstring keyParam = L"-param";
		const wstring keyName = L"-name";

		wstring strServiceName;
		if (mapCmd.find(keyName) != mapCmd.end())
		{
			strServiceName = mapCmd[keyName];
		}

		if (strServiceName != CService1::getInstance()->GetServiceName() && strServiceName != CService2::getInstance()->GetServiceName())
		{
			wprintf(L"Error service name:%s;\r\nService name muset be:Service1 or Service2", strServiceName);
			return -1;
		}

		if (mapCmd.find(keyInstall) != mapCmd.end())
		{
			wstring strParam = mapCmd[keyParam];
			serviceMgr.InstallService(strServiceName, strParam);
		}

		if (mapCmd.find(keyStart) != mapCmd.end())
		{
			serviceMgr.StartService(strServiceName);
		}

		if (mapCmd.find(keyStop) != mapCmd.end())
		{
			serviceMgr.StopService(strServiceName);
		}

		if (mapCmd.find(keyDelete) != mapCmd.end())
		{
			serviceMgr.DeleteService(strServiceName);
		}
	}

	return 0;
}

