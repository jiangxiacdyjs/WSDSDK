#if !defined(AFX_CASENSORINDLG_H__370995A9_4679_4B85_A78F_01799B65B405__INCLUDED_)
#define AFX_CASENSORINDLG_H__370995A9_4679_4B85_A78F_01799B65B405__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CASensorInDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCASensorInDlg dialog

class CCASensorInDlg : public CDialog
{
// Construction
public:
	CCASensorInDlg(CWnd* pParent = NULL,long lNetHandle = 0);   // standard constructor

	void	LoadParam(); 
	
// Dialog Data
	//{{AFX_DATA(CCASensorInDlg)
	enum { IDD = IDD_DIALOG_SENSOR_IN };
	int		m_nSensorIn;
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
	//{{AFX_VIRTUAL(CCASensorInDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCASensorInDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnRadioSensorIn();
	afx_msg void OnBtnSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	long		m_lNetHandle;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CASENSORINDLG_H__370995A9_4679_4B85_A78F_01799B65B405__INCLUDED_)
