// PinkCard2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "PinkCard2.h"
#include "PinkCard2Dlg.h"
#include "OptionsDlg.h"
#include "GroupManager.h"
#include "SplashScreenEx.h"
#include "ProgramConfiguration.h"
#include "ADDGroupDialog.h"
#include "GroupObj.h"
#include "ScheduleSendDlg.h"
#include "SendMessageDlg.h"
#include "Networkc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//USER SECTION
#define WM_TRAY WM_USER+1///<Komunikat odbierany przez aplikacjê gdy jest w TRAY'u



//CAboutDlg dialog used for App About
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    afx_msg void OnPaint();
// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

afx_msg void CAboutDlg::OnPaint()
{
  CPaintDC dc1(this);
  CDC cdc1;
  cdc1.CreateCompatibleDC(&dc1);
  CBitmap bmpDlgBg;
  bmpDlgBg.LoadBitmap(IDB_BITMAP_ABOUT);
  cdc1.SelectObject((HBITMAP)bmpDlgBg);
  CRect rect;
  GetClientRect(rect);
  rect.NormalizeRect();
  dc1.BitBlt(0,0,rect.Width(),rect.Height(),&cdc1,0,0,SRCCOPY);
 return;
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CPinkCard2Dlg dialog
CPinkCard2Dlg::CPinkCard2Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPinkCard2Dlg::IDD, pParent)
	, visible(false)
	, MainConfigObj(NULL)
	, MainGroupObj(NULL)
	, RefreshLanHostsClistObjTIMERid(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPinkCard2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LAN_RESOURCESLIST1, LanClistCtrl);
	DDX_Control(pDX, IDC_COMBO_LANDOMAIN, LanDomains);
	DDX_Control(pDX, IDC_GROUPS_LIST1, GroupClistCtrl);
}

BEGIN_MESSAGE_MAP(CPinkCard2Dlg, CDialog)
	ON_WM_KEYDOWN()
	ON_WM_SYSCOMMAND()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_CONTEXTMENU()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_EXIT, OnBnClickedButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_OPTIONS, OnBnClickedButtonOptions)
	ON_BN_CLICKED(IDC_BUTTON_GROUPS_EDIT, OnBnClickedButtonGroupsEdit)
	ON_COMMAND(ID_TRAYMENU_SHOW1,OnShow)
	ON_MESSAGE( WM_TRAY , TrayMessage )
	ON_BN_CLICKED(IDC_BUTTON_ABOUT, OnBnClickedButtonAbout)
	ON_CBN_SELCHANGE(IDC_COMBO_LANDOMAIN, OnCbnSelchangeComboLandomain)
	ON_BN_CLICKED(IDC_BUTTON_GROUPS_ADD, OnBnClickedButtonGroupsAdd)
	ON_BN_CLICKED(IDC_BUTTON_GROUPS_DELETE, OnBnClickedButtonGroupsDelete)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_GROUPS_LIST1, OnLvnItemchangedGroupsList1)
	ON_NOTIFY(LVN_ITEMACTIVATE, IDC_GROUPS_LIST1, OnLvnItemActivateGroupsList1)
	ON_NOTIFY(LVN_ITEMCHANGING, IDC_GROUPS_LIST1, OnLvnItemchangingGroupsList1)
	ON_NOTIFY(NM_CLICK, IDC_GROUPS_LIST1, OnNMClickGroupsList1)
	ON_COMMAND(ID_SENDMESSAGE_SENDMESSAGE, OnRMenuSendmessage)
	ON_COMMAND(ID_MENU_SCHEDULESEND, OnMenuSchedulesend)
	ON_BN_CLICKED(IDC_BUTTON_TEST, OnBnClickedButtonTest)
	ON_COMMAND(ID_TRAYMENU_CLOSE1, OnTrayMenuClose)
	ON_COMMAND(ID_FILE_EDIT, OnMenuExitApp)
	ON_COMMAND(ID_PINKCARD2MENU_ABOUT, OnPinkcard2menuAbout)
	ON_COMMAND(ID_FILE_OPEN158, OnMenuConfigDlgDoModal)
