#pragma once


// CAddScheduleEvent dialog

class CAddScheduleEvent : public CDialog
{
	DECLARE_DYNAMIC(CAddScheduleEvent)

public:
	CAddScheduleEvent(CWnd* pParent = NULL,CString& CSReturnString = (CString)"");   // standard constructor
	virtual ~CAddScheduleEvent();

// Dialog Data
	enum { IDD = IDD_ADDSCHEDULEEVENT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
