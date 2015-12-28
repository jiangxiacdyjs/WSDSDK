#if !defined(AFX_WADLG_H__F4EE55AC_6C77_41D3_BDBF_3925F8BBF9D3__INCLUDED_)
#define AFX_WADLG_H__F4EE55AC_6C77_41D3_BDBF_3925F8BBF9D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WADlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWADlg dialog

class CWADlg : public CDialog
{
// Construction
public:
    unsigned int m_lNetHandle;
	CWADlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CWADlg)
	enum { IDD = IDD_DIALOG_WA };
	UINT	m_agc;
	UINT	m_brightness;
	UINT	m_contrast;
	UINT	m_sharpness;
	UINT	m_saturation;
	UINT	m_focusstatus;
	UINT	m_shuttermode;
	UINT	m_shutterspeed;
	UINT	m_iris;
	UINT	m_gain;
	CString	m_content;
	UINT	m_index;
	UINT	m_left;
	UINT	m_top;
	double	m_multiple;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWADlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWADlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonSave();
	afx_msg void OnButtonSetDefault();
	afx_msg void OnButtonSetShutterMode();
	afx_msg void OnButtonSetShutterSpeed();
	afx_msg void OnButtonSetNorth();
	afx_msg void OnButtonShowAngle();
	afx_msg void OnButtonShow();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WADLG_H__F4EE55AC_6C77_41D3_BDBF_3925F8BBF9D3__INCLUDED_)
