#if !defined(AFX_MDDLG_H__2A4E833D_9EF0_40E2_8A7D_B49053EEF7A1__INCLUDED_)
#define AFX_MDDLG_H__2A4E833D_9EF0_40E2_8A7D_B49053EEF7A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MDDlg.h : header file
//
#include "GridCtrl.h"
#include "MDGridCtrl.h"
#include "afxwin.h"
/////////////////////////////////////////////////////////////////////////////
// CMDDlg dialog

class CMDDlg : public CDialog
{
// Construction
public:
	CMDDlg(CWnd* pParent = NULL,long lNetHandle = 0);   // standard constructor

	BOOL	InitControl();
	void	FillDateTimeInfo(std::vector<NS_WEEK_TIME_S>& emVectorDateTime);
	void	InitGrid();
	
// Dialog Data
	//{{AFX_DATA(CMDDlg)
	enum { IDD = IDD_DIALOG_MD };
	CGridCtrl	m_stWeek;
	BOOL		m_bMDEnable;
	UINT		m_nSensitivity;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMDDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMDDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnWrite();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	long				m_lNetHandle;

	
    CMDGridCtrl m_mdGrid;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MDDLG_H__2A4E833D_9EF0_40E2_8A7D_B49053EEF7A1__INCLUDED_)
