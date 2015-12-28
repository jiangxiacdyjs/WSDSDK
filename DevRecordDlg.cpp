// DevRecordDlg.cpp : implementation file
//

#include "stdafx.h"
#include "netsdk_demo.h"
#include "DevRecordDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TIMER_REFRESH 1000

/////////////////////////////////////////////////////////////////////////////
// CDevRecordDlg dialog
CDevRecordDlg::CDevRecordDlg(CWnd* pParent /*=NULL*/,long lNetHandle)
	: CDialog(CDevRecordDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDevRecordDlg)
	m_dwDiskReserve = 0;
	m_nDiskStrategy = 0;
	m_dwFileMaxTime = 0;
	m_nFileStrategy = 0;
	m_dwMaxAlarmFileTime = 0;
	//}}AFX_DATA_INIT
	m_lNetHandle	= lNetHandle;
}

void CDevRecordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDevRecordDlg)
	DDX_Control(pDX, IDC_STATIC_WEEK, m_stWeek);
	DDX_Control(pDX, IDC_LIST_DISK, m_listDisk);
	DDX_Control(pDX, IDC_STATIC_RECORD_STATUS, m_stRecordStatus);
	DDX_Text(pDX, IDC_EDIT_DISK_RESERVE, m_dwDiskReserve);
	DDV_MinMaxDWord(pDX, m_dwDiskReserve, 10, 1000000);
	DDX_Radio(pDX, IDC_RADIO_DISK_STOP, m_nDiskStrategy);
	DDX_Text(pDX, IDC_EDIT_FILE_MAXTIME, m_dwFileMaxTime);
	DDV_MinMaxDWord(pDX, m_dwFileMaxTime, 1, 15);
	DDX_Radio(pDX, IDC_RADIO_FILE_STOP, m_nFileStrategy);
	DDX_Text(pDX, IDC_EDIT_ALARM_FILE_MAXTIME, m_dwMaxAlarmFileTime);
	DDV_MinMaxUInt(pDX, m_dwMaxAlarmFileTime, 10, 60);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDevRecordDlg, CDialog)
	//{{AFX_MSG_MAP(CDevRecordDlg)
	ON_BN_CLICKED(IDC_BTN_START, OnBtnStart)
	ON_BN_CLICKED(IDC_BTN_STOP, OnBtnStop)
	ON_BN_CLICKED(IDC_BTN_RECORD_READ, OnBtnRecordRead)
	ON_BN_CLICKED(IDC_BTN_RECORD_SAVE, OnBtnRecordSave)
	//}}AFX_MSG_MAP
    ON_WM_TIMER()
    ON_WM_CLOSE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDevRecordDlg message handlers

BOOL CDevRecordDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	theApp.m_lang.TransDialog(m_hWnd, IDD);
	
	InitList();
	InitGrid();
	InitControl();

    SetTimer(TIMER_REFRESH, 3000, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDevRecordDlg::InitGrid()
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

void CDevRecordDlg::InitList()
{
	m_listDisk.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_FLATSB|LVS_EX_UNDERLINEHOT|LVS_EX_GRIDLINES);
	
	CString strCol;
	int nFmt = LVCFMT_LEFT;
	int iSub = 0;
	
	m_listDisk.InsertColumn(iSub ++,uistrings[STR_PARTITION].strings[g_nLangID],nFmt,100);
	m_listDisk.InsertColumn(iSub ++,uistrings[STR_SPACE_TOTAL].strings[g_nLangID],nFmt,100);
	m_listDisk.InsertColumn(iSub ++,uistrings[STR_SPACE_LEFT].strings[g_nLangID],nFmt,100);
}

BOOL CDevRecordDlg::InitControl()
{
	// ----------------------------------------------------------------------
    unsigned int size = 0;
    NS_DEV_RECORD_INFO_S cfg;
    ZeroMemory(&cfg, sizeof(cfg));
    if(NS_NET_GetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_GET_DEV_RECORD_INFO, &cfg, &size) != 0)
    {
        AfxMessageBox(_T("Get device record info Failed."));
        return FALSE;
    }

 
    UpdateStatus(cfg.recordstatus0);
 
 	// ----------------------------------------------------------------------

    m_dwDiskReserve = cfg.diskreserve;
    m_nDiskStrategy = cfg.diskstrategy;
    m_dwFileMaxTime = cfg.filetime;
    m_dwMaxAlarmFileTime = cfg.recordtime;
    m_nFileStrategy = cfg.filestrategy;
    m_rcrdchn = cfg.rcrdchn;

    //磁盘列表
 	m_listDisk.DeleteAllItems();
 	CString strDisk;
 	int nIndex = 0;
 	for(nIndex = 0; nIndex < cfg.disknum; nIndex ++)
 	{
 		m_listDisk.InsertItem(nIndex,cfg.disks[nIndex].diskname);
 		
 		strDisk.Format("%d M",cfg.disks[nIndex].disktotal);
 		m_listDisk.SetItemText(nIndex,1,strDisk);
 		
 		strDisk.Format("%d M",cfg.disks[nIndex].diskfree);
 		m_listDisk.SetItemText(nIndex,2,strDisk);
 	}

    //时间计划
    m_stWeek.SetAllValue(0);
    m_stWeek.Invalidate();

    std::vector<NS_WEEK_TIME_S> emVectorDateTime;
    nIndex = 0;
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
	
	return TRUE;
}

