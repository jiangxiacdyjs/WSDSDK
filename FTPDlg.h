#if !defined(AFX_FTPDLG_H__53B6DA61_6128_4880_9448_1F89A87980FF__INCLUDED_)
#define AFX_FTPDLG_H__53B6DA61_6128_4880_9448_1F89A87980FF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FTPDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFTPDlg dialog

class CFTPDlg : public CDialog
{
// Construction
public:
	CFTPDlg(CWnd* pParent = NULL,long lNetHandle = 0);   // standard constructor
	
	void	LoadParam(); 

// Dialog Data
	//{{AFX_DATA(CFTPDlg)
	enum { IDD = IDD_DIALOG_FTP };
	CString	m_strFTPHost;
	CString	m_strFTPUser;
	CString	m_strFTPPwd;
	CString	m_strFTPPath;
	int		m_nFTPType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFTPDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFTPDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		
public:
	long		m_lNetHandle;
	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FTPDLG_H__53B6DA61_6128_4880_9448_1F89A87980FF__INCLUDED_)