END_MESSAGE_MAP()


BOOL CPinkCard2Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

    //Add tray icon
   	this->AddTrayIcon(true);

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

    //Load menu from resources
	CMenu Menu;
	Menu.LoadMenu(IDR_MAINDLG_MENU1);
	SetMenu(&Menu);
	Menu.Detach();

	//Set icons
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
		
	//Read config file
	MainConfigObj = new CProgramConfiguration;
	MainConfigObj->LoadData();
	load_std_options_data();

	//Show splash screen
	if(MainConfigObj->bShowSplashScreen == true)
	{
	 CSplashScreenEx *pSplash=new CSplashScreenEx();
	 pSplash->Create(this,NULL,500,CSS_FADE | CSS_CENTERSCREEN);
	 pSplash->SetBitmap(IDB_BITMAP_SPLASH,0,0,0);
	 pSplash->Show();
	}
	
    //load bitmaps for background
	CString CSTemp = MainConfigObj->CSSkinPath;
	CSTemp.Append("PinkCard2gnd.bmp");
	HBITMAP hBitmap = (HBITMAP)::LoadImage(AfxGetInstanceHandle(),
					  CSTemp.GetBuffer(0),
					  IMAGE_BITMAP,
					  0,
					  0,
					  LR_LOADFROMFILE |
					  LR_CREATEDIBSECTION);
	CSTemp.ReleaseBuffer();
	if(bmpObjbg.DeleteObject())
	{
	 bmpObjbg.Detach();
	}
	bmpObjbg.Attach(hBitmap);

	//Read all groups
	MainGroupObj = new CGroupObj(MainConfigObj);
	MainGroupObj->LoadAllGroups(); 

	//Load images to CImageList mfc obj
	HIMAGELIST hlist = ImageList_Create(16,16,ILC_COLOR8|ILC_MASK,8,1);
    MyImageList.Attach(hlist);
    CBitmap cBmp;
    cBmp.LoadBitmap(IDB_OK_PC_BITMAP);
    MyImageList.Add(&cBmp,RGB(0,0,0));
    cBmp.DeleteObject();
	cBmp.LoadBitmap(IDB_PEOPLE_BITMAP);
    MyImageList.Add(&cBmp,RGB(0,0,0));
	cBmp.DeleteObject();
	
	//Set bk color for main listctrl...
	LanClistCtrl.SetBkColor(RGB(87,159,216));
	LanClistCtrl.SetTextBkColor(RGB(87,159,216));
    
    GroupClistCtrl.SetBkColor(RGB(145,170,231));
	GroupClistCtrl.SetTextBkColor(RGB(145,170,231));

	//Initial extended style for the list control on this dialog
	DWORD dwStyle = LanClistCtrl.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
	LanClistCtrl.SetExtendedStyle(dwStyle);

	//Get Domain or workgroup list
	FillDomainListBox(LanDomains);

	//Get Hosts list from LAN...
	FillHostsListBox(LanClistCtrl);
    
	//Get Group data from files to ClistCtrl
	FillGroupListBox(GroupClistCtrl);

	//Set timer for refresh host list
    SetTimer(_REFRESH_LAN_CLIST_OBJ_CTRL_ID,50000,NULL);

	//Initialize EventListVector;
    lpvUserEventList = new vector<string>;
	//and load data
	LoadUserScheduledEvent();

  return TRUE;
}

void CPinkCard2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg* dlg = new CAboutDlg;
		dlg->DoModal();
		delete dlg;
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

void CPinkCard2Dlg::OnDestroy()
{
	KillTimer(_REFRESH_LAN_CLIST_OBJ_CTRL_ID);
	CString CSpath;
	MainConfigObj->IOSysFilesPath(true,CSpath);
	MainGroupObj->SaveGroups(CSpath);
	MainConfigObj->SaveData();
	delete MainConfigObj;
	delete MainGroupObj;
	delete lpvUserEventList;
	MyImageList.DeleteImageList();
	WinHelp(0L, HELP_QUIT);
	CDialog::OnDestroy();
}

