// TrackDlg.cpp : implementation file
//

#include "stdafx.h"
#include "netsdk_demo.h"
#include "TrackDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTrackDlg dialog
CTrackDlg::CTrackDlg(CWnd* pParent /*=NULL*/,long lNetHandle)
	: CDialog(CTrackDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTrackDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_lNetHandle	= lNetHandle;
}

void CTrackDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTrackDlg)
	DDX_Control(pDX, IDC_LIST_PTZ_TRACK, m_listTrack);
	DDX_Control(pDX, IDC_COMBO_PTZ_STAYTIME, m_cmbStayTime);
	DDX_Control(pDX, IDC_COMBO_PTZ_PRESET, m_cmbPreset);
	DDX_Control(pDX, IDC_COMBO_PTZ_TRACK, m_cmbTrack);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTrackDlg, CDialog)
	//{{AFX_MSG_MAP(CTrackDlg)
	ON_BN_CLICKED(IDC_BTN_PTZ_ADD, OnBtnPtzAdd)
	ON_BN_CLICKED(IDC_BTN_PTZ_DELETE, OnBtnPtzDelete)
	ON_BN_CLICKED(IDC_BTN_PTZ_WRITE, OnBtnPtzWrite)
	ON_BN_CLICKED(IDC_BTN_PTZ_INVOKE, OnBtnPtzInvoke)
	ON_CBN_SELCHANGE(IDC_COMBO_PTZ_TRACK, OnSelchangeComboPtzTrack)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTrackDlg message handlers

BOOL CTrackDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	theApp.m_lang.TransDialog(m_hWnd, IDD);
	
	
	if(!InitPreset())
	{
		AfxMessageBox("Read Preset Failed...");
	}

	InitTrackList();
	InitControls();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTrackDlg::InitTrackList()
{
	m_listTrack.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_UNDERLINEHOT|LVS_EX_GRIDLINES);
	
	CString strCol;
	int nFmt = LVCFMT_CENTER;
	int iSub = 0;
	
	m_listTrack.InsertColumn(iSub ++,uistrings[STR_TRACK_ID].strings[g_nLangID],LVCFMT_RIGHT,50);
	
	m_listTrack.InsertColumn(iSub ++,uistrings[STR_TRACK_PRESET].strings[g_nLangID],LVCFMT_CENTER,80);
	
	m_listTrack.InsertColumn(iSub ++,uistrings[STR_TRACK_INTERVAL].strings[g_nLangID],LVCFMT_CENTER,80);
}

BOOL CTrackDlg::InitPreset()
{
    unsigned int size = 0;
    if(NS_NET_GetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_GET_PRESET_INFO, &m_presets, &size) != 0)
        return FALSE;

	m_vectorPreset.clear();
	for(int nIndex = 0; nIndex < m_presets.count ; nIndex ++)
	{
		m_vectorPreset.push_back(m_presets.presets[nIndex]);
	}

	return TRUE;
}

void CTrackDlg::InitControls()
{
	CString strCmb;
	for(int nTrack = 1; nTrack <= NS_MAX_TRACK_NUM; nTrack ++)
	{
		strCmb.Format(_T("%d"),nTrack);
		m_cmbTrack.AddString(strCmb);
	}
	
	for(int nPreset = 0; nPreset < m_vectorPreset.size(); nPreset ++)
	{
		strCmb.Format(_T("%d"),m_vectorPreset.at(nPreset).id);
		
		m_cmbPreset.AddString(strCmb);
	}
	
	for(int nStayTime = 1; nStayTime <= NS_MAX_STAY_TIME; nStayTime ++)
	{
		strCmb.Format(_T("%d"),nStayTime);
		m_cmbStayTime.AddString(strCmb);
	}
}

// Get List Select Item
int CTrackDlg::GetListSelect()
{
	return m_listTrack.GetNextItem(-1,LVNI_SELECTED);
}

