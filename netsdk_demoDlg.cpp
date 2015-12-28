// JSNetDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "netsdk_demo.h"
#include "netsdk_demoDlg.h"

#include "PresetDlg.h"
#include "TrackDlg.h"
#include "BPSDlg.h"
#include "ColorDlg.h"
#include "ComDlg.h"
#include "MDDlg.h"
#include "NetDlg.h"
#include "OSDDlg.h"
#include "SystemDlg.h"
#include "PortDlg.h"
#include "TimeDlg.h"
#include "UserDlg.h"
#include "VideoLossDlg.h"
#include "UpdateDlg.h"
#include "AlarmDlg.h"
#include "AudioDlg.h"
#include "DevRecordDlg.h"
#include "DevRecSearchDlg.h"
#include "VideoMaskDlg.h"

#include "ACDlg.h"
#include "EmailDlg.h"
#include "FTPDlg.h"
#include "SensorOutDlg.h"
#include "CARecordDlg.h"

#include "CASensorInDlg.h"
#include "CAMDDlg.h"
#include "CAVLDlg.h"

#include "HsDlg.h"
#include "3DRectDlg.h"
#include "BallVideoMaskDlg.h"
#include "WADlg.h"
#include "EncryptStrDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TIMER_CONNECT       2013
#define TIMER_DISCONNECT    2014

CString g_strChannel;
unsigned int g_u32DevHandle;

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetsdkDemoDlg dialog

CNetsdkDemoDlg::CNetsdkDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNetsdkDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNetsdkDemoDlg)
	m_nPort			= 554;
	m_strDVSChn = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon			= AfxGetApp()->LoadIcon(IDR_MAINFRAME);

    m_u32DevHandle = 0;
    m_u32PlayerHandle = 0;
    m_u32Mp4Handle = 0;
	m_pu32Mp4ReaderHandle = 0;
	m_u32VideoDecoderHandle = 0;
	m_u32AudioDecoderHandle = 0;
    m_bAuto = FALSE;
	m_speed = 1.0;
	m_strDVSAddr=AfxGetApp()->GetProfileString("setting","boardip","192.168.2.40");
    m_strDVSAddrOld = "";

	m_nLauguage = theApp.GetProfileInt("Setting", "LANG", 0);
	m_strPassword	= theApp.GetProfileString("Setting", "password", "admin");
	m_strUser		= theApp.GetProfileString("Setting", "user", "admin");
	
	m_font.CreatePointFont(300,"宋体");
}

void CNetsdkDemoDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CNetsdkDemoDlg)
    DDX_Control(pDX, IDC_CHECK_SENSOR_2, m_btnSensor2);
    DDX_Control(pDX, IDC_CHECK_SENSOR_1, m_btnSensor1);
    DDX_Control(pDX, IDC_CHECK_ABC, m_btnABC);
    DDX_Control(pDX, IDC_CHECK_AUDIO_OUT, m_btnAudioOut);
    DDX_Control(pDX, IDC_COMBO_TYPE, m_cmbType);
    DDX_Control(pDX, IDC_STATIC_VIDEO, m_stVideo);
    DDX_Text(pDX, IDC_EDIT_ADDR, m_strDVSAddr);
    DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
    DDV_MaxChars(pDX, m_strPassword, 256);
    DDX_Text(pDX, IDC_EDIT_PORT, m_nPort);
    DDV_MinMaxUInt(pDX, m_nPort, 1, 65535);
    DDX_Text(pDX, IDC_EDIT_USER, m_strUser);
    DDV_MaxChars(pDX, m_strUser, 256);
	DDX_Radio(pDX, IDC_RADIO_CHS, m_nLauguage);
	//}}AFX_DATA_MAP
    DDX_Control(pDX, IDC_COMBO_CHANNEL, m_cmboChannel);
    DDX_Text(pDX, IDC_COMBO_CHANNEL, m_strDVSChn);
    DDX_Control(pDX, IDC_BUTTON_LEFTUP, m_btnLeftUp);
    DDX_Control(pDX, IDC_BTN_PTZ_LEFT, m_btnLeft);
    DDX_Control(pDX, IDC_BUTTON_LEFTDOWN, m_btnLeftDown);
    DDX_Control(pDX, IDC_BTN_PTZ_UP, m_btnUp);
    DDX_Control(pDX, IDC_BTN_PTZ_DOWN, m_btnDown);
    DDX_Control(pDX, IDC_BUTTON_RIGHTUP, m_btnRightUp);
    DDX_Control(pDX, IDC_BTN_PTZ_RIGHT, m_btnRight);
    DDX_Control(pDX, IDC_BUTTON_RIGHTDOWN, m_btnRightDown);

    DDX_Control(pDX, IDC_BTN_PTZ_ZOOM_ADD, m_btnZoomAdd);
    DDX_Control(pDX, IDC_BTN_PTZ_ZOOM_SUB, m_btnZoomSub);
    DDX_Control(pDX, IDC_BTN_PTZ_FOCUS_ADD, m_btnFocusAdd);
    DDX_Control(pDX, IDC_BTN_PTZ_FOCUS_SUB, m_btnFocusSub);
    DDX_Control(pDX, IDC_BTN_PTZ_IRISA_ADD, m_btnIrisAdd);
    DDX_Control(pDX, IDC_BTN_PTZ_IRISA_SUB, m_btnIrisSub);
}

BEGIN_MESSAGE_MAP(CButtonEx, CButton)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CNetsdkDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CNetsdkDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_PREVIEW_START, OnBtnPreviewStart)
	ON_BN_CLICKED(IDC_BTN_PREVIEW_STOP, OnBtnPreviewStop)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_RECORD_START, OnBtnRecordStart)
	ON_BN_CLICKED(IDC_BTN_RECORD_STOP, OnBtnRecordStop)
	ON_BN_CLICKED(IDC_BTN_SNAP, OnBtnSnap)
	ON_BN_CLICKED(IDC_CHECK_AUDIO_OUT, OnCheckAudioOut)
	ON_BN_CLICKED(IDC_BTN_SEARCH, OnBtnSearch)
	ON_BN_CLICKED(IDC_BTN_PTZ_AUTO, OnBtnPtzAuto)
	ON_BN_CLICKED(IDC_CHECK_ABC, OnCheckAbc)
	ON_BN_CLICKED(IDC_BTN_PTZ_PRESET, OnBtnPtzPreset)
	ON_BN_CLICKED(IDC_CHECK_SENSOR_1, OnCheckSensor1)
	ON_BN_CLICKED(IDC_CHECK_SENSOR_2, OnCheckSensor2)
	ON_BN_CLICKED(IDC_BTN_DEV_BPS, OnBtnDevBps)
	ON_BN_CLICKED(IDC_BTN_DEV_COLOR, OnBtnDevColor)
	ON_BN_CLICKED(IDC_BTN_DEV_COM, OnBtnDevCom)
	ON_BN_CLICKED(IDC_BTN_DEV_MD, OnBtnDevMd)
	ON_BN_CLICKED(IDC_BTN_NET, OnBtnNet)
	ON_BN_CLICKED(IDC_BTN_OSD, OnBtnOsd)
	ON_BN_CLICKED(IDC_BTN_SYS, OnBtnSys)
	ON_BN_CLICKED(IDC_BTN_PORT, OnBtnPort)
	ON_BN_CLICKED(IDC_BTN_TIME, OnBtnTime)
	ON_BN_CLICKED(IDC_BTN_USER, OnBtnUser)
	ON_BN_CLICKED(IDC_BTN_VL, OnBtnVl)
	ON_BN_CLICKED(IDC_BTN_UPDATE, OnBtnUpdate)
	ON_BN_CLICKED(IDC_BTN_SENSOR, OnBtnSensor)
	ON_BN_CLICKED(IDC_BTN_AUDIO, OnBtnAudio)
	ON_BN_CLICKED(IDC_BTN_DEV_REC, OnBtnDevRec)
	ON_BN_CLICKED(IDC_BTN_PTZ_TRACK, OnBtnPtzTrack)
	ON_BN_CLICKED(IDC_BTN_PTZ_LIGHT_OPEN, OnBtnPtzLightOpen)
	ON_BN_CLICKED(IDC_BTN_PTZ_LIGHT_CLOSE, OnBtnPtzLightClose)
	ON_BN_CLICKED(IDC_BTN_PTZ_BRUSH_OPEN, OnBtnPtzBrushOpen)
	ON_BN_CLICKED(IDC_BTN_PTZ_BRUSH_CLOSE, OnBtnPtzBrushClose)
	ON_BN_CLICKED(IDC_BTN_AC, OnBtnAc)
	ON_BN_CLICKED(IDC_BTN_EMAIL, OnBtnEmail)
	ON_BN_CLICKED(IDC_BTN_FTP, OnBtnFtp)
	ON_BN_CLICKED(IDC_BTN_SENSOR_OUT, OnBtnSensorOut)
	ON_BN_CLICKED(IDC_BTN_CA_SENSOR_IN, OnBtnCaSensorIn)
	ON_BN_CLICKED(IDC_BTN_CA_MD, OnBtnCaMd)
	ON_BN_CLICKED(IDC_BTN_CA_VL, OnBtnCaVl)
	ON_BN_CLICKED(IDC_BTN_RECORD, OnBtnRecord)
	ON_BN_CLICKED(IDC_BTN_DEV_REC_SEARCH, OnBtnDevRecSearch)
	ON_BN_CLICKED(IDC_BTN_HS, OnBtnHs)
	ON_BN_CLICKED(IDC_BUTTON_3D, OnButton3d)
	ON_BN_CLICKED(IDC_BUTTON_DEVCHN, OnButtonDevchn)
	ON_BN_CLICKED(IDC_BUTTON_3D_MODE2, OnButton3dMode2)
	ON_BN_CLICKED(IDC_BTN_VIDEO_MASK, OnBtnVideoMask)
	ON_BN_CLICKED(IDC_BTN_BALL_VIDEO_MASK, OnBtnBallVideoMask)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, OnButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_DISCONNECT, OnButtonDisconnect)
	ON_BN_CLICKED(IDC_BUTTON_PLAYBACK, OnButtonPlayback)
	ON_BN_CLICKED(IDC_BUTTON_PLAYBACK_SLOW, OnButtonPlaybackSlow)
	ON_BN_CLICKED(IDC_BUTTON_PLAYBACK_FAST, OnButtonPlaybackFast)
	ON_BN_CLICKED(IDC_BUTTON_PLAYBACK_PAUSE, OnButtonPlaybackPause)
	ON_BN_CLICKED(IDC_BUTTON_PLAYBACK_SEEK, OnButtonPlaybackSeek)
	ON_BN_CLICKED(IDC_RADIO_CHS, OnRadioChs)
	ON_BN_CLICKED(IDC_RADIO_ENG, OnRadioEng)
	ON_BN_CLICKED(IDC_BUTTON_WA_IMAGE, OnButtonWaImage)
	ON_BN_CLICKED(IDC_BUTTON_ENCRYPT_STR, OnButtonEncryptStr)
	ON_BN_CLICKED(IDC_BUTTON_VIDEODECODER, OnButtonVideodecoder)
	ON_BN_CLICKED(IDC_BUTTON_AUDIODECODER, OnButtonAudiodecoder)
	//}}AFX_MSG_MAP
	
    ON_WM_TIMER()
    ON_MESSAGE(WM_NS_NETSTAT,OnNetStatusMsg)
    ON_MESSAGE(WM_NS_ALARM,OnAlarmMsg)
    ON_MESSAGE(WM_NS_BTN_MESSAGE,OnBtnMessage)				// 按钮按下弹起消息
    ON_WM_CREATE()
    ON_BN_CLICKED(IDC_BUTTON_PTZ20, OnBnClickedButtonPtz20)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetsdkDemoDlg message handlers

