// GroupManager.cpp : implementation file
#include "stdafx.h"
#include "PinkCard2.h"
#include "GroupManager.h"
#include "GroupObj.h"

// CGroupManager dialog
IMPLEMENT_DYNAMIC(CGroupManager, CDialog)
CGroupManager::CGroupManager(CWnd* pParent /*=NULL*/,CPinkCard2Dlg* mdlg,CGroupObj* lpGrpObj,CProgramConfiguration* cfg)
: CDialog(CGroupManager::IDD,pParent)
, lpMainGrpObj(NULL)
, CSGroupName(_T(""))
, lpCfgObj(NULL)
{
 hPinkCard2Dlg = mdlg;
 lpMainGrpObj = lpGrpObj;
 lpCfgObj = cfg;
}

CGroupManager::~CGroupManager()
{
}

void CGroupManager::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_GROUPEDIT_LANRESOURCES,  CListLanHosts);
	DDX_Control(pDX, IDC_LIST_GROUPEDIT_GROUPDETAILS, GrpItemsClistCtrlObj);
}

BEGIN_MESSAGE_MAP(CGroupManager, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_LIST_GROUP_CANCEL_BUTTON, OnBnClickedListGroupCancelButton)
	ON_BN_CLICKED(IDC_LIST_GROUP_OK_BUTTON, OnBnClickedListGroupOkButton)
	ON_BN_CLICKED(IDC_LIST_GROUP_DEL_BUTTON, OnBnClickedListGroupDelButton)
	ON_BN_CLICKED(IDC_LIST_GROUP_ADDTOGRP_BUTTON, OnBnClickedListGroupAddToGrpButton)
END_MESSAGE_MAP()

BOOL CGroupManager::OnInitDialog(void)
{
 CString CSTemp = lpCfgObj->CSSkinPath;
 CSTemp.Append("GroupManagerBg-1.bmp");
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
 CListLanHosts.SubclassDlgItem(IDC_LIST_GROUPEDIT_LANRESOURCES,this);
 GrpItemsClistCtrlObj.SubclassDlgItem(IDC_LIST_GROUPEDIT_GROUPDETAILS,this);
 hPinkCard2Dlg->FillHostsListBox(CListLanHosts);
 if(hPinkCard2Dlg->GetFirstSelectedItemTextFromGroupClistCtrl(CSGroupName) == false)
 {
  CSGroupName = "Error!";
 }
 hPinkCard2Dlg->FillGroupItemsListBox(GrpItemsClistCtrlObj,CSGroupName);
return 0;
}

void CGroupManager::OnBnClickedListGroupCancelButton()
{
 this->EndDialog(0);
return;
}

void CGroupManager::OnBnClickedListGroupOkButton()
{
 this->EndDialog(0);
 return;
}

void CGroupManager::OnBnClickedListGroupDelButton()
{
 POSITION pos = GrpItemsClistCtrlObj.GetFirstSelectedItemPosition();
 if (pos == NULL)
 {
  gFunMessageBox("Please select item to delete!",lpCfgObj);
 return;
 }
 else
 {
   while (pos)
   {
	 int nItem = GrpItemsClistCtrlObj.GetNextSelectedItem(pos);
	 CString CSItem = CListLanHosts.GetItemText(nItem,0);
	 lpMainGrpObj->DelItemFromGroup(CSGroupName,CSItem);
   } 
 }
hPinkCard2Dlg->FillGroupItemsListBox(GrpItemsClistCtrlObj,CSGroupName);
return;
}

void CGroupManager::OnPaint(void)
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
	 dc1.TextOut(230,315,CSGroupName);
	 CDialog::OnPaint();
	}
	else
	{
     CPaintDC dc1(this);
	 CDC cdc1;
	 cdc1.CreateCompatibleDC(&dc1);
	 dc1.SetBkMode(TRANSPARENT);
	 dc1.SetTextColor(RGB(0,0,0));
	 dc1.TextOut(230,315,CSGroupName);
	}
}

void CGroupManager::OnBnClickedListGroupAddToGrpButton()
{
 POSITION pos = CListLanHosts.GetFirstSelectedItemPosition();
 if (pos == NULL)
 {
  gFunMessageBox("Please select item to add!",lpCfgObj);
 return;
 }
 else
 {
   while (pos)
   {
	 int nItem = CListLanHosts.GetNextSelectedItem(pos);
	 CString CSItem = CListLanHosts.GetItemText(nItem,0);
	 if(lpMainGrpObj->FindItem(CSGroupName,CSItem) != -1)
	 {
       CString CStemp = CSGroupName;
	   CStemp.Append(" already include ");
       CStemp.Append(CSItem);
       gFunMessageBox(CStemp,lpCfgObj); 
	  return;
	 }
	 lpMainGrpObj->AddItemToGroup(CSGroupName,CSItem);
   } 
 }
hPinkCard2Dlg->FillGroupItemsListBox(GrpItemsClistCtrlObj,CSGroupName);
return;	
}
