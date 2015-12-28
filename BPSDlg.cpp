// BPSDlg.cpp : implementation file
//

#include "stdafx.h"
#include "netsdk_Demo.h"
#include "BPSDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBPSDlg dialog
CBPSDlg::CBPSDlg(CWnd* pParent /*=NULL*/,long lNetHandle)
	: CDialog(CBPSDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBPSDlg)
		// NOTE: the ClassWizard will add member initialization here
	m_nPicture			= 0;
	m_nVBR				= 0;
	m_nBitRate			= 0;
	m_nFrameRate		= 0;
	m_nIFrameInterval	= 0;
	m_nMaxBitRate		= 0;
	//}}AFX_DATA_INIT
	m_lNetHandle	= lNetHandle;
}

void CBPSDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBPSDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Radio(pDX, IDC_RADIO_PICTURE, m_nPicture);
	DDX_Radio(pDX, IDC_RADIO_VBR, m_nVBR);
	DDX_Text(pDX, IDC_EDIT_BITRATE, m_nBitRate);
	DDX_Text(pDX, IDC_EDIT_FRAMERATE, m_nFrameRate);
	DDX_Text(pDX, IDC_EDIT_IINTERVAL, m_nIFrameInterval);
	DDX_Text(pDX, IDC_EDIT_BITRATE_MAX, m_nMaxBitRate);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBPSDlg, CDialog)
	//{{AFX_MSG_MAP(CBPSDlg)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBPSDlg message handlers
BOOL CBPSDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	theApp.m_lang.TransDialog(m_hWnd, IDD);

    unsigned int size = 0;
    ZeroMemory(&m_cfg, sizeof(m_cfg));
    if(NS_NET_GetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_GET_BPS_INFO, &m_cfg, &size) != 0)
    {
        AfxMessageBox("Get bps Failed.");
        return FALSE;
    }
    
    m_nBitRate = m_cfg.bps.bps;
    m_nMaxBitRate = m_cfg.bps.maxbps;
    m_nVBR = m_cfg.bps.brmode;
    m_nPicture = m_cfg.bps.preferfps;
    m_nFrameRate = m_cfg.bps.fps;
    m_nIFrameInterval = m_cfg.bps.gop;

	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CBPSDlg::OnBtnSave() 
{
	// TODO: Add your control notification handler code here

	UpdateData();
    unsigned int size = sizeof(m_cfg);
    m_cfg.dwSize = size;
    m_cfg.bps.bps = m_nBitRate;
    m_cfg.bps.maxbps = m_nMaxBitRate;
    m_cfg.bps.brmode = m_nVBR;
    m_cfg.bps.preferfps = m_nPicture;
    m_cfg.bps.fps = m_nFrameRate;
    m_cfg.bps.gop = m_nIFrameInterval;
    if(NS_NET_SetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_SET_BPS_INFO, &m_cfg, size) != 0)
    {
        AfxMessageBox("Set bps Failed.");
        return ;
    }
	else
	{
		AfxMessageBox("Set BPS Info Success");
	}
}
