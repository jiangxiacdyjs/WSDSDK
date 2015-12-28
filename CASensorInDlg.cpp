// CASensorInDlg.cpp : implementation file
//

#include "stdafx.h"
#include "netsdk_Demo.h"
#include "CASensorInDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCASensorInDlg dialog
CCASensorInDlg::CCASensorInDlg(CWnd* pParent /*=NULL*/,long lNetHandle)
	: CDialog(CCASensorInDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCASensorInDlg)
	m_nSensorIn		= 0;
	m_bACEn			= FALSE;
	m_bEmailEn		= FALSE;
	m_bFTPEn		= FALSE;
	m_bRecordEn		= FALSE;
	m_bSensorOut1En = FALSE;
	m_bSensorOut2En = FALSE;
	m_bSoundEn		= FALSE;
	m_nInterval		= 30;
	m_bSnapEn		= FALSE;
	//}}AFX_DATA_INIT
	m_lNetHandle	= lNetHandle;
}

void CCASensorInDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCASensorInDlg)
	DDX_Radio(pDX, IDC_RADIO_SENSOR_IN_1, m_nSensorIn);
	DDX_Check(pDX, IDC_CHECK_AC, m_bACEn);
	DDX_Check(pDX, IDC_CHECK_EMAIL, m_bEmailEn);
	DDX_Check(pDX, IDC_CHECK_FTP, m_bFTPEn);
	DDX_Check(pDX, IDC_CHECK_RECORD, m_bRecordEn);
	DDX_Check(pDX, IDC_CHECK_SENSOR1, m_bSensorOut1En);
	DDX_Check(pDX, IDC_CHECK_SENSOR2, m_bSensorOut2En);
	DDX_Check(pDX, IDC_CHECK_SOUND, m_bSoundEn);
	DDX_Text(pDX, IDC_EDIT_INTERVAL, m_nInterval);
	DDV_MinMaxUInt(pDX, m_nInterval, 5, 36000);
	DDX_Check(pDX, IDC_CHECK_SNAP, m_bSnapEn);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCASensorInDlg, CDialog)
	//{{AFX_MSG_MAP(CCASensorInDlg)
	ON_BN_CLICKED(IDC_RADIO_SENSOR_IN_1, OnRadioSensorIn)
	ON_BN_CLICKED(IDC_RADIO_SENSOR_IN_2, OnRadioSensorIn)
	ON_BN_CLICKED(IDC_RADIO_SENSOR_IN_3, OnRadioSensorIn)
	ON_BN_CLICKED(IDC_RADIO_SENSOR_IN_4, OnRadioSensorIn)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCASensorInDlg message handlers

BOOL CCASensorInDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	theApp.m_lang.TransDialog(m_hWnd, IDD);
	
	LoadParam();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCASensorInDlg::LoadParam() 
{
	// TODO: Add your control notification handler code here
    unsigned int size = 0;
    NS_CA_AI_INFO_S cfg;
    ZeroMemory(&cfg, sizeof(cfg));
    cfg.id = m_nSensorIn;
    if(NS_NET_GetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_GET_CA_AI_INFO, &cfg, &size) != 0)
    {
        AfxMessageBox(_T("Get Alarm sensor in Config Failed."));
        return ;
    }
    m_bACEn = cfg.acen;
    m_bEmailEn = cfg.emailen;
    m_bRecordEn = cfg.recorden;
    m_bFTPEn = cfg.ftpen;
    m_bSensorOut1En = cfg.ao0en;
    m_bSensorOut2En = cfg.ao1en;
    m_bSoundEn = cfg.sounden;
    m_bSnapEn = cfg.captureen;
    m_nInterval = cfg.interval;
	UpdateData(FALSE);
}

void CCASensorInDlg::OnRadioSensorIn() 
{
	// TODO: Add your control notification handler code here
	UpdateData();

	LoadParam() ;
}

void CCASensorInDlg::OnBtnSave() 
{
    UpdateData();
    NS_CA_AI_INFO_S cfg;
    unsigned int size = sizeof(cfg);
    ZeroMemory(&cfg, sizeof(cfg));
    cfg.id = m_nSensorIn;
    cfg.acen = m_bACEn;
    cfg.emailen = m_bEmailEn;
    cfg.recorden = m_bRecordEn;
    cfg.ftpen = m_bFTPEn;
    cfg.ao0en = m_bSensorOut1En;
    cfg.ao1en = m_bSensorOut2En;
    cfg.sounden = m_bSoundEn;
    cfg.captureen = m_bSnapEn;
    cfg.interval = m_nInterval;
    if(NS_NET_SetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_SET_CA_AI_INFO, &cfg, size) != 0)
    {
        AfxMessageBox(_T("Set Alarm sensor in Config Failed."));
        return ;
    }
    AfxMessageBox(_T("OK"));
}
