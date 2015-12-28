#if !defined(AFX_OSDDLG_H__79E92006_1B44_4253_B0C8_4AF60525AAA3__INCLUDED_)
#define AFX_OSDDLG_H__79E92006_1B44_4253_B0C8_4AF60525AAA3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OSDDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COSDDlg dialog

class COSDDlg : public CDialog
{
// Construction
public:
	COSDDlg(CWnd* pParent = NULL,long lNetHandle = 0);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COSDDlg)
	enum { IDD = IDD_DIALOG_OSD };
	CString	m_strOSDChannel;
	BOOL	m_bOSDBps;
	BOOL	m_bOSDChannel;
	BOOL	m_bOSDTime;
	long	m_lBpsLeft;
	long	m_lBpsTop;
	long	m_lChnLeft;
	long	m_lChnTop;
	long	m_lTimeLeft;
	long	m_lTimeTop;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COSDDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COSDDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	long				m_lNetHandle;


};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OSDDLG_H__79E92006_1B44_4253_B0C8_4AF60525AAA3__INCLUDED_)
