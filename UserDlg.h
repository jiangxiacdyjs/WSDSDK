#if !defined(AFX_USERDLG_H__665BEE54_DB0B_4086_8793_3AA4610155A9__INCLUDED_)
#define AFX_USERDLG_H__665BEE54_DB0B_4086_8793_3AA4610155A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UserDlg.h : header file
//
#include "afxtempl.h"
/////////////////////////////////////////////////////////////////////////////
// CUserDlg dialog

class CUserDlg : public CDialog
{
// Construction
public:
	CUserDlg(CWnd* pParent = NULL,long lNetHandle = 0);   // standard constructor

	void	InitUserList();
	BOOL	LoadParam();
	void	RefreshList();
	void	AddUserList(NS_USER_T emUser);
	
	void	SelectListItem(int nItem);
	int		GetSelectList();
	
	BOOL	IsUserExist(CString strUser, NS_USER_GROUP_E emPower);
	
// Dialog Data
	//{{AFX_DATA(CUserDlg)
	enum { IDD = IDD_DIALOG_USER };
	CListCtrl	m_listUser;
	BOOL		m_bAuthEnable;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUserDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUserDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckAuthEn();
	afx_msg void OnBtnUserAdd();
	afx_msg void OnBtnUserSet();
	afx_msg void OnBtnUserDel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	long								m_lNetHandle;

	CList<NS_USER_T,NS_USER_T>	m_emLstUser;


};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USERDLG_H__665BEE54_DB0B_4086_8793_3AA4610155A9__INCLUDED_)
