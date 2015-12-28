#pragma once
#include "afxwin.h"

#include "3DPositioningWnd.h"

#define CLASS_CVideoWndBase		_T("CVideoWndBase")
#define COLORREF_BK_OVERLAY				RGB(1,1,1)
#define COLORREF_BK_NOT_OVERLAY	RGB(5,5,5)

typedef enum{
    VIDEO_WND_MSG_LBUTTON_DBL_CLK = 0,
    VIDEO_WND_MSG_REGION_SELECT ,
};

typedef struct  
{
    int x;
    int y;
    int vw;
    int vh;
}VIDEO_WND_LBUTTON_DBL_CLK_POINT_T;

typedef struct  
{
    int x;
    int y;
    int w;
    int h;
    int vw;
    int vh;
    BOOL zoom;
}VIDEO_WND_REGION_T;

typedef void (* VIDEO_WND_MSG_CALLBACK)(UINT nMsg, LPVOID pParam, DWORD dwSize, PVOID pUserData);

class CVideoWndBase :
    public CWnd
{
protected:
    VIDEO_WND_MSG_CALLBACK   m_msgCallback;
    PVOID                   m_msgUserData;
    C3DPositioningWnd       * m_p3dWnd;
    CRect                   m_rc3D;
    CPoint                  m_ptLeftTop;
    BOOL	                m_bTrackLeave;
    CPoint                  m_ptNow;
    CString                 m_str3D;
    BOOL                    m_bPositioning;
public:
    void    EnableRegionSelector(BOOL bEnable)
    {
        m_bPositioning = bEnable;
    }

    void SetWndMsgCallback(VIDEO_WND_MSG_CALLBACK cb, PVOID pUserData)
    {
        m_msgCallback = cb;
        m_msgUserData = pUserData;
    }
    BOOL	Create(UINT uID, RECT &rect, CWnd *pParentWnd,
        DWORD dwStyle = WS_CLIPCHILDREN | WS_TABSTOP | WS_VISIBLE | WS_CHILDWINDOW);
public:
    CVideoWndBase(void);
    ~CVideoWndBase(void);
    DECLARE_MESSAGE_MAP()
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
protected:
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg LRESULT OnMouseLeave(WPARAM wparam,LPARAM lparam);
};
