#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CSendMessageDlg dialog
class CSendMessageDlg : public CDialog
{
	DECLARE_DYNAMIC(CSendMessageDlg)

public:
	CSendMessageDlg(CWnd* pParent = NULL,CProgramConfiguration* cfg = NULL);   // standard constructor
	virtual ~CSendMessageDlg();

    //Dialog Data
	enum { IDD = IDD_SEND_MESSAGE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog(void);
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	CRichEditCtrl CrichEdit2;
private:
	CBitmap bmpDlgBg;
	CProgramConfiguration* lpCfgObj;
};
