// EncryptStrDlg.cpp : implementation file
//

#include "stdafx.h"
#include "netsdk_demo.h"
#include "EncryptStrDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEncryptStrDlg dialog


CEncryptStrDlg::CEncryptStrDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEncryptStrDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEncryptStrDlg)
	m_str = _T("");
	m_id = 1;
	//}}AFX_DATA_INIT
}


void CEncryptStrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEncryptStrDlg)
	DDX_Text(pDX, IDC_EDIT_ENCRYPT_STR, m_str);
	DDV_MaxChars(pDX, m_str, 32);
	DDX_Text(pDX, IDC_EDIT_ID, m_id);
	DDV_MinMaxUInt(pDX, m_id, 1, 8);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEncryptStrDlg, CDialog)
	//{{AFX_MSG_MAP(CEncryptStrDlg)
	ON_BN_CLICKED(IDC_BTN_READ, OnBtnRead)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEncryptStrDlg message handlers

void CEncryptStrDlg::OnBtnRead() 
{
	// TODO: Add your control notification handler code here
	if (UpdateData())
	{
		unsigned int size = 0;
		NS_ENCRYPT_STR_S cfg;
		ZeroMemory(&cfg, sizeof(cfg));
		cfg.id = m_id;
		if(NS_NET_GetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_GET_ENCRYPT_STR, &cfg, &size) != 0)
		{
			AfxMessageBox("Get encrypt str failed.");
			return ;
		}
		m_str= cfg.str;
		
		UpdateData(FALSE);
	}
}

void CEncryptStrDlg::OnBtnSave() 
{
	// TODO: Add your control notification handler code here
	if (UpdateData())
	{
		unsigned int size = sizeof(NS_ENCRYPT_STR_S);
		NS_ENCRYPT_STR_S cfg;
		ZeroMemory(&cfg, sizeof(cfg));
		cfg.id = m_id;
		strcpy(cfg.str, m_str);
		if(NS_NET_SetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_SET_ENCRYPT_STR, &cfg, size) != 0)
		{ 
			AfxMessageBox("Set encrypt str failed.");
			return ;
		}
		AfxMessageBox("OK");
	}
}

BOOL CEncryptStrDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
