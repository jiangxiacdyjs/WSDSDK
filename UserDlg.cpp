// UserDlg.cpp : implementation file
//

#include "stdafx.h"
#include "netsdk_demo.h"
#include "UserDlg.h"

#include "UserAddDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUserDlg dialog
CUserDlg::CUserDlg(CWnd* pParent /*=NULL*/,long lNetHandle)
	: CDialog(CUserDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUserDlg)
	m_bAuthEnable	= FALSE;
	//}}AFX_DATA_INIT
	m_lNetHandle	= lNetHandle;
}

void CUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUserDlg)
	DDX_Control(pDX, IDC_LIST_USER, m_listUser);
	DDX_Check(pDX, IDC_CHECK_AUTH_EN, m_bAuthEnable);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CUserDlg, CDialog)
	//{{AFX_MSG_MAP(CUserDlg)
	ON_BN_CLICKED(IDC_CHECK_AUTH_EN, OnCheckAuthEn)
	ON_BN_CLICKED(IDC_BTN_USER_ADD, OnBtnUserAdd)
	ON_BN_CLICKED(IDC_BTN_USER_SET, OnBtnUserSet)
	ON_BN_CLICKED(IDC_BTN_USER_DEL, OnBtnUserDel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUserDlg message handlers

BOOL CUserDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	theApp.m_lang.TransDialog(m_hWnd, IDD);
	
	InitUserList();
	LoadParam();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CUserDlg::InitUserList()
{
	m_listUser.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_FLATSB|LVS_EX_UNDERLINEHOT|LVS_EX_GRIDLINES);
	
	CString strCol;
	int nFmt = LVCFMT_LEFT;
	int iSub = 0;
	
	m_listUser.InsertColumn(iSub ++,uistrings[STR_USER_NAME].strings[g_nLangID],nFmt,150);
	m_listUser.InsertColumn(iSub ++,uistrings[STR_USER_GROUP].strings[g_nLangID],nFmt,150);
}

BOOL CUserDlg::LoadParam()
{
    {
        unsigned int size = 0;
        NS_AUTH_INFO_S cfg;
        ZeroMemory(&cfg, sizeof(cfg));
        if(NS_NET_GetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_GET_AUTH_INFO, &cfg, &size) != 0)
        {
            AfxMessageBox("Get auth info Failed.");
            return FALSE;
        }
        m_bAuthEnable = cfg.enable;
    }

    {
        unsigned int size = 0;
        NS_USER_INFO_S cfg;
        ZeroMemory(&cfg, sizeof(cfg));
        if(NS_NET_GetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_GET_USER_INFO, &cfg, &size) != 0)
        {
            AfxMessageBox("Get user info Failed.");
            return FALSE;
        }
	    //
	    m_emLstUser.RemoveAll();
	    {
		    for(int nIndex = 0; nIndex < cfg.usernum; nIndex ++)
		    {
			    m_emLstUser.AddTail(cfg.users[nIndex]);
		    }
	    }
    }
    

	RefreshList();
	UpdateData(FALSE);
	
	return TRUE;
}

void CUserDlg::RefreshList()
{
	m_listUser.DeleteAllItems();
	for(int nIndex = 0; nIndex < m_emLstUser.GetCount(); nIndex ++)
	{
		AddUserList(m_emLstUser.GetAt(m_emLstUser.FindIndex(nIndex)));
	}
}

void CUserDlg::AddUserList(NS_USER_T emUser)
{
	CString strItem;
	
	int nc = m_listUser.GetItemCount();

	m_listUser.InsertItem(nc,emUser.user);
	
	if(emUser.group == NS_USER_GROUP_ADMIN)
		strItem = uistrings[STR_GROUP_ADMIN].strings[g_nLangID];
	else if(emUser.group == NS_USER_GROUP_OPERATOR)
		strItem = uistrings[STR_GROUP_OPER].strings[g_nLangID];
	else
		strItem = uistrings[STR_GROUP_GUEST].strings[g_nLangID];

	m_listUser.SetItemText(nc,1,strItem);
	m_listUser.SetItemData(nc,(DWORD)emUser.group);
}

void CUserDlg::OnCheckAuthEn() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	
	CWaitCursor wait;
	
    {
        unsigned int size = 0;
        NS_AUTH_INFO_S cfg;
        ZeroMemory(&cfg, sizeof(cfg));
        cfg.enable = m_bAuthEnable;
        if(NS_NET_SetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_SET_AUTH_INFO, &cfg, size) != 0)
        {
            AfxMessageBox("Set auth info Failed.");
            return ;
        }
    }
}

