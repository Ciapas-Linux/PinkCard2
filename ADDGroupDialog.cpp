// ADDGroupDialog.cpp : implementation file
//

#include "stdafx.h"
#include "PinkCard2.h"
#include "ADDGroupDialog.h"
#include "GroupObj.h"

// CADDGroupDialog dialog

IMPLEMENT_DYNAMIC(CADDGroupDialog, CDialog)
CADDGroupDialog::CADDGroupDialog(CWnd* pParent /*=NULL*/,CGroupObj* grp,CProgramConfiguration* cfg)
	: CDialog(CADDGroupDialog::IDD, pParent)
	, grpobj(NULL)
	, lpCfgObj(NULL)
{
	grpobj = grp;
	lpCfgObj = cfg;
}

CADDGroupDialog::~CADDGroupDialog()
{
}

void CADDGroupDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CADDGroupDialog, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_ADDGRP_BUTTON_OK, OnBnClickedAddgrpButtonOk)
	ON_BN_CLICKED(IDC_ADDGRP_BUTTON_CLOSE, OnBnClickedAddgrpButtonClose)
	ON_EN_UPDATE(IDC_ADDGRP_EDIT_INPUT1, OnEnUpdateAddgrpEditInput1)
END_MESSAGE_MAP()


// CADDGroupDialog message handlers
void CADDGroupDialog::OnBnClickedAddgrpButtonOk()
{
	CString rString;
    GetDlgItemText(IDC_ADDGRP_EDIT_INPUT1,rString); 
	if(grpobj->FindGroup(rString) != -1)
	{
     gFunMessageBox("This group allready exist, please input another name!",lpCfgObj);
	return;
	}
	if(rString.GetLength() == 0)
	{
	  gFunMessageBox("Please input group name!",lpCfgObj);
	return;
	}
	grpobj->AddEmptyGroup(rString);
	CString CSBuf;
	CString CSTmp;
	lpCfgObj->IOSysFilesPath(true,CSTmp);
	CSBuf.Append(CSTmp);
	CSBuf.Append(rString);
    CSBuf.Append(".grp");
	CFile(CSBuf.GetBuffer(0),CFile::modeCreate);
	CSBuf.ReleaseBuffer();
	this->EndDialog(0);
return;
}

void CADDGroupDialog::OnBnClickedAddgrpButtonClose()
{
	this->EndDialog(0);
return;
}

void CADDGroupDialog::OnEnUpdateAddgrpEditInput1()
{
 
return;
}

afx_msg void CADDGroupDialog::OnPaint()
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
   CPaintDC dc1(this);
   CDC cdc1;
   cdc1.CreateCompatibleDC(&dc1);
   dc1.SetBkMode(TRANSPARENT);
   dc1.SetTextColor(RGB(0,0,0));
   dc1.TextOut(30,25,"Please input group name:");
 }
 CDialog::OnPaint();
return afx_msg void();
}

BOOL CADDGroupDialog::OnInitDialog(void)
{
	CString CSTemp = lpCfgObj->CSSkinPath;
	CSTemp.Append("AddNewGroupDlgBkg-1.bmp");
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