#if !defined(AFX_BPSDLG_H__546CCD80_7209_4A6C_AC39_47A878EB10ED__INCLUDED_)
#define AFX_BPSDLG_H__546CCD80_7209_4A6C_AC39_47A878EB10ED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BPSDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBPSDlg dialog

class CBPSDlg : public CDialog
{
    NS_BPS_INFO_S m_cfg;
// Construction
public:
	CBPSDlg(CWnd* pParent = NULL,long lNetHandle = 0);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBPSDlg)
	enum { IDD = IDD_DIALOG_BPS };
		// NOTE: the ClassWizard will add data members here
	int		m_nPicture;
	int		m_nVBR;
	int		m_nBitRate;
	int		m_nFrameRate;
	int		m_nIFrameInterval;
	int		m_nMaxBitRate;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBPSDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBPSDlg)
	afx_msg void OnBtnSave();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	long						m_lNetHandle;


};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BPSDLG_H__546CCD80_7209_4A6C_AC39_47A878EB10ED__INCLUDED_)
