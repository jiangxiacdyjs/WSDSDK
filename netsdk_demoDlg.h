// JSNetDemoDlg.h : header file
//

#if !defined(AFX_JSNETDEMODLG_H__BBC2F56C_FA93_4BB5_9EBA_6E5A92691384__INCLUDED_)
#define AFX_JSNETDEMODLG_H__BBC2F56C_FA93_4BB5_9EBA_6E5A92691384__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/////////////////////////////////////////////////////////////////////////////
// CNetsdkDemoDlg dialog
#pragma comment(lib, "ns_net.lib")
#pragma comment(lib, "ns_player.lib")

#include "SearchDevDlg.h"
#include "VideoWndBase.h"
#include "PTZ20Dlg.h"

#define WM_NS_NETSTAT           WM_USER + 1
#define WM_NS_BTN_MESSAGE       WM_USER + 2
#define WM_NS_ALARM             WM_USER + 3

class CButtonEx : public CButton
{
public:
    void    SetParentMessage(BOOL bSendMessageToParent,HWND hWndParent)
    {
        if(bSendMessageToParent)
        {
            m_bSendMessageToParent = bSendMessageToParent;
            m_hWndParent = hWndParent;
        }
    }

    // Operations
public:

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CBmpButton)
protected:
    virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
    {
        static BOOL bDown = FALSE;

        if(message == WM_LBUTTONDBLCLK)
            message = WM_LBUTTONDOWN;

        switch(message)
        {
        case WM_RBUTTONUP:
            if(m_bSendMessageToParent && IsWindow(m_hWndParent))
            {
                ::SendMessage(m_hWndParent,WM_NS_BTN_MESSAGE,(WPARAM)m_hWnd,(LPARAM)WM_RBUTTONUP);
            }
            break;
        case WM_LBUTTONDOWN:
            {
                bDown		= TRUE;
                m_bLDown	= TRUE;

                RECT rc;
                GetClientRect(&rc);
                int x, y;
                x = LOWORD( lParam );
                y = HIWORD( lParam );
                POINT pt = {x, y};
                if( ::PtInRect(&rc, pt) )
                {
                    if(m_bSendMessageToParent && IsWindow(m_hWndParent))
                    {
                        ::SendMessage(m_hWndParent,WM_NS_BTN_MESSAGE,(WPARAM)m_hWnd,(LPARAM)WM_LBUTTONDOWN);
                    }
                }	
            }
            break;
        case WM_LBUTTONUP:
            if(bDown && m_bIsCheckStyle)
            {
                bDown = FALSE;
                RECT rc;
                GetClientRect(&rc);
                int x, y;
                x = LOWORD( lParam );
                y = HIWORD( lParam );
                POINT pt = {x, y};
                if( ::PtInRect(&rc, pt) )
                {
                    m_bIsChecked = !m_bIsChecked;
                }
            }

            m_bLDown = FALSE;

            if(m_bSendMessageToParent && IsWindow(m_hWndParent))
            {
                ::SendMessage(m_hWndParent,WM_NS_BTN_MESSAGE,(WPARAM)m_hWnd,(LPARAM)WM_LBUTTONUP);
            }

            break;
        }

        return CButton::DefWindowProc(message, wParam, lParam);
    }
    //}}AFX_VIRTUAL

    // Implementation
public:
    CButtonEx()
    {
        m_bIsCheckStyle			= FALSE;
        m_bIsChecked			= FALSE;
        m_bLDown				= FALSE;
        m_bSendMessageToParent	= FALSE;
        m_hWndParent			= NULL;	
    }

    virtual ~CButtonEx()
    {

    }


public:
    //{{AFX_MSG(CBmpButton)
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()

protected:
    BOOL		m_bLDown ;
    BOOL		m_bSendMessageToParent;
    HWND		m_hWndParent;
    BOOL        m_bIsCheckStyle;
    BOOL        m_bIsChecked;
};

class CNetsdkDemoDlg : public CDialog
{
public:
	CFont		m_font;
    CPTZ20Dlg m_ptz20Dlg;

