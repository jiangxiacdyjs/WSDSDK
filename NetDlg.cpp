// NetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "netsdk_demo.h"
#include "NetDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNetDlg dialog
CNetDlg::CNetDlg(CWnd* pParent /*=NULL*/,long lNetHandle)
	: CDialog(CNetDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNetDlg)
		// NOTE: the ClassWizard will add member initialization here
	m_strDNS			= _T("");
	m_strGateWay		= _T("");
	m_strIP				= _T("");
	m_strSubMask		= _T("");
	m_bDHCP				= FALSE;
	m_strMac			= _T("");
	m_bWifiDHCP			= FALSE;
	m_bWifiEnable		= FALSE;
	m_strWifiIP			= _T("");
	m_strWifiMask		= _T("");
	m_strWifiMac		= _T("");
	m_strWifiGateWay	= _T("");
	m_strWifiSSID		= _T("");
	m_bWifiSecEn		= FALSE;
	m_strWifiWepPass	= _T("");
	m_bWifiExist		= FALSE;
	m_strWifiName		= _T("");
	//}}AFX_DATA_INIT
	m_lNetHandle		= lNetHandle;
}

void CNetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNetDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDC_LIST_WIFI_AP, m_listWifiAP);
	DDX_Control(pDX, IDC_COMBO_WIFI_WEPTYPE, m_cmbWifiWepType);
	DDX_Control(pDX, IDC_COMBO_WIFI_WEPINDEX, m_cmbWifiWepIndex);
	DDX_Control(pDX, IDC_COMBO_WIFI_WEPOPT, m_cmbWifiWepOpt);
	DDX_Control(pDX, IDC_COMBO_WIFI_SECTYPE, m_cmbWifiSecType);
	DDX_Text(pDX, IDC_EDIT_DNS, m_strDNS);
	DDV_MaxChars(pDX, m_strDNS, 260);
	DDX_Text(pDX, IDC_EDIT_GATEWAY, m_strGateWay);
	DDV_MaxChars(pDX, m_strGateWay, 260);
	DDX_Text(pDX, IDC_EDIT_IP, m_strIP);
	DDV_MaxChars(pDX, m_strIP, 260);
	DDX_Text(pDX, IDC_EDIT_SUBMASK, m_strSubMask);
	DDV_MaxChars(pDX, m_strSubMask, 260);
	DDX_Check(pDX, IDC_CHECK_DHCP, m_bDHCP);
	DDX_Text(pDX, IDC_EDIT_MAC, m_strMac);
	DDV_MaxChars(pDX, m_strMac, 260);
	DDX_Check(pDX, IDC_CHECK_WIFI_DHCP, m_bWifiDHCP);
	DDX_Check(pDX, IDC_CHECK_WIFI_ENABLE, m_bWifiEnable);
	DDX_Text(pDX, IDC_EDIT_WIFI_IP, m_strWifiIP);
	DDV_MaxChars(pDX, m_strWifiIP, 260);
	DDX_Text(pDX, IDC_EDIT_WIFI_MASK, m_strWifiMask);
	DDV_MaxChars(pDX, m_strWifiMask, 260);
	DDX_Text(pDX, IDC_EDIT_WIFI_MAC, m_strWifiMac);
	DDV_MaxChars(pDX, m_strWifiMac, 260);
	DDX_Text(pDX, IDC_EDIT_WIFI_GATEWAY, m_strWifiGateWay);
	DDV_MaxChars(pDX, m_strWifiGateWay, 260);
	DDX_Text(pDX, IDC_EDIT_WIFI_SSID, m_strWifiSSID);
	DDV_MaxChars(pDX, m_strWifiSSID, 260);
	DDX_Check(pDX, IDC_CHECK_WIFI_SECEN, m_bWifiSecEn);
	DDX_Text(pDX, IDC_EDIT_WIFI_WEPPWD, m_strWifiWepPass);
	DDV_MaxChars(pDX, m_strWifiWepPass, 260);
	DDX_Check(pDX, IDC_CHECK_WIFI_EXIST, m_bWifiExist);
	DDX_Text(pDX, IDC_EDIT_WIFI_NAME, m_strWifiName);
	DDV_MaxChars(pDX, m_strWifiName, 260);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CNetDlg, CDialog)
	//{{AFX_MSG_MAP(CNetDlg)
	ON_BN_CLICKED(IDC_BTN_WRITE, OnBtnWrite)
	ON_BN_CLICKED(IDC_BTN_WIFI_WRITE, OnBtnWifiWrite)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetDlg message handlers

BOOL CNetDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	theApp.m_lang.TransDialog(m_hWnd, IDD);
	

	InitWifiAPList();
	ReadNet();
	ReadWifi();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CNetDlg::InitWifiAPList()
{
	m_listWifiAP.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	
	CString strCol;
	int nFmt = LVCFMT_CENTER;
	int iSub = 0;
	
	m_listWifiAP.InsertColumn(iSub ++,"SSID",LVCFMT_RIGHT,200);	
	m_listWifiAP.InsertColumn(iSub ++,"Encry",nFmt,50);
}

