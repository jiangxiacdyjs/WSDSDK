// SystemDlg.cpp : implementation file
//

#include "stdafx.h"
#include "netsdk_demo.h"
#include "SystemDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSystemDlg dialog
CSystemDlg::CSystemDlg(CWnd* pParent /*=NULL*/,long lNetHandle)
	: CDialog(CSystemDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSystemDlg)
		// NOTE: the ClassWizard will add member initialization here
	m_nEncType		 = 0;
	m_nVStandard	 = 0;
	m_nEncFormat	 = 0;
	m_nVIput		 = 0;
	//}}AFX_DATA_INIT
	m_lNetHandle	= lNetHandle;
}

void CSystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSystemDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDC_LIST_ENC, m_listEnc);
	DDX_Control(pDX, IDC_COMBO_INPUT, m_cmbInput);
	DDX_Control(pDX, IDC_COMBO_FORMAT, m_cmbFormat);
	DDX_Control(pDX, IDC_COMBO_STANDARD, m_cmbStandard);
	DDX_Control(pDX, IDC_COMBO_ENCODER, m_cmbEncoder);
	DDX_Control(pDX, IDC_EDIT_VERSION_WEB, m_editWeb);
	DDX_Control(pDX, IDC_EDIT_VERSION_LINUX, m_editLinux);
	DDX_Control(pDX, IDC_EDIT_DEVICE_NAME, m_editDeviceName);
	DDX_Control(pDX, IDC_EDIT_DEVICE_ID, m_editDeviceID);
	DDX_Control(pDX, IDC_EDIT_CHANNELS, m_editChannel);
	DDX_Control(pDX, IDC_EDIT_VERSION, m_editVersion);
	DDX_CBIndex(pDX, IDC_COMBO_ENCODER, m_nEncType);
	DDX_CBIndex(pDX, IDC_COMBO_STANDARD, m_nVStandard);
	DDX_CBIndex(pDX, IDC_COMBO_FORMAT, m_nEncFormat);
	DDX_CBIndex(pDX, IDC_COMBO_INPUT, m_nVIput);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSystemDlg, CDialog)
	//{{AFX_MSG_MAP(CSystemDlg)
	ON_BN_CLICKED(IDC_BTN_LOAD_DEFAULT, OnBtnLoadDefault)
	ON_BN_CLICKED(IDC_BTN_RESET, OnBtnReset)
	ON_BN_CLICKED(IDC_BTN_REBOOT, OnBtnReboot)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	ON_BN_CLICKED(IDC_BTN_ENC_ADD, OnBtnEncAdd)
	ON_BN_CLICKED(IDC_BTN_ENC_DEL, OnBtnEncDel)
	ON_BN_CLICKED(IDC_BTN_ENC_SAVE, OnBtnEncSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSystemDlg message handlers

BOOL CSystemDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	theApp.m_lang.TransDialog(m_hWnd, IDD);
	
	InitEncList();
	LoadParam();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSystemDlg::InitEncList()
{
	m_listEnc.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_UNDERLINEHOT|LVS_EX_GRIDLINES);
	
	m_listEnc.InsertColumn(0,"Channel",LVCFMT_LEFT,80);
	m_listEnc.InsertColumn(1,"Input",LVCFMT_LEFT,50);	
	m_listEnc.InsertColumn(2,"Format",LVCFMT_LEFT,50);
	m_listEnc.InsertColumn(3,"Type",LVCFMT_LEFT,50);
	m_listEnc.InsertColumn(4,"Standard",LVCFMT_LEFT,80);
}