void CDevRecordDlg::OnBtnStart() 
{
	// TODO: Add your control notification handler code here
    NS_CMD_INFO_S cfg;
    unsigned int size = sizeof(NS_CMD_INFO_S);
    cfg.dwSize = sizeof(NS_CMD_INFO_S);
    if(NS_NET_SetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_DEV_RECORD_START, &cfg, size) != 0)
    {
        AfxMessageBox("Start Device Record Failed.");
        return ;
    }
}

void CDevRecordDlg::OnBtnStop() 
{
	// TODO: Add your control notification handler code here
    NS_CMD_INFO_S cfg;
    unsigned int size = sizeof(NS_CMD_INFO_S);
    cfg.dwSize = sizeof(NS_CMD_INFO_S);
    if(NS_NET_SetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_DEV_RECORD_STOP, &cfg, size) != 0)
    {
        AfxMessageBox("Stop Device Record Failed.");
        return ;
    }
}

void CDevRecordDlg::OnBtnRecordRead() 
{
	// TODO: Add your control notification handler code here
	InitControl();
}

void CDevRecordDlg::OnBtnRecordSave() 
{
	// TODO: Add your control notification handler code here
	UpdateData();


    unsigned int size = 0;
    NS_DEV_RECORD_INFO_S cfg;
    ZeroMemory(&cfg, sizeof(cfg));
    size = sizeof(cfg);
    cfg.dwSize = size;
    cfg.diskreserve = m_dwDiskReserve;
    cfg.diskstrategy = m_nDiskStrategy;
    cfg.filetime = m_dwFileMaxTime;
    cfg.filestrategy = m_nFileStrategy;
    cfg.recordtime = m_dwMaxAlarmFileTime;
    cfg.rcrdchn = m_rcrdchn;


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

    if(NS_NET_SetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_SET_DEV_RECORD_INFO, &cfg, size) != 0)
    {
        AfxMessageBox(_T("Set device record info Failed."));
        return ;
    }
    AfxMessageBox(_T("OK"));
}

void CDevRecordDlg::FillDateTimeInfo(std::vector<NS_WEEK_TIME_S>& emVectorDateTime)
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

void CDevRecordDlg::UpdateStatus(NS_DEV_RECORD_STATUS_E status)
{
    if (status == NS_DEV_RECORD_STATUS_STOP)
    {
        SetDlgItemText(IDC_STATIC_RECORD_STATUS, uistrings[STR_DEV_REC_STATUS_IDLE].strings[g_nLangID]);
    }
    else if (status == NS_DEV_RECORD_STATUS_MANUAL)
    {
        SetDlgItemText(IDC_STATIC_RECORD_STATUS, uistrings[STR_DEV_REC_STATUS_MANUAL].strings[g_nLangID]);
    }
    else if (status == NS_DEV_RECORD_STATUS_ALARM)
    {
        SetDlgItemText(IDC_STATIC_RECORD_STATUS, uistrings[STR_DEV_REC_STATUS_ALARM].strings[g_nLangID]);
    }
    else if (status == NS_DEV_RECORD_STATUS_MD)
    {
        SetDlgItemText(IDC_STATIC_RECORD_STATUS, uistrings[STR_DEV_REC_STATUS_MD].strings[g_nLangID]);
    }
    else if (status == NS_DEV_RECORD_STATUS_SCHEDULE)
    {
        SetDlgItemText(IDC_STATIC_RECORD_STATUS, uistrings[STR_DEV_REC_STATUS_SCHE].strings[g_nLangID]);
    }
    else if (status == NS_DEV_RECORD_STATUS_SNAP)
    {
        SetDlgItemText(IDC_STATIC_RECORD_STATUS, uistrings[STR_DEV_REC_STATUS_SNAP].strings[g_nLangID]);
    }
    else
    {

    }
}

void CDevRecordDlg::Refresh()
{
    unsigned int size = 0;
    NS_DEV_RECORD_INFO_S cfg;
    ZeroMemory(&cfg, sizeof(cfg));
    if(NS_NET_GetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_GET_DEV_RECORD_INFO, &cfg, &size) != 0)
    {
        AfxMessageBox(_T("Get device record info Failed."));
        return ;
    }
    UpdateStatus(cfg.recordstatus0);
}

void CDevRecordDlg::OnTimer(UINT_PTR nIDEvent)
{
    // TODO: Add your message handler code here and/or call default

    if (nIDEvent == TIMER_REFRESH)
    {
        Refresh();
        return;
    }

    CDialog::OnTimer(nIDEvent);
}

void CDevRecordDlg::OnClose()
{
    // TODO: Add your message handler code here and/or call default
    KillTimer(TIMER_REFRESH);
    CDialog::OnClose();
}
