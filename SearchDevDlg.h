#pragma once
#include "afxwin.h"


// CSearchDevDlg dialog

class CSearchDevDlg : public CDialog
{
	DECLARE_DYNAMIC(CSearchDevDlg)

public:
	CSearchDevDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSearchDevDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_SEARCH_DEV };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	afx_msg LRESULT OnFoundDev(WPARAM wp,LPARAM lp);
	DECLARE_MESSAGE_MAP()
public:
    int AddDevice(CString strDevIP);
    std::map<CString, CString> m_devices;
    CListBox m_listDev;
    virtual BOOL OnInitDialog();
    afx_msg void OnClose();
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedCancel();
    afx_msg void OnTimer(UINT_PTR nIDEvent);
};