void CPinkCard2Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this);
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
	 if(MainConfigObj->bUseBmpSkin == true)
	 {
	  CPaintDC dc1(this);
	  CDC cdc1;
	  cdc1.CreateCompatibleDC(&dc1);
      cdc1.SelectObject((HBITMAP)bmpObjbg);
	  CRect rect;
	  GetClientRect(rect);
	  rect.NormalizeRect();
	  dc1.BitBlt(0,0,rect.Width(),rect.Height(),&cdc1,0,0,SRCCOPY);
      GroupClistCtrl.RedrawWindow(NULL,NULL,RDW_UPDATENOW);
	 }
	 else
	 {
	  CPaintDC dc1(this);
	  CDC cdc1;
	  cdc1.CreateCompatibleDC(&dc1);
	  dc1.SetBkMode(TRANSPARENT);
	  dc1.SetTextColor(RGB(0,0,0));
	  dc1.TextOut(25,17,"Domain:");
	  dc1.TextOut(16,40,"Lan:");
	  dc1.TextOut(16,246,"Group:");
	  dc1.TextOut(50,435,"powered by      RSA:)");
	 }
	 CDialog::OnPaint();
	}

}

void CPinkCard2Dlg::OnKeyDown(UINT nChar,UINT nRepCnt,UINT nFlags)
{
 return;
}

void CPinkCard2Dlg::OnTimer(UINT TimerId)
{
 if(TimerId == _REFRESH_LAN_CLIST_OBJ_CTRL_ID)
 {
  FillHostsListBox(LanClistCtrl);
 }
 
return;
}

BOOL CPinkCard2Dlg::PreTranslateMessage(MSG* pMsg) 
{
    if(pMsg->message==WM_KEYDOWN)
    {
        if(pMsg->wParam==VK_RETURN)
		{
		  
		}
        if(pMsg->wParam==VK_ESCAPE)
		{
		   pMsg->wParam = NULL;
		   this->AddTrayIcon(true);
           visible = false;
           this->ShowWindow(SW_HIDE);
	    }
    }
	//pMsg->wParam=VK_TAB;
    return CDialog::PreTranslateMessage(pMsg);
return false;
}

HCURSOR CPinkCard2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CPinkCard2Dlg::OnBnClickedButtonExit()
{
	if(gFunAskMessageBox("Would you like to close this program ?",MainConfigObj) == true)
	{
     this->DestroyWindow();
	}
return;
}

void CPinkCard2Dlg::OnBnClickedButtonOptions()
{
 COptionsDlg* dlg = new  COptionsDlg(0,MainConfigObj);
 dlg->DoModal();
 delete dlg;
return;
}

void CPinkCard2Dlg::OnBnClickedButtonGroupsEdit()
{	
  if(GroupClistCtrl.GetSelectedCount() == 0)
  {
    gFunMessageBox("Please select group to edit!",MainConfigObj);
  return;
  }
  if(GroupClistCtrl.GetSelectedCount() > 1)
  {
    gFunMessageBox("Please select only one group to edit!",MainConfigObj);
   return;
  }
  CGroupManager* dlg = new CGroupManager(0,this,MainGroupObj,MainConfigObj);
  dlg->DoModal();
  delete dlg;
return;
}

void CPinkCard2Dlg::AddTrayIcon(bool Add)
{
	NOTIFYICONDATA nid;
	nid.cbSize=sizeof(NOTIFYICONDATA); 
	nid.hWnd=this->m_hWnd; 
	nid.uID=0; 
	if (Add==true)
	{
		nid.uFlags=NIF_ICON | NIF_TIP | NIF_MESSAGE ; 
		nid.uCallbackMessage=WM_TRAY; 
		nid.hIcon=AfxGetApp()->LoadIcon(IDR_MAINFRAME); 
		GetWindowText(nid.szTip,64);
		Shell_NotifyIcon(NIM_ADD,&nid);	
	}
	else		
	{
		nid.uFlags=0; 
		Shell_NotifyIcon(NIM_DELETE,&nid);	
	}
return;
}

