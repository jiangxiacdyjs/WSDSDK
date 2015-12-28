#if !defined(AFX_ENCRYPTSTRDLG_H__BD3B9095_569C_440A_8B95_70210E97D409__INCLUDED_)
#define AFX_ENCRYPTSTRDLG_H__BD3B9095_569C_440A_8B95_70210E97D409__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EncryptStrDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEncryptStrDlg dialog

class CEncryptStrDlg : public CDialog
{
// Construction
public:
    unsigned int m_lNetHandle;
	CEncryptStrDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEncryptStrDlg)
	enum { IDD = IDD_DIALOG_ENCRYPT_STR };
	CString	m_str;
	UINT	m_id;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEncryptStrDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEncryptStrDlg)
	afx_msg void OnBtnRead();
	afx_msg void OnBtnSave();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ENCRYPTSTRDLG_H__BD3B9095_569C_440A_8B95_70210E97D409__INCLUDED_)
