#if !defined(AFX_VIDEOMASKDLG_H__6B9CC4AD_7780_4F06_BD7D_49DA6322BB0B__INCLUDED_)
#define AFX_VIDEOMASKDLG_H__6B9CC4AD_7780_4F06_BD7D_49DA6322BB0B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VideoMaskDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVideoMaskDlg dialog

class CVideoMaskDlg : public CDialog
{
// Construction
public:
    unsigned int m_lNetHandle;
	CVideoMaskDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CVideoMaskDlg)
	enum { IDD = IDD_DIALOG_VIDEO_MASK };
	UINT	m_nBottom;
	UINT	m_nLeft;
	UINT	m_nRight;
	UINT	m_nTop;
	BOOL	m_bEnable;
	UINT	m_nColor;

    UINT	m_nBottom2;
    UINT	m_nLeft2;
    UINT	m_nRight2;
    UINT	m_nTop2;
    BOOL	m_bEnable2;
    UINT	m_nColor2;

    UINT	m_nBottom3;
    UINT	m_nLeft3;
    UINT	m_nRight3;
    UINT	m_nTop3;
    BOOL	m_bEnable3;
    UINT	m_nColor3;

    UINT	m_nBottom4;
    UINT	m_nLeft4;
    UINT	m_nRight4;
    UINT	m_nTop4;
    BOOL	m_bEnable4;
    UINT	m_nColor4;
    //}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVideoMaskDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CVideoMaskDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedOk();
    virtual BOOL OnInitDialog();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIDEOMASKDLG_H__6B9CC4AD_7780_4F06_BD7D_49DA6322BB0B__INCLUDED_)
