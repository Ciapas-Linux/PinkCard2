#pragma once

#include "GroupObj.h"
#include "ProgramConfiguration.h"
#include "afxwin.h"

// CADDGroupDialog dialog

class CADDGroupDialog : public CDialog
{
	DECLARE_DYNAMIC(CADDGroupDialog)

public:
	CADDGroupDialog(CWnd* pParent = NULL,CGroupObj* grp = NULL,CProgramConfiguration* cfg = NULL);   // standard constructor
	virtual ~CADDGroupDialog();

// Dialog Data
	enum { IDD = IDD_ADDGROUP_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    afx_msg void OnPaint();
	BOOL OnInitDialog(void);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedAddgrpButtonOk();
	afx_msg void OnBnClickedAddgrpButtonClose();
private:
	CGroupObj* grpobj;
public:
	CProgramConfiguration* lpCfgObj;
	afx_msg void OnEnUpdateAddgrpEditInput1();
private:
	CBitmap bmpDlgBg;
};
