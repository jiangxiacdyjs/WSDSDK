#if !defined(AFX_SENSOROUTDLG_H__8D4DF1D8_FDA1_4749_A544_21BAA91F7CBF__INCLUDED_)
#define AFX_SENSOROUTDLG_H__8D4DF1D8_FDA1_4749_A544_21BAA91F7CBF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SensorOutDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSensorOutDlg dialog

class CSensorOutDlg : public CDialog
{
// Construction
public:
	CSensorOutDlg(CWnd* pParent = NULL,long lNetHandle = 0);   // standard constructor

	void	LoadParam(); 

// Dialog Data
	//{{AFX_DATA(CSensorOutDlg)
	enum { IDD = IDD_DIALOG_SENSOR_OUT };
	BOOL	m_bSensorOut1;
	BOOL	m_bSensorOut2;
	UINT	m_nHoldTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSensorOutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSensorOutDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	long		m_lNetHandle;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SENSOROUTDLG_H__8D4DF1D8_FDA1_4749_A544_21BAA91F7CBF__INCLUDED_)