afx_msg LRESULT CPinkCard2Dlg::TrayMessage(WPARAM  wParam, LPARAM lParam)
{
	switch(lParam)
	{
		case WM_LBUTTONDOWN:	
			OnShow();		
			return 0;

		case WM_RBUTTONDOWN:	
			CPoint mouse;
			CMenu menu,*pmenu;
			menu.LoadMenu(IDR_TRAY_MENU1);
			pmenu=menu.GetSubMenu(0);
			pmenu->SetDefaultItem(0,TRUE);
			GetCursorPos(&mouse);
			SetForegroundWindow();
			pmenu->TrackPopupMenu(TPM_RIGHTALIGN,mouse.x,mouse.y,this);
			return 0;
	}
	return 0;
}

void CPinkCard2Dlg::OnShow(void)
{
    visible = true;
	SetForegroundWindow(); 
	this->ShowWindow(SW_RESTORE);
	this->AddTrayIcon(false);
return;
}

void CPinkCard2Dlg::OnSize(UINT  nType, int cx, int cy)
{
   CDialog::OnSize(nType, cx, cy);
return;
}

void CPinkCard2Dlg::OnClose()
{
 this->AddTrayIcon(true);
 visible = false;
 this->ShowWindow(SW_HIDE);
return;
}

void CPinkCard2Dlg::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{
 if(!visible)
    lpwndpos->flags &= ~SWP_SHOWWINDOW;
    CDialog::OnWindowPosChanging(lpwndpos);
return;
}

bool CPinkCard2Dlg::FillDomainListBox(CComboBox& combo)
{
 CNetworkc* CnetObj = new CNetworkc;
 vector<CString> vCSdomain;
 CnetObj->EnumeratorDomainFromNetResources(MainConfigObj->CSNetProvName,vCSdomain,NULL,0);
 if(vCSdomain.size() == 0)
 {
  delete CnetObj;
  return false;
 }
 for(unsigned int lop = 0;lop < vCSdomain.size();lop++)
 {
  combo.InsertString(lop,(LPCTSTR)vCSdomain[lop]);
 }
 combo.SetCurSel(0);
 delete CnetObj;
return true;
}

void CPinkCard2Dlg::OnBnClickedButtonAbout()
{
 CAboutDlg* about = new CAboutDlg;
 about->DoModal();
 delete about;
return;
}

void CPinkCard2Dlg::OnCbnSelchangeComboLandomain()
{
	CString CSrString; 
	LanDomains.GetDlgItemText(IDC_COMBO_LANDOMAIN,CSrString);
    MainConfigObj->CSLastUsedDomain = CSrString;
return;
}

bool CPinkCard2Dlg::FillHostsListBox(CListCtrl& listctrl)
{
   int nColumnCount = listctrl.GetHeaderCtrl()->GetItemCount();
   if(nColumnCount > 0)
   {
    for (int i=0;i < nColumnCount ;i++)
    {
     listctrl.DeleteColumn(0);
    }
   }
   listctrl.DeleteAllItems();
   listctrl.SetImageList(&MyImageList,LVSIL_SMALL);
   listctrl.InsertColumn(0,"computer name",LVCFMT_LEFT,150);
   listctrl.InsertColumn(1,"comment",LVCFMT_LEFT,200);
   listctrl.InsertColumn(2,"status",LVCFMT_LEFT,120);
 
   CNetworkc* myNetObj = new CNetworkc;
   vector<CString> vs_hosts;
   vector<CString> vs_comment;
   CString domain;
   if(GetDlgItemText(IDC_COMBO_LANDOMAIN,domain) <= 0)
   {
    delete myNetObj;
    return false;  
   }
   myNetObj->EnumeratorHostsFromNetResources(domain,MainConfigObj->CSNetProvName,vs_hosts,vs_comment,NULL,0);
   if(myNetObj->CheckObjCounter() == 0)
   {
    delete myNetObj;
    return false;
   }
   LVITEM lvi;
   ZeroMemory(&lvi,sizeof(lvi));
   lvi.mask = LVIF_IMAGE | LVIF_TEXT;
   CString CScompname;
   CString CScomment;
   for(unsigned int lop = 0;lop < vs_hosts.size(); lop++)
   {
    //HostName
    CScompname =  (LPCTSTR)vs_hosts[lop];
	lvi.pszText = CScompname.GetBuffer(0);
	lvi.iItem = lop;
    lvi.iSubItem = 0;
    lvi.iImage = (0%8);
     if(listctrl.InsertItem(&lvi) == -1)
	 {
	  CScomment.ReleaseBuffer();
	  delete myNetObj;
	 return false;
	 }
	CScompname.ReleaseBuffer();

	//COmment
	CScomment = (LPCTSTR)vs_comment[lop];
	lvi.pszText = CScomment.GetBuffer(0);
	lvi.iSubItem =1;
	 if(!listctrl.SetItem(&lvi))
	 {
	   CScomment.ReleaseBuffer();
	   delete myNetObj;
	 return false;
	 }
	CScomment.ReleaseBuffer();
   }
delete myNetObj;
return true;
}

