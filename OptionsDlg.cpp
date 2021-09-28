// OptionsDlg.cpp : implementation file

#include "stdafx.h"
#include "PinkCard2.h"
#include "OptionsDlg.h"
#include "ProgramConfiguration.h"

// COptionsDlg dialog
IMPLEMENT_DYNAMIC(COptionsDlg, CDialog)
COptionsDlg::COptionsDlg(CWnd* pParent /*=NULL*/,CProgramConfiguration* cfg)
	: CDialog(COptionsDlg::IDD, pParent)
	, lpcfg(cfg)
{
}

COptionsDlg::~COptionsDlg()
{
}

void COptionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OPTIONS_CHECK_SPLASH, splash_checkbox);
}


BEGIN_MESSAGE_MAP(COptionsDlg, CDialog)
	ON_EN_CHANGE(IDC_OPTIONS_PROVNAME_EDIT1, OnEnChangeOptionsProvnameEdit)
	ON_EN_CHANGE(IDC_OPTIONS_PORT_EDIT2, OnEnChangeOptionsPortEdit)
	ON_BN_CLICKED(IDC_OPTIONS_CHECK_SPLASH, OnBnClickedOptionsCheckSplash)
	ON_EN_CHANGE(IDC_OPTIONS_SYSPATH_EDIT, OnEnChangeOptionsSyspathEdit)
	ON_BN_CLICKED(IDC_OPTIONS_DEFAULT_BUTTON, OnBnClickedOptionsDefaultButton1)
	ON_BN_CLICKED(IDC_OPTIONS_CHECK_AUTOHIDEONSEND_CHECK, OnBnClickedOptionsCheckAutoHideOnSendCheck)
	ON_BN_CLICKED(IDC_OPTIONS_CHECK_GFX_CHECK, OnBnClickedOptionsCheckGfxCheck)
	ON_EN_CHANGE(IDC_OPTIONS_SKINPATH_EDIT, OnEnChangeOptionsSkinPathEdit)
	ON_BN_CLICKED(IDC_OPTIONS_SETSKINFOLDER_BUTTON, OnBnClickedOptionsSetSkinFolderButton)
	ON_BN_CLICKED(IDC_OPTIONS_SETPATHFOLDER_BUTTON, OnBnClickedOptionsSetpathfolderButton)
	ON_BN_CLICKED(IDC_OPTIONS_DEFAULTSKINPATH_BUTTON, OnBnClickedOptionsDefaultSkinPathButton)
END_MESSAGE_MAP()


// COptionsDlg message handlers
void COptionsDlg::OnEnChangeOptionsProvnameEdit()
{
	CString CSprovname;
	this->GetDlgItemText(IDC_OPTIONS_PROVNAME_EDIT1,CSprovname);
	lpcfg->CSNetProvName = CSprovname;
return;	
}

void COptionsDlg::OnEnChangeOptionsPortEdit()
{
	char buf[101];
	ZeroMemory(buf,sizeof(buf));
	this->GetDlgItemText(IDC_OPTIONS_PORT_EDIT2,buf,100);
	lpcfg->IPortNumber = atoi(buf);
return;	
}

BOOL COptionsDlg::OnInitDialog(void)
{
	splash_checkbox.SubclassDlgItem(IDC_OPTIONS_CHECK_SPLASH,this);
	HideOnSendCheckBox.SubclassDlgItem(IDC_OPTIONS_CHECK_AUTOHIDEONSEND_CHECK,this);
	UseSkinBmpCheckBox.SubclassDlgItem(IDC_OPTIONS_CHECK_GFX_CHECK,this);
	SetDlgItemText(IDC_OPTIONS_PROVNAME_EDIT1,lpcfg->CSNetProvName);
	CString CSPathTemp;
	lpcfg->IOSysFilesPath(true,CSPathTemp);
	SetDlgItemText(IDC_OPTIONS_SYSPATH_EDIT,CSPathTemp);
	SetDlgItemText(IDC_OPTIONS_SKINPATH_EDIT,lpcfg->CSSkinPath); 
    int Iport =  lpcfg->IPortNumber;
	char buf[101];
	ZeroMemory(buf,sizeof(buf));
	_itoa(Iport,buf,10);
	CString CSPort;
	CSPort = buf;
    SetDlgItemText(IDC_OPTIONS_PORT_EDIT2,CSPort); 
    
	if(lpcfg->bShowSplashScreen == true)
    {
	 splash_checkbox.SetCheck(BST_CHECKED);
    }
	else
	{
	 splash_checkbox.SetCheck(BST_UNCHECKED);
	}

    if(lpcfg->bUseBmpSkin == true)
    {
	 UseSkinBmpCheckBox.SetCheck(BST_CHECKED);
    }
	else
	{
	 UseSkinBmpCheckBox.SetCheck(BST_UNCHECKED);
	}

	if(lpcfg->bAutoHideOnSend == true)
    {
	 HideOnSendCheckBox.SetCheck(BST_CHECKED);
    }
	else
	{
	 HideOnSendCheckBox.SetCheck(BST_UNCHECKED);
	}
 return true;
}

