// ComDlg.cpp : implementation file
//

#include "stdafx.h"
#include "netsdk_demo.h"
#include "ComDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CComDlg dialog
CComDlg::CComDlg(CWnd* pParent /*=NULL*/,long lNetHandle)
	: CDialog(CComDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CComDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_lNetHandle	= lNetHandle;

	m_nCom	= 0;
	m_nStop	= 0;
	m_nData	= 0;
	m_nAddr	= 0;
	m_nBaud = 0;
	m_strCheckBit.Empty();
	m_strProt.Empty();
}

void CComDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CComDlg)
	DDX_Control(pDX, IDC_COMBO_PTZ, m_cmbPTZ);
	DDX_Control(pDX, IDC_EDIT_PTZADDRESS, m_editPTZAddress);
	DDX_Control(pDX, IDC_COMBO_CHECKBIT, m_cmbCheckBit);
	DDX_Control(pDX, IDC_COMBO_STOPBITS, m_cmbStopBits);
	DDX_Control(pDX, IDC_COMBO_DATABITS, m_cmbDataBits);
	DDX_Control(pDX, IDC_COMBO_BITRATE, m_cmbBitrate);
	DDX_Control(pDX, IDC_COMBO_COM, m_cmbCom);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CComDlg, CDialog)
	//{{AFX_MSG_MAP(CComDlg)
	ON_BN_CLICKED(IDC_BTN_COMSAVE, OnBtnComsave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComDlg message handlers

BOOL CComDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	theApp.m_lang.TransDialog(m_hWnd, IDD);

	char pszCheck[MAX_PATH];
	memset(pszCheck,0,MAX_PATH);

	char pszProt[MAX_PATH];
	memset(pszProt,0,MAX_PATH);

    unsigned int size = 0;
    NS_PTZ_INFO_S cfg;
    ZeroMemory(&cfg, sizeof(cfg));
    if(NS_NET_GetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_GET_PTZ_INFO, &cfg, &size) != 0)
    {
        AfxMessageBox("Get ptz info Failed.");
        return FALSE;
    }
    
	{
        m_cmbCheckBit.SetCurSel(cfg.parity);
        m_nCom = cfg.type;
        m_nBaud = cfg.baud;
        m_nData = cfg.data;
        m_nStop = cfg.stop;
        m_nAddr = cfg.addr;
		m_strProt = cfg.protocol;
		
		for(int nIndex = 0; nIndex < cfg.protocolCount; nIndex ++)
		{
			m_emVectorPTZ.push_back(cfg.protocols[nIndex]);
		}	

		UpdateControls();
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CComDlg::UpdateControls()
{
    CString strCmb;
    
    m_cmbCom.SetCurSel(m_nCom);
    
    strCmb.Format("%d",m_nBaud);
    m_cmbBitrate.SelectString(0,strCmb);
    
    strCmb.Format("%d",m_nData);
    m_cmbDataBits.SelectString(0,strCmb);
    
    strCmb.Format("%d",m_nStop);
    m_cmbStopBits.SelectString(0,strCmb);
    
    
    strCmb.Format("%d",m_nAddr);
    m_editPTZAddress.SetWindowText(strCmb);
    
    m_cmbPTZ.ResetContent();
    
    int nIndex = 0;
    for(; nIndex < m_emVectorPTZ.size(); nIndex ++)
    {	
        strCmb = m_emVectorPTZ.at(nIndex).c_str();
        m_cmbPTZ.AddString(strCmb);
    }
    
    nIndex = m_cmbPTZ.FindStringExact(0, m_strProt);
    m_cmbPTZ.SetCurSel(nIndex);
    
}

void CComDlg::OnBtnComsave() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	
	CString strPTZAddress;
	m_editPTZAddress.GetWindowText(strPTZAddress);
	
	int nPTZAddress = atoi(strPTZAddress);
	if(strPTZAddress.IsEmpty() || nPTZAddress < 0 || nPTZAddress > 255)
	{
		AfxMessageBox("Invalid PTZ Address");
		return;
	}
	
	CString strPTZProtocol;
	m_cmbPTZ.GetWindowText(strPTZProtocol);
	
	int nProtocolLen = strPTZProtocol.GetLength();
	if(nProtocolLen == 0 || nProtocolLen > 30)
	{
		AfxMessageBox("Invalid PTZ Protocol");
		return;
	}

	m_nCom		= m_cmbCom.GetCurSel();
	m_nStop		= m_cmbStopBits.GetCurSel() + 1;
	m_nData		= m_cmbDataBits.GetCurSel() + 5;
	
	m_cmbCheckBit.GetLBText(m_cmbCheckBit.GetCurSel(),m_strCheckBit);
	m_strCheckBit  = m_strCheckBit.Left(1);
	
	CString strBaud;
	m_cmbBitrate.GetLBText(m_cmbBitrate.GetCurSel(),strBaud);
	
	m_nBaud     = atoi(strBaud);
	m_nAddr		= nPTZAddress;
	m_strProt	= strPTZProtocol;
	
    NS_PTZ_INFO_S cfg;
    ZeroMemory(&cfg, sizeof(cfg));
    unsigned int size = sizeof(cfg);
    cfg.dwSize = size;
    cfg.type = m_nCom;
    cfg.stop = m_nStop;
    cfg.data = m_nData;
    cfg.parity = m_cmbCheckBit.GetCurSel();
    cfg.baud = m_nBaud;
    cfg.addr = m_nAddr;
    strcpy(cfg.protocol , strPTZProtocol);
    if(NS_NET_SetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_SET_PTZ_INFO, &cfg, size) != 0)
    {
        AfxMessageBox("Set ptz Failed.");
        return ;
    }
    else
    {
        AfxMessageBox("Set ptz Info Success");
    }
}


