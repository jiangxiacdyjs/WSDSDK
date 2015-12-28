// SensorOutDlg.cpp : implementation file
//

#include "stdafx.h"
#include "netsdk_demo.h"
#include "SensorOutDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSensorOutDlg dialog
CSensorOutDlg::CSensorOutDlg(CWnd* pParent /*=NULL*/,long lNetHandle)
	: CDialog(CSensorOutDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSensorOutDlg)
	m_bSensorOut1	= FALSE;
	m_bSensorOut2	= FALSE;
	m_nHoldTime		= 10;
	//}}AFX_DATA_INIT
	m_lNetHandle	= lNetHandle;
}

void CSensorOutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSensorOutDlg)
	DDX_Check(pDX, IDC_CHECK_SENSOR_OUT_1, m_bSensorOut1);
	DDX_Check(pDX, IDC_CHECK_SENSOR_OUT_2, m_bSensorOut2);
	DDX_Text(pDX, IDC_EDIT_HOLDTIME, m_nHoldTime);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSensorOutDlg, CDialog)
	//{{AFX_MSG_MAP(CSensorOutDlg)add
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSensorOutDlg message handlers
BOOL CSensorOutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	theApp.m_lang.TransDialog(m_hWnd, IDD);
	
	
	LoadParam();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSensorOutDlg::LoadParam() 
{
	// TODO: Add your control notification handler code here
    unsigned int size = 0;
    NS_CA_AO_INFO_S cfg;
    ZeroMemory(&cfg, sizeof(cfg));
    if(NS_NET_GetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_GET_CA_AO_INFO, &cfg, &size) != 0)
    {
        AfxMessageBox(_T("Get Alarm sensor out Config Failed."));
        return ;
    }
    m_bSensorOut1 = cfg.ao0;
    m_bSensorOut2 = cfg.ao1;
    m_nHoldTime = cfg.holdtime;

    UpdateData(FALSE);
}

void CSensorOutDlg::OnBtnSave() 
{
    UpdateData();
    NS_CA_AO_INFO_S cfg;
    unsigned int size = sizeof(cfg);
    ZeroMemory(&cfg, sizeof(cfg));
    cfg.ao0 = m_bSensorOut1;
    cfg.ao1 = m_bSensorOut2;
    cfg.holdtime = m_nHoldTime;
    if(NS_NET_SetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_SET_CA_AO_INFO, &cfg, size) != 0)
    {
        AfxMessageBox(_T("Set Alarm sensor out Config Failed."));
        return ;
    }
    AfxMessageBox(_T("OK"));
}
