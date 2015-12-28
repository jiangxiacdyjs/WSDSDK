// VideoMaskDlg.cpp : implementation file
//

#include "stdafx.h"
#include "netsdk_demo.h"
#include "VideoMaskDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVideoMaskDlg dialog


CVideoMaskDlg::CVideoMaskDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVideoMaskDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVideoMaskDlg)
	m_nBottom = 0;
	m_nLeft = 0;
	m_nRight = 0;
	m_nTop = 0;
	m_bEnable = FALSE;
	m_nColor = 0;

    m_nBottom2 = 0;
    m_nLeft2 = 0;
    m_nRight2 = 0;
    m_nTop2 = 0;
    m_bEnable2 = FALSE;
    m_nColor2 = 0;

    m_nBottom3= 0;
    m_nLeft3 = 0;
    m_nRight3 = 0;
    m_nTop3 = 0;
    m_bEnable3 = FALSE;
    m_nColor3 = 0;

    m_nBottom4 = 0;
    m_nLeft4 = 0;
    m_nRight4 = 0;
    m_nTop4 = 0;
    m_bEnable4 = FALSE;
    m_nColor4 = 0;
    //}}AFX_DATA_INIT
}


void CVideoMaskDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVideoMaskDlg)
	DDX_Text(pDX, IDC_EDIT_BOTTOM, m_nBottom);
	DDX_Text(pDX, IDC_EDIT_LEFT, m_nLeft);
	DDX_Text(pDX, IDC_EDIT_RIGHT, m_nRight);
	DDX_Text(pDX, IDC_EDIT_TOP, m_nTop);
	DDX_Check(pDX, IDC_CHECK_VIDEO_MASK, m_bEnable);
	DDX_Text(pDX, IDC_EDIT_COLOR, m_nColor);
    DDX_Text(pDX, IDC_EDIT_BOTTOM2, m_nBottom2);
    DDX_Text(pDX, IDC_EDIT_LEFT2, m_nLeft2);
    DDX_Text(pDX, IDC_EDIT_RIGHT2, m_nRight2);
    DDX_Text(pDX, IDC_EDIT_TOP2, m_nTop2);
    DDX_Check(pDX, IDC_CHECK_VIDEO_MASK2, m_bEnable2);
    DDX_Text(pDX, IDC_EDIT_COLOR2, m_nColor2);
    DDX_Text(pDX, IDC_EDIT_BOTTOM3, m_nBottom3);
    DDX_Text(pDX, IDC_EDIT_LEFT3, m_nLeft3);
    DDX_Text(pDX, IDC_EDIT_RIGHT3, m_nRight3);
    DDX_Text(pDX, IDC_EDIT_TOP3, m_nTop3);
    DDX_Check(pDX, IDC_CHECK_VIDEO_MASK3, m_bEnable3);
    DDX_Text(pDX, IDC_EDIT_COLOR3, m_nColor3);
    DDX_Text(pDX, IDC_EDIT_BOTTOM4, m_nBottom4);
    DDX_Text(pDX, IDC_EDIT_LEFT4, m_nLeft4);
    DDX_Text(pDX, IDC_EDIT_RIGHT4, m_nRight4);
    DDX_Text(pDX, IDC_EDIT_TOP4, m_nTop4);
    DDX_Check(pDX, IDC_CHECK_VIDEO_MASK4, m_bEnable4);
    DDX_Text(pDX, IDC_EDIT_COLOR4, m_nColor4);
    DDV_MinMaxUInt(pDX, m_nColor, 0, 13);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVideoMaskDlg, CDialog)
	//{{AFX_MSG_MAP(CVideoMaskDlg)
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVideoMaskDlg message handlers

void CVideoMaskDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();

	CDialog::OnOK();
}

