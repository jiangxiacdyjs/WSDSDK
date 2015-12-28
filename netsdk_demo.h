// JSNetDemo.h : main header file for the JSNETDEMO application
//

#if !defined(AFX_JSNETDEMO_H__CF0A66A1_A3B2_4E67_8A5D_8B29DBAF97DA__INCLUDED_)
#define AFX_JSNETDEMO_H__CF0A66A1_A3B2_4E67_8A5D_8B29DBAF97DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CNetsdkDemoApp:
// See JSNetDemo.cpp for the implementation of this class
//

#include "LangMan.h"
class CNetsdkDemoApp : public CWinApp
{
public:
	CLangMan m_lang;
	CNetsdkDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetsdkDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CNetsdkDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CNetsdkDemoApp theApp;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JSNETDEMO_H__CF0A66A1_A3B2_4E67_8A5D_8B29DBAF97DA__INCLUDED_)
