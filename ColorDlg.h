#if !defined(AFX_COLORDLG_H__AEFDDA88_C879_4FF9_81F1_655390116023__INCLUDED_)
#define AFX_COLORDLG_H__AEFDDA88_C879_4FF9_81F1_655390116023__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColorDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CColorDlg dialog

class CColorDlg : public CDialog
{
// Construction
public:
	CColorDlg(CWnd* pParent = NULL,long lNetHandle = 0);   // standard constructor

	void	InitSld();
	
	// Dialog Data
	//{{AFX_DATA(CColorDlg)
	enum { IDD = IDD_DIALOG_COLOR };
	CSliderCtrl	m_sldGain;
	CSliderCtrl	m_sldSat;
	CSliderCtrl	m_sldHue;
	CSliderCtrl	m_sldCon;
	CSliderCtrl	m_sldBri;
	int		m_nLampFrequency;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CColorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnWrite();
	afx_msg void OnBtnDef();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	long				m_lNetHandle;

	UINT				m_nDefBright;
	UINT				m_nDefHue;
	UINT				m_nDefCon;
	UINT				m_nDefSat;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORDLG_H__AEFDDA88_C879_4FF9_81F1_655390116023__INCLUDED_)