// Select list item
void CUserDlg::SelectListItem(int nItem)
{
	if (nItem >= 0)
	{
		if(nItem < m_listUser.GetItemCount())
		{
			m_listUser.SetItemState(nItem,LVIS_SELECTED,LVIS_SELECTED);
			m_listUser.EnsureVisible(nItem, FALSE);
		}	
		else
		{
			m_listUser.SetItemState(0,LVIS_SELECTED,LVIS_SELECTED);
			m_listUser.EnsureVisible(0, FALSE);
		}
	}
}

// Get List Select Item
int	CUserDlg::GetSelectList()
{
	return m_listUser.GetNextItem(-1,LVNI_SELECTED);
}

void CUserDlg::OnBtnUserAdd() 
{
	// TODO: Add your control notification handler code here
	CUserAddDlg dlg;
	if(dlg.DoModal() == IDOK)
	{
        unsigned int size = 0;
        NS_USER_CMD_S cfg;
        ZeroMemory(&cfg, sizeof(cfg));
        cfg.dwSize = sizeof(NS_USER_CMD_S);
        strcpy(cfg.user.user, dlg.m_strUser);
        strcpy(cfg.user.passwd, dlg.m_strPassword);
        cfg.user.group = (NS_USER_GROUP_E)dlg.m_nGroup;
        if(NS_NET_SetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_SET_USER_ADD, &cfg, size) != 0)
        {
            AfxMessageBox("add user  Failed.");
            return ;
        }
		else
		{
			LoadParam();
		}
	}
}

void CUserDlg::OnBtnUserSet() 
{
	// TODO: Add your control notification handler code here
	int nItem = GetSelectList();
	if(nItem >= 0)
	{
		CUserAddDlg dlg;
		dlg.m_bAddMode = FALSE;

		NS_USER_T emUser = m_emLstUser.GetAt(m_emLstUser.FindIndex(nItem));
		dlg.SetUser(emUser.user,emUser.passwd,emUser.group);
		if(dlg.DoModal() == IDOK)
		{
            unsigned int size = 0;
            NS_USER_CMD_S cfg;
            ZeroMemory(&cfg, sizeof(cfg));
            cfg.dwSize = sizeof(NS_USER_CMD_S);
            strcpy(cfg.user.user, dlg.m_strUser);
            strcpy(cfg.user.passwd, dlg.m_strPassword);
            cfg.user.group = (NS_USER_GROUP_E)dlg.m_nGroup;
            if(NS_NET_SetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_SET_USER_SET, &cfg, size) != 0)
            {
                AfxMessageBox("set user  Failed.");
                return ;
            }
            else
            {
                LoadParam();
            }
		}
	}
}

void CUserDlg::OnBtnUserDel() 
{
	// TODO: Add your control notification handler code here
	int nItem = GetSelectList();
	if(nItem >= 0)
	{
		CString strUser;
		NS_USER_GROUP_E emPower;
		
		strUser = m_listUser.GetItemText(nItem,0);
		emPower	= (NS_USER_GROUP_E)m_listUser.GetItemData(nItem);
		
		if(IsUserExist(strUser,emPower))
		{
            unsigned int size = 0;
            NS_USER_CMD_S cfg;
            ZeroMemory(&cfg, sizeof(cfg));
            cfg.dwSize = sizeof(NS_USER_CMD_S);
            strcpy(cfg.user.user, strUser);
            if(NS_NET_SetServerConfig(m_lNetHandle, g_strChannel, NS_CMD_SET_USER_DEL, &cfg, size) != 0)
            {
                AfxMessageBox("set user  Failed.");
                return ;
            }
            else
            {
                LoadParam();
            }
		}	
	}	
}

BOOL CUserDlg::IsUserExist(CString strUser, NS_USER_GROUP_E emPower)
{
	for(int nIndex = 0;nIndex < m_emLstUser.GetCount(); nIndex ++)
	{
		if(strcmp(m_emLstUser.GetAt(m_emLstUser.FindIndex(nIndex)).user,strUser) == 0 && 
					m_emLstUser.GetAt(m_emLstUser.FindIndex(nIndex)).group == emPower)
			return TRUE;
	}

	return FALSE;
}
