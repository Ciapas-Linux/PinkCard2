#pragma once
#include "afxwin.h"
#include "ProgramConfiguration.h"

// FunGfxAskMessageBoxDlg dialog

class FunGfxAskMessageBoxDlg : public CDialog
{
	DECLARE_DYNAMIC(FunGfxAskMessageBoxDlg)

public:
	FunGfxAskMessageBoxDlg(CWnd* pParent = NULL,const CString& CSText = "",bool* bRet = 0,CProgramConfiguration* lpcfg = NULL);   // standard constructor
	virtual ~FunGfxAskMessageBoxDlg();

// Dialog Data
	enum { IDD = IDD_FUNGFXASKMESSAGEBOXDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog(void);
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
private:
	CString CSMsgText;
	bool* bResult;
public:
	afx_msg void OnBnClickedFunAskMBoxButtonYes();
	afx_msg void OnBnClickedFunAskMBoxButtonNo();
private:
	CBitmap bmpDlgBg;
	CProgramConfiguration* lpCfgObj;
};
