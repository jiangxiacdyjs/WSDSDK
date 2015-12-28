#if !defined(AFX_DEVRECORDDLG_H__5E0E4274_E259_4A2E_B2B1_014AECC4102F__INCLUDED_)
#define AFX_DEVRECORDDLG_H__5E0E4274_E259_4A2E_B2B1_014AECC4102F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DevRecordDlg.h : header file
//
#include "GridCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CDevRecordDlg dialog

class CDevRecordDlg : public CDialog
{
// Construction
public:
	CDevRecordDlg(CWnd* pParent = NULL,long lNetHandle = 0);   // standard constructor

	BOOL		InitControl();
	void		InitGrid();		
	void		InitList();
	void		FillDateTimeInfo(std::vector<NS_WEEK_TIME_S>& emVectorDateTime);
    void        Refresh();
    void        UpdateStatus(NS_DEV_RECORD_STATUS_E status);

// Dialog Data
	//{{AFX_DATA(CDevRecordDlg)
	enum { IDD = IDD_DIALOG_DEV_RECORD };
	CGridCtrl	m_stWeek;
	CListCtrl	m_listDisk;
	CStatic		m_stRecordStatus;
	DWORD		m_dwDiskReserve;
	int			m_nDiskStrategy;
	DWORD		m_dwFileMaxTime;
	int			m_nFileStrategy;
    NS_DEV_RECORD_SIZE_E    m_rcrdchn;
	UINT	m_dwMaxAlarmFileTime;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDevRecordDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDevRecordDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnStart();
	afx_msg void OnBtnStop();
	afx_msg void OnBtnRecordRead();
	afx_msg void OnBtnRecordSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	long		m_lNetHandle;

    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnClose();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEVRECORDDLG_H__5E0E4274_E259_4A2E_B2B1_014AECC4102F__INCLUDED_)
