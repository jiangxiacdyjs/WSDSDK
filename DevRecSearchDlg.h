#if !defined(AFX_DEVRECSEARCHDLG_H__8CDA8B3B_E432_4188_8F49_488EB7C27CEA__INCLUDED_)
#define AFX_DEVRECSEARCHDLG_H__8CDA8B3B_E432_4188_8F49_488EB7C27CEA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DevRecSearchDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDevRecSearchDlg dialog

class CDevRecSearchDlg : public CDialog
{
// Construction
public:
	CDevRecSearchDlg(CWnd* pParent = NULL,long lNetHandle = 0);   // standard constructor

	void	CreateFileList();
		
	
// Dialog Data
	//{{AFX_DATA(CDevRecSearchDlg)
	enum { IDD = IDD_DIALOG_DEV_RECORD_SEARCH };
	CListCtrl	m_listFile;

	CTime	m_dateStart;
	CTime	m_dateStop;
	CTime	m_timeStart;
	CTime	m_timeStop;
	int		m_nDevRecType;

	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDevRecSearchDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDevRecSearchDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSearchStart();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	long		m_lNetHandle;

    afx_msg void OnBnClickedNextPage();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEVRECSEARCHDLG_H__8CDA8B3B_E432_4188_8F49_488EB7C27CEA__INCLUDED_)
