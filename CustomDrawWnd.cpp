// CustomDrawWnd.cpp : implementation file
//

#include "stdafx.h"
#include "CustomDrawWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustomDrawWnd

CCustomDrawWnd::CCustomDrawWnd()
{
}

CCustomDrawWnd::~CCustomDrawWnd()
{
}


BEGIN_MESSAGE_MAP(CCustomDrawWnd, CWnd)
	//{{AFX_MSG_MAP(CCustomDrawWnd)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CCustomDrawWnd message handlers


BOOL CCustomDrawWnd::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	PaintBkgnd();

	return CWnd::OnEraseBkgnd(pDC);
}

void CCustomDrawWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	Paint();
	// Do not call CWnd::OnPaint() for painting messages
}
