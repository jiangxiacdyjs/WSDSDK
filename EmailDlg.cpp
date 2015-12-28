// EmailDlg.cpp : implementation file
//

#include "stdafx.h"
#include "netsdk_demo.h"
#include "EmailDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEmailDlg dialog
CEmailDlg::CEmailDlg(CWnd* pParent /*=NULL*/,long lNetHandle)
	: CDialog(CEmailDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEmailDlg)
	m_strAddr	= _T("");
	m_strPwd	= _T("");
	m_strToAddr = _T("");
	m_strUser	= _T("");
	//}}AFX_DATA_INIT
	m_lNetHandle	= lNetHandle;
}

void CEmailDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEmailDlg)
	DDX_Text(pDX, IDC_EDIT_ADDR, m_strAddr);
	DDX_Text(pDX, IDC_EDIT_PWD, m_strPwd);
	DDX_Text(pDX, IDC_EDIT_TO_ADDR, m_strToAddr);
	DDX_Text(pDX, IDC_EDIT_USER, m_strUser);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEmailDlg, CDialog)
	//{{AFX_MSG_MAP(CEmailDlg)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEmailDlg message handlers

BOOL CEmailDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	theApp.m_lang.TransDialog(m_hWnd, IDD);
	
	
	LoadParam();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEmailDlg::LoadParam() 
{
    unsigned int size = 0;
    NS_CA_EMAIL_INFO_S cfg;
    ZeroMemory(&cfg, sizeof(cfg));
    if(NS_NET_GetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_GET_CA_EMAIL_INFO, &cfg, &size) != 0)
    {
        AfxMessageBox(_T("Get Alarm Email Config Failed."));
        return ;
    }
    m_strUser = cfg.smtpuser;
    m_strAddr = cfg.smtpserver;
    m_strPwd = cfg.smtppasswd;
    m_strToAddr = cfg.toaddr;

    UpdateData(FALSE);
}

void CEmailDlg::OnBtnSave() 
{
	// TODO: Add your control notification handler code here
	
    UpdateData();
    NS_CA_EMAIL_INFO_S cfg;
    unsigned int size = sizeof(cfg);
    ZeroMemory(&cfg, sizeof(cfg));
    strcpy(cfg.smtpuser, m_strUser);
    strcpy(cfg.smtpserver, m_strAddr);
    strcpy(cfg.smtppasswd, m_strPwd);
    strcpy(cfg.toaddr, m_strToAddr);
    if(NS_NET_SetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_SET_CA_EMAIL_INFO, &cfg, size) != 0)
    {
        AfxMessageBox(_T("Set Alarm Email Config Failed."));
        return ;
    }
    AfxMessageBox(_T("OK"));
}
