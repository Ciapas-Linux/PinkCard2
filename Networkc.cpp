#include "StdAfx.h"
#include "networkc.h"

CNetworkc::CNetworkc(void)
: ObjCounter(0)
, bNoMoreItems(false)
, bdone(false)
{
}

CNetworkc::~CNetworkc(void)
{
}

void CNetworkc::EnumeratorHostsFromNetResources(const CString& CSdomainName , const CString& CSNetworkProviderName,vector<CString>& VChostList,vector<CString>& VCComment,HANDLE hEnum , unsigned int  ctrl)
{
   DWORD dwCounter = 0xFFFFFFFF;
   DWORD dwSize = 16384;
   const char * dtype = NULL;
   const char * type = NULL;
   register int i;
    
   if(ctrl == 0)
   {
     bNoMoreItems = false;
	 if (WNetOpenEnum (RESOURCE_GLOBALNET, RESOURCETYPE_ANY, 0, NULL, &hEnum) != NO_ERROR)
	 { 
	  wDisplayLastErrorWSAnet(); 
	  return;
	 }
   }

   LPNETRESOURCE lpData;
   lpData  =  (LPNETRESOURCE)new char[16384];
   if (lpData == NULL)
   {
	wDisplayLastError();
   return;
   }
	while (bNoMoreItems == false)
	{
		DWORD res = WNetEnumResource (hEnum, &dwCounter, (LPVOID)lpData, &dwSize);
		if(res == ERROR_NO_MORE_ITEMS)
		  break;
		if(res != NO_ERROR && res != ERROR_NO_MORE_ITEMS)
		{
         delete [] lpData; 
         wDisplayLastErrorWSAnet();
		 return;
		}
	
		for (i = 0; i < (int)dwCounter; i++)
		{
			CString sContainerName(lpData[i].lpRemoteName);
	  
			//Network Provider
			if(sContainerName == CSNetworkProviderName && ctrl == 0)
			{
              ctrl++;
			  HANDLE hCont;
			   if(WNetOpenEnum (RESOURCE_GLOBALNET, RESOURCETYPE_ANY, 0, &lpData[i],&hCont) == NO_ERROR)
			   {
		        EnumeratorHostsFromNetResources (CSdomainName,CSNetworkProviderName,VChostList,VCComment,hCont,ctrl);
			   	WNetCloseEnum (hCont);
			   }
			   else
			   {
                delete [] lpData;
			    wDisplayLastErrorWSAnet(); 
				return;
			   }
			   break;
			}
     
            //Domain
			if(sContainerName == CSdomainName && ctrl == 1)
			{
              ctrl++;
			  HANDLE hCont;
			   if(WNetOpenEnum (RESOURCE_GLOBALNET, RESOURCETYPE_ANY, 0, &lpData[i],&hCont) == NO_ERROR)
			   {
		     	EnumeratorHostsFromNetResources (CSdomainName,CSNetworkProviderName,VChostList,VCComment,hCont,ctrl);
			  	WNetCloseEnum (hCont);
			   }
			   else
			   {
				delete [] lpData;
			    wDisplayLastErrorWSAnet(); 
				return;
			   }
			   break;
			 }
      
            //Hosts
            if(ctrl == 2)//FINITO
			{
			 VChostList.push_back(lpData[i].lpRemoteName);
			 VCComment.push_back(lpData[i].lpComment);
			 if(i + 1 == dwCounter)
			 {
			  bNoMoreItems = true;//dwCounter ObjCounter
			  ObjCounter = dwCounter; 
			 }
			}
		}
		dwSize = 16384;
	}
	delete [] lpData;
	WNetCloseEnum (hEnum);
return;
}

void CNetworkc::EnumeratorDomainFromNetResources(const CString& CSNetworkProviderName,vector<CString>& VCDomainList,HANDLE hEnum , unsigned int  ctrl)
{
   DWORD dwCounter = 0xFFFFFFFF;
   DWORD dwSize = 16384;
   const char * dtype = NULL;
   const char * type = NULL;
   register int i;
    
   if(ctrl == 0)
   {
     bNoMoreItems = false;
	 if (WNetOpenEnum (RESOURCE_GLOBALNET, RESOURCETYPE_ANY, 0, NULL, &hEnum) != NO_ERROR)
	 { 
	  wDisplayLastErrorWSAnet(); 
	  return;
	 }
   }

   LPNETRESOURCE lpData;
   lpData  =  (LPNETRESOURCE)new char[16384];
   if (lpData == NULL)
   {
	wDisplayLastError();
   return;
   }
	while (bNoMoreItems == false)
	{
		DWORD res = WNetEnumResource (hEnum, &dwCounter, (LPVOID)lpData, &dwSize);
		if(res == ERROR_NO_MORE_ITEMS)
		  break;
		if(res != NO_ERROR && res != ERROR_NO_MORE_ITEMS)
		{
         delete [] lpData; 
         wDisplayLastErrorWSAnet();
		 return;
		}
	
		for (i = 0; i < (int)dwCounter; i++)
		{
			CString sContainerName(lpData[i].lpRemoteName);
	  
			//Network Provider
			if(sContainerName == CSNetworkProviderName && ctrl == 0)
			{
              ctrl++;
			  HANDLE hCont;
			   if(WNetOpenEnum (RESOURCE_GLOBALNET, RESOURCETYPE_ANY, 0, &lpData[i],&hCont) == NO_ERROR)
			   {
		        EnumeratorDomainFromNetResources (CSNetworkProviderName,VCDomainList,hCont,ctrl);
			   	WNetCloseEnum (hCont);
			   }
			   else
			   {
                delete [] lpData;
			    wDisplayLastErrorWSAnet(); 
				return;
			   }
			   break;
			}
     
            //Domain
			if(lpData[i].dwDisplayType == RESOURCEDISPLAYTYPE_DOMAIN && ctrl == 1)
			{
             VCDomainList.push_back(lpData[i].lpRemoteName);
             if(i + 1 == dwCounter)
			 {
			  bNoMoreItems = true;//dwCounter ObjCounter
			  ObjCounter = dwCounter; 
			 }
			}
       	}//dwCounter
		dwSize = 16384;
	}
	delete [] lpData;
	WNetCloseEnum (hEnum);
return;
}

DWORD CNetworkc::CheckObjCounter(void)
{
	return ObjCounter;
}
