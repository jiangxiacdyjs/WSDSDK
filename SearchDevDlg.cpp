// SearchDevDlg.cpp : implementation file
//

#include "stdafx.h"
#include "netsdk_demo.h"
#include "SearchDevDlg.h"

#define WM_FOUND_DEV WM_USER + 202
#define TIMER_SEARCH 202
// CSearchDevDlg dialog

IMPLEMENT_DYNAMIC(CSearchDevDlg, CDialog)

CSearchDevDlg::CSearchDevDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSearchDevDlg::IDD, pParent)
{

}

CSearchDevDlg::~CSearchDevDlg()
{
}

void CSearchDevDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_DEV, m_listDev);
}


BEGIN_MESSAGE_MAP(CSearchDevDlg, CDialog)
    ON_WM_CLOSE()
	ON_WM_TIMER()
    ON_BN_CLICKED(IDOK, OnBnClickedOk)
    ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_MESSAGE(WM_FOUND_DEV, OnFoundDev)
END_MESSAGE_MAP()


// CSearchDevDlg message handlers
void OnSearchDevice(const NS_SEARCH_DEV_INFO_S * pDev, PVOID pUserData)
{
    TRACE("ËÑË÷µ½Éè±¸ %s\n", pDev->ip);
    CSearchDevDlg * pThis = (CSearchDevDlg *)pUserData;
    if (pThis)
    {
        pThis->PostMessage(WM_FOUND_DEV,(WPARAM)(new CString(pDev->ip)), 0);
    }
}

int CSearchDevDlg::AddDevice(CString strDevIP)
{
    BOOL bNew = TRUE;
    if (m_devices.find(strDevIP) != m_devices.end())
    {
        bNew = FALSE;
    }
    m_devices[strDevIP] = strDevIP;

    if (bNew && (strDevIP.GetLength() > 0) )
    {
        m_listDev.AddString(strDevIP);
    }
    return 0;
}

BOOL CSearchDevDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  Add extra initialization here
	theApp.m_lang.TransDialog(m_hWnd, IDD);
	
    NS_NET_StartSearchDevice(OnSearchDevice, this);
	SetTimer(TIMER_SEARCH, 5000, 0);
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CSearchDevDlg::OnClose()
{
    // TODO: Add your message handler code here and/or call default
    NS_NET_StopSearchDevice();
	KillTimer(TIMER_SEARCH);
    CDialog::OnClose();
}

void CSearchDevDlg::OnBnClickedOk()
{
    // TODO: Add your control notification handler code here
    NS_NET_StopSearchDevice();
    OnOK();
}

void CSearchDevDlg::OnBnClickedCancel()
{
    // TODO: Add your control notification handler code here
    NS_NET_StopSearchDevice();
    OnCancel();
}

void CSearchDevDlg::OnTimer(UINT_PTR nIDEvent)
{
    // TODO: Add your message handler code here and/or call default
    if (nIDEvent == TIMER_SEARCH)
    {
		NS_NET_StopSearchDevice();
		NS_NET_StartSearchDevice(OnSearchDevice, this);
    }
	
    CDialog::OnTimer(nIDEvent);
}

LRESULT CSearchDevDlg::OnFoundDev(WPARAM wp,LPARAM lp)
{
	CString * pDevIP = (CString *)wp;
	AddDevice(*pDevIP);
	delete ((CString *)wp);
	return 0;
}

