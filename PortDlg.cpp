// PortDlg.cpp : implementation file
//

#include "stdafx.h"
#include "netsdk_demo.h"
#include "PortDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPortDlg dialog
CPortDlg::CPortDlg(CWnd* pParent /*=NULL*/,long lNetHandle)
	: CDialog(CPortDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPortDlg)
	m_nPortABC		= 8004;
	m_nPortRTSP		= 554;
	m_nPortUpdate	= 8006;
	m_nPortWeb		= 80;
	m_bPPPOEEnable	= FALSE;
	m_strPPPOEUser	= _T("");
	m_strPPPOEPwd	= _T("");
	m_bDDNSOpen		= FALSE;
	m_strDDNSPwd	= _T("");
	m_strDDNSUrl	= _T("");
	m_strDDNSUser	= _T("");
	m_nNicType		= 0;
	m_nFtpPort		= 21;
	m_bUpnpABCOpen	= FALSE;
	m_bUpnpFtpOpen	= FALSE;
	m_bUpnpRtspOpen = FALSE;
	m_bUpnpUpdateOpen = FALSE;
	m_bUpnpWebOpen	= FALSE;
	//}}AFX_DATA_INIT
	m_lNetHandle	= lNetHandle;
}

void CPortDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPortDlg)
	DDX_Control(pDX, IDC_COMBO_DDNS_SUPPORT, m_cmbDDNSSupport);
	DDX_Text(pDX, IDC_EDIT_PORT_ABC, m_nPortABC);
	DDV_MinMaxUInt(pDX, m_nPortABC, 1, 65535);
	DDX_Text(pDX, IDC_EDIT_PORT_RTSP, m_nPortRTSP);
	DDV_MinMaxUInt(pDX, m_nPortRTSP, 1, 65535);
	DDX_Text(pDX, IDC_EDIT_PORT_UPDATE, m_nPortUpdate);
	DDV_MinMaxUInt(pDX, m_nPortUpdate, 1, 65535);
	DDX_Text(pDX, IDC_EDIT_PORT_WEB, m_nPortWeb);
	DDV_MinMaxUInt(pDX, m_nPortWeb, 1, 65535);
	DDX_Check(pDX, IDC_CHECK_PPPOE_ENABLE, m_bPPPOEEnable);
	DDX_Text(pDX, IDC_EDIT_PPPOE_USER, m_strPPPOEUser);
	DDV_MaxChars(pDX, m_strPPPOEUser, 36);
	DDX_Text(pDX, IDC_EDIT_PPPOE_PWD, m_strPPPOEPwd);
	DDV_MaxChars(pDX, m_strPPPOEPwd, 36);
	DDX_Check(pDX, IDC_CHECK_DDNS_OPEN, m_bDDNSOpen);
	DDX_Text(pDX, IDC_EDIT_DDNS_PWD, m_strDDNSPwd);
	DDV_MaxChars(pDX, m_strDDNSPwd, 36);
	DDX_Text(pDX, IDC_EDIT_DDNS_URL, m_strDDNSUrl);
	DDV_MaxChars(pDX, m_strDDNSUrl, 260);
	DDX_Text(pDX, IDC_EDIT_DDNS_USER, m_strDDNSUser);
	DDV_MaxChars(pDX, m_strDDNSUser, 36);
	DDX_Radio(pDX, IDC_RADIO_ETHERNET, m_nNicType);
	DDX_Text(pDX, IDC_EDIT_PORT_FTP, m_nFtpPort);
	DDV_MinMaxUInt(pDX, m_nFtpPort, 1, 65535);
	DDX_Check(pDX, IDC_CHECK_UPNP_OPEN_ABC, m_bUpnpABCOpen);
	DDX_Check(pDX, IDC_CHECK_UPNP_OPEN_FTP, m_bUpnpFtpOpen);
	DDX_Check(pDX, IDC_CHECK_UPNP_OPEN_RTSP, m_bUpnpRtspOpen);
	DDX_Check(pDX, IDC_CHECK_UPNP_OPEN_UPDATE, m_bUpnpUpdateOpen);
	DDX_Check(pDX, IDC_CHECK_UPNP_OPEN_WEB, m_bUpnpWebOpen);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPortDlg, CDialog)
	//{{AFX_MSG_MAP(CPortDlg)
	ON_BN_CLICKED(IDC_BTN_PORT_WRITE, OnBtnPortWrite)
	ON_BN_CLICKED(IDC_BTN_PPPOE_WRITE, OnBtnPppoeWrite)
	ON_BN_CLICKED(IDC_BTN_DDNS_WRITE, OnBtnDdnsWrite)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPortDlg message handlers

BOOL CPortDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	theApp.m_lang.TransDialog(m_hWnd, IDD);
	
	
	ReadPort();	
	ReadPppoe();	
	ReadDdns();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPortDlg::ReadPort()
{
    {
        unsigned int size = 0;
        NS_PORT_INFO_S cfg;
        ZeroMemory(&cfg, sizeof(cfg));
        if(NS_NET_GetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_GET_PORT_INFO, &cfg, &size) != 0)
        {
            AfxMessageBox("Get Port info Failed.");
            return ;
        }
        m_nPortRTSP = cfg.rtsp;
        m_nPortWeb = cfg.web;
        m_nPortABC = cfg.audio;
        m_nPortUpdate = cfg.update;
        m_nFtpPort = cfg.ftp;
    }
    {
        unsigned int size = 0;
        NS_UPNP_INFO_S cfg;
        ZeroMemory(&cfg, sizeof(cfg));
        if(NS_NET_GetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_GET_UPNP_INFO, &cfg, &size) != 0)
        {
            AfxMessageBox("Get upnp info Failed.");
            return ;
        }
        m_bUpnpRtspOpen = cfg.rtspen;
        m_bUpnpWebOpen = cfg.httpen;
        m_bUpnpABCOpen = cfg.voiceen;
        m_bUpnpUpdateOpen = cfg.updateen;
        m_bUpnpFtpOpen = cfg.ftpen;
    }

    UpdateData(FALSE);
}

