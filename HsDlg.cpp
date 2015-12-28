// HsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "netsdk_demo.h"
#include "HsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHsDlg dialog
CHsDlg::CHsDlg(CWnd* pParent /*=NULL*/,long lNetHandle)
	: CDialog(CHsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHsDlg)
	m_bMdStart		= FALSE;
	m_bMdStop		= FALSE;
	m_bVlStart		= FALSE;
	m_bVlResume		= FALSE;
	m_nMaxAlarmIn	= 0;
	m_nMaxAlarmOut	= 0;
	m_strAcAddr		= _T("");
	m_nAcPort		= 0;
	m_strDevId		= _T("");
	m_strDevName	= _T("");
	m_strServerAddr = _T("");
	m_nServerPort	= 0;
	//}}AFX_DATA_INIT
	m_lNetHandle	= lNetHandle;
}

void CHsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHsDlg)
	DDX_Check(pDX, IDC_CHECK_MD_START, m_bMdStart);
	DDX_Check(pDX, IDC_CHECK_MD_STOP, m_bMdStop);
	DDX_Check(pDX, IDC_CHECK_VL_START, m_bVlStart);
	DDX_Check(pDX, IDC_CHECK_VL_STOP, m_bVlResume);
	DDX_Text(pDX, IDC_EDIT_AI_MAX, m_nMaxAlarmIn);
	DDX_Text(pDX, IDC_EDIT_AO_MAX, m_nMaxAlarmOut);
	DDX_Text(pDX, IDC_EDIT_DEV_AC_ADDR, m_strAcAddr);
	DDX_Text(pDX, IDC_EDIT_DEV_AC_PORT, m_nAcPort);
	DDX_Text(pDX, IDC_EDIT_DEV_ID, m_strDevId);
	DDX_Text(pDX, IDC_EDIT_DEV_NAME, m_strDevName);
	DDX_Text(pDX, IDC_EDIT_DEV_SERVER_ADDR, m_strServerAddr);
	DDX_Text(pDX, IDC_EDIT_DEV_SERVER_PORT, m_nServerPort);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CHsDlg, CDialog)
	//{{AFX_MSG_MAP(CHsDlg)
	ON_BN_CLICKED(IDC_BTN_READ, OnBtnRead)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHsDlg message handlers

BOOL CHsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	theApp.m_lang.TransDialog(m_hWnd, IDD);
	
	LoadParam();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CHsDlg::LoadParam() 
{
	// TODO: Add your control notification handler code here
// 	if( NP_GetHSRegCfg(	(char*)m_strDevId.GetBuffer(_MAX_PATH),
// 						(char*)m_strDevName.GetBuffer(_MAX_PATH),
// 						(char*)m_strServerAddr.GetBuffer(_MAX_PATH),
// 						(long*)&m_nServerPort,
// 						(char*)m_strAcAddr.GetBuffer(_MAX_PATH),
// 						(long*)&m_nAcPort,
// 						(long*)&m_nMaxAlarmIn,
// 						(long*)&m_nMaxAlarmOut, 
// 						(long*)&m_bMdStart,
// 						(long*)&m_bMdStop,
// 						(long*)&m_bVlStart,
// 						(long*)&m_bVlResume,
// 						m_lNetHandle  ) != 0 )
// 	{
// 		AfxMessageBox(_T("Get Hs Config Failed."));
// 	}
	
	UpdateData(FALSE);
}

void CHsDlg::OnBtnRead() 
{
	// TODO: Add your control notification handler code here
	LoadParam();
	
}

void CHsDlg::OnBtnSave() 
{
	// TODO: Add your control notification handler code here
	UpdateData();

// 	long lRes = NP_SetHSRegCfg(	(char*)m_strDevId.GetBuffer(_MAX_PATH),
// 						(char*)m_strDevName.GetBuffer(_MAX_PATH),
// 						(char*)m_strServerAddr.GetBuffer(_MAX_PATH),
// 						m_nServerPort,
// 						(char*)m_strAcAddr.GetBuffer(_MAX_PATH),
// 						m_nAcPort,
// 						m_nMaxAlarmIn,
// 						m_nMaxAlarmOut, 
// 						m_bMdStart,
// 						m_bMdStop,
// 						m_bVlStart,
// 						m_bVlResume,
// 						m_lNetHandle  );
// 
// 	AfxMessageBox((lRes == 0) ? "Set Hs Config Success..." : "Set Hs Config Failed.");
}