BOOL CSystemDlg::LoadParam()
{
    {
        unsigned int size = 0;
        NS_SERVER_INFO_S cfg;
        ZeroMemory(&cfg, sizeof(cfg));
        if(NS_NET_GetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_GET_SERVER_INFO, &cfg, &size) != 0)
        {
            AfxMessageBox("Get system info Failed.");
            return FALSE;
        }

        CString strKernelVer,strServiceVer,strWebVer,strDevID,strDevName;

        m_editDeviceName.SetWindowText(cfg.name);
        m_editDeviceID.SetWindowText(cfg.DevID);
        m_editLinux.SetWindowText(cfg.kernelver);
        m_editVersion.SetWindowText(cfg.serverver);
        m_editWeb.SetWindowText(cfg.webver);
    }

    {
        unsigned int size = 0;
        NS_VIDEO_INFO_S cfg;
        ZeroMemory(&cfg, sizeof(cfg));
        if(NS_NET_GetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_GET_VIDEO_INFO, &cfg, &size) != 0)
        {
            AfxMessageBox("Get video info Failed.");
            return FALSE;
        }
    
 	    m_emVectorVEncType.clear();
 	    int nIndex = 0;
 	    for(nIndex = 0; nIndex < cfg.videoinfo.enctypenum; nIndex ++)
 	    {
 		    m_emVectorVEncType.push_back(cfg.videoinfo.enctypes[nIndex]);
 	    }
     
 	    m_emVectorVEncFormat.clear();
 	    for(nIndex = 0; nIndex < cfg.videoinfo.formatnum; nIndex ++)
 	    {
 		    m_emVectorVEncFormat.push_back(cfg.videoinfo.formats[nIndex]);
 	    }
     	
 	    m_emVectorVStdandard.clear();
 	    for(nIndex = 0; nIndex < cfg.videoinfo.standardnum; nIndex ++)
 	    {
 		    m_emVectorVStdandard.push_back(cfg.videoinfo.standards[nIndex]);
 	    }
     
 	    m_emVectorVEncChnS.clear();
 	    for(nIndex = 0; nIndex < cfg.videoinfo.channelnum; nIndex ++)
 	    {
 		    m_emVectorVEncChnS.push_back(cfg.videoinfo.channels[nIndex]);
 	    }

        m_nMaxVI = cfg.videoinfo.validvinum;
        m_nMaxVE = cfg.videoinfo.validvenum;
	    FillCtrls();
    }
	
	return TRUE;
}

// Get List Select Item
int CSystemDlg::GetListSelect()
{
	return m_listEnc.GetNextItem(-1,LVNI_SELECTED);
}

const char * formats[] = { "H261", "H263", "H264", "MPEG2", "MPEG4", "MJPEG" };
const char * enctypes[] = { "qcif", "cif", "d1", "720p", "uvga", "1080p", "qvga", "vga", "960p" };
const char * standards[] = { "PAL", "NTSC", "AUTO" };

void CSystemDlg::FillCtrls()
{
	CString strParam, strChns;
	strChns.Format(_T("%d"),m_emVectorVEncChnS.size());
	m_editChannel.SetWindowText(strChns);
	
 	m_cmbInput.ResetContent();
 	
 	int nIndex = 0;
 	for( nIndex = 0; nIndex < m_nMaxVI; nIndex ++)
 	{
 		strParam.Format("%d",nIndex + 1);
 		m_cmbInput.AddString(strParam);
 	}
 	m_cmbInput.SetCurSel(m_nVIput);
 	
 	//
 	m_cmbFormat.ResetContent();

 	for(nIndex = 0; nIndex < m_emVectorVEncFormat.size(); nIndex ++)
 	{
 		m_cmbFormat.AddString(formats[m_emVectorVEncFormat.at(nIndex)]);
 	}
    if (m_emVectorVEncChnS.size() > 0)
    {
        m_cmbFormat.SetCurSel(m_emVectorVEncChnS[0].format);
    }


    for(nIndex = 0; nIndex < m_emVectorVEncType.size(); nIndex ++)
    {
        m_cmbEncoder.AddString(enctypes[m_emVectorVEncType.at(nIndex)]);
    }

    if (m_emVectorVEncChnS.size() > 0)
    {
        m_cmbFormat.SetCurSel(m_emVectorVEncChnS[0].enctype);
    }


    for(nIndex = 0; nIndex < m_emVectorVStdandard.size(); nIndex ++)
    {
        m_cmbStandard.AddString(standards[m_emVectorVStdandard.at(nIndex)]);
    }
    if (m_emVectorVEncChnS.size() > 0)
    {
        m_cmbStandard.SetCurSel(m_emVectorVEncChnS[0].standard);
    }
	// -------------------------------------------------------
	
	FillEncList();
}

