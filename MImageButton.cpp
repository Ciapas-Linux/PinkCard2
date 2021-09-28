// MImageButton.cpp : implementation file
//

#include "stdafx.h"
#include "MImageButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMImageButton

CMImageButton::CMImageButton()
{
	m_ImageOnLeft = TRUE;
	m_ImageWidth = m_ImageHeight = 0;
}

CMImageButton::~CMImageButton()
{
	if( m_Up.GetSafeHandle() )
		m_Up.DeleteObject();
	if( m_Down.GetSafeHandle() )
		m_Down.DeleteObject();
	if( m_Focus.GetSafeHandle() )
		m_Focus.DeleteObject();
	if( m_Disabled.GetSafeHandle() )
		m_Disabled.DeleteObject();

}


BEGIN_MESSAGE_MAP(CMImageButton, CButton)
	//{{AFX_MSG_MAP(CMImageButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMImageButton message handlers

void CMImageButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	CRect Rect = lpDrawItemStruct->rcItem;
	SIZE DrawArea;
	int XOffset, YOffset, YTextOffset=0, YImageOffset=0;
	UINT nOffset = 0;
	UINT nFrameStyle=0;
	int	nStateFlag;
	CBitmap* pImage;

	CString Text;

	CDC DestDC;
	DestDC.Attach( lpDrawItemStruct->hDC );

	// Based on the size of the button text, and the images, determine drawing 
	// positions of each.
	GetWindowText( Text );
	DrawArea  = DestDC.GetTextExtent(Text);
	DrawArea.cx += (m_ImageWidth+4);
	if( DrawArea.cy > m_ImageHeight )
		YTextOffset = ( m_ImageHeight - DrawArea.cy ) /2;
	else
	{
		YImageOffset = (DrawArea.cy - m_ImageHeight) /2;
		DrawArea.cy = m_ImageHeight;
	}
	if( Text.Find( "&" ) >= 0 )
	{
		CSize Tmp;
		Tmp = DestDC.GetTextExtent( "&" );
		DrawArea.cx -= Tmp.cx;
	}
	XOffset = (Rect.right - DrawArea.cx)/2;
	YOffset = (Rect.bottom - DrawArea.cy)/2;
	
	// Determine if button is in the selected state
	if ( lpDrawItemStruct->itemState & ODS_SELECTED)
	{
		nFrameStyle = DFCS_PUSHED;
		pImage = m_Down.GetSafeHandle() ? &m_Down : &m_Up;
		nOffset += 1;
	}

	// Determine if button is disabled
	if( lpDrawItemStruct->itemState & ODS_DISABLED )
	{
		nStateFlag = DSS_DISABLED;
		pImage = m_Disabled.GetSafeHandle() ? &m_Disabled : &m_Up;
	}
	else
	{
		nStateFlag = DSS_NORMAL;
		pImage = &m_Up;
	}
	
	// Determine if button has the focus state
	if ( lpDrawItemStruct->itemState & ODS_FOCUS )
		pImage = m_Focus.GetSafeHandle() ? &m_Focus : &m_Up;

	// If button is selected, the use DrawFrameControl to display its frame
	if( ! (lpDrawItemStruct->itemState & ODS_SELECTED) )
	{
		// If the button is focused, then we need to draw the black rectangle,
		// and shrink the button a tiny bit (visual appearance of all buttons)
		if( lpDrawItemStruct->itemState & ODS_FOCUS  )
		{
			DestDC.Rectangle(Rect.left, Rect.top, Rect.right, Rect.bottom  );
			Rect.DeflateRect(1,1);
		}
		DestDC.DrawFrameControl( &Rect, DFC_BUTTON, DFCS_BUTTONPUSH | nFrameStyle);
	}
	else
	{
		// If it's not selected, then drawing is more complex
		// Create out pens and brushes for drawing, and draw a rectangle.
		CBrush NewBrush;
		NewBrush.CreateSolidBrush( ::GetSysColor( COLOR_3DFACE ) );
		CBrush* pOldBrush = (CBrush*)DestDC.SelectObject( &NewBrush );
		DestDC.Rectangle(Rect.left, Rect.top, Rect.right, Rect.bottom );
		CPen NewPen;
		NewPen.CreatePen( PS_SOLID, 1, GetSysColor(COLOR_3DSHADOW) );
		CPen* pOldPen = (CPen*)DestDC.SelectObject( &NewPen );

		// Then, shrink the rectangle a tiny bit, and draw the inner rectangle
		Rect.left++;
		Rect.top++;
		Rect.bottom--;
		Rect.right--;
		DestDC.Rectangle( Rect.left, Rect.top, Rect.right, Rect.bottom  );
		DestDC.SelectObject( pOldPen );
		DestDC.SelectObject( pOldBrush );
		
	}

	if( m_ImageOnLeft )
	{
		// Draw the bitmap image, transparently, and then the text
		DrawTransparent( &DestDC, XOffset+nOffset, YOffset+nOffset+YImageOffset, pImage );
		DestDC.DrawState( CPoint(XOffset+m_ImageWidth+4+nOffset, YOffset+nOffset+YTextOffset),
			DrawArea, Text, DST_PREFIXTEXT|nStateFlag, TRUE, 0, (HBRUSH)0  );
	}
	else
	{
		// Draw the text, and then the bitmap image transparently
		DestDC.DrawState( CPoint(XOffset+nOffset, YOffset+nOffset+YTextOffset), DrawArea, 
			Text, DST_PREFIXTEXT|nStateFlag, TRUE, 0, (HBRUSH)0  );
		DrawTransparent( &DestDC, XOffset+nOffset+DrawArea.cx+m_ImageWidth, YOffset+nOffset+YImageOffset, pImage );
	}

	// Draw the focus rectangle for the button
	if( ( lpDrawItemStruct->itemState & ODS_FOCUS ) ) 
	{
		RECT Rect2;
		Rect2 = Rect;
		Rect2.left += 3;
		Rect2.right -= 3;
		Rect2.top += 3;
		Rect2.bottom -= 3;
		DestDC.DrawFocusRect( &Rect2 );
	}

	DestDC.Detach();

	
