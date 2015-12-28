#include "stdafx.h"
#include "LangMan.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define COUNT_OF(a) (sizeof(a)/sizeof((a)[0]))

CLangMan::CLangMan()
{
	m_lcid=0;
}

CLangMan::~CLangMan()
{

}

void CLangMan::Clear()
{
	m_lstFiles.RemoveAll();
}

BOOL CALLBACK CLangMan::EnumResNameProcCB(HMODULE hModule,LPCTSTR lpszType,LPTSTR lpszName,LONG_PTR lParam)
{
	CLangMan *pThis = (CLangMan*)lParam;
	return pThis->EnumResNameProc(hModule,lpszType,lpszName);
}

BOOL CLangMan::EnumResNameProc(HMODULE hModule,LPCTSTR lpszType,LPTSTR lpszName)
{
	HRSRC hRsrc = FindResource(hModule,lpszName,lpszType);
	DWORD dwSize = SizeofResource(NULL, hRsrc); 
	HGLOBAL hGlobal = LoadResource(NULL, hRsrc); 
	LPVOID pBuffer = LockResource(hGlobal); 
	
	char szTempPath[MAX_PATH];
	GetTempPath(sizeof(szTempPath),szTempPath);
	char szFileName[MAX_PATH];
	GetTempFileName(szTempPath,"UI_",0,szFileName);

	HANDLE hFile = CreateFile(szFileName,
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ,
		NULL,
		CREATE_ALWAYS,
		FILE_FLAG_DELETE_ON_CLOSE,//自动删除临时文件
		NULL);

	DWORD dwWrite=0;
	BOOL bOK = WriteFile(hFile,pBuffer,dwSize,&dwWrite,NULL);

	tagHandleFile hf;
	hf.hFile=hFile;
	hf.szFileName=szFileName;
	m_lstFiles.AddTail(hf);

	return TRUE;
}

//返回支持的语言种数
int CLangMan::GetLangCount()
{
	return m_lstFiles.GetCount();
}

//返回语言的描述
CString CLangMan::GetLangDesc(int nIndex)
{
	CString szDesc;
	if(nIndex>=0 && nIndex<GetLangCount())
	{
		POSITION pos = m_lstFiles.FindIndex(nIndex);
		tagHandleFile hf = m_lstFiles.GetAt(pos);
		szDesc = GetStringEx("settings","desc",hf.szFileName);
	}
	else
	{
		ASSERT(FALSE);
	}

	return szDesc;
}

int CLangMan::GetLCID(int nIndex)
{
	CString szDesc;
	if(nIndex>=0 && nIndex<GetLangCount())
	{
		POSITION pos = m_lstFiles.FindIndex(nIndex);
		tagHandleFile hf = m_lstFiles.GetAt(pos);
		return GetIntEx("settings","lcid",hf.szFileName);
	}
	else
	{
		ASSERT(FALSE);
	}

	return 0;
}

