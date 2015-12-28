// PresetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "netsdk_demo.h"
#include "PresetDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPresetDlg dialog
CPresetDlg::CPresetDlg(CWnd* pParent /*=NULL*/,long lNetHandle)
	: CDialog(CPresetDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPresetDlg)
	m_strPresetName = _T("");
	m_nPresetID		= 1;
	m_nGuarderPerp	= 1;
	m_nGuarderTime	= 1;
	m_bGuardEnable	= FALSE;
	//}}AFX_DATA_INIT
	m_lNetHandle	= lNetHandle;

}

void CPresetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPresetDlg)
	DDX_Control(pDX, IDC_LIST_PRESET, m_listPreset);
	DDX_Text(pDX, IDC_EDIT_PRESETNAME, m_strPresetName);
	DDX_Text(pDX, IDC_EDIT_PRESETPOS, m_nPresetID);
	DDX_Text(pDX, IDC_EDIT_GUARDER_PERP, m_nGuarderPerp);
	DDV_MinMaxUInt(pDX, m_nGuarderPerp, 1, 128);
	DDX_Text(pDX, IDC_EDIT_GUARDER_TIME, m_nGuarderTime);
	DDV_MinMaxUInt(pDX, m_nGuarderTime, 2, 255);
	DDX_Check(pDX, IDC_CHECK_GUARDER, m_bGuardEnable);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPresetDlg, CDialog)
	//{{AFX_MSG_MAP(CPresetDlg)
		ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
		ON_BN_CLICKED(IDC_BTN_DEL, OnBtnDel)
		ON_BN_CLICKED(IDC_BTN_INVOKE, OnBtnInvoke)
	ON_BN_CLICKED(IDC_BTN_GUARDER_SAVE, OnBtnGuarderSave)
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_CHECK_GUARDER, OnBnClickedCheckGuarder)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPresetDlg message handlers

BOOL CPresetDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	theApp.m_lang.TransDialog(m_hWnd, IDD);
	CreatePresetList();
	if(!InitPreset())
	{
		AfxMessageBox("Get Preset Info Failed.");
	}
	
	if(!InitGuard())
	{
		AfxMessageBox("Get Guard Info Failed.");
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPresetDlg::CreatePresetList()
{
	m_listPreset.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_UNDERLINEHOT|LVS_EX_GRIDLINES);
	m_listPreset.InsertColumn(0,uistrings[STR_PRESET_ID].strings[g_nLangID],LVCFMT_RIGHT,100);
	m_listPreset.InsertColumn(1,uistrings[STR_PRESET_NAME].strings[g_nLangID],LVCFMT_CENTER,120);
}

void CPresetDlg::FillPresetList()
{
	m_listPreset.DeleteAllItems();

	for(int nIndex = 0; nIndex < m_presets.count; nIndex ++)
	{
		AddPresetList(m_presets.presets[nIndex].id ,m_presets.presets[nIndex].name);
	}
}

BOOL CPresetDlg::IsPresetPosExist(UINT nPresetID)
{
// 	for(int nIndex = 0; nIndex < m_vectorPreset.size(); nIndex ++)
// 	{
// 		if(m_vectorPreset.at(nIndex).nPresetID == nPresetID)
// 			return TRUE;
// 	}
// 	
	return FALSE;
}

void CPresetDlg::AddPresetList(UINT nPresetID,CString strPresetName)
{
	int nItem	= m_listPreset.GetItemCount();
	
	CString strPosition;
	strPosition.Format("%d",nPresetID);

	// Insert Position
	m_listPreset.InsertItem(nItem,strPosition);
	
	// Insert Preset Name
	m_listPreset.SetItemText(nItem,1,strPresetName);
}

BOOL CPresetDlg::InitPreset()
{
    unsigned int size = 0;
	if(NS_NET_GetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_GET_PRESET_INFO, &m_presets, &size) != 0)
		return FALSE;

	FillPresetList();
	
	return TRUE;
}

BOOL CPresetDlg::InitGuard()
{
    unsigned int size = 0;
    if(NS_NET_GetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_GET_GUARDER_INFO, &m_guarder, &size) != 0)
        return FALSE;
	
    m_bGuardEnable = m_guarder.enable>0;
    m_nGuarderTime = m_guarder.time;
    m_nGuarderPerp = m_guarder.preset;
	UpdateData(FALSE);	
	
	return TRUE;
}

