#if !defined(AFX_ALARMDLG_H__59C4EED9_DD4D_47C7_A2F9_D985A3424406__INCLUDED_)
#define AFX_ALARMDLG_H__59C4EED9_DD4D_47C7_A2F9_D985A3424406__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AlarmDlg.h : header file
//
#include "GridCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CAlarmDlg dialog

class CAlarmDlg : public CDialog
{
// Construction
public:
	CAlarmDlg(CWnd* pParent = NULL,long lNetHandle = 0);   // standard constructor

	void	FillDateTimeInfo(std::vector<NS_WEEK_TIME_S>& emVectorDateTime);
	void	InitGrid();	
	void	LoadParam();

// Dialog Data
	//{{AFX_DATA(CAlarmDlg)
	enum { IDD = IDD_DIALOG_ALARM };
	CGridCtrl		m_stWeek;
	BOOL			m_bAlarmEnable0;
	BOOL			m_bAlarmEnable1;
	BOOL			m_bAlarmEnable2;
	BOOL			m_bAlarmEnable3;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAlarmDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAlarmDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnWrite();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	long		m_lNetHandle;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALARMDLG_H__59C4EED9_DD4D_47C7_A2F9_D985A3424406__INCLUDED_)
