// PinkCard2.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "ProgramConfiguration.h"

// CPinkCard2App:
// See PinkCard2.cpp for the implementation of this class
//

//Global function declaration
UINT TCPThreadListen(LPVOID LPVpParam);
UINT ScheduleEventThread(LPVOID LPVpParam);
void wGetHostName(CString& hostname);
void wGetModulePath(CString& CSretBuf);
void gFunMessageBox(const CString& CSText,CProgramConfiguration* lpcfg);
bool wDirectoryPicker(const char* Prompt, char* Dest,HWND m_hWnd);
bool gFunAskMessageBox(const CString CSText,CProgramConfiguration* lpcfg);
void wDisplayLastErrorWSAnet();

class CPinkCard2App : public CWinApp
{
public:
	CPinkCard2App();
// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation
	DECLARE_MESSAGE_MAP()
	int AddThread(CWinThread* pThread);
	int ThreadEnd(CWinThread* pThread);
public:
	CList<CWinThread*> m_ThreadList;
	int ExitInstance(void);
};

extern CPinkCard2App theApp;