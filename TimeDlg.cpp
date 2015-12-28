// TimeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "netsdk_demo.h"
#include "TimeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTimeDlg dialog
CTimeDlg::CTimeDlg(CWnd* pParent /*=NULL*/,long lNetHandle)
	: CDialog(CTimeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTimeDlg)
		// NOTE: the ClassWizard will add member initialization here
	m_bNTPEnable	= FALSE;
	m_strNTPServer	= _T("");
	//}}AFX_DATA_INIT
	m_lNetHandle	= lNetHandle;
}

void CTimeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTimeDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDC_DATETIMEPICKER, m_DateTime);
	DDX_Control(pDX, IDC_COMBO_TIMEZONE, m_cmdTimeZone);
	DDX_Check(pDX, IDC_CHECK_NTP_ENABLE, m_bNTPEnable);
	DDX_Text(pDX, IDC_EDIT_NTP_SERVER, m_strNTPServer);
	DDV_MaxChars(pDX, m_strNTPServer, 260);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTimeDlg, CDialog)
	//{{AFX_MSG_MAP(CTimeDlg)
	ON_BN_CLICKED(IDC_BNT_WRITE, OnBntWrite)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTimeDlg message handlers

BOOL CTimeDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	theApp.m_lang.TransDialog(m_hWnd, IDD);
	
	
	FillTimeZone();
	UpdateTimeCtrl();

    unsigned int size = 0;
    NS_TIME_INFO_S cfg;
    ZeroMemory(&cfg, sizeof(cfg));
    if(NS_NET_GetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_GET_TIME_INFO, &cfg, &size) != 0)
    {
        AfxMessageBox("Get time info Failed.");
        return FALSE;
    }
    m_bNTPEnable= cfg.ntpen;
    m_strNTPServer = cfg.ntphost;
    m_cmdTimeZone.SetCurSel(cfg.timezone);
	
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CTimeDlg::FillTimeZone()
{
	m_cmdTimeZone.AddString(uistrings[STR_TIME_ZONE_1].strings[g_nLangID]);
	m_cmdTimeZone.AddString(uistrings[STR_TIME_ZONE_2].strings[g_nLangID]);
	m_cmdTimeZone.AddString(uistrings[STR_TIME_ZONE_3].strings[g_nLangID]);
	m_cmdTimeZone.AddString(uistrings[STR_TIME_ZONE_4].strings[g_nLangID]);
	m_cmdTimeZone.AddString(uistrings[STR_TIME_ZONE_5].strings[g_nLangID]);
	m_cmdTimeZone.AddString(uistrings[STR_TIME_ZONE_6].strings[g_nLangID]);
	m_cmdTimeZone.AddString(uistrings[STR_TIME_ZONE_7].strings[g_nLangID]);
	m_cmdTimeZone.AddString(uistrings[STR_TIME_ZONE_8].strings[g_nLangID]);
	m_cmdTimeZone.AddString(uistrings[STR_TIME_ZONE_9].strings[g_nLangID]);
	m_cmdTimeZone.AddString(uistrings[STR_TIME_ZONE_10].strings[g_nLangID]);
	m_cmdTimeZone.AddString(uistrings[STR_TIME_ZONE_11].strings[g_nLangID]);
	m_cmdTimeZone.AddString(uistrings[STR_TIME_ZONE_12].strings[g_nLangID]);
	m_cmdTimeZone.AddString(uistrings[STR_TIME_ZONE_13].strings[g_nLangID]);
	m_cmdTimeZone.AddString(uistrings[STR_TIME_ZONE_14].strings[g_nLangID]);
	m_cmdTimeZone.AddString(uistrings[STR_TIME_ZONE_15].strings[g_nLangID]);
	m_cmdTimeZone.AddString(uistrings[STR_TIME_ZONE_16].strings[g_nLangID]);	
    m_cmdTimeZone.AddString(uistrings[STR_TIME_ZONE_17].strings[g_nLangID]);
	m_cmdTimeZone.AddString(uistrings[STR_TIME_ZONE_18].strings[g_nLangID]);
	m_cmdTimeZone.AddString(uistrings[STR_TIME_ZONE_19].strings[g_nLangID]);
    m_cmdTimeZone.AddString(uistrings[STR_TIME_ZONE_20].strings[g_nLangID]);
	m_cmdTimeZone.AddString(uistrings[STR_TIME_ZONE_21].strings[g_nLangID]);
	m_cmdTimeZone.AddString(uistrings[STR_TIME_ZONE_22].strings[g_nLangID]);
    m_cmdTimeZone.AddString(uistrings[STR_TIME_ZONE_23].strings[g_nLangID]);
	m_cmdTimeZone.AddString(uistrings[STR_TIME_ZONE_24].strings[g_nLangID]);
    m_cmdTimeZone.AddString(uistrings[STR_TIME_ZONE_25].strings[g_nLangID]);
	m_cmdTimeZone.AddString(uistrings[STR_TIME_ZONE_26].strings[g_nLangID]);
	m_cmdTimeZone.AddString(uistrings[STR_TIME_ZONE_27].strings[g_nLangID]);
	m_cmdTimeZone.AddString(uistrings[STR_TIME_ZONE_28].strings[g_nLangID]);
	m_cmdTimeZone.AddString(uistrings[STR_TIME_ZONE_29].strings[g_nLangID]);
	m_cmdTimeZone.AddString(uistrings[STR_TIME_ZONE_30].strings[g_nLangID]);
	m_cmdTimeZone.AddString(uistrings[STR_TIME_ZONE_31].strings[g_nLangID]);
	m_cmdTimeZone.AddString(uistrings[STR_TIME_ZONE_32].strings[g_nLangID]);
	m_cmdTimeZone.AddString(uistrings[STR_TIME_ZONE_33].strings[g_nLangID]);
	m_cmdTimeZone.AddString(uistrings[STR_TIME_ZONE_34].strings[g_nLangID]);
	m_cmdTimeZone.AddString(uistrings[STR_TIME_ZONE_35].strings[g_nLangID]);
}
void CTimeDlg::UpdateTimeCtrl()
{
	CTime tmNow;
	tmNow = CTime::GetCurrentTime();
	m_DateTime.SetTime(&tmNow);
}

void CTimeDlg::OnBntWrite() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
    {
        NS_TIME_INFO_S cfg;
        ZeroMemory(&cfg, sizeof(NS_TIME_INFO_S));
        unsigned int size = sizeof(NS_TIME_INFO_S);
        cfg.dwSize = sizeof(NS_TIME_INFO_S);
        cfg.ntpen = m_bNTPEnable;
        cfg.ntpport = 123;
        cfg.interval = 6;
        strcpy(cfg.ntphost, m_strNTPServer);
        cfg.timezone = m_cmdTimeZone.GetCurSel();

        CTime tmNVS;
        m_DateTime.GetTime(tmNVS);
        cfg.time = (DWORD)tmNVS.GetTime();
        if(NS_NET_SetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_SET_TIME_INFO, &cfg, size) != 0)
        {
            AfxMessageBox("Set time Failed.");
            return ;
        }
    }
    AfxMessageBox(_T("OK"));
}
