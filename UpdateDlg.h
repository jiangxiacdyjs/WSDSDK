#if !defined(AFX_UPDATEDLG_H__B25E4876_48F5_4569_BB91_DABE994FD7A9__INCLUDED_)
#define AFX_UPDATEDLG_H__B25E4876_48F5_4569_BB91_DABE994FD7A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UpdateDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUpdateDlg dialog

class CUpdateDlg : public CDialog
{
// Construction
public:
	CUpdateDlg(CWnd* pParent = NULL,long lNetHandle = 0,CString strDevIP = _T(""));   // standard constructor

	CString		GetOpenPacketFile();
	BOOL		UpdatePacket(CString strPacketFile);
	BOOL		TcpUpdateFile(CString strIp,UINT nPort,CString strUpdateFile);
	BOOL		SendFileData(SOCKET hSocket,BYTE* pData,DWORD dwData);
	CString		ChangeDDNSIP(CString strHost);
		
// Dialog Data
	//{{AFX_DATA(CUpdateDlg)
	enum { IDD = IDD_DIALOG_UPDATE };
	CString	m_strPacketFile;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUpdateDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUpdateDlg)
	afx_msg void OnBtnOpen();
	afx_msg void OnBtnUpdate();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	long		m_lNetHandle;
	CString		m_strDevIP;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UPDATEDLG_H__B25E4876_48F5_4569_BB91_DABE994FD7A9__INCLUDED_)
