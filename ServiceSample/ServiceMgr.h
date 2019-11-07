#pragma once

class CServiceMgr
{
public:
	CServiceMgr(void);
	~CServiceMgr(void);

	void InstallService(const wstring& strSvcName, const wstring& strSvcParam);
	void StartService(const wstring& strSvcName);
	void StopService(const wstring& strSvcName);
	void DeleteService(const wstring& strSvcName);
	void StartServiceControlDispater();
};