void CSystemDlg::FillEncList()
{
	m_listEnc.DeleteAllItems();
	
	CString strParam;
	for(int nIndex = 0; nIndex < m_emVectorVEncChnS.size(); nIndex ++)
	{
			strParam.Format("%d",nIndex + 1);
			m_listEnc.InsertItem(nIndex,strParam);
			
			strParam.Format("%d",m_emVectorVEncChnS.at(nIndex).vi + 1);
			m_listEnc.SetItemText(nIndex,1,strParam);
			
 			m_listEnc.SetItemText(nIndex,2,enctypes[m_emVectorVEncChnS[nIndex].enctype]);
 			
 			m_listEnc.SetItemText(nIndex,3,formats[m_emVectorVEncChnS[nIndex].format]);
 			
 			m_listEnc.SetItemText(nIndex,4,standards[m_emVectorVEncChnS[nIndex].standard]);
	}
	
}

void CSystemDlg::OnBtnEncAdd() 
{
	// TODO: Add your control notification handler code here
	if(m_emVectorVEncChnS.size() >= m_nMaxVE)
	{
		AfxMessageBox("Failed.");
		return;
	}
	
	if(!EncAdd())
	{
		AfxMessageBox("Failed.");
	}
}

BOOL CSystemDlg::EncAdd()
{
	return TRUE;
}

void CSystemDlg::OnBtnEncDel() 
{
	// TODO: Add your control notification handler code here
	if(m_emVectorVEncChnS.size() <= 1)
	{
		AfxMessageBox("Failed.");
		return;
	}
	
	int nList = GetListSelect();
	if(nList != -1 && nList < m_emVectorVEncChnS.size())
	{
		std::vector<NS_CHANNEL_INFO_T>::iterator iter = m_emVectorVEncChnS.begin() + nList; //;m_emVectorVEncChnS.at(nList)
		m_emVectorVEncChnS.erase(iter);
		FillEncList();
	}
	else
	{
		AfxMessageBox("Failed.");
	}
}

void CSystemDlg::OnBtnEncSave() 
{
	// TODO: Add your control notification handler code here
}

// 修改设备名称
void CSystemDlg::OnBtnSave() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	
	CString strDevName;
	m_editDeviceName.GetWindowText(strDevName);

    NS_SERVER_INFO_S cfg;
    unsigned int size = sizeof(NS_SERVER_INFO_S);
    cfg.dwSize = sizeof(NS_SERVER_INFO_S);
    strcpy(cfg.name , strDevName);
    if(NS_NET_SetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_SET_SERVER_INFO, &cfg, size) != 0)
    {
        AfxMessageBox("Set Device Name Failed.");
        return ;
    }

    AfxMessageBox(_T("OK"));
}

// 恢复设备出厂默认值
void CSystemDlg::OnBtnLoadDefault() 
{
	// TODO: Add your control notification handler code here
    NS_CMD_INFO_S cfg;
    unsigned int size = sizeof(NS_CMD_INFO_S);
    cfg.dwSize = sizeof(NS_CMD_INFO_S);
    if(NS_NET_SetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_RESTORE_SETTING, &cfg, size) != 0)
    {
        AfxMessageBox("Load Device Default Failed.");
        return ;
    }
    PostMessage(WM_CLOSE, 0, 0);
}

// 重启视频服务器服务
void CSystemDlg::OnBtnReset() 
{
	// TODO: Add your control notification handler code here
    NS_CMD_INFO_S cfg;
    unsigned int size = sizeof(NS_CMD_INFO_S);
    cfg.dwSize = sizeof(NS_CMD_INFO_S);
    if(NS_NET_SetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_RESTART_SERVICE, &cfg, size) != 0)
    {
        AfxMessageBox("Restart service Failed.");
        return ;
    }
    PostMessage(WM_CLOSE, 0, 0);
}

// 重启视频服务器设备
void CSystemDlg::OnBtnReboot() 
{
	// TODO: Add your control notification handler code here
    NS_CMD_INFO_S cfg;
    unsigned int size = sizeof(NS_CMD_INFO_S);
    cfg.dwSize = sizeof(NS_CMD_INFO_S);
    if(NS_NET_SetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_REBOOT_DEVICE, &cfg, size) != 0)
    {
        AfxMessageBox("Reboot Failed.");
        return ;
    }
    PostMessage(WM_CLOSE, 0, 0);
}

