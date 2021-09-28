#pragma once
#include "afxwin.h"


// FunGfxMessageBoxDlg dialog

class FunGfxMessageBoxDlg : public CDialog
{
	DECLARE_DYNAMIC(FunGfxMessageBoxDlg)

public:
	FunGfxMessageBoxDlg(CWnd* pParent = NULL,const CString& CSText = "",CProgramConfiguration* cgf = NULL);   // standard constructor
	virtual ~FunGfxMessageBoxDlg();

// Dialog Data
	enum { IDD = IDD_FUNGFXMESSAGEBOXDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg void OnPaint(void);
    BOOL OnInitDialog(void);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedFunmsgdlgOkButton();
private:
	CString CSMsgText;
	CProgramConfiguration* lpCfgObj;
	CBitmap bmpDlgBg;
};
