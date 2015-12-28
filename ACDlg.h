#if !defined(AFX_ACDLG_H__FAA5E763_1F3F_4932_875A_93F388118111__INCLUDED_)
#define AFX_ACDLG_H__FAA5E763_1F3F_4932_875A_93F388118111__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ACDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CACDlg dialog

class CACDlg : public CDialog
{
// Construction
public:
	CACDlg(CWnd* pParent = NULL,long lNetHandle = 0);   // standard constructor

	void	LoadParam(); 
		
// Dialog Data
	//{{AFX_DATA(CACDlg)
	enum { IDD = IDD_DIALOG_AC };
	CString	m_strAddr;
	UINT	m_nPort;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CACDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CACDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	long		m_lNetHandle;
	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ACDLG_H__FAA5E763_1F3F_4932_875A_93F388118111__INCLUDED_)