//	CButton::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

// CMImageButton::SetData - Sets image information for the CMImageButton class
//      ImageOnLeft - If TRUE then image appears to left of text, otherwise image appears to the right
//      IDUp - Must specified the ID for the bitmap to display when in the normal, 'Up' state.
//      IDDown - Specifies the image to use for the down state of the button.  May be zero.
//      IDFocus - Specifies the image to use for the focus state of the button.  May be zero.
//      IDDisabled - Specifies the image to use for the disabled state of the button.  May be zero.
// Returns: TRUE if succesful, FALSE if not
// Comments: If IDDown or IDFocus are zero, then the Up image is used for those states.  If the
//      IDDisabled value is zero, then an embossed version of the up image is created and used.
BOOL CMImageButton::SetData(BOOL ImageOnLeft, UINT IDUp, UINT IDDown, UINT IDFocus, UINT IDDisabled)
{
	// If button already has data loaded, then delete the bitmaps
	if( m_Up.GetSafeHandle() )
		m_Up.DeleteObject();
	if( m_Down.GetSafeHandle() )
		m_Down.DeleteObject();
	if( m_Focus.GetSafeHandle() )
		m_Focus.DeleteObject();
	if( m_Disabled.GetSafeHandle() )
		m_Disabled.DeleteObject();
	
	// Load the 'Up' state bitmap (required).  Use it to specify height and width of all images
	m_Up.LoadBitmap( IDUp );
	BITMAP BM;
	m_Up.GetObject( sizeof(BM), &BM );
	m_ImageHeight = BM.bmHeight;
	m_ImageWidth = BM.bmWidth;

	// Store the ImageOnLeft value
	m_ImageOnLeft = ImageOnLeft;
	
	// Load other bitmaps as needed
	if( IDDown )
		m_Down.LoadBitmap( IDDown );
	if( IDFocus )
		m_Focus.LoadBitmap( IDFocus );
	
	// If a disabled image was specified, then load it, otherwise create an embossed version
	// of the 'Up' image.
	if( IDDisabled )
		m_Disabled.LoadBitmap( IDDisabled );
	else
		Emboss( m_Disabled, m_Up );
	
	return(TRUE);

}


