#if !defined(AFX_VIDEOLOSSDLG_H__57ABF917_83C2_4014_A8B8_E105DA95F08C__INCLUDED_)
#define AFX_VIDEOLOSSDLG_H__57ABF917_83C2_4014_A8B8_E105DA95F08C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VideoLossDlg.h : header file
//
#include "GridCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CVideoLossDlg dialog

class CVideoLossDlg : public CDialog
{
// Construction
public:
	CVideoLossDlg(CWnd* pParent = NULL,long lNetHandle = 0);   // standard constructor

	void	InitGrid();
	void	ReadVL();
	void	FillDateTimeInfo(std::vector<NS_WEEK_TIME_S>& emVectorDateTime);

// Dialog Data
	//{{AFX_DATA(CVideoLossDlg)
	enum { IDD = IDD_DIALOG_VIDEOLOSS };
	CGridCtrl	m_stWeek;
	UINT		m_nVLSensitivity;
	BOOL		m_bVLEnalbe;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVideoLossDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CVideoLossDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnWrite();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	long				m_lNetHandle;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIDEOLOSSDLG_H__57ABF917_83C2_4014_A8B8_E105DA95F08C__INCLUDED_)
