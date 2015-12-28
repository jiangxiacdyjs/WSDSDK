#if !defined(AFX_CARECORDDLG_H__DAD83945_DB26_44BD_A145_07A84F45D56D__INCLUDED_)
#define AFX_CARECORDDLG_H__DAD83945_DB26_44BD_A145_07A84F45D56D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CARecordDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCARecordDlg dialog

class CCARecordDlg : public CDialog
{
// Construction
public:
	CCARecordDlg(CWnd* pParent = NULL,long lNetHandle = 0);   // standard constructor

	void	LoadParam(); 
	
// Dialog Data
	//{{AFX_DATA(CCARecordDlg)
	enum { IDD = IDD_DIALOG_CA_RECORD };
	UINT	m_nRecordTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCARecordDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCARecordDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		
public:
	long		m_lNetHandle;

	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CARECORDDLG_H__DAD83945_DB26_44BD_A145_07A84F45D56D__INCLUDED_)