void CPortDlg::ReadPppoe()
{
    {
        unsigned int size = 0;
        NS_PPPOE_INFO_S cfg;
        ZeroMemory(&cfg, sizeof(cfg));
        if(NS_NET_GetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_GET_PPPOE_INFO, &cfg, &size) != 0)
        {
            AfxMessageBox("Get pppoe info Failed.");
            return ;
        }
        m_nNicType = cfg.nicsel;
        m_bPPPOEEnable = cfg.pppoeen;
        m_strPPPOEUser = cfg.pppoeuser;
        m_strPPPOEPwd = cfg.pppoepasswd;
    }
	UpdateData(FALSE);
}

void CPortDlg::ReadDdns()
{
	CString strDDNSProvider;

    unsigned int size = 0;
    NS_DDNS_INFO_S cfg;
    ZeroMemory(&cfg, sizeof(cfg));
    if(NS_NET_GetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_GET_DDNS_INFO, &cfg, &size) != 0)
    {
        AfxMessageBox("Get ddns info Failed.");
        return ;
    }
    m_bDDNSOpen = cfg.ddnsen;
    m_strDDNSUser = cfg.ddnsuser;
    m_strDDNSPwd = cfg.ddnspasswd;
    m_strDDNSUrl = cfg.ddnsurl;

    if (cfg.ddnsprovider == 0)
    {
        strDDNSProvider = cfg.ddnssupport0;
    }
    else
    {
        strDDNSProvider = cfg.ddnssupport1;
    }

    m_cmbDDNSSupport.ResetContent();
    m_cmbDDNSSupport.AddString(cfg.ddnssupport0);
    m_cmbDDNSSupport.AddString(cfg.ddnssupport1);
 	
 	m_cmbDDNSSupport.SetCurSel(cfg.ddnsprovider);
	
	UpdateData(FALSE);
}

void CPortDlg::OnBtnPortWrite() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
    {
        NS_PORT_INFO_S cfg;
        unsigned int size = sizeof(NS_PORT_INFO_S);
        cfg.dwSize = sizeof(NS_PORT_INFO_S);
        cfg.rtsp = m_nPortRTSP;
        cfg.web = m_nPortWeb;
        cfg.audio = m_nPortABC;
        cfg.update = m_nPortUpdate;
        cfg.ftp = m_nFtpPort;
        if(NS_NET_SetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_SET_PORT_INFO, &cfg, size) != 0)
        {
            AfxMessageBox("Set Port Failed.");
            return ;
        }
    }
    {
        NS_UPNP_INFO_S cfg;
        unsigned int size = sizeof(NS_UPNP_INFO_S);
        cfg.dwSize = sizeof(NS_UPNP_INFO_S);
        cfg.rtspen = m_bUpnpRtspOpen;
        cfg.httpen = m_bUpnpWebOpen;
        cfg.voiceen = m_bUpnpABCOpen;
        cfg.updateen = m_bUpnpUpdateOpen;
        cfg.ftpen = m_bUpnpFtpOpen;
        if(NS_NET_SetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_SET_UPNP_INFO, &cfg, size) != 0)
        {
            AfxMessageBox("Set upnp Failed.");
            return ;
        }
    }
    AfxMessageBox(_T("OK"));
}	

void CPortDlg::OnBtnPppoeWrite() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
    {
        NS_PPPOE_INFO_S cfg;
        unsigned int size = sizeof(NS_UPNP_INFO_S);
        cfg.dwSize = sizeof(NS_UPNP_INFO_S);
        cfg.nicsel = m_nNicType;
        cfg.pppoeen = m_bPPPOEEnable;
        strcpy(cfg.pppoepasswd , m_strPPPOEPwd);
        strcpy(cfg.pppoeuser , m_strPPPOEUser);
        if(NS_NET_SetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_SET_PPPOE_INFO, &cfg, size) != 0)
        {
            AfxMessageBox("Set PPPOE Failed.");
            return ;
        }
    }
    AfxMessageBox(_T("OK"));
}

void CPortDlg::OnBtnDdnsWrite() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	
	CString strDDNSProvider;	
	int nSel = m_cmbDDNSSupport.GetCurSel();
    {
        NS_DDNS_INFO_S cfg;
        unsigned int size = sizeof(NS_DDNS_INFO_S);
        cfg.dwSize = sizeof(NS_DDNS_INFO_S);
        cfg.ddnsen = m_bDDNSOpen;
        cfg.ddnsprovider = nSel;
        strcpy(cfg.ddnsuser , m_strDDNSUser);
        strcpy(cfg.ddnspasswd , m_strDDNSPwd);
        strcpy(cfg.ddnsurl , m_strDDNSUrl);
        if(NS_NET_SetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_SET_DDNS_INFO, &cfg, size) != 0)
        {
            AfxMessageBox("Set PPPOE Failed.");
            return ;
        }
    }
    AfxMessageBox(_T("OK"));
}
