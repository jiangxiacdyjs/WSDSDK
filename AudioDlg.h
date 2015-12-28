#if !defined(AFX_AUDIODLG_H__F04E5BFD_134D_4B4A_99AA_87D5A18DA68A__INCLUDED_)
#define AFX_AUDIODLG_H__F04E5BFD_134D_4B4A_99AA_87D5A18DA68A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AudioDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAudioDlg dialog

class CAudioDlg : public CDialog
{
// Construction
public:
	CAudioDlg(CWnd* pParent = NULL,long lNetHandle = 0);   // standard constructor

	void		InitSld();
	BOOL		LoadParam();
	BOOL		SaveParam();

// Dialog Data
	//{{AFX_DATA(CAudioDlg)
	enum { IDD = IDD_DIALOG_AUDIO };
	CSliderCtrl	m_sldOutput;
	CSliderCtrl	m_sldInput;
	BOOL		m_bEnable;
	int			m_nCodec;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAudioDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAudioDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnCheckAudioIn();
	afx_msg void OnRadioCodec();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	long		m_lNetHandle;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUDIODLG_H__F04E5BFD_134D_4B4A_99AA_87D5A18DA68A__INCLUDED_)
