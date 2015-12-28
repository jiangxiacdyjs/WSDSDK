// UpdateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "netsdk_demo.h"
#include "UpdateDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUpdateDlg dialog
CUpdateDlg::CUpdateDlg(CWnd* pParent /*=NULL*/,long lNetHandle,CString strDevIP)
	: CDialog(CUpdateDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUpdateDlg)
	m_strPacketFile = _T("");
	//}}AFX_DATA_INIT
	m_strDevIP		= strDevIP;
	m_lNetHandle	= lNetHandle;
}

void CUpdateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUpdateDlg)
	DDX_Text(pDX, IDC_EDIT_FILE, m_strPacketFile);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CUpdateDlg, CDialog)
	//{{AFX_MSG_MAP(CUpdateDlg)
	ON_BN_CLICKED(IDC_BTN_OPEN, OnBtnOpen)
	ON_BN_CLICKED(IDC_BTN_UPDATE, OnBtnUpdate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUpdateDlg message handlers
CString CUpdateDlg::GetOpenPacketFile()
{
	CFileDialog dlgFileOpen(TRUE,".*",NULL,OFN_FILEMUSTEXIST,
		"Packet Files(*.*)|*.*||");
	
	int StructSize = 0;
	DWORD dwVersion = GetVersion();
    if(dwVersion < 0x80000000)			//winnt/xp
		StructSize = 88;				//show new dialog
	else								//win9x
		StructSize = 76;				//show old dialog
	
	dlgFileOpen.m_ofn.lStructSize		= StructSize;
	//	dlgFileOpen.m_ofn.lpstrInitialDir	= g_pMainWndInSystem->m_strExePath;
	if(dlgFileOpen.DoModal() == IDOK)
	{
		return (CString)dlgFileOpen.m_ofn.lpstrFile;
	}
	
	return _T("");
}

void CUpdateDlg::OnBtnOpen() 
{
	// TODO: Add your control notification handler code here
	CString strPacketFile = GetOpenPacketFile();	
	if( !strPacketFile.IsEmpty() )
	{
		m_strPacketFile = strPacketFile;
		UpdateData(FALSE);
	}
}

void CUpdateDlg::OnBtnUpdate() 
{
	// TODO: Add your control notification handler code here
	UpdateData();	

	CWaitCursor wait;

	if(UpdatePacket(m_strPacketFile))
	{
		AfxMessageBox(uistrings[STR_SUCCESS].strings[g_nLangID]);
	}
	else
	{
		AfxMessageBox(uistrings[STR_FAIL].strings[g_nLangID]);
	}
}

BOOL CUpdateDlg::UpdatePacket(CString strPacketFile)
{
	long lRTSPPort,lWebPort,lABCPort,lUpdatePort,lFtpPort;

    {
        unsigned int size = 0;
        NS_PORT_INFO_S cfg;
        ZeroMemory(&cfg, sizeof(cfg));
        if(NS_NET_GetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_GET_PORT_INFO, &cfg, &size) != 0)
        {
            AfxMessageBox("Get Port info Failed.");
            return FALSE;
        }
        lUpdatePort = cfg.update;
    }

    {
        NS_UPDATE_DEVICE_S cfg;
        unsigned int size = sizeof(NS_UPDATE_DEVICE_S);
        if(NS_NET_SetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_UPDATE_DEVICE, &cfg, size) != 0)
        {
            AfxMessageBox("Failed to start updating device.");
            return FALSE;
        }
        if(!TcpUpdateFile(m_strDevIP,lUpdatePort,strPacketFile))
            return FALSE;
    }
	
	return TRUE;
}

CString CUpdateDlg::ChangeDDNSIP(CString strHost)
{
	CString strIP;
	if(strHost.IsEmpty())
		return _T("");
	
	// 格式化IP地址
	struct in_addr iaDest;		// Internet address structure	
    iaDest.s_addr = inet_addr(strHost);
    if (iaDest.s_addr == INADDR_NONE)
	{
		// 使用的域名
        LPHOSTENT pHost = gethostbyname(strHost);
		// 如果无法取到主机信息则直接返回失败
		if(pHost == NULL)
			return "";
		
		strIP = inet_ntoa(*(LPIN_ADDR)pHost->h_addr);
	}
	else
	{
		strIP = strHost;
	}
	
	return strIP;
}

// 更新文件过程
BOOL CUpdateDlg::TcpUpdateFile(CString strIp,UINT nPort,CString strUpdateFile)
{
#define FILE_READSIZE			1024 * 20		// 每个包更新20K数据
	
	BYTE  byteFile[FILE_READSIZE];		
	CFile fileUpdate;
	sockaddr_in addr;

	SOCKET hSock = socket(AF_INET,SOCK_STREAM,0);
	if(hSock == INVALID_SOCKET)
		goto Failed_Lable;
	
	strIp = ChangeDDNSIP(strIp);

	//准备服务器的信息，这里需要指定服务器的地址
	addr.sin_family				= AF_INET;
	addr.sin_addr.S_un.S_addr	= inet_addr(strIp);
	addr.sin_port				= htons(nPort);							// 更新文件使用的端口
	
	if(connect(hSock,(LPSOCKADDR)&addr,sizeof(addr)) == SOCKET_ERROR)
		goto Failed_Lable;
	
	if(fileUpdate.Open(strUpdateFile,CFile::modeRead | CFile::typeBinary | CFile::shareDenyWrite,NULL))
	{
		fileUpdate.SeekToBegin();
		memset(byteFile,0,FILE_READSIZE);
		
		// %I64u		
		LONGLONG llLength	= fileUpdate.GetLength();			
		LONGLONG llSend		= 0;
		int nReadCount		= -1;
		while(llLength > 0 && (nReadCount = fileUpdate.Read(byteFile,FILE_READSIZE)) > 0)
		{
			if(!SendFileData(hSock,byteFile,nReadCount))
			{
				fileUpdate.Close();
				goto Failed_Lable;
			}
		}

		fileUpdate.Close();
	}
	
	if(hSock != INVALID_SOCKET)
	{
		closesocket(hSock);
		hSock = INVALID_SOCKET;
	}	

	return TRUE;

	// -------------------------------------------------------------------------

Failed_Lable:
	if(hSock != INVALID_SOCKET)
	{
		closesocket(hSock);
		hSock = INVALID_SOCKET;
	}

	return FALSE;
}

// 发送文件数据
BOOL CUpdateDlg::SendFileData(SOCKET hSocket,BYTE* pData,DWORD dwData)
{
	if(hSocket == INVALID_SOCKET || pData == NULL || dwData == 0)
		return FALSE;
	
	int nTotal = 0;
	int nSend  = 0;
	int nCycle = 0;
	while(nTotal < dwData)
	{
		nSend = send(hSocket,(char*)(pData + nTotal), dwData - nTotal, 0);
		if(nSend <= 0)
		{
			nCycle ++ ;
			
			if(nCycle > 100)
				return FALSE;
			
			if(WSAGetLastError() == WSAEWOULDBLOCK)
			{
				Sleep(50);
				continue;
			}
			
			return FALSE;
		}
		
		nTotal += nSend;
	}
	
	return TRUE;
}

BOOL CUpdateDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	theApp.m_lang.TransDialog(m_hWnd, IDD);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
