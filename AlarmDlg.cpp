// AlarmDlg.cpp : implementation file
//

#include "stdafx.h"
#include "netsdk_Demo.h"
#include "AlarmDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAlarmDlg dialog
CAlarmDlg::CAlarmDlg(CWnd* pParent /*=NULL*/,long lNetHandle)
	: CDialog(CAlarmDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAlarmDlg)
	m_bAlarmEnable0	= FALSE;
	m_bAlarmEnable1 = FALSE;
	m_bAlarmEnable2 = FALSE;
	m_bAlarmEnable3 = FALSE;
	//}}AFX_DATA_INIT
	m_lNetHandle	= lNetHandle;
}

void CAlarmDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAlarmDlg)
	DDX_Control(pDX, IDC_STATIC_WEEK, m_stWeek);
	DDX_Check(pDX, IDC_CHECK_ALARM, m_bAlarmEnable0);
	DDX_Check(pDX, IDC_CHECK_ALARM1, m_bAlarmEnable1);
	DDX_Check(pDX, IDC_CHECK_ALARM2, m_bAlarmEnable2);
	DDX_Check(pDX, IDC_CHECK_ALARM3, m_bAlarmEnable3);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAlarmDlg, CDialog)
	//{{AFX_MSG_MAP(CAlarmDlg)
	ON_BN_CLICKED(IDC_BTN_WRITE, OnBtnWrite)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAlarmDlg message handlers

BOOL CAlarmDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	theApp.m_lang.TransDialog(m_hWnd, IDD);
	InitGrid();
	LoadParam();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAlarmDlg::InitGrid()
{
	CStringArray arrStr;
	if(theApp.GetProfileInt("Setting", "LANG", 0) == 1)
	{
		arrStr.Add("All");
		arrStr.Add("Sun.");
		arrStr.Add("Mon.");
		arrStr.Add("Tue.");
		arrStr.Add("Wed.");
		arrStr.Add("Thu.");
		arrStr.Add("Fri.");
		arrStr.Add("Sat.");
	}
	else
	{
		arrStr.Add("全部");
		arrStr.Add("星期日");
		arrStr.Add("星期一");
		arrStr.Add("星期二");
		arrStr.Add("星期三");
		arrStr.Add("星期四");
		arrStr.Add("星期五");
		arrStr.Add("星期六");
	}
	
	m_stWeek.SetWeekText(arrStr);
}

void CAlarmDlg::FillDateTimeInfo(std::vector<NS_WEEK_TIME_S>& emVectorDateTime)
{
	UpdateData();

    int  nTime			= 0;
    BOOL bTimeEnable	= TRUE;
    NS_WEEK_TIME_S emDateTime;

    for(int nWeekIndex = NS_WEEK_SUNDAY; nWeekIndex <= NS_WEEK_SATURDAY; nWeekIndex ++)
    {
        memset(&emDateTime,0,sizeof(NS_WEEK_TIME_S));

        nTime = 0;
        for(int nTimeIndex = GRID_COL - 1; nTimeIndex > 0; nTimeIndex --)
        {
            bTimeEnable = m_stWeek.GetGridItemData(nWeekIndex + 1,nTimeIndex);
            nTime = (nTime << 1) | (bTimeEnable ? 0x01 : 0x0);
        }

        emDateTime.emDate	= (NS_WEEK_DATE_E)nWeekIndex;
        emDateTime.nTime	= nTime;
        emDateTime.bEnable	= m_stWeek.GetGridItemData(nWeekIndex + 1,0);

        emVectorDateTime.push_back(emDateTime);
    }
}

void CAlarmDlg::LoadParam() 
{
	// TODO: Add your control notification handler code here
    // 布防规则
    std::vector<NS_WEEK_TIME_S> emVectorDateTime;

    unsigned int size = 0;
    NS_ALARM_IN_INFO_S cfg;
    ZeroMemory(&cfg, sizeof(cfg));
    if(NS_NET_GetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_GET_ALARM_IN_INFO, &cfg, &size) != 0)
    {
        AfxMessageBox(_T("Get alarm in Failed."));
        return ;
    }

    int nIndex = 0;
    for(;nIndex < 7; nIndex ++)
    {
        NS_WEEK_TIME_S day;
        day.emDate = (NS_WEEK_DATE_E)nIndex;
        int nTime = 0;
        for (int i=0; i<NS_DEV_RECORD_SCHEDULE_PARTS; i++)
        {
            nTime |= cfg.schedule.schedule[nIndex][i]<<i;
        }
        day.nTime = nTime;
        day.bEnable = cfg.schedule.bEnable[nIndex];
        emVectorDateTime.push_back(day);
    }
    m_bAlarmEnable0 = cfg.ai0en;
    m_bAlarmEnable1 = cfg.ai1en;
    m_bAlarmEnable2 = cfg.ai2en;
    m_bAlarmEnable3 = cfg.ai3en;

    m_stWeek.SetAllValue(0);
    m_stWeek.Invalidate();

    int  nTime			= 0;
    UINT nDate			= 0;
    BOOL bDateEnable	= FALSE;
    BOOL bTimeEnable	= FALSE;
    for(int nWeekIndex = NS_WEEK_SUNDAY; nWeekIndex < emVectorDateTime.size() && nWeekIndex <= NS_WEEK_SATURDAY; nWeekIndex ++)
    {
        nDate		= emVectorDateTime.at(nWeekIndex).emDate;
        if(nDate >= NS_WEEK_SUNDAY && NS_WEEK_SUNDAY <= NS_WEEK_SATURDAY)
        {
            bDateEnable	= emVectorDateTime.at(nDate).bEnable;
            m_stWeek.SetGridItemData(nDate + 1,0,bDateEnable);

            nTime		= emVectorDateTime.at(nDate).nTime;

            for(int nTimeIndex = GRID_COL - 1; nTimeIndex > 0; nTimeIndex --)
            {
                bTimeEnable = ((0x1 & (nTime >> (nTimeIndex - 1))) != 0);
                m_stWeek.SetGridItemData(nDate + 1,nTimeIndex,bTimeEnable);
            }
        }
    }

	
	UpdateData(FALSE);
}

void CAlarmDlg::OnBtnWrite() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	

    unsigned int size = 0;
    NS_ALARM_IN_INFO_S cfg;
    ZeroMemory(&cfg, sizeof(cfg));
    size = sizeof(NS_VIDEO_LOSS_INFO_S);
    cfg.dwSize = size;
    cfg.ai0en = m_bAlarmEnable0;
    cfg.ai1en = m_bAlarmEnable1;
    cfg.ai2en = m_bAlarmEnable2;
    cfg.ai3en = m_bAlarmEnable3;

    // 布防规则
    std::vector<NS_WEEK_TIME_S> emVectorDateTime;
    FillDateTimeInfo(emVectorDateTime);

    int nIndex = 0;
    for(; nIndex < 7; nIndex ++)
    {
        int nTime = emVectorDateTime.at(nIndex).nTime;
        for (int i=0; i<NS_DEV_RECORD_SCHEDULE_PARTS; i++)
        {
            cfg.schedule.schedule[nIndex][i] = (nTime& (1<<i))>>i;
        }
        cfg.schedule.bEnable[nIndex] = emVectorDateTime[nIndex].bEnable;
    }

    if(NS_NET_SetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_SET_ALARM_IN_INFO, &cfg, size) != 0)
    {
        AfxMessageBox(_T("Set alarm  in Failed."));
        return ;
    }
    AfxMessageBox(_T("Set alarm  in OK."));
}
