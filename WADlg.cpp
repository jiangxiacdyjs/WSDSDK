// WADlg.cpp : implementation file
//

#include "stdafx.h"
#include "netsdk_demo.h"
#include "WADlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWADlg dialog


CWADlg::CWADlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWADlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWADlg)
	m_agc = 0;
	m_brightness = 0;
	m_contrast = 0;
	m_sharpness = 0;
	m_saturation = 0;
	m_focusstatus = 0;
	m_shuttermode = 0;
	m_shutterspeed = 0;
	m_iris = 0;
	m_gain = 0;
	m_content = _T("");
	m_index = 0;
	m_left = 0;
	m_top = 0;
	m_multiple = 0.0;
	//}}AFX_DATA_INIT
}


void CWADlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWADlg)
	DDX_Text(pDX, IDC_EDIT_AGC, m_agc);
	DDX_Text(pDX, IDC_EDIT_BRIGHTNESS, m_brightness);
	DDX_Text(pDX, IDC_EDIT_CONTRAST, m_contrast);
	DDX_Text(pDX, IDC_EDIT_SHARPNESS, m_sharpness);
	DDX_Text(pDX, IDC_EDIT_SATURATION, m_saturation);
	DDX_Text(pDX, IDC_EDIT_FOCUS_STATUS, m_focusstatus);
	DDX_Text(pDX, IDC_EDIT_SHUTTER_MODE, m_shuttermode);
	DDV_MinMaxUInt(pDX, m_shuttermode, 0, 7);
	DDX_Text(pDX, IDC_EDIT_SHUTTER_SPEED, m_shutterspeed);
	DDX_Text(pDX, IDC_EDIT_GAIN, m_iris);
	DDX_Text(pDX, IDC_EDIT_IRIS, m_gain);
	DDX_Text(pDX, IDC_EDIT_CONTENT, m_content);
	DDV_MaxChars(pDX, m_content, 32);
	DDX_Text(pDX, IDC_EDIT_INDEX, m_index);
	DDV_MinMaxUInt(pDX, m_index, 0, 7);
	DDX_Text(pDX, IDC_EDIT_LEFT, m_left);
	DDX_Text(pDX, IDC_EDIT_TOP, m_top);
	DDX_Text(pDX, IDC_EDIT_MULTIPLE, m_multiple);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWADlg, CDialog)
	//{{AFX_MSG_MAP(CWADlg)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_SET_DEFAULT, OnButtonSetDefault)
	ON_BN_CLICKED(IDC_BUTTON_SET_SHUTTER_MODE, OnButtonSetShutterMode)
	ON_BN_CLICKED(IDC_BUTTON_SET_SHUTTER_SPEED, OnButtonSetShutterSpeed)
	ON_BN_CLICKED(IDC_BUTTON_SET_NORTH, OnButtonSetNorth)
	ON_BN_CLICKED(IDC_BUTTON_SHOW_ANGLE, OnButtonShowAngle)
	ON_BN_CLICKED(IDC_BUTTON_SHOW, OnButtonShow)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWADlg message handlers

BOOL CWADlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	theApp.m_lang.TransDialog(m_hWnd, IDD);

	{
		unsigned int size = 0;
		NS_WA_IMAGE_PARAM_S cfg;
		ZeroMemory(&cfg, sizeof(cfg));
		if(NS_NET_GetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_GET_WA_IMAGE_PARAM, &cfg, &size) != 0)
		{
			return FALSE;
		}
		m_brightness	= cfg.brightness;
		m_contrast		= cfg.contrast;
		m_saturation	= cfg.saturation;
		m_sharpness		= cfg.sharpness;
		m_agc			= cfg.agc;
		m_shuttermode	= cfg.shuttermode;
		m_shutterspeed  = cfg.shutterspeed;
		m_iris			= cfg.iris;
		m_gain			= cfg.gain;
	}

	{
		unsigned int size = 0;
		NS_WA_IMAGE_PARAM_S cfg;
		ZeroMemory(&cfg, sizeof(cfg));
		if(NS_NET_GetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_GET_WA_FOCUS_STATUS, &cfg, &size) != 0)
		{
			return FALSE;
		}
		m_focusstatus	= cfg.focusstatus;
	}

	{
		unsigned int size = 0;
		NS_WA_CAMERA_INFO_S cfg;
		ZeroMemory(&cfg, sizeof(cfg));
		if(NS_NET_GetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_GET_WA_CAMERA_INFO, &cfg, &size) != 0)
		{
			return FALSE;
		}
		m_multiple	= cfg.multiple;
	}
    UpdateData(FALSE);
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CWADlg::OnButtonSave() 
{
	// TODO: Add your control notification handler code here
	if (UpdateData())
	{
		unsigned int size = sizeof(NS_WA_IMAGE_PARAM_S);
		NS_WA_IMAGE_PARAM_S cfg;
		ZeroMemory(&cfg, sizeof(cfg));
		cfg.dwSize	= size;
		cfg.brightness	= m_brightness;
		cfg.contrast	= m_contrast;
		cfg.saturation	= m_saturation;
		cfg.sharpness	= m_sharpness;
		cfg.agc			= m_agc;
		if(NS_NET_SetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_SET_WA_IMAGE_PARAM, &cfg, size) != 0)
		{
			AfxMessageBox(uistrings[STR_FAIL].strings[g_nLangID]);
			return;
		}

		AfxMessageBox("OK");
	}
}

