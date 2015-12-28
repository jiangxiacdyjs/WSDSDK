#if !defined(AFX_NETDLG_H__CF00A4F3_BE8B_47AF_87EC_78B68DBBED4E__INCLUDED_)
#define AFX_NETDLG_H__CF00A4F3_BE8B_47AF_87EC_78B68DBBED4E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NetDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNetDlg dialog

class CNetDlg : public CDialog
{
// Construction
public:
	CNetDlg(CWnd* pParent = NULL,long lNetHandle = 0);   // standard constructor

	void		InitWifiAPList();
	
	void		ReadNet();
	void		ReadWifi();

// Dialog Data
	//{{AFX_DATA(CNetDlg)
	enum { IDD = IDD_DIALOG_NET };
		// NOTE: the ClassWizard will add data members here
	CListCtrl	m_listWifiAP;
	CComboBox	m_cmbWifiWepType;
	CComboBox	m_cmbWifiWepIndex;
	CComboBox	m_cmbWifiWepOpt;
	CComboBox	m_cmbWifiSecType;
	CString		m_strDNS;
	CString		m_strGateWay;
	CString		m_strIP;
	CString		m_strSubMask;
	BOOL		m_bDHCP;
	CString		m_strMac;
	BOOL		m_bWifiDHCP;
	BOOL		m_bWifiEnable;
	CString		m_strWifiIP;
	CString		m_strWifiMask;
	CString		m_strWifiMac;
	CString		m_strWifiGateWay;
	CString		m_strWifiSSID;
	BOOL		m_bWifiSecEn;
	CString		m_strWifiWepPass;
	BOOL		m_bWifiExist;
	CString		m_strWifiName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNetDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnWrite();
	afx_msg void OnBtnWifiWrite();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	long				m_lNetHandle;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETDLG_H__CF00A4F3_BE8B_47AF_87EC_78B68DBBED4E__INCLUDED_)
