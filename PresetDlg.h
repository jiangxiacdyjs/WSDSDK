#if !defined(AFX_PRESETDLG_H__42AFAFFC_436A_4F24_B12D_1012F7ACD72A__INCLUDED_)
#define AFX_PRESETDLG_H__42AFAFFC_436A_4F24_B12D_1012F7ACD72A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PresetDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPresetDlg dialog

class CPresetDlg : public CDialog
{
// Construction
public:
	CPresetDlg(CWnd* pParent = NULL,long lNetHandle = 0);   // standard constructor

	BOOL	InitPreset();
	BOOL	IsPresetPosExist(UINT nPresetID);
	
	void	CreatePresetList();
	void	FillPresetList();
	void	AddPresetList(UINT nPresetPosition,CString strPresetName);
	int		GetSelectList();

	BOOL	InitGuard();
		
// Dialog Data
	//{{AFX_DATA(CPresetDlg)
	enum { IDD = IDD_DIALOG_PRESET };
	CListCtrl	m_listPreset;
	CString		m_strPresetName;
	UINT		m_nPresetID;
	UINT		m_nGuarderPerp;
	UINT		m_nGuarderTime;
	BOOL		m_bGuardEnable;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPresetDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPresetDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnAdd();
	afx_msg void OnBtnDel();
	afx_msg void OnBtnInvoke();
	afx_msg void OnBtnGuarderSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	long						m_lNetHandle;

    NS_PRESET_INFO_S m_presets;
    NS_GUARDER_INFO_S   m_guarder;
    afx_msg void OnBnClickedCheckGuarder();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRESETDLG_H__42AFAFFC_436A_4F24_B12D_1012F7ACD72A__INCLUDED_)