// Add Preset to List
void CTrackDlg::AddPresetToList(std::vector<NS_PRESET_S> vectorPreset)
{
	m_listTrack.DeleteAllItems();
	
	CString strItem;	
	for(int nIndex = 0; nIndex < vectorPreset.size(); nIndex ++)
	{	
		int nItem	= m_listTrack.GetItemCount();
		int nSub	= 1;
		
		int nPreset   = vectorPreset.at(nIndex).id;
		int nStayTime = vectorPreset.at(nIndex).stayTime;
		
		strItem.Format("%d",nItem + 1);
		m_listTrack.InsertItem(nItem,strItem);
		
		strItem.Format("%d",nPreset);
		m_listTrack.SetItemText(nItem,nSub ++,strItem);
		
		strItem.Format("%d",nStayTime);
		m_listTrack.SetItemText(nItem,nSub ++,strItem);
		
		nItem ++;
	}
}

// 读取指定轨迹配置，并将配置信息显示在列表中
void CTrackDlg::OnSelchangeComboPtzTrack() 
{
	// TODO: Add your control notification handler code here
	CWaitCursor wait;

	// 动态获取当前轨迹对应的配置信息
	int nSel = m_cmbTrack.GetCurSel();
	if(nSel >= 0)
	{
		CString strItem;
		m_cmbTrack.GetLBText(nSel,strItem);
		UINT nTrack = atoi(strItem);
		
        unsigned int size = 0;
        if(NS_NET_GetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_GET_TRACK_INFO, &m_tracks, &size) != 0)
		{
			AfxMessageBox("Get Track Failed.");
            return ;
		}

		if(nTrack >= 1 && nTrack <= NS_MAX_TRACK_NUM)
		{
            NS_PRESET_S emPresets;
			{				
				m_vectorTrackPreset.clear();
				for(int nIndex = 0; nIndex < m_tracks.tracks[nTrack-1].presetCount ; nIndex ++)
				{
					m_vectorTrackPreset.push_back(m_tracks.tracks[nTrack-1].presets[nIndex]);
				}

				AddPresetToList(m_vectorTrackPreset);
			}
		}		
	}
}

// 添加预置位到当前选择轨迹,需要使用 "保存" 才会更新至视频服务器
void CTrackDlg::OnBtnPtzAdd() 
{
	// TODO: Add your control notification handler code here
	int nListCount = m_listTrack.GetItemCount();
	if(nListCount > NS_MAX_TRACK_NUM)
	{
		// 每条轨迹的预置位最多16个
		AfxMessageBox("Must Track Position 16");
		return;
	}
	
	int nTrackSel = m_cmbTrack.GetCurSel();
	if(nTrackSel < 0 || nTrackSel > NS_MAX_TRACK_NUM)
	{
		m_cmbTrack.SetFocus();
		return;
	}
	
	int nPresetSel = m_cmbPreset.GetCurSel();
	if(nPresetSel < 0 || nPresetSel > NS_MAX_PRESET_NUM)
	{
		m_cmbPreset.SetFocus();
		return;
	}
	
	CString strPresetPos;
	m_cmbPreset.GetLBText(nPresetSel,strPresetPos.GetBuffer(MAX_PATH));
	strPresetPos.ReleaseBuffer();
	nPresetSel = atoi(strPresetPos);
	if(nPresetSel < 0 || nPresetSel > NS_MAX_PRESET_NUM)
	{
		m_cmbPreset.SetFocus();
		return;
	}
	
	int nStaySel   = m_cmbStayTime.GetCurSel();
	if(nStaySel < 0 || nStaySel > NS_MAX_STAY_TIME)
	{
		m_cmbStayTime.SetFocus();
		return;
	}

	NS_PRESET_S emPreset;
	memset(&emPreset,0,sizeof(NS_PRESET_S));
	
	emPreset.id = nPresetSel;
	emPreset.stayTime = nStaySel + 1;
	m_vectorTrackPreset.push_back(emPreset);
	AddPresetToList(m_vectorTrackPreset);
}

