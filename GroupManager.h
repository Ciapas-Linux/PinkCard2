#pragma once

#include "PinkCard2Dlg.h"
#include "afxcmn.h"
#include "afxwin.h"

// CGroupManager dialog

class CGroupManager : public CDialog
{
	DECLARE_DYNAMIC(CGroupManager)

public:
	CGroupManager(CWnd* pParent = NULL,CPinkCard2Dlg* mdlg = NULL,CGroupObj* lpGrpObj = NULL,CProgramConfiguration* cfg = NULL);   // standard constructor
	virtual ~CGroupManager();

// Dialog Data
	enum { IDD = IDD_DIALOG_GROUPMANAGER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	BOOL OnInitDialog(void);
	CListCtrl CListLanHosts;
	CPinkCard2Dlg* hPinkCard2Dlg;
public:
	afx_msg void OnBnClickedListGroupCancelButton();
	afx_msg void OnBnClickedListGroupOkButton();
	afx_msg void OnBnClickedListGroupDelButton();
private:
	CString CSGroupName;
	CGroupObj* lpMainGrpObj;
	CListCtrl GrpItemsClistCtrlObj;
	afx_msg void OnPaint(void);
public:
	afx_msg void OnBnClickedListGroupAddToGrpButton();
private:
	CProgramConfiguration* lpCfgObj;
	CBitmap bmpDlgBg;
};
