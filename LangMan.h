#if !defined(AFX_LANGMAN_H__534A54E0_1C2C_4A89_A40D_6288299213EE__INCLUDED_)
#define AFX_LANGMAN_H__534A54E0_1C2C_4A89_A40D_6288299213EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>

//language mananger
//xwpcom 2009.05.12
class CLangMan
{
public:
	CLangMan();
	virtual ~CLangMan();

	BOOL	InitLangResource(CString szLangSection,LCID lcidDefault=1033);
	LCID	GetCurLCID()
	{
		return m_lcid;
	}
	int GetLCID(int nIndex);

	VOID TransMenu(HMENU hMenu, UINT id);
	BOOL TransDialog(HWND hWnd, UINT IDD);
	BOOL	SetLCID(LCID lcid);
	int GetLangCount();
	CString GetLangDesc(int nIndex);
	CString LoadString(UINT id);
	void	Clear();
protected:
	CString GetString(CString szSection,CString szName);
	static CString GetStringEx(CString szSection,CString szName,CString szIniFile);
	int GetInt(CString szSection,CString szName);
	static int GetIntEx(CString szSection,CString szName,CString szIniFile);
	BOOL SetMenuString(HMENU hMenu, UINT uItemID, PCTSTR ptzString, BOOL bByPosition = FALSE);
	VOID UpdateMenuFromLanguage(HMENU hMenu, PCTSTR ptzSection, PCTSTR ptzPath = TEXT(""));
	static BOOL WINAPI TransChildWindowCB(HWND hWnd, UINT IDD);

	static BOOL WINAPI UpdateDialogFromLanguageCB(HWND hWnd, LPARAM lParam);
	BOOL UpdateDialogFromLanguage(HWND hWnd, LPCTSTR pszSection);

	struct tagHandleFile
	{
		HANDLE hFile;
		CString szFileName;
	};

	static BOOL CALLBACK CLangMan::EnumResNameProcCB(
	  HMODULE hModule,   // module handle
	  LPCTSTR lpszType,  // resource type
	  LPTSTR lpszName,   // resource name
	  LONG_PTR lParam    // application-defined parameter
	);

	BOOL EnumResNameProc(
	  HMODULE hModule,   // module handle
	  LPCTSTR lpszType,  // resource type
	  LPTSTR lpszName   // resource name
	);

	CList<struct tagHandleFile,struct tagHandleFile> m_lstFiles;
	CString m_szFileName;//当前生效的ini文件
	LCID	m_lcid;
};

#endif // !defined(AFX_LANGMAN_H__534A54E0_1C2C_4A89_A40D_6288299213EE__INCLUDED_)
