// ScheduleSendDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PinkCard2.h"
#include "ScheduleSendDlg.h"
#include "AddScheduleEvent.h"

// CScheduleSendDlg dialog

IMPLEMENT_DYNAMIC(CScheduleSendDlg, CDialog)
CScheduleSendDlg::CScheduleSendDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CScheduleSendDlg::IDD, pParent)
	, TimeObj(0)
	, CSMyCommentForEvent(_T(""))
{
}

CScheduleSendDlg::~CScheduleSendDlg()
{
}

void CScheduleSendDlg::OnPaint()
{

return;
}

BOOL CScheduleSendDlg::OnInitDialog(void)
{


return false;
}

void CScheduleSendDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SCHEDULE_SEND_EVENT_LIST1, EventListCtrlObj);
	DDX_Control(pDX, IDC_SCHEDULESENDDLG_DATE, DateCtrl);
	DDX_Control(pDX, IDC_SCHEDULESENDDLG_TIME, TimeCtrl);
}


BEGIN_MESSAGE_MAP(CScheduleSendDlg, CDialog)
	ON_BN_CLICKED(IDC_SCHEDULE_SEND_BUTTON_OK, OnBnClickedScheduleSendButtonOk)
	ON_BN_CLICKED(IDC_SCHEDULE_SEND_BUTTON_CANCEL, OnBnClickedScheduleSendButtonCancel)
	ON_BN_CLICKED(IDC_SCHEDULE_S_BUTTON_ADD, OnBnClickedScheduleSButtonAdd)
	ON_BN_CLICKED(IDC_SCHEDULE_S_BUTTON_DEL, OnBnClickedScheduleSButtonDel)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_SCHEDULESENDDLG_DATE, OnDtnDateTimeChangeScheduleSendDlgDate)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_SCHEDULESENDDLG_TIME, OnDtnDateTimeChangeScheduleSendDlgTime)
END_MESSAGE_MAP()



void CScheduleSendDlg::OnBnClickedScheduleSendButtonOk()
{
 this->EndDialog(0);
return;
}

void CScheduleSendDlg::OnBnClickedScheduleSendButtonCancel()
{
 this->EndDialog(0);
return;
}

void CScheduleSendDlg::OnBnClickedScheduleSButtonAdd()
{
 CString CStemp;
 CAddScheduleEvent dlg(0,CStemp);
 CSMyCommentForEvent = CStemp;
 dlg.DoModal();
return;
}

void CScheduleSendDlg::OnBnClickedScheduleSButtonDel()
{

return;
}

void CScheduleSendDlg::OnDtnDateTimeChangeScheduleSendDlgDate(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	DateCtrl.GetTime(DateObj);
	*pResult = 0;
}

void CScheduleSendDlg::OnDtnDateTimeChangeScheduleSendDlgTime(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	TimeCtrl.GetTime(TimeObj);	
	*pResult = 0;
}
