// DevRecSearchDlg.cpp : implementation file
//

#include "stdafx.h"
#include "netsdk_demo.h"
#include "DevRecSearchDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDevRecSearchDlg dialog
CDevRecSearchDlg::CDevRecSearchDlg(CWnd* pParent /*=NULL*/,long lNetHandle)
	: CDialog(CDevRecSearchDlg::IDD, pParent)
{
	CTime tmNow		= CTime::GetCurrentTime();
	//{{AFX_DATA_INIT(CDevRecSearchDlg)
	m_dateStart		= tmNow;
	m_dateStop		= tmNow;
	m_timeStart		= tmNow;
	m_timeStop		= tmNow;
	m_nDevRecType	= 3;
	//}}AFX_DATA_INIT
	m_lNetHandle	= lNetHandle;
}

void CDevRecSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDevRecSearchDlg)
	DDX_Control(pDX, IDC_LIST_REC_FILE, m_listFile);
	DDX_DateTimeCtrl(pDX, IDC_DATE_START, m_dateStart);
	DDX_DateTimeCtrl(pDX, IDC_DATE_STOP, m_dateStop);
	DDX_DateTimeCtrl(pDX, IDC_TIME_START, m_timeStart);
	DDX_DateTimeCtrl(pDX, IDC_TIME_STOP, m_timeStop);
	DDX_CBIndex(pDX, IDC_COMBO_DEV_REC_TYPE, m_nDevRecType);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDevRecSearchDlg, CDialog)
	//{{AFX_MSG_MAP(CDevRecSearchDlg)
	ON_BN_CLICKED(IDC_BTN_SEARCH_START, OnBtnSearchStart)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_NEXT_PAGE, OnBnClickedNextPage)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDevRecSearchDlg message handlers
BOOL CDevRecSearchDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	theApp.m_lang.TransDialog(m_hWnd, IDD);
	
	
	CreateFileList();
    GetDlgItem(IDC_NEXT_PAGE)->EnableWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDevRecSearchDlg::CreateFileList()
{
	m_listFile.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_UNDERLINEHOT|LVS_EX_GRIDLINES);

	m_listFile.InsertColumn(0,uistrings[STR_FILE_NAME].strings[g_nLangID],LVCFMT_CENTER,500);
}

// 开始搜索前端录像文件
void CDevRecSearchDlg::OnBtnSearchStart() 
{
	// TODO: Add your control notification handler code here
	UpdateData();

    unsigned int size = 0;
    NS_SEARCH_DEV_RECORD_S cfg;
    ZeroMemory(&cfg, sizeof(cfg));
    cfg.dwSize = sizeof(cfg);
    cfg.action = NS_SEARCH_DEV_RECORD_ACTION_START;


    cfg.begin.day = m_dateStart.GetDay();
    cfg.begin.month = m_dateStart.GetMonth();
    cfg.begin.week = m_dateStart.GetDayOfWeek();
    cfg.begin.year = m_dateStart.GetYear();
    cfg.begin.second = m_timeStart.GetSecond();
    cfg.begin.hour = m_timeStart.GetHour();
    cfg.begin.minute = m_timeStart.GetMinute();
    
    cfg.end.hour = m_timeStop.GetHour();
    cfg.end.minute = m_timeStop.GetMinute();
    cfg.end.second = m_timeStop.GetSecond();
    cfg.end.year = m_dateStop.GetYear();
    cfg.end.month = m_dateStop.GetMonth();
    cfg.end.day = m_dateStop.GetDay();
    cfg.end.week = m_dateStop.GetDayOfWeek();

    cfg.type = (NS_DEV_RECORD_TYPE_E)m_nDevRecType;
    if(NS_NET_GetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_SEARCH_DEV_RECORD, &cfg, &size) != 0)
    {
        AfxMessageBox(_T("Search dev record failed."));
        return ;
    }

    GetDlgItem(IDC_NEXT_PAGE)->EnableWindow(cfg.hasmore);

    m_listFile.DeleteAllItems();
    for (int i =0; i < cfg.filenum; i++ )
    {
        m_listFile.InsertItem(0, cfg.files[i]);
    }
}

void CDevRecSearchDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
}

void CDevRecSearchDlg::OnBnClickedNextPage()
{
    unsigned int size = 0;
    NS_SEARCH_DEV_RECORD_S cfg;
    ZeroMemory(&cfg, sizeof(cfg));
    cfg.dwSize = sizeof(cfg);
    cfg.action = NS_SEARCH_DEV_RECORD_ACTION_NEXT_PAGE;


    cfg.begin.day = m_dateStart.GetDay();
    cfg.begin.month = m_dateStart.GetMonth();
    cfg.begin.week = m_dateStart.GetDayOfWeek();
    cfg.begin.year = m_dateStart.GetYear();
    cfg.begin.second = m_timeStart.GetSecond();
    cfg.begin.hour = m_timeStart.GetHour();
    cfg.begin.minute = m_timeStart.GetMinute();

    cfg.end.hour = m_timeStop.GetHour();
    cfg.end.minute = m_timeStop.GetMinute();
    cfg.end.second = m_timeStop.GetSecond();
    cfg.end.year = m_dateStop.GetYear();
    cfg.end.month = m_dateStop.GetMonth();
    cfg.end.day = m_dateStop.GetDay();
    cfg.end.week = m_dateStop.GetDayOfWeek();

    if(NS_NET_GetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_SEARCH_DEV_RECORD, &cfg, &size) != 0)
    {
        AfxMessageBox(_T("Search dev record failed."));
        return ;
    }

    GetDlgItem(IDC_NEXT_PAGE)->EnableWindow(cfg.hasmore);

    m_listFile.DeleteAllItems();
    for (int i =0; i < cfg.filenum; i++ )
    {
        m_listFile.InsertItem(0, cfg.files[i]);
    }
}
