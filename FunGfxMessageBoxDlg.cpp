// FunGfxMessageBoxDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PinkCard2.h"
#include "FunGfxMessageBoxDlg.h"


// FunGfxMessageBoxDlg dialog
IMPLEMENT_DYNAMIC(FunGfxMessageBoxDlg, CDialog)
FunGfxMessageBoxDlg::FunGfxMessageBoxDlg(CWnd* pParent /*=NULL*/,const CString& CSText,CProgramConfiguration* cfg)
	: CDialog(FunGfxMessageBoxDlg::IDD, pParent)
	, lpCfgObj(NULL)
{
 CSMsgText = CSText;
 lpCfgObj = cfg;
}

FunGfxMessageBoxDlg::~FunGfxMessageBoxDlg()
{
}

void FunGfxMessageBoxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(FunGfxMessageBoxDlg, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_FUNMSGDLG_OK_BUTTON1, OnBnClickedFunmsgdlgOkButton)
END_MESSAGE_MAP()


// FunGfxMessageBoxDlg message handlers
void FunGfxMessageBoxDlg::OnBnClickedFunmsgdlgOkButton()
{
 this->EndDialog(0);
return;
}

void FunGfxMessageBoxDlg::OnPaint(void)
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
  dc1.SetBkMode(TRANSPARENT);
  dc1.SetTextColor(RGB(160,210,255));
  dc1.TextOut(20,90,CSMsgText);
 }
 else
 {
  CPaintDC dc1(this);
  CDC cdc1;
  cdc1.CreateCompatibleDC(&dc1);
  dc1.SetBkMode(TRANSPARENT);
  dc1.SetTextColor(RGB(0,0,0));
  dc1.TextOut(20,90,CSMsgText);
 }

 CDialog::OnPaint();
return;
}

BOOL FunGfxMessageBoxDlg::OnInitDialog(void)
{
  CString CSTemp = lpCfgObj->CSSkinPath;
  CSTemp.Append("FunMsgBoxBg-1.bmp");
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
return 0;
}
