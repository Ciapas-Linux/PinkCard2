#pragma once

class CNetworkc
{
public:
	CNetworkc(void);
	~CNetworkc(void);
	void EnumeratorHostsFromNetResources(const CString& CSdomainName , const CString& CSNetworkProviderName,vector<CString>& VChostList,vector<CString>& VCComment,HANDLE hEnum , unsigned int  ctrl);
	void EnumeratorDomainFromNetResources(const CString& CSNetworkProviderName,vector<CString>& VCDomainList,HANDLE hEnum , unsigned int  ctrl);
private:
	DWORD ObjCounter;
	bool bNoMoreItems;
public:
	DWORD CheckObjCounter(void);
private:
	bool bdone;
};