void CPinkCard2Dlg::OnBnClickedButtonGroupsAdd()
{
 CADDGroupDialog* dlg = new CADDGroupDialog(0,MainGroupObj,MainConfigObj);
 dlg->DoModal();
 FillGroupListBox(GroupClistCtrl);
 delete dlg;
return;
}

int CPinkCard2Dlg::FillGroupListBox(CListCtrl& mylistctrl)
{
 mylistctrl.DeleteAllItems();
 int nColumnCount = mylistctrl.GetHeaderCtrl()->GetItemCount();
   if(nColumnCount > 0)
   {
    for (int i=0;i < nColumnCount ;i++)
    {
     mylistctrl.DeleteColumn(0);
    }
   }
 mylistctrl.SetImageList(&MyImageList,LVSIL_SMALL);
 mylistctrl.InsertColumn(0,"group name",LVCFMT_LEFT,120);
 mylistctrl.InsertColumn(1,"comment",LVCFMT_LEFT,180);
 LVITEM lvi;
 lvi.mask = LVIF_IMAGE | LVIF_TEXT;
 CString CStextdata;
 
 vector <string> grpnames;
 MainGroupObj->GetGroupNames(grpnames);

 for(unsigned int lop = 0;lop < grpnames.size() ; lop++)
 {
  CStextdata =  (char*)grpnames[lop].c_str();
  lvi.pszText = CStextdata.GetBuffer(0);
  lvi.iItem = lop;
  lvi.iSubItem = 0;
  lvi.iImage = (1%8);
  mylistctrl.InsertItem(&lvi);
  CStextdata.ReleaseBuffer();
 }
return 0;
}

void CPinkCard2Dlg::OnBnClickedButtonGroupsDelete()
{
    if(gFunAskMessageBox("Are you sure ?",MainConfigObj) == true)
	{
	 POSITION pos = GroupClistCtrl.GetFirstSelectedItemPosition();
     if (pos == NULL)
	 {
      gFunMessageBox("Please select group to delete!",MainConfigObj);
	 return; 
	 }
	 else
     {
      if(GroupClistCtrl.GetSelectedCount() > 1)
	  {
	   gFunMessageBox("Only the one!",MainConfigObj);
      return; 
	  }
      char cbuf[301];
	  ZeroMemory(cbuf,sizeof(cbuf));
	  int nItem = GroupClistCtrl.GetNextSelectedItem(pos);
      GroupClistCtrl.GetItemText(nItem,0,cbuf,300);
	  CString CSGrpName = cbuf;
	   if(MainGroupObj->DeleteGroup(CSGrpName) == true)
	   {
	    CString CSmpath;
		MainConfigObj->IOSysFilesPath(true,CSmpath);
	    if(DeleteFile((LPCTSTR)CSmpath + CSGrpName + ".grp") == false)
	    {
	     gFunMessageBox("Group delete error!",MainConfigObj);
	    }
	   }
	  }
	}
	FillGroupListBox(GroupClistCtrl);
return;
}