BOOL CNetsdkDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	InitUI();
	InitNetSDK();

    char version[128];
    NS_NET_GetVersion(version);
    CString strTitle;
    strTitle.Format("SDK DEMO %s", version);
    SetWindowText(strTitle);

    CRect rc;
    m_stVideo.GetWindowRect(&rc);
    ScreenToClient(&rc);
    m_videoWnd.Create(IDD_DIALOG_VIDEO, rc, this);
    m_videoWnd.SetWndMsgCallback(OnVideoWndMsg, this);

	m_cmbType.SetCurSel(0);
    m_btnLeft.SetParentMessage(TRUE, m_hWnd);
    m_btnLeftUp.SetParentMessage(TRUE, m_hWnd);
    m_btnRight.SetParentMessage(TRUE, m_hWnd);
    m_btnUp.SetParentMessage(TRUE, m_hWnd);
    m_btnDown.SetParentMessage(TRUE, m_hWnd);
    m_btnLeftDown.SetParentMessage(TRUE, m_hWnd);
    m_btnRightUp.SetParentMessage(TRUE, m_hWnd);
    m_btnRightDown.SetParentMessage(TRUE, m_hWnd);

    m_btnZoomAdd.SetParentMessage(TRUE, m_hWnd);
    m_btnZoomSub.SetParentMessage(TRUE, m_hWnd);
    m_btnFocusAdd.SetParentMessage(TRUE, m_hWnd);
    m_btnFocusSub.SetParentMessage(TRUE, m_hWnd);
    m_btnIrisAdd.SetParentMessage(TRUE, m_hWnd);
    m_btnIrisSub.SetParentMessage(TRUE, m_hWnd);

    SetTimer(TIMER_CONNECT , 3000, NULL);

    //用于测试稳定性
//     SetTimer(TIMER_DISCONNECT , 7000, NULL);

    m_ptz20Dlg.Create(IDD_DIALOG_PTZ20, this);


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CNetsdkDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CNetsdkDemoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CNetsdkDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// 初始化通讯库
BOOL CNetsdkDemoDlg::InitNetSDK()
{
    NS_NET_Init();
    NS_PLAYER_Init();
    NS_MP4_Init();
	return TRUE;
}

HRESULT CNetsdkDemoDlg::OnNetStatusMsg(WPARAM wParam,LPARAM lParam)
{
    NS_NETSTAT_E e = (NS_NETSTAT_E)lParam;
    switch(e)
    {
    case NS_NETSTAT_CONNING_FAILED:
        AfxMessageBox(uistrings[STR_ERR_CONNECT].strings[g_nLangID]);
        break;
    case NS_NETSTAT_LOGIN_FAILED:
        AfxMessageBox(uistrings[STR_ERR_PASSWORD].strings[g_nLangID]);
        break;
    case NS_NETSTAT_ABNORMAL_DISCONNED:
        SetTimer(TIMER_CONNECT , 3000, NULL);
        AfxMessageBox(uistrings[STR_ERR_DISCONN].strings[g_nLangID]);
        break;
    default:
        break;
    }
	return 0;
}

HRESULT CNetsdkDemoDlg::OnAlarmMsg(WPARAM wParam,LPARAM lParam)
{
    unsigned int e = lParam;
    switch(e)
    {
    case NS_STREAM_MD_ONLY:
        AfxMessageBox(uistrings[STR_ALARM_MD].strings[g_nLangID]);
        break;
    case NS_STREAM_SENSORIN_ONLY:
        AfxMessageBox(uistrings[STR_ALARM_IN].strings[g_nLangID]);
        break;
    case NS_STREAM_VIDEO_LOSS_ONLY:
        AfxMessageBox(uistrings[STR_ALARM_VL].strings[g_nLangID]);
        break;
    default:
        break;
    }
    return 0;
}

void __stdcall CNetsdkDemoDlg::OnDraw(long h, HDC hDC, long lParam)
{
	CNetsdkDemoDlg*  pThis	= (CNetsdkDemoDlg*)lParam;		// 当前类指针
	if(hDC)
	{

		CDC* pDC = CDC::FromHandle(hDC);
		
		CFont *pOldfont = pDC->SelectObject(&pThis->m_font);
		pDC->SetBkMode(TRANSPARENT);	
		pDC->SetTextColor(RGB(255,0,0));
		
		pDC->MoveTo(0, 0);

		CRect rc;
		pThis->m_videoWnd.GetClientRect(rc);

		::MoveToEx(hDC, 0, 0, NULL);
		::LineTo(hDC, rc.Width(), rc.Height());
		::MoveToEx(hDC, rc.Width(), 0, NULL);
		::LineTo(hDC, 0, rc.Height());

		pDC->TextOut(10, 200, _T("THE BLACK LINE IS DRAWED BY DRAW CALLBACK"));
		
		pDC->SelectObject(pOldfont);
		/*
		*/
	}
}

// 开始预览
void CNetsdkDemoDlg::OnBtnPreviewStart() 
{
	// TODO: Add your control notification handler code here
	UpdateData();

	OnBtnPreviewStop();

	int nType = m_cmbType.GetCurSel();

    UpdateData();

	TRACE("启动媒体流\n");
	
    const char * psUsername = m_strUser; 
    const char * psPassword = m_strPassword;
    const char * psHost = m_strDVSAddr;
    const char * psChannel = m_strDVSChn;
//	const char * psChannel = "stream2";
    unsigned short u16Port = m_nPort;
    
    int ret = NS_NET_StartStream(&m_u32StreamHandle, m_u32DevHandle, psChannel, 0, &m_stStreamInfo, OnStreamFunc, OnStreamFunc, this);
}