    NS_STREAM_INFO_S m_stStreamInfo;
    unsigned int m_u32DevHandle; 
    unsigned int m_u32StreamHandle; 
    unsigned int m_u32PlayerHandle; 
    unsigned int m_u32Mp4Handle;
	unsigned int m_pu32Mp4ReaderHandle;
	unsigned int m_u32VideoDecoderHandle;
	unsigned int m_u32AudioDecoderHandle;

	double		m_speed;
    static int OnStreamFunc(unsigned int u32ChnHandle,/* 通道句柄 */
                                                      unsigned int u32DataType,/* 数据类型，详见STREAM_TYPE_E
                                                      0x01-视频，0x02-音频*/
                                                      unsigned char* pu8Buffer,/* 数据包含帧头 */
                                                      unsigned int u32Length,  /* 数据长度 */
                                                      NS_U64 u64TimeStamp,    /* 时间戳*/
                                                      NS_STREAM_INFO_S *pStreamInfo,/*码流属性*/
                                                      void* pUserData);        /* 用户数据*/
    static int OnTalkFunc(unsigned int u32DevHandle,/* 设备句柄 */
        unsigned int u32DataType,/* 数据类型，详见STREAM_TYPE_E
                                 0x01-视频，0x02-音频*/
                                 unsigned char* pu8Buffer,/* 数据包含帧头 */
                                 unsigned int u32Length,  /* 数据长度 */
                                 NS_U64 u64TimeStamp,    /* 时间戳*/
                                 NS_STREAM_INFO_S *pStreamInfo,/*码流属性*/
                                 void* pUserData);        /* 用户数据*/

    static int OnSnapShotFunc(unsigned int u32PlayerHandle,/* 句柄 */
                                NS_SNAPSHOT_FORMAT_E format,
                                 unsigned char* pu8Buffer,/* 数据包含帧头 */
                                 unsigned int u32Length,  /* 数据长度 */
                                 void* pUserData);        /* 用户数据*/

    static int OnNetStatusFunc(unsigned int u32DevHandle, /* 设备句柄 */
        NS_NETSTAT_E u32Event,     
        void* pUserData);

    static int OnVideoDecoderData(unsigned int nWidth,	/* 宽度*/
		unsigned int nHeight,	/* 高度*/
		unsigned char *in_Y,	/* Y分量*/
		unsigned int nYStride,	/* Y分量跨度*/
		unsigned char *in_U,	/* U分量*/
		int nUStride,			/* U分量跨度*/
		unsigned char *in_V,	/* V分量*/
		int nVStride,			/* V分量跨度*/
		NS_U64 u64TimeStamp,
		void* pUserData);        /* 用户数据*/

    static int OnAudioDecoderData(
		unsigned char * pu8Buffer,	/* PCM数据*/
		unsigned int u32Length,	/* PCM数据长度*/
		NS_U64 u64TimeStamp,
		void* pUserData);        /* 用户数据*/

