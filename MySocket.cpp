// MySocket.cpp : implementation file
//

#include "stdafx.h"
#include "MySocket.h"
#include "PinkCard2Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMySocket

CMySocket::CMySocket()
{
}

CMySocket::~CMySocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CMySocket, CAsyncSocket)
	//{{AFX_MSG_MAP(CMySocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CMySocket member functions

void CMySocket::UstawOjca(CDialog *pWnd)
{
	// Ustawienie pola wskaŸnika
	m_pWnd = pWnd;
}

void CMySocket::OnAccept(int nErrorCode)
{
	// Czy wyst¹pi³y jakiekolwiek b³êdy?
	if (nErrorCode == 0)
		// Nie, wywo³anie funkcji OnAccept przodka
		((CPinkCard2Dlg*)m_pWnd)->OnAccept();
}

void CMySocket::OnConnect(int nErrorCode)
{
	// Czy wyst¹pi³y jakiekolwiek b³êdy?
	if (nErrorCode == 0)
		// Nie, wywo³anie funkcji OnConnect przodka
		((CPinkCard2Dlg*)m_pWnd)->OnConnect();
}

void CMySocket::OnReceive(int nErrorCode)
{
	// Czy wyst¹pi³y jakiekolwiek b³êdy?
	if (nErrorCode == 0)
		// Nie, wywo³anie funkcji OnReceive przodka
		((CPinkCard2Dlg*)m_pWnd)->OnReceive();
}

void CMySocket::OnClose(int nErrorCode)
{
	// Czy wyst¹pi³y jakiekolwiek b³êdy?
	if (nErrorCode == 0)
		// Nie, wywo³anie funkcji OnClose przodka
		((CPinkCard2Dlg*)m_pWnd)->OnClose();
}

void CMySocket::OnSend(int nErrorCode)
{
	// Czy wyst¹pi³y jakiekolwiek b³êdy?
	if (nErrorCode == 0)
		// Nie, wywo³anie funkcji OnSend przodka
		((CPinkCard2Dlg*)m_pWnd)->OnSend();
}
