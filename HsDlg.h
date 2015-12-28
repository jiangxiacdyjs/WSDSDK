#if !defined(AFX_HSDLG_H__3A75BD24_9436_4F5B_BFDE_E4AFA2E22398__INCLUDED_)
#define AFX_HSDLG_H__3A75BD24_9436_4F5B_BFDE_E4AFA2E22398__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHsDlg dialog

class CHsDlg : public CDialog
{
// Construction
public:
	CHsDlg(CWnd* pParent = NULL,long lNetHandle = 0);   // standard constructor

	void	LoadParam(); 
	
// Dialog Data
	//{{AFX_DATA(CHsDlg)
	enum { IDD = IDD_DIALOG_HS };
	BOOL	m_bMdStart;
	BOOL	m_bMdStop;
	BOOL	m_bVlStart;
	BOOL	m_bVlResume;
	int		m_nMaxAlarmIn;
	int		m_nMaxAlarmOut;
	CString	m_strAcAddr;
	int		m_nAcPort;
	CString	m_strDevId;
	CString	m_strDevName;
	CString	m_strServerAddr;
	int		m_nServerPort;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnRead();
	afx_msg void OnBtnSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	long		m_lNetHandle;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HSDLG_H__3A75BD24_9436_4F5B_BFDE_E4AFA2E22398__INCLUDED_)
