#if !defined(AFX_BALLVIDEOMASKDLG_H__B6B52B2C_B055_4F7E_BAAC_3AB49949A1B7__INCLUDED_)
#define AFX_BALLVIDEOMASKDLG_H__B6B52B2C_B055_4F7E_BAAC_3AB49949A1B7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BallVideoMaskDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBallVideoMaskDlg dialog

class CBallVideoMaskDlg : public CDialog
{
public:
	long				m_lNetHandle;
// Construction
public:
	CBallVideoMaskDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBallVideoMaskDlg)
	enum { IDD = IDD_DIALOG_BALL_VIDEO_MASK };
	UINT	m_nColor;
	UINT	m_nHeight;
	UINT	m_nIndex;
	UINT	m_nWidth;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBallVideoMaskDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBallVideoMaskDlg)
	afx_msg void OnButtonSet();
	afx_msg void OnButtonShow();
	afx_msg void OnButtonHide();
	afx_msg void OnButtonDel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedButtonSetColor();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BALLVIDEOMASKDLG_H__B6B52B2C_B055_4F7E_BAAC_3AB49949A1B7__INCLUDED_)
