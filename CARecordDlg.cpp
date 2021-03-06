// CARecordDlg.cpp : implementation file
//

#include "stdafx.h"
#include "netsdk_Demo.h"
#include "CARecordDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCARecordDlg dialog
CCARecordDlg::CCARecordDlg(CWnd* pParent /*=NULL*/,long lNetHandle)
	: CDialog(CCARecordDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCARecordDlg)
	m_nRecordTime = 0;
	//}}AFX_DATA_INIT
	m_lNetHandle	= lNetHandle;
}

void CCARecordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCARecordDlg)
	DDX_Text(pDX, IDC_EDIT_TIME, m_nRecordTime);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCARecordDlg, CDialog)
	//{{AFX_MSG_MAP(CCARecordDlg)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCARecordDlg message handlers

BOOL CCARecordDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	theApp.m_lang.TransDialog(m_hWnd, IDD);
	
	LoadParam();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCARecordDlg::LoadParam() 
{
    unsigned int size = 0;
    NS_CA_RECORD_INFO_S cfg;
    ZeroMemory(&cfg, sizeof(cfg));
    if(NS_NET_GetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_GET_CA_RECORD_INFO, &cfg, &size) != 0)
    {
        AfxMessageBox(_T("Get Alarm record Config Failed."));
        return ;
    }
    m_nRecordTime = cfg.recordtime;

    UpdateData(FALSE);
}

void CCARecordDlg::OnBtnSave() 
{
    UpdateData();
    NS_CA_RECORD_INFO_S cfg;
    unsigned int size = sizeof(cfg);
    ZeroMemory(&cfg, sizeof(cfg));
    cfg.recordtime= m_nRecordTime;
    if(NS_NET_SetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_SET_CA_RECORD_INFO, &cfg, size) != 0)
    {
        AfxMessageBox(_T("Set Alarm record Config Failed."));
        return ;
    }
    AfxMessageBox(_T("OK"));
}