// DrawTransparent - Draws a bitmap with transparency
// Parameters:
//     DC - HDC to draw bitmap on
//     x - X coordinate on DC to draw bitmap at
//     y - Y coordinate on DC to draw bitmap at
//     hbmImage - Handle to bitmap to display
//     LowerLeft - If True, then transparency color is taken from lower left of bitmap
//     crColor - If LowerLeft is false, then this must specify transparent color for bitmap
void CMImageButton::DrawTransparent(CDC* pDC, int x, int y, CBitmap* hbmImage, BOOL LowerLeft, COLORREF crColor)
{
	CDC hdcImage;
	CDC hdcTrans;
	CBitmap hbmTrans;
	BITMAP bmBitmap;
	
	hbmImage->GetObject( sizeof(bmBitmap), &bmBitmap );
	// Change Background and text color, saving values for end
	COLORREF crOldBack = pDC->SetBkColor(RGB(255,255,255));
	COLORREF crOldText = pDC->SetTextColor(RGB(0,0,0) );

	// Create Memory DCs to do our work in
	hdcImage.CreateCompatibleDC(pDC);
	hdcTrans.CreateCompatibleDC(pDC);

	// Select passed Image bitmap into Image memory DC
	hdcImage.SelectObject(hbmImage);
	
	// Create transparent bitmap, and select into transparent DC
	hbmTrans.CreateBitmap( bmBitmap.bmWidth, bmBitmap.bmHeight, 1, 1, NULL);
	hdcTrans.SelectObject( hbmTrans);

	// If LowerLeft is true, then determine transparent color from bitmap passed
	if( LowerLeft )
		crColor = hdcImage.GetPixel( 0, bmBitmap.bmHeight-1 );

	// Select background color (transparent color) for our image memory DC
	hdcImage.SetBkColor(crColor);

	hdcTrans.BitBlt( 0, 0, bmBitmap.bmWidth, bmBitmap.bmHeight, &hdcImage, 0, 0, SRCCOPY);

	// Perform BitBlt operations (this is where the Masking occurs)
	pDC->BitBlt( x, y, bmBitmap.bmWidth, bmBitmap.bmHeight, &hdcImage, 0, 0, SRCINVERT);
	pDC->BitBlt( x, y, bmBitmap.bmWidth, bmBitmap.bmHeight, &hdcTrans, 0, 0, SRCAND);
	pDC->BitBlt( x, y, bmBitmap.bmWidth, bmBitmap.bmHeight, &hdcImage, 0, 0, SRCINVERT);

	// Retore original background and text colors for the passed DC
	pDC->SetBkColor(crOldBack);
	pDC->SetTextColor(crOldText);

}

// Emboss - Basic embossing ability
// Parameters: 
//      bmDest - Destination bitmap
//      bmSource - Source bitmap to be embossed
// Comments: Uses brute force so we can maintain 3 colors on a disabled bitmap:
//    the highlight, dark, and transparent colors
void CMImageButton::Emboss( CBitmap& Dest, CBitmap& bmSource )
{
	CDC memDC, memDCEmbossed;
	CBitmap hbmOldBM, hbmOldBMEmbossed;
	BITMAP bmInfo;
	COLORREF crTransparent, crLo = ::GetSysColor(COLOR_3DHILIGHT),crHi=::GetSysColor(COLOR_3DSHADOW);
	COLORREF crCur, crNewTransparent = ::GetSysColor( COLOR_3DFACE );
	int Row, Col, ColorAvg=0, Total=0;

	// Determine information for the bitmap passed
	bmSource.GetObject( sizeof(bmInfo), &bmInfo );
	
	// Create memory DCs, and the return bitmap, for drawing and creation
	memDC.CreateCompatibleDC(NULL);
	memDCEmbossed.CreateCompatibleDC(NULL);
	memDC.SelectObject(&bmSource );
	Dest.CreateCompatibleBitmap( &memDC, bmInfo.bmWidth, bmInfo.bmHeight );
	
	// Select the new bitmap into the memory DC.  Now, when we draw on the memory DC, it
	// will manipulate the bitmap that is selected into it.
	memDCEmbossed.SelectObject( Dest );

	// Perform some basic color analisys, to determine what colors to use
	crTransparent = memDC.GetPixel( 0, bmInfo.bmHeight-1 );
	for( Row=0; Row < bmInfo.bmHeight; Row++ )
		for( Col=0; Col < bmInfo.bmWidth; Col++ )
		{
			crCur = memDC.GetPixel( Row, Col );
			if( crCur != crTransparent )
			{
				ColorAvg+=(GetGValue(crCur)+GetBValue(crCur)+GetRValue(crCur));
				Total++;
			}
		}
	ColorAvg /= Total;

	// Draw the original bitmap into the memory DC, which will set the color depth and
	// dimensions of the new bitmap.
	memDCEmbossed.BitBlt( 0, 0, bmInfo.bmWidth, bmInfo.bmHeight, &memDC, 0, 0, SRCCOPY);
	
	// Now, go through each pixel, and make it one of 3 colors: Dark, light, and transparent
	for( Row=0; Row < bmInfo.bmHeight; Row++ )
		for( Col=0; Col < bmInfo.bmWidth; Col++ )
		{
			crCur = memDC.GetPixel( Col, Row );
			if( crCur != crTransparent )
			{
				if( (GetGValue(crCur)+GetBValue(crCur)+GetRValue(crCur)) > ColorAvg )
					memDCEmbossed.SetPixel( Col, Row, crHi);
				else
					memDCEmbossed.SetPixel( Col, Row, crLo);
			}
			else
				memDCEmbossed.SetPixel( Col, Row, crNewTransparent );
		}
	// Destructors clean up for us.
}