// 停止预览
void CNetsdkDemoDlg::OnBtnPreviewStop() 
{

    if (m_u32StreamHandle)
    {
        NS_NET_StopStream(m_u32DevHandle, m_u32StreamHandle);
        m_u32StreamHandle = 0;
    }

    if (m_pu32Mp4ReaderHandle)
    {
        NS_PLAYBACK_StopPlay(m_pu32Mp4ReaderHandle);
        m_u32StreamHandle = 0;
    }
	
    if (m_u32Mp4Handle)
    {
        NS_MP4_Close(m_u32Mp4Handle);
        m_u32Mp4Handle = 0;
    }
    if (m_u32PlayerHandle)
    {
        NS_PLAYER_Close(m_u32PlayerHandle);
        m_u32PlayerHandle = 0;
    }
    if (m_u32VideoDecoderHandle)
    {
        NS_VIDEODECODER_Close(m_u32VideoDecoderHandle);
        m_u32VideoDecoderHandle = 0;
    }
    if (m_u32AudioDecoderHandle)
    {
        NS_AUDIODECODER_Close(m_u32AudioDecoderHandle);
        m_u32AudioDecoderHandle = 0;
    }

    Invalidate();
}

// 开始录像
void CNetsdkDemoDlg::OnBtnRecordStart() 
{
    if (!m_u32Mp4Handle)
    {
        int ret = NS_MP4_Open(&m_u32Mp4Handle, "c:\\ns_mp4.mp4", &m_stStreamInfo);
        ASSERT(ret == NS_SUCCESS);
    }
}

// 停止录像
void CNetsdkDemoDlg::OnBtnRecordStop() 
{
    if (m_u32Mp4Handle)
    {
        NS_MP4_Close(m_u32Mp4Handle);
        m_u32Mp4Handle = 0;
		AfxMessageBox("c:\\ns_mp4.mp4");
    }
}

int CNetsdkDemoDlg::OnSnapShotFunc(unsigned int u32PlayerHandle,/* 句柄 */
                          NS_SNAPSHOT_FORMAT_E format,
                          unsigned char* pu8Buffer,/* 数据包含帧头 */
                          unsigned int u32Length,  /* 数据长度 */
                          void* pUserData)        /* 用户数据*/
{
    if (pu8Buffer)
    {
		const char * filename = NULL;
		if (format == NS_SNAPSHOT_FORMAT_JPEG)
		{
			filename = "c:\\netsdk_demo.jpeg";
		}
		else if (format == NS_SNAPSHOT_FORMAT_BMP)
		{
			filename = "c:\\netsdk_demo.bmp";
		}
		else
		{
			ASSERT(FALSE);
			return -1;
		}

        FILE * fh = fopen(filename, "wb");
        if (fh)
        {
            fwrite(pu8Buffer, 1, u32Length, fh);
            fclose(fh);
        }
    }

    return 0;
}

// 抓图
void CNetsdkDemoDlg::OnBtnSnap() 
{
    if (m_u32PlayerHandle)
    {
         NS_PLAYER_SnapShot(m_u32PlayerHandle , NS_SNAPSHOT_FORMAT_JPEG , 100, OnSnapShotFunc, this);
//        NS_PLAYER_SnapShot(m_u32PlayerHandle , NS_SNAPSHOT_FORMAT_BMP , 100, OnSnapShotFunc, this);
    }
}

// 音频监听
void CNetsdkDemoDlg::OnCheckAudioOut() 
{
	// TODO: Add your control notification handler code here
	if(m_btnAudioOut.GetCheck())
	{
        NS_PLAYER_TurnOnAudio(m_u32PlayerHandle);
	}
	else
	{
        NS_PLAYER_TurnOffAudio(m_u32PlayerHandle);
	}
}

// 语音对讲
void CNetsdkDemoDlg::OnCheckAbc() 
{
	// TODO: Add your control notification handler code here
	if(m_btnABC.GetCheck())
	{
        NS_NET_StartTalk(m_u32DevHandle, OnTalkFunc, this);
	}
	else
	{
        NS_NET_StopTalk(m_u32DevHandle);
	}
}



// 搜索设备
void CNetsdkDemoDlg::OnBtnSearch() 
{
	// TODO: Add your control notification handler code here
    CSearchDevDlg dlg;
    dlg.DoModal();
}



void CNetsdkDemoDlg::OnDestroy() 
{
	CString boardip;
	GetDlgItemText(IDC_EDIT_ADDR,boardip);
	AfxGetApp()->WriteProfileString("setting","boardip",boardip);
	theApp.WriteProfileString("Setting", "password", m_strPassword);
	theApp.WriteProfileString("Setting", "user", m_strUser);

    OnBtnPreviewStop();
    NS_NET_DeInit();
    NS_PLAYER_DeInit();
    NS_MP4_DeInit();
	NS_DECODER_DeInit();


	CDialog::OnDestroy();
	
}


// 云台自动
void CNetsdkDemoDlg::OnBtnPtzAuto() 
{
	// TODO: Add your control notification handler code here
    NS_PTZ_CMD_S cmd;
    ZeroMemory(&cmd, sizeof(NS_PTZ_CMD_S));
    cmd.dwSize = sizeof(NS_PTZ_CMD_S);
    cmd.speed = 50;
    m_bAuto = !m_bAuto;
    cmd.bStart = m_bAuto;
    NS_NET_PTZControl(m_u32DevHandle, NS_CMD_PTZ_AUTO, &cmd, cmd.dwSize);
}


// 灯光打开
void CNetsdkDemoDlg::OnBtnPtzLightOpen() 
{
	// TODO: Add your control notification handler code here
}

// 灯光关闭
void CNetsdkDemoDlg::OnBtnPtzLightClose() 
{
	// TODO: Add your control notification handler code here
}

// 雨刷打开
void CNetsdkDemoDlg::OnBtnPtzBrushOpen() 
{
	// TODO: Add your control notification handler code here
    NS_PTZ_CMD_S cmd;
    cmd.dwSize = sizeof(NS_PTZ_CMD_S);
    cmd.speed = 10;
    cmd.bStep = TRUE;
    cmd.bStart = TRUE;
    NS_NET_PTZControl(m_u32DevHandle, NS_CMD_PTZ_BRUSH, &cmd, cmd.dwSize);
}

// 雨刷关闭
void CNetsdkDemoDlg::OnBtnPtzBrushClose() 
{
	// TODO: Add your control notification handler code here
    NS_PTZ_CMD_S cmd;
    cmd.dwSize = sizeof(NS_PTZ_CMD_S);
    cmd.speed = 10;
    cmd.bStep = TRUE;
    cmd.bStart = FALSE;
    NS_NET_PTZControl(m_u32DevHandle, NS_CMD_PTZ_BRUSH, &cmd, cmd.dwSize);
}

// 探头输出1打开/关闭
void CNetsdkDemoDlg::OnCheckSensor1() 
{
	// TODO: Add your control notification handler code here
	BOOL bSensor1 = m_btnSensor1.GetCheck();
	BOOL bSensor2 = m_btnSensor2.GetCheck();

    unsigned int size = 0;
    NS_CA_AO_INFO_S cfg;
    ZeroMemory(&cfg, sizeof(cfg));
    cfg.dwSize = sizeof(NS_CA_AO_INFO_S);
    cfg.ao0 =  bSensor1;
    cfg.ao1 =  bSensor2;
    if(NS_NET_SetServerConfig(m_u32DevHandle, g_strChannel, NS_CMD_SET_CA_AO_INFO, &cfg, size) != 0)
    {
        AfxMessageBox("set sensor out  Failed.");
        return ;
    }
}

// 探头输出2打开/关闭
void CNetsdkDemoDlg::OnCheckSensor2() 
{
	// TODO: Add your control notification handler code here
	OnCheckSensor1() ;
}

// 预置位管理
void CNetsdkDemoDlg::OnBtnPtzPreset() 
{
	// TODO: Add your control notification handler code here
	CPresetDlg dlg(NULL,m_u32DevHandle);
	dlg.DoModal();
}

// 码率管理
void CNetsdkDemoDlg::OnBtnDevBps() 
{
	// TODO: Add your control notification handler code here
	CBPSDlg dlg(NULL,m_u32DevHandle);
	dlg.DoModal();
}

