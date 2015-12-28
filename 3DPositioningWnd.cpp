// 3DPositioningWnd.cpp: implementation of the C3DPositioningWnd class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "3DPositioningWnd.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

C3DPositioningWnd::C3DPositioningWnd()
{
	m_strTip = "3DPositioning";
	m_clrBackgroud = RGB(0,0,0);
}

C3DPositioningWnd::~C3DPositioningWnd()
{
    DestroyWindow();
}

void C3DPositioningWnd::PaintBkgnd()
{
	CPaintDC dc(this); // device context for painting

	CRect rcClient;
	GetClientRect(&rcClient);


	CPen newPen(PS_DOT,1,RGB(255, 0, 0));
	CPen* oldPen=dc.SelectObject(&newPen);
	
	dc.MoveTo(0,0);
	dc.LineTo(rcClient.right-1, 0);
	dc.LineTo(rcClient.right-1, rcClient.bottom-1);
	dc.LineTo(0, rcClient.bottom-1);
	dc.LineTo(0, 0);

	dc.SelectObject(oldPen);
}

void C3DPositioningWnd::Paint()
{
}
