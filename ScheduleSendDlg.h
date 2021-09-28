#pragma once
#include "afxcmn.h"
#include "afxdtctl.h"
#include "atltime.h"


// CScheduleSendDlg dialog

class CScheduleSendDlg : public CDialog
{
	DECLARE_DYNAMIC(CScheduleSendDlg)

public:
	CScheduleSendDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CScheduleSendDlg();

// Dialog Data
	enum { IDD = IDD_SCHEDULE_SEND_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    afx_msg void OnPaint();
	virtual BOOL OnInitDialog(void);
	DECLARE_MESSAGE_MAP()
private:
	CListCtrl EventListCtrlObj;
public:
	afx_msg void OnBnClickedScheduleSendButtonOk();
	afx_msg void OnBnClickedScheduleSendButtonCancel();
	afx_msg void OnBnClickedScheduleSButtonAdd();
	afx_msg void OnBnClickedScheduleSButtonDel();
private:
	CDateTimeCtrl DateCtrl;
	CDateTimeCtrl TimeCtrl;
	CTime TimeObj;
	CTime DateObj;
public:
	afx_msg void OnDtnDateTimeChangeScheduleSendDlgDate(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDtnDateTimeChangeScheduleSendDlgTime(NMHDR *pNMHDR, LRESULT *pResult);
private:
	CString CSMyCommentForEvent;
};