// 颜色管理
void CNetsdkDemoDlg::OnBtnDevColor() 
{
	// TODO: Add your control notification handler code here
	CColorDlg dlg(NULL,m_u32DevHandle);
	dlg.DoModal();
}

// 串口管理
void CNetsdkDemoDlg::OnBtnDevCom() 
{
	// TODO: Add your control notification handler code here
	CComDlg dlg(NULL,m_u32DevHandle);
	dlg.DoModal();
}

// 移动侦测管理
void CNetsdkDemoDlg::OnBtnDevMd() 
{
	// TODO: Add your control notification handler code here
	CMDDlg dlg(NULL,m_u32DevHandle);
	dlg.DoModal();
}

// 网络管理
void CNetsdkDemoDlg::OnBtnNet() 
{
	// TODO: Add your control notification handler code here
	CNetDlg dlg(NULL,m_u32DevHandle);
	dlg.DoModal();
}

// OSD管理
void CNetsdkDemoDlg::OnBtnOsd() 
{
	// TODO: Add your control notification handler code here
	COSDDlg dlg(NULL,m_u32DevHandle);
	dlg.DoModal();
}

// 系统管理
void CNetsdkDemoDlg::OnBtnSys() 
{
	// TODO: Add your control notification handler code here
	CSystemDlg dlg(NULL,m_u32DevHandle);
	dlg.DoModal();
}

// 通讯端口管理
void CNetsdkDemoDlg::OnBtnPort() 
{
	// TODO: Add your control notification handler code here
	CPortDlg dlg(NULL,m_u32DevHandle);
	dlg.DoModal();
}

// 时钟管理
void CNetsdkDemoDlg::OnBtnTime() 
{
	// TODO: Add your control notification handler code here
	CTimeDlg dlg(NULL,m_u32DevHandle);
	dlg.DoModal();
}

// 用户管理
void CNetsdkDemoDlg::OnBtnUser() 
{
	// TODO: Add your control notification handler code here
	CUserDlg dlg(NULL,m_u32DevHandle);
	dlg.DoModal();
}

// 视频丢失管理
void CNetsdkDemoDlg::OnBtnVl() 
{
	// TODO: Add your control notification handler code here
	CVideoLossDlg dlg(NULL,m_u32DevHandle);
	dlg.DoModal();
}

// 升级
void CNetsdkDemoDlg::OnBtnUpdate() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CUpdateDlg dlg(NULL,m_u32DevHandle,m_strDVSAddr);
	dlg.DoModal();
}

// 探头报警配置
void CNetsdkDemoDlg::OnBtnSensor() 
{
	// TODO: Add your control notification handler code here
	CAlarmDlg dlg(NULL,m_u32DevHandle);
	dlg.DoModal();
}

// 视频服务器声卡音量控制
void CNetsdkDemoDlg::OnBtnAudio() 
{
	// TODO: Add your control notification handler code here
	CAudioDlg dlg(NULL,m_u32DevHandle);
	dlg.DoModal();
}

// 前端录像管理
void CNetsdkDemoDlg::OnBtnDevRec() 
{
	// TODO: Add your control notification handler code here
	CDevRecordDlg dlg(NULL,m_u32DevHandle);
	dlg.DoModal();
}

// 轨迹管理
void CNetsdkDemoDlg::OnBtnPtzTrack() 
{
	// TODO: Add your control notification handler code here
	CTrackDlg dlg(NULL,m_u32DevHandle);
	dlg.DoModal();
}


// 报警中心配置
void CNetsdkDemoDlg::OnBtnAc() 
{
	// TODO: Add your control notification handler code here
	CACDlg dlg(NULL,m_u32DevHandle);
	dlg.DoModal();
}

// 邮件服务器
void CNetsdkDemoDlg::OnBtnEmail() 
{
	// TODO: Add your control notification handler code here
	CEmailDlg dlg(NULL,m_u32DevHandle);
	dlg.DoModal();
}

// FTP配置
void CNetsdkDemoDlg::OnBtnFtp() 
{
	// TODO: Add your control notification handler code here
	CFTPDlg dlg(NULL,m_u32DevHandle);
	dlg.DoModal();
}

// 探头输出配置
void CNetsdkDemoDlg::OnBtnSensorOut() 
{
	// TODO: Add your control notification handler code here
	CSensorOutDlg dlg(NULL,m_u32DevHandle);
	dlg.DoModal();
}

// 探头输入报警联动配置
void CNetsdkDemoDlg::OnBtnCaSensorIn() 
{
	// TODO: Add your control notification handler code here
	CCASensorInDlg dlg(NULL,m_u32DevHandle);
	dlg.DoModal();
}

// 报警联动录像配置
void CNetsdkDemoDlg::OnBtnRecord() 
{
	// TODO: Add your control notification handler code here
	CCARecordDlg dlg(NULL,m_u32DevHandle);
	dlg.DoModal();
}

// 移动侦测报警联动
void CNetsdkDemoDlg::OnBtnCaMd() 
{
	// TODO: Add your control notification handler code here
	CCAMDDlg dlg(NULL,m_u32DevHandle);
	dlg.DoModal();
}

// 视频丢失报警联动
void CNetsdkDemoDlg::OnBtnCaVl() 
{
	// TODO: Add your control notification handler code here
	CCAVLDlg dlg(NULL,m_u32DevHandle);
	dlg.DoModal();
}

// 前端录像文件搜索
void CNetsdkDemoDlg::OnBtnDevRecSearch() 
{
	// TODO: Add your control notification handler code here
	CDevRecSearchDlg dlg(NULL,m_u32DevHandle);
	dlg.DoModal();
}

void CNetsdkDemoDlg::OnBtnHs() 
{
	// TODO: Add your control notification handler code here
	CHsDlg dlg(NULL,m_u32DevHandle);
	dlg.DoModal();
}


void CNetsdkDemoDlg::OnButton3d() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
    if(m_u32DevHandle == 0)
    {
        uistrings[STR_ERR_NON_CONN].strings[g_nLangID];
        return;
    }

    m_videoWnd.EnableRegionSelector(TRUE);
    AfxMessageBox(uistrings[STR_3D].strings[g_nLangID]);
}

void CNetsdkDemoDlg::OnButtonDevchn() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
}

void CNetsdkDemoDlg::OnButton3dMode2() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
}


void CNetsdkDemoDlg::OnBtnVideoMask() 
{
	// TODO: Add your control notification handler code here
	CVideoMaskDlg dlg;
    dlg.m_lNetHandle = m_u32DevHandle;
	if (dlg.DoModal() == IDOK)
	{
	}
}

void CNetsdkDemoDlg::OnBtnBallVideoMask() 
{
	// TODO: Add your control notification handler code here
	CBallVideoMaskDlg dlg;
	dlg.m_lNetHandle = m_u32DevHandle;
	dlg.DoModal();
}



