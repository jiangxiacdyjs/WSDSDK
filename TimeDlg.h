#if !defined(AFX_TIMEDLG_H__BED620CB_F036_4DE5_8A02_24478B73F6B9__INCLUDED_)
#define AFX_TIMEDLG_H__BED620CB_F036_4DE5_8A02_24478B73F6B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TimeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTimeDlg dialog

class CTimeDlg : public CDialog
{
// Construction
public:
	CTimeDlg(CWnd* pParent = NULL,long lNetHandle = 0);   // standard constructor

	void	FillTimeZone();
	void	UpdateTimeCtrl();
	
// Dialog Data
	//{{AFX_DATA(CTimeDlg)
	enum { IDD = IDD_DIALOG_TIME };
		// NOTE: the ClassWizard will add data members here
	CDateTimeCtrl	m_DateTime;
	CComboBox		m_cmdTimeZone;
	BOOL			m_bNTPEnable;
	CString			m_strNTPServer;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTimeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTimeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBntWrite();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	long				m_lNetHandle;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIMEDLG_H__BED620CB_F036_4DE5_8A02_24478B73F6B9__INCLUDED_)
