#if !defined(AFX_COMDLG_H__8A39DA0B_CBF8_4EE9_B6E4_4E820664A642__INCLUDED_)
#define AFX_COMDLG_H__8A39DA0B_CBF8_4EE9_B6E4_4E820664A642__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ComDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CComDlg dialog

class CComDlg : public CDialog
{
// Construction
public:
	CComDlg(CWnd* pParent = NULL,long lNetHandle = 0);   // standard constructor

	void		UpdateControls();
	
// Dialog Data
	//{{AFX_DATA(CComDlg)
	enum { IDD = IDD_DIALOG_COM };
	CComboBox	m_cmbPTZ;
	CEdit		m_editPTZAddress;
	CComboBox	m_cmbCheckBit;
	CComboBox	m_cmbStopBits;
	CComboBox	m_cmbDataBits;
	CComboBox	m_cmbBitrate;
	CComboBox	m_cmbCom;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CComDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnComsave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	long				m_lNetHandle;

	UINT				m_nCom;
	UINT				m_nStop;
	UINT				m_nData;
	UINT				m_nAddr;
	UINT				m_nBaud;
	
	CString				m_strCheckBit;
	CString				m_strProt;

	std::vector<std::string> m_emVectorPTZ;
	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMDLG_H__8A39DA0B_CBF8_4EE9_B6E4_4E820664A642__INCLUDED_)
