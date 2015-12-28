// FTPDlg.cpp : implementation file
//

#include "stdafx.h"
#include "netsdk_demo.h"
#include "FTPDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFTPDlg dialog
CFTPDlg::CFTPDlg(CWnd* pParent /*=NULL*/,long lNetHandle)
	: CDialog(CFTPDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFTPDlg)
	m_strFTPHost	= _T("");
	m_strFTPUser	= _T("");
	m_strFTPPwd		= _T("");
	m_strFTPPath	= _T("");
	m_nFTPType		= 0;
	//}}AFX_DATA_INIT
	m_lNetHandle	= lNetHandle;
}

void CFTPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFTPDlg)
	DDX_Text(pDX, IDC_EDIT_FTP_HOST, m_strFTPHost);
	DDX_Text(pDX, IDC_EDIT_FTP_USER, m_strFTPUser);
	DDX_Text(pDX, IDC_EDIT_FTP_PWD, m_strFTPPwd);
	DDX_Text(pDX, IDC_EDIT_FTP_PATH, m_strFTPPath);
	DDX_Radio(pDX, IDC_RADIO_FTP_PIC, m_nFTPType);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFTPDlg, CDialog)
	//{{AFX_MSG_MAP(CFTPDlg)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFTPDlg message handlers

BOOL CFTPDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	theApp.m_lang.TransDialog(m_hWnd, IDD);
	

	LoadParam();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFTPDlg::LoadParam() 
{
    unsigned int size = 0;
    NS_CA_FTP_INFO_S cfg;
    ZeroMemory(&cfg, sizeof(cfg));
    if(NS_NET_GetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_GET_CA_FTP_INFO, &cfg, &size) != 0)
    {
        AfxMessageBox(_T("Get Alarm FTP Config Failed."));
        return ;
    }
    m_strFTPHost = cfg.host;
    m_strFTPUser = cfg.user;
    m_strFTPPwd = cfg.passwd;
    m_strFTPPath = cfg.path;
    m_nFTPType = cfg.type;

    UpdateData(FALSE);
}

void CFTPDlg::OnBtnSave() 
{
	// TODO: Add your control notification handler code here
    UpdateData();
    NS_CA_FTP_INFO_S cfg;
    unsigned int size = sizeof(cfg);
    ZeroMemory(&cfg, sizeof(cfg));
    strcpy(cfg.host, m_strFTPHost);
    strcpy(cfg.user, m_strFTPUser);
    strcpy(cfg.passwd, m_strFTPPwd);
    strcpy(cfg.path, m_strFTPPath);
    cfg.type = m_nFTPType;
    if(NS_NET_SetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_SET_CA_FTP_INFO, &cfg, size) != 0)
    {
        AfxMessageBox(_T("Set Alarm FTP Config Failed."));
        return ;
    }
    AfxMessageBox(_T("OK"));
}
