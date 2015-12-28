#if !defined(AFX_PORTDLG_H__AC0428DA_FA23_4E6C_B890_3EA6F9A74E68__INCLUDED_)
#define AFX_PORTDLG_H__AC0428DA_FA23_4E6C_B890_3EA6F9A74E68__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PortDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPortDlg dialog

class CPortDlg : public CDialog
{
// Construction
public:
	CPortDlg(CWnd* pParent = NULL,long lNetHandle = 0);   // standard constructor

	void	ReadPort();
	void	ReadPppoe();
	void	ReadDdns();

// Dialog Data
	//{{AFX_DATA(CPortDlg)
	enum { IDD = IDD_DIALOG_PORT };
	CComboBox	m_cmbDDNSSupport;
	UINT		m_nPortABC;
	UINT		m_nPortRTSP;
	UINT		m_nPortUpdate;
	UINT		m_nPortWeb;
	BOOL		m_bPPPOEEnable;
	CString		m_strPPPOEUser;
	CString		m_strPPPOEPwd;
	BOOL		m_bDDNSOpen;
	CString		m_strDDNSPwd;
	CString		m_strDDNSUrl;
	CString		m_strDDNSUser;
	int			m_nNicType;
	UINT		m_nFtpPort;
	BOOL		m_bUpnpABCOpen;
	BOOL		m_bUpnpFtpOpen;
	BOOL		m_bUpnpRtspOpen;
	BOOL		m_bUpnpUpdateOpen;
	BOOL		m_bUpnpWebOpen;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPortDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPortDlg)
	virtual BOOL OnInitDialog();
	
	afx_msg void OnBtnPortWrite();
	afx_msg void OnBtnPppoeWrite();
	afx_msg void OnBtnDdnsWrite();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		
public:
	long				m_lNetHandle;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PORTDLG_H__AC0428DA_FA23_4E6C_B890_3EA6F9A74E68__INCLUDED_)
