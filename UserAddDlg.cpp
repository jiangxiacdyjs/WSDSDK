// UserAddDlg.cpp : implementation file
//

#include "stdafx.h"
#include "netsdk_demo.h"
#include "UserAddDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUserAddDlg dialog
CUserAddDlg::CUserAddDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUserAddDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUserAddDlg)
	m_strPassword	= _T("");
	m_strUser		= _T("");
	m_nGroup		= 0;
	//}}AFX_DATA_INIT
	m_bAddMode		= TRUE;
}

void CUserAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUserAddDlg)
	DDX_Text(pDX, IDC_EDIT_PWD, m_strPassword);
	DDV_MaxChars(pDX, m_strPassword, 63);
	DDX_Text(pDX, IDC_EDIT_USER, m_strUser);
	DDV_MaxChars(pDX, m_strUser, 63);
	DDX_Radio(pDX, IDC_RADIO_ALL, m_nGroup);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CUserAddDlg, CDialog)
	//{{AFX_MSG_MAP(CUserAddDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUserAddDlg message handlers

BOOL CUserAddDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	theApp.m_lang.TransDialog(m_hWnd, IDD);
	
	
	GetDlgItem(IDC_EDIT_USER)->EnableWindow(m_bAddMode);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CUserAddDlg::SetUser(CString strUser,CString strPassword,NS_USER_GROUP_E emPower)
{
	m_strUser = strUser;
	m_strPassword = strPassword;
	m_nGroup  = (UINT)emPower;
}

void CUserAddDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
	
	CDialog::OnOK();
}