    static void OnVideoWndMsg(UINT nMsg, LPVOID pParam, DWORD dwSize, PVOID pUserData);
	static void __stdcall OnDraw(long h, HDC hDc, long lParam);
// Construction
public:
	CNetsdkDemoDlg(CWnd* pParent = NULL);	// standard constructor
		
protected:
    void        HandleVideoWndMsg(UINT nMsg, LPVOID pParam, DWORD dwSize);
	void        DealPtz(int nPTZType, BOOL bStart);
	BOOL		InitNetSDK();
	
// Dialog Data
	//{{AFX_DATA(CNetsdkDemoDlg)
	enum { IDD = IDD__DEMO_DIALOG };
	CStatic	m_stAssist;
	CButton		m_btnSensor2;
	CButton		m_btnSensor1;
	CButton		m_btnABC;
	CButton		m_btnAudioOut;
	CComboBox	m_cmbType;
	CStatic		m_stVideo;
	CString		m_strDVSAddr;
    CString		m_strDVSAddrOld;
	CString		m_strPassword;
	UINT		m_nPort;
	CString		m_strUser;
	int		m_nLauguage;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetsdkDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CNetsdkDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnPreviewStart();
	afx_msg void OnBtnPreviewStop();
	afx_msg void OnDestroy();
	afx_msg void OnBtnRecordStart();
	afx_msg void OnBtnRecordStop();
	afx_msg void OnBtnSnap();
	afx_msg void OnCheckAudioOut();
	afx_msg void OnBtnSearch();
	afx_msg void OnBtnPtzAuto();
	afx_msg void OnCheckAbc();
	afx_msg void OnBtnPtzPreset();
	afx_msg void OnCheckSensor1();
	afx_msg void OnCheckSensor2();
	afx_msg void OnBtnDevBps();
	afx_msg void OnBtnDevColor();
	afx_msg void OnBtnDevCom();
	afx_msg void OnBtnDevMd();
	afx_msg void OnBtnNet();
	afx_msg void OnBtnOsd();
	afx_msg void OnBtnSys();
	afx_msg void OnBtnPort();
	afx_msg void OnBtnTime();
	afx_msg void OnBtnUser();
	afx_msg void OnBtnVl();
	afx_msg void OnBtnUpdate();
	afx_msg void OnBtnSensor();
	afx_msg void OnBtnAudio();
	afx_msg void OnBtnDevRec();
	afx_msg void OnBtnPtzTrack();
	afx_msg void OnBtnPtzLightOpen();
	afx_msg void OnBtnPtzLightClose();
	afx_msg void OnBtnPtzBrushOpen();
	afx_msg void OnBtnPtzBrushClose();
	afx_msg void OnBtnAc();
	afx_msg void OnBtnEmail();
	afx_msg void OnBtnFtp();
	afx_msg void OnBtnSensorOut();
	afx_msg void OnBtnCaSensorIn();
	afx_msg void OnBtnCaMd();
	afx_msg void OnBtnCaVl();
	afx_msg void OnBtnRecord();
	afx_msg void OnBtnDevRecSearch();
	afx_msg void OnBtnHs();
	afx_msg void OnButton3d();
	afx_msg void OnButtonDevchn();
	afx_msg void OnButton3dMode2();
	afx_msg void OnBtnVideoMask();
	afx_msg void OnBtnBallVideoMask();
	afx_msg void OnButtonConnect();
	afx_msg void OnButtonDisconnect();
	afx_msg void OnButtonPlayback();
	afx_msg void OnButtonPlaybackSlow();
	afx_msg void OnButtonPlaybackFast();
	afx_msg void OnButtonPlaybackPause();
	afx_msg void OnButtonPlaybackSeek();
	afx_msg void OnRadioChs();
	afx_msg void OnRadioEng();
	afx_msg void OnButtonWaImage();
	afx_msg void OnButtonEncryptStr();
	afx_msg void OnButtonVideodecoder();
	afx_msg void OnButtonAudiodecoder();
	//}}AFX_MSG
	afx_msg HRESULT OnNetStatusMsg(WPARAM wParam,LPARAM lParam);
    afx_msg HRESULT OnAlarmMsg(WPARAM wParam,LPARAM lParam);
    afx_msg HRESULT OnBtnMessage(WPARAM wParam,LPARAM lParam);
	
	DECLARE_MESSAGE_MAP()

protected:
    BOOL    m_bAuto;	
public:
    CComboBox m_cmboChannel;
    CString m_strDVSChn;
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    CButtonEx m_btnLeftUp;
    CButtonEx m_btnLeft;
    CButtonEx m_btnRight;
    CButtonEx m_btnUp;
    CButtonEx m_btnDown;
    CButtonEx m_btnLeftDown;
    CButtonEx m_btnRightUp;
    CButtonEx m_btnRightDown;

    CButtonEx m_btnZoomAdd;
    CButtonEx m_btnZoomSub;
    CButtonEx m_btnFocusAdd;
    CButtonEx m_btnFocusSub;
    CButtonEx m_btnIrisAdd;
    CButtonEx m_btnIrisSub;

	int m_nFrameSaved;
	int m_nSampleSaved;

    CVideoWndBase m_videoWnd;
    afx_msg void OnBnClickedButtonPtz20();
private:
	void SelectUI( );
	void InitUI( );
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JSNETDEMODLG_H__BBC2F56C_FA93_4BB5_9EBA_6E5A92691384__INCLUDED_)
