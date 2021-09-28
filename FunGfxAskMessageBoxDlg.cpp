// FunGfxAskMessageBoxDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PinkCard2.h"
#include "FunGfxAskMessageBoxDlg.h"
#include "ProgramConfiguration.h"

// FunGfxAskMessageBoxDlg dialog

IMPLEMENT_DYNAMIC(FunGfxAskMessageBoxDlg, CDialog)
FunGfxAskMessageBoxDlg::FunGfxAskMessageBoxDlg(CWnd* pParent /*=NULL*/,const CString& CSText,bool* bRet,CProgramConfiguration* lpcfg)
	: CDialog(FunGfxAskMessageBoxDlg::IDD, pParent)
	, CSMsgText(_T(""))
	, bResult(false)
	, lpCfgObj(NULL)
{
 CSMsgText = CSText;
 lpCfgObj = lpcfg;
 bResult = bRet;
}

FunGfxAskMessageBoxDlg::~FunGfxAskMessageBoxDlg()
{
}

void FunGfxAskMessageBoxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(FunGfxAskMessageBoxDlg, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_FUNASKMBOX_BUTTON_YES, OnBnClickedFunAskMBoxButtonYes)
	ON_BN_CLICKED(IDC_FUNASKMBOX_BUTTON_NO, OnBnClickedFunAskMBoxButtonNo)
END_MESSAGE_MAP()


// FunGfxAskMessageBoxDlg message handlers
afx_msg void FunGfxAskMessageBoxDlg::OnPaint(void)
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
return afx_msg void();
}

void FunGfxAskMessageBoxDlg::OnBnClickedFunAskMBoxButtonYes()
{
 *bResult = true;
 this->EndDialog(0);
return;
}

void FunGfxAskMessageBoxDlg::OnBnClickedFunAskMBoxButtonNo()
{
 *bResult = false;
 this->EndDialog(0);
return;
}

BOOL FunGfxAskMessageBoxDlg::OnInitDialog(void)
{
	CString CSTemp = lpCfgObj->CSSkinPath;
	CSTemp.Append("FunAskMsgBoxBg-1.bmp");
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