void CWADlg::OnButtonSetDefault() 
{
	// TODO: Add your control notification handler code here
	{
		unsigned int size = sizeof(NS_WA_IMAGE_PARAM_S);
		NS_WA_IMAGE_PARAM_S cfg;
		ZeroMemory(&cfg, sizeof(cfg));
		cfg.dwSize	= size;
		if(NS_NET_SetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_SET_WA_IMAGE_PARAM_DEFAULT, &cfg, size) != 0)
		{
			AfxMessageBox(uistrings[STR_FAIL].strings[g_nLangID]);
			return;
		}
		
		AfxMessageBox("OK");
	}
}

void CWADlg::OnButtonSetShutterMode() 
{
	// TODO: Add your control notification handler code here
	/*
		0.设置AE自动模式
		shuttermode = 0
		1.设置快门优先模式
		shuttermode = 1（shutterspeed参数有效）
		2.AE光圈优先模式
		shuttermode = 2（iris参数有效）
		3.保留
		4.保留
		5.AE全手动模式 
		shuttermode = 5（shutterspeed， iris，gain参数有效）
		6.设置自动聚焦模式
		shuttermode = 6
		7.设置手动聚焦模式
		shuttermode = 7
	*/
	if (UpdateData())
	{
		unsigned int size = sizeof(NS_WA_IMAGE_PARAM_S);
		NS_WA_IMAGE_PARAM_S cfg;
		ZeroMemory(&cfg, sizeof(cfg));
		cfg.dwSize	= size;
		cfg.shuttermode		= m_shuttermode;
		cfg.shutterspeed	= m_shutterspeed;
		cfg.iris			= m_iris;
		cfg.gain			= m_gain;
		if(NS_NET_SetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_SET_WA_SHUTTER_MODE, &cfg, size) != 0)
		{
			AfxMessageBox(uistrings[STR_FAIL].strings[g_nLangID]);
			return;
		}
		
		AfxMessageBox("OK");
	}
}

void CWADlg::OnButtonSetShutterSpeed() 
{
	// TODO: Add your control notification handler code here
	if (UpdateData())
	{
		unsigned int size = sizeof(NS_WA_IMAGE_PARAM_S);
		NS_WA_IMAGE_PARAM_S cfg;
		ZeroMemory(&cfg, sizeof(cfg));
		cfg.dwSize	= size;
		cfg.shutterspeed = m_shutterspeed;
		if(NS_NET_SetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_SET_WA_SHUTTER_SPEED, &cfg, size) != 0)
		{
			AfxMessageBox(uistrings[STR_FAIL].strings[g_nLangID]);
			return;
		}
		
		AfxMessageBox("OK");
	}
}

void CWADlg::OnButtonSetNorth() 
{
	// TODO: Add your control notification handler code here
	{
		unsigned int size = sizeof(NS_WA_IMAGE_PARAM_S);
		NS_WA_IMAGE_PARAM_S cfg;
		ZeroMemory(&cfg, sizeof(cfg));
		cfg.dwSize	= size;
		if(NS_NET_SetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_SET_WA_NORTH, &cfg, size) != 0)
		{
			AfxMessageBox(uistrings[STR_FAIL].strings[g_nLangID]);
			return;
		}
		
		AfxMessageBox("OK");
	}
}

void CWADlg::OnButtonShowAngle() 
{
	// TODO: Add your control notification handler code here
	{
		unsigned int size = sizeof(NS_WA_IMAGE_PARAM_S);
		NS_WA_IMAGE_PARAM_S cfg;
		ZeroMemory(&cfg, sizeof(cfg));
		cfg.dwSize	= size;
 		cfg.showangle = TRUE;
//		cfg.showangle = FALSE;
		if(NS_NET_SetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_SET_WA_SHOW_ANGLE, &cfg, size) != 0)
		{
			AfxMessageBox(uistrings[STR_FAIL].strings[g_nLangID]);
			return;
		}
		
		AfxMessageBox("OK");
	}
}

void CWADlg::OnButtonShow() 
{
	// TODO: Add your control notification handler code here
	if (UpdateData())
	{
		unsigned int size = sizeof(NS_WA_OSD_INFO_S);
		NS_WA_OSD_INFO_S cfg;
		ZeroMemory(&cfg, sizeof(cfg));
		cfg.dwSize	= size;
		cfg.show	= TRUE;
		cfg.index	= m_index;
		cfg.left	= m_left;
		cfg.top		= m_top;
		strcpy(cfg.content, m_content);
		if(NS_NET_SetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_SET_WA_OSD_INFO, &cfg, size) != 0)
		{
			AfxMessageBox(uistrings[STR_FAIL].strings[g_nLangID]);
			return;
		}
		
		AfxMessageBox("OK");
	}
}
