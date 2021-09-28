// AddScheduleEvent.cpp : implementation file
//

#include "stdafx.h"
#include "PinkCard2.h"
#include "AddScheduleEvent.h"


// CAddScheduleEvent dialog

IMPLEMENT_DYNAMIC(CAddScheduleEvent, CDialog)
CAddScheduleEvent::CAddScheduleEvent(CWnd* pParent /*=NULL*/,CString& CSReturnString)
	: CDialog(CAddScheduleEvent::IDD, pParent)
{
}

CAddScheduleEvent::~CAddScheduleEvent()
{
}

void CAddScheduleEvent::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAddScheduleEvent, CDialog)
END_MESSAGE_MAP()


// CAddScheduleEvent message handlers