int CNetsdkDemoDlg::OnStreamFunc(unsigned int u32ChnHandle,/* 通道句柄 */
                                                            unsigned int u32DataType,/* 数据类型，详见STREAM_TYPE_E
                                                            0x01-视频，0x02-音频*/
                                                            unsigned char* pu8Buffer,/* 数据包含帧头 */
                                                            unsigned int u32Length,  /* 数据长度 */
                                                            NS_U64 u64TimeStamp,    /* 时间戳*/
                                                            NS_STREAM_INFO_S *pStreamInfo,/*码流属性*/
                                                            void* pUserData)        /* 用户数据*/
{
	static DWORD dwTickOld = GetTickCount();
	static BOOL bFirstVideoFrame = FALSE;

    int ret = 0;
    CNetsdkDemoDlg *pDlgPlay = (CNetsdkDemoDlg *)pUserData;

    if (!pDlgPlay->m_u32PlayerHandle)
    {
		
        ret = NS_PLAYER_Open(&pDlgPlay->m_u32PlayerHandle, (unsigned int)pDlgPlay->m_videoWnd.m_hWnd, &pDlgPlay->m_stStreamInfo);
        g_strChannel = pDlgPlay->m_strDVSChn;
		
		NS_PLAYER_ATTR stPlayerAttr;
		ZeroMemory(&stPlayerAttr, sizeof(NS_PLAYER_ATTR));
		stPlayerAttr.overlay = 0;
		stPlayerAttr.keycolor = COLORREF_BK_OVERLAY;
		stPlayerAttr.bufcount = 0;
		NS_PLAYER_SetAttr(pDlgPlay->m_u32PlayerHandle , &stPlayerAttr);

		NS_PLAYER_SetDrawCallback(pDlgPlay->m_u32PlayerHandle, OnDraw, pDlgPlay);
    }

    if (u32DataType == NS_STREAM_TYPE_VIDEO )//视频
    {
		// TRACE("%d bytes, %d\n", u32Length, (int)u64TimeStamp);
        if (pDlgPlay->m_u32PlayerHandle)
        {
			bFirstVideoFrame = TRUE;
            NS_PLAYER_InputData(pDlgPlay->m_u32PlayerHandle, u32DataType, pu8Buffer, u32Length, u64TimeStamp);
        }
        
        if (pDlgPlay->m_u32Mp4Handle)
        {
            ret = NS_MP4_Write(pDlgPlay->m_u32Mp4Handle, u32DataType, pu8Buffer, u32Length, u64TimeStamp);
        }

		if (pDlgPlay->m_u32VideoDecoderHandle)
		{
            ret = NS_VIDEODECODER_InputData(pDlgPlay->m_u32VideoDecoderHandle, u32DataType, pu8Buffer, u32Length, u64TimeStamp);
		}
    }
    if (u32DataType == NS_STREAM_TYPE_AUDIO )//视频
    {
        if (pDlgPlay->m_u32PlayerHandle && bFirstVideoFrame)
        {
            NS_PLAYER_InputData(pDlgPlay->m_u32PlayerHandle, u32DataType, pu8Buffer, u32Length, u64TimeStamp);
        }
        if (pDlgPlay->m_u32Mp4Handle)
        {
            ret = NS_MP4_Write(pDlgPlay->m_u32Mp4Handle, u32DataType, pu8Buffer, u32Length, u64TimeStamp);
        }
		if (pDlgPlay->m_u32AudioDecoderHandle)
		{
            ret = NS_AUDIODECODER_InputData(pDlgPlay->m_u32AudioDecoderHandle, u32DataType, pu8Buffer, u32Length, u64TimeStamp);
		}
    }
    else if (u32DataType == NS_STREAM_MD_ONLY)
    {
        pDlgPlay->PostMessage(WM_NS_ALARM, 0, u32DataType);
    }
    else if (u32DataType == NS_STREAM_SENSORIN_ONLY)
    {
        pDlgPlay->PostMessage(WM_NS_ALARM, 0, u32DataType);
    }
    else if (u32DataType == NS_STREAM_VIDEO_LOSS_ONLY)
    {
        pDlgPlay->PostMessage(WM_NS_ALARM, 0, u32DataType);
    }
    else
    {

    }

// 	DWORD dwTick = GetTickCount();
// 	TRACE("耗时 %d tick\n", dwTick - dwTickOld);
// 	dwTickOld = dwTick;

    return NS_SUCCESS;
}

int CNetsdkDemoDlg::OnTalkFunc(unsigned int u32DevHandle,/* 设备句柄 */
                      unsigned int u32DataType,/* 数据类型，详见STREAM_TYPE_E
                                               0x01-视频，0x02-音频*/
                                               unsigned char* pu8Buffer,/* 数据包含帧头 */
                                               unsigned int u32Length,  /* 数据长度 */
                                               NS_U64 u64TimeStamp,    /* 时间戳*/
                                               NS_STREAM_INFO_S *pStreamInfo,/*码流属性*/
                                               void* pUserData)        /* 用户数据*/
{
    return 0;
}

int CNetsdkDemoDlg::OnNetStatusFunc(unsigned int u32DevHandle, /* 设备句柄 */
                           NS_NETSTAT_E u32Event,     
                           void* pUserData)
{
    CNetsdkDemoDlg * pThis = (CNetsdkDemoDlg *)pUserData;

    if(pThis)
    {
        pThis->PostMessage(WM_NS_NETSTAT, u32DevHandle, u32Event);
    }
    return 0;
}

void CNetsdkDemoDlg::OnButtonConnect() 
{
	// TODO: Add your control notification handler code here
    OnButtonDisconnect();
    OnBtnPreviewStop();
    UpdateData();

	g_strChannel = "";

    NS_LOGIN_INFO_S loginInfo;
    ZeroMemory(&loginInfo, sizeof(NS_LOGIN_INFO_S));
    strcpy(loginInfo.szHost, m_strDVSAddr);
    strcpy(loginInfo.szUsername, m_strUser);
    strcpy(loginInfo.szPassword, m_strPassword);
    strcpy(loginInfo.szDevChn, m_strDVSChn);
    loginInfo.u16Port = m_nPort;
    loginInfo.s32ConnectTimeout = 5;
    loginInfo.cbEventCallBack = OnNetStatusFunc;
    loginInfo.pUserData = this;
    
	TRACE("登录设备\n");

    int nType = m_cmbType.GetCurSel();
    loginInfo.stNetProtocol.eSocketType = (NET_SOCKET_TYPE_E)nType;
    int ret = NS_NET_Login(&m_u32DevHandle, &loginInfo);
    if (ret != NS_SUCCESS)
    {
        return;
    }
    
    unsigned int size = 0;
    NS_SERVER_INFO_S cfg;
    ZeroMemory(&cfg, sizeof(cfg));
    if(NS_NET_GetServerConfig(m_u32DevHandle, g_strChannel, NS_CMD_GET_SERVER_INFO, &cfg, &size) != 0)
    {
        AfxMessageBox("Get system info Failed.");
        return ;
    }
    
    if (cfg.channelnum == 0)
    {
        AfxMessageBox("Get channel info Failed.");
        return ;
    }

    if (m_strDVSAddr != m_strDVSAddrOld)
    {
        m_strDVSAddrOld = m_strDVSAddr;

        m_cmboChannel.ResetContent();
        for (int i=0; i<cfg.channelnum; i++)
        {
            m_cmboChannel.AddString(cfg.channels[i]);
        }
        SetDlgItemText(IDC_COMBO_CHANNEL, cfg.channels[0]);
    }
	
    if(m_u32DevHandle)
    {
		g_u32DevHandle = m_u32DevHandle;

        unsigned int size = 0;
        NS_CA_AO_INFO_S cfg;
        ZeroMemory(&cfg, sizeof(cfg));
        if(NS_NET_GetServerConfig(m_u32DevHandle, g_strChannel, NS_CMD_GET_CA_AO_INFO, &cfg, &size) != 0)
        {
            AfxMessageBox("Get sensor out info Failed.");
            return ;
        }
        m_btnSensor1.SetCheck(cfg.ao0);
        m_btnSensor2.SetCheck(cfg.ao1);
    }

    KillTimer(TIMER_CONNECT);
    OnBtnPreviewStart();
}

void CNetsdkDemoDlg::OnButtonDisconnect() 
{
	// TODO: Add your control notification handler code here
    KillTimer(TIMER_CONNECT);

    OnBtnPreviewStop();
	if (m_u32DevHandle)
	{
        NS_NET_Logout(m_u32DevHandle);
        m_u32DevHandle = 0;
	}
}

void CNetsdkDemoDlg::OnTimer(UINT_PTR nIDEvent)
{
    // TODO: Add your message handler code here and/or call default
    if (nIDEvent == TIMER_CONNECT)
    {
        OnButtonConnect();
    }
    else if (nIDEvent == TIMER_DISCONNECT)
    {
        KillTimer(TIMER_CONNECT);
        SetTimer(TIMER_CONNECT , 3000, NULL);
        OnBtnPreviewStop();
        if (m_u32DevHandle)
        {
            NS_NET_Logout(m_u32DevHandle);
            m_u32DevHandle = 0;
        }
    }
    else
    {

    }


    CDialog::OnTimer(nIDEvent);
}

void CNetsdkDemoDlg::DealPtz(int nPTZType,BOOL bStart)
{
    NS_PTZ_CMD_S cmd;
    cmd.dwSize = sizeof(NS_PTZ_CMD_S);
    cmd.speed = 50;
    cmd.bStep = FALSE;
    cmd.bStart = bStart;
    NS_NET_PTZControl(m_u32DevHandle, nPTZType, &cmd, cmd.dwSize);
    return ;
}

