#if !defined(AFX_MIMAGEBUTTON_H__D6751986_DDBD_11D3_9F4A_080009EE62AA__INCLUDED_)
#define AFX_MIMAGEBUTTON_H__D6751986_DDBD_11D3_9F4A_080009EE62AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MImageButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMImageButton window

class CMImageButton : public CButton
{
// Construction
public:
	CMImageButton();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMImageButton)
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL SetData( BOOL ImageOnLeft, UINT IDUp, UINT IDDown=0, UINT IDFocus=0, UINT IDDisabled=0);
	void DrawTransparent(CDC* pDC, int x, int y, CBitmap* hbmImage, BOOL LowerLeft=TRUE, COLORREF crColor=0);
	void Emboss( CBitmap& Dest, CBitmap& bmSource );
	void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

	// Bitmaps for image display
	CBitmap m_Up, m_Down, m_Focus, m_Disabled;
	// Bitmap height and width information
	int m_ImageWidth, m_ImageHeight;
	// Flag for image on left or right
	BOOL m_ImageOnLeft;

	virtual ~CMImageButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMImageButton)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MIMAGEBUTTON_H__D6751986_DDBD_11D3_9F4A_080009EE62AA__INCLUDED_)