void CVideoMaskDlg::OnBnClickedOk()
{
    // TODO: Add your control notification handler code here
    UpdateData();
    NS_VIDEO_MASK_INFO_S cfg;
    unsigned int size = sizeof(NS_VIDEO_MASK_INFO_S);
    ZeroMemory(&cfg, sizeof(cfg));
    cfg.videomasknum = NS_MAX_VIDEO_MASK_NUM;
    cfg.videomasks[0].bottom = m_nBottom;
    cfg.videomasks[0].left = m_nLeft;
    cfg.videomasks[0].right = m_nRight;
    cfg.videomasks[0].top = m_nTop;
    cfg.videomasks[0].masken = m_bEnable;
    cfg.videomasks[0].color = m_nColor;

    cfg.videomasks[1].bottom = m_nBottom2;
    cfg.videomasks[1].left = m_nLeft2;
    cfg.videomasks[1].right = m_nRight2;
    cfg.videomasks[1].top = m_nTop2;
    cfg.videomasks[1].masken = m_bEnable2;
    cfg.videomasks[1].color = m_nColor2;

    cfg.videomasks[2].bottom = m_nBottom3;
    cfg.videomasks[2].left = m_nLeft3;
    cfg.videomasks[2].right = m_nRight3;
    cfg.videomasks[2].top = m_nTop3;
    cfg.videomasks[2].masken = m_bEnable3;
    cfg.videomasks[2].color = m_nColor3;

    cfg.videomasks[3].bottom = m_nBottom4;
    cfg.videomasks[3].left = m_nLeft4;
    cfg.videomasks[3].right = m_nRight4;
    cfg.videomasks[3].top = m_nTop4;
    cfg.videomasks[3].masken = m_bEnable4;
    cfg.videomasks[3].color = m_nColor4;
    cfg.dwSize = sizeof(NS_VIDEO_MASK_INFO_S);
    if(NS_NET_SetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_SET_VIDEO_MASK_INFO, &cfg, size) != 0)
    {
        AfxMessageBox("Set video info mask Failed.");
        return ;
    }
    AfxMessageBox(_T("OK"));
    OnOK();
}

BOOL CVideoMaskDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  Add extra initialization here
	theApp.m_lang.TransDialog(m_hWnd, IDD);
	
    unsigned int size = 0;
    NS_VIDEO_MASK_INFO_S cfg;
    ZeroMemory(&cfg, sizeof(cfg));
    if(NS_NET_GetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_GET_VIDEO_MASK_INFO, &cfg, &size) != 0)
    {
        AfxMessageBox(uistrings[STR_SET_VM_FAIL].strings[g_nLangID]);
        return FALSE;
    }
    m_nBottom = cfg.videomasks[0].bottom;
    m_nLeft = cfg.videomasks[0].left;
    m_nRight = cfg.videomasks[0].right;
    m_nTop = cfg.videomasks[0].top;
    m_bEnable = cfg.videomasks[0].masken;
    m_nColor = cfg.videomasks[0].color;

    m_nBottom2 = cfg.videomasks[1].bottom;
    m_nLeft2 = cfg.videomasks[1].left;
    m_nRight2 = cfg.videomasks[1].right;
    m_nTop2 = cfg.videomasks[1].top;
    m_bEnable2 = cfg.videomasks[1].masken;
    m_nColor2 = cfg.videomasks[1].color;

    m_nBottom3 = cfg.videomasks[2].bottom;
    m_nLeft3 = cfg.videomasks[2].left;
    m_nRight3 = cfg.videomasks[2].right;
    m_nTop3 = cfg.videomasks[2].top;
    m_bEnable3 = cfg.videomasks[2].masken;
    m_nColor3 = cfg.videomasks[2].color;

    m_nBottom4 = cfg.videomasks[3].bottom;
    m_nLeft4 = cfg.videomasks[3].left;
    m_nRight4 = cfg.videomasks[3].right;
    m_nTop4 = cfg.videomasks[3].top;
    m_bEnable4 = cfg.videomasks[3].masken;
    m_nColor4 = cfg.videomasks[3].color;
    UpdateData(FALSE);

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}
