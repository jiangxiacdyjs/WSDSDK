// 3DRectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "netsdk_demo.h"
#include "3DRectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// C3DRectDlg dialog


C3DRectDlg::C3DRectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(C3DRectDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(C3DRectDlg)
	m_nBottom = 50;
	m_nLeft = 0;
	m_nRight = 50;
	m_nTop = 0;
	m_nZoom = 0;
	//}}AFX_DATA_INIT
}


void C3DRectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(C3DRectDlg)
	DDX_Text(pDX, IDC_EDIT_BOTTOM, m_nBottom);
	DDX_Text(pDX, IDC_EDIT_LEFT, m_nLeft);
	DDX_Text(pDX, IDC_EDIT_RIGHT, m_nRight);
	DDX_Text(pDX, IDC_EDIT_TOP, m_nTop);
	DDX_Radio(pDX, IDC_RADIO_ZOOM_IN, m_nZoom);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(C3DRectDlg, CDialog)
	//{{AFX_MSG_MAP(C3DRectDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C3DRectDlg message handlers
