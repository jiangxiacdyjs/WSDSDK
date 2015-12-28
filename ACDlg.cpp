// ACDlg.cpp : implementation file
//

#include "stdafx.h"
#include "netsdk_demo.h"
#include "ACDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CACDlg dialog
CACDlg::CACDlg(CWnd* pParent /*=NULL*/,long lNetHandle)
	: CDialog(CACDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CACDlg)
	m_strAddr		= _T("");
	m_nPort			= 0;
	//}}AFX_DATA_INIT
	m_lNetHandle	= lNetHandle;
}

void CACDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CACDlg)
	DDX_Text(pDX, IDC_EDIT_ADDR, m_strAddr);
	DDX_Text(pDX, IDC_EDIT_PORT, m_nPort);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CACDlg, CDialog)
	//{{AFX_MSG_MAP(CACDlg)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CACDlg message handlers

BOOL CACDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	theApp.m_lang.TransDialog(m_hWnd, IDD);
	
	LoadParam();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CACDlg::LoadParam() 
{
	// TODO: Add your control notification handler code here
    unsigned int size = 0;
    NS_CA_CENTER_INFO_S cfg;
    ZeroMemory(&cfg, sizeof(cfg));
    if(NS_NET_GetServerConfig(m_lNetHandle,g_strChannel,  NS_CMD_GET_CA_CENTER_INFO, &cfg, &size) != 0)
    {
        AfxMessageBox(_T("Get Alarm Center Config Failed."));
        return ;
    }
    m_nPort = cfg.acport;
    m_strAddr = cfg.achost;

	UpdateData(FALSE);
}

void CACDlg::OnBtnSave() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
    NS_CA_CENTER_INFO_S cfg;
    unsigned int size = sizeof(cfg);
    ZeroMemory(&cfg, sizeof(cfg));
    cfg.acport = m_nPort;
    strcpy(cfg.achost, m_strAddr);
    if(NS_NET_SetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_SET_CA_CENTER_INFO, &cfg, size) != 0)
    {
        AfxMessageBox(_T("Set Alarm Center Config Failed."));
        return ;
    }
    AfxMessageBox(_T("Set Alarm Center Config OK."));
}