int	CPresetDlg::GetSelectList()
{
	return m_listPreset.GetNextItem(-1,LVNI_SELECTED);	
}

void CPresetDlg::OnBtnAdd() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	
	if(m_nPresetID <= 0 || m_nPresetID > NS_MAX_PRESET_NUM)
	{
		AfxMessageBox("Invalid Preset Pos");
		return;
	}
	
	if(IsPresetPosExist(m_nPresetID))
	{
		AfxMessageBox("Preset Pos Exist");
		return;
	}
	
	if(m_strPresetName.GetLength() > NS_MAX_PRESET_NUM)
	{
		AfxMessageBox("Invalid Preset Name");
		return;
	}
	
    NS_PTZ_PRESET_CMD_S preset;
    preset.id = m_nPresetID;
    strcpy(preset.name, m_strPresetName);
	if(NS_NET_SetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_SET_PRESET_ADD, &preset, sizeof(NS_PTZ_PRESET_CMD_S)) != 0)
	{
		AfxMessageBox("Add Preset Failed.");
		return;
	}

	InitPreset();
}

void CPresetDlg::OnBtnDel() 
{
	// TODO: Add your control notification handler code here
	int nSelectList = GetSelectList();
	if(nSelectList < 0)
	{
		AfxMessageBox("Delete Preset Must Select Preset First");
		return;
	}
	
	CString strItem;
	UINT nPresetID  = 0;	
	strItem			= m_listPreset.GetItemText(nSelectList,0);
	nPresetID		= atoi(strItem);
	
    NS_PTZ_PRESET_CMD_S preset;
    preset.id = nPresetID;
    if(NS_NET_SetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_SET_PRESET_DEL, &preset, sizeof(NS_PTZ_PRESET_CMD_S)) != 0)
    {
        AfxMessageBox("del Preset Failed.");
        return;
    }
    

	InitPreset();
}

void CPresetDlg::OnBtnInvoke() 
{
	// TODO: Add your control notification handler code here
	int nSelectList = GetSelectList();
	if(nSelectList < 0)
	{
		AfxMessageBox("Invoke Preset Must Select Preset First");
		return;
	}	
	
	CString strItem;
	UINT nPresetID	= 0;
	strItem			= m_listPreset.GetItemText(nSelectList,0);
	nPresetID		= atoi(strItem);
	
    NS_PTZ_PRESET_CMD_S preset;
    preset.id = nPresetID;
    if(NS_NET_PTZControl(m_lNetHandle, NS_CMD_PTZ_PRESET, &preset, sizeof(NS_PTZ_PRESET_CMD_S)) != 0)
    {
        AfxMessageBox("call Preset Failed.");
        return;
    }
    
}

// ±£´æ¿´ÊØÎ»ÅäÖÃ
void CPresetDlg::OnBtnGuarderSave() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	
	if(m_nGuarderPerp < 1 || m_nGuarderPerp > NS_MAX_PRESET_NUM)
	{
		AfxMessageBox("Invalid Preset");
		GetDlgItem(IDC_EDIT_GUARDER_PERP)->SetFocus();
		return;
	}
	
	if(m_nGuarderTime < 1 || m_nGuarderTime > 300)
	{
		AfxMessageBox("Invalid Interval");
		GetDlgItem(IDC_EDIT_GUARDER_TIME)->SetFocus();
		return;
	}

    unsigned int size = 0;
    m_guarder.dwSize = sizeof(m_guarder);
    m_guarder.enable = m_bGuardEnable;
    m_guarder.time = m_nGuarderTime;
    m_guarder.preset = m_nGuarderPerp;
    if(NS_NET_SetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_SET_GUARDER_INFO, &m_guarder, size) != 0)
	{
		AfxMessageBox("Failed");
		return ;
	}
}

void CPresetDlg::OnBnClickedCheckGuarder()
{
    // TODO: Add your control notification handler code here
    if( ! ((CButton *)GetDlgItem(IDC_CHECK_GUARDER))->GetCheck() )
    {
        GetDlgItem(IDC_EDIT_GUARDER_PERP)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_GUARDER_TIME)->EnableWindow(FALSE);
    }
    else
    {
        GetDlgItem(IDC_EDIT_GUARDER_PERP)->EnableWindow(TRUE);
        GetDlgItem(IDC_EDIT_GUARDER_TIME)->EnableWindow(TRUE);
    }
}