void CNetDlg::ReadNet() 
{
	// TODO: Add your control notification handler code here
    unsigned int size = 0;
    NS_ETHER_NET_INFO_S cfg;
    ZeroMemory(&cfg, sizeof(cfg));
    if(NS_NET_GetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_GET_ETHER_NET_INFO, &cfg, &size) != 0)
    {
        AfxMessageBox("Get Net info Failed.");
        return ;
    }

    m_strIP = cfg.ethip;
    m_strMac = cfg.ethmac;
    m_strSubMask = cfg.ethmask;
    m_strGateWay = cfg.ethgw;
    m_strDNS = cfg.dns;

	UpdateData(FALSE);
}


void CNetDlg::OnBtnWrite() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	
    NS_ETHER_NET_INFO_S cfg;
    unsigned int size = sizeof(cfg);
    ZeroMemory(&cfg, sizeof(cfg));
    
    cfg.dwSize = size;
    strcpy(cfg.ethip , m_strIP);
    strcpy(cfg.ethmac , m_strMac);
    strcpy(cfg.ethmask , m_strSubMask);
    strcpy(cfg.ethgw , m_strGateWay);
    strcpy(cfg.dns , m_strDNS);
    if(NS_NET_SetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_SET_ETHER_NET_INFO, &cfg, size) != 0)
    {
        AfxMessageBox("Set Net info Failed.");
        return ;
    }
    AfxMessageBox(_T("OK"));
}

void CNetDlg::ReadWifi() 
{
	// TODO: Add your control notification handler code here
	CString strWifiWepType;

	UINT nWifiSecType  = 0;
	UINT nWifiWepOpt   = 0;
	UINT nWifiWepIndex = 0;
	UINT nWifiWepType  = 0;
	
    unsigned int size = 0;
    NS_WIFI_INFO_S cfg;
    ZeroMemory(&cfg, sizeof(cfg));
    if(NS_NET_GetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_GET_WIFI_INFO, &cfg, &size) != 0)
    {
        AfxMessageBox("Get wifi info Failed.");
        return ;
    }
    m_bWifiExist = cfg.wifiexist;
    m_strWifiName = cfg.wifiname;
    m_bWifiEnable = cfg.wifien;
    m_strWifiMac = cfg.wifimac;
    m_strWifiGateWay = cfg.wifigw;
    m_strWifiSSID = cfg.wifissid;
    m_bWifiSecEn = cfg.wifisecen;
    nWifiSecType = cfg.wifisectype;
    nWifiWepOpt = 0;
    nWifiWepType = cfg.wifiweptype;
    nWifiWepIndex = cfg.wifiwepindex;
    m_strWifiWepPass = cfg.wifiweppass;

	m_listWifiAP.DeleteAllItems();
	
	m_cmbWifiWepOpt.SetCurSel(nWifiWepOpt);
	m_cmbWifiWepIndex.SetCurSel(nWifiWepIndex);
	m_cmbWifiSecType.SetCurSel(nWifiSecType);
	m_cmbWifiWepType.SetCurSel(nWifiWepType);
	
	UpdateData(FALSE);
}

void CNetDlg::OnBtnWifiWrite() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	
	CString strWifiWepType;
	UINT nWifiSecType  = 0;
	UINT nWifiWepOpt   = 0;
	UINT nWifiWepIndex = 0;
	UINT nWifiWepType  = 0;
	
	nWifiSecType = m_cmbWifiSecType.GetCurSel();
	nWifiWepOpt  = m_cmbWifiWepOpt.GetCurSel();
	nWifiWepIndex = m_cmbWifiWepIndex.GetCurSel();
	nWifiWepType = m_cmbWifiWepType.GetCurSel();

    NS_WIFI_INFO_S cfg;
    unsigned int size = sizeof(cfg);
    ZeroMemory(&cfg, sizeof(cfg));
    
    cfg.dwSize = size;
    cfg.wifiexist = m_bWifiExist;
    cfg.wifien = m_bWifiEnable;
    cfg.wifisecen = m_bWifiSecEn;
    cfg.wifisectype = nWifiSecType;
    cfg.wifiweptype = nWifiWepType;
    cfg.wifiwepindex = nWifiWepIndex;
    strcpy(cfg.wifiname , m_strWifiName);
    strcpy(cfg.wifimac , m_strWifiMac);
    strcpy(cfg.wifigw , m_strWifiGateWay);
    strcpy(cfg.wifissid , m_strWifiSSID);
    strcpy(cfg.wifiweppass , m_strWifiWepPass);
    if(NS_NET_SetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_SET_WIFI_INFO, &cfg, size) != 0)
    {
        AfxMessageBox("Set Net info Failed.");
        return ;
    }
}
