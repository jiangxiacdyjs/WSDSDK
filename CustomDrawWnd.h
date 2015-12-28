#if !defined(AFX_CUSTOMDRAWWND_H__E8470987_D48F_47BE_B2DD_448E5C969A22__INCLUDED_)
#define AFX_CUSTOMDRAWWND_H__E8470987_D48F_47BE_B2DD_448E5C969A22__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CustomDrawWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCustomDrawWnd window

class CCustomDrawWnd : public CWnd
{
// Construction
public:
	CCustomDrawWnd();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomDrawWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCustomDrawWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCustomDrawWnd)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	virtual void PaintBkgnd()=0;
	virtual void Paint()=0;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMDRAWWND_H__E8470987_D48F_47BE_B2DD_448E5C969A22__INCLUDED_)
