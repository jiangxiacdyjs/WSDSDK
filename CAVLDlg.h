#if !defined(AFX_CAVLDLG_H__4AE0FAAE_9328_41EC_89CD_6437866F43AA__INCLUDED_)
#define AFX_CAVLDLG_H__4AE0FAAE_9328_41EC_89CD_6437866F43AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CAVLDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCAVLDlg dialog

class CCAVLDlg : public CDialog
{
// Construction
public:
	CCAVLDlg(CWnd* pParent = NULL,long lNetHandle = 0);   // standard constructor

	void	LoadParam(); 
	
// Dialog Data
	//{{AFX_DATA(CCAVLDlg)
	enum { IDD = IDD_DIALOG_CA_VL };
	BOOL	m_bACEn;
	BOOL	m_bEmailEn;
	BOOL	m_bSensorOut1En;
	BOOL	m_bSensorOut2En;
	BOOL	m_bSoundEn;
	UINT	m_nInterval;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCAVLDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCAVLDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	long		m_lNetHandle;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAVLDLG_H__4AE0FAAE_9328_41EC_89CD_6437866F43AA__INCLUDED_)
