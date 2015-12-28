#if !defined(AFX_GRIDCTRL_H__AE9CB1A4_1BC9_4616_B49D_0BC251F74C7A__INCLUDED_)
#define AFX_GRIDCTRL_H__AE9CB1A4_1BC9_4616_B49D_0BC251F74C7A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GridCtrl.h : header file
//
#include <afxtempl.h>
/////////////////////////////////////////////////////////////////////////////
// CGridCtrl window

#define GRID_ROW 8
#define GRID_COL 25

#define WM_GRID_CHANGE		WM_USER + 1000

class CGridCtrl : public CStatic
{
// Construction
public:
	CGridCtrl();

// Attributes
public:
	CDialog*		m_pDlgOwner;
	
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGridCtrl)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetGridItemData(int x, int y, int nVal);
	int GetGridItemData(int x, int y);
	void SetAllValue(int nVal);
	void SetWeekText(const CStringArray& arr);
	virtual ~CGridCtrl();

	// Generated message map functions
protected:
	void ChangeSelectAllState();
	BOOL IsAllSelect();
	BOOL IsInClient(CPoint point);
	void DrawBk(CDC *pDC);
	void SelectOneRow(CPoint point);
	void Select(CPoint point);
	void SelectAll();
	void DrawBlock(CDC *pDC);
	void DrawText(CDC *pDC);
	void DrawLine(CDC *pDC);

	BOOL NotifyChange();

protected:
	CFont m_font;
	CPoint m_ptStart;
	CPoint m_ptStop;
	CRect m_rcSelect;
	BOOL  m_bDrag;
	CRect m_rcCursorClient;
	int   m_arrData[GRID_ROW][GRID_COL];
	CRect m_arrRct[GRID_ROW][GRID_COL];

	CStringArray	m_arrWeekStr;

	//{{AFX_MSG(CGridCtrl)
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRIDCTRL_H__AE9CB1A4_1BC9_4616_B49D_0BC251F74C7A__INCLUDED_)
