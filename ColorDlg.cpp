// ColorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "netsdk_demo.h"
#include "ColorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorDlg dialog
CColorDlg::CColorDlg(CWnd* pParent /*=NULL*/,long lNetHandle)
	: CDialog(CColorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CColorDlg)
	m_nLampFrequency = 1;
	//}}AFX_DATA_INIT
	m_lNetHandle	= lNetHandle;

	m_nDefBright	= 0;
	m_nDefHue		= 0;
	m_nDefCon		= 0;
	m_nDefSat		= 0;
}

void CColorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CColorDlg)
	DDX_Control(pDX, IDC_SLIDER_GAIN, m_sldGain);
	DDX_Control(pDX, IDC_SLIDER_SAT, m_sldSat);
	DDX_Control(pDX, IDC_SLIDER_HUE, m_sldHue);
	DDX_Control(pDX, IDC_SLIDER_CON, m_sldCon);
	DDX_Control(pDX, IDC_SLIDER_BRI, m_sldBri);
	DDX_Radio(pDX, IDC_RADIO_FREQUENCY_60, m_nLampFrequency);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CColorDlg, CDialog)
	//{{AFX_MSG_MAP(CColorDlg)
	ON_BN_CLICKED(IDC_BTN_WRITE, OnBtnWrite)
	ON_BN_CLICKED(IDC_BTN_DEF, OnBtnDef)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorDlg message handlers

BOOL CColorDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	theApp.m_lang.TransDialog(m_hWnd, IDD);
	InitSld();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CColorDlg::InitSld()
{
	m_sldHue.SetRange(0,255);
	m_sldHue.SetLineSize(1);
	
	m_sldCon.SetRange(0,255);
	m_sldCon.SetLineSize(1);
	
	m_sldBri.SetRange(0,255);
	m_sldBri.SetLineSize(1);
	
	m_sldSat.SetRange(0,255);
	m_sldSat.SetLineSize(1);

	m_sldGain.SetRange(0,255);
	m_sldGain.SetLineSize(1);
	

    unsigned int size = 0;
    NS_COLOR_INFO_S cfg;
    ZeroMemory(&cfg, sizeof(cfg));
    if(NS_NET_GetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_GET_COLOR_INFO, &cfg, &size) != 0)
    {
        AfxMessageBox("Get bps Failed.");
        return ;
    }
    
	m_sldBri.SetPos(cfg.bright);
	m_sldCon.SetPos(cfg.contrast);
	m_sldSat.SetPos(cfg.saturation);
	m_sldHue.SetPos(cfg.hue);
	m_sldGain.SetPos(cfg.gain);

	m_nLampFrequency = cfg.lampfrequency;
	UpdateData(FALSE);
}

void CColorDlg::OnBtnWrite() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	
	UINT nBrightness = m_sldBri.GetPos();
	UINT nContrast = m_sldCon.GetPos();
	UINT nSaturation = m_sldSat.GetPos();
	UINT nHue = m_sldHue.GetPos();
	UINT nGain = m_sldGain.GetPos();
	
    unsigned int size = 0;
    NS_COLOR_INFO_S cfg;
    ZeroMemory(&cfg, sizeof(cfg));
    cfg.bright = nBrightness;
    cfg.contrast = nContrast;
    cfg.hue = nHue;
    cfg.saturation = nSaturation;
    cfg.gain = nGain;
	cfg.lampfrequency = m_nLampFrequency;
    if(NS_NET_SetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_SET_COLOR_INFO, &cfg, size) != 0)
    {
        AfxMessageBox("Set bps Failed.");
        return ;
    }
    AfxMessageBox(_T("OK"));
}

void CColorDlg::OnBtnDef() 
{
	// TODO: Add your control notification handler code here
    unsigned int size = 0;
    NS_COLOR_INFO_S cfg;
    ZeroMemory(&cfg, sizeof(cfg));
    cfg.bright = 128;
    cfg.contrast = 128;
    cfg.hue = 128;
    cfg.saturation = 128;
    cfg.gain = 128;
	cfg.lampfrequency = 1;
    if(NS_NET_SetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_SET_COLOR_INFO, &cfg, size) != 0)
    {
        AfxMessageBox("Set bps Failed.");
        return ;
    }

	m_sldBri.SetPos(128);	
	m_sldCon.SetPos(128);	
	m_sldHue.SetPos(128);	
	m_sldSat.SetPos(128);
	m_sldGain.SetPos(128);
	
	AfxMessageBox("Set Video Color Success.");

	m_nLampFrequency = 1;
	UpdateData(FALSE);
}