void CPinkCard2Dlg::OnLvnItemchangedGroupsList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	*pResult = 0;
}

//Doubble click on item
void CPinkCard2Dlg::OnLvnItemActivateGroupsList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMIA = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;
}

void CPinkCard2Dlg::OnLvnItemchangingGroupsList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	*pResult = 0;
}

//Click on row on Group ListBox
void CPinkCard2Dlg::OnNMClickGroupsList1(NMHDR *pNMHDR, LRESULT *pResult)
{
 *pResult = 0;
}

bool CPinkCard2Dlg::load_std_options_data(void)
{
	CString CSPathBuf;
	MainConfigObj->IOSysFilesPath(true,CSPathBuf);
	if(CSPathBuf.IsEmpty() == true)
	{
	 CString CSPathBuf;
     wGetModulePath(CSPathBuf);
	 MainConfigObj->IOSysFilesPath(false,CSPathBuf);
	}

	if(MainConfigObj->CSNetProvName.IsEmpty() == true)
	{
	 MainConfigObj->CSNetProvName = "Microsoft Windows Network";
	}
    
	if(MainConfigObj->IPortNumber == 0)
	{
     MainConfigObj->IPortNumber = 2689;
	}

return true;
}

afx_msg void CPinkCard2Dlg::OnContextMenu(CWnd* pWnd , CPoint point)
{
    
	//HOSTS LIST CListCtrl
	if(GetDlgItem(IDC_LAN_RESOURCESLIST1) == pWnd)
	{
     if(LanClistCtrl.GetSelectedCount() > 0)
	 {
	  CMenu menu;
      menu.LoadMenu(IDR_CONTEXT_HOSTS_MENU1);
      CMenu *pContextMenu = menu.GetSubMenu(0);
      pContextMenu->TrackPopupMenu(TPM_LEFTALIGN | 
      TPM_LEFTBUTTON | TPM_RIGHTBUTTON,
      point.x, point.y, AfxGetMainWnd());
	 }else
	 {
	  gFunMessageBox("Please select hosts!",MainConfigObj);
	 }
	} 
	
    //GROUP LIST CListCtrl
	if(GetDlgItem(IDC_GROUPS_LIST1) == pWnd)
	{
     if(GroupClistCtrl.GetSelectedCount() > 0)
	 {
	  CMenu menu;
      menu.LoadMenu(IDR_CONTEXT_GROUP_MENU1);
      CMenu *pContextMenu = menu.GetSubMenu(0);
      pContextMenu->TrackPopupMenu(TPM_LEFTALIGN | 
      TPM_LEFTBUTTON | TPM_RIGHTBUTTON,
      point.x, point.y, AfxGetMainWnd());
	 }else
	 {
	  gFunMessageBox("Please select groups!",MainConfigObj);
	 }
	} 

return afx_msg void();
}

void CPinkCard2Dlg::OnRMenuSendmessage()
{
 CSendMessageDlg* dlg = new CSendMessageDlg(0,MainConfigObj);
 dlg->DoModal();
 delete dlg;
return;
}

void CPinkCard2Dlg::OnMenuSchedulesend()
{
 CScheduleSendDlg* dlg = new CScheduleSendDlg;
 dlg->DoModal();
 delete dlg;
return;	
}



bool CPinkCard2Dlg::GetFirstSelectedItemTextFromClistCtrl(CString& CSresult, const CListCtrl& rControl)
{
 POSITION pos = rControl.GetFirstSelectedItemPosition();
 if (pos == NULL)
 {
  return false; 
 }
 if(rControl.GetSelectedCount() > 1)
 {
  return false; 
 }
 char cbuf[301];
 ZeroMemory(cbuf,sizeof(cbuf));
 int nItem = rControl.GetNextSelectedItem(pos);
 rControl.GetItemText(nItem,0,cbuf,300);
 CSresult = cbuf;
return true;
}