// 处理云台控制按钮弹起消息
HRESULT CNetsdkDemoDlg::OnBtnMessage(WPARAM wParam,LPARAM lParam)
{
    CWaitCursor wait;		// 显示等待光标

    HWND hWndBtn	= (HWND)wParam;
    UINT nMessageID = (UINT)lParam;

    if(nMessageID == WM_LBUTTONDOWN)
    {
        if(hWndBtn == GetDlgItem(IDC_BTN_PTZ_UP)->m_hWnd)
            DealPtz(NS_CMD_PTZ_UP,TRUE);
        else if(hWndBtn == GetDlgItem(IDC_BTN_PTZ_DOWN)->m_hWnd)
            DealPtz(NS_CMD_PTZ_DOWN,TRUE);
        else if(hWndBtn == GetDlgItem(IDC_BTN_PTZ_LEFT)->m_hWnd)
            DealPtz(NS_CMD_PTZ_LEFT,TRUE);
        else if(hWndBtn == GetDlgItem(IDC_BTN_PTZ_RIGHT)->m_hWnd)
            DealPtz(NS_CMD_PTZ_RIGHT,TRUE);
        else if(hWndBtn == GetDlgItem(IDC_BUTTON_RIGHTUP)->m_hWnd)
            DealPtz(NS_CMD_PTZ_RIGHT_UP,TRUE);
        else if(hWndBtn == GetDlgItem(IDC_BUTTON_RIGHTDOWN)->m_hWnd)
            DealPtz(NS_CMD_PTZ_RIGHT_DOWN,TRUE);
        else if(hWndBtn == GetDlgItem(IDC_BUTTON_LEFTUP)->m_hWnd)
            DealPtz(NS_CMD_PTZ_LEFT_UP,TRUE);
        else if(hWndBtn == GetDlgItem(IDC_BUTTON_LEFTDOWN)->m_hWnd)
            DealPtz(NS_CMD_PTZ_LEFT_DOWN,TRUE);
        else if(hWndBtn == GetDlgItem(IDC_BTN_PTZ_ZOOM_ADD)->m_hWnd)
            DealPtz(NS_CMD_PTZ_ZOOM_ADD,TRUE);
        else if(hWndBtn == GetDlgItem(IDC_BTN_PTZ_ZOOM_SUB)->m_hWnd)
            DealPtz(NS_CMD_PTZ_ZOOM_SUB,TRUE);
        else if(hWndBtn == GetDlgItem(IDC_BTN_PTZ_FOCUS_ADD)->m_hWnd)
            DealPtz(NS_CMD_PTZ_FOCUS_ADD,TRUE);
        else if(hWndBtn == GetDlgItem(IDC_BTN_PTZ_FOCUS_SUB)->m_hWnd)
            DealPtz(NS_CMD_PTZ_FOCUS_SUB,TRUE);
        else if(hWndBtn == GetDlgItem(IDC_BTN_PTZ_IRISA_ADD)->m_hWnd)
            DealPtz(NS_CMD_PTZ_IRIS_ADD,TRUE);
        else if(hWndBtn == GetDlgItem(IDC_BTN_PTZ_IRISA_SUB)->m_hWnd)
            DealPtz(NS_CMD_PTZ_IRIS_SUB,TRUE);
    }
    else if(nMessageID == WM_LBUTTONUP)
    {
        if(hWndBtn == GetDlgItem(IDC_BTN_PTZ_UP)->m_hWnd)
            DealPtz(NS_CMD_PTZ_UP,FALSE);
        else if(hWndBtn == GetDlgItem(IDC_BTN_PTZ_DOWN)->m_hWnd)
            DealPtz(NS_CMD_PTZ_DOWN,FALSE);
        else if(hWndBtn == GetDlgItem(IDC_BTN_PTZ_LEFT)->m_hWnd)
            DealPtz(NS_CMD_PTZ_LEFT,FALSE);
        else if(hWndBtn == GetDlgItem(IDC_BTN_PTZ_RIGHT)->m_hWnd)
            DealPtz(NS_CMD_PTZ_RIGHT,FALSE);
        else if(hWndBtn == GetDlgItem(IDC_BUTTON_RIGHTUP)->m_hWnd)
            DealPtz(NS_CMD_PTZ_RIGHT_UP,FALSE);
        else if(hWndBtn == GetDlgItem(IDC_BUTTON_RIGHTDOWN)->m_hWnd)
            DealPtz(NS_CMD_PTZ_RIGHT_DOWN,FALSE);
        else if(hWndBtn == GetDlgItem(IDC_BUTTON_LEFTUP)->m_hWnd)
            DealPtz(NS_CMD_PTZ_LEFT_UP,FALSE);
        else if(hWndBtn == GetDlgItem(IDC_BUTTON_LEFTDOWN)->m_hWnd)
            DealPtz(NS_CMD_PTZ_LEFT_DOWN,FALSE);
        else if(hWndBtn == GetDlgItem(IDC_BTN_PTZ_ZOOM_ADD)->m_hWnd)
            DealPtz(NS_CMD_PTZ_ZOOM_ADD,FALSE);
        else if(hWndBtn == GetDlgItem(IDC_BTN_PTZ_ZOOM_SUB)->m_hWnd)
            DealPtz(NS_CMD_PTZ_ZOOM_SUB,FALSE);
        else if(hWndBtn == GetDlgItem(IDC_BTN_PTZ_FOCUS_ADD)->m_hWnd)
            DealPtz(NS_CMD_PTZ_FOCUS_ADD,FALSE);
        else if(hWndBtn == GetDlgItem(IDC_BTN_PTZ_FOCUS_SUB)->m_hWnd)
            DealPtz(NS_CMD_PTZ_FOCUS_SUB,FALSE);
        else if(hWndBtn == GetDlgItem(IDC_BTN_PTZ_IRISA_ADD)->m_hWnd)
            DealPtz(NS_CMD_PTZ_IRIS_ADD,FALSE);
        else if(hWndBtn == GetDlgItem(IDC_BTN_PTZ_IRISA_SUB)->m_hWnd)
            DealPtz(NS_CMD_PTZ_IRIS_SUB,FALSE);

    }
    else if(nMessageID == WM_RBUTTONUP)
    {
    }
    return 0;
}

void CNetsdkDemoDlg::OnVideoWndMsg(UINT nMsg, LPVOID pParam, DWORD dwSize, PVOID pUserData)
{
    CNetsdkDemoDlg * pDlg = (CNetsdkDemoDlg*) pUserData;

    if (pDlg)
    {
        pDlg->HandleVideoWndMsg(nMsg, pParam, dwSize);
    }
}

void CNetsdkDemoDlg::HandleVideoWndMsg(UINT nMsg, LPVOID pParam, DWORD dwSize)
{
    if (nMsg == VIDEO_WND_MSG_LBUTTON_DBL_CLK)
    {
        VIDEO_WND_LBUTTON_DBL_CLK_POINT_T point;

        memcpy(&point, pParam, sizeof(VIDEO_WND_LBUTTON_DBL_CLK_POINT_T) );
        int ret = NS_NET_PTZ_DirectTo(m_u32DevHandle, 0, point.vw, point.vh, point.x, point.y, 0, 0);
    }
    else if (nMsg == VIDEO_WND_MSG_REGION_SELECT)
    {
        VIDEO_WND_REGION_T rgn;

        memcpy(&rgn, pParam, sizeof(VIDEO_WND_REGION_T) );
        int ret = NS_NET_PTZ_DirectTo(m_u32DevHandle, rgn.zoom, rgn.vw, rgn.vh, rgn.x, rgn.y, rgn.w, rgn.h);
    }
}

void CNetsdkDemoDlg::OnBnClickedButtonPtz20()
{
    // TODO: Add your control notification handler code here
	m_ptz20Dlg.ShowWindow(SW_SHOW);
    m_ptz20Dlg.CenterWindow();
}

void CNetsdkDemoDlg::OnButtonPlayback() 
{
	// TODO: Add your control notification handler code here
	OnBtnPreviewStop();

	NS_MP4_FILE_INFO_S mp4Info;
	ZeroMemory(&mp4Info ,sizeof(NS_MP4_FILE_INFO_S));
	ZeroMemory(&m_stStreamInfo ,sizeof(NS_STREAM_INFO_S));

	int ret = NS_PLAYBACK_StartPlay(&m_pu32Mp4ReaderHandle, "c:\\ns_mp4.mp4", &mp4Info, &m_stStreamInfo, OnStreamFunc, this);
}

NS_PLAY_SPEED_E ConvertSpeed(double speed)
{
	NS_PLAY_SPEED_E d = NS_PLAY_SPEED_NORMAL;
	if (speed == 1.0)
	{
		return NS_PLAY_SPEED_NORMAL;
	}
	else if (speed == 2.0)
	{
		return NS_PLAY_SPEED_FAST_2;
	}
	else if (speed == 4.0)
	{
		return NS_PLAY_SPEED_FAST_4;
	}
	else if (speed == 8.0)
	{
		return NS_PLAY_SPEED_FAST_8;
	}
	else if (speed == 16.0)
	{
		return NS_PLAY_SPEED_FAST_16;
	}
	else if (speed == 32.0)
	{
		return NS_PLAY_SPEED_FAST_32;
	}
	else if (speed == 0.5)
	{
		return NS_PLAY_SPEED_SLOW_2;
	}
	else if (speed == 0.25)
	{
		return NS_PLAY_SPEED_SLOW_4;
	}
	else if (speed == 0.125)
	{
		return NS_PLAY_SPEED_SLOW_8;
	}
	else if (speed == 0.0625)
	{
		return NS_PLAY_SPEED_SLOW_16;
	}
	else if (speed == 0.03125)
	{
		return NS_PLAY_SPEED_SLOW_32;
	}
	return d;
}

