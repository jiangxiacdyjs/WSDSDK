// OSDDlg.cpp : implementation file
//

#include "stdafx.h"
#include "netsdk_demo.h"
#include "OSDDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COSDDlg dialog
COSDDlg::COSDDlg(CWnd* pParent /*=NULL*/,long lNetHandle)
	: CDialog(COSDDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COSDDlg)
	m_strOSDChannel = _T("");
	m_bOSDBps		= FALSE;
	m_bOSDChannel	= FALSE;
	m_bOSDTime		= FALSE;
	m_lBpsLeft = 0;
	m_lBpsTop = 0;
	m_lChnLeft = 0;
	m_lChnTop = 0;
	m_lTimeLeft = 0;
	m_lTimeTop = 0;
	//}}AFX_DATA_INIT
	m_lNetHandle	= lNetHandle;
}

void COSDDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COSDDlg)
	DDX_Text(pDX, IDC_EDIT_CHANNEL, m_strOSDChannel);
	DDX_Check(pDX, IDC_OSD_BPS, m_bOSDBps);
	DDX_Check(pDX, IDC_OSD_CHANNEL, m_bOSDChannel);
	DDX_Check(pDX, IDC_OSD_TIME, m_bOSDTime);
	DDX_Text(pDX, IDC_EDIT_BPS_LEFT, m_lBpsLeft);
	DDX_Text(pDX, IDC_EDIT_BPS_TOP, m_lBpsTop);
	DDX_Text(pDX, IDC_EDIT_CHN_LEFT, m_lChnLeft);
	DDX_Text(pDX, IDC_EDIT_CHN_TOP, m_lChnTop);
	DDX_Text(pDX, IDC_EDIT_TIME_LEFT, m_lTimeLeft);
	DDX_Text(pDX, IDC_EDIT_TIME_TOP, m_lTimeTop);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(COSDDlg, CDialog)
	//{{AFX_MSG_MAP(COSDDlg)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COSDDlg message handlers

BOOL COSDDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	theApp.m_lang.TransDialog(m_hWnd, IDD);
	

    unsigned int size = 0;
    NS_OSD_INFO_S cfg;
    ZeroMemory(&cfg, sizeof(cfg));
    if(NS_NET_GetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_GET_OSD_INFO, &cfg, &size) != 0)
    {
        AfxMessageBox("Get osd info Failed.");
        return FALSE;
    }
    
    m_strOSDChannel = cfg.name;
    m_bOSDChannel = cfg.nameen;
    m_lChnLeft = cfg.nameleft;
    m_lChnTop = cfg.nametop;

    m_bOSDTime = cfg.timeen;
    m_lTimeLeft = cfg.timeleft;
    m_lTimeTop = cfg.timetop;

    m_bOSDBps = cfg.bpsen;
    m_lBpsLeft = cfg.bpsleft;
    m_lBpsTop = cfg.bpstop;
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void COSDDlg::OnBtnSave() 
{
	// TODO: Add your control notification handler code here
	CWaitCursor wait;

	UpdateData();
    NS_OSD_INFO_S cfg;
    unsigned int size = sizeof(cfg);
    ZeroMemory(&cfg, sizeof(cfg));
    strcpy(cfg.name, m_strOSDChannel);
    cfg.nameen = m_bOSDChannel;
    cfg.nameleft = m_lChnLeft;
    cfg.nametop = m_lChnTop;
    
    cfg.timeen = m_bOSDTime;
    cfg.timeleft = m_lTimeLeft;
    cfg.timetop = m_lTimeTop;
    
    cfg.bpsen = m_bOSDBps;
    cfg.bpsleft = m_lBpsLeft;
    cfg.bpstop = m_lBpsTop;
    if(NS_NET_SetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_SET_OSD_INFO, &cfg, size) != 0)
    {
        AfxMessageBox("Set osd info Failed.");
        return ;
    }
    
    AfxMessageBox(_T("OK"));
}
