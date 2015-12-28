#if !defined(AFX_CAMDDLG_H__66A7690D_6A9E_4A4C_A8D3_FA02F83755F0__INCLUDED_)
#define AFX_CAMDDLG_H__66A7690D_6A9E_4A4C_A8D3_FA02F83755F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CAMDDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCAMDDlg dialog

class CCAMDDlg : public CDialog
{
// Construction
public:
	CCAMDDlg(CWnd* pParent = NULL,long lNetHandle = 0);   // standard constructor

	void	LoadParam(); 

// Dialog Data
	//{{AFX_DATA(CCAMDDlg)
	enum { IDD = IDD_DIALOG_CA_MD };
	BOOL	m_bACEn;
	BOOL	m_bEmailEn;
	BOOL	m_bFTPEn;
	BOOL	m_bRecordEn;
	BOOL	m_bSensorOut1En;
	BOOL	m_bSensorOut2En;
	BOOL	m_bSoundEn;
	UINT	m_nInterval;
	BOOL	m_bSnapEn;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCAMDDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCAMDDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		
public:
	long		m_lNetHandle;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAMDDLG_H__66A7690D_6A9E_4A4C_A8D3_FA02F83755F0__INCLUDED_)