void CNetsdkDemoDlg::OnButtonPlaybackSlow() 
{
	// TODO: Add your control notification handler code here
	if (m_speed <= 1.0/32)
	{
		return;
	}

	int ret = 0;
	m_speed /= 2;
	if (m_pu32Mp4ReaderHandle)
	{
		 ret = NS_PLAYBACK_SetSpeed(m_pu32Mp4ReaderHandle, ConvertSpeed(m_speed) );
	}
}

void CNetsdkDemoDlg::OnButtonPlaybackFast() 
{
	// TODO: Add your control notification handler code here
	if (m_speed >= 32.0)
	{
		return;
	}
	
	int ret = 0;
	m_speed *= 2;
	if (m_pu32Mp4ReaderHandle)
	{
		ret = NS_PLAYBACK_SetSpeed(m_pu32Mp4ReaderHandle, ConvertSpeed(m_speed) );
	}
}

void CNetsdkDemoDlg::OnButtonPlaybackPause() 
{
	// TODO: Add your control notification handler code here
	int ret = 0;
	if (m_pu32Mp4ReaderHandle)
	{
		ret = NS_PLAYBACK_Pause(m_pu32Mp4ReaderHandle);
	}
}

void CNetsdkDemoDlg::OnButtonPlaybackSeek() 
{
	// TODO: Add your control notification handler code here
	int ret = 0;
	if (m_pu32Mp4ReaderHandle)
	{
		ret = NS_PLAYBACK_SetPlayPos(m_pu32Mp4ReaderHandle, 15.0);
	}
}

void CNetsdkDemoDlg::OnRadioChs() 
{
	// TODO: Add your control notification handler code here
	SelectUI();
}

void CNetsdkDemoDlg::OnRadioEng() 
{
	// TODO: Add your control notification handler code here
	SelectUI();
}

ui_string_t uistrings[] =
{
	{STR_SUCCESS,	{_T("成功"), _T("Success")} },
	{STR_FAIL,		{_T("失败"), _T("Fail")} },
	{STR_SET_VM_FAIL, { _T("设置视频遮挡信息失败，请检查是否是球机."), _T("Failed.   Please check if it is a ball camera")} },
	{STR_FILE_NAME, { _T("文件名称"), _T("File Name") }},
	{STR_PARTITION, { _T("磁盘分区"), _T("Partition") }},
	{STR_SPACE_TOTAL, { _T("总容量"), _T("Space Total") }},
	{STR_SPACE_LEFT, { _T("剩余容量"), _T("Space Left") }},
	{STR_PRESET_ID, { _T("预置位ID"), _T("Preset ID") }},
	{STR_PRESET_NAME, { _T("预置位名称"), _T("Preset Name") }},
	{STR_USER_NAME, { _T("用户名称"), _T("User") }},
	{STR_USER_GROUP, { _T("用户组"), _T("Group") }},
	{STR_GROUP_ADMIN, { _T("管理员"), _T("Admin") }},
	{STR_GROUP_OPER, { _T("操作员"), _T("Operator") }},
	{STR_GROUP_GUEST, { _T("普通"), _T("Guest") }},
	{STR_ERR_CONNECT, { _T("连接失败"), _T("Failed to connect") }},
	{STR_ERR_PASSWORD, { _T("用户或密码错误"), _T("Error user or password") }},
	{STR_ERR_DISCONN, { _T("网络连接断开"), _T("Disconnected") }},
	{STR_ALARM_MD, { _T("移动报警"), _T("Motion Detection") }},
	{STR_ALARM_IN, { _T("探头报警"), _T("Alarm In") }},
	{STR_ALARM_VL, { _T("视频丢失报警"), _T("Video Loss") }},
	{STR_ERR_NON_CONN, { _T("请先连接设备"), _T("Not connected") }},
	{STR_3D, { _T("操作方法：在视频窗口上双击 或者 鼠标左键拖动"), _T("Double click or drag and drop to operate") }},
	{STR_TRACK_ID, { _T("序号"), _T("ID") }},
	{STR_TRACK_PRESET, { _T("预置点"), _T("Preset") }},
	{STR_TRACK_INTERVAL, { _T("停留时间"), _T("Stay Time") }},

	{STR_DEV_REC_STATUS_IDLE, { _T("空闲"), _T("Idle") }},
	{STR_DEV_REC_STATUS_MANUAL, { _T("手动录像"), _T("Manual record") }},
	{STR_DEV_REC_STATUS_ALARM, { _T("报警录像"), _T("Alarm record") }},
	{STR_DEV_REC_STATUS_MD, { _T("移动报警录像"), _T("MD alarm record") }},
	{STR_DEV_REC_STATUS_SCHE, { _T("定时录像"), _T("Schedule record") }},
	{STR_DEV_REC_STATUS_SNAP, { _T("抓拍"), _T("Snap") }},

	{STR_TIME_ZONE_1, { _T("(GMT-12:00) 国际日期变更线西"), _T("(GMT-12:00)") }},
	{STR_TIME_ZONE_2, { _T("(GMT-11:00) 中途岛 , 萨摩亚群岛"), _T("(GMT-11:00)") }},
	{STR_TIME_ZONE_3, { _T("(GMT-10:00) 夏威夷"), _T("(GMT-10:00)") }},
	{STR_TIME_ZONE_4, { _T("(GMT-09:00) 阿拉斯加"), _T("(GMT-09:00)") }},
	{STR_TIME_ZONE_5, { _T("(GMT-08:00) 太平洋时间(美国和加拿大); 蒂华纳"), _T("(GMT-08:00)") }},
	{STR_TIME_ZONE_6, { _T("(GMT-07:00) 山地时间(美国和加拿大)"), _T("(GMT-07:00)") }},
	{STR_TIME_ZONE_7, { _T("(GMT-06:00) 中部时间(美国和加拿大); 萨斯喀彻温;瓜达拉哈拉,墨西哥城,蒙特雷; 中美洲"), _T("(GMT-06:00)") }},
	{STR_TIME_ZONE_8, { _T("(GMT-05:00) 波哥大,利马,基多"), _T("(GMT-05:00)") }},
	{STR_TIME_ZONE_9, { _T("(GMT-05:00) 东部时间(加拿大和美国); 印第安纳州(东部)"), _T("(GMT-05:00)") }},
	{STR_TIME_ZONE_10, { _T("(GMT-04:00) 大西洋标准时间(美国 &amp;加拿大), 卡拉卡斯(委内瑞拉首都), 拉巴斯"), _T("(GMT-04:00)") }},
	{STR_TIME_ZONE_11, { _T("(GMT-03:30) 纽芬兰"), _T("(GMT-12:00)") }},
	{STR_TIME_ZONE_12, { _T("(GMT-03:00) 布宜诺斯艾利斯(阿根廷首都), 乔治城, 巴西利亚"), _T("(GMT-03:30)") }},
	{STR_TIME_ZONE_13, { _T("(GMT-02:00) 中部-阿根廷"), _T("(GMT-02:00)") }},
	{STR_TIME_ZONE_14, { _T("(GMT-01:00) 亚速尔群岛, 德总角"), _T("(GMT-01:00)") }},
	{STR_TIME_ZONE_15, { _T("(GMT)       卡萨布兰卡市,蒙罗维亚,都柏林,爱丁堡,里斯本(葡萄牙首都),伦敦"), _T("(GMT)") }},
	{STR_TIME_ZONE_16, { _T("(GMT+01:00) 阿姆斯特丹, 柏林, 伯恩, 罗马, 斯德哥尔摩, 维也纳"), _T("(GMT+01:00)") }},
	{STR_TIME_ZONE_17, { _T("(GMT+01:00) 贝尔格来德, 布拉迪斯拉发, 布达佩斯, 炉布尔雅那, 布拉格"), _T("(GMT+01:00)") }},
	{STR_TIME_ZONE_18, { _T("(GMT+01:00) 布鲁塞尔, 哥本哈根, 马德里, 巴黎, 维尔纽斯"), _T("(GMT+01:00)") }},
	{STR_TIME_ZONE_19, { _T("(GMT+01:00) 萨拉热窝, 斯科普里, 索非亚, 华沙, 札格拉布"), _T("(GMT+01:00)") }},
	{STR_TIME_ZONE_20, { _T("(GMT+02:00) 雅典, 布加勒斯特, 开罗, 伊斯坦布尔, 明斯克"), _T("(GMT+02:00)") }},
	{STR_TIME_ZONE_21, { _T("(GMT+02:00) 哈拉雷，赫尔辛基"), _T("(GMT+02:00)") }},
	{STR_TIME_ZONE_22, { _T("(GMT+03:00) 莫斯科,圣彼得堡,窝瓦河,巴格达,科威特,利雅德"), _T("(GMT+03:00)") }},
	{STR_TIME_ZONE_23, { _T("(GMT+03:30) 德黑兰"), _T("(GMT+03:00)") }},
	{STR_TIME_ZONE_24, { _T("(GMT+04:00) 阿布达比, 巴库, 马斯喀特, 第比利斯"), _T("(GMT+04:00)") }},
	{STR_TIME_ZONE_25, { _T("(GMT+04:30) 喀布尔"), _T("(GMT+04:30)") }},
	{STR_TIME_ZONE_26, { _T("(GMT+05:00) 凯撒琳镇, 伊斯兰马巴德, 克拉啻港市, 塔什干"), _T("(GMT+05:00)") }},
	{STR_TIME_ZONE_27, { _T("(GMT+05:30) 新德里"), _T("(GMT+05:30)") }},
	{STR_TIME_ZONE_28, { _T("(GMT+06:00) 亚斯塔蒂, 阿曼蒂, 可伦波, 狄哈卡"), _T("(GMT+06:00)") }},
	{STR_TIME_ZONE_29, { _T("(GMT+07:00) 曼谷, 河内, 雅加达"), _T("(GMT+07:00)") }},
	{STR_TIME_ZONE_30, { _T("(GMT+08:00) 北京, 香港, 新加坡, 台北"), _T("(GMT+08:00)") }},
	{STR_TIME_ZONE_31, { _T("(GMT+09:00) 汉城, 东京, 亚库次客"), _T("(GMT+09:00)") }},
	{STR_TIME_ZONE_32, { _T("(GMT+09:30) 爱得莱德, 达尔文"), _T("(GMT+09:30)") }},
	{STR_TIME_ZONE_33, { _T("(GMT+10:00) 坎培拉, 关岛, 摩尔斯比港, 海蔘威"), _T("(GMT+10:00)") }},
	{STR_TIME_ZONE_34, { _T("(GMT+11:00) 麦哲伦, 所罗门岛"), _T("(GMT+11:00)") }},
	{STR_TIME_ZONE_35, { _T("(GMT+12:00) 斐济, 勘查加半岛, 马绍尔群岛, 威尔尼顿"), _T("(GMT+12:00)") }},
};

