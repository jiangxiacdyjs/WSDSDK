#if !defined(AFX_EMAILDLG_H__43571C59_5C6F_494D_8C6B_199EDE40A6C2__INCLUDED_)
#define AFX_EMAILDLG_H__43571C59_5C6F_494D_8C6B_199EDE40A6C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EmailDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEmailDlg dialog

class CEmailDlg : public CDialog
{
// Construction
public:
	CEmailDlg(CWnd* pParent = NULL,long lNetHandle = 0);   // standard constructor

	void	LoadParam(); 
	
// Dialog Data
	//{{AFX_DATA(CEmailDlg)
	enum { IDD = IDD_DIALOG_EMAIL };
	CString	m_strAddr;
	CString	m_strPwd;
	CString	m_strToAddr;
	CString	m_strUser;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEmailDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEmailDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	long		m_lNetHandle;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EMAILDLG_H__43571C59_5C6F_494D_8C6B_199EDE40A6C2__INCLUDED_)
