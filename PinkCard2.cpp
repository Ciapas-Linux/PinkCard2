// PinkCard2.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "PinkCard2.h"
#include "PinkCard2Dlg.h"
#include "SplashScreenEx.h"
#include "ProgramConfiguration.h"
#include "FunGfxMessageBoxDlg.h"
#include "FunGfxAskMessageBoxDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPinkCard2App
BEGIN_MESSAGE_MAP(CPinkCard2App, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CPinkCard2App construction
CPinkCard2App::CPinkCard2App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CPinkCard2App object
CPinkCard2App theApp;


UINT TCPThreadListen(LPVOID LPVpParam)
{
	//MessageBox(NULL,"TCPThread","START",MB_OK);
	
	AfxSocketInit();
	CPinkCard2Dlg *Dlg = (CPinkCard2Dlg *)(theApp.m_pMainWnd);
	CAsyncSocket Socket;
	BOOL pom = true;

	Socket.Create(14456,SOCK_STREAM);
	Socket.SetSockOpt(SO_BROADCAST,&pom,sizeof(BOOL)); 

   /* while((*EndThread)!=true)
	{
	
	
	
	
	
	}*/


    Socket.Close();

	//MessageBox(NULL,"TCPThread","STOP",MB_OK);
	return 0;
}

UINT ScheduleEventThread(LPVOID LPVpParam)
{
	
	return 0;
}

void wGetHostName(CString& hostname)
{
 char buff[300];
 ZeroMemory(buff,sizeof(buff));
 gethostname(buff,300);
 hostname = buff;
return;
}

void gFunMessageBox(const CString& CSText,CProgramConfiguration* lpcfg)
{
 FunGfxMessageBoxDlg dlg(0,CSText,lpcfg);
 dlg.DoModal();
return;
}

bool gFunAskMessageBox(const CString CSText,CProgramConfiguration* lpcfg)
{
 bool bTmp;
 bool* bpRet = &bTmp;
 FunGfxAskMessageBoxDlg dlg(0,CSText,bpRet,lpcfg);
 dlg.DoModal();
 if(*bpRet == true)
	 return true;
 else return false;
}
	
void wGetModulePath(CString& CSretBuf)
{
 char chtmp[201];
 ZeroMemory(chtmp,sizeof(chtmp));
 GetModuleFileName(NULL,(LPTSTR)chtmp,(DWORD)200);
 CSretBuf = chtmp;
 CSretBuf = CSretBuf.Left(CSretBuf.ReverseFind('\\') + 1);
return;
}

bool wDirectoryPicker(const char* Prompt,char* Dest,HWND m_hWnd)
{
 BROWSEINFO bi;
 ITEMIDLIST* pItemIDList;
 char Folder[_MAX_PATH];
 memset(&bi, 0, sizeof(bi));
 bi.hwndOwner=m_hWnd;
 bi.pszDisplayName=Folder;
 bi.lpszTitle=Prompt;
 bi.ulFlags = BIF_EDITBOX | BIF_VALIDATE | BIF_NEWDIALOGSTYLE;
 if((pItemIDList=SHBrowseForFolder(&bi))!=NULL)
 {
  SHGetPathFromIDList(pItemIDList,Dest);
  return true;
 }else return false;
return false;
}

void wDisplayLastErrorWSAnet()
{
  LPVOID lpMsgBuf;
  int error = WSAGetLastError();
  CString CSErrorCode;
  CSErrorCode.Format(_T("%d"),error);
  CString CSTemp; 
  FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|
                FORMAT_MESSAGE_FROM_SYSTEM|
                FORMAT_MESSAGE_IGNORE_INSERTS,
                NULL,
                error,
                MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT),
                (LPTSTR)&lpMsgBuf,
                0,
                NULL);
  CSTemp.Append((LPCTSTR)lpMsgBuf);
  CSTemp.Append("Error code : ");
  CSTemp.Append(CSErrorCode);
  MessageBox(NULL,CSTemp.GetBuffer(0),"PinkCard2 Error !",MB_OK|MB_ICONINFORMATION);
  CSTemp.ReleaseBuffer();
  LocalFree( lpMsgBuf );
return;
}

void wDisplayLastError()
{
  LPVOID lpMsgBuf;
  FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|
                FORMAT_MESSAGE_FROM_SYSTEM|
                FORMAT_MESSAGE_IGNORE_INSERTS,
                NULL,
                GetLastError(),
                MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT),
                (LPTSTR)&lpMsgBuf,
                0,
                NULL);
  MessageBox(NULL,(LPCTSTR)lpMsgBuf,"PinkCard Error !",MB_OK|MB_ICONINFORMATION);
  LocalFree( lpMsgBuf );
return;
}

BOOL CPinkCard2App::InitInstance()
{
	//One program instance in memory.....
	if(FindWindow(NULL,"PinkCard2")!=NULL)
	{
	 AfxMessageBox("This program is already run!");
	return FALSE;
	}
	
   	AfxEnableControlContainer();

    #ifdef _AFXDLL
//	 Enable3dControls();			
    #else
//	 Enable3dControlsStatic();	
    #endif

	
	// list control
	if (!AfxOleInit())
	{
		AfxMessageBox("Unable to initialize OLE.\nTerminating application!");
		return FALSE;
	}

	InitCommonControls();
    AfxInitRichEdit2();
	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

   	//watek nasluchu na TCP
	CWinThread *pThread;
	pThread=AfxBeginThread(TCPThreadListen,this,THREAD_PRIORITY_NORMAL,0,CREATE_SUSPENDED);
	pThread->m_bAutoDelete=false;
	pThread->ResumeThread();  
	AddThread(pThread);
	
	//W¹tek planowanych zadañ
	pThread=AfxBeginThread(ScheduleEventThread,this,THREAD_PRIORITY_NORMAL,0,CREATE_SUSPENDED);
	pThread->m_bAutoDelete=false;
	pThread->ResumeThread();  
	AddThread(pThread);
	
	//Create main dialog
	//CPinkCard2Dlg& = dlg;
	CPinkCard2Dlg*  dlg = new CPinkCard2Dlg;
	m_pMainWnd = dlg;
	INT_PTR nResponse = dlg->DoModal();

	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}
 delete dlg;
return FALSE;
}

int CPinkCard2App::AddThread(CWinThread* pThread)
{
 m_ThreadList.AddHead(pThread);
return 0;
}

int CPinkCard2App::ThreadEnd(CWinThread* pThread)
{
 	WaitForSingleObject(pThread->m_hThread,INFINITE); 
	m_ThreadList.RemoveAt(m_ThreadList.Find(pThread));
	delete pThread;
return 0;
}

int CPinkCard2App::ExitInstance(void)
{
 m_ThreadList.RemoveAll();
return 0;
}
