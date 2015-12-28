#if !defined(AFX_USERADDDLG_H__9CAD7239_BFE4_4358_9DA6_D6E23810EADA__INCLUDED_)
#define AFX_USERADDDLG_H__9CAD7239_BFE4_4358_9DA6_D6E23810EADA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UserAddDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUserAddDlg dialog

class CUserAddDlg : public CDialog
{
// Construction
public:
	CUserAddDlg(CWnd* pParent = NULL);   // standard constructor

	void	SetUser(CString strUser,CString strPassword,NS_USER_GROUP_E emPower);
	
	// Dialog Data
	//{{AFX_DATA(CUserAddDlg)
	enum { IDD = IDD_DIALOG_USER_ADD };
	CString	m_strPassword;
	CString	m_strUser;
	int		m_nGroup;
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUserAddDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUserAddDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	BOOL		m_bAddMode;
	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USERADDDLG_H__9CAD7239_BFE4_4358_9DA6_D6E23810EADA__INCLUDED_)
