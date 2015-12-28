// AudioDlg.cpp : implementation file
//

#include "stdafx.h"
#include "netsdk_Demo.h"
#include "AudioDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAudioDlg dialog
CAudioDlg::CAudioDlg(CWnd* pParent /*=NULL*/,long lNetHandle)
	: CDialog(CAudioDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAudioDlg)
	m_bEnable	= FALSE;
	m_nCodec	= -1;
	//}}AFX_DATA_INIT
	m_lNetHandle	= lNetHandle;
}

void CAudioDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAudioDlg)
	DDX_Control(pDX, IDC_SLIDER_OUTPUT, m_sldOutput);
	DDX_Control(pDX, IDC_SLIDER_INPUT, m_sldInput);
	DDX_Check(pDX, IDC_CHECK_AUDIO_IN, m_bEnable);
	DDX_Radio(pDX, IDC_RADIO_AR_G711U, m_nCodec);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAudioDlg, CDialog)
	//{{AFX_MSG_MAP(CAudioDlg)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_CHECK_AUDIO_IN, OnCheckAudioIn)
	ON_BN_CLICKED(IDC_RADIO_AR_G711U, OnRadioCodec)
	ON_BN_CLICKED(IDC_RADIO_AR_AMRNB, OnRadioCodec)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAudioDlg message handlers

BOOL CAudioDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	theApp.m_lang.TransDialog(m_hWnd, IDD);
	InitSld();
	LoadParam();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAudioDlg::InitSld()
{
	m_sldInput.SetRange(0,100);
	m_sldOutput.SetRange(0,100);
}

BOOL CAudioDlg::LoadParam()
{
    unsigned int size = 0;
    NS_AUDIO_INFO_S cfg;
    ZeroMemory(&cfg, sizeof(cfg));
    if(NS_NET_GetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_GET_AUDIO_INFO, &cfg, &size) != 0)
    {
        AfxMessageBox(_T("Get audio info Failed."));
        return FALSE;
    }
 	UINT nVolInput = cfg.nVolumeInput;
    UINT nVolOutput = cfg.nVolumeOutput;
    m_bEnable = cfg.bEnable;
 	
 	m_sldInput.SetPos(nVolInput);
 	m_sldOutput.SetPos(nVolOutput);
 	
 	SetDlgItemInt(IDC_STATIC_VOL_INPUT,nVolInput);
 	SetDlgItemInt(IDC_STATIC_VOL_OUTPUT,nVolOutput);
 	
	if (cfg.emArCodecType == NS_AUDIO_CODEC_FORMAT_G711A)
	{
		m_nCodec = 0;
	}
	else if (cfg.emArCodecType == NS_AUDIO_CODEC_FORMAT_G711U)
	{
		m_nCodec = 1;
	}
	else
	{
 		m_nCodec = 2;
	}
	 
	UpdateData(FALSE);

	return TRUE;
}

BOOL CAudioDlg::SaveParam()
{
	UINT nVolInput	= m_sldInput.GetPos();
	UINT nVolOutput	= m_sldOutput.GetPos();
	
    unsigned int size = 0;
    NS_AUDIO_INFO_S cfg;
    ZeroMemory(&cfg, sizeof(cfg));
    size = sizeof(NS_AUDIO_INFO_S);
    cfg.dwSize = size;
    cfg.nVolumeInput = nVolInput;
    cfg.nVolumeOutput = nVolOutput;
    cfg.bEnable = m_bEnable;

	if (m_nCodec == 0)
	{
		cfg.emArCodecType = NS_AUDIO_CODEC_FORMAT_G711A;
	}
	else if (m_nCodec == 1)
	{
		cfg.emArCodecType = NS_AUDIO_CODEC_FORMAT_G711U;
	}
	else
	{
		cfg.emArCodecType = NS_AUDIO_CODEC_FORMAT_AMRNB;
	}
	
    if(NS_NET_SetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_SET_AUDIO_INFO, &cfg, size) != 0)
    {
        AfxMessageBox(_T("Set audio info Failed."));
        return FALSE;
    }

    SetDlgItemInt(IDC_STATIC_VOL_INPUT,nVolInput);
	SetDlgItemInt(IDC_STATIC_VOL_OUTPUT,nVolOutput);
	
    AfxMessageBox(_T("Set audio info OK."));
	return TRUE;
}

void CAudioDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	if(pScrollBar)
	{
		UINT nID = pScrollBar->GetDlgCtrlID();
		if((nID == IDC_SLIDER_OUTPUT) || (nID == IDC_SLIDER_INPUT))
		{		
			switch(nSBCode)                        // 按是哪一种操作进行处理
			{  
				case SB_LINELEFT:
					break;
				case SB_LINERIGHT:
					break;                  
				case SB_THUMBPOSITION:                //拖动滑动块（不允许拖动）
					break;
				case SB_ENDSCROLL: 
					return;
                }      
			TRACE("%d, %d\n", nSBCode, nPos);
			SaveParam();
		}
	}
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

// 启用音频输入
void CAudioDlg::OnCheckAudioIn() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	
    SaveParam();
}

// 音频编码
void CAudioDlg::OnRadioCodec() 
{
	// TODO: Add your control notification handler code here
	UpdateData();

    SaveParam();
}