BOOL CLangMan::SetLCID(LCID lcid)
{
	POSITION pos = m_lstFiles.GetHeadPosition();
	while(pos)
	{
		tagHandleFile hf = m_lstFiles.GetNext(pos);
		UINT ret = GetPrivateProfileInt("settings","lcid",0,hf.szFileName);	
		if(ret == lcid)
		{
			m_lcid = lcid;
			m_szFileName = hf.szFileName;
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CLangMan::TransDialog(HWND hWnd, UINT IDD)
{
	ASSERT(!m_szFileName.IsEmpty());
	
	TCHAR tzSection[32];
	wsprintf(tzSection, TEXT("%u"), IDD);
	UpdateDialogFromLanguage(hWnd, (LPCTSTR)tzSection);

	DWORD dwParam[2];
	dwParam[0]=(DWORD)this;
	dwParam[1]=(DWORD)tzSection;
	EnumChildWindows(hWnd, (WNDENUMPROC) UpdateDialogFromLanguageCB, (LPARAM)dwParam);

	return TRUE;
}

BOOL CLangMan::UpdateDialogFromLanguageCB(HWND hWnd, LPARAM lParam)
{
	LPDWORD dwParam=(LPDWORD )lParam;
	CLangMan *pThis = (CLangMan *)dwParam[0];
	LPCTSTR pszSection=(LPCTSTR )dwParam[1];

	return pThis->UpdateDialogFromLanguage(hWnd,pszSection);
}

BOOL CLangMan::UpdateDialogFromLanguage(HWND hWnd, LPCTSTR pszSection)
{
	TCHAR tzText[1024];
	TCHAR tzName[MAX_PATH];

	// 获取窗口标识字符串
	wsprintf(tzName, TEXT("%u"), GetDlgCtrlID(hWnd));

	if (GetPrivateProfileString(pszSection, tzName, NULL, tzText, COUNT_OF(tzText), m_szFileName))
	{
		SetWindowText(hWnd, tzText);
	}

	DWORD dwParam[2];
	dwParam[0]=(DWORD)this;
	dwParam[1]=(DWORD)pszSection;
	EnumChildWindows(hWnd, (WNDENUMPROC) UpdateDialogFromLanguageCB, (LPARAM)dwParam);

	return TRUE;
}

BOOL CLangMan::InitLangResource(CString szLangSection,LCID lcidDefault)
{
	ASSERT(m_lstFiles.GetCount() == 0);
	
	EnumResourceNames(NULL,szLangSection,(ENUMRESNAMEPROC)CLangMan::EnumResNameProcCB,(long)this);

	int nc = m_lstFiles.GetCount();
	POSITION pos = m_lstFiles.GetHeadPosition();
	while(pos)
	{
		tagHandleFile hf = m_lstFiles.GetNext(pos);
		if(m_szFileName.IsEmpty())
		{
			m_szFileName = hf.szFileName;
		}
	}

	SetLCID(lcidDefault);

	return TRUE;
}

CString CLangMan::LoadString(UINT id)
{
	CString szName;
	szName.Format("%d",id);
	return GetString("String",szName);
}

CString CLangMan::GetString(CString szSection,CString szName)
{
	return GetStringEx(szSection,szName,m_szFileName);
}

int CLangMan::GetInt(CString szSection,CString szName)
{
	return GetIntEx(szSection,szName,m_szFileName);
}

CString CLangMan::GetStringEx(CString szSection,CString szName,CString szIniFile)
{
	TCHAR tzText[4*1024];

	CString szText;
	DWORD dwRet = GetPrivateProfileString(szSection, szName, NULL, tzText, COUNT_OF(tzText), szIniFile);
	if(dwRet>0)
	{
		szText = tzText;
	}
	else
	{
		ASSERT(FALSE);
	}

	szText.Replace("\\n","\n");//替换换行

	return szText;
}

int CLangMan::GetIntEx(CString szSection,CString szName,CString szIniFile)
{
	UINT ret = GetPrivateProfileInt(szSection,szName,0,szIniFile);	
	return (int)ret;
}

VOID CLangMan::TransMenu(HMENU hMenu, UINT id)
{
	ASSERT(!m_szFileName.IsEmpty());

	PCTSTR ptzResName = MAKEINTRESOURCE(id);

	TCHAR tzSection[32];
	wsprintf(tzSection, TEXT("%u"), ptzResName);
	UpdateMenuFromLanguage(hMenu, tzSection);
}

VOID CLangMan::UpdateMenuFromLanguage(HMENU hMenu, PCTSTR ptzSection, PCTSTR ptzPath)
{
	INT i;
	INT iNum;
	TCHAR tzName[256];
	MENUITEMINFO miiItem;

	// 初始化变量，获取菜单项数量
	miiItem.cbSize = CDSIZEOF_STRUCT(MENUITEMINFO, cch);
	miiItem.fMask = MIIM_SUBMENU | MIIM_ID;
	iNum = GetMenuItemCount(hMenu);
	for (i = 0; i < iNum; i++)
	{
		// 获取弹出菜单句柄和标识
		GetMenuItemInfo(hMenu, i, TRUE, &miiItem);
		if (miiItem.wID)
		{
			// 获取菜单标识文本
			if (miiItem.hSubMenu)
			{
				wsprintf(tzName, TEXT("%s|%u"), ptzPath, i);
			}
			else
			{
				wsprintf(tzName, TEXT("%u"), miiItem.wID);
			}

			// 设置菜单字符串
			CString szText = GetString(ptzSection, tzName);
			if(!szText.IsEmpty())
			{
				SetMenuString(hMenu, i, szText, TRUE);
			}

			// 递归修改菜单字符串
			if (miiItem.hSubMenu)
			{
				UpdateMenuFromLanguage(miiItem.hSubMenu, ptzSection, tzName);
			}
		}
	}
}

// 设置菜单字符串
BOOL CLangMan::SetMenuString(HMENU hMenu, UINT uItemID, PCTSTR ptzString, BOOL bByPosition)
{
	MENUITEMINFO miiItem;

	miiItem.cbSize = CDSIZEOF_STRUCT(MENUITEMINFO, cch);
#if (_WINVER >= 0x0410)
	miiItem.fMask = MIIM_STRING;
#else (_WINVER >= 0x0410)
	miiItem.fMask = MIIM_TYPE;
	miiItem.cch = 0;
	miiItem.dwTypeData = NULL;
	GetMenuItemInfo(hMenu, uItemID, bByPosition, &miiItem);
#endif (_WINVER >= 0x0410)
	miiItem.dwTypeData = (PTSTR) ptzString;

	return SetMenuItemInfo(hMenu, uItemID, bByPosition, &miiItem);
}

