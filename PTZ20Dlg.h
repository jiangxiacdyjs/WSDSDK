#if !defined(AFX_PTZ20DLG_H__4A0564BC_E1C4_4D82_8D8F_C6D9E0E496C6__INCLUDED_)
#define AFX_PTZ20DLG_H__4A0564BC_E1C4_4D82_8D8F_C6D9E0E496C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PTZ20Dlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPTZ20Dlg dialog

class CPTZ20Dlg : public CDialog
{
// Construction
public:
	CPTZ20Dlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPTZ20Dlg)
	enum { IDD = IDD_DIALOG_PTZ20 };
	CComboBox	m_cmbCMD;
	int		m_data1;
	int		m_data2;
	CString	m_packet;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPTZ20Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPTZ20Dlg)
	afx_msg void OnButtonTest();
	afx_msg void OnRadioAuto();
	afx_msg void OnRadioDarm();
	afx_msg void OnRadioIdle();
	afx_msg void OnRadioInq();
	afx_msg void OnRadioCmr();
	afx_msg void OnRadioPattern();
	afx_msg void OnRadioProduce();
	afx_msg void OnRadioRegion();
	afx_msg void OnRadioSequence();
	afx_msg void OnRadioSys();
	afx_msg void OnRadioTitle();
	afx_msg void OnRadioVar();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PTZ20DLG_H__4A0564BC_E1C4_4D82_8D8F_C6D9E0E496C6__INCLUDED_)
