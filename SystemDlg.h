#if !defined(AFX_SYSTEMDLG_H__D4486ED3_17D5_4E69_934B_B81AD03524A2__INCLUDED_)
#define AFX_SYSTEMDLG_H__D4486ED3_17D5_4E69_934B_B81AD03524A2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SystemDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSystemDlg dialog

class CSystemDlg : public CDialog
{
// Construction
public:
	CSystemDlg(CWnd* pParent = NULL,long lNetHandle = 0);   // standard constructor

	void	InitEncList();
	BOOL	LoadParam();
	
	void	FillCtrls();
	void	FillEncList();
	int		GetListSelect();
	
	BOOL	EncAdd();
	
// Dialog Data
	//{{AFX_DATA(CSystemDlg)
	enum { IDD = IDD_DIALOG_SYSTEM };
		// NOTE: the ClassWizard will add data members here
	CListCtrl	m_listEnc;
	CComboBox	m_cmbInput;
	CComboBox	m_cmbFormat;
	CComboBox	m_cmbStandard;
	CComboBox	m_cmbEncoder;
	CEdit		m_editWeb;
	CEdit		m_editLinux;
	CEdit		m_editDeviceName;
	CEdit		m_editDeviceID;
	CEdit		m_editChannel;
	CEdit		m_editVersion;
	int			m_nEncType;
	int			m_nVStandard;
	int			m_nEncFormat;
	int			m_nVIput;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSystemDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSystemDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnLoadDefault();
	afx_msg void OnBtnReset();
	afx_msg void OnBtnReboot();
	afx_msg void OnBtnSave();
	afx_msg void OnBtnEncAdd();
	afx_msg void OnBtnEncDel();
	afx_msg void OnBtnEncSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		
public:
	long								m_lNetHandle;

	UINT								m_nMaxVE;
	UINT								m_nMaxVI;
	std::vector<NS_VENCODE_TYPE_E>		m_emVectorVEncType;
	std::vector<NS_VENCODE_FORMAT_E>	m_emVectorVEncFormat;
	std::vector<NS_VI_STANDARD_E>		m_emVectorVStdandard;
	std::vector<NS_CHANNEL_INFO_T>		m_emVectorVEncChnS;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYSTEMDLG_H__D4486ED3_17D5_4E69_934B_B81AD03524A2__INCLUDED_)