bool CPinkCard2Dlg::GetFirstSelectedItemTextFromGroupClistCtrl(CString& CSresult)
{
 POSITION pos = GroupClistCtrl.GetFirstSelectedItemPosition();
 if (pos == NULL)
 {
  return false; 
 }
 if(GroupClistCtrl.GetSelectedCount() > 1)
 {
  return false; 
 }
 char cbuf[301];
 ZeroMemory(cbuf,sizeof(cbuf));
 int nItem = GroupClistCtrl.GetNextSelectedItem(pos);
 GroupClistCtrl.GetItemText(nItem,0,cbuf,300);
 CSresult = cbuf;
return true;
}

int CPinkCard2Dlg::FillGroupItemsListBox(CListCtrl& ClistCtrlObj,const CString& CSGroupName)
{
 ClistCtrlObj.DeleteAllItems();
 int nColumnCount = ClistCtrlObj.GetHeaderCtrl()->GetItemCount();
   if(nColumnCount > 0)
   {
    for (int i=0;i < nColumnCount ;i++)
    {
     ClistCtrlObj.DeleteColumn(0);
    }
   }
 ClistCtrlObj.SetImageList(&MyImageList,LVSIL_SMALL);
 ClistCtrlObj.InsertColumn(0,"item name",LVCFMT_LEFT,120);
 LVITEM lvi;
 lvi.mask = LVIF_IMAGE | LVIF_TEXT;
  
 vector <CString> GrpItemData;
 MainGroupObj->GetGroupData(GrpItemData,CSGroupName);
 CString CStextdata;

 for(unsigned int lop = 0;lop < GrpItemData.size() ; lop++)
 {
  CStextdata =  GrpItemData[lop];
  lvi.pszText = CStextdata.GetBuffer(0);
  lvi.iItem = lop;
  lvi.iSubItem = 0;
  lvi.iImage = (1%8);
  ClistCtrlObj.InsertItem(&lvi);
  CStextdata.ReleaseBuffer();
 }
	return 0;
}

void CPinkCard2Dlg::OnBnClickedButtonTest()
{
 
// for(int lop = 0;lop<63;lop++)
// {
//  FillHostsListBox(LanClistCtrl);
// }

//vector<string> vs_hosts;
//vector<string> vs_comment;
//CCSocket mySock;
//CString domain;
//for(int fuk = 0;fuk <70;fuk++)
//{
//   vs_hosts.clear();
//   vs_comment.clear();
//   GetDlgItemText(IDC_COMBO_LANDOMAIN,domain);
//   unsigned int ret = mySock.EnumLanHosts(vs_hosts,vs_comment,domain,MainConfigObj->CSNetProvName);
//}  
//
// unsigned int mukacz = vs_hosts.size();
//
// for(unsigned int luk = 0;luk<vs_hosts.size();luk++)
// {
//  AfxMessageBox((char*)vs_hosts[luk].c_str());
// }


return;
}

void CPinkCard2Dlg::OnTrayMenuClose()
{
 if(gFunAskMessageBox("Would you like to close this program ?",MainConfigObj) == true)
 {
  this->DestroyWindow();
 }	
}

void CPinkCard2Dlg::OnMenuExitApp()
{
 if(gFunAskMessageBox("Would you like to close this program ?",MainConfigObj) == true)
 {
  this->DestroyWindow();
 }
return;
}

void CPinkCard2Dlg::OnPinkcard2menuAbout()
{
 CAboutDlg* dlg = new CAboutDlg;
 dlg->DoModal();
 delete dlg;
return;
}

void CPinkCard2Dlg::OnMenuConfigDlgDoModal()
{
 COptionsDlg* dlg = new COptionsDlg(0,MainConfigObj);
 dlg->DoModal();
 delete dlg;
return;
}

int CPinkCard2Dlg::LoadUserScheduledEvent(void)
{
	return 0;
}

void CPinkCard2Dlg::TESTER(void)
{
 
return;
}