void COptionsDlg::OnBnClickedOptionsCheckSplash()
{
 if(splash_checkbox.GetCheck() == BST_CHECKED)
 {
  lpcfg->bShowSplashScreen = true;
 }
 else
 {
  lpcfg->bShowSplashScreen = false;
 }
return;
}

void COptionsDlg::OnEnChangeOptionsSyspathEdit()
{
	CString CSSysFilesPath;
	this->GetDlgItemText(IDC_OPTIONS_SYSPATH_EDIT,CSSysFilesPath);
	lpcfg->IOSysFilesPath(false,CSSysFilesPath);//Save data to obj...
return;	
}

void COptionsDlg::OnBnClickedOptionsDefaultButton1()
{
 CString CSmodulePath;
 wGetModulePath(CSmodulePath);
 this->SetDlgItemText(IDC_OPTIONS_SYSPATH_EDIT,CSmodulePath);
return;
}

void COptionsDlg::OnBnClickedOptionsCheckAutoHideOnSendCheck()
{
 if(HideOnSendCheckBox.GetCheck() == BST_CHECKED)
 {
  lpcfg->bAutoHideOnSend = true;
 }
 else
 {
  lpcfg->bAutoHideOnSend = false;
 }
return;
}

void COptionsDlg::OnBnClickedOptionsCheckGfxCheck()
{
if(UseSkinBmpCheckBox.GetCheck() == BST_CHECKED)
 {
  lpcfg->bUseBmpSkin = true;
 }
 else
 {
  lpcfg->bUseBmpSkin = false;
 }
return;	
}

void COptionsDlg::OnEnChangeOptionsSkinPathEdit()
{
 CString CStemp;
 this->GetDlgItemText(IDC_OPTIONS_SKINPATH_EDIT,CStemp);
 lpcfg->CSSkinPath = CStemp;
return;
}

void COptionsDlg::OnBnClickedOptionsSetSkinFolderButton()
{
 char Buff[300];
 ZeroMemory(Buff,sizeof(Buff));
 LPCTSTR lpcPrompt = "Please select directory";
 wDirectoryPicker(lpcPrompt,Buff,m_hWnd);
 SetDlgItemText(IDC_OPTIONS_SKINPATH_EDIT,Buff); 
return;
}

void COptionsDlg::OnBnClickedOptionsSetpathfolderButton()
{
 char Buff[300];
 ZeroMemory(Buff,sizeof(Buff));
 LPCTSTR lpcPrompt = "Please select directory";
 wDirectoryPicker(lpcPrompt,Buff,m_hWnd);
 CString CSSkinFolder = Buff;
 if(CSSkinFolder.GetLength() > 3)
 {
  CSSkinFolder.Append("\\");
 }
 SetDlgItemText(IDC_OPTIONS_SYSPATH_EDIT,CSSkinFolder.GetBuffer(0));  
 CSSkinFolder.ReleaseBuffer();
return;
}

void COptionsDlg::OnBnClickedOptionsDefaultSkinPathButton()
{
 CString CSmodulePath;
 wGetModulePath(CSmodulePath);
 CSmodulePath.Append("skins\\default\\");
 if(CSmodulePath.GetLength() != 0)
 {
  this->SetDlgItemText(IDC_OPTIONS_SKINPATH_EDIT,CSmodulePath);
 }
return;
}
