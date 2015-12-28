#if !defined(AFX_TRACKDLG_H__66157A0D_6DAF_48A6_874D_C48B64F9F3C1__INCLUDED_)
#define AFX_TRACKDLG_H__66157A0D_6DAF_48A6_874D_C48B64F9F3C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TrackDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTrackDlg dialog

class CTrackDlg : public CDialog
{
// Construction
public:
	CTrackDlg(CWnd* pParent = NULL,long lNetHandle = 0);   // standard constructor

	BOOL	InitPreset();
	void	InitTrackList();
	void	InitControls();
	void	AddPresetToList(std::vector<NS_PRESET_S> vectorPreset);
	int		GetListSelect();
		
// Dialog Data
	//{{AFX_DATA(CTrackDlg)
	enum { IDD = IDD_DIALOG_TRACK };
	CListCtrl	m_listTrack;
	CComboBox	m_cmbStayTime;
	CComboBox	m_cmbPreset;
	CComboBox	m_cmbTrack;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTrackDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTrackDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnPtzAdd();
	afx_msg void OnBtnPtzDelete();
	afx_msg void OnBtnPtzWrite();
	afx_msg void OnBtnPtzInvoke();
	afx_msg void OnSelchangeComboPtzTrack();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	long						m_lNetHandle;

	std::vector<NS_PRESET_S>	m_vectorPreset;

	std::vector<NS_PRESET_S>	m_vectorTrackPreset;				

    NS_PRESET_INFO_S m_presets;
    NS_TRACK_INFO_S m_tracks;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRACKDLG_H__66157A0D_6DAF_48A6_874D_C48B64F9F3C1__INCLUDED_)
