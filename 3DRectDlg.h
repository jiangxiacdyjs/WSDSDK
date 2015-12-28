#if !defined(AFX_3DRECTDLG_H__DE882D83_3E28_4247_B788_67FDF92BB7A3__INCLUDED_)
#define AFX_3DRECTDLG_H__DE882D83_3E28_4247_B788_67FDF92BB7A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// 3DRectDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// C3DRectDlg dialog

class C3DRectDlg : public CDialog
{
// Construction
public:
	C3DRectDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(C3DRectDlg)
	enum { IDD = IDD_DIALOG_3D_RECT };
	UINT	m_nBottom;
	UINT	m_nLeft;
	UINT	m_nRight;
	UINT	m_nTop;
	int		m_nZoom;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C3DRectDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(C3DRectDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_3DRECTDLG_H__DE882D83_3E28_4247_B788_67FDF92BB7A3__INCLUDED_)