// 删除当前选择轨迹列表中的预置位,需要使用 "保存" 才会更新至视频服务器
void CTrackDlg::OnBtnPtzDelete() 
{
	// TODO: Add your control notification handler code here
	int nTrackSel  = m_cmbTrack.GetCurSel();
	if(nTrackSel < 0 || nTrackSel > NS_MAX_TRACK_NUM)
	{
		m_cmbTrack.SetFocus();
		AfxMessageBox("Please select track first ...");
		return;
	}
	
	int nListIndex = GetListSelect();
	if(nListIndex >= 0)
	{
		CString strPresetPos = m_listTrack.GetItemText(nListIndex,1);
		UINT nPresetID = atoi(strPresetPos);
		
		// 删除列表中的项
		m_listTrack.DeleteItem(nListIndex);
		
		// 找到预置位 删除轨迹数组中的预置位
		if(nListIndex < m_vectorTrackPreset.size())
		{
			std::vector<NS_PRESET_S>::iterator iter = m_vectorTrackPreset.begin() + nListIndex;//m_vectorTrackPreset.at(nListIndex);
			m_vectorTrackPreset.erase(iter);
			AddPresetToList(m_vectorTrackPreset);
		}
	}
}

// 更新当前配置到视频服务器
void CTrackDlg::OnBtnPtzWrite() 
{
	// TODO: Add your control notification handler code here
	int nListCount = m_listTrack.GetItemCount();
	if(nListCount > 16)
	{
		// 每条轨迹的预置位最多16个
		return;
	}
	
	int nTrackSel  = m_cmbTrack.GetCurSel();
	if(nTrackSel < 0 || nTrackSel > 16)
	{
		m_cmbTrack.SetFocus();
		return;
	}
	
	CWaitCursor wait;

	NS_TRACK_S track;
    ZeroMemory(&track, sizeof(NS_TRACK_S));
    track.id = nTrackSel + 1;
	for(int nIndex = 0; nIndex < m_vectorTrackPreset.size() && nIndex < _MAX_PATH; nIndex ++)
	{
		track.presets[nIndex].id = m_vectorTrackPreset.at(nIndex).id;
		track.presets[nIndex].stayTime = m_vectorTrackPreset.at(nIndex).stayTime;
	}
	track.presetCount = m_vectorTrackPreset.size();
	
    NS_PTZ_TRACK_CMD_S stData;
    ZeroMemory(&stData, sizeof(NS_PTZ_TRACK_CMD_S));
    stData.dwSize = sizeof(NS_PTZ_TRACK_CMD_S);
    stData.track = track;
    if(NS_NET_SetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_SET_TRACK, &stData, sizeof(NS_PTZ_TRACK_CMD_S)) != 0)
    {
        AfxMessageBox("set track Failed.");
        return;
    }
}

// 调用当前轨迹
void CTrackDlg::OnBtnPtzInvoke() 
{
	// TODO: Add your control notification handler code here
	int nSel = m_cmbTrack.GetCurSel();
	if(nSel >= 0)
	{
		UINT nTrack;
		CString strTrack;
		m_cmbTrack.GetLBText(nSel,strTrack);
		nTrack = atoi(strTrack);
		
        NS_PTZ_TRACK_CMD_S stData;
        ZeroMemory(&stData, sizeof(NS_PTZ_TRACK_CMD_S));
        stData.dwSize = sizeof(NS_PTZ_TRACK_CMD_S);
        stData.track.id = nTrack;
        if(NS_NET_PTZControl(m_lNetHandle, NS_CMD_PTZ_TRACK, &stData, sizeof(NS_PTZ_TRACK_CMD_S)) != 0)
        {
            AfxMessageBox("call track Failed.");
            return;
        }
	}
}