int g_nLangID = 0;
void CNetsdkDemoDlg::InitUI()
{
// 	//强制英文版
// 	m_nLauguage = 1;
// 	GetDlgItem(IDC_STATIC_LANG)->ShowWindow(SW_HIDE);
// 	GetDlgItem(IDC_RADIO_CHS)->ShowWindow(SW_HIDE);
// 	GetDlgItem(IDC_RADIO_ENG)->ShowWindow(SW_HIDE);

	LCID lcid=2052;
	if(1 == m_nLauguage)
	{
		lcid=1033;

		GetDlgItem(IDC_BUTTON_PTZ20)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_WA_IMAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_ENCRYPT_STR)->ShowWindow(SW_HIDE);
		g_nLangID = 1;
	}
	else
	{
		GetDlgItem(IDC_BUTTON_PTZ20)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_WA_IMAGE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_ENCRYPT_STR)->ShowWindow(SW_SHOW);
		g_nLangID = 0;
	}

	theApp.m_lang.Clear();
	theApp.m_lang.InitLangResource("LANG",lcid);
	theApp.m_lang.TransDialog(m_hWnd, IDD);
}

void CNetsdkDemoDlg::SelectUI()
{
	UpdateData();
	theApp.WriteProfileInt("Setting", "LANG", m_nLauguage);
	theApp.m_lang.TransDialog(m_hWnd, IDD);
	InitUI();
}

void CNetsdkDemoDlg::OnButtonWaImage() 
{
	// TODO: Add your control notification handler code here
	CWADlg dlg;
    dlg.m_lNetHandle = m_u32DevHandle;
	if (dlg.DoModal() == IDOK)
	{
	}
}

void CNetsdkDemoDlg::OnButtonEncryptStr() 
{
	// TODO: Add your control notification handler code here
	CEncryptStrDlg dlg;
    dlg.m_lNetHandle = m_u32DevHandle;
	if (dlg.DoModal() == IDOK)
	{
	}
}

void pgm_save(unsigned char *buf,int wrap, int xsize,int ysize, const char *recfilename)
{
	FILE *f;
	int i;
	
	int ci=0;
	
	static int framenum =0;
	
	
	f=fopen(recfilename,"ab+");   
	
	for(i=0;i<ysize;i++)
	{
		fwrite(buf + i * wrap, 1, xsize, f );
		
	}
	fclose(f);
}

int CNetsdkDemoDlg::OnVideoDecoderData(unsigned int nWidth,	/* 宽度*/
									   unsigned int nHeight,	/* 高度*/
										unsigned char *in_Y,	/* Y分量*/
									   unsigned int nYStride,	/* Y分量跨度*/
									   unsigned char *in_U,	/* U分量*/
									   int nUStride,			/* U分量跨度*/
									   unsigned char *in_V,	/* V分量*/
									   int nVStride,			/* V分量跨度*/
									   NS_U64 u64TimeStamp,
									   void* pUserData)        /* 用户数据*/
{
	/*yuv文件可用elecard查看*/
	const char * outrecfilename = "c:\\ns_net.yuv";

	CNetsdkDemoDlg * pThis = (CNetsdkDemoDlg *)pUserData;
	if (pThis)
	{
		if (pThis->m_nFrameSaved == 0)
		{
			::DeleteFile(outrecfilename);
		}

		if (pThis->m_nFrameSaved++ < 50)
		{

			pgm_save(in_Y, nYStride,
				nWidth, nHeight,  outrecfilename);
			pgm_save(in_U, nUStride,
				nWidth/2, nHeight/2,  outrecfilename);
			pgm_save(in_V, nVStride,
				nWidth/2, nHeight/2,  outrecfilename);
		}
		else
		{
			NS_VIDEODECODER_Close(pThis->m_u32VideoDecoderHandle);
			NS_DECODER_DeInit();
		}
	}

	return 0;
}

void CNetsdkDemoDlg::OnButtonVideodecoder() 
{
	// TODO: Add your control notification handler code here
	if (m_u32StreamHandle)
	{
		m_nFrameSaved = 0;
		NS_DECODER_Init();
		if (NS_VIDEODECODER_Open(&m_u32VideoDecoderHandle, m_stStreamInfo.struVencChAttr.enVideoFormat, OnVideoDecoderData, this) == NS_SUCCESS)
		{
		}
	}
}

int CNetsdkDemoDlg::OnAudioDecoderData(
									   unsigned char * pu8Buffer,	/* PCM数据*/
									   unsigned int u32Length,	/* PCM数据长度*/
									   NS_U64 u64TimeStamp,
										void* pUserData)       /* 用户数据*/
{
	/*pcm文件可用mplayer播放: mplayer  -demuxer rawaudio -rawaudio rate=8000:channels=1 ns_net.pcm*/
	const char * outrecfilename = "c:\\ns_net.pcm";
	
	CNetsdkDemoDlg * pThis = (CNetsdkDemoDlg *)pUserData;
	if (pThis)
	{
		if (pThis->m_nFrameSaved == 0)
		{
			::DeleteFile(outrecfilename);
		}
		
		if (pThis->m_nSampleSaved++ < 5000)
		{
			FILE *f;
			f=fopen(outrecfilename,"ab+");   
			if (f)
			{
				fwrite(pUserData, 1, u32Length, f);
				fclose(f);
			}
		}
		else
		{
			NS_VIDEODECODER_Close(pThis->m_u32VideoDecoderHandle);
			NS_DECODER_DeInit();
		}
	}
	
	return 0;
}

void CNetsdkDemoDlg::OnButtonAudiodecoder() 
{
	// TODO: Add your control notification handler code here
	if (m_u32StreamHandle)
	{
		m_nSampleSaved = 0;
		NS_DECODER_Init();
		if (NS_AUDIODECODER_Open(&m_u32AudioDecoderHandle, m_stStreamInfo.struAencChAttr.enAudioFormat, OnAudioDecoderData, this) == NS_SUCCESS)
		{
		}
	}
}
