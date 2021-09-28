#pragma once

#include "ProgramConfiguration.h"
#include "afxwin.h"

// COptionsDlg dialog
class COptionsDlg : public CDialog
{
	DECLARE_DYNAMIC(COptionsDlg)

public:
	COptionsDlg(CWnd* pParent = NULL,CProgramConfiguration* cfg = NULL);   // standard constructor
	virtual ~COptionsDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_OPTIONS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   	virtual BOOL OnInitDialog(void);
	DECLARE_MESSAGE_MAP()
private:
	CProgramConfiguration* lpcfg;
public:
	afx_msg void OnEnChangeOptionsPortEdit();
	afx_msg void OnEnChangeOptionsProvnameEdit();
	afx_msg void OnBnClickedOptionsCheckSplash();
	CButton splash_checkbox;
	CButton HideOnSendCheckBox;
	CButton UseSkinBmpCheckBox;
	afx_msg void OnEnChangeOptionsSyspathEdit();
	afx_msg void OnBnClickedOptionsDefaultButton1();
	afx_msg void OnBnClickedOptionsCheckAutoHideOnSendCheck();
	afx_msg void OnBnClickedOptionsCheckGfxCheck();
	afx_msg void OnEnChangeOptionsSkinPathEdit();
	afx_msg void OnBnClickedOptionsSetSkinFolderButton();
	afx_msg void OnBnClickedOptionsSetpathfolderButton();
	afx_msg void OnBnClickedOptionsDefaultSkinPathButton();
};
