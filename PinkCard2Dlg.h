// PinkCard2Dlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "ProgramConfiguration.h"
#include "GroupObj.h"
#include "PinkCard2.h"

inline afx_msg LRESULT ThreadEnd( WPARAM wParam, LPARAM lParam ); 

// CPinkCard2Dlg dialog
class CPinkCard2Dlg : public CDialog
{
// Construction
public:
	CPinkCard2Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CGniazdaDlg)
	enum { IDD = IDD_PINKCARD2_DIALOG };
	//}}AFX_DATA

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
protected:
	HICON m_hIcon;
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT TimerId);
	afx_msg void OnKeyDown(UINT nChar,UINT nRepCnt,UINT nFlags);
	afx_msg HCURSOR OnQueryDragIcon();
	void OnClose();
	BOOL PreTranslateMessage(MSG* pMsg); 

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonExit();
	afx_msg void OnBnClickedButtonOptions();
	afx_msg void OnBnClickedButtonGroupsEdit();
private:
	CListCtrl LanClistCtrl;
	CImageList MyImageList;
	CComboBox LanDomains;
public:
	void AddTrayIcon(bool Add);
	afx_msg LRESULT TrayMessage(WPARAM  wParam, LPARAM lParam);
	void OnShow(void);
	void OnSize(UINT  nType, int cx, int cy);
	bool visible;
	void OnWindowPosChanging(WINDOWPOS* lpwndpos);
	bool FillDomainListBox(CComboBox& combo);
private:
	CProgramConfiguration* MainConfigObj;
public:
	afx_msg void OnBnClickedButtonAbout();
	afx_msg void OnCbnSelchangeComboLandomain();
	bool FillHostsListBox(CListCtrl& listctrl);
	afx_msg void OnBnClickedButtonGroupsAdd();
private:
	CGroupObj* MainGroupObj;
	CListCtrl GroupClistCtrl;
public:
	int FillGroupListBox(CListCtrl& mylistctrl);
	afx_msg void OnBnClickedButtonGroupsDelete();
	afx_msg void OnLvnItemchangedGroupsList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemActivateGroupsList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangingGroupsList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickGroupsList1(NMHDR *pNMHDR, LRESULT *pResult);
	bool load_std_options_data(void);
	afx_msg void OnContextMenu(CWnd* pWnd , CPoint point);
	afx_msg void OnRMenuSendmessage();
	afx_msg void OnMenuSchedulesend();
	bool GetFirstSelectedItemTextFromClistCtrl(CString& CSresult, const CListCtrl& rControl);
    bool GetFirstSelectedItemTextFromGroupClistCtrl(CString& CSresult);
	int FillGroupItemsListBox(CListCtrl& ClistCtrlObj,const CString& CSGroupName);
private:
	CBitmap bmpObjbg;
	UINT_PTR RefreshLanHostsClistObjTIMERid;
public:
	afx_msg void OnBnClickedButtonTest();
	afx_msg void OnTrayMenuClose();
	afx_msg void OnMenuExitApp();
	afx_msg void OnPinkcard2menuAbout();
	afx_msg void OnMenuConfigDlgDoModal();
private:
	vector<string>* lpvUserEventList;
public:
	int LoadUserScheduledEvent(void);
	void TESTER(void);
};


