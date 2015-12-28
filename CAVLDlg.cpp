// CAVLDlg.cpp : implementation file
//

#include "stdafx.h"
#include "netsdk_demo.h"
#include "CAVLDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCAVLDlg dialog
CCAVLDlg::CCAVLDlg(CWnd* pParent /*=NULL*/,long lNetHandle)
	: CDialog(CCAVLDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCAVLDlg)
	m_bACEn			= FALSE;
	m_bEmailEn		= FALSE;
	m_bSensorOut1En = FALSE;
	m_bSensorOut2En = FALSE;
	m_bSoundEn		= FALSE;
	m_nInterval		= 30;
	//}}AFX_DATA_INIT
	m_lNetHandle	= lNetHandle;
	
}

void CCAVLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCAVLDlg)
	DDX_Check(pDX, IDC_CHECK_AC, m_bACEn);
	DDX_Check(pDX, IDC_CHECK_EMAIL, m_bEmailEn);
	DDX_Check(pDX, IDC_CHECK_SENSOR1, m_bSensorOut1En);
	DDX_Check(pDX, IDC_CHECK_SENSOR2, m_bSensorOut2En);
	DDX_Check(pDX, IDC_CHECK_SOUND, m_bSoundEn);
	DDX_Text(pDX, IDC_EDIT_INTERVAL, m_nInterval);
	DDV_MinMaxUInt(pDX, m_nInterval, 5, 36000);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCAVLDlg, CDialog)
	//{{AFX_MSG_MAP(CCAVLDlg)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCAVLDlg message handlers

BOOL CCAVLDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	theApp.m_lang.TransDialog(m_hWnd, IDD);
	
	LoadParam();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCAVLDlg::LoadParam() 
{
	// TODO: Add your control notification handler code here
    unsigned int size = 0;
    NS_CA_VL_INFO_S cfg;
    ZeroMemory(&cfg, sizeof(cfg));
    if(NS_NET_GetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_GET_CA_VL_INFO, &cfg, &size) != 0)
    {
        AfxMessageBox(_T("Get Alarm video loss Config Failed."));
        return ;
    }
    m_bACEn = cfg.acen;
    m_bEmailEn = cfg.emailen;
    m_bSensorOut1En = cfg.ao0en;
    m_bSensorOut2En = cfg.ao1en;
    m_bSoundEn = cfg.sounden;
    m_nInterval = cfg.interval;
	
	UpdateData(FALSE);
}

void CCAVLDlg::OnBtnSave() 
{
    UpdateData();
    NS_CA_VL_INFO_S cfg;
    unsigned int size = sizeof(cfg);
    ZeroMemory(&cfg, sizeof(cfg));
    cfg.acen = m_bACEn;
    cfg.emailen = m_bEmailEn;
    cfg.ao0en = m_bSensorOut1En;
    cfg.ao1en = m_bSensorOut2En;
    cfg.sounden = m_bSoundEn;
    cfg.interval = m_nInterval;
    if(NS_NET_SetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_SET_CA_VL_INFO, &cfg, size) != 0)
    {
        AfxMessageBox(_T("Set Alarm video loss Config Failed."));
        return ;
    }
    AfxMessageBox(_T("OK"));
}
