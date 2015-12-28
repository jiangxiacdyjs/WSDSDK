// BallVideoMaskDlg.cpp : implementation file
//

#include "stdafx.h"
#include "netsdk_Demo.h"
#include "BallVideoMaskDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBallVideoMaskDlg dialog


CBallVideoMaskDlg::CBallVideoMaskDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBallVideoMaskDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBallVideoMaskDlg)
	m_nColor = 0;
	m_nHeight = 50;
	m_nIndex = 0;
	m_nWidth = 50;
	//}}AFX_DATA_INIT
}


void CBallVideoMaskDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBallVideoMaskDlg)
	DDX_Text(pDX, IDC_EDIT_COLOR, m_nColor);
	DDV_MinMaxUInt(pDX, m_nColor, 0, 14);
	DDX_Text(pDX, IDC_EDIT_HEIGHT, m_nHeight);
	DDV_MinMaxUInt(pDX, m_nHeight, 1, 60);
	DDX_Text(pDX, IDC_EDIT_INDEX, m_nIndex);
	DDV_MinMaxUInt(pDX, m_nIndex, 0, 3);
	DDX_Text(pDX, IDC_EDIT_WIDTH, m_nWidth);
	DDV_MinMaxUInt(pDX, m_nWidth, 1, 80);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBallVideoMaskDlg, CDialog)
	//{{AFX_MSG_MAP(CBallVideoMaskDlg)
	ON_BN_CLICKED(IDC_BUTTON_SET, OnButtonSet)
	ON_BN_CLICKED(IDC_BUTTON_SHOW, OnButtonShow)
	ON_BN_CLICKED(IDC_BUTTON_HIDE, OnButtonHide)
	ON_BN_CLICKED(IDC_BUTTON_DEL, OnButtonDel)
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BUTTON_SET_COLOR, OnBnClickedButtonSetColor)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBallVideoMaskDlg message handlers

void CBallVideoMaskDlg::OnButtonSet() 
{
	// TODO: Add your control notification handler code here
	if (UpdateData())
	{
        unsigned int size = 0;
        NS_BALL_VIDEO_MASK_S cfg;
        ZeroMemory(&cfg, sizeof(cfg));
        size = sizeof(cfg);
        cfg.dwSize = size;
        cfg.action = NS_BALL_VIDEO_MASK_ACTION_ADD;
        cfg.maskid = (NS_BALL_VIDEO_MASK_ID_E)(m_nIndex+1);
        cfg.maskwidth = m_nWidth;
        cfg.maskheight = m_nHeight;

        if(NS_NET_SetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_SET_BALL_VIDEO_MASK, &cfg, size) != 0)
        {
            AfxMessageBox(uistrings[STR_SET_VM_FAIL].strings[g_nLangID]);
            return ;
        }
        AfxMessageBox(_T("OK"));
	}
}

void CBallVideoMaskDlg::OnButtonShow() 
{
	// TODO: Add your control notification handler code here
	if (UpdateData())
	{
        unsigned int size = 0;
        NS_BALL_VIDEO_MASK_S cfg;
        ZeroMemory(&cfg, sizeof(cfg));
        size = sizeof(cfg);
        cfg.dwSize = size;
        cfg.action = NS_BALL_VIDEO_MASK_ACTION_SHOW;
        cfg.maskid = (NS_BALL_VIDEO_MASK_ID_E)(m_nIndex+1);

        if(NS_NET_SetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_SET_BALL_VIDEO_MASK, &cfg, size) != 0)
        {
            AfxMessageBox(uistrings[STR_SET_VM_FAIL].strings[g_nLangID]);
            return ;
        }
	}
}

void CBallVideoMaskDlg::OnButtonHide() 
{
	// TODO: Add your control notification handler code here
	if (UpdateData())
	{
        unsigned int size = 0;
        NS_BALL_VIDEO_MASK_S cfg;
        ZeroMemory(&cfg, sizeof(cfg));
        size = sizeof(cfg);
        cfg.dwSize = size;
        cfg.action = NS_BALL_VIDEO_MASK_ACTION_HIDE;
        cfg.maskid = (NS_BALL_VIDEO_MASK_ID_E)(m_nIndex+1);

        if(NS_NET_SetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_SET_BALL_VIDEO_MASK, &cfg, size) != 0)
        {
            AfxMessageBox(uistrings[STR_SET_VM_FAIL].strings[g_nLangID]);
            return ;
        }
        AfxMessageBox(_T("OK"));
	}
}

void CBallVideoMaskDlg::OnButtonDel() 
{
	// TODO: Add your control notification handler code here
	if (UpdateData())
	{
        unsigned int size = 0;
        NS_BALL_VIDEO_MASK_S cfg;
        ZeroMemory(&cfg, sizeof(cfg));
        size = sizeof(cfg);
        cfg.dwSize = size;
        cfg.action = NS_BALL_VIDEO_MASK_ACTION_DEL;
        cfg.maskid = (NS_BALL_VIDEO_MASK_ID_E)(m_nIndex+1);

        if(NS_NET_SetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_SET_BALL_VIDEO_MASK, &cfg, size) != 0)
        {
            AfxMessageBox(uistrings[STR_SET_VM_FAIL].strings[g_nLangID]);
            return ;
        }
        AfxMessageBox(_T("OK"));
	}
}

void CBallVideoMaskDlg::OnBnClickedButtonSetColor()
{
    // TODO: Add your control notification handler code here
    if (UpdateData())
    {
        unsigned int size = 0;
        NS_BALL_VIDEO_MASK_S cfg;
        ZeroMemory(&cfg, sizeof(cfg));
        size = sizeof(cfg);
        cfg.dwSize = size;
        cfg.action = NS_BALL_VIDEO_MASK_ACTION_SET_COLOR;
        cfg.maskcolor = (NS_VIDEO_MASK_COLOR_E)(m_nColor+1);

        if(NS_NET_SetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_SET_BALL_VIDEO_MASK, &cfg, size) != 0)
        {
            AfxMessageBox(uistrings[STR_FAIL].strings[g_nLangID]);
            return ;
        }
        AfxMessageBox(_T("OK"));
    }
}

BOOL CBallVideoMaskDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	theApp.m_lang.TransDialog(m_hWnd, IDD);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
