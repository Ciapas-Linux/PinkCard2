// SendMessageDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PinkCard2.h"
#include "SendMessageDlg.h"
#include "ProgramConfiguration.h"

// CSendMessageDlg dialog

IMPLEMENT_DYNAMIC(CSendMessageDlg, CDialog)
CSendMessageDlg::CSendMessageDlg(CWnd* pParent /*=NULL*/,CProgramConfiguration* cfg)
	: CDialog(CSendMessageDlg::IDD, pParent)
	, lpCfgObj(NULL)
{
	lpCfgObj = cfg;
}

CSendMessageDlg::~CSendMessageDlg()
{
}

void CSendMessageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SEND_MESSAGEDLG_RICHEDIT21, CrichEdit2);
}

BOOL CSendMessageDlg::OnInitDialog(void)
{
    CString CSTemp = lpCfgObj->CSSkinPath;
	CSTemp.Append("SendDlgBkg-1.bmp");
	HBITMAP hBitmap = (HBITMAP)::LoadImage(AfxGetInstanceHandle(),
					  CSTemp.GetBuffer(0),
					  IMAGE_BITMAP,
					  0,
					  0,
					  LR_LOADFROMFILE |
					  LR_CREATEDIBSECTION);
	CSTemp.ReleaseBuffer();
	if(bmpDlgBg.DeleteObject())
	{
	 bmpDlgBg.Detach();
	}
	bmpDlgBg.Attach(hBitmap);
return true;
}

afx_msg void CSendMessageDlg::OnPaint(void)
{
 if(lpCfgObj->bUseBmpSkin == true)
 {
  CPaintDC dc1(this);
  CDC cdc1;
  cdc1.CreateCompatibleDC(&dc1);
  cdc1.SelectObject((HBITMAP)bmpDlgBg);
  CRect rect;
  GetClientRect(rect);
  rect.NormalizeRect();
  dc1.BitBlt(0,0,rect.Width(),rect.Height(),&cdc1,0,0,SRCCOPY);
 }
 else
 {
 
 
 }
 CDialog::OnPaint();
return afx_msg void();
}

BEGIN_MESSAGE_MAP(CSendMessageDlg, CDialog)
 ON_WM_PAINT()
END_MESSAGE_MAP()


// CSendMessageDlg message handlers
